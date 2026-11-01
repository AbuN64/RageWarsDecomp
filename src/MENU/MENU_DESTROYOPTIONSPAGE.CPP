#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* Releases the object g_optionsPage holds through Cache_FreeMemory, clears g_optionsPage and returns zero. */
extern void *g_optionsPage;

s32 Menu_DestroyOptionsPage(void) {
    Cache_FreeMemory(g_optionsPage);
    g_optionsPage = 0;
    return 0;
}
#endif
