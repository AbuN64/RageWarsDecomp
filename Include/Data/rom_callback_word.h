#ifndef DATA_ROM_CALLBACK_WORD_H
#define DATA_ROM_CALLBACK_WORD_H
#include "types.h"

/* Stored 32-bit callback/state word, including null (zero). Callback words
 * are virtual addresses, called unchanged: Vhandler_MapBootstrapAddressRange
 * maps 0x00200000 through the TLB. They are not handler indices or offsets
 * to which a caller adds 0x80000000. Data links retain their full address. */
typedef struct RomCallbackWord {
    u32 address;
} RomCallbackWord;
typedef char RomCallbackWordSizeCheck[(sizeof(RomCallbackWord) == 4) ? 1 : -1];
#endif
