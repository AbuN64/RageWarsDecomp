#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "COMMON/LONE/RESIDENT_CHOICE_SCREEN.H"
#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* Releases the object g_residentChoiceScreen holds through Cache_FreeMemory, clears g_residentChoiceScreen, calls Tsmos_SetModeOneFlag with 2
   and returns zero. */


s32 Frontend_FreePage67Screen(void) {
    Cache_FreeMemory(g_residentChoiceScreen);
    g_residentChoiceScreen = 0;
    Tsmos_SetModeOneFlag(2);
    return 0;
}
