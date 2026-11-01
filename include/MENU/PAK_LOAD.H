#ifndef MENU_PAK_LOAD_H
#define MENU_PAK_LOAD_H
#include "COMMON/RECORDRECAT1C.H"
#include "COMMON/LONE/g_pakDefaultPreviewTypeLabel.H"
#include "COMMON/PAK_MENU.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
extern struct Saved g_pakControllerRecord;
extern Shared_MenuData g_playerViewRenderContext;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern struct Saved g_pakLoadedProfileEuropean;
extern char *g_pakProfileGameNames[], *g_pakSnapshotGameNames[], *g_pakCompanyCodes[], *g_pakLegacySnapshotGameNames[], *g_pakDefaultNoteNamesLocalized[];
extern u8 *g_localizedPakStatusHeading[];
extern struct Dialog g_pakLoadedBlockDialogEuropean, g_pakSelectedBlockDialogEuropean, g_pakLoadedProfileDialogEuropean, g_pakSelectedProfileDialogEuropean, g_pakOtherNoteDialogEuropean, g_pakLoadErrorDialogEuropean;
static __inline__ char *rw_pak_profile_name(Shared_Game *settings) { return g_pakProfileGameNames[settings->language]; }
static __inline__ char *rw_pak_block_name(Shared_Game *settings) { return g_pakSnapshotGameNames[settings->language]; }
static __inline__ char *rw_pak_company(Shared_Game *settings) { return g_pakCompanyCodes[settings->language]; }
static __inline__ char *rw_pak_game_code(Shared_Game *settings) { return g_pakLegacySnapshotGameNames[settings->language]; }
static __inline__ char *rw_pak_invalid_name(Shared_Game *settings) { return g_pakDefaultNoteNamesLocalized[settings->language]; }
static __inline__ u8 *rw_pak_note_text(Shared_Game *settings) { return g_localizedPakStatusHeading[settings->language]; }
static __inline__ struct Dialog *rw_pak_loaded_block_dialog(void) { return &g_pakLoadedBlockDialogEuropean; }
static __inline__ struct Dialog *rw_pak_selected_block_dialog(void) { return &g_pakSelectedBlockDialogEuropean; }
static __inline__ struct Dialog *rw_pak_loaded_profile_dialog(void) { return &g_pakLoadedProfileDialogEuropean; }
static __inline__ struct Dialog *rw_pak_selected_profile_dialog(void) { return &g_pakSelectedProfileDialogEuropean; }
static __inline__ struct Dialog *rw_pak_other_note_dialog(void) { return &g_pakOtherNoteDialogEuropean; }
static __inline__ struct Dialog *rw_pak_load_error_dialog(void) { return &g_pakLoadErrorDialogEuropean; }
static __inline__ struct Saved *rw_pak_loaded_profile(void) { return &g_pakLoadedProfileEuropean; }
#else
extern struct Saved g_pakLoadedProfile;
extern char *g_pakProfileGameNameFixed, *g_pakSnapshotGameNameFixed, *g_pakLegacySnapshotGameNameFixed, *g_pakDefaultNoteNameFixed;
extern u8 *g_pakCompanyCodeFixed;
extern struct Dialog g_pakLoadedBlockDialog, g_pakSelectedBlockDialog, g_pakLoadedProfileDialog, g_pakSelectedProfileDialog, g_pakOtherNoteDialog, g_pakLoadErrorDialog;
static __inline__ char *rw_pak_profile_name(Shared_Game *settings) { return g_pakProfileGameNameFixed; }
static __inline__ char *rw_pak_block_name(Shared_Game *settings) { return g_pakSnapshotGameNameFixed; }
static __inline__ char *rw_pak_company(Shared_Game *settings) { return (char *)g_pakCompanyCodeFixed; }
static __inline__ char *rw_pak_game_code(Shared_Game *settings) { return g_pakLegacySnapshotGameNameFixed; }
static __inline__ char *rw_pak_invalid_name(Shared_Game *settings) { return g_pakDefaultNoteNameFixed; }
static __inline__ u8 *rw_pak_note_text(Shared_Game *settings) { return g_pakDefaultPreviewTypeLabel; }
static __inline__ struct Dialog *rw_pak_loaded_block_dialog(void) { return &g_pakLoadedBlockDialog; }
static __inline__ struct Dialog *rw_pak_selected_block_dialog(void) { return &g_pakSelectedBlockDialog; }
static __inline__ struct Dialog *rw_pak_loaded_profile_dialog(void) { return &g_pakLoadedProfileDialog; }
static __inline__ struct Dialog *rw_pak_selected_profile_dialog(void) { return &g_pakSelectedProfileDialog; }
static __inline__ struct Dialog *rw_pak_other_note_dialog(void) { return &g_pakOtherNoteDialog; }
static __inline__ struct Dialog *rw_pak_load_error_dialog(void) { return &g_pakLoadErrorDialog; }
static __inline__ struct Saved *rw_pak_loaded_profile(void) { return &g_pakLoadedProfile; }
#endif
#endif
