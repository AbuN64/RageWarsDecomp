#ifndef UI_TSMOS_SCREENS_PAKINTERFACESCREEN_H
#define UI_TSMOS_SCREENS_PAKINTERFACESCREEN_H
#include "TYPES.H"
/* The PAK interface screen (frontend "PAKInterface"): a header, then four per-user records
   (m_PAKInterfacePlayer[anUser]), each holding four 400-byte player records and the name being typed.
   Only the fields the ROM code reads are named; the rest is padding of the measured size. */
#define PAK_USERS 4
#define PAK_PLAYER_RECORD_SIZE 400
#define PAK_NAME_LENGTH 8
typedef struct PAKNameChar {
    u8 ch;
    u8 attr;
} PAKNameChar;
/* One 400-byte "global" player record; only the fields the update code tests are named. */
typedef struct PAKGlobalPlayer {
    u8 m_Name[8];
    s32 m_Marker;
    s8 m_Slot;
    s8 m_User;
    s8 m_Quick;
    u8 pad0F[393 - 15];
    u8 m_Field189;
    u8 m_Field18A;
    u8 m_Field18B;
    u8 m_Field18C;
    u8 m_Field18D;
    u8 pad18E[PAK_PLAYER_RECORD_SIZE - 398];
} PAKGlobalPlayer;
/* A widget of the screen's user list: the display-list node with the item it draws, its alpha, its x and width, and the previous and next widget. */
struct PAKListItem;
typedef struct PAKUserWidget {
    u8 pad0[8];
    struct PAKListItem *m_pItem;
    u8 padC[4];
    u8 m_Alpha;
    u8 pad11[3];
    u16 m_X;
    u8 pad16[2];
    s16 m_Width;
    u8 pad1A[44 - 26];
    struct PAKUserWidget *m_pPrev;
    struct PAKUserWidget *m_pNext;
    u8 pad34[4];
    char *m_pText;
} PAKUserWidget;
/* One row of the Controller Pak management list: the line shown, the note name and the pages it takes. */
#define PAK_NOTE_ROWS 16
#define PAK_PLAYER(user) (g_pakInterfaceScreen->m_PAKInterfacePlayer[user])
typedef struct PAKNoteRow {
    char m_Line[40];
    char m_Name[20];
    char m_Size[10];
} PAKNoteRow;
/* A name-entry character widget of the display list: the label holding the typed character, its flags and the next widget. */
typedef struct PAKNameWidget {
    u8 pad0[8];
    struct PAKLabel *m_pLabel;
    u8 padC[18 - 12];
    u16 m_Flags;
    u8 pad14[56 - 20];
    struct PAKNameWidget *m_pNext;
} PAKNameWidget;
/* A list row widget; only its alpha byte and its text pointer are used. */
typedef struct PAKLabel {
    u8 m_Unread0[16];
    u8 m_Alpha;
    u8 m_Unread11[56 - 17];
    char *m_pText;
} PAKLabel;
typedef struct PAKInterfacePlayer {
    s32 m_State;
    s32 m_Mode;
    s32 m_Step;
    PAKUserWidget *m_pWidget;
    PAKUserWidget *m_pObject;
    s32 m_Panel;
    PAKGlobalPlayer m_MiddleRecords[PAK_USERS];
    PAKNoteRow m_Notes[PAK_NOTE_ROWS];
    char m_TextAB8[2754 - 1624 - PAK_NOTE_ROWS * 70];
    char m_BlocksText[10];
    char m_PagesFreeText[12];
    s32 m_ListCursor;
    s32 m_ListTop;
    PAKLabel *m_ListRows[3];
    s32 m_QuickRecord;
    s32 m_RecordState[PAK_USERS];
    PAKUserWidget *m_pSlotObject[PAK_USERS];
    u8 padB40[2856 - 2816 - PAK_USERS * 4];
    s32 m_SelectedRecord;
    s32 m_FieldB3C;
    s32 m_NameTarget;
    PAKNameChar m_Name[PAK_NAME_LENGTH];
    s32 m_NameCursor;
    s32 m_FieldB48;
    s32 m_FieldB4C;
    char m_ModeText[2916 - 2896];
    s32 m_Marker;
} PAKInterfacePlayer;
/* One of the four slots: which user list and which of its four middle records hold the slot's player (-1 for none). */
typedef struct PAKSlotState {
    s32 m_User;
    s32 m_Record;
    s32 m_State;
} PAKSlotState;
/* What the Controller Pak holds for one user: the four middle-list player records, then the marker and a checksum. */
#define PAK_SAVE_DATA_SIZE 1600
#define PAK_CHECKSUM_SEED 7
typedef struct PAKSaveBlock {
    PAKGlobalPlayer m_Records[PAK_USERS];
    s32 m_Marker;
    s32 m_Checksum;
} PAKSaveBlock;
typedef struct PAKInterfaceScreen {
    void *m_pDisplayList;
    void *m_pUserList;
    u8 m_Wipe[28];
    void *m_pFlicker;
    PAKUserWidget *m_pFlickerWidget;
    s32 m_UserBusy[PAK_USERS];
    PAKUserWidget *m_pBarA;
    s32 m_BarStepA;
    PAKUserWidget *m_pBarB;
    s32 m_BarStepB;
    s32 m_ExitPhase;
    s32 m_ExitStep;
    s32 m_Mode;
    PAKInterfacePlayer m_PAKInterfacePlayer[PAK_USERS];
    PAKSlotState m_Slot[PAK_USERS];
    PAKSaveBlock m_SaveBlock;
    s32 m_ExitTarget;
} PAKInterfaceScreen;
#define PAKINTERFACE_MAX_USERS PAK_USERS
extern PAKInterfaceScreen *g_pakInterfaceScreen;
extern s32 PAKInterface_OnInitialUpdate(s32 a, s32 b, s32 c, s32 d);
extern s32 PAKInterface_OnDestroy(s32 a, s32 b, s32 c, s32 d);
extern s32 PAKInterface_OnButtonUp(s32 a, s32 b, s32 c, s32 d);
extern s32 PAKInterface_OnRight(s32 a, s32 b, s32 c, s32 d);
extern PAKGlobalPlayer g_pakGlobalPlayers[PAK_USERS];
/* Per-global-player update flags, 150 bytes apart: the active flag at +0, the pending flag at +25. */
#define PAK_UPDATE_INFO_SIZE 150
#define PAK_UPDATE_ACTIVE 0
#define PAK_UPDATE_PENDING 25
#define PAK_UPDATE_START_PRESSED 120
extern u8 g_pakUpdateInfo[PAK_USERS][PAK_UPDATE_INFO_SIZE];
/* The same record by field: the active and pending flags the update code tests, and the start-pressed flag at +120. */
typedef struct PAKUpdateInfo {
    u8 m_Active;
    u8 m_Unread1[PAK_UPDATE_PENDING - 1];
    u8 m_Pending;
    u8 m_Unread1A[PAK_UPDATE_START_PRESSED - PAK_UPDATE_PENDING - 1];
    u8 m_StartPressed;
    u8 m_Unread79[PAK_UPDATE_INFO_SIZE - PAK_UPDATE_START_PRESSED - 1];
} PAKUpdateInfo;
extern char s_pakInterfaceSourceFile[];
extern s32 AssertFailed(char *file, s32 line, char *expr);
#define PAK_ASSERT(line, cond, expr) \
    if (!(cond)) { \
        if (AssertFailed(s_pakInterfaceSourceFile, line, expr)) { \
            *(char *)0 = 0; \
        } \
    }
extern char s_pakAssertSlotRange[];
extern char s_pakAssertUserRange[];
extern char s_pakAssertIndexRange[];
extern char s_pakAssertUserObject[];
extern char s_pakAssertNoEmptySlot[];
extern char s_pakAssertExitMode[];
extern void TSMOS_InputDisable(void);
extern char s_pakFmtDecimal[];
extern char s_pakFmtLineNamed[];
extern char s_pakFmtLine[];
extern char s_pakAssertNullObject[];
extern char s_pakAssertRow0[];
extern char s_pakAssertRow1[];
extern char s_pakAssertRow2[];
extern char *pText_PAK_Empty[];
extern char *pText_PAK_UnnamedNote[];
extern s32 PAK_GetNoteInfo(s32 anUser, s32 anNote, s32 *apState, char *apName, u8 *apExt, s32 *apPages, s32 *apInfoA, s32 *apInfoB);
extern s32 IsJapName(char *apName, s32 anLength);
extern char *x_sprintf(char *apDst, const char *apFormat, ...);
extern void *SM_DLFindObjectByID(void *apList, u16 anId);
extern s32 PAKInterface_CalcSaveGameSize(void);
extern void PAKInterface_ScrollManagementList(s32 anUser, s32 anDirection);
extern s32 PAKInterface_FindEmptyGlobalSlot(void);
extern void PAKInterface_InitGlobalSlot(s32 anFlag, s32 anSlot);
extern s32 PAKInterface_FindEmptyMiddleSlot(void);
extern s32 PAK_GetPagesFree(s32 anUser, s32 *apPages);
extern s32 PAK_GetNotesFree(s32 anUser, s32 *apNotes);
extern s32 PAK_PagesForBytes(s32 anBytes);
extern s32 Chksum(void *apData, s32 anSize, s32 anSeed);
extern void *memcpy(void *apDst, const void *apSrc, u32 anSize);
extern void CPersistentPlayerData_Initialize(PAKGlobalPlayer *apPlayer);
extern void PAKInterface_RefreshMiddleList(s32 anUser);
extern void PAKInterface_InitPlayerMode(s32 anUser);
extern void PAKInterface_RefreshMiddleNamesForCopy(s32 anUser);
struct WidgetLayout;
/* The screen manager's widget of one user, from the screen's user list. */
extern struct WidgetLayout *PAKInterface_GetUserObject(void *apUserList, s32 anUser);
extern void PAKInterface_SetControlOwner(void *apUserList, s32 anUser, s32 anFlag);
/* A list widget row: the widget's own 14 words, then the global player the row stands for. */
typedef struct PAKListItem {
    u8 m_WidgetHead[14];
    u16 m_WidgetType;
    u8 m_WidgetTail[40];
    PAKGlobalPlayer *m_pPlayer;
} PAKListItem;
/* The engine application record; only the bytes the pak screens read are named: the frontend mode and the language the text tables are indexed with. */
#define ENGINE_APP_FRONTEND_MODE_OFFSET 157725
#define ENGINE_APP_LANGUAGE_OFFSET 159121
#define ENGINE_APP_PLAYER_SETUP_OFFSET 157920
/* The setup bytes of the player being created that a quick-play name entry copies into its record. */
typedef struct PAKPlayerSetup {
    u8 pad0[121];
    u8 m_Field121;
    u8 m_Field122;
    u8 m_Field123;
    u8 pad7C;
    u8 m_Field125;
    u8 pad7E[130 - 126];
    u8 m_Field130;
} PAKPlayerSetup;
typedef struct EngineApp {
    u8 pad0[ENGINE_APP_FRONTEND_MODE_OFFSET];
    u8 m_FrontendMode;
    u8 pad1[ENGINE_APP_PLAYER_SETUP_OFFSET - ENGINE_APP_FRONTEND_MODE_OFFSET - 1];
    PAKPlayerSetup m_PlayerSetup;
    u8 pad2[ENGINE_APP_LANGUAGE_OFFSET - ENGINE_APP_PLAYER_SETUP_OFFSET - sizeof(PAKPlayerSetup)];
    u8 m_Language;
} EngineApp;
extern EngineApp g_engineApp;
extern char *pText_MultiFileName[];
extern char *pText_GameCode[];
extern char *x_strcpy(char *apDst, const char *apSrc);
extern s32 PAK_AnySavesOnPak(char *apFileName, s32 anUser, s32 *apNote);
extern s32 PAK_DeleteNote(s32 anUser, s32 anNote);
extern s32 PAK_FindFirstAvailableExt(s32 anUser, s32 *apExt);
extern s32 PAK_WriteNote(s32 anUser, s32 anSize, void *apData, char *apName, s32 *apExt, char *apGameCode);
extern s32 PAK_ReadNote(s32 anUser, s32 anNote, void *apData, s32 anSize);
extern s32 PAKInterface_CheckForRoomOnPak(s32 anUser, s32 *apResult);
extern void PAKInterface_PrepareSaveBlockForSave(s32 anUser);
extern void PAKInterface_PrepareDataAfterLoad(s32 anUser);
extern PAKListItem *PAKInterface_AddListItem(void *apList, u16 anStringId);


extern char s_pakAssertNextMode[];
extern char s_pakAssertScreenMode[];
extern char s_pakAssertCheckStatus[];
extern s32 PAK_CheckStatus(s32 anUser);
extern s32 PAKInterface_LoadGame(s32 anUser, s32 anNote);
extern s32 PAKInterface_FindEmptyPlayerDataSlot(s32 anUser);
extern s32 PAKInterface_IsPlayerDataListEmpty(s32 anUser);
extern s32 PAKInterface_ValidatePAKAgainstGlobal(s32 anUser);
extern s32 RandomSwapWord(void);
/* The same row when it carries a text string instead of a player. */
typedef struct PAKListTextItem {
    u8 m_WidgetHead[52];
    s32 m_StringId;
    char *m_pText;
} PAKListTextItem;
extern void SM_DLSetDisabled(PAKUserWidget *apObject, s32 anDisabled);
extern void SM_DLSetVisible(PAKUserWidget *apObject, s32 anVisible);
extern s32 SM_DLIsDisabled(PAKUserWidget *apObject);
extern void SMMU_SwitchUserControlFocusByObject(void *apUserList, s32 anUser, PAKUserWidget *apObject);
extern PAKUserWidget *SMMU_GetActiveControl(void *apUserList, s32 anUser);
extern s32 PAKInterface_GetGlobalPlayerByMarker(s32 anMarker, s32 anSlot);
extern s32 ControllerConnected(s32 anController);
extern s32 PAKInterface_AddPlayerToMiddle(s32 anUser, s32 anSlot);
extern char s_pakAssertSlotObject[];
extern char s_pakAssertListObject[];
extern char s_pakAssertListObjectType[];
extern char s_pakAssertListItem[];

#if defined(VERSION_US_REV1)
#endif
/* Versioned setup strings and control identifiers from the native menu tables. */
#if defined(VERSION_US)
extern const char g_modeToken[];
#elif defined(VERSION_EU)
extern const char g_modeToken[];
#elif defined(VERSION_EU_X)
extern const char g_modeToken[];
#elif defined(VERSION_DE)
extern const char g_modeToken[];
#else
extern const char g_modeToken[];
#endif
#if defined(VERSION_DE)
extern s32 g_pakProfileOperationPhase;
#elif defined(VERSION_US)
extern s32 g_pakDialogProbeStateUs;
#elif defined(VERSION_EU)
extern s32 g_pakDialogProbeStateEu;
#elif defined(VERSION_EU_X)
extern s32 g_pakDialogProbeStateEuX;
#else
extern s32 g_pakDialogProbeStateUsRev1;
#endif
#if defined(VERSION_DE)
enum { SETUP_LABEL_ID = 641 };
enum { PANEL_ROOT_ID = 737 };
enum { PANEL_TEXT_ID = 739 };
enum { MODE_DEFAULT_ID = 862 };
enum { MODE_17_ID = 866 };
enum { MODE_2_ID = 864 };
enum { MODE_3_ID = 865 };
enum { MODE_46_ID = 867 };
enum { MODE_5_ID = 863 };
enum { MODE_HIDE_ID = 738 };
enum { SLOT_DEFAULT_ID = 652 };
enum { SLOT_1_ID = 654 };
enum { SLOT_2_ID = 656 };
enum { SLOT_3_ID = 658 };
enum { CHECK_0_ID = 662 };
enum { CHECK_1_ID = 664 };
enum { CHECK_2_ID = 666 };
enum { CHECK_DEFAULT_ID = 668 };
#elif defined(VERSION_EU_X)
enum { SETUP_LABEL_ID = 650 };
enum { PANEL_ROOT_ID = 721 };
enum { PANEL_TEXT_ID = 723 };
enum { MODE_DEFAULT_ID = 877 };
enum { MODE_17_ID = 881 };
enum { MODE_2_ID = 879 };
enum { MODE_3_ID = 880 };
enum { MODE_46_ID = 882 };
enum { MODE_5_ID = 878 };
enum { MODE_HIDE_ID = 722 };
enum { SLOT_DEFAULT_ID = 660 };
enum { SLOT_1_ID = 662 };
enum { SLOT_2_ID = 664 };
enum { SLOT_3_ID = 666 };
enum { CHECK_0_ID = 671 };
enum { CHECK_1_ID = 673 };
enum { CHECK_2_ID = 675 };
enum { CHECK_DEFAULT_ID = 677 };
#else
enum { SETUP_LABEL_ID = 645 };
enum { PANEL_ROOT_ID = 705 };
enum { PANEL_TEXT_ID = 709 };
enum { MODE_DEFAULT_ID = 836 };
enum { MODE_17_ID = 840 };
enum { MODE_2_ID = 838 };
enum { MODE_3_ID = 839 };
enum { MODE_46_ID = 841 };
enum { MODE_5_ID = 837 };
enum { MODE_HIDE_ID = 708 };
enum { SLOT_DEFAULT_ID = 651 };
enum { SLOT_1_ID = 653 };
enum { SLOT_2_ID = 655 };
enum { SLOT_3_ID = 657 };
enum { CHECK_0_ID = 665 };
enum { CHECK_1_ID = 667 };
enum { CHECK_2_ID = 669 };
enum { CHECK_DEFAULT_ID = 671 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_1_2EC = 719 };
enum { UI_CASE_1_2EE = 721 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_1_2EC = 744 };
enum { UI_CASE_1_2EE = 746 };
#else
enum { UI_CASE_1_2EC = 748 };
enum { UI_CASE_1_2EE = 750 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_2_2D4 = 672 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_2_2D4 = 720 };
#else
enum { UI_CASE_2_2D4 = 724 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_3_2BB = 725 };
enum { UI_CASE_3_2BC = 727 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_3_2BB = 732 };
enum { UI_CASE_3_2BC = 733 };
#else
enum { UI_CASE_3_2BB = 699 };
enum { UI_CASE_3_2BC = 700 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_4_2D5 = 742 };
enum { UI_CASE_4_2DA = 744 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_4_2D5 = 750 };
enum { UI_CASE_4_2DA = 757 };
#else
enum { UI_CASE_4_2D5 = 725 };
enum { UI_CASE_4_2DA = 730 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_6_2E4 = 681 };
enum { UI_CASE_6_2E8 = 687 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_6_2E4 = 709 };
enum { UI_CASE_6_2E8 = 713 };
#else
enum { UI_CASE_6_2E4 = 740 };
enum { UI_CASE_6_2E8 = 744 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_7_2CA = 751 };
enum { UI_CASE_7_2CC = 753 };
enum { UI_CASE_7_2CB = 754 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_7_2CA = 740 };
enum { UI_CASE_7_2CC = 741 };
enum { UI_CASE_7_2CB = 739 };
#else
enum { UI_CASE_7_2CA = 714 };
enum { UI_CASE_7_2CC = 716 };
enum { UI_CASE_7_2CB = 715 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_8_2CE = 755 };
enum { UI_CASE_8_2CF = 757 };
enum { UI_CASE_8_2CB = 754 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_8_2CE = 736 };
enum { UI_CASE_8_2CF = 737 };
enum { UI_CASE_8_2CB = 739 };
#else
enum { UI_CASE_8_2CE = 718 };
enum { UI_CASE_8_2CF = 719 };
enum { UI_CASE_8_2CB = 715 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_9_2C6 = 688 };
enum { UI_CASE_9_2C8 = 690 };
enum { UI_CASE_9_2C7 = 691 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_9_2C6 = 681 };
enum { UI_CASE_9_2C8 = 684 };
enum { UI_CASE_9_2C7 = 682 };
#else
enum { UI_CASE_9_2C6 = 710 };
enum { UI_CASE_9_2C8 = 712 };
enum { UI_CASE_9_2C7 = 711 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_10_2A4 = 710 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_10_2A4 = 685 };
#else
enum { UI_CASE_10_2A4 = 676 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_11_2D1 = 722 };
enum { UI_CASE_11_2D2 = 723 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_11_2D1 = 726 };
enum { UI_CASE_11_2D2 = 728 };
#else
enum { UI_CASE_11_2D1 = 721 };
enum { UI_CASE_11_2D2 = 722 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_12_2F2 = 729 };
enum { UI_CASE_12_2F3 = 730 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_12_2F2 = 689 };
enum { UI_CASE_12_2F3 = 690 };
#else
enum { UI_CASE_12_2F2 = 754 };
enum { UI_CASE_12_2F3 = 755 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_13_2AF = 711 };
enum { UI_CASE_13_2B6 = 718 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_13_2AF = 759 };
enum { UI_CASE_13_2B6 = 766 };
#else
enum { UI_CASE_13_2AF = 687 };
enum { UI_CASE_13_2B6 = 694 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_17_2A5 = 706 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_17_2A5 = 743 };
#else
enum { UI_CASE_17_2A5 = 677 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_15_2EF = 707 };
enum { UI_CASE_15_2F1 = 709 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_15_2EF = 747 };
enum { UI_CASE_15_2F1 = 749 };
#else
enum { UI_CASE_15_2EF = 751 };
enum { UI_CASE_15_2F1 = 753 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_16_2B7 = 692 };
enum { UI_CASE_16_2B9 = 693 };
enum { UI_CASE_16_2BA = 682 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_16_2B7 = 705 };
enum { UI_CASE_16_2B9 = 707 };
enum { UI_CASE_16_2BA = 706 };
#else
enum { UI_CASE_16_2B7 = 695 };
enum { UI_CASE_16_2B9 = 697 };
enum { UI_CASE_16_2BA = 698 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_21_2E1 = 678 };
enum { UI_CASE_21_2E2 = 680 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_21_2E1 = 729 };
enum { UI_CASE_21_2E2 = 731 };
#else
enum { UI_CASE_21_2E1 = 737 };
enum { UI_CASE_21_2E2 = 738 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_23_2AC = 695 };
enum { UI_CASE_23_2AE = 697 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_23_2AC = 702 };
enum { UI_CASE_23_2AE = 704 };
#else
enum { UI_CASE_23_2AC = 684 };
enum { UI_CASE_23_2AE = 686 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_24_2A9 = 700 };
enum { UI_CASE_24_2AA = 701 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_24_2A9 = 686 };
enum { UI_CASE_24_2AA = 687 };
#else
enum { UI_CASE_24_2A9 = 681 };
enum { UI_CASE_24_2AA = 682 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_25_2EA = 698 };
enum { UI_CASE_25_2EB = 699 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_25_2EA = 700 };
enum { UI_CASE_25_2EB = 701 };
#else
enum { UI_CASE_25_2EA = 746 };
enum { UI_CASE_25_2EB = 747 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_26_2A6 = 703 };
enum { UI_CASE_26_2A7 = 704 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_26_2A6 = 697 };
enum { UI_CASE_26_2A7 = 698 };
#else
enum { UI_CASE_26_2A6 = 678 };
enum { UI_CASE_26_2A7 = 679 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_28_2DE = 673 };
enum { UI_CASE_28_2DF = 674 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_28_2DE = 717 };
enum { UI_CASE_28_2DF = 719 };
#else
enum { UI_CASE_28_2DE = 734 };
enum { UI_CASE_28_2DF = 735 };
#endif
#if defined(VERSION_DE)
enum { UI_CASE_29_2BF = 676 };
enum { UI_CASE_29_2C0 = 677 };
#elif defined(VERSION_EU_X)
enum { UI_CASE_29_2BF = 715 };
enum { UI_CASE_29_2C0 = 716 };
#else
enum { UI_CASE_29_2BF = 703 };
enum { UI_CASE_29_2C0 = 704 };
#endif

extern s32 PAKInterface_AddPlayerProfileLink(s32 first, s32 second);

extern int PAKInterface_ArePlayerLinksEmpty(void);

extern int PAKInterface_AreProfileSlotsEmpty(int player);

extern void PAKInterface_BeginLinkedProfileTransfer(s32 player);

extern void PAKInterface_BeginScreenExit(int focusEntry);

extern void PAKInterface_BuildSavePacket(s32 index);

extern void PAKInterface_CopyActiveProfilesToPakSlots(s32 player);

extern int PAKInterface_CountActivePlayerPanels(void);

extern s32 PAKInterface_CountPendingPlayerPanels(void);

extern s32 PAKInterface_CountUnfinishedPlayerPanels(void);

extern void PAKInterface_EnablePlayerPanel(s32 index);

extern int PAKInterface_FindEmptyPlayerLink(void);

extern int PAKInterface_FindEmptyProfileSlot(int player);

extern int PAKInterface_FindPlayerProfileLink(int id, int value);

extern int PAKInterface_GetRecordsNoteSize(void);

extern s32 PAKInterface_JoinChosenProfile(s32 player);

extern void PAKInterface_LabelActiveProfileRows(s32 player);

extern void PAKInterface_LoadLinkedPlayerProfile(s32 linkIndex);

extern void PAKInterface_PulseIdlePanelLabels(s32 index);

extern void PAKInterface_ReassignLocalProfiles(void);

extern int PAKInterface_RemovePlayerProfileLink(int id, int value);

extern void PAKInterface_RestoreSavePacket(s32 index);

extern void PAKInterface_ReturnWithoutAction(void);
#endif
