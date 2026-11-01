#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_Menu_ApplySoundSlidersPackedAddress24[];
extern char g_Menu_CancelSoundOptionsScreenPackedAddress24[];
extern char g_Menu_CancelSoundSliderPopupPackedAddress24[];
extern char g_Menu_ConfirmSoundOptionsScreenPackedAddress24[];
extern char g_Menu_ConfirmSoundSliderPopupPackedAddress24[];
extern char g_Menu_CreateSoundOptionsScreenPackedAddress24[];
extern char g_Menu_CreateSoundSlidersPackedAddress24[];
extern char g_Menu_FreeSoundOptionsScreenPackedAddress24[];
extern char g_Menu_FreeSoundSlidersPackedAddress24[];
extern char g_Menu_SoundOptionsReturnZeroPackedAddress24[];
extern char g_Menu_SoundSliderReturnZeroPackedAddress24[];
extern char g_Menu_UpdateSoundOptionsScreenPackedAddress24[];
#include "include_asm.h"
#include "DATA/OVL1_J/MENU_CREATESOUNDOPTIONSSCREEN_DATA.H"

/* g_MenuCreatesoundoptionsscreenWords1_MenuCreatesoundoptionsscreenData.CPP */
/* ROM-grounded data: rodata/writable/800E58A0 */
s32 g_MenuCreatesoundoptionsscreenWords1[2] = {
    0, 0,
};

/* g_MenuCreatesoundoptionsscreenPointerWords1_MenuCreatesoundoptionsscreenData.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char g_Achieve_DispatchResultsActorEventAddress[];
extern char g_Menu_DispatchSoundOptionsEventAddress[];
RestD_src_3cb405cbLayout499 D_src_3cb405cb = {
    { 3591, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 404),
    { 3592, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 412),
    { 3590, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 148),
    { 3587, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 356),
    { 2, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 760),
    { 1, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 684),
    { 0, 0, 0, 3591, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 336),
    { 3592, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 344),
    { 3590, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 144),
    { 3587, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 288),
    { 2, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 596),
    { 1, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 504),
    { 0, 0, 0 },
};
#endif
#if defined(VERSION_EU)
extern char g_Menu_SoundOptionsReturnZeroPackedAddress24[];
extern char g_Menu_UpdateSoundOptionsScreenPackedAddress24[];
extern char g_Menu_CreateSoundOptionsScreenPackedAddress24[];
extern char g_Menu_FreeSoundOptionsScreenPackedAddress24[];
extern char g_Menu_CancelSoundOptionsScreenPackedAddress24[];
extern char g_Menu_ConfirmSoundOptionsScreenPackedAddress24[];
extern char g_Menu_SoundSliderReturnZeroPackedAddress24[];
extern char g_Menu_ApplySoundSlidersPackedAddress24[];
extern char g_Menu_CreateSoundSlidersPackedAddress24[];
extern char g_Menu_FreeSoundSlidersPackedAddress24[];
extern char g_Menu_CancelSoundSliderPopupPackedAddress24[];
extern char g_Menu_ConfirmSoundSliderPopupPackedAddress24[];
RestD_src_3cb405cbLayout500 D_src_3cb405cb = {
    { 3591, 6 },
    (void *)&g_Menu_SoundOptionsReturnZeroPackedAddress24,
    { 3592, 6 },
    (void *)&g_Menu_UpdateSoundOptionsScreenPackedAddress24,
    { 3590, 6 },
    (void *)&g_Menu_CreateSoundOptionsScreenPackedAddress24,
    { 3587, 6 },
    (void *)&g_Menu_FreeSoundOptionsScreenPackedAddress24,
    { 2, 6 },
    (void *)&g_Menu_CancelSoundOptionsScreenPackedAddress24,
    { 1, 6 },
    { (void *)&g_Menu_ConfirmSoundOptionsScreenPackedAddress24, 0, 0, 0 },
    { 3591, 13 },
    (void *)&g_Menu_SoundSliderReturnZeroPackedAddress24,
    { 3592, 13 },
    (void *)&g_Menu_ApplySoundSlidersPackedAddress24,
    { 3590, 13 },
    (void *)&g_Menu_CreateSoundSlidersPackedAddress24,
    { 3587, 13 },
    (void *)&g_Menu_FreeSoundSlidersPackedAddress24,
    { 2, 13 },
    (void *)&g_Menu_CancelSoundSliderPopupPackedAddress24,
    { 1, 13 },
    { (void *)&g_Menu_ConfirmSoundSliderPopupPackedAddress24, 0, 0, 0 },
};
#endif
#if defined(VERSION_EU_X)
extern char g_Achieve_DispatchResultsActorEventAddress[];
extern char g_Menu_DispatchSoundOptionsEventAddress[];
RestD_src_3cb405cbLayout501 D_src_3cb405cb = {
    { 3591, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 400),
    { 3592, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 408),
    { 3590, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 144),
    { 3587, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 352),
    { 2, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 756),
    { 1, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 680),
    { 0, 0, 0, 3591, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 336),
    { 3592, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 344),
    { 3590, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 144),
    { 3587, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 288),
    { 2, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 596),
    { 1, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 504),
    { 0, 0, 0 },
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
RestMenuCreatesoundoptionsscreenPointerWords1Record502 g_MenuCreatesoundoptionsscreenPointerWords1 = {
    3591,
    6,
    (unsigned int)g_Menu_SoundOptionsReturnZeroPackedAddress24_MenuCreatesoundoptionsscreenData,
    3592,
    6,
    (unsigned int)g_Menu_UpdateSoundOptionsScreenPackedAddress24_MenuCreatesoundoptionsscreenData,
};
#endif

#if defined(VERSION_US)
extern char g_Achieve_DispatchResultsActorEventAddress[];
extern char g_Menu_UpdateSoundOptionsScreenPackedAddress24_MenuCreatesoundoptionsscreenData[];
extern char g_Menu_DispatchSoundOptionsEventAddress[];
RestMenuCreatesoundoptionsscreenPointerWordsTailUsLayout503 g_MenuCreatesoundoptionsscreenPointerWordsTailUs = {
    { 3590, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 148),
    { 3587, 6 },
    (unsigned int)(g_Achieve_DispatchResultsActorEventAddress + 356),
    { 2, 6 },
    (unsigned int)(g_Menu_UpdateSoundOptionsScreenPackedAddress24_MenuCreatesoundoptionsscreenData + 348),
    { 1, 6 },
    (unsigned int)(g_Menu_UpdateSoundOptionsScreenPackedAddress24_MenuCreatesoundoptionsscreenData + 272),
    { 0, 0, 0, 3591, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 336),
    { 3592, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 344),
    { 3590, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 144),
    { 3587, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 288),
    { 2, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 596),
    { 1, 13 },
    (unsigned int)(g_Menu_DispatchSoundOptionsEventAddress + 504),
    { 0, 0, 0 },
};
#endif
