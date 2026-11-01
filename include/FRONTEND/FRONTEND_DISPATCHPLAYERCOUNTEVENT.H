#ifndef FRONTEND_FRONTEND_DISPATCHPLAYERCOUNTEVENT_H
#define FRONTEND_FRONTEND_DISPATCHPLAYERCOUNTEVENT_H
#include "COMMON/SETTINGSRECAT24.H"
/* The one object g_playerCountScreen points to; the settings screens each read their own fields of it. */
typedef struct SettingsScreenState {
    struct StateFrontendUpdatePlayerCountScreen head; /* 0x0: menu, list, delay, target */
    char text[12]; /* 0x14 */
    s32 count; /* 0x20, also the counter value */
} SettingsScreenState;
extern s32 Frontend_DispatchPlayerCountEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
#endif
