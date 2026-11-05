#include "Common/matrixrecord.h"
#include "Common/rotation_extraction.h"
#include "types.h"
#include "Math/math_double.h"
#include "Ui/X_files/x_plus.h"
#include "Common/messagesemaphore.h"
#include "include_asm.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include <platform_sdk.h>
#include "Resmgr/resmgr_string_memory.h"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Data/rest_source_records.h"

/* Copies n bytes between possibly overlapping buffers and returns the destination: forwards when the destination is below the source and backwards otherwise, aligning to a word boundary with single bytes when both pointers share alignment, then copying whole words and the remaining bytes. */

char *XPlus_MoveMemory(char *dst, const char *src, s32 length) {
    char *dstCursor;
    s32 count;

    dstCursor = dst;
    if (length == 0 || dst == src) {
        return dst;
    }
    if (dst < src) {
        count = (s32)src;
        if ((count | (s32)dst) & 3) {
            if ((count ^ (s32)dst) & 3) {
                count = length;
            } else if (length < 4) {
                count = length;
            } else {
                count = 4 - (count & 3);
            }
            length -= count;
            do {
                *dstCursor++ = *src++;
            } while (--count != 0);
        }
        count = (u32)length >> 2;
        if (count != 0) {
            do {
                *(s32 *)dstCursor = *(const s32 *)src;
                src += 4;
                dstCursor += 4;
            } while (--count != 0);
        }
        count = length & 3;
        if (count != 0) {
            do {
                *dstCursor++ = *src++;
            } while (--count != 0);
        }
    } else {
        src += length;
        dstCursor = dst + length;
        count = (s32)src;
        if ((count | (s32)dstCursor) & 3) {
            if ((count ^ (s32)dstCursor) & 3) {
                count = length;
            } else if (length < 5) {
                count = length;
            } else {
                count &= 3;
            }
            length -= count;
            do {
                *--dstCursor = *--src;
            } while (--count != 0);
        }
        count = (u32)length >> 2;
        if (count != 0) {
            do {
                src -= 4;
                dstCursor -= 4;
                *(s32 *)dstCursor = *(const s32 *)src;
            } while (--count != 0);
        }
        count = length & 3;
        if (count != 0) {
            do {
                *--dstCursor = *--src;
            } while (--count != 0);
        }
    }
    return dst;
}

f64 XPlus_ParseDecimalDouble(u8 *text) {
    f64 sign;
    f64 divisor;
    f64 value;
    f64 fraction;
    f64 exponentSign;
    f64 exponent;
    f64 scale;
    f64 threshold;

    sign = k_decimalInitialSign;
    fraction = k_decimalInitialFraction;
    divisor = sign;
    if (*text == 32) {
        do {
            text++;
        } while (*text == 32);
    }
    if (*text == 45) {
        text++;
        sign = k_decimalNegativeSign;
    }
    if (*text == 43) {
        text++;
    }

    value = k_decimalInitialInteger;
    if ((u32)(*text - 48) < 10) {
        do {
            value = value * k_decimalIntegerRadix + (f64)(*text - 48);
            text++;
        } while ((u32)(*text - 48) < 10);
    }

    if (*text == 46) {
        text++;
        fraction = k_decimalFractionZero;
        if ((u32)(*text - 48) < 10) {
            do {
                divisor *= k_decimalFractionRadix;
                fraction = fraction * k_decimalFractionRadix + (f64)(*text - 48);
                text++;
            } while ((u32)(*text - 48) < 10);
        }
    }

    if (*text == 101 || *text == 69) {
        text++;
        exponentSign = k_decimalInitialExponentSign;
        if (*text == 45) {
            text++;
            exponentSign = k_decimalNegativeExponentSign;
        }
        if (*text == 43) {
            text++;
        }
        exponent = k_decimalInitialExponent;
        if ((u32)(*text - 48) < 10) {
            do {
                exponent = exponent * k_decimalExponentRadix + (f64)(*text - 48);
                text++;
            } while ((u32)(*text - 48) < 10);
        }
        if (exponent < k_decimalDirectExponentLimit) {
            threshold = k_decimalExponentLoopLimit;
            scale = k_decimalInitialExponentScale;
            if (exponent == threshold) {
                goto compare_sign;
            } else {
                do {
                    scale *= k_decimalExponentScaleRadix;
                    exponent -= k_decimalInitialExponentScale;
                } while (exponent != threshold);
            }
            goto set_threshold;
        } else {
            scale = XMath_PowerDouble(k_decimalPowerRadix, exponent);
        }
set_threshold:
        threshold = k_decimalOverflowExponentLimit;
compare_sign:
        if (exponentSign < threshold) {
            return sign * (value + fraction / divisor) / scale;
        }
        return sign * (value + fraction / divisor) * scale;
    }
    return sign * (value + fraction / divisor);
}

/* Splits a path into drive, directory, file name and extension like _splitpath: a leading "X:" goes to the drive, everything through the last '/' or '\\' to the directory, the rest up to the last '.' at or after that point to the name and from the '.' on to the extension (or all of it to the name when there is none), each copied with a bounded strncpy and terminated, and any missing part cleared. */

static inline s32 path_length(u8 *text) {
    u8 *end = text;

    while (*end++) {
    }
    return end - text - 1;
}

static inline void copy_part(u8 *dst, u8 *src, s32 limit) {
    if (limit != 0) {
    copy:
        if ((*dst++ = *src++) != 0) {
            if (--limit != 0) {
                goto copy;
            }
        }
        if (limit != 0) {
            while (--limit != 0) {
                *dst++ = 0;
            }
        }
    }
}

void XPlus_SplitPath(u8 *path, u8 *drive, u8 *dir, u8 *name, u8 *ext) {
    u8 *dot;
    u8 *slash;
    u8 *scan;
    s32 length;

    slash = 0;
    dot = 0;
    if (path_length(path) > 0 && path[1] == ':') {
        if (drive != 0) {
            copy_part(drive, path, 2);
            drive[2] = 0;
        }
        path += 2;
    } else if (drive != 0) {
        *drive = 0;
    }
    for (scan = path; *scan != 0; scan++) {
        if (*scan == '/' || *scan == '\\') {
            slash = scan + 1;
        } else if (*scan == '.') {
            dot = scan;
        }
    }
    if (slash != 0) {
        if (dir != 0) {
            length = slash - path;
            if (length >= 0x100) {
                length = 0xFF;
            }
            copy_part(dir, path, length);
            dir[length] = 0;
        }
        path = slash;
    } else if (dir != 0) {
        *dir = 0;
    }
    if (dot != 0 && dot >= path) {
        if (name != 0) {
            length = dot - path;
            if (length >= 0x100) {
                length = 0xFF;
            }
            copy_part(name, path, length);
            name[length] = 0;
        }
        if (ext != 0) {
            length = scan - dot;
            if (length >= 0x100) {
                length = 0xFF;
            }
            copy_part(ext, dot, length);
            ext[length] = 0;
        }
    } else {
        if (name != 0) {
            length = scan - path;
            if (length >= 257) {
                length = 0x100;
            }
            copy_part(name, path, length);
            name[length] = 0;
        }
        if (ext != 0) {
            *ext = 0;
        }
    }
}

/* Quick-sorts the elements between base and max for XPlus_SortArray (the qsort helper qst): picks the median of the first, middle and last elements as the pivot when the span reaches the six-element threshold g_xplusSortMedianThreshold, partitions around it with the comparator g_xplusSortComparator swapping g_xplusSortElementSize bytes at a time, then recurses into the smaller side and loops on the larger while it spans at least g_xplusSortPartitionThreshold bytes. Written from the BSD qsort qst structure with the halving shift unsigned. */

void XPlus_PartitionSortRange(char *base, char *max) {
    char swapByte;
    char *lowScan;
    char *highScan;
    char *swapTarget;
    s32 swapCount;
    char *pivot;
    char *nextLowScan;
    s32 spanBytes;
    s32 upperSpanBytes;

    spanBytes = max - base;
    do {
        pivot = lowScan = base + g_xplusSortElementSize * ((unsigned)(spanBytes / g_xplusSortElementSize) >> 1);
        if (spanBytes >= g_xplusSortMedianThreshold) {
            highScan = (g_xplusSortComparator((swapTarget = base), lowScan) > 0 ? swapTarget : lowScan);
            if (g_xplusSortComparator(highScan, (nextLowScan = max - g_xplusSortElementSize)) > 0) {
                highScan = (highScan == swapTarget ? lowScan : swapTarget);
                if (g_xplusSortComparator(highScan, nextLowScan) < 0) {
                    highScan = nextLowScan;
                }
            }
            if (highScan != lowScan) {
                swapCount = g_xplusSortElementSize;
                do {
                    swapByte = *lowScan;
                    *lowScan++ = *highScan;
                    *highScan++ = swapByte;
                } while (--swapCount);
            }
        }
        for (lowScan = base, highScan = max - g_xplusSortElementSize;;) {
            while (lowScan < pivot && g_xplusSortComparator(lowScan, pivot) <= 0) {
                lowScan += g_xplusSortElementSize;
            }
            while (highScan > pivot) {
                if (g_xplusSortComparator(pivot, highScan) <= 0) {
                    highScan -= g_xplusSortElementSize;
                    continue;
                }
                nextLowScan = lowScan + g_xplusSortElementSize;
                if (lowScan == pivot) {
                    pivot = swapTarget = highScan;
                } else {
                    swapTarget = highScan;
                    highScan -= g_xplusSortElementSize;
                }
                goto swap;
            }
            if (lowScan == pivot) {
                break;
            } else {
                swapTarget = pivot;
                nextLowScan = pivot = lowScan;
                highScan -= g_xplusSortElementSize;
            }
swap:
            swapCount = g_xplusSortElementSize;
            do {
                swapByte = *lowScan;
                *lowScan++ = *swapTarget;
                *swapTarget++ = swapByte;
            } while (--swapCount);
            lowScan = nextLowScan;
        }
        lowScan = (highScan = pivot) + g_xplusSortElementSize;
        if ((spanBytes = highScan - base) <= (upperSpanBytes = max - lowScan)) {
            if (spanBytes >= g_xplusSortPartitionThreshold) {
                XPlus_PartitionSortRange(base, highScan);
            }
            base = lowScan;
            spanBytes = upperSpanBytes;
        } else {
            if (upperSpanBytes >= g_xplusSortPartitionThreshold) {
                XPlus_PartitionSortRange(lowScan, max);
            }
            max = highScan;
        }
    } while (spanBytes >= g_xplusSortPartitionThreshold);
}

/* Sorts n elements of the given size with a comparator (qsort): records the element size, the four- and six-element thresholds and the comparator in g_xplusSortElementSize to g_xplusSortComparator, quick-sorts arrays of four or more through XPlus_PartitionSortRange, swaps the smallest of the first elements into place as a sentinel, and finishes with an insertion sort that shifts bytes. Written from the BSD qsort driver structure. */

void XPlus_SortArray(char *base, s32 count, s32 elementSize, s32 (*compareElements)(char *left, char *right)) {
    char swapByte;
    char *dstScan;
    char *minScan;
    char *probe;
    char *insertionLimit;
    char *sortedEnd;
    char *arrayEnd;

    if (count <= 1) {
        return;
    }
    g_xplusSortPartitionThreshold = elementSize * 4;
    g_xplusSortMedianThreshold = elementSize * 6;
    g_xplusSortElementSize = elementSize;
    g_xplusSortComparator = compareElements;
    arrayEnd = base + count * elementSize;
    if (count >= 4) {
        XPlus_PartitionSortRange(base, arrayEnd);
        insertionLimit = base + g_xplusSortPartitionThreshold;
    } else {
        insertionLimit = arrayEnd;
    }
    for (minScan = probe = base; (probe += g_xplusSortElementSize) < insertionLimit;) {
        if (g_xplusSortComparator(minScan, probe) > 0) {
            minScan = probe;
        }
    }
    if (minScan != base) {
        for (dstScan = base, insertionLimit = base + g_xplusSortElementSize; dstScan < insertionLimit;) {
            swapByte = *minScan;
            *minScan++ = *dstScan;
            *dstScan++ = swapByte;
        }
    }
    for (sortedEnd = base; (insertionLimit = sortedEnd += g_xplusSortElementSize) < arrayEnd;) {
        while (g_xplusSortComparator(insertionLimit -= g_xplusSortElementSize, sortedEnd) > 0) {
        }
        if ((insertionLimit += g_xplusSortElementSize) != sortedEnd) {
            for (probe = sortedEnd + g_xplusSortElementSize; --probe >= sortedEnd;) {
                swapByte = *probe;
                for (dstScan = minScan = probe; (minScan -= g_xplusSortElementSize) >= insertionLimit; dstScan = minScan) {
                    *dstScan = *minScan;
                }
                *dstScan = swapByte;
            }
        }
    }
}

void *XPlus_FillMemory(void *destination, int fillValue, u32 byteCount) {
    u8 *start;
    u8 *end;
    u8 *cur;
    u8 *next;
    u32 byte;
    u32 word;

    start = destination;
    end = start + byteCount;
    byte = fillValue & 0xFF;
    word = (byte << 24) | (byte << 16) | (byte << 8) | byte;
    cur = start;

    if (cur >= end) {
        goto word_test;
    }
align_test:
    if (!((u32)cur & 3)) {
        goto word_test;
    }
    *cur = fillValue;
    cur += 1;
    if (cur < end) {
        goto align_test;
    }
    goto word_test;

word_test:
    next = cur + 4;
    while (next < end) {
        *(u32 *)cur = word;
        cur = next;
        next = cur + 4;
    }

    if (cur < end) {
        do {
            *cur++ = fillValue;
        } while (cur < end);
    }
    return start;
}

s32 XPlus_SearchSortedArray(s32 *index, u8 *base, s32 count, void *key,
                     s32 stride, s32 (*compare)(void *, void *)) {
    s32 low = 0;
    s32 half = 0;
    s32 high = count - 1;
    s32 result;
    u8 *entry;
    if (index != 0) {
        *index = 0;
    }
    if (count != 0) {
        while (low <= high) {
            half = (high - low) >> 1;
            entry = base + (low + half) * stride;
            result = compare(key, entry);
            if (result < 0) {
                goto less;
            }
            if (result != 0) {
                goto more;
            }

            while ((entry -= stride) > base && compare(key, entry) == 0) {
                half--;
            }
            if (index != 0) {
                *index = low + half;
            }
            return 1;
more:
            low += half + 1;
            continue;
less:
            high -= half + 1;
        }
        if (index != 0) {
            *index = low + half;
        }
    }
    return 0;
}

void XPlus_SeedRandomGenerator(int seed) {
    g_xplusRandomState = seed;
}

s32 XPlus_NextRandomInteger(void) {
    s32 nextState;

    nextState = (g_xplusRandomState * 0x343FD) + 0x269EC3;
    g_xplusRandomState = nextState;
    return (nextState >> 16) & 0x7FFF;
}

/** Return strlen(string) (byte count not including the terminating NUL). */
s32 XPlus_StringLength(const char *string) {
    const char *cursor;
    u8 c;

    cursor = string + 1;
    if (*string != 0) {
        do {
            c = *cursor;
            cursor += 1;
        } while (c != 0);
    }
    return (cursor - string) - 1;
}

u8 *XPlus_CopyString(u8 *destination, u8 *source) {
    u8 *destCursor;
    u8 c;

    c = *source;
    source++;
    *destination = c;
    destCursor = destination + 1;
    if (c != 0) {
        do {
            c = *source;
            source++;
            *destCursor = c;
            destCursor++;
        } while (c != 0);
    }
    return destination;
}

/** strncpy: copy up to count bytes from source to destination, NUL-padding the remainder. */
u8 *XPlus_CopyStringBounded(u8 *destination, u8 *source, s32 count) {
    s32 remaining;
    u8 *start;
    u8 *destCursor;
    u8 *sourceCursor;
    u8 c;

    destCursor = destination;
    sourceCursor = source;
    remaining = count;
    start = destCursor;
    if (remaining != 0) {
    loop_1:
        c = *sourceCursor;
        sourceCursor += 1;
        *destCursor = c;
        destCursor += 1;
        if (c & 0xFF) {
            remaining -= 1;
            if (remaining != 0) {
                goto loop_1;
            }
        }
        if (remaining != 0) {
            remaining -= 1;
            if (remaining != 0) {
                do {
                    *destCursor = 0;
                    remaining -= 1;
                    destCursor += 1;
                } while (remaining != 0);
            }
        }
    }
    return start;
}

u8 *XPlus_AppendString(u8 *destination, u8 *source) {
    u8 *sourceCursor;
    u8 *destCursor;
    u8 c;
    sourceCursor = source;
    destCursor = destination;
    if (*destination != 0) {
        do {
            destCursor += 1;
        } while (*destCursor != 0);
    }
    do {
        c = *sourceCursor;
        sourceCursor += 1;
        *destCursor = c;
        destCursor += 1;
    } while (c & 0xFF);
    return destination;
}

u8 *XPlus_AppendStringBounded(u8 *destination, u8 *source, s32 count) {
    u8 *end = destination + 1;
    u8 byte;
    if (*destination != 0) {
        do { } while (*end++ != 0);
    }
    --end;
    while (count-- != 0) {
        byte = *source++;
        *end++ = byte;
        if (!(byte & 0xFF)) return destination;
    }
    *end = 0;
    return destination;
}

s32 XPlus_CompareStrings(const void *leftString, const void *rightString) {
    const u8 *a = leftString;
    const u8 *b = rightString;
    s32 difference;

    while ((difference = *a - *b) == 0) {
        if (*b == 0) {
            break;
        }
        a++;
        b++;
    }
    return difference;
}

s32 XPlus_CompareStringsBounded(u8 *a, u8 *b, s32 count) {
    u8 *aCursor;
    u8 *bCursor;
    u8 c;
    aCursor = a;
    bCursor = b;
    if (count == 0) {
        return 0;
    }
    count -= 1;
    while (count != 0 && (c = *aCursor) != 0 && c == *bCursor) {
        count -= 1;
        aCursor += 1;
        bCursor += 1;
    }
    return *aCursor - *bCursor;
}

s32 XPlus_CompareStringsIgnoreCase(u8 *a, u8 *b)
{
  s32 c2;
  int letterA;
  s32 c1;
  c2 = *b;
  b += 1;
  letterA = 65;
  if (c2 >= letterA)
  {
    if (c2 < 91)
    {
      c2 += 32;
    }
  }
  c1 = *a;
  a += 1;
  if (c1 >= letterA)
  {
    if (c1 < 91)
    {
      c1 += 32;
    }
  }
  if (c2 != 0)
  {
    if (c2 == c1)
    {
      return XPlus_CompareStringsIgnoreCase(a, b);
    }
  }
  return c1 - c2;
}

/* Returns a pointer to the last occurrence of a character in a string, or 0 when it does not occur
   (strrchr). */
u8 *XPlus_FindLastCharacter(u8 *s, int c) {
    u8 *start = s;
    while (*s++ != 0) {
    }
    s--;
    for (; s != start; s--) {
        if (*s == (u8)c) {
            break;
        }
    }
    if (*s == (u8)c) {
        return s;
    }
    return 0;
}

/** In-place ASCII-uppercase a NUL-terminated string; NULL-safe. */
u8 *XPlus_UppercaseString(u8 *string) {
    u8 *cursor;
    u8 c;
    cursor = string;
    if (string == 0) {
        return 0;
    }
    if (*string != 0) {
        do {
            c = *cursor;
            if ((u32)(c - 97) < 26U) {
                *cursor = c - 32;
            }
            cursor += 1;
        } while (*cursor != 0);
    }
    return string;
}

/** In-place ASCII-lowercase a NUL-terminated string; NULL-safe. */
u8 *XPlus_LowercaseString(u8 *string) {
    u8 *cursor;
    u8 c;
    cursor = string;
    if (string == 0) {
        return 0;
    }
    if (*string != 0) {
        do {
            c = *cursor;
            if ((u32)(c - 65) < 26U) {
                *cursor = c + 32;
            }
            cursor += 1;
        } while (*cursor != 0);
    }
    return string;
}

/* Searches a zero-terminated byte string for a pattern and returns the position just past the first match, or zero when there is none. */
u8 *XPlus_FindPatternEnd(u8 *text, u8 *pattern) {
    u8 *match;
    while (*text != 0) {
        while (*text != 0 && *text != *pattern) {
            text++;
        }
        match = pattern;
        while (*match != 0 && *text == *match) {
            match++;
            text++;
        }
        if (*match == 0) {
            return text;
        }
    }
    return 0;
}

/** Convert a lowercase ASCII letter to uppercase. */
int XPlus_UppercaseCharacter(int c) {
    if ((unsigned int)(c - 'a') < 26) {
        c -= 'a' - 'A';
    }
    return c;
}

/** Convert an uppercase ASCII letter to lowercase. */
int XPlus_LowercaseCharacter(int c) {
    if ((unsigned int)(c - 'A') < 26) {
        c += 'a' - 'A';
    }
    return c;
}

/* Parses a signed decimal integer from a string, skipping leading spaces and one optional sign (atoi). */
s32 XPlus_ParseDecimalInteger(u8 *text) {
    s32 value;
    s32 digit;
    u8 sign;
    while (*text == ' ') {
        text++;
    }
    digit = *text;
    sign = digit;
    text++;
    if (sign == '-' || sign == '+') {
        digit = *text;
        text++;
    }
    value = 0;
    while (digit >= '0' && digit <= '9') {
        value = (digit - '0') + value * 10;
        digit = *text;
        text++;
    }
    if (sign == '-') {
        return -value;
    }
    return value;
}

/* Formats a signed integer as a NUL-terminated decimal string (K&R itoa with the reverse inlined). */
void XPlus_FormatDecimalInteger(s32 n, char *s) {
    s32 i;
    s32 j;
    s32 sign;
    s32 len;
    char c;
    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    len = i;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    s[len] = '\0';
}

void *XPlus_CopyBytes(void *destination, const void *source, s32 bytes) {
    void *result = destination;
    if (bytes != 0) {
        result = XPlus_MoveMemory(destination, source, bytes);
    }
    return result;
}

/* Fills count bytes at destination with the byte value, storing single bytes up to word alignment, replicated words through the middle and single bytes at the tail, and returns destination. Adapted from XPlus_FillMemory. */
void *XPlus_FillBytes(void *destination, int value, u32 count) {
    u8 *start;
    u8 *end;
    u8 *cur;
    u8 *next;
    u32 fillByte;
    u32 fillWord;
    start = destination;
    end = start + count;
    fillByte = value & 0xFF;
    fillWord = (fillByte << 24) | (fillByte << 16) | (fillByte << 8) | fillByte;
    cur = start;
    if (cur >= end) {
        goto word_test;
    }
align_test:
    if (!((u32)cur & 3)) {
        goto word_test;
    }
    *cur = value;
    cur += 1;
    if (cur < end) {
        goto align_test;
    }
    goto word_test;
word_test:
    next = cur + 4;
    while (next < end) {
        *(u32 *)cur = fillWord;
        cur = next;
        next = cur + 4;
    }
    if (cur < end) {
        do {
            *cur++ = value;
        } while (cur < end);
    }
    return start;
}

u8 *XPlus_FindByte(u8 *buffer, s32 value, s32 length) {
    u8 *cursor;
    s32 count;
    cursor = buffer;
    count = length;
    if (count != 0) {
        value = value & 0xFF;
loop:
        if (*cursor != value) {
            count -= 1;
            cursor += 1;
            if (count != 0) {
                goto loop;
            }
        }
    }
    if (count == 0) {
        return 0;
    }
    return cursor;
}

s32 XPlus_CompareMemory(u8 *a, u8 *b, s32 count) {
    u8 *aCursor;
    u8 *bCursor;
    u8 *end;
    u8 bByte;
    u8 aByte;
    aCursor = a;
    bCursor = b;
    end = aCursor + count;
    if (count < 4) {
        goto block_17;
    }
    if ((u32)aCursor & 3) {
        goto block_17;
    }
    if ((u32)bCursor & 3) {
        goto block_17;
    }
    end -= 4;
    if (end < aCursor) {
        end += 4;
        goto block_16;
    }
loop_6:
    if (*(u32 *)aCursor != *(u32 *)bCursor) {
        aCursor -= 4;
        bCursor -= 4;
        goto block_11;
    }
    aCursor += 4;
    bCursor += 4;
    if (end >= aCursor) {
        goto loop_6;
    }
block_11:
    end += 4;
    goto block_16;
block_12:
    aByte = *aCursor;
    bByte = *bCursor;
    if (aByte == bByte) {
        aCursor += 1;
        bCursor += 1;
        goto block_16;
    }
    if (aByte < bByte) {
        return -1;
    }
    return 1;
block_16:
    ;
block_17:
    if (aCursor < end) {
        goto block_12;
    }
    return 0;
}

/** Compute a CRC-32 over length bytes, continuing from crc. */
u32 XPlus_UpdateCrc32(u8 *data, u32 length, u32 crc) {
    u32 table[256];
    u32 i;
    u32 j;
    u32 value;
    u32 shifted;
    u8 *end;
    for (i = 0; i < 256; i++) {
        value = i;
        for (j = 0; j < 8; j++) {
            shifted = value >> 1;
            if (value & 1) {
                shifted ^= 0xEDB88320U;
            }
            value = shifted;
        }
        table[i] = value;
    }
    end = data + length;
    crc = ~crc;
    while (data < end) {
        crc = table[(crc ^ *data++) & 0xFF] ^ ((crc >> 8) & 0xFFFFFF);
    }
    return ~crc;
}

/* Builds a path from drive, directory, filename and extension components. */
void XPlus_BuildPath(u8 *path, u8 *drive, u8 *directory, u8 *name, u8 *extensionArg) {
    u8 *extension = extensionArg;
    u8 *out;
    u8 *cursor;
    u8 driveLetter;
    u8 lastDirChar;
    u8 dirChar;
    u8 extFirst;
    u8 nameChar;
    u8 extChar;
    out = path;
    cursor = directory;
    if (drive != 0) {
        driveLetter = *drive;
        if (driveLetter != 0) {
            *out++ = driveLetter;
            *out++ = 58;
        }
    }
    if ((cursor != 0) && (*cursor != 0)) {
        do {
            dirChar = *cursor;
            cursor += 1;
            *out = dirChar;
            out += 1;
        } while (cursor[0] != 0);
        lastDirChar = cursor[-1];
        if ((lastDirChar != 47) && (lastDirChar != 92)) {
            *out = 92;
            out += 1;
        }
    }
    if (name != 0) {
        nameChar = *name;
        cursor = name;
        if (nameChar != 0) {
            do {
                cursor += 1;
                *out = nameChar;
                nameChar = *cursor;
                out += 1;
            } while (nameChar != 0);
        }
    }
    if (extension != 0) {
        cursor = extension;
        extFirst = *cursor;
        if (extFirst != 0) {
            if (extFirst != 46) {
                *out = 46;
                out += 1;
            }
            extChar = *cursor;
            if (extChar != 0) {
                do {
                    cursor += 1;
                    *out = extChar;
                    extChar = *cursor;
                    out += 1;
                } while (extChar != 0);
            }
        }
    }
    *out = 0;
}

void XPlus_InitializeSemaphore(void *messageSemaphore) {
    MessageSemaphore *semaphore = messageSemaphore;
    osCreateMesgQueue(messageSemaphore, &semaphore->message, 1);
    osSendMesg(messageSemaphore, 1, 1);
}

void XPlus_AcquireSemaphore(s32 queue) {
    osRecvMesg(queue, queue + 24, 1);
}

void XPlus_ReleaseSemaphore(s32 *queue) {
    osSendMesg(queue, 1, 1);
}

#if defined(VERSION_US)
/* Zero word ending X_PLUS's object; no instruction reads it. */
unsigned int g_xPlusReleaseSemaphoreZeroTail[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
XplusNextrandomintegerEncodedWordsLayout g_XplusNextrandomintegerData = {
    1,
    "re\000\000"
};
#endif

#if defined(VERSION_US_REV1)
const float k_xplusParsedecimaldoubleDataFloatConstants[34] = {
    1.875f, 0.0f, 0.0f, 0.0f, -1.875f, 0.0f,
    0.0f, 0.0f, 2.5625f, 0.0f, 0.0f, 0.0f,
    2.5625f, 0.0f, 1.875f, 0.0f, -1.875f, 0.0f,
    0.0f, 0.0f, 2.5625f, 0.0f, 2.96875f, 0.0f,
    0.0f, 0.0f, 1.875f, 0.0f, 2.5625f, 0.0f,
    2.5625f, 0.0f, 0.0f, 0.0f,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const f32 k_xplusParsedecimaldoubleDataConstants[34] = {
    1.875f, 0.0f, 0.0f, 0.0f, -1.875f, 0.0f,
    0.0f, 0.0f, 2.5625f, 0.0f, 0.0f, 0.0f,
    2.5625f, 0.0f, 1.875f, 0.0f, -1.875f, 0.0f,
    0.0f, 0.0f, 2.5625f, 0.0f, 2.96875f, 0.0f,
    0.0f, 0.0f, 1.875f, 0.0f, 2.5625f, 0.0f,
    2.5625f, 0.0f, 0.0f, 0.0f,
};
#endif
