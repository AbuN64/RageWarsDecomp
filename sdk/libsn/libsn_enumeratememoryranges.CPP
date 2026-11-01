#include "TYPES.H"
#include "IO/DEBUG_MEMORY.H"

/* Rebuild the debugger memory map: entries 16-47 describe the valid pages of the 32 TLB entries
 * (snapshot taken by Libgultra_TrwReadTlbEntry), entries 0-15 copy the static region table from
 * KSEG0 (0x80000000) up to the end marker (last == 0xFFFFFFFF); unused entries get first = -1. */
void Libsn_EnumerateMemoryRanges(void) {
    u32 addressSpaceId, pageMask, entryHi, entryLo0, entryLo1, pageSize, first, rangeCount, supportedMask, i;
    u32 *entry;
    u32 *boundary;
    u32 *supportedMasks;
    addressSpaceId = Libgultra_TrwReadTlbEntry() & 0xFF;
    entry = &g_libsnPageTableEntries[0].pageMask;
    for (i = 16; i < 48; i++) {
        g_libsnHostMemoryRanges[i].first = -1;
        g_libsnHostMemoryRanges[i].flags = 0;
        pageMask = *entry++;
        entryHi = *entry++;
        entryLo0 = *entry++;
        entryLo1 = *entry++;
        if ((entryLo0 | entryLo1) & TLBLO_V) {
            pageMask &= OS_PM_16M;
            supportedMasks = g_libsnSupportedPageMasks;
            pageSize = 0x1000;
            while (1) {
                supportedMask = *supportedMasks;
                if (supportedMask == pageMask) break;
                supportedMasks++;
                if (supportedMask & 0x80000000) {
                    pageSize = 0;
                    break;
                }
                pageSize <<= 2;
            }
            if (pageSize != 0) {
                if ((entryLo0 & entryLo1 & (TLBLO_V | TLBLO_G)) != (TLBLO_V | TLBLO_G)) {
                    if ((entryLo0 & (TLBLO_V | TLBLO_G)) == TLBLO_V && (entryHi & TLBHI_PIDMASK) != addressSpaceId) entryLo0 &= ~TLBLO_V;
                    if ((entryLo1 & (TLBLO_V | TLBLO_G)) == TLBLO_V && (entryHi & TLBHI_PIDMASK) != addressSpaceId) entryLo1 &= ~TLBLO_V;
                }
                first = entryHi & TLBHI_VPN2MASK;
                if (entryLo0 & entryLo1 & TLBLO_V) pageSize <<= 1;
                else if (entryLo1 & TLBLO_V) first += pageSize;
                g_libsnHostMemoryRanges[i].first = first;
                g_libsnHostMemoryRanges[i].last = first + pageSize - 1;
                g_libsnHostMemoryRanges[i].flags = MEMORY_READ | MEMORY_WRITE;
            }
        }
    }
    boundary = &g_libsnDefaultMemoryRanges[0].last;
    first = 0x80000000;
    while (*boundary < first) boundary += 2;
    rangeCount = 0;
    do {
        g_libsnHostMemoryRanges[rangeCount].first = first;
        g_libsnHostMemoryRanges[rangeCount].last = *boundary++;
        g_libsnHostMemoryRanges[rangeCount].flags = *boundary++;
        first = g_libsnHostMemoryRanges[rangeCount].last + 1;
        rangeCount++;
    } while (first != 0);
    for (; rangeCount < 16; rangeCount++) {
        g_libsnHostMemoryRanges[rangeCount].first = -1;
        g_libsnHostMemoryRanges[rangeCount].flags = 0;
    }
}
