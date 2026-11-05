#ifndef COMMON_MENUSELECTIONMESSAGE_H
#define COMMON_MENUSELECTIONMESSAGE_H
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"

/* The selection-message screen g_resultsModelPreviewScreen: its menu rules block, then its item and reply state. */
struct SelectionMessageScreen;

struct SoundOptionsScreen;
struct SoundOptionsScreen {
    void *menu;
    char pad4[0x8 - 0x4];
    void *music;
    void *effects;
    char pad10[0x14 - 0x10];
    s32 target;
};




struct ActorDefinitionHeader;


#endif
