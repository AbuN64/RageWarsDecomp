#ifndef COMMON_PAK_SAVE_TEXT_H
#define COMMON_PAK_SAVE_TEXT_H
#include "COMMON/ITEMRECAT20V1.H"
/* Localized Controller Pak note metadata and result dialog resources. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern struct MenuSettings g_gameSettings;
extern char *g_pakProfileGameNames[], *g_pakSnapshotGameNames[], *g_pakLegacySnapshotGameNames[];
extern char g_pakNoSpaceDialogEu[], g_pakSaveSuccessDialogEu[], g_pakSaveErrorDialogEu[];
static __inline__ char *rw_pak_save_name(void) { return g_pakProfileGameNames[g_gameSettings.language]; }
/* Note titles are indexed through the menu settings view, the game code straight from its table:
 * both shapes are what the PAL save code compiles from (Snapshot_SaveControllerRecord, Snapshot_SaveSnapshotAndClose). */
static __inline__ struct MenuSettings *rw_pak_settings(void) { return &g_gameSettings; }
#define RW_PAK_RECORD_TITLE (g_pakProfileGameNames[rw_pak_settings()->language])
#define RW_PAK_SNAPSHOT_TITLE (g_pakSnapshotGameNames[rw_pak_settings()->language])
#define RW_PAK_GAME_CODE (g_pakLegacySnapshotGameNames[g_gameSettings.language])
static __inline__ char *rw_pak_no_space_dialog(void) { return g_pakNoSpaceDialogEu; }
static __inline__ char *rw_pak_save_success_dialog(void) { return g_pakSaveSuccessDialogEu; }
static __inline__ char *rw_pak_save_error_dialog(void) { return g_pakSaveErrorDialogEu; }
#else
extern char *g_pakProfileGameNameFixed, *g_pakLegacySnapshotGameNameFixed;
extern char g_pakNoSpaceDialog[], g_pakSaveSuccessDialog[], g_pakSaveErrorDialog[];
static __inline__ char *rw_pak_save_name(void) { return g_pakProfileGameNameFixed; }
/* Controller Pak note header strings, four pointers in a row: "RAGE WARS", "TUROK 2", company "51",
 * game code "NRWE". The titles are read as members of this view; a member read through the getter is
 * a cheap reg+offset load that expand_call passes straight into its argument register. */
typedef struct PakNoteHeader {
    char *recordTitle;   /* g_pakProfileGameNameFixed */
    char *snapshotTitle; /* g_pakSnapshotGameNameFixed */
    char *companyCode;   /* g_pakCompanyCodeFixed */
    char *gameCode;      /* g_pakLegacySnapshotGameNameFixed */
} PakNoteHeader;
static __inline__ PakNoteHeader *rw_pak_note_header(void) { return (PakNoteHeader *)&g_pakProfileGameNameFixed; }
#define RW_PAK_RECORD_TITLE (rw_pak_note_header()->recordTitle)
#define RW_PAK_SNAPSHOT_TITLE (rw_pak_note_header()->snapshotTitle)
#define RW_PAK_GAME_CODE (g_pakLegacySnapshotGameNameFixed)
static __inline__ char *rw_pak_no_space_dialog(void) { return g_pakNoSpaceDialog; }
static __inline__ char *rw_pak_save_success_dialog(void) { return g_pakSaveSuccessDialog; }
static __inline__ char *rw_pak_save_error_dialog(void) { return g_pakSaveErrorDialog; }
#endif
#endif
