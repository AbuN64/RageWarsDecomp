#include "MENU/BUILD/DEFINITION_DATA.H"

#if defined(VERSION_US_REV1)
extern char g_menuPaged_Snapshot_SelectNote[];
extern char g_menuPaged_Snapshot_UpdateNoteLabel[];
extern char g_menuPaged_Menu_DrawMenuItemLabel[];

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
} g_menuItemFragment11 = {
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
