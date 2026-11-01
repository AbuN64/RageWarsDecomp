#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/shared/800CC840 */
const unsigned int g_lowPassFixedPointScale_StorageWords[2] = {
    0x40D00000, 0x00000000,
};
#endif
