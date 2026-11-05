#include "../../../include/LIBC.H"
#include "include_asm.h"
#include "../../../include/EXTERNS.H"
#include "Common/runtime_declarations.h"
#include "Common/lldivresult.h"
#include <stdarg.h>
#include "types.h"
#include "../../../include/PRINTF/_LDTOB.H"
#include "Common/audio_callbacks.h"
#include "Common/resident_event_handler.h"
#include <platform_sdk.h>
#include "stdarg.h"
#include "Libc/libc_formatinteger_data.h"

/* 800C7C68.CPP */
#if defined(VERSION_DE)
unsigned int g_xprintfDecimalPowerDoubles[22] = {
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

/* EU enters __umoddi3 one word before its symbol (__umoddi3_Xprintf), so EU keeps the ROM body. */


extern u8 g_printfDigitCharacters[];
