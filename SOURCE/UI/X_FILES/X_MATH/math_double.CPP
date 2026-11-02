#include "include_asm.h"
#include "COMMON/OBJRECAT3CV2.H"
#include "TYPES.H"
#include "MATH/math_double.H"
#include "MATH/XMATH_EVALUATEEXPONENTIALDOUBLE.H"

#include "MATH/DOUBLEBITS.H"

extern const f64 k_xmathScaleExponentOverflow;
extern const f64 k_xmathScaleExponentUnit;
extern const f64 k_xmathScaleExponentDenormalUnit;

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
