#include "../../include/LIBC.H"
#include "include_asm.h"
#include "../../include/EXTERNS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/LLDIVRESULT.H"
#include <stdarg.h>
#include "TYPES.H"
#include "../../include/PRINTF/_LDTOB.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include <ultra64.h>
#include "stdarg.h"

/* 800C7C68.CPP */
#if defined(VERSION_DE)
unsigned int g_XprintfWords1[22] = {
    0x40590000, 0x00000000, 0x40240000, 0x00000000, 0x40590000, 0x00000000, 0x40C38800, 0x00000000,
    0x4197D784, 0x00000000, 0x4341C379, 0x37E08000, 0x4693B8B5, 0xB5056E17, 0x4D384F03, 0xE93FF9F5,
    0x5A827748, 0xF9301D32, 0x75154FDD, 0x7F73BF3C, 0x3B490FDB, 0x3C490FDB,
};
#endif

/* 802C2520.CPP */
/* _Printf core of the SDK: scans the format, parses flags, width, precision and size qualifier, and emits each field through prout. */

extern u8 g_printfFlagCharactersText;
extern u8 g_printfLengthQualifierCharacters;
extern const char g_printfPaddingCharacters[];
extern const char g_libcZeroPaddingText[];

/* va_arg(ap, int) as this SDK expands it: load at the aligned cursor, then advance it. */
#define PRINTF_VA_INT(ap) ({ int _v = *(int *)((((unsigned int)(ap) + 3) & -4)); ap = (va_list)((((unsigned int)(ap) + 3) & -4) + 4); _v; })
#define PRINTF_PUT(s, n) \
    if (0 < (n)) { \
        arg = (*prout)(arg, (const char *)(s), (n)); \
        if (arg != 0) { \
            x.nchar += (n); \
        } else { \
            return x.nchar; \
        } \
    }
#define PRINTF_PAD(m, s, n) \
    if (0 < (n)) { \
        int i, j = (n); \
        for (; 0 < j; j -= i) { \
            i = ((unsigned int)j <= (m)) ? j : (m); \
            PRINTF_PUT(s, i); \
        } \
    }
extern unsigned int g_printfFlagBits[];
s32 _Printf(void *(*prout)(void *, const char *, s32), void *arg, const char *fmt, va_list ap) {
    _Pft x;
    x.nchar = 0;
    for (;;) {
        const unsigned char *s = (const unsigned char *)fmt;
        unsigned char c;
        int n;
        unsigned char *t;
        unsigned char *fchar;
        unsigned int *fbit;
        unsigned char ac[32];
        while ((c = *s) != 0 && c != 0x25) ++s;
        n = s - (const unsigned char *)fmt;
        PRINTF_PUT(fmt, n);
        if (c == 0) {
            return x.nchar;
        }
        ++s;
        for (x.flags = 0, fchar = &g_printfFlagCharactersText, fbit = g_printfFlagBits; (t = (unsigned char *)Libc_FindStringByte((const char *)fchar, *s)) != 0; ++s) {
            x.flags |= fbit[t - fchar];
        }
        if (*s == 0x2A) {
            x.width = PRINTF_VA_INT(ap);
            if (x.width < 0) {
                x.width = -x.width;
                x.flags |= 4;
            }
            ++s;
        } else {
            for (x.width = 0; (*s >= 0x30 && *s <= 0x39); ++s) {
                if (x.width < 999) {
                    x.width = x.width * 10 + *s - 0x30;
                }
            }
        }
        if (*s != 0x2E) {
            x.prec = -1;
        } else if (*++s == 0x2A) {
            x.prec = PRINTF_VA_INT(ap);
            ++s;
        } else {
            for (x.prec = 0; (*s >= 0x30 && *s <= 0x39); ++s) {
                if (x.prec < 999) {
                    x.prec = x.prec * 10 + *s - 0x30;
                }
            }
        }
        x.qual = Libc_FindStringByte((const char *)&g_printfLengthQualifierCharacters, *s) ? *s++ : 0;
        if (x.qual == 0x6C && *s == 0x6C) {
            x.qual = 0x4C;
            ++s;
        }
        _Putfld(&x, &ap, *s, ac);
        x.width -= x.n0 + x.nz0 + x.n1 + x.nz1 + x.n2 + x.nz2;
        if (!(x.flags & 4)) {
            PRINTF_PAD(32, g_printfPaddingCharacters, x.width);
        }
        PRINTF_PUT(ac, x.n0);
        PRINTF_PAD(32, g_libcZeroPaddingText, x.nz0);
        PRINTF_PUT(x.s, x.n1);
        PRINTF_PAD(32, g_libcZeroPaddingText, x.nz1);
        PRINTF_PUT(x.s + x.n1, x.n2);
        PRINTF_PAD(32, g_libcZeroPaddingText, x.nz2);
        if (x.flags & 4) {
            PRINTF_PAD(32, g_printfPaddingCharacters, x.width);
        }
        fmt = (const char *)s + 1;
    }
}



void _Putfld(_Pft *px, va_list *pap, int code, unsigned char *ac)
{
    px->n0 = px->nz0 = px->n1 = px->nz1 = px->n2 =
        px->nz2 = 0;

    /* Standard printf dispatch reconstructed from the conversion arms;
     * original table identity/entry audit remains pending. */
    switch ((unsigned char)code) {
    case 'c': goto case_c;
    case 'd': case 'i': goto case_d;
    case 'o': case 'u': case 'x': case 'X': goto case_x;
    case 'e': case 'E': case 'f': case 'g': case 'G': goto case_e;
    case 'n': goto case_n;
    case 'p': goto case_p;
    case 's': goto case_s;
    case '%': goto case_percent;
    default: goto case_default;
    }

case_c:
    ac[px->n0++] = va_arg(*pap, int);
    return;
case_d:
    if (px->qual == 'l') {
        px->v.ll = va_arg(*pap, long);
    } else if (px->qual == 'L') {
        px->v.ll = va_arg(*pap, long long);
    } else {
        px->v.ll = va_arg(*pap, int);
    }

    if (px->qual == 'h') {
        px->v.ll = (short)px->v.ll;
    }

    if (px->v.ll < 0) {
        ac[px->n0++] = '-';
    } else if (px->flags & 2) {
        ac[px->n0++] = '+';
    } else if (px->flags & 1) {
        ac[px->n0++] = ' ';
    }

    px->s = (unsigned char *)&ac[px->n0];

    _Litob(px, (unsigned char)code);
    return;
case_x:
    if (px->qual == 'l') {
        px->v.ll = va_arg(*pap, long);
    } else if (px->qual == 'L') {
        px->v.ll = va_arg(*pap, long long);
    } else {
        px->v.ll = va_arg(*pap, int);
    }

    if (px->qual == 'h') {
        px->v.ll = (unsigned short)px->v.ll;
    } else if (px->qual == 0) {
        px->v.ll = (unsigned int)px->v.ll;
    }

    if (px->flags & 8) {
        ac[px->n0++] = '0';

        if ((unsigned char)code == 'x' || (unsigned char)code == 'X') {
            ac[px->n0++] = code;
        }
    }

    px->s = (unsigned char *)&ac[px->n0];
    _Litob(px, (unsigned char)code);
    return;
case_e:
    px->v.ld = px->qual == 'L' ? va_arg(*pap, double) : va_arg(*pap, double);

    if ((((unsigned short *)&(px->v.ld))[0] & 0x8000))
        ac[px->n0++] = '-';
    else if (px->flags & 2)
        ac[px->n0++] = '+';
    else if (px->flags & 1)
        ac[px->n0++] = ' ';

    px->s = (unsigned char *)&ac[px->n0];
    _Ldtob(px, (unsigned char)code);
    return;
case_n:
    if (px->qual == 'h') {
        *va_arg(*pap, unsigned short *) = px->nchar;
    } else if (px->qual == 'l') {
        *va_arg(*pap, unsigned long *) = px->nchar;
    } else if (px->qual == 'L') {
        *va_arg(*pap, unsigned long long *) = px->nchar;
    } else {
        *va_arg(*pap, unsigned int *) = px->nchar;
    }
    return;
case_p:
    px->v.ll = (long)va_arg(*pap, void *);
    px->s = (unsigned char *)&ac[px->n0];
    _Litob(px, 'x');
    return;
case_s:
    px->s = va_arg(*pap, unsigned char *);
    px->n1 = Libc_StringLength((const char *)px->s);

    if (px->prec >= 0 && px->prec < px->n1) {
        px->n1 = px->prec;
    }
    return;
case_percent:
    ac[px->n0++] = '%';
    return;
case_default:
    ac[px->n0++] = code;
}

/* EU enters __umoddi3 one word before its symbol (__umoddi3_Xprintf), so EU keeps the ROM body. */

extern u8 g_lowercaseHexDigitsText[];
extern u8 g_printfDigitCharacters[];



static inline void lldivInline(LldivResult *result, s64 numerator, s64 denominator) {
    result->quot = Libc_SignedDivide(numerator, denominator);
    result->rem = Libc_SignedRemainder(numerator, denominator);
}
/* Formats px->v.ll into px->s in the radix selected by code (o/x/X/d/i/u), zero-padding to the precision
 * (libc _Litob). The first digit and quotient use the u64 '%' and '/' operators (__umoddi3/__udivdi3 libcalls). */
void _Litob(_Pft *px, unsigned char code) {
    char buffer[0x18];
    const u8 *table;
     LldivResult qr;
    s32 base;
    s32 i;
    u64 value;
    table = g_lowercaseHexDigitsText;
    if (code == 0x58) {
        table = g_printfDigitCharacters;
    }
    base = (code == 0x6F) ? 8 : ((code != 0x78 && code != 0x58) ? 10 : 16);
    i = 0x18;
    value = px->v.ll;
    if ((code == 0x64 || code == 0x69) && px->v.ll < 0) {
        value = -value;
    }
    if (value != 0 || px->prec != 0) {
        buffer[--i] = table[value % base];
    }
    px->v.ll = value / base;
    while (px->v.ll > 0 && i > 0) {
        lldivInline(&qr, px->v.ll, base);
        px->v.ll = qr.quot;
        buffer[--i] = table[qr.rem];
    }
    px->n1 = 0x18 - i;
    Libc_CopyBytes(px->s, &buffer[i], px->n1);
    if (px->n1 < px->prec) {
        px->nz0 = px->prec - px->n1;
    }
    if (px->prec < 0 && (px->flags & 0x14) == 0x10) {
        i = (px->width - px->n0) - px->nz0 - px->n1;
        if (i > 0) {
            px->nz0 = px->nz0 + i;
        }
    }
}
