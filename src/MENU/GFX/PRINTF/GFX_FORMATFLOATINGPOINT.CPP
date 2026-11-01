#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/GFX_INITIALIZEFRONTENDSERVICES.H"
#include "MATH/XMATH_EVALUATEEXPONENTIALDOUBLE.H"
#include "MENU/GFX/GFX_FORMATFLOATINGPOINT.H"

s32 Gfx_FormatFloatingPoint(u8 *buf, f64 input, s32 ch, s32 width, s32 precision) {
    u8 fraction[128];
    u8 integer[128];
    u8 exponent[16];
    f64 value;
    f64 whole, digit, mantissa, mantissa_digit;
    u8 format = ch;
    s32 prec;
    s32 negative;
    u8 *fp = fraction;
    u8 *ip = &integer[127];
    u8 *ep = &exponent[15];
    u8 *iend = ip;
    s32 nf, ni, ne;
    s32 fixed;
    s32 pow_n, maxdigits, k;
    s32 i, n, e, carry, trim, padding, point;
    u8 *p, *q, *out;
    u8 *integer_carry;
    u8 *fp_trim, *exp_trim;
    u8 c, exp_negative;
    f64 scale, round, base, power, frac, sci_frac;
    f64 fixed_ten, fixed_base, fixed_limit;
    f64 norm_ten, sci_ten, sci_base, sci_bias, sci_limit;

    prec = precision;
    *ip = 0;
    *ep = 0;
    value = input;
    negative = value < g_formatNegativeThreshold;
    if (negative) value = -value;
    if (prec >= 127) prec = 126;
    if (prec == 6) {
        scale = g_formatDefaultPrecisionScale;
    } else {
        base = g_formatPositivePrecisionBase;
        pow_n = prec;
        if (pow_n == 0) {
            scale = g_formatZeroPrecisionScale;
        } else {
            if (pow_n < 0) {
                pow_n = -pow_n;
                base = g_formatNegativePrecisionBase;
            }
            power = g_formatPrecisionPowerIdentity;
            for (;;) {
                if (pow_n & 1) power *= base;
                pow_n >>= 1;
                if (!pow_n) break;
                base *= base;
            }
            scale = power;
        }
    }
    fixed = 0;
    round = g_formatRoundingNumerator / scale;
    if (format == 'f' || (format == 'g' &&
        (value == g_formatFixedZero || (value >= g_formatFixedMinimum && value < scale)))) {
        fixed = 1;
    }
    ni = 0;
    nf = ni;
    ne = ni;
    if (fixed) {
        value = XMath_SplitDoubleFraction(value, &whole);
        if (value >= round || format != 'g') {
            value += round;
            if (value >= g_formatFractionCarryUnit) {
                whole += g_formatFractionCarryUnit;
                value -= g_formatFractionCarryUnit;
            }
            frac = value;
            i = 0;
            if (i < prec) {
                fixed_ten = g_formatFractionDecimalBase;
                do {
                    frac = XMath_SplitDoubleFraction(frac * fixed_ten, &digit);
                    nf++;
                    *fp++ = (s32)digit + '0';
                    i++;
                } while (i < prec);
            }
            if (format == 'g') {
                for (fp_trim = fp - 1; fp_trim >= fraction && *fp_trim == '0'; fp_trim--) {
                    *fp_trim = 0;
                    nf--;
                }
            }
        }
        if (whole == g_formatIntegerZero) {
            if (format != 'g' || nf < prec || nf < width) {
                *--ip = '0';
                ni++;
            }
        } else if (whole <= g_formatDirectIntegerLimit) {
            n = (s32)whole;
            while (n != 0) {
                *--ip = n % 10 + '0';
                ni++;
                n /= 10;
            }
        } else {
            if (whole > g_formatLargeIntegerLimit) {
                fixed_limit = g_formatLargeIntegerLimit;
                fixed_base = g_formatLargeIntegerReciprocalBase;
                round = g_formatLargeIntegerRoundingBias;
                fixed_ten = g_formatLargeIntegerDecimalBase;
                do {
                    *--ip = (s32)((XMath_SplitDoubleFraction(whole * fixed_base, &whole) + round) * fixed_ten) + '0';
                    ni++;
                } while (whole > fixed_limit);
            }
        }
        if (format == 'g') {
            maxdigits = prec;
            if (maxdigits < width) maxdigits = width;
            trim = ni + nf - maxdigits;
            if (nf < trim) trim = nf;
            if (trim > 0) {
                for (p = &fraction[nf - 1]; p >= fraction && trim > 0; p--, trim--) {
                    nf--;
                    c = *p;
                    *p = 0;
                    if ((c & 0xff) >= '6') {
                        carry = 1;
                        for (q = p - 1; q >= fraction && carry; q--) {
                            c = ++*q;
                            if ((c & 0xff) >= ':') *q = '0';
                            else carry = 0;
                        }
                        if (carry) {
                            for (integer_carry = iend - 1; integer_carry >= ip && carry; integer_carry--) {
                                c = ++*integer_carry;
                                if ((c & 0xff) >= ':') *integer_carry = '0';
                                else carry = 0;
                            }
                            if (carry) {
                                *--ip = '1';
                                ni++;
                                trim--;
                            }
                        }
                    }
                }
            }
        }
    } else {
        e = 0;
        norm_ten = g_formatNormalizationDecimalBase;
        if (value >= norm_ten) {
        sci_base = g_formatScientificReciprocalBase;
        do {
            value *= sci_base;
            e++;
        } while (value >= norm_ten);
        }
        sci_limit = g_formatScientificDigitLimit;
        sci_bias = g_formatScientificRoundingBase - round;
        while (value > sci_limit) {
            if (value < sci_bias) {
                value *= g_formatScientificValueScale;
                e--;
            } else break;
        }
        value = XMath_SplitDoubleFraction(value, &mantissa);
        if (format == 'g') {
            prec--;
            scale *= g_formatScientificPrecisionScale;
            round = g_formatScientificRoundingNumerator / scale;
        }
        if (value >= round || format != 'g') {
            value += round;
            if (value >= g_formatScientificFractionCarryUnit) {
                value -= g_formatScientificFractionCarryUnit;
                mantissa += g_formatScientificFractionCarryUnit;
                if (mantissa >= g_formatMantissaCarryLimit) {
                    e++;
                    mantissa *= g_formatMantissaDecimalScale;
                    value *= g_formatMantissaDecimalScale;
                }
            }
            sci_frac = value;
            i = 0;
            if (i < prec) {
                scale = g_formatScientificFractionDecimalBase;
                do {
                    sci_frac = XMath_SplitDoubleFraction(sci_frac * scale, &mantissa_digit);
                    nf++;
                    *fp++ = (s32)mantissa_digit + '0';
                    i++;
                } while (i < prec);
            }
            if (format == 'g') {
                for (exp_trim = fp - 1; exp_trim >= fraction && *exp_trim == '0'; exp_trim--) {
                    *exp_trim = 0;
                    nf--;
                }
            }
        }
        exp_negative = e < 0;
        if (e < 0) e = -e;
        while (e > 0) {
            *--ep = e % 10 + '0';
            ne++;
            e /= 10;
        }
        while (ne < 2) {
            *--ep = '0';
            ne++;
        }
        *--ep = exp_negative ? '-' : '+';
        *--ep = 'e';
        ne += 2;
        *--ip = (s32)mantissa + '0';
        ni++;
    }
    point = 0;
    if (format != 'g' || nf > 0) point = 1;
    padding = width - (negative + ni + point + nf + ne);
    if (padding < 0) padding = 0;
    out = buf;
    for (k = 0; k < padding; k++) *out++ = ' ';
    if (negative) *out++ = '-';
    for (k = 0; k < ni; k++) *out++ = *ip++;
    if (point) {
        *out++ = '.';
        fp = fraction;
        for (k = 0; k < nf; k++) *out++ = *fp++;
    }
    for (k = 0; k < ne; k++) *out++ = *ep++;
    *out = 0;
    return out - buf;
}
