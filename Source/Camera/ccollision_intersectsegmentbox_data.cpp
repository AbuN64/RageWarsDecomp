#include "Io/debug_memory.h"
#include "types.h"
#include "include_asm.h"

#if defined(VERSION_DE)
MemoryBoundary g_debugMemoryRdramOnlyBoundaries[2] = {
    { 0x807fffff, 0x3 }, { 0x7fffffff, 0x0 }
};
#endif
