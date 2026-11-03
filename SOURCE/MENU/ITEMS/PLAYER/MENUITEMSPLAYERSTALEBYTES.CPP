#include "include_asm.h"

#if defined(VERSION_US)
/* Stale bytes 00000010 000B0000; no instruction reads it. */
unsigned char g_menuItemsPlayerStaleBytes[8] = { 0x00, 0x00, 0x00, 0x10, 0x00, 0x0B, 0x00, 0x00 };
#endif

