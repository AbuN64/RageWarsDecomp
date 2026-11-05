#if defined(VERSION_DE)
#include "Menu/menu_leftover_de_1c88e0.h"
#include "Menu/Build/definition_data.h"
#include "Menu/menu_leftover_de_1c8870.h"
#include "Menu/menu_leftover_de_1c8870_symbols.h"

// The callback column cells that hold 0x004xxxxx literals point into the older build's paged menu code, which none of the five ROMs holds.
struct MenuBuildItemData g_menuLeftover_de_1C8870[1] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)0x0044029C, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_menuLeftover_de_1C8894 = { (unsigned int)g_menuLeftover_de_1C8870, 0x0001, 0x0000, (unsigned int)0x00443380, 0x00000000, (unsigned int)0x004415B4, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, (int)((char *)&g_menuLeftover_de_1C8E5C) };

struct MenuBuildDefinitionData g_menuLeftover_de_1C88B8 = { (unsigned int)g_menuLeftover_de_1C8870, 0x0001, 0x0000, (unsigned int)0x004433B8, 0x00000000, (unsigned int)0x004415B4, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
