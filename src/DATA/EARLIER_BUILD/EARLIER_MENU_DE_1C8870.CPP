#if defined(VERSION_DE)
#include "MENU/BUILD/DEFINITION_DATA.H"

extern char g_earlierMenuPaged_44029C[];
extern char g_earlierMenuPaged_4415B4[];
extern char g_earlierMenuPaged_443380[];
extern char g_earlierMenuPaged_4433B8[];
extern char g_earlierMenuDef_450E5C[];
extern struct MenuBuildItemData g_earlierMenuItems_450870[1];

struct MenuBuildItemData g_earlierMenuItems_450870[1] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450894 = { (unsigned int)g_earlierMenuItems_450870, 0x0001, 0x0000, (unsigned int)g_earlierMenuPaged_443380, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, (int)g_earlierMenuDef_450E5C };

struct MenuBuildDefinitionData g_earlierMenuDef_4508B8 = { (unsigned int)g_earlierMenuItems_450870, 0x0001, 0x0000, (unsigned int)g_earlierMenuPaged_4433B8, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
