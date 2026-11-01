#include "COMMON/PACKEDMESHMATERIAL.H"
#include "TYPES.H"
#include "ENGINE/PPDECOM.H"
#include <ultra64.h>

/* Sorts num elements of the given width with a comparator and a swap routine using an iterative quicksort: partitions around the middle element, pushes the larger side onto a 30-entry stack and continues with the smaller, and hands ranges of eight or fewer elements to PpDecom_SelectionSortRange. Written from the classic iterative quicksort structure. */

void PpDecom_QuickSortRecords(char *base, u32 num, u32 width, s32 (*compare)(char *, char *), void (*swap)(char *, char *)) {
    char *lo;
    char *hi;
    char *loguy;
    char *higuy;
    u32 size;
    char *lostk[30];
    char *histk[30];
    s32 stkptr;

    if (num < 2 || width == 0) {
        return;
    }
    stkptr = 0;
    lo = base;
    hi = base + width * (num - 1);
recurse:
    size = (hi - lo) / width + 1;
    if (size <= 8) {
        PpDecom_SelectionSortRange((u32)lo, (u32)hi, width, (s32 (*)(u32, u32))compare, (void (*)(u32, u32))swap);
    } else {
        swap(lo + (size / 2) * width, lo);
        loguy = lo;
        higuy = hi + width;
        for (;;) {
            do {
                loguy += width;
            } while (loguy <= hi && compare(loguy, lo) <= 0);
            do {
                higuy -= width;
            } while (higuy > lo && compare(higuy, lo) >= 0);
            if (higuy < loguy) {
                break;
            }
            swap(loguy, higuy);
        }
        swap(lo, higuy);
        if (higuy - 1 - lo >= hi - loguy) {
            if (lo + width < higuy) {
                lostk[stkptr] = lo;
                histk[stkptr] = higuy - width;
                ++stkptr;
            }
            if (loguy < hi) {
                lo = loguy;
                goto recurse;
            }
        } else {
            if (loguy < hi) {
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;
            }
            if (lo + width < higuy) {
                hi = higuy - width;
                goto recurse;
            }
        }
    }
    --stkptr;
    if (stkptr >= 0) {
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;
    }
}

/* Sorts fixed-stride records by selecting a maximum and swapping it to the end. */
void PpDecom_SelectionSortRange(u32 firstRecord, u32 lastRecord, s32 width, s32 (*compareRecords)(u32, u32), void (*swapRecords)(u32, u32)) {
    u32 candidateRecord;
    u32 scanRecord;
    u32 greatestRecord;
    u32 unsortedLastRecord;
    unsortedLastRecord = lastRecord;
    if (firstRecord < unsortedLastRecord) {
        scanRecord = firstRecord + width;
        do {
            do { greatestRecord = firstRecord; } while (0);
            if (unsortedLastRecord >= scanRecord) {
                candidateRecord = scanRecord;
                do {
                    if (compareRecords(candidateRecord, greatestRecord) > 0) {
                        greatestRecord = scanRecord;
                    }
                    scanRecord += width;
                    candidateRecord = scanRecord;
                } while (unsortedLastRecord >= scanRecord);
            }
            swapRecords(greatestRecord, unsortedLastRecord);
            unsortedLastRecord -= width;
            scanRecord = firstRecord + width;
        } while (firstRecord < unsortedLastRecord);
    }
}
