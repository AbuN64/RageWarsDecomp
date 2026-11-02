#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

extern s32 Frontend_AcknowledgePage67Event(void);
extern s32 Frontend_ActivatePauseMenuAction(void);
extern s32 Frontend_ClearPage67ModeFlag(void);
extern s32 Frontend_ConsumeConfirmationEvent(void);
extern s32 Frontend_ConsumePauseMenuEvent(void);
extern s32 Frontend_CreatePauseConfirmation(struct Pair14 *window);
extern s32 Frontend_CreatePauseMenu(struct MenuWidget *root);
extern s32 Frontend_CreateTimedMenu(struct Pair14 *window);
extern s32 Frontend_DestroyPauseMenu(void);
extern char Frontend_DestroyPauseMenu_Address[];
extern s32 Frontend_FreePage67Screen(void);
extern s32 Frontend_HandlePage67Choice(void);
extern s32 Frontend_IgnorePage67Event(void);
extern s32 Frontend_ResumeMatchOnInput(void *first, void *second, u32 event, s32 value);
extern s32 Frontend_ReturnConfirmationEventZero(void);
extern s32 Frontend_ReturnPauseEventZero(void);
extern s32 Frontend_ReturnPauseEventZeroAlt(void);
extern s32 Frontend_SetPauseMenuInputMode(void);
extern s32 Frontend_UpdatePage67Exit(s32 unused0, s32 unused1, s32 event);
extern s32 Timed_DestroyPauseConfirmation(void);
extern s32 Timed_FinishPauseConfirmationTransition(s32 unused0, s32 unused1, s32 event);
extern s32 Timed_SetConfirmationInputMode(void);
extern s32 Timed_UpdateTimedScreen(void);
extern char g_Frontend_AcknowledgePage67EventPackedAddress24[];
extern char g_Frontend_ActivatePauseMenuActionPackedAddress24[];
extern char g_Frontend_ClearPage67ModeFlagPackedAddress24[];
extern char g_Frontend_ConsumeConfirmationEventPackedAddress24[];
extern char g_Frontend_ConsumePauseMenuEventPackedAddress24[];
extern char g_Frontend_CreatePauseConfirmationPackedAddress24[];
extern char g_Frontend_CreatePauseMenuPackedAddress24[];
extern char g_Frontend_CreateTimedMenuPackedAddress24[];
extern char g_Frontend_DestroyPauseMenuPackedAddress24[];
extern char g_Frontend_FreePage67ScreenPackedAddress24[];
extern char g_Frontend_HandlePage67ChoicePackedAddress24[];
extern char g_Frontend_IgnorePage67EventPackedAddress24[];
extern char g_Frontend_ResumeMatchOnInputPackedAddress24[];
extern char g_Frontend_ReturnConfirmationEventZeroPackedAddress24[];
extern char g_Frontend_ReturnPauseEventZeroAltPackedAddress24[];
extern char g_Frontend_ReturnPauseEventZeroPackedAddress24[];
extern char g_Frontend_SetPauseMenuInputModePackedAddress24[];
extern char g_Frontend_UpdatePage67ExitPackedAddress24[];
extern char g_Timed_DestroyPauseConfirmationPackedAddress24[];
extern char g_Timed_FinishPauseConfirmationTransitionPackedAddress24[];
extern char g_Timed_SetConfirmationInputModePackedAddress24[];
extern char g_Timed_UpdateTimedScreenPackedAddress24[];

#include "include_asm.h"

/* 800E5550.CPP */
/* ROM-grounded data: rodata/writable/800E5550 */
#if defined(VERSION_DE)
struct {
    void * g_pauseMenuState;
    void * g_pauseTimedMenu;
    s32 g_residentChoiceScreen;
} g_FrontendDestroypausemenuWords1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_FrontendDestroypausemenuWords1SizeCheck[(sizeof(g_FrontendDestroypausemenuWords1) == 12) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * g_pauseMenuState;
    void * g_pauseTimedMenu;
    s32 g_residentChoiceScreen;
} g_FrontendDestroypausemenuWords1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_FrontendDestroypausemenuWords1SizeCheck[(sizeof(g_FrontendDestroypausemenuWords1) == 12) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_pauseMenuState;
    void * g_pauseTimedMenu;
    s32 g_residentChoiceScreen;
} g_FrontendDestroypausemenuWords1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_FrontendDestroypausemenuWords1SizeCheck[(sizeof(g_FrontendDestroypausemenuWords1) == 12) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_pauseMenuState;
    void * g_pauseTimedMenu;
    s32 g_residentChoiceScreen;
} g_FrontendDestroypausemenuWords1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_FrontendDestroypausemenuWords1SizeCheck[(sizeof(g_FrontendDestroypausemenuWords1) == 12) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_pauseMenuState;
    void * g_pauseTimedMenu;
    s32 g_residentChoiceScreen;
} g_FrontendDestroypausemenuWords1 __attribute__((aligned(4))) = {
    0,
    0,
    0
};
typedef char g_FrontendDestroypausemenuWords1SizeCheck[(sizeof(g_FrontendDestroypausemenuWords1) == 12) ? 1 : -1];
#endif

/* 800E555C.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry eventHandlers0[9];
    ResidentEventHandlerEntry eventHandlers108[8];
    ResidentEventHandlerEntry eventHandlers204[8];
    u8 alignmentFill300[8];
} g_frontendDestroyPauseMenuRecord __attribute__((aligned(4))) = {
    { { 3591, 1, (ResidentEventHandler)(void *)((char *)&Frontend_SetPauseMenuInputMode - 0x80000000U) }, { 3592, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnPauseEventZeroAlt - 0x80000000U) }, { 3594, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnPauseEventZero - 0x80000000U) }, { 3590, 1, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePauseMenu - 0x80000000U) }, { 3587, 1, (ResidentEventHandler)(void *)&Frontend_DestroyPauseMenu_Address }, { 1, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ActivatePauseMenuAction - 0x80000000U) }, { 2, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumePauseMenuEvent - 0x80000000U) }, { 10, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ResumeMatchOnInput - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 31, (ResidentEventHandler)(void *)((char *)&Timed_SetConfirmationInputMode - 0x80000000U) }, { 3592, 31, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnConfirmationEventZero - 0x80000000U) }, { 3594, 31, (ResidentEventHandler)(void *)((char *)&Timed_FinishPauseConfirmationTransition - 0x80000000U) }, { 3590, 31, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePauseConfirmation - 0x80000000U) }, { 3587, 31, (ResidentEventHandler)(void *)((char *)&Timed_DestroyPauseConfirmation - 0x80000000U) }, { 1, 31, (ResidentEventHandler)(void *)((char *)&Timed_UpdateTimedScreen - 0x80000000U) }, { 2, 31, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumeConfirmationEvent - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 32, (ResidentEventHandler)(void *)((char *)&Frontend_ClearPage67ModeFlag - 0x80000000U) }, { 3592, 32, (ResidentEventHandler)(void *)((char *)&Frontend_IgnorePage67Event - 0x80000000U) }, { 3594, 32, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePage67Exit - 0x80000000U) }, { 3590, 32, (ResidentEventHandler)(void *)((char *)&Frontend_CreateTimedMenu - 0x80000000U) }, { 3587, 32, (ResidentEventHandler)(void *)((char *)&Frontend_FreePage67Screen - 0x80000000U) }, { 1, 32, (ResidentEventHandler)(void *)((char *)&Frontend_HandlePage67Choice - 0x80000000U) }, { 2, 32, (ResidentEventHandler)(void *)((char *)&Frontend_AcknowledgePage67Event - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0xe, 0x7, 0x0, 0x0, 0x0, 0x5 }
};
typedef char g_frontendDestroyPauseMenuRecordSizeCheck[(sizeof(g_frontendDestroyPauseMenuRecord) == 308) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry handlers[25];
    u32 alignmentFill[2];
} g_frontendDestroyPauseMenuRecord __attribute__((aligned(4))) = {
    { { 3591, 1, (ResidentEventHandler)(void *)&g_Frontend_SetPauseMenuInputModePackedAddress24 }, { 3592, 1, (ResidentEventHandler)(void *)&g_Frontend_ReturnPauseEventZeroAltPackedAddress24 }, { 3594, 1, (ResidentEventHandler)(void *)&g_Frontend_ReturnPauseEventZeroPackedAddress24 }, { 3590, 1, (ResidentEventHandler)(void *)&g_Frontend_CreatePauseMenuPackedAddress24 }, { 3587, 1, (ResidentEventHandler)(void *)&g_Frontend_DestroyPauseMenuPackedAddress24 }, { 1, 1, (ResidentEventHandler)(void *)&g_Frontend_ActivatePauseMenuActionPackedAddress24 }, { 2, 1, (ResidentEventHandler)(void *)&g_Frontend_ConsumePauseMenuEventPackedAddress24 }, { 10, 1, (ResidentEventHandler)(void *)&g_Frontend_ResumeMatchOnInputPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 }, { 3591, 31, (ResidentEventHandler)(void *)&g_Timed_SetConfirmationInputModePackedAddress24 }, { 3592, 31, (ResidentEventHandler)(void *)&g_Frontend_ReturnConfirmationEventZeroPackedAddress24 }, { 3594, 31, (ResidentEventHandler)(void *)&g_Timed_FinishPauseConfirmationTransitionPackedAddress24 }, { 3590, 31, (ResidentEventHandler)(void *)&g_Frontend_CreatePauseConfirmationPackedAddress24 }, { 3587, 31, (ResidentEventHandler)(void *)&g_Timed_DestroyPauseConfirmationPackedAddress24 }, { 1, 31, (ResidentEventHandler)(void *)&g_Timed_UpdateTimedScreenPackedAddress24 }, { 2, 31, (ResidentEventHandler)(void *)&g_Frontend_ConsumeConfirmationEventPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 }, { 3591, 32, (ResidentEventHandler)(void *)&g_Frontend_ClearPage67ModeFlagPackedAddress24 }, { 3592, 32, (ResidentEventHandler)(void *)&g_Frontend_IgnorePage67EventPackedAddress24 }, { 3594, 32, (ResidentEventHandler)(void *)&g_Frontend_UpdatePage67ExitPackedAddress24 }, { 3590, 32, (ResidentEventHandler)(void *)&g_Frontend_CreateTimedMenuPackedAddress24 }, { 3587, 32, (ResidentEventHandler)(void *)&g_Frontend_FreePage67ScreenPackedAddress24 }, { 1, 32, (ResidentEventHandler)(void *)&g_Frontend_HandlePage67ChoicePackedAddress24 }, { 2, 32, (ResidentEventHandler)(void *)&g_Frontend_AcknowledgePage67EventPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x00000000, 0x00800000 }
};
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    ResidentEventHandlerEntry eventHandlers0[9];
    ResidentEventHandlerEntry eventHandlers108[8];
    ResidentEventHandlerEntry eventHandlers204[8];
    u8 alignmentFill300[8];
} g_frontendDestroyPauseMenuRecord __attribute__((aligned(4))) = {
    { { 3591, 1, (ResidentEventHandler)(void *)((char *)&Frontend_SetPauseMenuInputMode - 0x80000000U) }, { 3592, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnPauseEventZeroAlt - 0x80000000U) }, { 3594, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnPauseEventZero - 0x80000000U) }, { 3590, 1, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePauseMenu - 0x80000000U) }, { 3587, 1, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyPauseMenu - 0x80000000U) }, { 1, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ActivatePauseMenuAction - 0x80000000U) }, { 2, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumePauseMenuEvent - 0x80000000U) }, { 10, 1, (ResidentEventHandler)(void *)((char *)&Frontend_ResumeMatchOnInput - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 31, (ResidentEventHandler)(void *)((char *)&Timed_SetConfirmationInputMode - 0x80000000U) }, { 3592, 31, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnConfirmationEventZero - 0x80000000U) }, { 3594, 31, (ResidentEventHandler)(void *)((char *)&Timed_FinishPauseConfirmationTransition - 0x80000000U) }, { 3590, 31, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePauseConfirmation - 0x80000000U) }, { 3587, 31, (ResidentEventHandler)(void *)((char *)&Timed_DestroyPauseConfirmation - 0x80000000U) }, { 1, 31, (ResidentEventHandler)(void *)((char *)&Timed_UpdateTimedScreen - 0x80000000U) }, { 2, 31, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumeConfirmationEvent - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 32, (ResidentEventHandler)(void *)((char *)&Frontend_ClearPage67ModeFlag - 0x80000000U) }, { 3592, 32, (ResidentEventHandler)(void *)((char *)&Frontend_IgnorePage67Event - 0x80000000U) }, { 3594, 32, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePage67Exit - 0x80000000U) }, { 3590, 32, (ResidentEventHandler)(void *)((char *)&Frontend_CreateTimedMenu - 0x80000000U) }, { 3587, 32, (ResidentEventHandler)(void *)((char *)&Frontend_FreePage67Screen - 0x80000000U) }, { 1, 32, (ResidentEventHandler)(void *)((char *)&Frontend_HandlePage67Choice - 0x80000000U) }, { 2, 32, (ResidentEventHandler)(void *)((char *)&Frontend_AcknowledgePage67Event - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x8f, 0xa7, 0x0, 0x28, 0x24, 0x2, 0x0, 0x33 }
};
typedef char g_frontendDestroyPauseMenuRecordSizeCheck[(sizeof(g_frontendDestroyPauseMenuRecord) == 308) ? 1 : -1];
#endif
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
extern char g_Frontend_CreatePauseMenuPackedAddress242[];
extern char g_Frontend_DestroyPauseMenuPackedAddress242[];
extern char g_Frontend_SetPauseMenuInputModePackedAddress242[];
extern char g_Frontend_ReturnPauseEventZeroPackedAddress242[];
extern char g_Frontend_ReturnPauseEventZeroAltPackedAddress242[];
extern char g_Frontend_ResumeMatchOnInputPackedAddress242[];
extern char g_Frontend_ConsumePauseMenuEventPackedAddress242[];
extern char g_Frontend_ActivatePauseMenuActionPackedAddress242[];
#if defined(VERSION_US)
ResidentEventHandlerEntry g_FrontendDestroypausemenuPointerWords1[9] = {
    { 3591, 1, (ResidentEventHandler)(void *)&g_Frontend_SetPauseMenuInputModePackedAddress242 }, { 3592, 1, (ResidentEventHandler)(void *)&g_Frontend_ReturnPauseEventZeroAltPackedAddress242 }, { 3594, 1, (ResidentEventHandler)(void *)&g_Frontend_ReturnPauseEventZeroPackedAddress242 }, { 3590, 1, (ResidentEventHandler)(void *)&g_Frontend_CreatePauseMenuPackedAddress242 }, { 3587, 1, (ResidentEventHandler)(void *)&g_Frontend_DestroyPauseMenuPackedAddress242 }, { 1, 1, (ResidentEventHandler)(void *)&g_Frontend_ActivatePauseMenuActionPackedAddress242 }, { 2, 1, (ResidentEventHandler)(void *)&g_Frontend_ConsumePauseMenuEventPackedAddress242 }, { 10, 1, (ResidentEventHandler)(void *)&g_Frontend_ResumeMatchOnInputPackedAddress242 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_FrontendDestroypausemenuPointerWords1[9] = {
    { 3591, 1, (ResidentEventHandler)(void *)&g_Frontend_SetPauseMenuInputModePackedAddress242 }, { 3592, 1, (ResidentEventHandler)(void *)&g_Frontend_ReturnPauseEventZeroAltPackedAddress242 }, { 3594, 1, (ResidentEventHandler)(void *)&g_Frontend_ReturnPauseEventZeroPackedAddress242 }, { 3590, 1, (ResidentEventHandler)(void *)&g_Frontend_CreatePauseMenuPackedAddress242 }, { 3587, 1, (ResidentEventHandler)(void *)&g_Frontend_DestroyPauseMenuPackedAddress242 }, { 1, 1, (ResidentEventHandler)(void *)&g_Frontend_ActivatePauseMenuActionPackedAddress242 }, { 2, 1, (ResidentEventHandler)(void *)&g_Frontend_ConsumePauseMenuEventPackedAddress242 }, { 10, 1, (ResidentEventHandler)(void *)&g_Frontend_ResumeMatchOnInputPackedAddress242 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    ResidentEventHandlerEntry eventHandlers0[8];
    ResidentEventHandlerEntry eventHandlers96[8];
    u8 alignmentFill192[8];
} g_pauseMenuEventHandlerRecords __attribute__((aligned(4))) = {
    { { 3591, 31, (ResidentEventHandler)(void *)((char *)&Timed_SetConfirmationInputMode - 0x80000000U) }, { 3592, 31, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnConfirmationEventZero - 0x80000000U) }, { 3594, 31, (ResidentEventHandler)(void *)((char *)&Timed_FinishPauseConfirmationTransition - 0x80000000U) }, { 3590, 31, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePauseConfirmation - 0x80000000U) }, { 3587, 31, (ResidentEventHandler)(void *)((char *)&Timed_DestroyPauseConfirmation - 0x80000000U) }, { 1, 31, (ResidentEventHandler)(void *)((char *)&Timed_UpdateTimedScreen - 0x80000000U) }, { 2, 31, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumeConfirmationEvent - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { { 3591, 32, (ResidentEventHandler)(void *)((char *)&Frontend_ClearPage67ModeFlag - 0x80000000U) }, { 3592, 32, (ResidentEventHandler)(void *)((char *)&Frontend_IgnorePage67Event - 0x80000000U) }, { 3594, 32, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePage67Exit - 0x80000000U) }, { 3590, 32, (ResidentEventHandler)(void *)((char *)&Frontend_CreateTimedMenu - 0x80000000U) }, { 3587, 32, (ResidentEventHandler)(void *)((char *)&Frontend_FreePage67Screen - 0x80000000U) }, { 1, 32, (ResidentEventHandler)(void *)((char *)&Frontend_HandlePage67Choice - 0x80000000U) }, { 2, 32, (ResidentEventHandler)(void *)((char *)&Frontend_AcknowledgePage67Event - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x2e, 0x48, 0x1c, 0xf4, 0x0, 0x20, 0x43, 0x3a }
};
typedef char g_pauseMenuEventHandlerRecordsSizeCheck[(sizeof(g_pauseMenuEventHandlerRecords) == 200) ? 1 : -1];
#endif
#endif
