#include "Io/debug_memory.h"

#if defined(VERSION_US)
MemoryBoundary k_debugMemoryBoundaries[2] = {
    { 0x52000058, 0x6000010 }, { 0x7fffffff, 0x0 }
};
#endif
