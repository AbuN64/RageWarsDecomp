#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#if defined(VERSION_DE)
/* 800DE794.CPP */
char g_itemsConstantWords[12] =
    "d\000\000\000 %3d\000\000\000";
#endif
#if defined(VERSION_EU)
/* Picks the label for each of the eight option rows (ids 2..9): the first text when the row's flag is set, else the second. */
typedef struct { s32 id; u8 pad4[0x10]; char ***text; } OptionRowEu;
#endif
#if defined(VERSION_EU_X)
#include "TYPES.H"
#endif
