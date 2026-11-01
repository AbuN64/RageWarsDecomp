#include "include_asm.h"

#include "MENU/OPTIONEDITSTATE.H"
#include "TYPES.H"
#include "COMMON/SOUNDINFO.H"
#include "ENGINE/VOLUME.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VOLUME_MENU_RESOURCES.H"

/* 80444EC0_6.CPP */
/* Passes what SoundVoicePool_GetGlobalState returns to SoundVoicePool_Resume, then calls SoundElement_DisableMusicGainOverride and SoundElement_EnablePeriodicSound,
   and returns one. */
extern s32 SoundVoicePool_GetGlobalState();
struct SoundVoicePool;
extern void SoundVoicePool_Resume(struct SoundVoicePool *);

s32 Pak_ResumeMenuAudio(void) {
    SoundVoicePool_Resume(SoundVoicePool_GetGlobalState());
    SoundElement_DisableMusicGainOverride();
    SoundElement_EnablePeriodicSound();
    return 1;
}

/* Returns one. Nothing in the cartridge image calls it or stores its address as a word. */
s32 Pak_ReturnCallbackSuccess(void) {
    return 1;
}

/* 80444EC0_7.CPP */
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_pakAllocateMenuFirstResource,
   and returns one. */

s32 Pak_AllocateMenuFirst(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_pakAllocateMenuFirstResource);
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogRowThreeResource,
   and returns one. */

s32 Pak_AllocateMenuSecond(void *first, void *second, void *third) {
#if defined(VERSION_EU)
    Menu_AllocateMenu(third, second, g_pakAllocateMenuSecondResource_eu);
#elif defined(VERSION_EU_X)
    Menu_AllocateMenu(third, second, g_pakAllocateMenuSecondResource_eu_x);
#else
    Menu_AllocateMenu(third, second, g_initialDialogRowThreeResource);
#endif
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogRowOneResource,
   and returns one. */

s32 Pak_AllocateMenuThird(void *first, void *second, void *third) {
#if defined(VERSION_EU)
    Menu_AllocateMenu(third, second, g_initialDialogRowThreeResource);
#elif defined(VERSION_EU_X)
    Menu_AllocateMenu(third, second, g_initialDialogRowThreeResource);
#else
    Menu_AllocateMenu(third, second, g_initialDialogRowOneResource);
#endif
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogRowTwoResource,
   and returns one. */

s32 Pak_AllocateMenuFourth(void *first, void *second, void *third) {
#if defined(VERSION_EU)
    Menu_AllocateMenu(third, second, g_initialDialogRowOneResource);
#elif defined(VERSION_EU_X)
    Menu_AllocateMenu(third, second, g_initialDialogRowOneResource);
#else
    Menu_AllocateMenu(third, second, g_initialDialogRowTwoResource);
#endif
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_pakAllocateMenuFifthResource,
   and returns one. */

s32 Pak_AllocateMenuFifth(void *first, void *second, void *third) {
#if defined(VERSION_EU)
    Menu_AllocateMenu(third, second, g_initialDialogRowTwoResource);
#elif defined(VERSION_EU_X)
    Menu_AllocateMenu(third, second, g_initialDialogRowTwoResource);
#else
    Menu_AllocateMenu(third, second, g_pakAllocateMenuFifthResource);
#endif
    return 1;
}
#endif
