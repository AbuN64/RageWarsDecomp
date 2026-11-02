#include "MENU/BUILD/DEFINITION_DATA.H"

#if defined(VERSION_US_REV1)
extern char addrLow_Timer_UpdateOperationChoiceLabel[];
extern char addrLow_Timer_UpdateOwnerChannelLabel[];
extern char g_menuPaged_Snapshot_SelectNote[];
extern char g_menuPaged_Snapshot_UpdateNoteLabel[];
extern char g_menuPaged_Menu_DrawMenuItemLabel[];

struct {
    unsigned int resourceCallback1;
    unsigned int callback1;
    unsigned int initializeCallback1;
    unsigned int parameter1;
    struct MenuBuildItemData items1[3];
    short type1;
    unsigned short reserved021;
} g_menuItemFragment6 = {
    (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel,
    (unsigned int)addrLow_Timer_UpdateOwnerChannelLabel,
    0x00000000,
    0x00000000,
    {
        { 0x0000, 0x0000, 0x00010041, 0x0000, 0xFFF8, 0x00, 0x00, 0xFF, 0x01, 0x800D7768, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)addrLow_Timer_UpdateOperationChoiceLabel, 0x00000000, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0006, 0x00, 0x00, 0xFF, 0x01, 0x800D7714, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
        { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x800D7718, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)g_menuPaged_Snapshot_UpdateNoteLabel, (unsigned int)g_menuPaged_Snapshot_SelectNote, 0x00000000 },
    },
    0x0000,
    0x0000,
};
#endif
