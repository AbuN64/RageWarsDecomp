#include "include_asm.h"

#include "UI/TSMOS/PAKINTERFACE.H"
#include "TYPES.H"

#if VERSION_US
/* The byte size of the pak save block. */
s32 PAKInterface_CalcSaveGameSize(void) {
    s32 size;

    size = 1608;
    return size;
}
#endif
