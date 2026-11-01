#ifndef IO_DEBUG_MEMORY_H
#define IO_DEBUG_MEMORY_H
#include "TYPES.H"
extern s8 g_libsnMonitorEnabled;
/* Inclusive address ranges and transfer permissions, populated by the
 * debug memory-map enumerator. */
typedef struct MemoryRange { u32 first, last, flags; } MemoryRange;
extern MemoryRange g_libsnHostMemoryRanges[48];
/* Last address and permission flags of each debug memory region; Libsn_InitializeHostMemoryAccess
 * sets the RAM size limits of entries 1 and 3. */
typedef struct MemoryBoundary { u32 last, flags; } MemoryBoundary;
extern MemoryBoundary g_libsnDefaultMemoryRanges[];
/* MemoryRange.flags: the debugger may read (1) / write (2) the range. */
#define MEMORY_READ 1
#define MEMORY_WRITE 2
/* R4300 TLB fields (libultra R4300.h names). */
#ifndef TLBLO_V
#define TLBPGMASK_16M 0x1FFE000
#endif
/* One TLB entry as Libgultra_TrwReadTlbEntry stores it (CP0 PageMask, EntryHi, EntryLo0, EntryLo1). */
typedef struct TlbEntry { u32 pageMask, entryHi, entryLo0, entryLo1; } TlbEntry;
/* Snapshot of all 32 TLB entries; Libgultra_TrwReadTlbEntry fills it and returns CP0 EntryHi. */
extern TlbEntry g_libsnPageTableEntries[32];
extern u32 Libgultra_TrwReadTlbEntry(void);
/* PageMask of each supported page size (4 KB, 16 KB, ... 16 MB), ended by 0x80000000. */
extern u32 g_libsnSupportedPageMasks[8];
#endif
