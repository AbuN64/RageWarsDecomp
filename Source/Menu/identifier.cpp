#include "../../sdk/include/libgultra_inferred/IDENTIFIER.H"
#include "include_asm.h"
#include "../../sdk/include/PERIPHERAL_PORT_BYTE_VIEWS.H"
#include "types.h"

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void Menu_EmptyResourceRangeHookEuX(void) { }
#endif

#if defined(VERSION_US)
/** Perform no operation. */
void Menu_EmptyResourceRangeHookUs(void) {
}
#endif

#if !(defined(VERSION_DE))
s32 Menu_ClassifyResourceRange(s32 resourceId) {
    if ((resourceId == 1999) || (resourceId == 2999) || (resourceId == 3999) ||
        (resourceId == 4999) || (resourceId == 5999) || (resourceId == 6999) ||
        (resourceId == 99)) {
        return 0;
    }
    if ((u32)(resourceId - 1000) < 1000) {
        return 1;
    }
    if ((u32)(resourceId - 2000) < 1000) {
        return 2;
    }
    if ((u32)(resourceId - 3000) < 1000) {
        return 3;
    }
    if ((u32)(resourceId - 4000) < 1000) {
        return 4;
    }
    if ((u32)(resourceId - 5000) < 1000) {
        return 5;
    }
    if ((u32)(resourceId - 6000) < 1000) {
        return 6;
    }
    return -1;
}
#endif

#if defined(VERSION_US_REV1)
unsigned int k_SystemZeroWords[1] = {
    0x00000000,
};
#endif
