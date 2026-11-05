#ifndef MENU_SOUND_MENU_APPLYSOUNDSLIDERS_SYMBOLS_H
#define MENU_SOUND_MENU_APPLYSOUNDSLIDERS_SYMBOLS_H
#include "types.h"
extern void **g_soundOptionSliders;
typedef s32 (*SoundOptionsEventHandler)(void *, s32, s32, s32, s32);
extern SoundOptionsEventHandler g_soundOptionsEventHandlers;
extern unsigned char g_soundEffectsVolumeOption[];
extern unsigned char g_gameSettingsVolumeBytes[];
#endif
