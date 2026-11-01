#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/WORLD.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/GLOBALS.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/STATEPAIR.H"
#include "RESMGR/TSMOS_SETIDLETIMER.H"
#include "COMMON/PLAYERPROFILES.H"
#if defined(VERSION_US_REV1)
/* 80408AC4_16.CPP */
/* 80408AC4_16.CPP */
/* 8043962C_11.CPP */
extern void Player_InitializeProfile(void *);
extern Pulse *g_profileResetScreen;
/* Initialize the pulse screen, its shared menu state, and player profiles. */
s32 Frontend_CreateProfileResetScreen(MenuWidget *tree) {
    s32 i;
    Shared_Game *settings;
    Shared_PlayerSettingsRecord *record;
    Shared_MenuObject *object;

    g_profileResetScreen = Cache_AllocateMemory(sizeof(*g_profileResetScreen));
    object = &g_playerViewRenderContext.object;
    Pools_ResetActorPools(object, 0);
    Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
    Scene_LoadLevelResources(&g_world, 0, 0);
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
    Frontend_RequestScreenMode(0);
    i = 7;
    Tsmos_DeactivateControllerState();
    record = &object->playerSettings[7];
    do {
        record->enabled = 0;
        i--;
        record--;
    } while (i >= 0);
    g_profileResetScreen->widget = Node_FindWidgetByResourceId(tree, 919);
    g_profileResetScreen->phase = 0;
    settings = &g_gameSettings;
    settings->laps = 10;
    settings->players = 10;
    for (i = 0; i < 4; i++) {
        Player_InitializeProfile(&g_localPlayerProfiles[i]);
    }
    Tsmos_SetIdleTimer(0.0f);
    return 0;
}
/* 80408CB0_17.CPP */
/* 80408CB0_17.CPP */
/* bigCheatActivatedTextData.CPP */
char s_bigCheatActivatedText[20] = "big cheat activated";
/* janesCheatActivatedTextData.CPP */
/* ROM-grounded data: rodata/unresolved/800E5CAC_unclaimed_E68DC */
void * g_GfxGetnormalizedcounterEncodedWords[1] = {
    (void *)&s_bigCheatActivatedText,
};
char s_janesCheatActivatedText[24] = "janes cheat activated";
/* gfxGetnormalizedcounterEncodedWordsTableData.CPP */
extern char g_cMenuProfile_ResetRoundEndDelayEntry[];
extern char addrLow_CMenuProfile_HasRoundProgress[];
extern char addrLow_CMenuProfile_SetFirstResultLabel[];
extern char addrLow_CMenuProfile_SetSecondResultLabel[];
extern char addrLow_CMenuProfile_ControllerSelectionReturnZero[];
extern char g_menuPaged_Menu_DrawMenuOptionSprite[];
extern char g_menuPaged_Menu_DrawMenuEntries[];
extern char g_menuPaged_Menu_DrawMenuItemLabel[];
unsigned int k_GfxGetnormalizedcounterEncodedWords[84] = {
    0x800E5CE0, 0x00000000, 0x8014641C, 0x801464B2, 0x80146548, 0x801465DE, 0x800E5D00, 0x800E5D04,
    0x800E5D08, 0x800E5D0C, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, 0x800D76C4,
    (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000028, 0x0000FF01,
    0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)addrLow_CMenuProfile_SetFirstResultLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000000F,
    0x0000FF01, 0x800D7E14, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, (unsigned int)addrLow_CMenuProfile_SetSecondResultLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041,
    0x00000023, 0x0000FF01, 0x800D76D0, (unsigned int)g_menuPaged_Menu_DrawMenuItemLabel, 0x00000000, (unsigned int)addrLow_CMenuProfile_ControllerSelectionReturnZero, 0x00000000, 0x800E5D20,
    0x00050000, (unsigned int)g_cMenuProfile_ResetRoundEndDelayEntry, 0x00000000, (unsigned int)g_menuPaged_Menu_DrawMenuEntries, (unsigned int)addrLow_CMenuProfile_HasRoundProgress, 0x00040000, 0x00000000, 0x00000000,
    0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0xFFFFFFFF,
    0x00000001, 0x00000001, 0x00000001, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
#endif
