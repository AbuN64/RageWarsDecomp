#include "include_asm.h"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
unsigned int s_SchedACCLAIMNETText[3] = {
    0x3162FFFF, 0x00031C00, 0x00621825,
};
#endif
#if defined(VERSION_EU_X)
char s_SchedACCLAIMNETText[12] =
    ".ACCLAIM.NET";
#endif
#endif
