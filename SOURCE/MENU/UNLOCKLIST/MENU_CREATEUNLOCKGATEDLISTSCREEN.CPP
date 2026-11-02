#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"


#if defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU_X) || defined(VERSION_EU) || defined(VERSION_DE)
typedef struct Shared_MenuWidgetState { s32 list; s32 resourceWidget; void *item; s32 scrollDelay; s32 nextScreen; s32 seen; } Shared_MenuWidgetState;
extern Shared_MenuWidgetState *g_unlockGatedListScreen;
extern char g_profileModeOnePlayedLevels[];

extern s32 SmpFade_CreateFadeWidget(s32, s32);
extern s32 Defs_TestBit(void *bitArray, s32 index);
extern void Widget_SetWidgetFlag100(MenuWidget *record, int enable);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);

/* Resource ids of this screen are numbered per version (relative to us): eu-x 4, de -2. */
static inline s32 unlockRes(s32 id) {
#if defined(VERSION_EU_X)
    return id + 4;
#elif defined(VERSION_DE)
    return id - 2;
#else
    return id;
#endif
}

s32 Menu_CreateUnlockGatedListScreen(void *window) {
    void *obj;

    g_unlockGatedListScreen = (Shared_MenuWidgetState *)Cache_AllocateMemory(24);
    g_unlockGatedListScreen->list = SmpFade_CreateFadeWidget(unlockRes(310), unlockRes(311));
    g_unlockGatedListScreen->seen = 0;

    if (Defs_TestBit(g_profileModeOnePlayedLevels, 0) == 0) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(window, unlockRes(314)), 1);
    }

    g_unlockGatedListScreen->resourceWidget = SmpFlicker_CreateFlickerWidget(unlockRes(313), 110);

    obj = Node_FindWidgetByResourceId(window, unlockRes(312));
    g_unlockGatedListScreen->item = obj;
    ((ListScreenItem *)obj)->alpha = 15;

    g_unlockGatedListScreen->scrollDelay = 3;
    g_unlockGatedListScreen->nextScreen = -1;
    return 0;
}
#endif
