#include "include_asm.h"

/* UnsignedRemainder: libgcc2 remainder with the VR4300 HI/LO hazards. */
/* gcc-2.8.1 libgcc2 __umoddi3 compiled in place: the remainder libcall of u64 '%'. */
#define L_umoddi3
#if defined(VERSION_US)
#define LIBGCC2_EXTERNAL_CLZ s_ambiencText
#else
#define LIBGCC2_EXTERNAL_CLZ g_u64RemainderNormalizationBitWidths
#endif
#include "../../libgcc/libgcc2.inc.c"
