#include "include_asm.h"
#include "include/libgultra.h"

/* _floatdisf.CPP */
/* GNU GCC 2.8.0 libgcc2.c runtime conversion, GPLv2+. Target has this pre-2.8.1 rounding/sign contract. */
typedef unsigned int USItype;
typedef long long DItype;
typedef unsigned long long UDItype;
typedef int SItype;
typedef double DFtype;
typedef float SFtype;
SFtype
__floatdisf (DItype u)
{
  /* Do the calculation in DFmode
     so that we don't lose any of the precision of the high word
     while multiplying it.  */
  DFtype f;
  SItype negate = 0;

  if (u < 0)
    u = -u, negate = 1;

  /* Protect against double-rounding error.
     Represent any low-order bits, that might be truncated in DFmode,
     by a bit that won't be lost.  The bit can go in anywhere below the
     rounding position of the SFmode.  A fixed mask and bit position
     handles all usual configurations.  It doesn't handle the case
     of 128-bit DImode, however.  */
  if (53 < 64
      && 53 > (64 - 53 + 24))
    {

      if (u >= ((UDItype) 1 << 53))
	{
	  if ((USItype) u & (2048U - 1))
	    u |= 2048U;
	}
    }
  f = (USItype) (u >> 32);
  f *= 65536.0;
  f *= 65536.0;
  f += (USItype) (u & (4294967296ULL - 1));

  return (SFtype) (negate ? -f : f);
}

#if defined(VERSION_US)
char s_FloatdisfSFXRAIText[12] =
    "\024SFX_RAI\000\000\000\000";
#endif

#if defined(VERSION_EU_X)
unsigned int k_floatdisfFragment[3] = {
    0x43020000, 0x3E800000, 0x00000000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_floatdisfFragment[3] = {
    0x3DCCCCCD, 0x44000000, 0x00000000,
};
#endif

#if defined(VERSION_DE)
unsigned int k_FloatdisfEncodedWords[3] = {
    0x00000000, 0x00006000, 0x00000000,
};
#endif

/* G_LIBULTRAENCODEDWORDSBLOCK1.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CD388 */
unsigned int g_turretRangeAndQuarterScale[3] = {
    0x43020000, 0x3E800000, 0x00000000,
};
#endif
