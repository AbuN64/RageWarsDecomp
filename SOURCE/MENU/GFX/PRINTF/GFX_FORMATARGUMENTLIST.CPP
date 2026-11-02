#include "COMMON/TEXTURE.H"
#include "MENU/GNU_VA_ARG.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/MESSAGESEMAPHORE.H"
#include "TYPES.H"
#include "COMMON/GFX_INITIALIZEFRONTENDSERVICES.H"
#include "MENU/GFX/GFX_FORMATFLOATINGPOINT.H"
#include "RESMGR/resmgr_string_memory.H"

extern s32 XPlus_StringLength(u8 *string);

static inline void put(u8 **pp, const u8 *p, s32 len) {
    s32 i;
    for (i = 0; i < len; i++) {
        **pp = p[i];
        (*pp)++;
    }
}

static inline void pad(u8 **pp, s32 howmany, const u8 *with) {
    s32 n;

    if (howmany > 0) {
        n = howmany;
        while (n > 16) {
            put(pp, with, 16);
            n -= 16;
        }
        put(pp, with, n);
    }
}

static inline s32 fetch(u8 **app) {
    return VA(*app, s32);
}

static inline u8 *ultoa(u32 val, u8 *endp, s32 base, s32 octzero, const u8 *xdigs) {
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
        for (cp = fmt; (ch = *fmt) != 0 && ch != '%'; fmt++) {
        }
        if ((n = fmt - cp) != 0) {
            put(&out, cp, n);
            ret += n;
        }
        fmt++;
        if (ch == 0) {
            goto done;
        }
        flags = 0;
        dprec = 0;
        width = 0;
        prec = -1;
        sign = 0;
rflag:
        ch = *fmt++;
reswitch:
        switch (ch) {
        case ' ':
            if (!sign) {
                sign = ' ';
            }
            goto rflag;
        case '#':
            flags |= 0x10;
            goto rflag;
        case '*':
            width = VA(ap, int);
            if (width >= 0) {
                goto rflag;
            }
            width = -width;
        case '-':
            flags |= 0x40;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            if ((ch = *fmt++) == '*') {
                prec = VA(ap, int);
                if (prec < 0) {
                    prec = -1;
                }
                goto rflag;
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
            goto rflag;
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
            goto rflag;
        case 'h':
            flags |= 8;
            goto rflag;
        case 'l':
            flags |= 2;
            goto rflag;
        case 'q':
            flags |= 4;
            goto rflag;
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
            do {
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
                    case 1: case 2: case 4:
                        ulval = VA(ap, long);
                        break;
                    case 8:
                        ulval = (short)VA(ap, int);
                        break;
                    default:
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
                goto number;
            } while (0);
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
                put(&out, &sign, 1);
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
            put(&out, buf, size);
            if (flags & 0x40) {
                pad(&out, -width - size, g_formatSpacePadding);
            }
            ret += width > size ? width : size;
            continue;
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
            continue;
        case 'o':
            if (flags & 4) {
                uqval = VA(ap, int);
            } else {
                {
                    u8 **q = &ap;
                    switch (flags & 0xF) {
                case 1: case 2: case 4:
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
            goto nosign;
        case 'p':
            base = 16;
            xdigs = g_printfLowercaseHexDigits;
            flags &= ~4;
            ulval = (u32)VA(ap, void *);
            ch = 'x';
            if (prec < 0) {
                prec = 8;
            }
            goto nosign;
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
                case 1: case 2: case 4:
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
            goto nosign;
        case 'X':
            xdigs = g_formatUppercaseHexDigits;
            goto hex;
        case 'x':
            xdigs = g_printfLowercaseHexDigits;
hex:
            if (flags & 4) {
                uqval = VA(ap, int);
            } else {
                {
                    u8 **q = &ap;
                    switch (flags & 0xF) {
                case 1: case 2: case 4:
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
nosign:
            sign = 0;
number:
            if ((dprec = prec) >= 0) {
                flags &= ~0x80;
            }
            cp = buf + 128;
            if (flags & 4) {
                if (uqval != 0 || prec != 0) {
                    cp = ultoa(uqval, cp, base, flags & 0x10, xdigs);
                }
            } else {
                if (ulval != 0 || prec != 0) {
                    cp = ultoa(ulval, cp, base, flags & 0x10, xdigs);
                }
            }
            size = buf + 128 - cp;
            break;
        default:
            if (ch == 0) {
                goto done;
            }
            *(cp = buf) = ch;
            size = 1;
            sign = 0;
            break;
        }

        realsz = dprec > size ? dprec : size;
        if (sign) {
            realsz++;
        } else if (flags & 0x20) {
            realsz += 2;
        }
        if ((flags & 0xC0) == 0) {
            pad(&out, width - realsz, g_formatSpacePadding);
        }
        if (sign) {
            put(&out, &sign, 1);
        } else if (flags & 0x20) {
            ox[0] = '0';
            ox[1] = ch;
            put(&out, ox, 2);
        }
        if ((flags & 0xC0) == 0x80) {
            pad(&out, width - realsz, g_formatZeroPadding);
        }
        pad(&out, dprec - size, g_formatZeroPadding);
        put(&out, cp, size);
        if (flags & 0x40) {
            pad(&out, width - realsz, g_formatSpacePadding);
        }
        ret += width > realsz ? width : realsz;
    }
done:
    put(&out, g_formatPercentText, 1);
    return ret;
}
