#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "TYPES.H"

struct StateMenuConfirmGermanExtraOptions;
struct StateMenuConfirmGermanExtraOptions {
    void *first;
    char pad4[0x34 - 4];
    s32 ready;
};
#endif
