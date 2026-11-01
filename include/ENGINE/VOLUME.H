#ifndef ENGINE_VOLUME_H
#define ENGINE_VOLUME_H
#include "COMMON/MENURECAT20V1.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "MENU/OPTIONEDITSTATE.H"
#include "MULTI/SETUP_SETUPNAMESPINNER.H"

extern s32 Pak_FormatVolumeSlotOne(struct Field *field);

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_volumeOneValueLabel[];
#else
extern char *g_volumeOneValueLabel[];
#endif

extern s32 Pak_ReturnCallbackSuccess(void);

extern s32 Pak_ResumeMenuAudio(void);

extern void Pak_EnterPlayerOptions(PlayerOptionsEntry *player);

extern void Pak_RestoreControllerSetup(void);

extern void Pak_RenderMenuEntryCallback(struct MenuStyle *menu, s8 *member);
#endif
