#include "include_asm.h"
#if defined(VERSION_DE)
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"
/* German Menu_DestroyOptionsPage: releases the object g_optionsPage holds through Cache_FreeMemory, clears
   g_optionsPage, reloads the default language strings and returns zero. */
extern void *g_optionsPage;
extern void Node_LoadLanguageStringsIfAny(s32);
s32 Frontend_CloseSettingsPage(void) {
    Cache_FreeMemory(g_optionsPage);
    g_optionsPage = 0;
    Node_LoadLanguageStringsIfAny(0);
    return 0;
}
#endif
