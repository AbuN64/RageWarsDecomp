#include "include_asm.h"

/* SignedDivide: libgcc2 division with the VR4300 HI/LO hazards. */
#define __divdi3 Libc_SignedDivide
#define L_divdi3
#define LIBGCC2_EXTERNAL_CLZ g_signedDivideLeadingZeroTable
#include "../../libgcc/libgcc2.inc.c"
