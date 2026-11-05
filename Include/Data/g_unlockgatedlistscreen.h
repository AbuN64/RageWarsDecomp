#ifndef DATA_G_UNLOCKGATEDLISTSCREEN_H
#define DATA_G_UNLOCKGATEDLISTSCREEN_H
#include "types.h"
/* The 24-byte unlock-gated list screen record Menu_CreateUnlockGatedListScreen allocates. */
typedef struct Shared_MenuWidgetState {
    s32 list;
    s32 resourceWidget;
    void *item;
    s32 scrollDelay;
    s32 nextScreen;
    s32 seen;
} Shared_MenuWidgetState;

extern Shared_MenuWidgetState *g_unlockGatedListScreen;
#endif
