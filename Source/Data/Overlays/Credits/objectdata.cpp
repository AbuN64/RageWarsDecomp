#include "Data/rest_source_records.h"
#include "Menu/Build/definition_data.h"
#include "Data/Overlays/Credits/objectdata_addresses.h"
#include "Menu/Pak/timer.h"
#include "Common/pak_preview_selection.h"
#include "Common/runtime_declarations.h"

/* Callback columns store the recovered function address with the high bit cleared. */
/* G_MENUPAKPROFILECHOICEITEMS.CPP */
#if defined(VERSION_US_REV1)

struct {
    unsigned int resourceCallback1;
    unsigned int callback1;
    unsigned int initializeCallback1;
    unsigned int parameter1;
    struct MenuBuildItemData items1[3];
    short type1;
    unsigned short reserved021;
} g_menuPakProfileChoiceItems = {
    (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
    (unsigned int)Timer_UpdateOwnerChannelLabel,
    0x00000000,
    0x00000000,
    {
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0xFFF8, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_pakProfileLoadProfileChoiceLabels, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
        (unsigned int)Timer_UpdateOperationChoiceLabel, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0006, 0x00, 0x00, 0xFF, 0x01, 0x800D7714,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
        (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7718,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
        (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
    },
    0x0000,
    0x0000,
};
#endif

/* G_MENUSNAPSHOTNOTEITEMFLAGWORDS.CPP */
#if defined(VERSION_US_REV1)

struct {
    unsigned int flags;
    short x;
    short y;
} g_menuSnapshotNoteItemFlagWords = {
    0x00011001,
    0x0000,
    0x0000,
};
#endif

/* G_MENUSNAPSHOTNOTEITEMTAILWORDS.CPP */
#if defined(VERSION_US_REV1)

struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    int resource;
} g_menuSnapshotNoteItemTailWords = {
    0x00,
    0x00,
    0xFF,
    0x01,
    0x800D771C,
};

struct {
    unsigned int resourceCallback1;
    unsigned int callback1;
    unsigned int initializeCallback1;
    unsigned int parameter1;
    short type1;
    unsigned short reserved021;
    unsigned int flags1;
    short x1;
    short y1;
    unsigned char red1;
    unsigned char green1;
    unsigned char blue1;
    unsigned char alpha1;
    int resource1;
    unsigned int resourceCallback2;
    unsigned int callback2;
    unsigned int initializeCallback2;
} g_menuSnapshotNoteItemHeadAndRows = {
    (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
    (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
    (unsigned int)g_menuPaged_Snapshot_SelectNote,
    0x00000000,
    0x0000,
    0x0000,
    0x00011001,
    0x0000,
    0x0000,
    0x00,
    0x00,
    0xFF,
    0x01,
    0x800D7720,
    (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
    (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
    (unsigned int)g_menuPaged_Snapshot_SelectNote,
};
#endif

/* G_MENUSNAPSHOTNOTEITEMROWS.CPP */
#if defined(VERSION_US_REV1)

struct {
    unsigned int parameter1;
    struct MenuBuildItemData items1[3];
    short type1;
    unsigned short reserved021;
    unsigned int flags1;
    short x1;
    short y1;
    unsigned char red1;
    unsigned char green1;
    unsigned char blue1;
    unsigned char alpha1;
    int resource1;
    unsigned int resourceCallback1;
    unsigned int callback1;
    unsigned int initializeCallback1;
} g_menuSnapshotNoteItemRows = {
    0x00000000,
    {
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7724,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
        (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7728,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
        (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D772C,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
        (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
    },
    0x0000,
    0x0000,
    0x00011001,
    0x0000,
    0x0000,
    0x00,
    0x00,
    0xFF,
    0x01,
    0x800D7730,
    (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
    (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
    (unsigned int)g_menuPaged_Snapshot_SelectNote,
};
#endif

/* G_MENUSNAPSHOTNOTEITEMFINALROW.CPP */
#if defined(VERSION_US_REV1)

struct {
    unsigned int parameter1;
    short type1;
    unsigned short reserved021;
    unsigned int flags1;
    short x1;
    short y1;
    unsigned char red1;
    unsigned char green1;
    unsigned char blue1;
    unsigned char alpha1;
    int resource1;
    unsigned int resourceCallback1;
    unsigned int callback1;
    unsigned int initializeCallback1;
} g_menuSnapshotNoteItemFinalRow = {
    0x00000000,
    0x0000,
    0x0000,
    0x00011001,
    0x0000,
    0x0000,
    0x00,
    0x00,
    0xFF,
    0x01,
    0x800D7734,
    (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
    (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel,
    (unsigned int)g_menuPaged_Snapshot_SelectNote,
};
#endif

/* G_MENUINVENTORYDATA.CPP */
#if defined(VERSION_US_REV1)

struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    int resource;
    unsigned int resourceCallback;
    unsigned int callback;
    unsigned int initializeCallback;
    unsigned int parameter;
    struct MenuBuildItemData items[45];
    struct MenuBuildDefinitionData definitions[1];
} g_menuInventoryData = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x000007D0,
    0x0043EFD0,
    0x00000000,
    0x00000000,
    0x10D60000,
    {
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10D60001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10D60002 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10E00000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10E00001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10E00002 },
        { 0x0001, 0x0000, 0x00024010, 0x0029, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11080000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11940000 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (unsigned int)&k_menuDigitLabelPointers[2],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10EA0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10EA0001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10EA0002 },
        { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080D, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11320000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F9, 0x0043EFD0, 0x00000000,
        0x00000000, 0x111E0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E5, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11090000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11940001 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (unsigned int)&k_menuDigitLabelPointers[3],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10F40000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10F40001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10F40002 },
        { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080F, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11300000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F8, 0x0043EFD0, 0x00000000,
        0x00000000, 0x111C0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E6, 0x0043EFD0, 0x00000000,
        0x00000000, 0x110A0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11940002 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (unsigned int)&k_menuDigitLabelPointers[4],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10FE0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10FE0001 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10FE0002 },
        { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080E, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11340000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FC, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11200000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E7, 0x0043EFD0, 0x00000000,
        0x00000000, 0x110B0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11940003 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (unsigned int)&k_menuDigitLabelPointers[5],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10FE0003 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10FE0004 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10FE0005 },
        { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080C, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11330000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FB, 0x0043EFD0, 0x00000000,
        0x00000000, 0x111F0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E8, 0x0043EFD0, 0x00000000,
        0x00000000, 0x110C0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11940004 },
        { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (unsigned int)&k_menuDigitLabelPointers[6],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x00024010, 0x0075, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000810, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11310000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FA, 0x0043EFD0, 0x00000000,
        0x00000000, 0x111D0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E9, 0x0043EFD0, 0x00000000,
        0x00000000, 0x110D0000 },
        { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, 0x0043EFD0, 0x00000000,
        0x00000000, 0x11940005 },
        { 0x0000, 0x0000, 0x00010081, 0x0000, 0x001E, 0x00, 0x00, 0x00, 0x00, (unsigned int)g_menuOkayLabelSlot,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)g_menuPaged_Multi_CreateMenuWithDefaultMusicGain, 0x00000000 },
    },
    {
        { 0x00450DD0, 0x0031, 0x0000, (unsigned int)g_menuPaged_Multi_EmptyItemHook, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0030, 0x0000, 0x0000, 0x0000, 0x004521BC },
    },
};

unsigned int g_menuInventoryDataTailLeadWords[2] = {
    0x00010110, 0x00000004,
};

struct {
    struct MenuBuildItemData items[1];
    struct MenuBuildDefinitionData definitions[2];
} g_menuInventoryDataTail = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
    },
    {
        { 0x004514E0, 0x0001, 0x0000, (unsigned int)g_menuPaged_Items_CacheIdentifierBand, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00451AF0 },
        { 0x004514E0, 0x0001, 0x0000, (unsigned int)g_menuPaged_Items_PrepareControllerReturn, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

unsigned int g_menuInventoryDataTailTrailingWord[1] = {
    0xFF01F808,
};

struct {
    struct MenuBuildItemData items[12];
} gPakSlotPromptItems = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_fragTagOnLabelText[8],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Player_FormatPlayerPartnerStatus,
        0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D,
        (unsigned int)g_menuPaged_Player_DrawPulsingMenuSprite, 0x00000000,
        (unsigned int)g_menuPaged_Player_RespawnItemPlayer, 0x00000000 },
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_fragTagOnLabelText[40],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Player_FormatPlayerPartnerStatus,
        0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x20010001, 0xFFEC, 0x0000, 0xEC, 0x00, 0x00, 0x01, 0x0000012D,
        (unsigned int)g_menuPaged_Player_DrawPulsingMenuSprite, 0x00000000,
        (unsigned int)g_menuPaged_Player_RespawnItemPlayer, 0x00000000 },
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_fragTagOnLabelText[72],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Player_FormatPlayerPartnerStatus,
        0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D,
        (unsigned int)g_menuPaged_Player_DrawPulsingMenuSprite, 0x00000000,
        (unsigned int)g_menuPaged_Player_RespawnItemPlayer, 0x00000000 },
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_fragTagOnLabelText[104],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Player_FormatPlayerPartnerStatus,
        0x00000000, 0x00000000 },
        { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D,
        (unsigned int)g_menuPaged_Player_DrawPulsingMenuSprite, 0x00000000,
        (unsigned int)g_menuPaged_Player_RespawnItemPlayer, 0x00000000 },
    },
};

struct {
    struct MenuBuildDefinitionData definitions[12];
} gPakSlotPrompts = {
    {
        { 0x00451550, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigurePlayerMenuFlags, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Player_UpdatePlayerRespawnDelay,
        0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x004515BC, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigurePlayerMenuFlags, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Player_UpdatePlayerRespawnDelay,
        0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451628, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigurePlayerMenuFlags, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Player_UpdatePlayerRespawnDelay,
        0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451694, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigurePlayerMenuFlags, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Player_UpdatePlayerRespawnDelay,
        0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451550, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureAndProbeControllerPak, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x004515BC, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureAndProbeControllerPak, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451628, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureAndProbeControllerPak, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451694, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureAndProbeControllerPak, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451550, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureControllerPakMenu, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x004515BC, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureControllerPakMenu, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451628, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureControllerPakMenu, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
        { 0x00451694, 0x0003, 0x0000, (unsigned int)g_menuPaged_Player_ConfigureControllerPakMenu, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

struct {
    struct MenuBuildItemData items[16];
    struct MenuBuildDefinitionData definitions[1];
} g_menuSettingsData = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7DA4,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00400041, 0x0000, 0x002F, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_sceneMaskLabelTables[0],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectSceneMaskText,
        (unsigned int)g_menuPaged_Items_CycleSceneMask, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_playerOptionControlTypeExpertText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerOptionControlTypeText,
        (unsigned int)g_menuPaged_Items_AdjustPlayerOptionControlType, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_playerOptionControlSideLeftText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerOptionControlSideText,
        (unsigned int)g_menuPaged_Items_AdjustPlayerOptionControlSide, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_playerOptionLookSpringOnText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerOptionLookSpringText,
        (unsigned int)g_menuPaged_Items_AdjustPlayerOptionLookSpring, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_playerOptionAutoAimOffText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectPlayerOptionAutoAimText,
        (unsigned int)g_menuPaged_Items_AdjustPlayerOptionAutoAim, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_bloodColorOffText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectBloodColorText,
        (unsigned int)g_menuPaged_Items_AdjustBloodColor, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_gameOptionSplitScreenLayoutHorizontalText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectSplitScreenPreferenceText,
        (unsigned int)g_menuPaged_Items_AdjustSplitScreenPreference, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_packedGameOptionValueText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_FormatPackedGameOption,
        (unsigned int)g_menuPaged_Items_AdjustPackedGameOption, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_playerOptionStickHorizontalStepText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_FormatPlayerOptionStickHorizontalStep,
        (unsigned int)g_menuPaged_Items_AdjustPlayerOptionStickHorizontal, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_playerOptionStickVerticalStepText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_FormatPlayerOptionStickVerticalStep,
        (unsigned int)g_menuPaged_Items_AdjustPlayerOptionStickVertical, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_weaponSelectNormalText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Items_SelectQuickWeaponSelectText,
        (unsigned int)g_menuPaged_Items_ToggleQuickWeaponSelect, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_frontendScreenModePaletteDefault, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
        (unsigned int)g_menuPaged_Items_UpdateScreenModeMenuItem, (unsigned int)g_menuPaged_Items_RequestScreenModeFade,
        0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_packedButtonOptionStepText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
        (unsigned int)g_menuPaged_Pak_FormatPackedButtonOption, (unsigned int)g_menuPaged_Pak_AdjustPackedButtonOption,
        0x00000000 },
        { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0013, 0x00, 0x00, 0xFF, 0x01, 0x800D765C,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu,
        0x00000000 },
    },
    {
        { 0x004518B0, 0x0010, 0x0000, (unsigned int)g_menuPaged_Items_ResetScreenModeFadeCooldown, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x000F, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

unsigned int g_menuSettingsDataTailLeadWords[3] = {
    0x00000094, 0x08000C00, 0x00000000,
};

struct {
    struct MenuBuildItemData items1[5];
    struct MenuBuildDefinitionData definitions1[1];
    struct MenuBuildItemData items2[8];
    struct MenuBuildDefinitionData definitions2[1];
    struct MenuBuildItemData items3[7];
    struct MenuBuildDefinitionData definitions3[1];
    struct MenuBuildItemData items4[7];
    struct MenuBuildDefinitionData definitions4[1];
    struct MenuBuildItemData items5[16];
    struct MenuBuildDefinitionData definitions5[1];
    struct MenuBuildItemData items6[45];
    struct MenuBuildDefinitionData definitions6[1];
} g_menuSettingsDataTail = {
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D76F4,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00000101, 0x0000, 0x005D, 0x00, 0x00, 0xFF, 0x01, 0x800D7A88,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, 0x800D7A90,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)g_menuPaged_Pak_StopMusicAndResetMatch, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuNoLabelSlot,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Menu_TryCreateMenu,
        0x00000000 },
    },
    {
        { 0x00451B20, 0x0005, 0x0000, ((unsigned int)Pak_SetRecordTypeFour - 0x80000000U), 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, 0x00000000, 0x0004, 0x0000, 0x0000, 0x0000, 0x004521BC },
    },
    {
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_editFogTextPointer, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText,
        0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugColorThicknessLabels.redTextPointer,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Pak_AdjustDebugRed, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugColorThicknessLabels.greenTextPointer,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Pak_AdjustDebugGreen, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugColorThicknessLabels.blueTextPointer,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Pak_AdjustDebugBlue, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugColorThicknessLabels.thicknessTextPointer,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Pak_AdjustDebugThickness, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugFieldOfViewLabel,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Pak_AdjustDebugFarClip, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugFieldOfViewLabel.fieldOfViewTextPointer,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Pak_AdjustDebugFieldOfView, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugAmbientColorLabel,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, (unsigned int)g_menuPaged_Pak_UpdateChoiceText,
        (unsigned int)g_menuPaged_Pak_ToggleTextChoice, 0x00000000 },
    },
    {
        { 0x00451BF8, 0x0008, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries,
        0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x004521BC },
    },
    {
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)s_editLightText_PointerWord,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugAmbientColorLabel.redTextPointer,
        (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText, (unsigned int)g_menuPaged_Pak_SyncAmbientRed,
        (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_ambGreenTextPointer, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText,
        (unsigned int)g_menuPaged_Pak_SyncAmbientGreen, (unsigned int)g_menuPaged_Menu_TryCreateMenu,
        0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)&g_debugDirectionalColorLabel, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText,
        (unsigned int)g_menuPaged_Pak_SyncAmbientBlue, (unsigned int)g_menuPaged_Menu_TryCreateMenu,
        0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_debugDirectionalColorLabel.redTextPointer,
        (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText, (unsigned int)g_menuPaged_Pak_SyncDirectionalRed,
        (unsigned int)g_menuPaged_Menu_TryCreateMenu, 0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_dirGreenTextPointer, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText,
        (unsigned int)g_menuPaged_Pak_SyncDirectionalGreen, (unsigned int)g_menuPaged_Menu_TryCreateMenu,
        0x00000000 },
        { 0x0002, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_SAllregionstextEncodedWords, (unsigned int)g_menuPaged_Menu_DrawLayeredMenuText,
        (unsigned int)g_menuPaged_Pak_SyncDirectionalBlue, (unsigned int)g_menuPaged_Menu_TryCreateMenu,
        0x00000000 },
    },
    {
        { 0x00451D3C, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries,
        0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x004521BC },
    },
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08002001, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, 0x800D7DB4,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_volumeZeroValueLabelFixed,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Pak_UpdateMusicVolumeLabel,
        (unsigned int)g_menuPaged_Pak_AdjustMusicVolume, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_sfxVolumeText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Pak_FormatSoundEffectsVolume,
        (unsigned int)g_menuPaged_Pak_AdjustSoundEffectsVolume, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_speechVolumeText,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Pak_UpdateSpeechVolumeLabel,
        (unsigned int)g_menuPaged_Pak_AdjustSpeechVolume, 0x00000000 },
        { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_musicPreviewFixedValueText, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
        (unsigned int)g_menuPaged_Pak_FormatMusicPreview, (unsigned int)g_menuPaged_Pak_SelectMusicPreview,
        0x00000000 },
        { 0x0000, 0x0000, 0x00410401, 0x0000, 0x0044, 0x00, 0x00, 0xFF, 0x01, 0x800D765C,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)g_menuPaged_Pak_RestoreAudioAndCloseMenu, 0x00000000 },
    },
    {
        { 0x00451E5C, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries,
        0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385,
        (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_redBloodScoreText[8],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_redBloodScoreText[12],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)g_menuPaged_Pak_ResumeMenuAudio,
        0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_redBloodScoreText[16],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)g_menuPaged_Pak_ReturnCallbackSuccess, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_redBloodScoreText[24],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        ((unsigned int)Pak_AllocateMenuFirst - 0x80000000U), 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_redBloodScoreText[32],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        ((unsigned int)Pak_AllocateMenuSecond - 0x80000000U), 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7DB4,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        (unsigned int)g_menuPaged_Pak_OpenMusicPreviewMenu, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_optionLabelSlots[3],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        ((unsigned int)Pak_AllocateMenuThird - 0x80000000U), 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_redBloodScoreText[36],
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        ((unsigned int)Pak_AllocateMenuFourth - 0x80000000U), 0x00000000 },
        { 0x0000, 0x0000, 0x00410101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_ownerModePersonViewText,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, (unsigned int)g_menuPaged_Pak_UpdateOwnerModeText,
        (unsigned int)g_menuPaged_Pak_ToggleOwnerMode, 0x00000000 },
        { 0x0000, 0x0000, 0x00410101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_ownerNotificationEnabledLabels, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText,
        (unsigned int)g_menuPaged_Pak_UpdateOwnerNotificationOptionText,
        (unsigned int)g_menuPaged_Pak_AdjustOwnerNotificationOption, 0x00000000 },
        { 0x0000, 0x0000, 0x00410101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_menuChoiceEnabledLabels,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, (unsigned int)g_menuPaged_Pak_UpdateMenuChoiceText,
        (unsigned int)g_menuPaged_Pak_AdjustMenuChoice, 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_editFogTextPointer, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText,
        0x00000000, ((unsigned int)Pak_OpenMenuChoiceFirstMenu - 0x80000000U), 0x00000000 },
        { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (unsigned int)s_editLightText_PointerWord,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        ((unsigned int)Pak_OpenMenuChoiceSecondMenu - 0x80000000U), 0x00000000 },
        { 0x0000, 0x0000, 0x00410101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01,
        (unsigned int)g_textureVariationBypassDisabledLabels, (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText,
        (unsigned int)g_menuPaged_Pak_UpdateTextureVariationBypassText,
        (unsigned int)g_menuPaged_Pak_ToggleTextureVariationBypass, 0x00000000 },
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D76F4,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000,
        ((unsigned int)Pak_AllocateMenuFifth - 0x80000000U), 0x00000000 },
    },
    {
        { 0x00451F7C, 0x0010, 0x0000, (unsigned int)g_menuPaged_Pak_EnterPlayerOptions,
        (unsigned int)g_menuPaged_Pak_RestoreControllerSetup, (unsigned int)g_menuPaged_Pak_RenderMenuEntryCallback,
        0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 },
    },
    {
        { 0x0000, 0x0000, 0x00000041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7A5C,
        (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)g_playerNameBufferPointers,
        (unsigned int)g_menuPaged_Setup_DrawNameCursor, (unsigned int)g_menuPaged_Setup_UpdateNameCursor, 0x00000000,
        0x00000000 },
        { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_playerNameBufferPointers[1],
        (unsigned int)g_menuPaged_Setup_DrawNameCursor, (unsigned int)g_menuPaged_Setup_UpdateNameCursor, 0x00000000,
        0x00000000 },
        { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_playerNameBufferPointers[2],
        (unsigned int)g_menuPaged_Setup_DrawNameCursor, (unsigned int)g_menuPaged_Setup_UpdateNameCursor, 0x00000000,
        0x00000000 },
        { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (unsigned int)&g_playerNameBufferPointers[3],
        (unsigned int)g_menuPaged_Setup_DrawNameCursor, (unsigned int)g_menuPaged_Setup_UpdateNameCursor, 0x00000000,
        0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x000A, 0x07, 0x01, 0x20, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 4),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 12),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 20),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 28),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 36),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 44),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 52),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0x20, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 60),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 68),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 76),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 84),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 92),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 100),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 108),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 116),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 124),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 132),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 140),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 148),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 156),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 164),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 172),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 180),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 188),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 196),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 204),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 212),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 220),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 228),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 236),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 244),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, ((unsigned int)&g_keyboardKeyLabelWords + 252),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0xE0, ((unsigned int)&g_keyboardKeyLabelWords + 260),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, ((unsigned int)&g_keyboardKeyLabelWords + 268),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, ((unsigned int)&g_keyboardKeyLabelWords + 276),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, ((unsigned int)&g_keyboardKeyLabelWords + 284),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, ((unsigned int)&g_keyboardKeyLabelWords + 292),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_AppendNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, ((unsigned int)&g_keyboardKeyLabelWords + 300),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_DeleteNameCharacter, 0x00000000 },
        { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0xE0, ((unsigned int)&g_keyboardKeyLabelWords + 308),
        (unsigned int)g_menuPaged_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)g_menuPaged_Setup_CommitPlayerName, 0x00000000 },
    },
    {
        { 0x004521E0, 0x002D, 0x0000, (unsigned int)g_menuPaged_Setup_SetupNameSpinner, 0x00000000,
        (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)g_menuPaged_Setup_HasActiveGameCounters, 0x0005,
        0x0000, 0x0000, 0x0000, 0x00000000 },
    },
};

unsigned int g_menuSettingsDataTailTrailingWords[2] = {
    0x00000000, 0x0C706172,
};
#endif
