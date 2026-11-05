#ifndef MENU_SOUND_MENU_DISPATCHSOUNDSLIDEREVENT_SYMBOLS_H
#define MENU_SOUND_MENU_DISPATCHSOUNDSLIDEREVENT_SYMBOLS_H
#include "types.h"
typedef s32 (*SoundSliderEventHandler)(void *, s32, s32, s32, s32);
extern SoundSliderEventHandler g_soundSliderEventHandlers;
#endif
