#include "types.h"
#include "include_asm.h"
#include "Common/texture.h"
#include "Menu/gnu_va_arg.h"
#include "Common/resident_event_handler.h"
#include "Common/messagesemaphore.h"
#include "Common/gfx_initializefrontendservices.h"
#include "Menu/Gfx/gfx_formatfloatingpoint.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Ui/X_files/x_plus.h"
#include "Data/rest_source_records.h"
#include "Menu/Gfx/Printf/gfxdata_symbols.h"
#include "Common/rotation_extraction.h"
#include "Common/triple.h"
#include "Math/xmath_evaluateexponentialdouble.h"

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
const double g_gfx_FormatFloatingPointConstantWords[28] = {
    0.0, 1000000.0, 10.0, 1.0, 0.1, 1.0, 0.5, 0.0, 9.999999747378752e-05, 1.0, 10.0, 0.0, 2147483647.0, 0.5,
    0.1, 0.05000000074505805, 10.0, 10.0, 0.10000000149011612, 0.0, 1.0, 10.0, 0.1, 0.5, 1.0, 10.0, 0.1, 10.0,
};
#endif

#if !(defined(VERSION_US_REV1))
extern const char g_printfLowercaseHexDigits[17];
#endif

#if defined(VERSION_US_REV1)
extern const char g_printfLowercaseHexDigits[17];
#endif

#if defined(VERSION_DE)
unsigned int k_PrintfEncodedWords[2] = {
    0x00000000, 0x00000000,
};
#endif
#if !(defined(VERSION_DE))
const unsigned int k_PrintfEncodedWords[2] = {
    0x00000000, 0x00000000,
};
#endif

static inline void put_gfxFormatargumentlist(u8 **pp, const u8 *p, s32 len) {
    s32 i;
    for (i = 0; i < len; i++) {
        **pp = p[i];
        (*pp)++;
    }
}

static inline void pad_gfxFormatargumentlist(u8 **pp, s32 howmany, const u8 *with) {
    s32 n;

    if (howmany > 0) {
        n = howmany;
        while (n > 16) {
            put_gfxFormatargumentlist(pp, with, 16);
            n -= 16;
        }
        put_gfxFormatargumentlist(pp, with, n);
    }
}

static inline s32 fetch_gfxFormatargumentlist(u8 **app) {
    return VA(*app, s32);
}

static inline u8 *ultoa_gfxFormatargumentlist(u32 val, u8 *endp, s32 base, s32 octzero, const u8 *xdigs) {
    u8 *cp = endp;
    s32 sval;

    switch (base) {
    case 10:
        if (val < 10) {
            *--cp = val + '0';
            return cp;
        }
        if ((s32)val < 0) {
            *--cp = val % 10 + '0';
            sval = val / 10;
        } else {
            sval = val;
        }
        do {
            *--cp = sval % 10 + '0';
            sval /= 10;
        } while (sval != 0);
        break;
    case 8:
        do {
            *--cp = (val & 7) + '0';
            val >>= 3;
        } while (val);
        if (octzero && *cp != '0') {
            *--cp = '0';
        }
        break;
    case 16:
        do {
            *--cp = xdigs[val & 15];
            val >>= 4;
        } while (val);
        break;
    default:
        return 0;
    }
    return cp;
}

s32 Gfx_FormatArgumentList(u8 *out, u8 *fmt0, u8 *ap) {
    u8 *fmt;
    u8 ch;
    s32 n;
    s32 flags;
    s32 width;
    s32 prec;
    s32 dprec;
    s32 realsz;
    s32 size;
    s32 ret;
    s32 base;
    u32 ulval;
    u32 uqval;
    const u8 *xdigs;
    u8 *cp;
    u8 sign;
    u8 buf[128];
    u8 ox[2];

    ulval = 0;
    uqval = 0;
    xdigs = 0;
    fmt = fmt0;
    ret = 0;
    for (;;) {
next_format:
        for (cp = fmt; (ch = *fmt) != 0 && ch != '%'; fmt++) {
        }
        if ((n = fmt - cp) != 0) {
            put_gfxFormatargumentlist(&out, cp, n);
            ret += n;
        }
        fmt++;
        if (ch == 0) {
            break;
        }
        flags = 0;
        dprec = 0;
        width = 0;
        prec = -1;
        sign = 0;
        /* Flags, width, precision and length modifiers loop here until a conversion character ends the spec. */
        for (;;) {
        ch = *fmt++;
reswitch:
        switch (ch) {
        case ' ':
            if (!sign) {
                sign = ' ';
            }
            continue;
        case '#':
            flags |= 0x10;
            continue;
        case '*':
            width = VA(ap, int);
            if (width >= 0) {
                continue;
            }
            width = -width;
        case '-':
            flags |= 0x40;
            continue;
        case '+':
            sign = '+';
            continue;
        case '.':
            if ((ch = *fmt++) == '*') {
                prec = VA(ap, int);
                if (prec < 0) {
                    prec = -1;
                }
                continue;
            }
            n = 0;
            while ((u32)(ch - '0') < 10) {
                n = 10 * n + (ch - '0');
                ch = *fmt++;
            }
            prec = n < 0 ? -1 : n;
            goto reswitch;
        case '0':
            flags |= 0x80;
            continue;
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
            n = 0;
            do {
                n = 10 * n + (ch - '0');
                ch = *fmt++;
            } while ((u32)(ch - '0') < 10);
            width = n;
            goto reswitch;
        case 'L':
            flags |= 1;
            continue;
        case 'h':
            flags |= 8;
            continue;
        case 'l':
            flags |= 2;
            continue;
        case 'q':
            flags |= 4;
            continue;
        case 'c':
            *(cp = buf) = VA(ap, int);
            size = 1;
            sign = 0;
            break;
        case 'D':
            flags |= 2;
        case 'd':
        case 'i':
            /* Single-pass loops preserve the original GCC allocation weights. */
            {
                if (flags & 4) {
                    uqval = VA(ap, int);
                    if ((s32)uqval < 0) {
                        uqval = -uqval;
                        sign = '-';
                    }
                } else {
                    {
                        u8 **q = &ap;
                        switch (flags & 0xF) {
                    case 1: case 2:
                        ulval = VA(ap, long);
                        break;
                    case 8:
                        ulval = (short)VA(ap, int);
                        break;
                    default:
                        /* This loop has no visible effect; it is kept so the compiler hoists the
                           va_arg alignment mask the same way as in the original build. */
                        do { ulval = VA(*q, s32); } while (0);
                        break;
                        }
                    }
                    if ((s32)ulval < 0) {
                        ulval = -ulval;
                        sign = '-';
                    }
                }
                base = 10;
                goto signed_number;
            }
        case 'g':
        case 'G':
            if (prec == 0) {
                prec = 1;
            }
        case 'e':
        case 'E':
        case 'f': {
            f64 dval;
            if (sign == '+') {
                put_gfxFormatargumentlist(&out, &sign, 1);
                width--;
                ret++;
            }
            if (prec == -1) {
                prec = 6;
            }
            {
                u8 *aq = (u8 *)((((s32)ap + 7) & -8) + 8);
                dval = *(f64 *)(aq - 8);
                ap = aq;
            }
            if (flags & 0x40) {
                width = -width;
            }
            size = Gfx_FormatFloatingPoint(buf, dval, ch, width, prec);
            n = 0;
            if (flags & 0x80) {
                while (buf[n] == ' ') {
                    buf[n] = '0';
                    n++;
                }
            }
            put_gfxFormatargumentlist(&out, buf, size);
            if (flags & 0x40) {
                pad_gfxFormatargumentlist(&out, -width - size, g_formatSpacePadding);
            }
            ret += width > size ? width : size;
            goto next_format;
        }
        case 'n':
            if (flags & 4) {
                *VA(ap, int *) = ret;
            } else if (flags & 2) {
                *VA(ap, long *) = ret;
            } else if (flags & 8) {
                *VA(ap, short *) = ret;
            } else {
                *VA(ap, int *) = ret;
            }
            goto next_format;
        case 'o':
            if (flags & 4) {
                uqval = VA(ap, int);
            } else {
                {
                    u8 **q = &ap;
                    switch (flags & 0xF) {
                case 1: case 2:
                    ulval = VA(ap, long);
                    break;
                case 8:
                    ulval = (unsigned short)VA(ap, int);
                    break;
                default:
                    ulval = VA(*q, s32);
                    break;
                    }
                }
            }
            base = 8;
            goto unsigned_number;
        case 'p':
            base = 16;
            xdigs = g_printfLowercaseHexDigits;
            flags &= ~4;
            ulval = (u32)VA(ap, void *);
            ch = 'x';
            if (prec < 0) {
                prec = 8;
            }
            goto unsigned_number;
        case 's':
            cp = VA(ap, u8 *);
            if (prec >= 0) {
                u8 *p = XPlus_FindByte(cp, 0, prec);
                if (p != 0) {
                    size = p - cp;
                    if (size > prec) {
                        size = prec;
                    }
                } else {
                    size = prec;
                }
            } else {
                size = XPlus_StringLength(cp);
            }
            sign = 0;
            break;
        case 'U':
            flags |= 2;
        case 'u':
            if (flags & 4) {
                uqval = VA(ap, int);
            } else {
                {
                    u8 **q = &ap;
                    switch (flags & 0xF) {
                case 1: case 2:
                    ulval = VA(ap, long);
                    break;
                case 8:
                    ulval = (unsigned short)VA(ap, int);
                    break;
                default:
                    ulval = VA(*q, s32);
                    break;
                    }
                }
            }
            base = 10;
            goto unsigned_number;
        case 'X':
        case 'x':
            xdigs = ch == 'X' ? g_formatUppercaseHexDigits : g_printfLowercaseHexDigits;
            if (flags & 4) {
                uqval = VA(ap, int);
            } else {
                {
                    u8 **q = &ap;
                    switch (flags & 0xF) {
                case 1: case 2:
                    ulval = VA(ap, long);
                    break;
                case 8:
                    ulval = (unsigned short)VA(ap, int);
                    break;
                default:
                    ulval = VA(*q, s32);
                    break;
                    }
                }
            }
            base = 16;
            if (flags & 0x10) {
                if (flags & 4 ? uqval != 0 : ulval != 0) {
                    flags |= 0x20;
                }
            }
            goto unsigned_number;
        default:
            if (ch == 0) {
                goto done;
            }
            *(cp = buf) = ch;
            size = 1;
            sign = 0;
            break;
        }
        break;
        }
        goto field;
unsigned_number:
    sign = 0;
signed_number:
        if ((dprec = prec) >= 0) {
            flags &= ~0x80;
        }
        cp = buf + 128;
        if (flags & 4) {
            if (uqval != 0 || prec != 0) {
                cp = ultoa_gfxFormatargumentlist(uqval, cp, base, flags & 0x10, xdigs);
            }
        } else {
            if (ulval != 0 || prec != 0) {
                cp = ultoa_gfxFormatargumentlist(ulval, cp, base, flags & 0x10, xdigs);
            }
        }
        size = buf + 128 - cp;
field:
        realsz = dprec > size ? dprec : size;
        if (sign) {
            realsz++;
        } else if (flags & 0x20) {
            realsz += 2;
        }
        if ((flags & 0xC0) == 0) {
            pad_gfxFormatargumentlist(&out, width - realsz, g_formatSpacePadding);
        }
        if (sign) {
            put_gfxFormatargumentlist(&out, &sign, 1);
        } else if (flags & 0x20) {
            ox[0] = '0';
            ox[1] = ch;
            put_gfxFormatargumentlist(&out, ox, 2);
        }
        if ((flags & 0xC0) == 0x80) {
            pad_gfxFormatargumentlist(&out, width - realsz, g_formatZeroPadding);
        }
        pad_gfxFormatargumentlist(&out, dprec - size, g_formatZeroPadding);
        put_gfxFormatargumentlist(&out, cp, size);
        if (flags & 0x40) {
            pad_gfxFormatargumentlist(&out, width - realsz, g_formatSpacePadding);
        }
        ret += width > realsz ? width : realsz;
    }
done:
    put_gfxFormatargumentlist(&out, g_formatPercentText, 1);
    return ret;
}

#if defined(VERSION_EU_X)
void *const k_gfxdataFragment[1] = {
    (void *)(addrLow_Initial_ToggleMenuRowOption + 208),
};
#endif
typedef struct HuffmanNode {
    unsigned short left;
    short right;
} HuffmanNode;

#if defined(VERSION_US_REV1)

#endif

#if defined(VERSION_US)
const double g_gfx_FormatFloatingPointConstantWords[28] = {
    0.0, 1000000.0, 10.0, 1.0, 0.1, 1.0, 0.5, 0.0, 9.999999747378752e-05, 1.0, 10.0, 0.0, 2147483647.0, 0.5,
    0.1, 0.05000000074505805, 10.0, 10.0, 0.10000000149011612, 0.0, 1.0, 10.0, 0.1, 0.5, 1.0, 10.0, 0.1, 10.0,
};
#endif

s32 Gfx_FormatFloatingPoint(u8 *buf, f64 input, s32 ch, s32 width, s32 precision) {
    u8 fraction[128];
    u8 integer[128];
    u8 exponent[16];
    f64 value;
    f64 whole, digit, mantissa, mantissaDigit;
    u8 format = ch;
    s32 prec;
    s32 negative;
    u8 *fp = fraction;
    u8 *ip = &integer[127];
    u8 *ep = &exponent[15];
    u8 *iend = ip;
    s32 nf, ni, ne;
    s32 fixed;
    s32 powN, maxdigits, k;
    s32 i, n, e, carry, trim, padding, point;
    u8 *p, *q, *out;
    u8 *integerCarry;
    u8 *fpTrim, *expTrim;
    u8 c, expNegative;
    f64 scale, round, base, power, frac, sciFrac;
    f64 fixedTen, fixedBase, fixedLimit;
    f64 normTen, sciTen, sciBase, sciBias, sciLimit;

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
        powN = prec;
        if (powN == 0) {
            scale = g_formatZeroPrecisionScale;
        } else {
            if (powN < 0) {
                powN = -powN;
                base = g_formatNegativePrecisionBase;
            }
            power = g_formatPrecisionPowerIdentity;
            for (;;) {
                if (powN & 1) power *= base;
                powN >>= 1;
                if (!powN) break;
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
                fixedTen = g_formatFractionDecimalBase;
                do {
                    frac = XMath_SplitDoubleFraction(frac * fixedTen, &digit);
                    nf++;
                    *fp++ = (s32)digit + '0';
                    i++;
                } while (i < prec);
            }
            if (format == 'g') {
                for (fpTrim = fp - 1; fpTrim >= fraction && *fpTrim == '0'; fpTrim--) {
                    *fpTrim = 0;
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
                fixedLimit = g_formatLargeIntegerLimit;
                fixedBase = g_formatLargeIntegerReciprocalBase;
                round = g_formatLargeIntegerRoundingBias;
                fixedTen = g_formatLargeIntegerDecimalBase;
                do {
                    *--ip = (s32)((XMath_SplitDoubleFraction(whole * fixedBase, &whole) + round) * fixedTen) + '0';
                    ni++;
                } while (whole > fixedLimit);
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
                            for (integerCarry = iend - 1; integerCarry >= ip && carry; integerCarry--) {
                                c = ++*integerCarry;
                                if ((c & 0xff) >= ':') *integerCarry = '0';
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
        normTen = g_formatNormalizationDecimalBase;
        if (value >= normTen) {
        sciBase = g_formatScientificReciprocalBase;
        do {
            value *= sciBase;
            e++;
        } while (value >= normTen);
        }
        sciLimit = g_formatScientificDigitLimit;
        sciBias = g_formatScientificRoundingBase - round;
        while (value > sciLimit) {
            if (value < sciBias) {
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
            sciFrac = value;
            i = 0;
            if (i < prec) {
                scale = g_formatScientificFractionDecimalBase;
                do {
                    sciFrac = XMath_SplitDoubleFraction(sciFrac * scale, &mantissaDigit);
                    nf++;
                    *fp++ = (s32)mantissaDigit + '0';
                    i++;
                } while (i < prec);
            }
            if (format == 'g') {
                for (expTrim = fp - 1; expTrim >= fraction && *expTrim == '0'; expTrim--) {
                    *expTrim = 0;
                    nf--;
                }
            }
        }
        expNegative = e < 0;
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
        *--ep = expNegative ? '-' : '+';
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

/* Retained data for this translation unit. */
#if defined(VERSION_US_REV1)
const double g_formatFloatingPointDoubleConstants[28] = {
    0.0, 1000000.0, 10.0, 1.0, 0.1, 1.0, 0.5, 0.0, 9.999999747378752e-05, 1.0, 10.0, 0.0, 2147483647.0, 0.5,
    0.1, 0.05000000074505805, 10.0, 10.0, 0.10000000149011612, 0.0, 1.0, 10.0, 0.1, 0.5, 1.0, 10.0, 0.1, 10.0,
};
#endif
#if !(defined(VERSION_US_REV1))
const char g_printfLowercaseHexDigits[17] =
    "0123456789abcdef\000";
#endif
#if defined(VERSION_US_REV1)
const char g_printfLowercaseHexDigits[17] =
    "0123456789abcdef";
#endif
