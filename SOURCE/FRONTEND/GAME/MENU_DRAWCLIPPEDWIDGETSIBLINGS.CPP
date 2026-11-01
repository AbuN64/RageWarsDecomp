#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "MENU/STATE.H"
#include "TYPES.H"
#include "UI/QUAG/N64_ENG.H"
#if defined(VERSION_EU_X)
/* 80408AC4_14.CPP */
/* 80406A88_8.CPP */
extern void Node_LoadLanguageStringsIfAny(int);
extern void *g_optionsPage;
int Menu_DestroyEuxOptionsAndReloadLanguage(void) {
    Cache_FreeMemory(g_optionsPage);
    g_optionsPage = 0;
    Node_LoadLanguageStringsIfAny(g_languageIndex);
    return 0;
}
#endif
