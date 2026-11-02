#include "MENU/STATE.H"
#include "TYPES.H"

#if defined(VERSION_DE)
/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Frontend_ReturnGermanOptionsEventZeroA(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Frontend_ReturnGermanOptionsEventZeroB(void) {
    return 0;
}
#endif
