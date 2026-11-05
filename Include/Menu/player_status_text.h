#ifndef MENU_PLAYER_STATUS_TEXT_H
#define MENU_PLAYER_STATUS_TEXT_H
#include "types.h"
#include "Common/Lone/g_languageindex.h"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_playerStatusMessages[15][4];
#define playerStatusText(row) g_playerStatusMessages[row][g_languageIndex]
#else
extern char *g_playerStatusMessages[15];
#define playerStatusText(row) g_playerStatusMessages[row]
#endif
#endif
