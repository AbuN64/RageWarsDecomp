#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

extern char Frontend_ActivateCompactOptionsPage[];
extern char Frontend_CloseCompactOptionsPage[];
extern char Frontend_CloseOptionsPage[];
extern char Frontend_CloseSettingsPage[];
extern char Frontend_ConsumeTabOptionsEvent[];
extern char Frontend_CreateGameOptionsScreen[];
extern char Frontend_DestroyCompactOptionsPage[];
extern char Frontend_DestroyTabOptionsPage[];
extern char Frontend_HandleCompactOptionsShortcut[];
extern char Frontend_HandleOptionsPageShortcut[];
extern char Frontend_HandleTabOptionsShortcut[];
extern char Frontend_SelectNextLanguage[];
extern char Frontend_SelectPreviousLanguage[];
extern char Frontend_UpdateOptionsPageExit[];
extern char Menu_AnimateTabOptionsMenu[];
extern char Menu_CreateLocalizedSettingsPage[];
extern char Menu_CreateSessionSettingsControls[];
extern char Menu_CreateSettingsPage[];
extern char Menu_FinishTabOptionsTransition[];
extern char Menu_OpenGameOptionsScreen[];
extern char Menu_OpenLocalizedGameOptions[];
extern char g_Frontend_ActivateCompactOptionsPagePackedAddress24[];
extern char g_Frontend_CloseCompactOptionsPagePackedAddress24[];
extern char g_Frontend_CloseOptionsPagePackedAddress24[];
extern char g_Frontend_DestroyCompactOptionsPagePackedAddress24[];
extern char g_Frontend_DestroyTabOptionsPagePackedAddress24[];
extern char g_Frontend_HandleCompactOptionsShortcutPackedAddress24[];
extern char g_Frontend_HandleOptionsPageShortcutPackedAddress24[];
extern char g_Frontend_HandleTabOptionsShortcutPackedAddress24[];
extern char g_Frontend_TabOptionsEvent02PlayModeEvent01HandlerPackedAddress24[];
extern char g_Frontend_UpdateOptionsPageExitPackedAddress24[];
extern int Menu_DestroyEuxOptionsAndReloadLanguage(void);
extern char g_Menu_AnimateTabOptionsMenuPackedAddress24[];
extern char g_Menu_CreateEuropeanSettingsPagePackedAddress24[];
extern char g_Menu_CreateSessionSettingsControlsPackedAddress24[];
extern char g_Menu_DestroyOptionsPagePackedAddress24[];
extern char g_Menu_FinishTabOptionsTransitionPackedAddress24[];
extern char g_Menu_OpenLocalizedGameOptionsPackedAddress24[];

#include "include_asm.h"
#include "DATA/OVLTBL/OPTIONS_CREATEOPTIONSPAGE_DATA.H"

/* 800E4504_2.CPP */
/* ROM-grounded data: rodata/writable/800E4510 */
#if defined(VERSION_DE)
struct {
    void * g_optionsPage;
    void * g_gameOptionsScreenState;
    void * g_optionsShortcutScreen;
} g_OptionsCreateoptionspageEncodedWordsBlock1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_OptionsCreateoptionspageEncodedWordsBlock1SizeCheck[(sizeof(g_OptionsCreateoptionspageEncodedWordsBlock1) == 12) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * g_optionsPage;
    void * g_gameOptionsScreenState;
    void * g_optionsShortcutScreen;
} g_OptionsCreateoptionspageEncodedWordsBlock1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_OptionsCreateoptionspageEncodedWordsBlock1SizeCheck[(sizeof(g_OptionsCreateoptionspageEncodedWordsBlock1) == 12) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_optionsPage;
    void * g_gameOptionsScreenState;
    void * g_optionsShortcutScreen;
} g_OptionsCreateoptionspageEncodedWordsBlock1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_OptionsCreateoptionspageEncodedWordsBlock1SizeCheck[(sizeof(g_OptionsCreateoptionspageEncodedWordsBlock1) == 12) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_optionsPage;
    void * g_gameOptionsScreenState;
    void * g_optionsShortcutScreen;
} g_OptionsCreateoptionspageEncodedWordsBlock1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_OptionsCreateoptionspageEncodedWordsBlock1SizeCheck[(sizeof(g_OptionsCreateoptionspageEncodedWordsBlock1) == 12) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_optionsPage;
    void * g_gameOptionsScreenState;
    void * g_optionsShortcutScreen;
} g_OptionsCreateoptionspageEncodedWordsBlock1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_OptionsCreateoptionspageEncodedWordsBlock1SizeCheck[(sizeof(g_OptionsCreateoptionspageEncodedWordsBlock1) == 12) ? 1 : -1];
#endif

/* 800E451C.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#if defined(VERSION_DE)
ResidentEventHandlerEntry D_src_4b23fe05[19] = {
    { 3592, 4, (ResidentEventHandler)(void *)((char *)&Frontend_UpdateOptionsPageExit - 0x80000000U) }, { 3590, 4, (ResidentEventHandler)(void *)((char *)&Menu_CreateSettingsPage - 0x80000000U) }, { 3587, 4, (ResidentEventHandler)(void *)((char *)&Frontend_CloseSettingsPage - 0x80000000U) }, { 2, 4, (ResidentEventHandler)(void *)((char *)&Frontend_CloseOptionsPage - 0x80000000U) }, { 1, 4, (ResidentEventHandler)(void *)((char *)&Frontend_HandleOptionsPageShortcut - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 }, { 3592, 11, (ResidentEventHandler)(void *)((char *)&Frontend_ActivateCompactOptionsPage - 0x80000000U) }, { 3590, 11, (ResidentEventHandler)(void *)((char *)&Frontend_CreateGameOptionsScreen - 0x80000000U) },
    { 3587, 11, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyCompactOptionsPage - 0x80000000U) }, { 2, 11, (ResidentEventHandler)(void *)((char *)&Frontend_CloseCompactOptionsPage - 0x80000000U) }, { 1, 11, (ResidentEventHandler)(void *)((char *)&Frontend_HandleCompactOptionsShortcut - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 }, { 3592, 22, (ResidentEventHandler)(void *)((char *)&Menu_AnimateTabOptionsMenu - 0x80000000U) }, { 3594, 22, (ResidentEventHandler)(void *)((char *)&Menu_FinishTabOptionsTransition - 0x80000000U) }, { 3590, 22, (ResidentEventHandler)(void *)((char *)&Menu_OpenGameOptionsScreen - 0x80000000U) }, { 3587, 22, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyTabOptionsPage - 0x80000000U) },
    { 2, 22, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumeTabOptionsEvent - 0x80000000U) }, { 1, 22, (ResidentEventHandler)(void *)((char *)&Frontend_HandleTabOptionsShortcut - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
ResidentEventHandlerEntry D_src_4b23fe05[19] = {
    { 3592, 4, (ResidentEventHandler)(void *)&g_Frontend_UpdateOptionsPageExitPackedAddress24 }, { 3590, 4, (ResidentEventHandler)(void *)&g_Menu_CreateEuropeanSettingsPagePackedAddress24 }, { 3587, 4, (ResidentEventHandler)(void *)&g_Menu_DestroyOptionsPagePackedAddress24 }, { 2, 4, (ResidentEventHandler)(void *)&g_Frontend_CloseOptionsPagePackedAddress24 }, { 1, 4, (ResidentEventHandler)(void *)&g_Frontend_HandleOptionsPageShortcutPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 }, { 3592, 11, (ResidentEventHandler)(void *)&g_Frontend_ActivateCompactOptionsPagePackedAddress24 }, { 3590, 11, (ResidentEventHandler)(void *)&g_Menu_CreateSessionSettingsControlsPackedAddress24 },
    { 3587, 11, (ResidentEventHandler)(void *)&g_Frontend_DestroyCompactOptionsPagePackedAddress24 }, { 2, 11, (ResidentEventHandler)(void *)&g_Frontend_CloseCompactOptionsPagePackedAddress24 }, { 1, 11, (ResidentEventHandler)(void *)&g_Frontend_HandleCompactOptionsShortcutPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 }, { 3592, 22, (ResidentEventHandler)(void *)&g_Menu_AnimateTabOptionsMenuPackedAddress24 }, { 3594, 22, (ResidentEventHandler)(void *)&g_Menu_FinishTabOptionsTransitionPackedAddress24 }, { 3590, 22, (ResidentEventHandler)(void *)&g_Menu_OpenLocalizedGameOptionsPackedAddress24 }, { 3587, 22, (ResidentEventHandler)(void *)&g_Frontend_DestroyTabOptionsPagePackedAddress24 },
    { 2, 22, (ResidentEventHandler)(void *)&g_Frontend_TabOptionsEvent02PlayModeEvent01HandlerPackedAddress24 }, { 1, 22, (ResidentEventHandler)(void *)&g_Frontend_HandleTabOptionsShortcutPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    ResidentEventHandlerEntry eventHandlers0[8];
    ResidentEventHandlerEntry eventHandlers96[6];
    ResidentEventHandlerEntry eventHandlers168[7];
    u8 alignmentFill252[8];
} D_src_4b23fe05 __attribute__((aligned(4))) = {
    { { 3592, 4, (ResidentEventHandler)(void *)((char *)&Frontend_UpdateOptionsPageExit - 0x80000000U) }, { 3590, 4, (ResidentEventHandler)(void *)((char *)&Menu_CreateLocalizedSettingsPage - 0x80000000U) }, { 3587, 4, (ResidentEventHandler)(void *)((char *)&Menu_DestroyEuxOptionsAndReloadLanguage - 0x80000000U) }, { 2, 4, (ResidentEventHandler)(void *)((char *)&Frontend_CloseOptionsPage - 0x80000000U) }, { 1, 4, (ResidentEventHandler)(void *)((char *)&Frontend_HandleOptionsPageShortcut - 0x80000000U) }, { 8, 93, (ResidentEventHandler)(void *)((char *)&Frontend_SelectNextLanguage - 0x80000000U) }, { 7, 93, (ResidentEventHandler)(void *)((char *)&Frontend_SelectPreviousLanguage - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3592, 11, (ResidentEventHandler)(void *)((char *)&Frontend_ActivateCompactOptionsPage - 0x80000000U) }, { 3590, 11, (ResidentEventHandler)(void *)((char *)&Menu_CreateSessionSettingsControls - 0x80000000U) }, { 3587, 11, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyCompactOptionsPage - 0x80000000U) }, { 2, 11, (ResidentEventHandler)(void *)((char *)&Frontend_CloseCompactOptionsPage - 0x80000000U) }, { 1, 11, (ResidentEventHandler)(void *)((char *)&Frontend_HandleCompactOptionsShortcut - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3592, 22, (ResidentEventHandler)(void *)((char *)&Menu_AnimateTabOptionsMenu - 0x80000000U) }, { 3594, 22, (ResidentEventHandler)(void *)((char *)&Menu_FinishTabOptionsTransition - 0x80000000U) }, { 3590, 22, (ResidentEventHandler)(void *)((char *)&Menu_OpenLocalizedGameOptions - 0x80000000U) }, { 3587, 22, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyTabOptionsPage - 0x80000000U) }, { 2, 22, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumeTabOptionsEvent - 0x80000000U) }, { 1, 22, (ResidentEventHandler)(void *)((char *)&Frontend_HandleTabOptionsShortcut - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0xe, 0x3, 0x0, 0x0, 0x0, 0x1f }
};
typedef char D_src_4b23fe05SizeCheck[(sizeof(D_src_4b23fe05) == 260) ? 1 : -1];
#endif
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
#if defined(VERSION_US)
ResidentEventHandlerEntry g_OptionsCreateoptionspageEncodedWords[1] = {
    { 3592, 4, (ResidentEventHandler)(void *)&g_frontend_UpdateOptionsPageExitEntry }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_OptionsCreateoptionspageEncodedWords[1] = {
    { 3592, 4, (ResidentEventHandler)(void *)&g_frontend_UpdateOptionsPageExitEntry }
};
#endif
#endif

#if defined(VERSION_US)
extern char g_Menu_DispatchOptionsTransitionEventAddress[];
extern char g_frontend_UpdateOptionsPageExitEntry[];
extern char g_Frontend_DispatchOptionsPageEventAddress[];
extern char g_Frontend_DispatchCompactOptionsEventAddress[];
#if defined(VERSION_US)
ResidentEventHandlerEntry g_optionsCreateOptionsPageEntryTriples[18] = {
    { 3590, 4, (ResidentEventHandler)(void *)(g_Menu_DispatchOptionsTransitionEventAddress + 148) }, { 3587, 4, (ResidentEventHandler)(void *)(g_Menu_DispatchOptionsTransitionEventAddress + 3936) }, { 2, 4, (ResidentEventHandler)(void *)(g_frontend_UpdateOptionsPageExitEntry + 316) }, { 1, 4, (ResidentEventHandler)(void *)(g_frontend_UpdateOptionsPageExitEntry + 124) }, { 0, 0, (ResidentEventHandler)0 }, { 3592, 11, (ResidentEventHandler)(void *)(g_Frontend_DispatchOptionsPageEventAddress + 604) }, { 3590, 11, (ResidentEventHandler)(void *)(g_Frontend_DispatchOptionsPageEventAddress + 144) }, { 3587, 11, (ResidentEventHandler)(void *)(g_Frontend_DispatchOptionsPageEventAddress + 548) },
    { 2, 11, (ResidentEventHandler)(void *)(g_Frontend_DispatchOptionsPageEventAddress + 860) }, { 1, 11, (ResidentEventHandler)(void *)(g_Frontend_DispatchOptionsPageEventAddress + 656) }, { 0, 0, (ResidentEventHandler)0 }, { 3592, 22, (ResidentEventHandler)(void *)(g_Menu_DispatchOptionsTransitionEventAddress + 2520) }, { 3594, 22, (ResidentEventHandler)(void *)(g_Menu_DispatchOptionsTransitionEventAddress + 1956) }, { 3590, 22, (ResidentEventHandler)(void *)(g_Menu_DispatchOptionsTransitionEventAddress + 684) }, { 3587, 22, (ResidentEventHandler)(void *)(g_Frontend_DispatchCompactOptionsEventAddress + 144) }, { 2, 22, (ResidentEventHandler)(void *)(g_Frontend_DispatchCompactOptionsEventAddress + 568) },
    { 1, 22, (ResidentEventHandler)(void *)(g_Frontend_DispatchCompactOptionsEventAddress + 208) }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
