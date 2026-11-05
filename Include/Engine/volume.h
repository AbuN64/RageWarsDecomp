#ifndef ENGINE_VOLUME_H
#define ENGINE_VOLUME_H
extern int g_modelEditorApplyToAllRecords;
#include "Common/Lone/g_languageindex.h"
#include "Data/Overlays/Credits/objectdata_addresses.h"
#include "Common/pak_enter_player_options.h"
#include "Common/shared_gameslot.h"
#include "Menu/optioneditstate.h"
#include "Multi/setup_setupnamespinner.h"
struct Field;
struct MenuStyle;

struct MusicPreviewOwnerView {
    char pad[0x5D0];
    s32 value;
};


struct PlayerOptionsEntry;
extern s32 Pak_FormatSoundEffectsVolume(struct Field *field);

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#else
#endif

extern s32 Pak_ReturnCallbackSuccess(void);

extern s32 Pak_ResumeMenuAudio(void);

extern void Pak_EnterPlayerOptions(struct PlayerOptionsEntry *player);

extern void Pak_RestoreControllerSetup(void);

extern void Pak_RenderMenuEntryCallback(struct MenuStyle *menu, s8 *member);
extern char g_modelEditorApplyToAllDisabledText[];
extern char g_modelEditorApplyToAllEnabledText[];
extern char g_musicPreviewValueFormat_eu[];
extern char s_menuByteOptionValueFormat[];
extern u8 g_playerModelLighting[];
extern u8 g_savedPlayerModelLighting[];
extern u8 g_savedSecondaryMenuByteOptions[];
extern u8 g_secondaryMenuByteOptions[];
#endif
