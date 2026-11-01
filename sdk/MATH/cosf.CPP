#include "include_asm.h"
#include "COMMON/ALDELAY28.H"
#include "TYPES.H"

/* cosf, drafted from ultralib src/gu/cosf.c: reduce |x| by multiples of pi around pi/2 in double
   precision and evaluate the odd polynomial, negating for an odd multiple; anything beyond 2^28
   returns zero. This library carries no NaN test and takes |x| with abs.s (__builtin_fabs, where
   the reference's ABS macro compiles to a compare and branch); P, rpi, pihi, pilo and zero are the
   cartridge's tables, and the 0.5 of the reduction and ROUND, ROUND's 0.0 and the 0.5 subtracted
   from n are its own constants. */


extern const f64 g_cosinePolynomialCoefficients[5];  /* P */
extern const f64 g_cosineInversePi;     /* rpi */
extern const f64 g_cosinePiHigh;     /* pihi */
extern const f64 g_cosinePiLow;     /* pilo */
extern const f32 g_cosineLargeAngleZero;     /* zero */
extern const double g_cosineRoundingHalf; /* 0.5 */
extern const double g_cosineRoundingSignBoundary; /* 0.0 */
extern const double g_cosineQuadrantOffset; /* 0.5 */

float Math_Cosf(float x)
{
    float absx;
    double dx, xsq, poly;
    double dn;
    int n;
    double result;
    int ix, xpt;

    ix = *(int *)&x;
    xpt = (ix >> 22);
    xpt &= 0x1ff;

    if (xpt < 0x136) {
        absx = __builtin_fabs(x);

        dx = absx;

        dn = dx * g_cosineInversePi + g_cosineRoundingHalf;
        n = (dn >= g_cosineRoundingSignBoundary) ? (int)(dn + g_cosineRoundingHalf) : (int)(dn - g_cosineRoundingHalf);
        dn = n;

        dn -= g_cosineQuadrantOffset;

        dx = dx - dn * g_cosinePiHigh;
        dx = dx - dn * g_cosinePiLow;

        xsq = dx * dx;

        {
            const f64 *P = g_cosinePolynomialCoefficients;

            poly = ((P[4] * xsq + P[3]) * xsq + P[2]) * xsq + P[1];
        }

        result = dx + (dx * xsq) * poly;

        if ((n & 1) == 0)
            return (float)result;

        return -(float)result;
    }

    return g_cosineLargeAngleZero;
}



