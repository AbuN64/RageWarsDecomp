#include "Engine/visdata.h"
#include "include_asm.h"
#include "Common/rotation_extraction.h"
#include "types.h"
#include "Math/math_double.h"
#include "Math/xmath_evaluateexponentialdouble.h"
#include "Math/doublebits.h"
#include "Common/triple.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Ui/X_files/x_math.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Resmgr/resmgr_string_memory.h"
#include <platform_sdk.h>
#include "Common/ballisticparams.h"
#include "Ui/math_double.h"
#include "Common/vector4f.h"
#include "Common/vector.h"
#include "Common/matrixrecord.h"
#include "Ui/matrixfromangles.h"
#include "Data/rest_source_records.h"

/* Scales a double by 2^shift (ldexp): adds shift to the biased exponent in place, returns zeros and infinities unchanged, saturates to the
   k_xmathScaleExponentOverflow constant on overflow, flushes to zero below 2^-53 and builds denormal results through a recursive multiply. */
double ScaleDoubleExponent(double value, int shift) {
    DoubleBits *bits = (DoubleBits *)&value;
    u32 high = bits->w.hi;
    s32 exponent;
    u32 current;
    u32 sign;
    exponent = high >> 20;
    exponent &= 0x7FF;
    if (exponent != 0) {
        if ((u32)exponent < 2047) {
            exponent = (s32)((u32)exponent + (u32)shift);
            if (exponent != 0) {
                if ((u32)exponent < 2047) {
                    bits->w.hi = (high & 0x800FFFFF) | ((exponent & 0x7FF) << 20);
                    return value;
                }
                if (shift >= 0) {
overflow:
                    current = bits->w.hi;
                    sign = current;
                    value = k_xmathScaleExponentOverflow;
                    current &= 0x7FFFFFFF;
                    current |= (sign >> 31) << 31;
                    bits->w.hi = current;
                    return k_xmathScaleExponentOverflow;
                }
                if ((u32)exponent < (u32)-53) {
                    value = 0.0;
                    bits->w.hi = (bits->w.hi & 0x7FFFFFFF) | ((high >> 31) << 31);
                    return value;
                }
            }
            bits->w.hi = (bits->w.hi & 0x800FFFFF) | 0x100000;
            value *= ScaleDoubleExponent(k_xmathScaleExponentUnit, exponent - 1);
            return value;
        }
        if ((high & 0xFFFFF) == 0 && bits->w.lo == 0) {
            if (shift >= 0) {
                goto overflow;
            }
            bits->w.hi = (high & 0x7FFFFFFF) | ((high >> 31) << 31);
        }
        return value;
    }
    if ((high & 0xFFFFF) == 0 && bits->w.lo == 0) {
        return value;
    }
    return ScaleDoubleExponent(value * ScaleDoubleExponent(k_xmathScaleExponentDenormalUnit, 53), shift - 53);
}

/* Splits a double into a mantissa in [0.5, 1) and a power of two (frexp): rewrites the biased exponent to 0x3FE and
   returns the old one minus 0x3FE through exponent; zero returns 0 with exponent 0. */
static inline f64 Frexp(f64 value, s32 *exponent) {
    DoubleBits bits;

    if (value != 0.0) {
        bits.d = value;
        *exponent = ((bits.w.hi >> 20) & 0x7FF) - 1022;
        bits.w.hi = (bits.w.hi & 0x800FFFFF) | 0x3FE00000;
        return bits.d;
    }
    *exponent = 0;
    return 0.0;
}

/* Returns the natural logarithm of a double (log): -infinity for zero or negative values; otherwise splits it with
   frexp into m * 2^e, maps m to x = 2(m - 1) / (m + 1) around sqrt(1/2) and returns x + x^3 P(x^2) / Q(x^2) plus
   e ln 2, with ln 2 split into 0.693359375 - 2.1219444e-4 for precision (the Cephes log rational form). */
f64 NaturalLogDouble(f64 value) {
    s32 exponent;
    f64 x;
    f64 divisor;
    f64 z;
    f64 p;
    f64 q;
    f64 correction;

    if (value <= 0.0) {
        return -1.0 / 0.0;
    }
    x = Frexp(value, &exponent);
    if (0.7071067690849304 < x) {
        divisor = x * 0.5 + 0.5;
        x = x - 0.5;
        x = x - 0.5;
    } else {
        exponent--;
        x = x - 0.5;
        divisor = x * 0.5 + 0.5;
    }
    x = x / divisor;
    z = x * x;
    p = ((z * -0.7895611524581909) + 16.383943557739258) * z;
    q = (((z - 35.66797637939453) * z) + 312.0322265625) * z;
    z = z * (p - 64.12494659423828);
    z = z / (q - 769.4993286132812);
    correction = x * z;
    x = x + correction;
    return (exponent * -2.1219444170128557e-4 + x) + exponent * 0.693359375;
}

/* Raises x to the power y: 1 for a zero exponent, 0 or infinity for a zero base, exp(y log x) through NaturalLogDouble (log) and an inline exponential scaled by ScaleDoubleExponent_XmathEvaluateexponentialdouble (ldexp) for a positive base, and for a negative base the same magnitude signed by the parity of an integer exponent, or negated when the exponent's reciprocal is odd, otherwise negative infinity. */

static inline f64 exp_inline(f64 x) {
    f64 t;
    f64 r;
    f64 p;
    s32 k;

    if (-2.710504946537621e-20 < x && x < 2.710504946537621e-20) {
        return 1.0;
    }
    t = x * 1.4426950216293335;
    k = t;
    if (k < 0) {
        k--;
    }
    if (0.5 <= t - k) {
        k++;
    }
    r = x - k * 0.693359375 + k * 2.1219444170128557e-4;
    t = r * r;
    p = ((t * 1.652032915444579e-5 + 6.943599786609411e-3) * t + 0.25) * r;
    return ScaleDoubleExponent(p / ((t * 4.9586285604164e-4 + 5.55538684129715e-2) * t + 0.5 - p) + 0.5, k + 1);
}

f64 XMath_PowerDouble(f64 x, f64 y) {
    s32 k;
    f64 t;

    if (y == 0.0) {
        return 1.0;
    }
    if (x == 0.0) {
        if (y < 0.0) {
            return 1.0 / 0.0;
        }
        return 0.0;
    }
    if (x < 0.0) {
        k = y;
        if (k == y) {
            t = NaturalLogDouble(-x) * y;
            if (k & 1) {
                return -exp_inline(t);
            }
            return exp_inline(t);
        }
        k = 1.0 / y;
        if (!(-2.710504946537621e-20 < y - k * y && y - k * y < 2.710504946537621e-20 && (k & 1))) {
            return -1.0 / 0.0;
        }
        return -exp_inline(NaturalLogDouble(-x) * y);
    }
    return exp_inline(NaturalLogDouble(x) * y);
}

/* Rounds toward negative infinity by the 2^52 add-and-subtract trick; a negative value goes through
 * XMath_CeilDouble (ceil) as -ceil(-value). */
static inline f64 floor_inline(f64 value) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = 4503599627370496.0;
    if (limit <= value) {
        return value;
    }
    if (value < 0.0) {
        return -XMath_CeilDouble(-value);
    }
    temp = value;
    temp += limit;
    temp -= limit;
    if (value < temp) {
        integral = temp - 1.0;
    } else {
        integral = temp;
    }
    return integral;
}

/* Rounds toward positive infinity the same way; a negative value goes through the floor as -floor(-value). */
static inline f64 ceil_inline(f64 value) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = 4503599627370496.0;
    if (limit <= value) {
        return value;
    }
    if (value < 0.0) {
        return -floor_inline(-value);
    }
    temp = value;
    temp += limit;
    temp -= limit;
    if (temp < value) {
        integral = temp + 1.0;
    } else {
        integral = temp;
    }
    return integral;
}

/* Returns the remainder of x / y with the sign of x: x minus y times the quotient rounded toward zero. */
double FloatModulo(double x, double y) {
    f64 quotient = x / y;
    f64 zero = 0.0;

    if (zero > quotient) {
        return x - ceil_inline(quotient) * y;
    }
    return x - floor_inline(quotient) * y;
}

/* Converts an array of three angles into another angle triple via sine/cosine products, clamping and atan2-style calls, and writes it back. Adapted from XMath_ConvertYxzToZyxAngles, with the clamped product, branch products, fallback call, and result order changed. */

void XMath_ConvertZyxToYxzAngles(f32 *angles) {
    f32 sinFirstAngle;
    f32 cosFirstAngle;
    f32 sinSecondAngle;
    f32 cosSecondAngle;
    f32 sinThirdAngle;
    f32 cosThirdAngle;
    f32 angle;
    f32 test;
    f32 out1;
    f32 out2;

    XMath_EvaluateSineCosine(angles[0], &sinFirstAngle, &cosFirstAngle);
    XMath_EvaluateSineCosine(angles[1], &sinSecondAngle, &cosSecondAngle);
    XMath_EvaluateSineCosine(angles[2], &sinThirdAngle, &cosThirdAngle);
    test = (cosFirstAngle * sinThirdAngle * sinSecondAngle) - (sinFirstAngle * cosThirdAngle);
    if ((1.0f) < test) {
        test = (1.0f);
    }
    if (test < (-1.0f)) {
        test = (-1.0f);
    }
    angle = XMath_EvaluateArcSine(-test);
    test = ((f32 (*)(f32))XMath_EvaluateCosine)(angle);
    if (((9.9999997473787516e-05f) < test) || (test < (-9.9999997473787516e-05f))) {
        f32 product = cosFirstAngle * cosThirdAngle;
        f32 cross = sinFirstAngle * sinThirdAngle;
        f32 first0 = (product * sinSecondAngle) + cross;
        f32 first1 = cosFirstAngle * cosSecondAngle;
        f32 second0 = cosSecondAngle * sinThirdAngle;
        f32 second1 = (cross * sinSecondAngle) + product;
        out1 = XMath_EvaluateArcTangentTwo(first0, first1);
        out2 = XMath_EvaluateArcTangentTwo(second0, second1);
    } else {
        out1 = 0.0f;
        out2 = XMath_EvaluateArcTangentTwo(-sinSecondAngle, cosSecondAngle * cosThirdAngle);
    }
    angles[0] = angle;
    angles[1] = out1;
    angles[2] = out2;
}

/* Converts a vector of three angles into another angle triple via sine/cosine products, clamping and atan2-style calls, and writes it back. Adapted from XMath_ConvertYzxToZyxAngles, with the clamped product, the branch products, and the stored order of the second and third results changed. */

void XMath_ConvertZyxToYzxAngles(CVector3 *angles) {
    f32 sinFirstAngle;
    f32 cosFirstAngle;
    f32 sinSecondAngle;
    f32 cosSecondAngle;
    f32 sinThirdAngle;
    f32 cosThirdAngle;
    f32 outX;
    f32 outZ;
    f32 clamped;
    f32 angle;
    f32 test;

    XMath_EvaluateSineCosine(angles->x, &sinFirstAngle, &cosFirstAngle);
    XMath_EvaluateSineCosine(angles->y, &sinSecondAngle, &cosSecondAngle);
    XMath_EvaluateSineCosine(angles->z, &sinThirdAngle, &cosThirdAngle);

    clamped = cosSecondAngle * sinThirdAngle;
    if ((1.0f) < clamped) {
        clamped = (1.0f);
    }
    if (clamped < (-1.0f)) {
        clamped = (-1.0f);
    }

    angle = XMath_EvaluateArcSine(clamped);
    test = ((f32 (*)(f32))XMath_EvaluateCosine)(angle);
    if (((9.9999997473787516e-05f) < test) || (test < (-9.9999997473787516e-05f))) {
        f32 saved18 = sinSecondAngle;
        f32 product = saved18 * sinThirdAngle;
        f32 saved10 = sinFirstAngle;
        f32 saved24 = cosThirdAngle;
        f32 secondArg = cosSecondAngle * saved24;
        f32 t = cosFirstAngle * product;

        outX = XMath_EvaluateArcTangentTwo((saved10 * saved24) - t,
                             (saved10 * product) + (cosFirstAngle * saved24));
        outZ = XMath_EvaluateArcTangentTwo(saved18, secondArg);
    } else {
        { f32 t = sinFirstAngle * sinSecondAngle * cosThirdAngle; outX = XMath_EvaluateArcTangentTwo(sinFirstAngle * cosSecondAngle, (cosFirstAngle * sinThirdAngle) - t); }
        outZ = 0.0f;
    }

    angles->x = outX;
    angles->y = outZ;
    angles->z = angle;
}

void XMath_ConvertYzxToZyxAngles(CVector3 *angles) {
    f32 sinFirstAngle;
    f32 cosFirstAngle;
    f32 sinSecondAngle;
    f32 cosSecondAngle;
    f32 sinThirdAngle;
    f32 cosThirdAngle;
    f32 outX;
    f32 outZ;
    f32 clamped;
    f32 angle;
    f32 test;

    XMath_EvaluateSineCosine(angles->x, &sinFirstAngle, &cosFirstAngle);
    XMath_EvaluateSineCosine(angles->y, &sinSecondAngle, &cosSecondAngle);
    XMath_EvaluateSineCosine(angles->z, &sinThirdAngle, &cosThirdAngle);

    clamped = -sinSecondAngle * cosThirdAngle;
    if ((1.0f) < clamped) {
        clamped = (1.0f);
    }
    if (clamped < (-1.0f)) {
        clamped = (-1.0f);
    }

    angle = XMath_EvaluateArcSine(-clamped);
    test = ((f32 (*)(f32))XMath_EvaluateCosine)(angle);
    if (((9.9999997473787516e-05f) < test) || (test < (-9.9999997473787516e-05f))) {
        f32 product = sinSecondAngle * sinThirdAngle;
        f32 saved10 = sinFirstAngle;
        f32 saved20 = cosSecondAngle;
        f32 saved21 = sinThirdAngle;
        f32 secondArg = saved20 * cosThirdAngle;

        outX = XMath_EvaluateArcTangentTwo((cosFirstAngle * product) + (saved10 * saved20),
                             (-saved10 * product) + (saved20 * cosFirstAngle));
        outZ = XMath_EvaluateArcTangentTwo(saved21, secondArg);
    } else {
        outX = XMath_EvaluateArcTangentTwo(-cosThirdAngle * sinFirstAngle, cosThirdAngle * cosFirstAngle);
        outZ = 0.0f;
    }

    angles->x = outX;
    angles->y = angle;
    angles->z = outZ;
}

void XMath_ConvertYxzToZyxAngles(f32 *angles) {
    f32 sinFirstAngle;
    f32 cosFirstAngle;
    f32 sinSecondAngle;
    f32 cosSecondAngle;
    f32 sinThirdAngle;
    f32 cosThirdAngle;
    f32 angle;
    f32 test;
    f32 out0;
    f32 out2;

    XMath_EvaluateSineCosine(angles[0], &sinFirstAngle, &cosFirstAngle);
    XMath_EvaluateSineCosine(angles[1], &sinSecondAngle, &cosSecondAngle);
    XMath_EvaluateSineCosine(angles[2], &sinThirdAngle, &cosThirdAngle);
    test = (cosSecondAngle * sinFirstAngle * sinThirdAngle) - (sinSecondAngle * cosThirdAngle);
    if ((1.0f) < test) {
        test = (1.0f);
    }
    if (test < (-1.0f)) {
        test = (-1.0f);
    }
    angle = XMath_EvaluateArcSine(-test);
    test = ((f32 (*)(f32))XMath_EvaluateCosine)(angle);
    if (((9.9999997473787516e-05f) < test) || (test < (-9.9999997473787516e-05f))) {
        f32 product = cosSecondAngle * cosThirdAngle;
        f32 cross = sinSecondAngle * sinThirdAngle;
        f32 first0 = cross + (sinFirstAngle * product);
        f32 first1 = cosFirstAngle * cosSecondAngle;
        f32 second0 = cosFirstAngle * sinThirdAngle;
        f32 second1 = product + (cross * sinFirstAngle);
        out0 = XMath_EvaluateArcTangentTwo(first0, first1);
        out2 = XMath_EvaluateArcTangentTwo(second0, second1);
    } else {
        out0 = XMath_EvaluateArcTangentTwo(sinFirstAngle, cosFirstAngle * cosThirdAngle);
        out2 = 0.0f;
    }
    angles[0] = out0;
    angles[1] = angle;
    angles[2] = out2;
}

f32 XMath_EvaluateSine(f32 angle) {
    f32 angleSquared;
    f32 result;
    f32 reducedAngle;
    f32 workingAngle;
    s32 resultSign;

    workingAngle = angle;
    resultSign = 1;
    reducedAngle = workingAngle;
    if (((25.132743835449219f) < workingAngle) || (workingAngle < (-25.13274383544922f))) {
        FloatModulo((f64)workingAngle, (6.2831859588623047));
    } else {
        if ((6.2831859588623047f) < workingAngle) {
            do {
                reducedAngle -= (6.2831859588623047f);
            } while ((6.2831859588623047f) < reducedAngle);
        }
        result = 0.0f;
        if (reducedAngle < result) {
            do {
                reducedAngle += (6.283185958862305f);
            } while (reducedAngle < result);
        }
    }
    if (workingAngle < (-1.5707963705062866f)) {
        do {
            workingAngle += (6.2831854820251465f);
        } while (workingAngle < (-1.5707963705062866f));
    }
    if ((4.7123889923095703f) < workingAngle) {
        do {
            workingAngle -= (6.2831854820251465f);
        } while ((4.7123889923095703f) < workingAngle);
    }
    if ((1.5707963705062866f) < workingAngle) {
        resultSign = -1;
        workingAngle -= (3.1415927410125732f);
    }
    angleSquared = workingAngle * workingAngle;
    result = (((((((angleSquared * (2.7557318844628753e-06f)) - (0.00019841270113829523f)) * angleSquared) + (0.0083333337679505348f)) * angleSquared) - (0.1666666716337204f)) * angleSquared * workingAngle) + workingAngle;
    if (resultSign < 0) {
        result = -result;
    }
    return result;
}

/* Computes the sine and cosine of an angle by reducing it into one turn, folding it into a quadrant, and evaluating one odd polynomial for each output.
   Adapted from XMath_EvaluateSine with the fmod result kept and copied back into the angle, a shared zero local for the wrap loops, the quadrant fold producing a sine and a cosine argument, and both polynomials computed before the two pointer stores changed. */

void XMath_EvaluateSineCosine(f32 angle, f32 *sinOut, f32 *cosOut) {
    f32 r;
    f32 zero;
    f32 s;
    f32 c;
    f32 s2;
    f32 c2;
    f32 ps;
    f32 pc;

    r = angle;
    if (((25.132743835449219f) < angle) || (angle < (-25.13274383544922f))) {
        r = FloatModulo((f64)angle, (6.2831859588623047));
    } else {
        if ((6.2831859588623047f) < angle) {
            do {
                r -= (6.2831859588623047f);
            } while ((6.2831859588623047f) < r);
        }
        zero = 0.0f;
        if (r < zero) {
            do {
                r += (6.283185958862305f);
            } while (r < zero);
        }
    }
    angle = r;
    zero = 0.0f;
    while (angle < zero) {
        angle += (6.2831854820251465f);
    }
    if ((6.2831854820251465f) <= angle) {
        do {
            angle -= (6.2831854820251465f);
        } while ((6.2831854820251465f) <= angle);
    }
    if ((3.1415929794311523f) <= angle) {
        if ((4.7123894691467285f) <= angle) {
            angle -= (4.7123894691467285f);
            s = angle - (1.5707964897155762f);
            c = angle;
        } else {
            angle -= (3.1415929794311523f);
            s = -angle;
            c = angle - (1.5707964897155762f);
        }
    } else if ((1.5707964897155762f) <= angle) {
        angle -= (1.5707964897155762f);
        s = (1.5707964897155762f) - angle;
        c = -angle;
    } else {
        s = angle;
        c = (1.5707964897155762f) - angle;
    }
    s2 = s * s;
    c2 = c * c;
    ps = ((((((((s2 * (2.7557318844628753e-06f)) - (0.00019841270113829523f)) * s2) + (0.008333333767950535f)) * s2) - (0.1666666716337204f)) * s2) + (1.0f)) * s;
    pc = ((((((((c2 * (2.7557318844628753e-06f)) - (0.00019841270113829523f)) * c2) + (0.008333333767950535f)) * c2) - (0.1666666716337204f)) * c2) + (1.0f)) * c;
    *sinOut = ps;
    *cosOut = pc;
}

/* Returns the hyperbolic tangent of a double: 1 beyond 25.3, 1 - 2/(exp(2|x|) + 1) above atanh(0.5) with exp computed inline by a rational approximation scaled by ScaleDoubleExponent_XmathEvaluateexponentialdouble (ldexp), and the odd rational series x + x^3 P(x^2)/Q(x^2) for small arguments, with the sign of x restored. */

static inline f64 exp_inline_tanh(f64 x) {
    f64 t;
    f64 r;
    f64 p;
    s32 k;

    if (-2.710504946537621e-20 < x && x < 2.710504946537621e-20) {
        return 1.0;
    }
    t = x * 1.4426950216293335;
    k = t;
    if (k < 0) {
        k--;
    }
    if (0.5 <= t - k) {
        k++;
    }
    r = x - k * 0.693359375 + k * 2.1219444170128557e-4;
    t = r * r;
    p = ((t * 1.652032915444579e-5 + 6.943599786609411e-3) * t + 0.25) * r;
    return ScaleDoubleExponent(p / ((t * 4.9586285604164e-4 + 5.55538684129715e-2) * t + 0.5 - p) + 0.5, k + 1);
}

f64 XMath_EvaluateHyperbolicTangent(f64 x) {
    f64 z;
    f64 s;
    f64 result;

    z = x;
    if (x < 0.0) {
        z = -x;
    }
    if (z > 25.299999237060547) {
        result = 1.0;
    } else if (z > 0.5493061542510986) {
        result = exp_inline_tanh(z + z);
        result = 0.5 - 1.0 / (result + 1.0);
        result = result + result;
    } else if (z < 2.3000000515249751e-10) {
        result = z;
    } else {
        s = z * z;
        result = z + z * (((s * -0.9643748998641968 - 99.2259292602539) * s - 1613.411865234375) * s)
                / (((s + 112.74474334716795) * s + 2233.77197265625) * s + 4840.23583984375);
    }
    if (x < 0.0) {
        result = -result;
    }
    return result;
}

/* Returns the angle of the vector (x, y) in radians, atan2(y, x): both components within 1e-6 of zero are snapped to zero, the axes return exact multiples of pi/2, and otherwise the arctangent of |y/x| comes from the (t - 1)/(t + 1) series around pi/4, negated for a negative ratio and offset by the quadrant's term from k_xmathAtanQuadrantOffsets. */

f32 XMath_EvaluateArcTangentTwo(f32 y, f32 x) {
    s32 quadrant;
    f32 ratio;
    f32 magnitude;
    f32 t;
    f32 t2;
    f32 angle;

    if (-1e-6f < x && x < 1e-6f) {
        x = 0.0f;
    }
    if (-1e-6f < y && y < 1e-6f) {
        y = 0.0f;
    }
    if (x == 0.0f && y == 0.0f) {
        return 0.0f;
    }
    if (x == 0.0f) {
        if (y >= 0.0f) {
            return 1.5707964f;
        }
        return -1.5707964f;
    }
    if (y == 0.0f) {
        if (x >= 0.0f) {
            return 0.0f;
        }
        return 3.1415927f;
    }
    quadrant = 0;
    if (x < 0.0f) {
        quadrant = 1;
    }
    if (y < 0.0f) {
        quadrant |= 2;
    }
    ratio = y / x;
    magnitude = ratio;
    if (quadrant != 0 && quadrant != 3) {
        magnitude = -ratio;
    }
    if (magnitude < 1e-6f) {
        return k_xmathAtanQuadrantOffsets[quadrant];
    }
    magnitude = ratio;
    if (ratio < 0.0f) {
        magnitude = -ratio;
    }
    t = (magnitude - 1.0f) / (magnitude + 1.0f);
    t2 = t * t;
    angle = (((((((-0.004054058f * t2 + 0.021861229f) * t2 - 0.055909887f) * t2 + 0.09642004f) * t2
                 - 0.13908534f) * t2 + 0.19946536f) * t2 - 0.33329856f) * t2 + 0.99999934f) * t
            + 0.7853982f;
    if (ratio < 0.0f) {
        angle = -angle;
    }
    return angle + k_xmathAtanQuadrantOffsets[quadrant];
}

/** Square root that returns 0 for zero or negative input. */
static inline f32 safeSqrt(f32 value) {
    if (value <= 0.0f) {
        return 0.0f;
    }
    return Gu_Sqrtf(value);
}
/** Length of a 3-vector. */
static inline f32 vectorLength(f32 *v) {
    return safeSqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
/** Arc sine by polynomial: clamps to [-1, 1], pi/2 - sqrt(1 - |x|) * poly(|x|), sign restored. */
static inline f32 arcSin(f32 x) {
    s32 negative;
    f32 polynomial;
    f32 result;
    if (x > 1.0f) {
        x = 1.0f;
    }
    if (x < -1.0f) {
        x = -1.0f;
    }
    negative = 0;
    if (x < 0.0f) {
        negative = 1;
        x = -x;
    }
    polynomial = (((((x * -0.0116805276f + 0.0308918804f) * x - 0.0501743034f) * x + 0.0889789909f) * x - 0.214598805f) * x + 1.57079625f);
    result = 1.5707964f - safeSqrt(1.0f - x) * polynomial;
    if (negative) {
        result = -result;
    }
    return result;
}
/** Arc cosine as pi/2 - arcSin. */
static inline f32 arcCos(f32 x) {
    return 1.5707964f - arcSin(x);
}
/** Angle between two 3-vectors, 0 when either has zero length. */
f32 VectorAngle(f32 *a, f32 *b) {
    f32 lengthA = vectorLength(a);
    f32 lengthB = vectorLength(b);
    f32 product = lengthA * lengthB;
    f32 value;
    if (product == 0.0f) {
        return 0.0f;
    }
    value = (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]) / product;
    if (value > 1.0f) {
        value = 1.0f;
    } else if (value < -1.0f) {
        value = -1.0f;
    }
    return arcCos(value);
}

/* Clips a polygon of n vertices against the plane a*x + b*y + c*z + d >= 0 (Sutherland-Hodgman): walks each edge from the previous vertex, copies inside vertices to the output, and where an edge crosses the plane emits the intersection point (the edge midpoint when the edge is nearly parallel to the plane), storing the output count and returning whether any intersection was emitted. */

s32 XMath_ClipPolygonToPlane(CVector3 *out, s32 *outCount, CVector3 *in, s32 n, f32 a, f32 b, f32 c, f32 d) {
    CVector3 delta;
    CVector3 *prev;
    CVector3 *point;
    CVector3 *cur;
    s32 count;
    s32 clipped;
    s32 i;
    s32 prevInside;
    s32 inside;
    f32 dot;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 t;

    count = 0;
    clipped = 0;
    *outCount = 0;
    if (n == 0) {
        return 0;
    }
    prev = &in[n - 1];
    prevInside = prev->x * a + prev->y * b + prev->z * c + d >= 0.0f;
    for (i = 0; i < n; i++) {
        cur = &in[i];
        inside = cur->x * a + cur->y * b + cur->z * c + d >= 0.0f;
        if (prevInside) {
            *out++ = *prev;
            count++;
        }
        if (prevInside != inside) {
            dx = cur->x - prev->x;
            delta.x = dx;
            dx = a * delta.x;
            dy = cur->y - prev->y;
            delta.y = dy;
            dy = b * delta.y;
            dz = cur->z - prev->z;
            delta.z = dz;
            dz = c * delta.z;
            dot = dx + dy + dz;
            dist = a * prev->x + b * prev->y + c * prev->z + d;
            clipped = 1;
            point = out++;
            count++;
            dist = -dist;
            if (dot < 0.001f && (t = 0.5f, -0.001f < dot)) {
            } else {
                t = dist / dot;
            }
            point->x = prev->x + t * delta.x;
            point->y = prev->y + t * delta.y;
            point->z = prev->z + t * delta.z;
        }
        prev = cur;
        prevInside = inside;
    }
    *outCount = count;
    return clipped;
}

#include "Common/triple.h"

void MatrixFromAngles(MatrixF *matrix, f32 *angles) {
    u16 mask = 0;
    f32 sy, cy, sx, cx, sz, cz, one;
    if (angles[0] != 0.0f) mask = 4;
    if (angles[1] != 0.0f) mask |= 2;
    if (angles[2] != 0.0f) mask |= 1;
    switch (mask) {
    case 0:
        XPlus_FillBytes(matrix, 0, 64);
        one = k_xmathAngleMatrixIdentityUnit;
        matrix->m[0][0] = one; matrix->m[1][1] = one; matrix->m[2][2] = one; matrix->m[3][3] = one;
        return;
    case 2:
        XPlus_FillBytes(matrix, 0, 64);
        one = k_xmathAngleMatrixYUnit;
        matrix->m[0][0] = one; matrix->m[1][1] = one; matrix->m[2][2] = one; matrix->m[3][3] = one;
        XMath_EvaluateSineCosine(angles[1], &sy, &cy);
        matrix->m[2][0] = sy; matrix->m[0][0] = cy; matrix->m[0][2] = -sy; matrix->m[2][2] = cy;
        return;
    case 4:
        XPlus_FillBytes(matrix, 0, 64);
        one = k_xmathAngleMatrixXUnit;
        matrix->m[0][0] = one; matrix->m[1][1] = one; matrix->m[2][2] = one; matrix->m[3][3] = one;
        XMath_EvaluateSineCosine(angles[0], &sx, &cx);
        matrix->m[1][1] = cx; matrix->m[2][1] = -sx; matrix->m[1][2] = sx; matrix->m[2][2] = cx;
        return;
    case 1:
        XPlus_FillBytes(matrix, 0, 64);
        one = k_xmathAngleMatrixZUnit;
        matrix->m[0][0] = one; matrix->m[1][1] = one; matrix->m[2][2] = one; matrix->m[3][3] = one;
        XMath_EvaluateSineCosine(angles[2], &sz, &cz);
        matrix->m[0][0] = cz; matrix->m[1][0] = -sz; matrix->m[0][1] = sz; matrix->m[1][1] = cz;
        return;
    }
    XMath_EvaluateSineCosine(angles[0], &sx, &cx);
    XMath_EvaluateSineCosine(angles[1], &sy, &cy);
    XMath_EvaluateSineCosine(angles[2], &sz, &cz);
    {
        f32 sxsy = sx * sy;
        f32 cxcz = cx * cz;
        f32 cxsz = cx * sz;
        matrix->m[0][0] = cy * cz;
        matrix->m[1][0] = sxsy * cz - cxsz;
        matrix->m[2][0] = cxcz * sy + sx * sz;
        matrix->m[0][1] = cy * sz;
        matrix->m[1][1] = sxsy * sz + cxcz;
        matrix->m[2][1] = cxsz * sy - sx * cz;
        matrix->m[0][2] = -sy;
        matrix->m[1][2] = sx * cy;
        matrix->m[2][2] = cx * cy;
        matrix->m[0][3] = matrix->m[1][3] = matrix->m[2][3] = matrix->m[3][0] = matrix->m[3][1] = matrix->m[3][2] = 0.0f;
        matrix->m[3][3] = k_xmathAnglesMatrixHomogeneousUnit;
    }
}

/* The values XMath_BuildYxzRotationMatrix loads by address:
 * The float constant 1.0 (k_xmathRotationMatrixHomogeneousUnit)
 */

/* Build a rotation matrix from the three Euler angles in angles. */
void XMath_BuildYxzRotationMatrix(RotationMatrixWords *outputMatrix, CVector3 *angles) {
    f32 sinX;
    f32 cosX;
    f32 sinY;
    f32 cosY;
    f32 sinZ;
    f32 cosZ;
    f32 sinXSinZ;
    f32 sinXCosZ;
    f32 cosYCosZ;
    f32 sinZCosY;
    f32 cosXSinY;
    f32 cosXSinZ;
    f32 cosXCosZ;
    f32 sinYCosZ;
    f32 cosXCosY;
    float sinYSinXCosZ;
    f32 matrixXContribution;
    f32 matrixYContribution;
    f32 cosYSinXSinZ;
    float sinYSinXSinZ;
    f32 sinYSinZ;
    f32 unusedCosYSinZ;
    XMath_EvaluateSineCosine(angles->x, &sinX, &cosX);
    XMath_EvaluateSineCosine(angles->y, &sinY, &cosY);
    XMath_EvaluateSineCosine(angles->z, &sinZ, &cosZ);
    sinXSinZ = sinX * sinZ;
    sinXCosZ = sinX * cosZ;
    sinYSinXSinZ = sinY * sinXSinZ;
    cosYCosZ = cosY * cosZ;
    sinZCosY = sinZ * cosY;
    cosXSinY = cosX * sinY;
    sinYSinXCosZ = sinY * sinXCosZ;
    cosXSinZ = cosX * sinZ;
    cosXCosZ = cosX * cosZ;
    sinYCosZ = sinY * cosZ;
    cosXCosY = cosX * cosY;
    matrixXContribution = sinYSinXSinZ;
    matrixYContribution = sinYSinXCosZ;
    cosYSinXSinZ = cosY * sinXSinZ;
    sinYSinZ = sinY * sinZ;
    unusedCosYSinZ = cosY * sinZ;
    outputMatrix->m21 = -sinX;
    outputMatrix->m20 = cosXSinY;
    outputMatrix->m01 = cosXSinZ;
    outputMatrix->m11 = cosXCosZ;
    outputMatrix->m03 = outputMatrix->m13 = outputMatrix->m23 = outputMatrix->m30 = outputMatrix->m31 = outputMatrix->m32 = 0.0f;
    outputMatrix->m22 = cosXCosY;
    outputMatrix->m33 = k_xmathRotationMatrixHomogeneousUnit;
    outputMatrix->m00 = cosYCosZ + matrixXContribution;
    outputMatrix->m10 = matrixYContribution - sinZCosY;
    outputMatrix->m02 = cosYSinXSinZ - sinYCosZ;
    outputMatrix->m12 = sinYSinZ + sinXCosZ * cosY;
}

void XMath_ExtractYxzAngles(RotationMatrixWords *inputMatrix, CVector3 *outputAngles) {
    f32 clamped;
    f32 magnitude;
    f32 polynomial;
    f32 root;
    f32 delta;
    f32 test;
    f32 angle;
    f32 angle_temp;
    f32 out2;
    s32 negative;
    clamped = inputMatrix->m21;
    if (k_yxzExtractionClampAndZero < clamped) {
        clamped = k_yxzExtractionClampAndZero;
    }
    if (clamped < *(&k_yxzExtractionClampAndZero + 1)) {
        clamped = *(&k_yxzExtractionClampAndZero + 1);
    }
    magnitude = -clamped;
    if (k_yxzExtractionClampAndZero < magnitude) {
        magnitude = k_yxzExtractionClampAndZero;
    }
    if (magnitude < *(&k_yxzExtractionClampAndZero + 1)) {
        magnitude = *(&k_yxzExtractionClampAndZero + 1);
    }
    negative = 0;
    if (magnitude < 0.0f) {
        negative = 1;
        magnitude = -magnitude;
    }
    polynomial = (((((((((magnitude * k_yxzExtractionPolynomialCoefficientsHigh) + *(&k_yxzExtractionPolynomialCoefficientsHigh + 1)) * magnitude)
        - k_yxzExtractionPolynomialCoefficientsMiddle) * magnitude) + *(&k_yxzExtractionPolynomialCoefficientsMiddle + 1)) * magnitude)
        - k_yxzExtractionPolynomialCoefficientsLow) * magnitude) + *(&k_yxzExtractionPolynomialCoefficientsLow + 1);
    delta = k_yxzExtractionClampAndZero - magnitude;
    if (delta <= 0.0f) {
        root = 0.0f;
    } else {
        root = Gu_Sqrtf(delta);
    }
    angle_temp = k_yxzExtractionHalfPi - (root * polynomial);
    if (negative != 0) {
        angle_temp = -angle_temp;
    }
    angle = angle_temp;
    test = XMath_EvaluateSine(angle + k_yxzExtractionHalfPi);
    if ((*(&k_yxzExtractionHalfPi + 1) < test) || (test < *(&k_yxzExtractionHalfPi + 1))) {
        polynomial = XMath_EvaluateArcTangentTwo(inputMatrix->m20, inputMatrix->m22);
        out2 = XMath_EvaluateArcTangentTwo(inputMatrix->m01, inputMatrix->m11);
    } else {
        polynomial = 0.0f;
        out2 = XMath_EvaluateArcTangentTwo(inputMatrix->m02, inputMatrix->m00);
    }
    outputAngles->x = angle;
    outputAngles->y = polynomial;
    outputAngles->z = out2;
}
/* Computes an arcsine-style angle from a clamped matrix element by polynomial approximation, then derives the other two Euler angles with atan2-style calls and writes the triple. Adapted from XMath_ExtractYxzAngles, with the source element, the zero test, the branch operands, and the stored order changed. */

void XMath_ExtractZyxAngles(RotationMatrixWords *inputMatrix, CVector3 *outputAngles) {
    f32 clamped;
    f32 magnitude;
    f32 polynomial;
    f32 root;
    f32 delta;
    f32 test;
    f32 angle;
    f32 angle_temp;
    f32 out2;
    s32 negative;
    clamped = inputMatrix->m02;
    if (k_zyxExtractionClampAndZero < clamped) {
        clamped = k_zyxExtractionClampAndZero;
    }
    if (clamped < *(&k_zyxExtractionClampAndZero + 1)) {
        clamped = *(&k_zyxExtractionClampAndZero + 1);
    }
    magnitude = -clamped;
    if (k_zyxExtractionClampAndZero < magnitude) {
        magnitude = k_zyxExtractionClampAndZero;
    }
    if (magnitude < *(&k_zyxExtractionClampAndZero + 1)) {
        magnitude = *(&k_zyxExtractionClampAndZero + 1);
    }
    negative = 0;
    if (magnitude < 0.0f) {
        negative = 1;
        magnitude = -magnitude;
    }
    polynomial = (((((((((magnitude * k_zyxExtractionPolynomialCoefficientsHigh) + *(&k_zyxExtractionPolynomialCoefficientsHigh + 1)) * magnitude)
        - k_zyxExtractionPolynomialCoefficientsMiddle) * magnitude) + *(&k_zyxExtractionPolynomialCoefficientsMiddle + 1)) * magnitude)
        - k_zyxExtractionPolynomialCoefficientsLow) * magnitude) + *(&k_zyxExtractionPolynomialCoefficientsLow + 1);
    delta = k_zyxExtractionClampAndZero - magnitude;
    if (delta <= 0.0f) {
        root = 0.0f;
    } else {
        root = Gu_Sqrtf(delta);
    }
    angle_temp = k_zyxExtractionHalfPi - (root * polynomial);
    if (negative != 0) {
        angle_temp = -angle_temp;
    }
    angle = angle_temp;
    test = XMath_EvaluateSine(angle + k_zyxExtractionHalfPi);
    if ((0.0f < test) || (test < 0.0f)) {
        polynomial = XMath_EvaluateArcTangentTwo(inputMatrix->m12, inputMatrix->m22);
        out2 = XMath_EvaluateArcTangentTwo(inputMatrix->m01, inputMatrix->m00);
    } else {
        polynomial = XMath_EvaluateArcTangentTwo(-inputMatrix->m21, inputMatrix->m11);
        out2 = 0.0f;
    }
    outputAngles->x = polynomial;
    outputAngles->y = angle;
    outputAngles->z = out2;
}

void XMath_MultiplyMatrices(s32 matrix, s32 leftMatrix, s32 rightMatrix) {
    Matrix temporary;
    Matrix *out = (Matrix *)matrix;
    Matrix *a = (Matrix *)leftMatrix;
    Matrix *b = (Matrix *)rightMatrix;
    s32 row;

    if (out == a) {
        temporary = *a;
        if (a == b) {
            b = &temporary;
        }
        a = &temporary;
    } else if (out == b) {
        temporary = *b;
        b = &temporary;
    }

    {
        f32 *destination = out->m;
        f32 *left = a->m;
        f32 *right = b->m;
        row = 0;
        do {
            destination[0] = left[0] * right[0] +
                left[4] * right[1] +
                left[8] * right[2] +
                left[12] * right[3];
            destination[1] = left[1] * right[0] +
                left[5] * right[1] +
                left[9] * right[2] +
                left[13] * right[3];
            destination[2] = left[2] * right[0] +
                left[6] * right[1] +
                left[10] * right[2] +
                left[14] * right[3];
            destination[3] = left[3] * right[0] +
                left[7] * right[1] +
                left[11] * right[2] +
                left[15] * right[3];
            destination += 4;
            right += 4;
        } while (++row < 4);
    }
}

/* Re-orthonormalises the rotation rows of a matrix: normalises the first and second rows (a zero length is left to divide by zero), rebuilds the third row as their cross product and the second as the cross product of the third and first, and writes the three rows back. */

static inline f32 safe_sqrt_invert(f32 x) {
    if (x <= 0.0f) {
        return 0.0f;
    }
    return Gu_Sqrtf(x);
}

static inline void normalize_x(CVector3 *v) {
    f32 scale;

    scale = k_xmathNormalizeXUnit / safe_sqrt_invert(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x *= scale;
    v->y *= scale;
    v->z *= scale;
}

static inline void normalize_y(CVector3 *v) {
    f32 scale;

    scale = k_xmathNormalizeYUnit / safe_sqrt_invert(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x *= scale;
    v->y *= scale;
    v->z *= scale;
}

static inline CVector3 cross(CVector3 *a, CVector3 *b) {
    CVector3 r;

    r.x = a->y * b->z - a->z * b->y;
    r.y = a->z * b->x - a->x * b->z;
    r.z = a->x * b->y - a->y * b->x;
    return r;
}

void XMath_OrthogonalizeMatrixBasis(struct PlaneEquation *m) {
    CVector3 x;
    CVector3 y;
    CVector3 z;

    x.x = m[0].normal.x;
    x.y = m[0].normal.y;
    x.z = m[0].normal.z;
    y.x = m[1].normal.x;
    y.y = m[1].normal.y;
    y.z = m[1].normal.z;
    normalize_x(&x);
    normalize_y(&y);
    z = cross(&x, &y);
    y = cross(&z, &x);
    {
        CVector3 *p = &x;

        m[0].normal.x = p->x;
        m[0].normal.y = p->y;
        m[0].normal.z = p->z;
    }
    m[1].normal.x = y.x;
    m[1].normal.y = y.y;
    m[1].normal.z = y.z;
    m[2].normal.x = z.x;
    m[2].normal.y = z.y;
    m[2].normal.z = z.z;
}

s32 XMath_InvertAffineMatrix(f32 *out, f32 *input)
{
  struct CQuatern_t copy[4];
  f32 *m;
  f32 determinant;
  f32 absoluteDeterminant;
  f32 reciprocal;
  f32 negativeReciprocal;
  f32 m5;
  f32 m10;
  f32 m6;
  f32 m9;
  f32 m4;
  f32 m8;
  f32 minor0;
  f32 affineOne;
  s32 result;
  m = input;
  if (input == out)
  {
    struct CQuatern_t *dst = copy;
    struct CQuatern_t *src = (struct CQuatern_t *) out;
    struct CQuatern_t *end = src + 4;
    do
    {
      *dst = *src;
      src++;
      dst++;
    }
    while (src != end);
    m = (f32 *) copy;
  }
  m5 = m[5];
  m10 = m[10];
  m6 = m[6];
  m9 = m[9];
  minor0 = (m5 * m10) - (m6 * m9);
  m4 = m[4];
  m8 = m[8];
  determinant = ((m[0] * minor0) - (m[1] * ((m4 * m10) - (m6 * m8)))) + (m[2] * ((m4 * m9) - (m5 * m8)));
  reciprocal = determinant;
  absoluteDeterminant = reciprocal;
  if (!(reciprocal >= 0.0f))
  {
    absoluteDeterminant = -determinant;
  }
  result = 1;
  if (!(absoluteDeterminant < k_xmathMatrixDeterminantTolerance))
  {
    affineOne = k_xmathAffineMatrixUnit;
    reciprocal = affineOne / determinant;
    out[0] = reciprocal * minor0;
    negativeReciprocal = -reciprocal;
    out[1] = negativeReciprocal * ((m[1] * m[10]) - (m[2] * m[9]));
    out[2] = reciprocal * ((m[1] * m[6]) - (m[2] * m[5]));
    out[3] = 0.0f;
    out[4] = negativeReciprocal * ((m[4] * m[10]) - (m[6] * m[8]));
    out[5] = reciprocal * ((m[0] * m[10]) - (m[2] * m[8]));
    out[6] = negativeReciprocal * ((m[0] * m[6]) - (m[2] * m[4]));
    out[7] = 0.0f;
    out[8] = reciprocal * ((m[4] * m[9]) - (m[5] * m[8]));
    out[9] = negativeReciprocal * ((m[0] * m[9]) - (m[1] * m[8]));
    out[10] = reciprocal * ((m[0] * m[5]) - (m[1] * m[4]));
    out[11] = 0.0f;
    out[12] = -(((m[12] * out[0]) + (m[13] * out[4])) + (m[14] * out[8]));
    out[13] = -(((m[12] * out[1]) + (m[13] * out[5])) + (m[14] * out[9]));
    out[14] = -(((m[12] * out[2]) + (m[13] * out[6])) + (m[14] * out[10]));
    result = 0;
    out[15] = affineOne;
  }
  return result;
}

/* Invert a 4x4 matrix with partial pivoting. Return one for a singular
 * matrix, leaving the destination untouched until elimination succeeds. */
s32 InvertMatrix(struct MatrixF *output, struct MatrixF *input)
{
    f32 augmented[4][8];
    s32 rowOrder[4];
    s32 i, j, elementIndex, pivotRow, otherRow;
    f32 value, entry, absoluteEntry;
    for (j = 0; j < 4; j++) {
        for (elementIndex = 0; elementIndex < 4; elementIndex++) {
            augmented[j][elementIndex] = input->m[j][elementIndex];
            augmented[j][elementIndex + 4] = 0.0f;
        }
        augmented[j][j + 4] = 1.0f;
        rowOrder[j] = j;
    }
    for (i = 0; i < 4; i++) {
        elementIndex = i;
        if (0.0f <= augmented[rowOrder[elementIndex]][elementIndex]) {
            value = augmented[rowOrder[elementIndex]][elementIndex];
        } else {
            value = -augmented[rowOrder[elementIndex]][elementIndex];
        }
        for (j = elementIndex + 1; j < 4; j++) {
            entry = augmented[rowOrder[j]][i];
            if (!(0.0f <= entry)) {
                absoluteEntry = -entry;
            } else {
                absoluteEntry = entry;
            }
            if (value < absoluteEntry) {
                elementIndex = j;
                if (!(0.0f <= entry)) {
                    value = -entry;
                } else {
                    value = entry;
                }
                absoluteEntry = value;
            }
        }
        pivotRow = rowOrder[elementIndex];
        rowOrder[elementIndex] = rowOrder[i];
        rowOrder[i] = pivotRow;
        value = augmented[pivotRow][i];
        if (value == 0.0f) return 1;
        augmented[pivotRow][i] = 1.0f;
        for (elementIndex = i + 1; elementIndex < 8; elementIndex++) augmented[pivotRow][elementIndex] /= value;
        for (j = i + 1; j < 4; j++) {
            otherRow = rowOrder[j];
            value = -augmented[otherRow][i];
            if (value != 0.0f) {
                augmented[otherRow][i] = 0.0f;
                for (elementIndex = i + 1; elementIndex < 8; elementIndex++) augmented[otherRow][elementIndex] += value * augmented[pivotRow][elementIndex];
            }
        }
    }
    for (i = 3; i > 0; i--) {
        pivotRow = rowOrder[i];
        for (j = i - 1; j >= 0; j--) {
            otherRow = rowOrder[j];
            value = augmented[otherRow][i];
            for (elementIndex = i; elementIndex < 8; elementIndex++) augmented[otherRow][elementIndex] -= value * augmented[pivotRow][elementIndex];
        }
    }
    for (j = 0; j < 4; j++) {
        otherRow = rowOrder[j];
        for (elementIndex = 0; elementIndex < 4; elementIndex++) output->m[j][elementIndex] = augmented[otherRow][elementIndex + 4];
    }
    return 0;
}

/* Rounds a double up to the next integer by the 2^52 add-and-subtract trick, handling negative values through an inlined round-down that recurses back into this function. Adapted from XMath_FloorDouble with the rounding direction reversed, the negative case routed through an inline copy of the round-down and the constants changed. */

static inline f64 round_down(f64 value) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = k_xmathCeilIntegralLimit;
    if (limit <= value) {
        return value;
    }
    if (value < k_xmathCeilSignBoundary) {
        return -XMath_CeilDouble(-value);
    }
    temp = value;
    temp += limit;
    temp -= limit;
    if (value < temp) {
        integral = temp - k_xmathCeilIntegralBias;
    } else {
        integral = temp;
    }
    return integral;
}

/* Returns e raised to a double: 1 for arguments of negligible magnitude, and otherwise splits the argument into k ln 2 plus a remainder r, evaluates the rational approximation 1/2 + p(r)/(q(r) - p(r)) and scales it by two to the power k + 1 through ScaleDoubleExponent_XmathEvaluateexponentialdouble. */

/* Returns the arcsine of a value clamped to [-1, 1] using the polynomial approximation pi/2 - sqrt(1 - x) * p(x) on its magnitude and restoring the sign afterwards. */

/* Returns the arccosine of a value clamped to [-1, 1] as pi/2 minus the arcsine, which is computed by the polynomial approximation pi/2 - sqrt(1 - x) * p(x) on the magnitude with the sign restored. Adapted from XMath_EvaluateArcSine with the constants moved to k_xmathArcCosineUpperClamp through k_xmathArcCosineHalfPi and the final subtraction from pi/2 added. */

/** Perform the pair of adjacent no-op hooks. */
void XMath_InitializeMath(void) {
}

void XMath_ShutdownMath(void) {
}

f32 XMath_SquareFloat(f32 value) {
    return value * value;
}

void XMath_EvaluatePositiveSquareRoot(f32 value) {
    if (!(value <= 0.0f)) {
        Gu_Sqrtf(value);
    }
}

f32 XMath_EvaluateReciprocalSquareRoot(f32 value) {
    f32 squareRoot;

    if (value <= 0.0f) {
        squareRoot = 0.0f;
    } else {
        squareRoot = Gu_Sqrtf(value);
    }
    return k_xmathReciprocalSquareRootUnit / squareRoot;
}

f32 XMath_OffsetFloatRemainder(f32 value, f32 divisor) {
    f32 result;
    result = (f32) FloatModulo((f64) value, (f64) divisor);
    if (result < divisor) {
        result += divisor;
    }
    return result;
}

f64 XMath_FloorDouble(f64 value) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = k_xmathFloorIntegralLimit;
    if (limit <= value) {
        return value;
    }
    if (value < k_xmathFloorSignBoundary) {
        return -XMath_CeilDouble(-value);
    }
    temp = value;
    temp += limit;
    temp -= limit;
    if (value < temp) {
        integral = temp - k_xmathFloorIntegralBias;
    } else {
        integral = temp;
    }
    return integral;
}

f64 XMath_CeilDouble(f64 value) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = k_xmathCeilIntegralLimit;
    if (limit <= value) {
        return value;
    }
    if (value < k_xmathCeilSignBoundary) {
        return -round_down(-value);
    }
    temp = value;
    temp += limit;
    temp -= limit;
    if (temp < value) {
        integral = temp + k_xmathCeilRoundUpUnit;
    } else {
        integral = temp;
    }
    return integral;
}

f64 XMath_SplitDoubleFraction(f64 value, f64 *whole) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = k_xmathFractionIntegralLimit;
    if (limit <= value) {
        integral = value;
    } else {
        if (value < k_xmathFractionSignBoundary) {
            integral = -XMath_CeilDouble(-value);
        } else {
            temp = value;
            temp += limit;
            temp -= limit;
            if (value < temp) {
                integral = temp - k_xmathFractionIntegralBias;
            } else {
                integral = temp;
            }
        }
    }
    *whole = integral;
    return value - integral;
}

f32 XMath_AbsoluteFloat(f32 value) {
    if (value >= 0.0f) {
        return value;
    }
    return -value;
}

s32 XMath_AbsoluteInteger(s32 value) {
    if (value < 0) {
        if (value) {
            return -value;
        } else {
            return -value;
        }
    }
    return value;
}

/* Returns the base-10 logarithm of a double: NaturalLogDouble(value) times 1/ln 10. */
f64 Log10Double(f64 value) {
    return NaturalLogDouble(value) * k_xmathNaturalLogToDecimalScale;
}

f64 XMath_EvaluateExponentialDouble(f64 x) {
    f64 r;
    f64 t;
    f64 p;
    f64 q;
    s32 k;

    if (k_xmathExponentialUpperLimit < x) {
        f64 result = k_xmathExponentialInitialResult;
        if (x < k_xmathExponentialLowerLimit) return result;
    }
    t = x * k_xmathExponentialToBinaryScale;
    k = t;
    if (k < 0) {
        k--;
    }
    if (k_xmathExponentialRoundingAndDenominatorConstant <= t - k) {
        k++;
    }
    r = x - k * k_xmathExponentialReductionLeadingTerm + k * k_xmathExponentialReductionTrailingTerm;
    t = r * r;
    p = ((t * k_xmathExponentialNumeratorCubicCoefficient + k_xmathExponentialNumeratorLinearCoefficient) * t + k_xmathExponentialNumeratorConstant) * r;
    q = (t * k_xmathExponentialDenominatorQuadraticCoefficient + k_xmathExponentialDenominatorLinearCoefficient) * t + k_xmathExponentialRoundingAndDenominatorConstant;
    return ScaleDoubleExponent(p / (q - p) + k_xmathExponentialRoundingAndDenominatorConstant, k + 1);
}

f64 XMath_SplitDoubleExponent(f64 value, s32 *exponent) {
    DoubleBits u;
    f64 special;

    special = k_xmathExponentSpecialValue;
    if (value != special) {
        if (k_xmathExponentSpecialValue || exponent) {
            goto normal;
        } else {
            goto normal;
        }
    }
    *exponent = 0;
    return special;
normal:
    u.d = value;

    *exponent = ((u.w.hi >> 20) & 0x7FF) - 1022;
    u.w.hi = (u.w.hi & 0x800FFFFF) | 0x3FE00000;
    return u.d;
}

void XMath_EvaluateCosine(f32 angle) {
    ((s32 (*)(f32))XMath_EvaluateSine)(angle + k_xmathCosinePhaseOffset);
}

f32 XMath_EvaluateTangent(f32 angle) {
    f32 r1 = XMath_EvaluateSine(angle);
    f32 r2 = XMath_EvaluateSine(angle + k_xmathTangentCosinePhaseOffset);
    return r1 / r2;
}

f32 XMath_EvaluateArcTangent(f32 value) {
    f32 reducedValueSquared;
    f32 reducedValue;
    f32 result;
    f32 magnitude;

    magnitude = value;
    if (value < 0.0f) {
        magnitude = -value;
    }
    reducedValue = (magnitude - k_xmathArcTangentReductionUnit) / (magnitude + k_xmathArcTangentReductionUnit);
    reducedValueSquared = reducedValue * reducedValue;
    result = (((((((((((((((reducedValueSquared * k_xmathArcTangentPolynomialLeadingCoefficient) + k_xmathArcTangentCoefficientPairHigh) * reducedValueSquared) - *(&k_xmathArcTangentCoefficientPairHigh + 1)) * reducedValueSquared) + k_xmathArcTangentCoefficientPairMiddle) * reducedValueSquared) - *(&k_xmathArcTangentCoefficientPairMiddle + 1)) * reducedValueSquared) + k_xmathArcTangentCoefficientPairLow) * reducedValueSquared) - *(&k_xmathArcTangentCoefficientPairLow + 1)) * reducedValueSquared) + k_xmathArcTangentCoefficientAndOffset) * reducedValue) + *(&k_xmathArcTangentCoefficientAndOffset + 1);
    if (value < 0.0f) {
        result = -result;
    }
    return result;
}

f32 XMath_EvaluateArcSine(f32 x) {
    s32 negative;
    f32 poly;
    f32 root;
    f32 result;

    if (k_xmathArcSineClampConstants < x) {
        x = k_xmathArcSineClampConstants;
    }
    do {
        if (x < *(&k_xmathArcSineClampConstants + 1)) {
            x = *(&k_xmathArcSineClampConstants + 1);
        }
        negative = 0;
        if (x < 0.0f) {
            negative = 1;
            x = -x;
        }
        poly = (((((x * k_xmathArcSineCoefficientPairHigh + *(&k_xmathArcSineCoefficientPairHigh + 1)) * x - k_xmathArcSineCoefficientPairMiddle) * x + *(&k_xmathArcSineCoefficientPairMiddle + 1)) * x
                 - k_xmathArcSineCoefficientPairLow) * x) + *(&k_xmathArcSineCoefficientPairLow + 1);
        x = k_xmathArcSineClampConstants - x;
        if (x <= 0.0f) {
            root = 0.0f;
        } else {
            root = Gu_Sqrtf(x);
        }
    } while (0);
    result = k_xmathArcSineResultConstants - root * poly;
    if (negative) {
        result = -result;
    }
    return result;
}

f32 XMath_EvaluateArcCosine(f32 x) {
    s32 negative;
    f32 poly;
    f32 root;
    f32 result;

    if (*(&k_xmathArcSineResultConstants + 1) < x) {
        x = *(&k_xmathArcSineResultConstants + 1);
    }
    do {
        if (x < k_xmathArcCosineLowerClamp) {
            x = k_xmathArcCosineLowerClamp;
        }
        negative = 0;
        if (x < 0.0f) {
            negative = 1;
            x = -x;
        }
        poly = (((((x * (-0.011680527590215206f) + k_xmathArcCosineCoefficientPairHigh) * x - *(&k_xmathArcCosineCoefficientPairHigh + 1)) * x + k_xmathArcCosineCoefficientPairLow) * x
                 - *(&k_xmathArcCosineCoefficientPairLow + 1)) * x) + k_xmathArcCosineCoefficientAndOffset;
        x = *(&k_xmathArcSineResultConstants + 1) - x;
        if (x <= 0.0f) {
            root = 0.0f;
        } else {
            root = Gu_Sqrtf(x);
        }
    } while (0);
    result = *(&k_xmathArcCosineCoefficientAndOffset + 1) - root * poly;
    if (negative) {
        result = -result;
    }
    return *(&k_xmathArcCosineCoefficientAndOffset + 1) - result;
}

inline static f32 wrap_centered(f32 angle)
{
  f32 angleReductionValue;
  f32 value;

  f32 originalAngle;
  value = angle;
  originalAngle = value;
  if (1)
  {
    if (((long long) (k_xmathCenteredAngleUpperThreshold < originalAngle)) || (originalAngle < k_xmathCenteredAngleLowerThreshold))
    {
      value = (f32) FloatModulo((f64) value, k_xmathCenteredAnglePeriodDouble);
    }
    else
    {
      if (k_xmathCenteredAngleUpperLimit < value)
      {
        angleReductionValue = k_xmathCenteredAngleUpperLimit;
        do
        {
          value -= angleReductionValue;
          if (1)
          {
          }
        }
        while (angleReductionValue < value);
      }
      if (value < 0.0f)
      {
        do
        {
          value += k_xmathCenteredAnglePeriod;
        }
        while (value < (angleReductionValue = 0.0f));
      }
    }
  }
  return value;
}

f32 XMath_WrapAnglePositive(f32 angle)
{
  f32 angleReductionValue;
  f32 value;
  f32 *angleWrapConstants;
  f32 originalAngle;
  value = angle;
  originalAngle = value;
  if (1)
  {
    if (((long long) (k_xmathPositiveAngleModuloThreshold < originalAngle)) || (originalAngle < (-25.13274383544922f)))
    {
      value = (f32) FloatModulo((f64) value, k_xmathPositiveAnglePeriodDouble);
    }
    else
    {
      if (k_xmathPositiveAngleWrapConstants[0] < value)
      {
        angleReductionValue = k_xmathPositiveAngleWrapConstants[0];
        do
        {
          value -= angleReductionValue;
          if (1)
          {
          }
        }
        while (angleReductionValue < value);
      }
      if (value < 0.0f)
      {
        do
        {
          angleWrapConstants = k_xmathPositiveAngleWrapConstants;
          value += angleWrapConstants[1];
        }
        while (value < (angleReductionValue = 0.0f));
      }
    }
  }
  return value;
}

f32 XMath_WrapAngleCentered(f32 x)
{
  f32 centerOffset;
  float shiftedAngle;
  f32 wrappedAngle;
  centerOffset = k_xmathAngleCenterOffset;
  wrappedAngle = x + centerOffset;
  {
    shiftedAngle = wrappedAngle;
  }
  wrappedAngle = wrap_centered(shiftedAngle);
  return wrappedAngle - k_xmathCenteredAngleOffset;
}

/* Normalizes an offset angle, using double remainder for large magnitudes and repeated single-precision adjustments otherwise. */







inline static f32 wrap(f32 angle)
{
  f32 angleReductionValue;
  f32 value;
  f32 *angleWrapConstants;
  f32 originalAngle;
  value = angle;
  originalAngle = value;
  if (1)
  {
    if (((long long) (k_xmathVectorAngleUpperThreshold < originalAngle)) || (originalAngle < k_xmathVectorAngleLowerThreshold))
    {
      value = (f32) FloatModulo((f64) value, k_xmathVectorAnglePeriodDouble);
    }
    else
    {
      if (k_xmathVectorAngleWrapConstants[0] < value)
      {
        angleReductionValue = k_xmathVectorAngleWrapConstants[0];
        do
        {
          value -= angleReductionValue;
          if (1)
          {
          }
        }
        while (angleReductionValue < value);
      }
      if (value < 0.0f)
      {
        do
        {
          angleWrapConstants = k_xmathVectorAngleWrapConstants;
          value += angleWrapConstants[1];
        }
        while (value < (angleReductionValue = 0.0f));
      }
    }
  }
  return value;
}


static inline f32 centered(f32 x)
{
  f32 centerOffset;
  float shiftedAngle;
  f32 wrappedAngle;
  centerOffset = k_xmathVectorAngleCenterOffset;
  wrappedAngle = x + centerOffset;
  {
    shiftedAngle = wrappedAngle;
  }
  wrappedAngle = wrap(shiftedAngle);
  return wrappedAngle - k_xmathVectorAngleCenterResultOffset;
}



static inline f32 safe_sqrt(f32 x) {
    if (x <= 0.0f) {
        return 0.0f;
    }
    return Gu_Sqrtf(x);
}

f32 XMath_SubtractAnglesCentered(f32 a, f32 b) { return centered(a - b); }

/** Clear a three-component floating-point vector. */
void Vector3Zero(float *vector) {
    vector[0] = vector[1] = vector[2] = 0.0f;
}

void Vector3Set(void *destination, float xValue, float yValue, float zValue) {
    CVector3 *vector = destination;
    vector->x = xValue;
    vector->y = yValue;
    vector->z = zValue;
}

/** Split a three-float vector into three destinations. */
void Vector3Unpack(float *source, float *xOut, float *yOut, float *zOut) {
    *xOut = source[0];
    *yOut = source[1];
    *zOut = source[2];
}

void Vector3Copy(Triple *destination, Triple *source) {
    *destination = *source;
}

/** Store the component-wise sum of the left and right vectors in the destination. */
void Vector3Add(void *destination, void *leftVector, void *rightVector) {
    CVector3 *destinationVector = destination;
    CVector3 *left = leftVector;
    CVector3 *right = rightVector;
    destinationVector->x = left->x + right->x;
    destinationVector->y = left->y + right->y;
    destinationVector->z = left->z + right->z;
}

/** Store the component-wise difference of the left and right vectors in the destination. */
void Vector3Subtract(void *destination, void *leftVector, void *rightVector) {
    CVector3 *destinationVector = destination;
    CVector3 *left = leftVector;
    CVector3 *right = rightVector;
    destinationVector->x = left->x - right->x;
    destinationVector->y = left->y - right->y;
    destinationVector->z = left->z - right->z;
}

/** Scale a 3-vector (source) by a scalar (scaleFactor), store into destination. */
void Vector3Scale(void *destination, void *source, f32 scaleFactor) {
    CVector3 *sourceVector = source;
    CVector3 *destinationVector = destination;
    destinationVector->x = sourceVector->x * scaleFactor;
    destinationVector->y = sourceVector->y * scaleFactor;
    destinationVector->z = sourceVector->z * scaleFactor;
}

/** Store the negated source vector in the destination. */
void Vector3Negate(void *destination, void *source) {
    CVector3 *destinationVector = destination;
    CVector3 *sourceVector = source;
    destinationVector->x = -sourceVector->x;
    destinationVector->y = -sourceVector->y;
    destinationVector->z = -sourceVector->z;
}

void Vector3Distance(f32 *a, f32 *b) {
    f32 dx = a[0] - b[0];
    f32 dy = a[1] - b[1];
    f32 dz = a[2] - b[2];
    f32 sum;

    sum = ((dx * dx) + (dy * dy)) + (dz * dz);
    if (!(((dx * dx) + (dy * dy)) + (dz * dz) <= 0.0f)) {
        sum = dz;
        Gu_Sqrtf(((dx * dx) + (dy * dy)) + (sum * sum));
    }
}

f32 Vector3Dot(f32 *a, f32 *b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/** Cross product of two vectors, written through a local temp to allow aliasing with out. */
void Vector3Cross(CVector3 *out, CVector3 *lhs, CVector3 *rhs) {
    CVector3 result;

    result.x = (lhs->y * rhs->z) - (lhs->z * rhs->y);
    result.y = (lhs->z * rhs->x) - (lhs->x * rhs->z);
    result.z = (lhs->x * rhs->y) - (lhs->y * rhs->x);
    *out = result;
}

void XMath_EvaluateVectorLength(CVector3 *vector)
{
  f32 sum;
  sum = ((vector->x * vector->x) + (vector->y * vector->y)) + (vector->z * vector->z);
  if (!((((vector->x * vector->x) + (vector->y * vector->y)) + (vector->z * vector->z)) <= 0.0f))
  {
    sum = vector->z;
    Gu_Sqrtf(((vector->x * vector->x) + (vector->y * vector->y)) + (sum * sum));
  }
}

void Vector3Normalize(f32 *vector) {
    f32 mag;
    f32 scale;

    mag = safe_sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));
    scale = k_xmathVectorNormalizeUnit / mag;
    vector[0] = vector[0] * scale;
    vector[1] = vector[1] * scale;
    vector[2] = vector[2] * scale;
}

void Vector3RotatePitch(CVector3 *destination, CVector3 *source, f32 angle) {
    CVector3 rotated;
    f32 sinOut;
    f32 cosOut;

    XMath_EvaluateSineCosine(angle, &sinOut, &cosOut);
    rotated.x = source->x;
    rotated.y = (cosOut * source->y) - (sinOut * source->z);
    rotated.z = (cosOut * source->z) + (sinOut * source->y);
    *destination = rotated;
}

void Vector3RotateYaw(CVector3 *destination, CVector3 *source, f32 angle) {
    CVector3 rotated;
    f32 sineAngle;
    f32 cosineAngle;

    XMath_EvaluateSineCosine(angle, &sineAngle, &cosineAngle);
    rotated.x = (cosineAngle * source->x) + (sineAngle * source->z);
    rotated.y = source->y;
    rotated.z = (cosineAngle * source->z) - (sineAngle * source->x);
    *destination = rotated;
}

void Vector3RotateRoll(CVector3 *destination, CVector3 *source, f32 angle) {
    CVector3 rotated;
    f32 sineAngle;
    f32 cosineAngle;

    XMath_EvaluateSineCosine(angle, &sineAngle, &cosineAngle);
    rotated.x = (cosineAngle * source->x) - (sineAngle * source->y);
    rotated.y = (cosineAngle * source->y) + (sineAngle * source->x);
    rotated.z = source->z;
    *destination = rotated;
}

void Vector3Angles(f32 *vector, f32 *pitchOut, f32 *yawOut) {
    f32 magnitude_squared;
    f32 magnitude;
    f32 x;
    f32 z;

    x = vector[0];
    z = vector[2];
    x *= x;
    z *= z;
    x += z;
    magnitude_squared = x;
    if (magnitude_squared <= 0.0f) {
        magnitude = 0.0f;
    } else {
        magnitude = Gu_Sqrtf(magnitude_squared);
    }
    *yawOut = XMath_EvaluateArcTangentTwo(vector[0], vector[2]);
    *pitchOut = -XMath_EvaluateArcTangentTwo(vector[1], magnitude);
}

void Vector3AnglesInverse(f32 *vector, f32 *pitchOut, f32 *yawOut) {
    f32 magnitude_squared;
    f32 magnitude;
    f32 x;
    f32 z;

    x = vector[0];
    z = vector[2];
    x *= x;
    z *= z;
    x += z;
    magnitude_squared = x;
    if (magnitude_squared <= 0.0f) {
        magnitude = 0.0f;
    } else {
        magnitude = Gu_Sqrtf(magnitude_squared);
    }
    *yawOut = XMath_EvaluateArcTangentTwo(vector[0], vector[2]);
    *pitchOut = XMath_EvaluateArcTangentTwo(vector[1], magnitude);
    *yawOut = -*yawOut;
}

/* Projects n vectors onto the screen plane: each one with depth above 0.01 becomes (ox + sx * x / z, oy + sy * y / z, z), and any other becomes zero. */



void Vector3ProjectArray(CVector3 *out, CVector3 *in, s32 n, f32 ox, f32 sx, f32 oy, f32 sy) {
    s32 i;

    for (i = 0; i < n; i++) {
        if (in[i].z > 0.01f) {
            out[i].x = ox + sx * (in[i].x / in[i].z);
            out[i].y = oy + sy * (in[i].y / in[i].z);
            out[i].z = in[i].z;
        } else {
            out[i].x = 0.0f;
            out[i].y = 0.0f;
            out[i].z = 0.0f;
        }
    }
}

void Vector3IntersectPlane(CVector3 *intersectionOut, CVector3 *lineStart, CVector3 *lineEnd, f32 normalX, f32 normalY, f32 normalZ, f32 planeOffset) {
    CVector3 delta;
    f32 numerator;
    f32 denominator;
    f32 fraction;

    delta.x = lineEnd->x - lineStart->x;
    delta.y = lineEnd->y - lineStart->y;
    delta.z = lineEnd->z - lineStart->z;
    numerator = -((normalX * lineStart->x) + (normalY * lineStart->y) + (normalZ * lineStart->z) + planeOffset);
    denominator = (normalX * delta.x) + (normalY * delta.y) + (normalZ * delta.z);
    if (!(denominator < k_xmathPlaneDenominatorUpperTolerance) || (fraction = k_xmathPlaneParallelFraction, !(k_xmathPlaneDenominatorLowerTolerance < denominator))) {
        fraction = numerator / denominator;
    }
    intersectionOut->x = lineStart->x + (fraction * delta.x);
    intersectionOut->y = lineStart->y + (fraction * delta.y);
    intersectionOut->z = lineStart->z + (fraction * delta.z);
}

/* Copies a whole 4x4 matrix from source to destination. */
void XMath_CopyMatrix(void *destination, void *source) {
    *(Matrix *)destination = *(Matrix *)source;
}

void XMath_SetMatrixElements(MatrixRecord *matrix, float element00, float element01, float element02,
                    float element03, float element10, float element11, float element12,
                    float element13, float element20, float element21, float element22,
                    float element23, float element30, float element31, float element32, float element33) {
    matrix->matrix.m[0] = element00;
    matrix->matrix.m[4] = element01;
    matrix->matrix.m[8] = element02;
    matrix->matrix.m[12] = element03;
    matrix->matrix.m[1] = element10;
    matrix->matrix.m[5] = element11;
    matrix->matrix.m[9] = element12;
    matrix->matrix.m[13] = element13;
    matrix->matrix.m[2] = element20;
    matrix->matrix.m[6] = element21;
    matrix->matrix.m[10] = element22;
    matrix->matrix.m[14] = element23;
    matrix->matrix.m[3] = element30;
    matrix->matrix.m[7] = element31;
    matrix->matrix.m[11] = element32;
    matrix->matrix.m[15] = element33;
}

void XMath_ClearMatrix(s32 destination) {
    XPlus_FillBytes(destination, 0, 64);
}

void XMath_SetIdentityMatrix(s32 matrixAddress) {
    Matrix *matrix = (Matrix *)matrixAddress;

    XPlus_FillBytes(matrixAddress, 0, 64);
    matrix->m[15] = matrix->m[10] = matrix->m[5] = matrix->m[0] = (f32)k_xmathIdentityMatrixUnit;
}

void XMath_TransposeMatrix(f32 *matrix) {
    s32 i;
    s32 j;
    s32 offset1;
    s32 offset2;
    f32 temp;

    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            offset2 = j * 16 + i * 4;
            offset1 = i * 16 + j * 4;
            temp = *(f32 *)((u8 *)matrix + offset2);
            *(f32 *)((u8 *)matrix + offset2) =
                *(f32 *)((u8 *)matrix + offset1);
            *(f32 *)((u8 *)matrix + offset1) = temp;
        }
    }
}

/** Scatter three floats from scale into matrix's fields. */
void XMath_SetMatrixScaleDiagonal(Matrix *matrix, CVector3 *scale) {
    matrix->m[0] = scale->x;
    matrix->m[5] = scale->y;
    matrix->m[10] = scale->z;
}

void XMath_ScaleMatrixRows(void *matrix, void *scale) {
    Matrix *m = (Matrix *)matrix;
    CVector3 *v = (CVector3 *)scale;

    m->m[0] = m->m[0] * v->x;
    m->m[4] = m->m[4] * v->x;
    m->m[8] = m->m[8] * v->x;
    m->m[1] = m->m[1] * v->y;
    m->m[5] = m->m[5] * v->y;
    m->m[9] = m->m[9] * v->y;
    m->m[2] = m->m[2] * v->z;
    m->m[6] = m->m[6] * v->z;
    m->m[10] = m->m[10] * v->z;
    m->m[12] = m->m[12] * v->x;
    m->m[13] = m->m[13] * v->y;
    m->m[14] = m->m[14] * v->z;
}

/** Broadcast a float value into three fields of the object. */
void XMath_SetUniformMatrixScaleDiagonal(Matrix *matrix, float value) {
    matrix->m[0] = value;
    matrix->m[5] = value;
    matrix->m[10] = value;
}

void XMath_ScaleMatrixUniformly(void *matrix, f32 scale) {
    Matrix *o = (Matrix *)matrix;

    o->m[0] = o->m[0] * scale;
    o->m[4] = o->m[4] * scale;
    o->m[8] = o->m[8] * scale;
    o->m[1] = o->m[1] * scale;
    o->m[5] = o->m[5] * scale;
    o->m[9] = o->m[9] * scale;
    o->m[2] = o->m[2] * scale;
    o->m[6] = o->m[6] * scale;
    o->m[10] = o->m[10] * scale;
    o->m[12] = o->m[12] * scale;
    o->m[13] = o->m[13] * scale;
    o->m[14] = o->m[14] * scale;
}

void XMath_ResetMatrixRotation(Matrix3x4View *matrix) {
    s32 col;
    s32 row;

    col = 0;
    row = 0;
    do {
        row = 0;
        do {
            matrix->m[row][col] = 0;
            row += 1;
        } while (row < 3);
        col += 1;
    } while (col < 3);
    matrix->m[0][0] = k_xmathRotationResetUnit;
    matrix->m[1][1] = k_xmathRotationResetUnit;
    matrix->m[2][2] = k_xmathRotationResetUnit;
}

void XMath_PremultiplyEulerRotation(s32 matrix, f32 *angles) {
    f32 buf[16];
    MatrixFromAngles(buf, angles);
    XMath_MultiplyMatrices(matrix, buf, matrix);
}

void XMath_PremultiplyPitchRotation(s32 destinationMatrix, f32 angle) {
    Matrix matrix;
    f32 sineAngle;
    f32 cosineAngle;
    Matrix *p;

    if (angle != 0.0f) {
        XMath_EvaluateSineCosine(angle, &sineAngle, &cosineAngle);
        p = &matrix;
        XPlus_FillBytes(p, 0, 64);
        p->m[0] = k_xmathPitchRotationUnit;
        {
            f32 cosineValue = cosineAngle;
            f32 sineValue = sineAngle;
            p->m[5] = k_xmathPitchRotationUnit;
            p->m[10] = k_xmathPitchRotationUnit;
            p->m[15] = k_xmathPitchRotationUnit;
            matrix.m[5] = cosineValue;
            matrix.m[9] = -sineValue;
            matrix.m[6] = sineValue;
            matrix.m[10] = cosineValue;
        }
        XMath_MultiplyMatrices(destinationMatrix, (s32) p, destinationMatrix);
    }
}

void XMath_PremultiplyYawRotation(s32 matrixAddress, f32 radians) {
    Matrix matrix;
    f32 sinAngle;
    f32 cosAngle;
    Matrix *p;

    if (radians != 0.0f) {
        XMath_EvaluateSineCosine(radians, &sinAngle, &cosAngle);
        p = &matrix;
        XPlus_FillBytes(p, 0, 64);
        p->m[0] = k_xmathYawRotationUnit;
        {
            f32 cosineValue = cosAngle;
            f32 sineValue = sinAngle;
            f32 negativeSine;
            p->m[5] = k_xmathYawRotationUnit;
            p->m[10] = k_xmathYawRotationUnit;
            p->m[15] = k_xmathYawRotationUnit;
            negativeSine = -sineValue;
            matrix.m[8] = sineValue;
            matrix.m[0] = cosineValue;
            matrix.m[2] = negativeSine;
            matrix.m[10] = cosineValue;
        }
        XMath_MultiplyMatrices(matrixAddress, (s32) p, matrixAddress);
    }
}

void XMath_PremultiplyRollRotation(s32 matrixAddress, f32 radians) {
    Matrix matrix;
    f32 sinAngle;
    f32 cosAngle;
    Matrix *p;

    if (radians != 0.0f) {
        XMath_EvaluateSineCosine(radians, &sinAngle, &cosAngle);
        p = &matrix;
        XPlus_FillBytes(p, 0, 64);
        p->m[0] = k_xmathRollRotationUnit;
        {
            f32 cosineValue = cosAngle;
            f32 sineValue = sinAngle;
            f32 negativeSine;
            p->m[5] = k_xmathRollRotationUnit;
            p->m[10] = k_xmathRollRotationUnit;
            p->m[15] = k_xmathRollRotationUnit;
            negativeSine = -sineValue;
            matrix.m[0] = cosineValue;
            matrix.m[4] = negativeSine;
            matrix.m[1] = sineValue;
            matrix.m[5] = cosineValue;
        }
        XMath_MultiplyMatrices(matrixAddress, (s32) p, matrixAddress);
    }
}

/** Clear the translation row of the matrix. */
void XMath_ClearMatrixTranslation(Matrix *matrix) {
    matrix->m[12] = 0;
    matrix->m[13] = 0;
    matrix->m[14] = 0;
}

/** Copy a three-float vector into the translation row of the matrix. */
void XMath_SetMatrixTranslation(Matrix *matrix, float *translation) {
    matrix->m[12] = translation[0];
    matrix->m[13] = translation[1];
    matrix->m[14] = translation[2];
}

/** Copy the translation row of the matrix into the output vector. */
void XMath_GetMatrixTranslation(char *object, float *output) {
    output[0] = ((Matrix *)(object))->m[12];
    output[1] = ((Matrix *)(object))->m[13];
    output[2] = ((Matrix *)(object))->m[14];
}

void XMath_AddMatrixTranslation(Matrix *matrix, void *translation) {
    CVector3 *offset = translation;
    matrix->m[12] = matrix->m[12] + offset->x;
    matrix->m[13] = matrix->m[13] + offset->y;
    matrix->m[14] = matrix->m[14] + offset->z;
}

/** Combine three column vectors into the first three matrix columns. */
void XMath_SetMatrixRows(float *matrix, float *rowX, float *rowY, float *rowZ) {
    matrix[0] = rowX[0];
    matrix[4] = rowX[1];
    matrix[8] = rowX[2];
    matrix[1] = rowY[0];
    matrix[5] = rowY[1];
    matrix[9] = rowY[2];
    matrix[2] = rowZ[0];
    matrix[6] = rowZ[1];
    matrix[10] = rowZ[2];
}

/** Split the first three matrix columns into three vectors. */
void XMath_GetMatrixRows(float *inputMatrix, float *rowX, float *rowY, float *rowZ) {
    rowX[0] = inputMatrix[0];
    rowX[1] = inputMatrix[4];
    rowX[2] = inputMatrix[8];
    rowY[0] = inputMatrix[1];
    rowY[1] = inputMatrix[5];
    rowY[2] = inputMatrix[9];
    rowZ[0] = inputMatrix[2];
    rowZ[1] = inputMatrix[6];
    rowZ[2] = inputMatrix[10];
}

/** Write three row vectors into the first three matrix rows. */
void XMath_SetMatrixColumns(float *matrix, float *columnX, float *columnY, float *columnZ) {
    matrix[0] = columnX[0];
    matrix[1] = columnX[1];
    matrix[2] = columnX[2];
    matrix[4] = columnY[0];
    matrix[5] = columnY[1];
    matrix[6] = columnY[2];
    matrix[8] = columnZ[0];
    matrix[9] = columnZ[1];
    matrix[10] = columnZ[2];
}

/** Split the first three matrix rows into three row vectors. */
void XMath_GetMatrixColumns(float *inputMatrix, float *columnX, float *columnY, float *columnZ) {
    columnX[0] = inputMatrix[0];
    columnX[1] = inputMatrix[1];
    columnX[2] = inputMatrix[2];
    columnY[0] = inputMatrix[4];
    columnY[1] = inputMatrix[5];
    columnY[2] = inputMatrix[6];
    columnZ[0] = inputMatrix[8];
    columnZ[1] = inputMatrix[9];
    columnZ[2] = inputMatrix[10];
}

/** Thin wrapper forwarding destinationMatrix twice (as first and third args) to XMath_MultiplyMatrices. */
void XMath_PremultiplyMatrix(int destinationMatrix, int leftMatrix) {
    XMath_MultiplyMatrices(destinationMatrix, leftMatrix, destinationMatrix);
}

void XMath_PostmultiplyMatrix(s32 destinationMatrix, s32 rightMatrix) {
    XMath_MultiplyMatrices(destinationMatrix, destinationMatrix, rightMatrix);
}

void XMath_TransformPointArray(void *matrix, void *outputPoints, void *inputPoints, s32 pointCount) {
    Matrix *m = (Matrix *)matrix;
    s32 i;
    f32 vx, vy, vz;

    i = 0;
    if (pointCount > 0) {
        do {
            CVector3 *v = (CVector3 *)inputPoints + i;
            CVector3 *out = (CVector3 *)outputPoints + i;

            vx = v->x;
            vy = v->y;
            vz = v->z;
            out->x = (m->m[0] * vx) + (m->m[4] * vy) + (m->m[8] * vz) + m->m[12];
            out->y = (m->m[1] * vx) + (m->m[5] * vy) + (m->m[9] * vz) + m->m[13];
            out->z = (m->m[2] * vx) + (m->m[6] * vy) + (m->m[10] * vz) + m->m[14];
            i += 1;
        } while (i < pointCount);
    }
}

void XMath_BuildAxisAngleMatrix(struct MatrixF *matrixF, CVector3 *axis, f32 radians) {
    f32 sine;
    f32 cosine;
    f32 cosine_value;
    f32 one;
    f32 one_minus_cosine;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 txx;
    f32 txy;
    f32 txz;
    f32 tyy;
    f32 tyz;
    f32 tzz;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 zero;

    XMath_EvaluateSineCosine(radians, &sine, &cosine);
    cosine_value = cosine;
    one = k_xmathAxisAngleUnit;
    one_minus_cosine = one - cosine_value;
    tx = one_minus_cosine * axis->x;
    ty = one_minus_cosine * axis->y;
    tz = one_minus_cosine * axis->z;
    txx = tx * axis->x;
    txy = tx * axis->y;
    txz = tx * axis->z;
    tyy = ty * axis->y;
    tyz = ty * axis->z;
    tzz = tz * axis->z;
    sx = sine * axis->x;
    sy = sine * axis->y;
    sz = sine * axis->z;
    zero = 0.0f;
    matrixF->m[3][2] = zero;
    matrixF->m[3][1] = zero;
    matrixF->m[3][0] = zero;
    matrixF->m[2][3] = zero;
    matrixF->m[1][3] = zero;
    matrixF->m[0][3] = zero;
    matrixF->m[3][3] = one;
    matrixF->m[0][0] = txx + cosine_value;
    matrixF->m[0][1] = txy + sz;
    matrixF->m[0][2] = txz - sy;
    matrixF->m[1][0] = txy - sz;
    matrixF->m[1][1] = tyy + cosine_value;
    matrixF->m[1][2] = tyz + sx;
    matrixF->m[2][0] = txz + sy;
    matrixF->m[2][1] = tyz - sx;
    matrixF->m[2][2] = tzz + cosine_value;
}

void XMath_BuildScaleRotationTranslationMatrix(void *matrix, CVector3 *scale, void *angles, CVector3 *translation) {
    Matrix *m = matrix;

    MatrixFromAngles(matrix, angles);

    m->m[0] = m->m[0] * scale->x;
    m->m[1] = m->m[1] * scale->x;
    m->m[2] = m->m[2] * scale->x;
    m->m[4] = m->m[4] * scale->y;
    m->m[5] = m->m[5] * scale->y;
    m->m[6] = m->m[6] * scale->y;
    m->m[8] = m->m[8] * scale->z;
    m->m[9] = m->m[9] * scale->z;
    m->m[10] = m->m[10] * scale->z;
    m->m[12] = m->m[12] + translation->x;
    m->m[13] = m->m[13] + translation->y;
    m->m[14] = m->m[14] + translation->z;
}




/* Unit scale of each angle-matrix builder (Matrix_FromAngles and its axis variants). */
float k_xmathAngleMatrixIdentityUnit = 1.0f;
float k_xmathAngleMatrixYUnit = 1.0f;
float k_xmathAngleMatrixXUnit = 1.0f;
float k_xmathAngleMatrixZUnit = 1.0f;
float k_xmathAnglesMatrixHomogeneousUnit = 1.0f;

#if !(defined(VERSION_US_REV1))
const float k_xmathUnit[1] = {
    1.0f,
};
#endif

/* YXZ and ZYX Euler extraction: clamp bounds, the arcsine polynomial coefficient and addend of each Horner step, half pi and the sine tolerance (each second word is read through the first one's address); then the vector-normalize, determinant-tolerance and affine units. */
float k_yxzExtractionClampAndZero = 1.0f;
float k_yxzExtractionClampMinimum = -1.0f;
float k_yxzExtractionPolynomialCoefficientsHigh = -0.0116805276f;
float k_yxzExtractionPolynomialCoefficientsHighAddend = 0.0308918804f;
float k_yxzExtractionPolynomialCoefficientsMiddle = 0.0501743034f;
float k_yxzExtractionPolynomialCoefficientsMiddleAddend = 0.0889789909f;
float k_yxzExtractionPolynomialCoefficientsLow = 0.214598805f;
float k_yxzExtractionPolynomialCoefficientsLowAddend = 1.57079625f;
float k_yxzExtractionHalfPi = 1.57079637f;
float k_yxzExtractionSineTolerance = 9.99999975e-05f;
float k_zyxExtractionClampAndZero = 1.0f;
float k_zyxExtractionClampMinimum = -1.0f;
float k_zyxExtractionPolynomialCoefficientsHigh = -0.0116805276f;
float k_zyxExtractionPolynomialCoefficientsHighAddend = 0.0308918804f;
float k_zyxExtractionPolynomialCoefficientsMiddle = 0.0501743034f;
float k_zyxExtractionPolynomialCoefficientsMiddleAddend = 0.0889789909f;
float k_zyxExtractionPolynomialCoefficientsLow = 0.214598805f;
float k_zyxExtractionPolynomialCoefficientsLowAddend = 1.57079625f;
float k_zyxExtractionHalfPi = 1.57079637f;
float k_xmathNormalizeXUnit = 1.0f;
float k_xmathNormalizeYUnit = 1.0f;
float k_xmathMatrixDeterminantTolerance = 9.99999975e-05f;
float k_xmathAffineMatrixUnit = 1.0f;






#if defined(VERSION_US_REV1)

const float k_xmathUnit[1] = {
    1.0f,
};

#endif

#if !(defined(VERSION_US_REV1))
const float k_xmathEvaluatereciprocalsquarerootUnit[1] = {
    1.0f,
};
#endif



/* Keep the original four-byte constant-pool alignment; the linked coefficient
 * arrays themselves remain eight-byte aligned at their ROM addresses. */



#if defined(VERSION_US_REV1)
const float k_xmathEvaluatereciprocalsquarerootUnit[1] = {
    1.0f,
};

#endif
















/* Retained data for this translation unit. */

#if defined(VERSION_US_REV1)
const unsigned int k_xmathSplitdoubleexponentDataZero[2] = {
    0x00000000, 0x00000000,
};
#endif
#if defined(VERSION_US_REV1)
const float k_XmathSplitdoubleexponentHalfPiWords[1] = {
    1.5707964f,
};
#endif
#if defined(VERSION_US_REV1)
const float k_xmathSplitdoubleexponentHalfPiCopy[1] = {
    1.5707964f,
};
#endif
#if defined(VERSION_US_REV1)
const double k_xmathSplitdoubleexponentPolynomialDoubles[5] = {
    0.007812505457518838, 2.648880056980157e-16, 3.90505195515418e-11, 1.3156112606732471e-08,
    0.0078124599427304665,
};
#endif
#if defined(VERSION_US_REV1)
const unsigned int k_xmathSplitdoubleexponentCoefficientWords[9] = {
    0x3F800000, 0xBF800000, 0xBC3F5FAF, 0x3CFD10F8, 0x3D4D8392, 0x3DB63A9E, 0x3E5BBFCA, 0x3FC90FDA,
    0x3FC90FDB,
};
#endif
#if defined(VERSION_US_REV1)
const float k_xmathSplitdoubleexponentSigns[2] = {
    1.0f, -1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_xmathSubtractanglescenteredRangeFloats[8] = {
    3.1415927f, 25.132744f, -25.132744f, 2.392699f, -0.0f, 6.283186f, 6.283186f, 3.1415927f,
};
#endif
#if defined(VERSION_US_REV1)
const float k_xmathSubtractanglescenteredUnit[1] = {
    1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float k_vectorIntersectPlaneUnitScales[6] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
};
#endif
const f64 k_xmathFloorIntegralLimit = 4503599627370496.0;
const f64 k_xmathFloorSignBoundary = 0.0;
const f64 k_xmathFloorIntegralBias = 1.0;
const f64 k_xmathCeilIntegralLimit = 4503599627370496.0;
const f64 k_xmathCeilSignBoundary = 0.0;
const f64 k_xmathCeilIntegralBias = 1.0;
const f64 k_xmathCeilRoundUpUnit = 1.0;
const f64 k_xmathFractionIntegralLimit = 4503599627370496.0;
const f64 k_xmathFractionSignBoundary = 0.0;
const f64 k_xmathFractionIntegralBias = 1.0;
double k_xmathNaturalLogToDecimalScale = 0.4342944920063018;
double k_xmathExponentialUpperLimit = -2.7105049465376212e-20;
double k_xmathExponentialLowerLimit = 2.7105049465376212e-20;
double k_xmathExponentialInitialResult = 1.0;
double k_xmathExponentialToBinaryScale = 1.4426950216293335;
double k_xmathExponentialRoundingAndDenominatorConstant = 0.5;
double k_xmathExponentialReductionLeadingTerm = 0.693359375;
double k_xmathExponentialReductionTrailingTerm = 0.00021219444170128557;
double k_xmathExponentialNumeratorCubicCoefficient = 1.652032915444579e-05;
double k_xmathExponentialNumeratorLinearCoefficient = 0.006943599786609411;
double k_xmathExponentialDenominatorQuadraticCoefficient = 0.00049586285604164;
double k_xmathExponentialDenominatorLinearCoefficient = 0.0555538684129715;
double k_xmathExponentialNumeratorConstant = 0.25;
#if !defined(VERSION_US_REV1)
double k_xmathExponentSpecialValue = 0.0;
float k_xmathCosinePhaseOffset = 1.57079637f;
float k_xmathTangentCosinePhaseOffset = 1.57079637f;
float k_xmathArcTangentReductionUnit = 1.0f;
float k_xmathArcTangentPolynomialLeadingCoefficient = -0.00405405788f;
#endif

#if !defined(VERSION_US_REV1)
/* Arctangent and arcsine polynomial coefficient and addend of each Horner step (each second word is read through the first one's address), the arctangent quarter-pi offset and the arcsine/arccosine clamps. */
float k_xmathArcTangentCoefficientPairHigh = 0.0218612291f;
float k_xmathArcTangentCoefficientPairHighAddend = 0.055909887f;
float k_xmathArcTangentCoefficientPairMiddle = 0.0964200422f;
float k_xmathArcTangentCoefficientPairMiddleAddend = 0.139085338f;
float k_xmathArcTangentCoefficientPairLow = 0.199465364f;
float k_xmathArcTangentCoefficientPairLowAddend = 0.333298564f;
float k_xmathArcTangentCoefficientAndOffset = 0.999999344f;
float k_xmathArcTangentQuarterPi = 0.785398185f;
float k_xmathArcSineClampConstants = 1.0f;
float k_xmathArcSineClampMinimum = -1.0f;
float k_xmathArcSineCoefficientPairHigh = -0.0116805276f;
float k_xmathArcSineCoefficientPairHighAddend = 0.0308918804f;
float k_xmathArcSineCoefficientPairMiddle = 0.0501743034f;
float k_xmathArcSineCoefficientPairMiddleAddend = 0.0889789909f;
float k_xmathArcSineCoefficientPairLow = 0.214598805f;
float k_xmathArcSineCoefficientPairLowAddend = 1.57079625f;
float k_xmathArcSineResultConstants = 1.57079637f;
float k_xmathArcCosineUpperClamp = 1.0f;
float k_xmathArcCosineLowerClamp = -1.0f;
#endif

/* Arccosine polynomial coefficient and addend of each Horner step, its offset and half pi, and the positive-angle wrap threshold. */
float k_xmathArcCosineCoefficientPairHigh = 0.0308918804f;
float k_xmathArcCosineCoefficientPairHighAddend = 0.0501743034f;
float k_xmathArcCosineCoefficientPairLow = 0.0889789909f;
float k_xmathArcCosineCoefficientPairLowAddend = 0.214598805f;
float k_xmathArcCosineCoefficientAndOffset = 1.57079625f;
float k_xmathArcCosineHalfPi = 1.57079637f;
float k_xmathPositiveAngleModuloThreshold = 25.1327438f;

#if defined(VERSION_US) || defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
/* Plane-intersection tolerances and the identity, rotation and axis-angle units. */
float k_xmathPlaneDenominatorUpperTolerance = 0.00100000005f;
float k_xmathPlaneDenominatorLowerTolerance = -0.00100000005f;
float k_xmathPlaneParallelFraction = 0.5f;
float k_xmathIdentityMatrixUnit = 1.0f;
float k_xmathRotationResetUnit = 1.0f;
float k_xmathPitchRotationUnit = 1.0f;
float k_xmathYawRotationUnit = 1.0f;
float k_xmathRollRotationUnit = 1.0f;
float k_xmathAxisAngleUnit = 1.0f;
#endif

#if defined(VERSION_US) || defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
/* Angle wrap periods, thresholds and offsets, vector-angle and plane tolerances, and the rotation units read by the angle helpers. */
double k_xmathPositiveAnglePeriodDouble = 6.2831859588623047;
f32 k_xmathPositiveAngleWrapConstants[2] = { 6.28318596f, 6.28318596f };
float k_xmathAngleCenterOffset = 3.14159274f;
float k_xmathCenteredAngleUpperThreshold = 25.1327438f;
float k_xmathCenteredAngleLowerThreshold = -25.1327438f;
double k_xmathCenteredAnglePeriodDouble = 6.2831859588623047;
float k_xmathCenteredAngleUpperLimit = 6.28318596f;
float k_xmathCenteredAnglePeriod = 6.28318596f;
float k_xmathCenteredAngleOffset = 3.14159274f;
float k_xmathVectorAngleCenterOffset = 3.14159274f;
float k_xmathVectorAngleUpperThreshold = 25.1327438f;
float k_xmathVectorAngleLowerThreshold = -25.1327438f;
double k_xmathVectorAnglePeriodDouble = 6.2831859588623047;
f32 k_xmathVectorAngleWrapConstants[2] = { 6.28318596f, 6.28318596f };
f32 k_xmathVectorAngleCenterResultOffset = 3.14159274f;
float k_xmathVectorNormalizeUnit = 1.0f;
#endif

/* Constants for decimal parsing, retained in their original data slots. */
double k_decimalInitialSign = 1.0;
double k_decimalInitialFraction = 0.0;
double k_decimalNegativeSign = -1.0;
double k_decimalInitialInteger = 0.0;
double k_decimalIntegerRadix = 10.0;
double k_decimalFractionZero = 0.0;
double k_decimalFractionRadix = 10.0;
double k_decimalInitialExponentSign = 1.0;
double k_decimalNegativeExponentSign = -1.0;
double k_decimalInitialExponent = 0.0;
double k_decimalExponentRadix = 10.0;
double k_decimalDirectExponentLimit = 30.0;
double k_decimalExponentLoopLimit = 0.0;
double k_decimalInitialExponentScale = 1.0;
double k_decimalExponentScaleRadix = 10.0;
double k_decimalPowerRadix = 10.0;
double k_decimalOverflowExponentLimit = 0.0;
