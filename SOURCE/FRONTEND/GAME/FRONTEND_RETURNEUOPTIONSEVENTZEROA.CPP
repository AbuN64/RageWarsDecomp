#include "COMMON/FRONTEND_RESOURCE_LOAD_STATE.H"
#include "TYPES.H"

#if defined(VERSION_EU)
s32 Frontend_ReturnEuOptionsEventZeroA(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Frontend_ReturnEuOptionsEventZeroB(void) {
    return 0;
}
#endif
