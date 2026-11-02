#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

extern char Frontend_ApplyModeChoice[];
extern char Frontend_ConsumePlayModeEvent[];
extern char Frontend_DestroyPlayModeMenu[];
extern char Frontend_HandlePlayModeShortcut[];
extern char Frontend_InitPlayModeMenu[];
extern char Frontend_UpdatePlayModeMenu[];

#include "include_asm.h"
#include "DATA/SCENARIO_SETUP/FRONTEND_APPLYMODECHOICE_DATA.H"

/* 800E4600.CPP */
/* ROM-grounded data: rodata/writable/800E4600 */
#if defined(VERSION_DE)
struct {
    void * g_playModeMenuState;
} g_FrontendApplymodechoiceWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendApplymodechoiceWords1SizeCheck[(sizeof(g_FrontendApplymodechoiceWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * g_playModeMenuState;
} g_FrontendApplymodechoiceWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendApplymodechoiceWords1SizeCheck[(sizeof(g_FrontendApplymodechoiceWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_playModeMenuState;
} g_FrontendApplymodechoiceWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendApplymodechoiceWords1SizeCheck[(sizeof(g_FrontendApplymodechoiceWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_playModeMenuState;
} g_FrontendApplymodechoiceWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendApplymodechoiceWords1SizeCheck[(sizeof(g_FrontendApplymodechoiceWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_playModeMenuState;
} g_FrontendApplymodechoiceWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendApplymodechoiceWords1SizeCheck[(sizeof(g_FrontendApplymodechoiceWords1) == 4) ? 1 : -1];
#endif

/* 800E4604.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char *g_playerSettingsFirstChoiceText[];
extern char *g_playerSettingsSecondChoiceText[];
extern char g_playerSettingsSlotNumberFormat[];
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry eventHandlers0[7];
    void * links84[10];
} D_src_6bb6ec48 __attribute__((aligned(4))) = {
    { { 3592, 3, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePlayModeMenu - 0x80000000U) }, { 3590, 3, (ResidentEventHandler)(void *)((char *)&Frontend_InitPlayModeMenu - 0x80000000U) }, { 3587, 3, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyPlayModeMenu - 0x80000000U) }, { 2, 3, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumePlayModeEvent - 0x80000000U) }, { 1, 3, (ResidentEventHandler)(void *)((char *)&Frontend_ApplyModeChoice - 0x80000000U) }, { 10, 3, (ResidentEventHandler)(void *)((char *)&Frontend_HandlePlayModeShortcut - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { (void *)&g_playerSettingsSecondChoiceText, (void *)&g_playerSettingsFirstChoiceText, (void *)g_playerSettingsSlotNumberFormat + 0x4, (void *)g_playerSettingsSlotNumberFormat + 0x10, (void *)g_playerSettingsSlotNumberFormat + 0xC, (void *)g_playerSettingsSlotNumberFormat + 0x8, (void *)g_playerSettingsSlotNumberFormat + 0xC, (void *)g_playerSettingsSlotNumberFormat + 0x8, (void *)g_playerSettingsSlotNumberFormat + 0x10, (void *)g_playerSettingsSlotNumberFormat + 0x4 }
};
typedef char D_src_6bb6ec48SizeCheck[(sizeof(D_src_6bb6ec48) == 124) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU)
extern s32 g_playerSettingsSlotNumberTranslations[];
unsigned int D_src_6bb6ec48[31] = {
    0x00000E08, 0x00000003, 0x0042495C, 0x00000E06, 0x00000003, 0x004241E0, 0x00000E03, 0x00000003,
    0x0042492C, 0x00000002, 0x00000003, 0x00424AC8, 0x00000001, 0x00000003, 0x004246E8, 0x0000000A,
    0x00000003, 0x00424A74, 0x00000000, 0x00000000, 0x00000000, 0x97150000, 0x4A19CE6C, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x10,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x40, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x30, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x20, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x30, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x20, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x40, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x10,
};
#endif
#if defined(VERSION_EU_X)
extern s32 g_playerSettingsSlotNumberTranslations[];
unsigned int D_src_6bb6ec48[31] = {
    0x00000E08, 0x00000003, 0x00424AAC, 0x00000E06, 0x00000003, 0x00424330, 0x00000E03, 0x00000003,
    0x00424A7C, 0x00000002, 0x00000003, 0x00424C18, 0x00000001, 0x00000003, 0x00424838, 0x0000000A,
    0x00000003, 0x00424BC4, 0x00000000, 0x00000000, 0x00000000, 0x00000E03, 0x00000020, (unsigned int)g_playerSettingsSlotNumberTranslations + 0xC,
    (unsigned int)g_playerSettingsSlotNumberTranslations + 0x30, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x24, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x18, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x24, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x18, (unsigned int)g_playerSettingsSlotNumberTranslations + 0x30, (unsigned int)g_playerSettingsSlotNumberTranslations + 0xC,
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
#if defined(VERSION_US)
ResidentEventHandlerEntry g_FrontendApplymodechoicePointerWords1[1] = {
    { 3592, 3, (ResidentEventHandler)(void *)&g_Frontend_UpdatePlayModeMenuPackedAddress24_FrontendApplymodechoiceData }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_FrontendApplymodechoicePointerWords1[1] = {
    { 3592, 3, (ResidentEventHandler)(void *)&g_Frontend_UpdatePlayModeMenuPackedAddress24_FrontendApplymodechoiceData }
};
#endif
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
extern char g_playerSettingsSlotNumberFormat[];
unsigned int g_frontendApplyModeChoiceEventHandlerRecords[28] = {
    0x00000E06, 0x00000003, 0x00423C20, 0x00000E03, 0x00000003, 0x0042436C, 0x00000002, 0x00000003,
    0x00424508, 0x00000001, 0x00000003, 0x00424128, 0x0000000A, 0x00000003, 0x004244B4, 0x00000000,
    0x00000000, 0x00000000, 0x00660000, 0x00040000, (unsigned int)g_playerSettingsSlotNumberFormat + 0x4, (unsigned int)g_playerSettingsSlotNumberFormat + 0x10, (unsigned int)g_playerSettingsSlotNumberFormat + 0xC, (unsigned int)g_playerSettingsSlotNumberFormat + 0x8,
    (unsigned int)g_playerSettingsSlotNumberFormat + 0xC, (unsigned int)g_playerSettingsSlotNumberFormat + 0x8, (unsigned int)g_playerSettingsSlotNumberFormat + 0x10, (unsigned int)g_playerSettingsSlotNumberFormat + 0x4,
};
#endif
#endif
