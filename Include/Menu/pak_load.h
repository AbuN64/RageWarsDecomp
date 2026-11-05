#ifndef MENU_PAK_LOAD_H
#define MENU_PAK_LOAD_H
#include "Common/player_message_menu.h"
#include "Common/ballisticparams.h"
#include "Common/pak_profile_load.h"
#include "Common/Lone/g_pakdefaultpreviewtypelabel.h"
#include "Common/pak_menu.h"
#include "Common/shared_optionsscreen.h"
struct Shared_Game;
extern struct Saved g_pakControllerRecord;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern struct Saved g_pakLoadedProfileEuropean;
extern char *g_pakProfileGameNames[], *g_pakSnapshotGameNames[], *g_pakCompanyCodes[], *g_pakLegacySnapshotGameNames[], *g_pakDefaultNoteNamesLocalized[];
extern u8 *g_localizedPakStatusHeading[];
extern struct Dialog g_pakLoadedBlockDialogEuropean, g_pakSelectedBlockDialogEuropean, g_pakLoadedProfileDialogEuropean, g_pakSelectedProfileDialogEuropean, g_pakOtherNoteDialogEuropean, g_pakLoadErrorDialogEuropean;
static __inline__ char *rw_pak_profile_name(struct Shared_Game *settings) { return g_pakProfileGameNames[settings->language]; }
static __inline__ char *rw_pak_block_name(struct Shared_Game *settings) { return g_pakSnapshotGameNames[settings->language]; }
static __inline__ char *rw_pak_company(struct Shared_Game *settings) { return g_pakCompanyCodes[settings->language]; }
static __inline__ char *rw_pak_game_code(struct Shared_Game *settings) { return g_pakLegacySnapshotGameNames[settings->language]; }
static __inline__ char *rw_pak_invalid_name(struct Shared_Game *settings) { return g_pakDefaultNoteNamesLocalized[settings->language]; }
static __inline__ u8 *rw_pak_note_text(struct Shared_Game *settings) { return g_localizedPakStatusHeading[settings->language]; }
static __inline__ struct Dialog *rw_pak_loaded_block_dialog(void) { return &g_pakLoadedBlockDialogEuropean; }
static __inline__ struct Dialog *rw_pak_selected_block_dialog(void) { return &g_pakSelectedBlockDialogEuropean; }
static __inline__ struct Dialog *rw_pak_loaded_profile_dialog(void) { return &g_pakLoadedProfileDialogEuropean; }
static __inline__ struct Dialog *rw_pak_selected_profile_dialog(void) { return &g_pakSelectedProfileDialogEuropean; }
static __inline__ struct Dialog *rw_pak_other_note_dialog(void) { return &g_pakOtherNoteDialogEuropean; }
static __inline__ struct Dialog *rw_pak_load_error_dialog(void) { return &g_pakLoadErrorDialogEuropean; }
static __inline__ struct Saved *rw_pak_loaded_profile(void) { return &g_pakLoadedProfileEuropean; }
#else
extern struct Saved g_pakLoadedProfile;
extern u8 *g_pakCompanyCodeFixed;
extern char *g_pakDefaultNoteNameFixed; /* default Controller Pak note name */
extern struct Dialog g_pakLoadedBlockDialog, g_pakSelectedBlockDialog, g_pakLoadedProfileDialog, g_pakSelectedProfileDialog, g_pakOtherNoteDialog, g_pakLoadErrorDialog;
static __inline__ char *rw_pak_profile_name(struct Shared_Game *settings) { return g_pakProfileGameNameFixed; }
static __inline__ char *rw_pak_block_name(struct Shared_Game *settings) { return g_pakSnapshotGameNameFixed; }
static __inline__ char *rw_pak_company(struct Shared_Game *settings) { return (char *)g_pakCompanyCodeFixed; }
static __inline__ char *rw_pak_game_code(struct Shared_Game *settings) { return g_pakLegacySnapshotGameNameFixed; }
static __inline__ char *rw_pak_invalid_name(struct Shared_Game *settings) { return g_pakDefaultNoteNameFixed; }
static __inline__ u8 *rw_pak_note_text(struct Shared_Game *settings) { return g_pakDefaultPreviewTypeLabel; }
static __inline__ struct Dialog *rw_pak_loaded_block_dialog(void) { return &g_pakLoadedBlockDialog; }
static __inline__ struct Dialog *rw_pak_selected_block_dialog(void) { return &g_pakSelectedBlockDialog; }
static __inline__ struct Dialog *rw_pak_loaded_profile_dialog(void) { return &g_pakLoadedProfileDialog; }
static __inline__ struct Dialog *rw_pak_selected_profile_dialog(void) { return &g_pakSelectedProfileDialog; }
static __inline__ struct Dialog *rw_pak_other_note_dialog(void) { return &g_pakOtherNoteDialog; }
static __inline__ struct Dialog *rw_pak_load_error_dialog(void) { return &g_pakLoadErrorDialog; }
static __inline__ struct Saved *rw_pak_loaded_profile(void) { return &g_pakLoadedProfile; }
#endif
typedef struct Dialog {
    struct EntryPakCreateMenuFromParameters *entries;
    s16 count;
    char pad6[0x1A];
    signed int value;
} Dialog;

#endif
