#ifndef FRONTEND_PLAYMODEMENU_STATE_H
#define FRONTEND_PLAYMODEMENU_STATE_H
#include "Frontend/frontend.h"
#include "types.h"
struct PlayModeMenuState;
struct MenuFrontendUpdatePlayModeMenu;
struct MenuWidget;

/* The 28-byte play-mode menu screen record Frontend_InitPlayModeMenu allocates: the menu music slider, the
 * prompt and title widgets, the opening countdown (set to the controller mode), the scroll countdown, and the
 * screen Frontend_ApplyModeChoice goes to. */
typedef struct PlayModeMenuState {
    struct MenuFrontendUpdatePlayModeMenu *music;
    void *prompt;
    struct MenuWidget *title;
    s32 opening;
    s32 reserved10;
    s32 scrollDelay;
    s32 nextScreen;
} PlayModeMenuState;

extern struct PlayModeMenuState *g_playModeMenuState;
#endif
