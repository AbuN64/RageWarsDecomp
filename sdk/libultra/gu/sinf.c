#include "include_asm.h"
#include "COMMON/GUMTXL2F.H"
#include "TYPES.H"
#include "COMMON/ALFXPARAM.H"
#include "COMMON/CTX.H"

/* sinf, drafted from ultralib src/gu/sinf.c in the single-precision form this library carries: x,
   its square, the polynomial, the quotient and the result are floats, only the polynomial is
   evaluated in double, and anything beyond 2^28 returns zero. P, rpi, pihi, pilo and zero are the
   cartridge's tables, and the two 0.5 literals of ROUND are its own constants. */

extern const f64 g_sinePolynomialCoefficients[5]; /* P */
extern const f64 g_sineInversePi;    /* rpi */
extern const f64 g_sinePiHigh;    /* pihi */
extern const f64 g_sinePiLow;    /* pilo */
extern const f32 g_sineExceptionalResult;    /* zero */
extern const float g_sinePositiveRoundingBias; /* 0.5 */
extern const float g_sineNegativeRoundingBias; /* 0.5 */

float Gu_Sinf(float x)
{
    float dx, xsq, poly;
    float dn;
    int n;
    float result;
    int ix, xpt;

    ix = *(int *)&x;
    xpt = (ix >> 22);
    xpt &= 0x1ff;

    if (xpt < 0xff) {
        dx = x;

        if (xpt >= 0xe6) {
            const f64 *P = g_sinePolynomialCoefficients;

            xsq = dx * dx;

            poly = ((P[4] * xsq + P[3]) * xsq + P[2]) * xsq + P[1];

            result = dx + (dx * xsq) * poly;

            return result;
        }

        return x;
    }

    if (xpt < 0x136) {
        dx = x;

        dn = dx * g_sineInversePi;

        n = (dn >= 0.0f) ? (int)(dn + g_sinePositiveRoundingBias) : (int)(dn - g_sineNegativeRoundingBias);
        dn = n;

        dx = dx - dn * g_sinePiHigh;
        dx = dx - dn * g_sinePiLow;

        xsq = dx * dx;

        {
            const f64 *P = g_sinePolynomialCoefficients;

            poly = ((P[4] * xsq + P[3]) * xsq + P[2]) * xsq + P[1];
        }

        result = dx + (dx * xsq) * poly;

        if ((n & 1) == 0) {
            return result;
        }

        return -result;
    }

    return g_sineExceptionalResult;
}


#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const unsigned int k_SinfEncodedWords[17] = {
    0xBFC55554, 0xBC83656D, 0x3F8110ED, 0x3804C2A0, 0xBF29F6FF, 0xEEA56814, 0x3EC5DBDF, 0x0E314BFE,
    0x3FD45F30, 0x6DC9C883, 0x400921FB, 0x50000000, 0x3E6110B4, 0x611A6263, 0x00000000, 0x3F000000,
    0x3F000000,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_EU)
unsigned int k_SinfEncodedWordsBlock1[1] = {
    0x4F000000,
};
#endif
