#ifndef COMMON_MENUSELECTIONMESSAGE_H
#define COMMON_MENUSELECTIONMESSAGE_H
#include "TYPES.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/ITEMRECAT20V1.H"

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
