#include "include_asm.h"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* 8042E080_15.CPP */
/* Enters the selected menu state and resolves the default destination from the game mode. */

extern void Tsmos_DeactivateControllerState(void);
void PAKInterface_BeginScreenExit(s32 focusEntry) {
    s32 unusedExitResult;

    Tsmos_DeactivateControllerState();
    g_pakProfileScreenState->ready = 5;
    g_pakProfileScreenState->timer = 4;
    g_pakProfileScreenState->focus = focusEntry;
    if (focusEntry == -2) {
        switch(g_gameSettings.controllerMode) {
        case 0:g_pakProfileScreenState->focus=7;break;
        case 2:g_pakProfileScreenState->focus=7;break;
        case 1:g_pakProfileScreenState->focus=9;break;
        case 3:g_pakProfileScreenState->focus=7;break;
        case 4:g_pakProfileScreenState->focus=10;break;
        }
    }
}

#if defined(VERSION_US)
char k_PakinterfaceBeginscreenexitEncodedWords[4] =
    "_DEA";
#endif

#if defined(VERSION_EU_X)
unsigned int k_PakinterfaceBeginscreenexitEncodedWordsBlock2[1] = {
    0x0000003E,
};
#endif

#if defined(VERSION_EU)
unsigned int k_PakinterfaceBeginscreenexitEncodedWordsBlock3[1] = {
    0x8C180FE8,
};
#endif

#if defined(VERSION_DE)
unsigned int k_PakinterfaceBeginscreenexitEncodedWordsBlock1[1] = {
    0x004360AC,
};
#endif

/* 8042E080_60.CPP */
/* Does nothing. Nothing in the cartridge image calls it or stores its address as a word. */
void PAKInterface_ReturnWithoutAction(void) {
}
