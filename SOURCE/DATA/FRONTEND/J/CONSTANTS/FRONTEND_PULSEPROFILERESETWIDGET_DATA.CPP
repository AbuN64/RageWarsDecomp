#include "DATA/REST_SOURCE_RECORDS.H"
extern char Frontend_HandleProfileResetConfirm_Address[];
#include "include_asm.h"
#include "DATA/OVL1_J/FRONTEND_PULSEPROFILERESETWIDGET_DATA.H"

/* g_FrontendPulseprofileresetwidgetWords1_FrontendPulseprofileresetwidgetData.CPP */
/* ROM-grounded data: rodata/writable/800E5950 */
s32 g_FrontendPulseprofileresetwidgetWords1[1] = {
    0,
};

/* g_FrontendPulseprofileresetwidgetPointerWords1_FrontendPulseprofileresetwidgetData.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
extern char g_Menu_DispatchSoundSliderEventAddress[];
extern char Frontend_HandleProfileResetConfirm_Address[];
extern char g_Frontend_DispatchProfileResetEventAddress[];
RestD_src_9d8a2047Layout476 D_src_9d8a2047 = {
    { 3592, 24 },
    (unsigned int)(g_Menu_DispatchSoundSliderEventAddress + 476),
    { 3590, 24 },
    (unsigned int)(g_Menu_DispatchSoundSliderEventAddress + 148),
    { 3587, 24 },
    (unsigned int)(g_Menu_DispatchSoundSliderEventAddress + 428),
    { 1, 24 },
    (unsigned int)(Frontend_HandleProfileResetConfirm_Address + 96),
    { 2, 24 },
    (unsigned int)(Frontend_HandleProfileResetConfirm_Address + 64),
    { 10, 24 },
    { (void *)&Frontend_HandleProfileResetConfirm_Address, 0, 0, 0 },
    (unsigned int)(g_Frontend_DispatchProfileResetEventAddress + 1432),
    { 2, 3590, 33 },
    (unsigned int)(g_Frontend_DispatchProfileResetEventAddress + 1496),
    { 2, 33 },
    (unsigned int)(g_Frontend_DispatchProfileResetEventAddress + 1708),
    { 1, 33 },
    (unsigned int)(g_Frontend_DispatchProfileResetEventAddress + 1536),
    { 0, 0, 0 },
};
#endif
#if defined(VERSION_EU_X)
RestD_src_9d8a2047Layout477 D_src_9d8a2047 = {
    { 3592, 24, 4433448, 3590, 24, 4433120, 3587, 24, 4433400, 1, 24, 4433744, 2, 24, 4433712, 10, 24, 4433648, 0, 0, 0 },
    0xACC200B8,
    0xACC4000C,
    { 3590, 33, 4435248, 2, 33, 4435460, 1, 33, 4435288, 0, 0, 0 },
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
RestFrontendPulseprofileresetwidgetPointerWords1Record478 g_FrontendPulseprofileresetwidgetPointerWords1 = {
    3592,
    24,
    (unsigned int)g_Frontend_PulseProfileResetWidgetPackedAddress24_FrontendPulseprofileresetwidgetData,
    3590,
    24,
    (unsigned int)g_Frontend_CreateProfileResetScreenUsPackedAddress24,
    3587,
    24,
    (unsigned int)g_Frontend_FreeProfileResetScreenPackedAddress24_FrontendPulseprofileresetwidgetData,
    1,
    24,
    (unsigned int)g_ProfileReset_ReturnUnhandledEventPackedAddress24,
    2,
    24,
    (unsigned int)g_Frontend_AcknowledgeProfileResetEventPackedAddress24_FrontendPulseprofileresetwidgetData,
    10,
    24,
    (unsigned int)g_Frontend_HandleProfileResetConfirmPackedAddress24_FrontendPulseprofileresetwidgetData,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif

#if defined(VERSION_US)
RestFrontendPulseprofileresetwidgetPointerWordsTailUsLayout479 g_FrontendPulseprofileresetwidgetPointerWordsTailUs = {
    0x1CE20028,
    "C:\\P",
    { 3590, 33, 4431632, 2, 33, 4431844, 1, 33, 4431672, 0, 0, 0 },
};
#endif
