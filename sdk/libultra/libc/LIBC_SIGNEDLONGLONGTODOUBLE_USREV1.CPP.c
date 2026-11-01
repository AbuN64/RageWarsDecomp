

/* LIBC_SIGNEDLONGLONGTODOUBLE_USREV1.CPP */
#if defined(VERSION_US_REV1)
/* __floatdidf: converts a signed 64-bit integer to double as its high word times 2^32 plus its
   unsigned low word; drafted from the GCC 2.7.2.3 libgcc2.c section L_floatdidf, each signed word
   adding its 2^32 correction. This object is built with -mfp32 (see the Makefile), under which the
   unchanged reference section is byte-identical. The 2^32 and 2^16 coefficients are the cartridge's
   own constants (already covered as data at 0x800CD350/0x800CD358/0x800CD360), so the code loads
   them by reference instead of emitting a constant pool. */
#include "../../include/EXTERNS.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/SITYPE.H"

 /* 2^32 */
 /* 2^16, HIGH_HALFWORD_COEFF */
 /* 2^32 */

double Libc_SignedLongLongToDoubleUsRev1(long long u)
{
  DFtype d, low;
  SItype negate = 0;

  if (u < 0)
    u = -u, negate = 1;

  d = (SItype) (u >> 32);
  if ((SItype) (u >> 32) < 0)
    d += g_longLongHighWordUnsignedBias;
  d *= g_longLongHighWordHalfwordScale;
  d *= g_longLongHighWordHalfwordScale;
  low = (SItype) u;
  if ((SItype) u < 0)
    low += g_longLongLowWordUnsignedBias;
  d += low;

  return (negate ? -d : d);
}
#endif
