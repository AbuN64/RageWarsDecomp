#ifndef MENU_H
#define MENU_H
#include "TYPES.H"
#include "COMMON/CALLBACK.H"

struct MenuDrawEventArgs {
    s32 word0;
    s32 word4;
    s32 word8;
    f32 wordC;
    f32 word10;
    u8 byte14;
    u8 pad15[3];
    s32 word18;
    s32 word1C;
    s32 word20;
    s32 word24;
};
extern s32 Menu_RouteElementEvent(s32 value, s32 event, s32 source, s32 active, s32 amount);

extern void Menu_GetScreenDrawOrigin(s32 *leftOut, s32 *topOut);

extern u8*g_settingsPagePrimaryLocalizedLabels[1];
extern u8*g_settingsPageSecondaryLocalizedLabels;
#endif
