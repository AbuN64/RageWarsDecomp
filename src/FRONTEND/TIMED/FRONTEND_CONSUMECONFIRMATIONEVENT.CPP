#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "TYPES.H"

/* 8042E080_84.CPP */
/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Frontend_ReturnConfirmationEventZero(void) {
    return 0;
}

/* 8042E080_85.CPP */
/* Calls MarkMenuEventHandled with the arguments it was given and returns zero. */
extern void MarkMenuEventHandled();

s32 Frontend_ConsumeConfirmationEvent(void) {
    MarkMenuEventHandled();
    return 0;
}
