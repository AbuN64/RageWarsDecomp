#include "DATA/REST_SOURCE_RECORDS.H"
extern char Player_FreeAlternatePlayerSettingsScreen_Address[];
extern char g_Player_AlternatePlayerSettingsEvent0E07HandlerPackedAddress24[];
extern char g_Player_AlternatePlayerSettingsEvent0E08HandlerPackedAddress24[];
extern char g_Player_CancelAlternatePlayerSettingsEntryPackedAddress24[];
extern char g_Player_CancelPlayerSettingsEntryPackedAddress24[];
extern char g_Player_ConfirmAlternatePlayerSettingsEntryPackedAddress24[];
extern char g_Player_ConfirmPlayerSettingsEntryPackedAddress24[];
extern char g_Player_FreeAlternatePlayerSettingsScreenPackedAddress24[];
extern char g_Player_FreePlayerSettingsScreenPackedAddress24[];
extern char g_Player_InitPlayerSettingsScreenPackedAddress24[];
extern char g_Player_OpenAlternatePlayerSettingsScreenPackedAddress24[];
extern char g_Player_PlayerSettingsEvent0AHandlerPackedAddress24[];
extern char g_Player_PlayerSettingsEvent0E07HandlerPackedAddress24[];
extern char g_Player_SelectNextAlternatePlayerSettingsEntryPackedAddress24[];
extern char g_Player_SelectNextPlayerSettingsEntryPackedAddress24[];
extern char g_Player_SelectPreviousAlternatePlayerSettingsEntryPackedAddress24[];
extern char g_Player_SelectPreviousPlayerSettingsEntryPackedAddress24[];
extern char g_Player_UpdatePlayerSettingsExitPackedAddress24[];
#include "include_asm.h"
#include "DATA/OVL1_J/PLAYER_DISPATCHPLAYERSETTINGSEVENT_DATA.H"

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char g_Frontend_DispatchResidentActorEventAddress[];
extern char Player_FreeAlternatePlayerSettingsScreen_Address[];
extern char g_Player_DispatchPlayerSettingsEventAddress[];
RestD_src_638b7747Layout508 D_src_638b7747 = {
    { 3591, 5 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 1812),
    { 3592, 5 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 1820),
    { 3590, 5 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 156),
    { 3587, 5 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 1764),
    { 10, 5 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 1944),
    { 2, 5 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 2052),
    { 1, 5 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 1952),
    { 8, 92 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 2112),
    { 7, 92 },
    (unsigned int)(g_Frontend_DispatchResidentActorEventAddress + 2296),
    { 0, 0, 0, 3591, 12 },
    (unsigned int)(Player_FreeAlternatePlayerSettingsScreen_Address + 48),
    { 3592, 12 },
    (unsigned int)(Player_FreeAlternatePlayerSettingsScreen_Address + 56),
    { 3590, 12 },
    (unsigned int)(g_Player_DispatchPlayerSettingsEventAddress + 144),
    { 3587, 12 },
    (void *)&Player_FreeAlternatePlayerSettingsScreen_Address,
    { 2, 12 },
    (unsigned int)(Player_FreeAlternatePlayerSettingsScreen_Address + 176),
    { 1, 12 },
    (unsigned int)(Player_FreeAlternatePlayerSettingsScreen_Address + 64),
    { 8, 450 },
    (unsigned int)(Player_FreeAlternatePlayerSettingsScreen_Address + 248),
    { 7, 450 },
    (unsigned int)(Player_FreeAlternatePlayerSettingsScreen_Address + 424),
    { 0, 0, 0, 9 },
};
#endif
#if defined(VERSION_EU)
extern char g_Player_PlayerSettingsEvent0E07HandlerPackedAddress24[];
extern char g_Player_UpdatePlayerSettingsExitPackedAddress24[];
extern char g_Player_InitPlayerSettingsScreenPackedAddress24[];
extern char g_Player_FreePlayerSettingsScreenPackedAddress24[];
extern char g_Player_PlayerSettingsEvent0AHandlerPackedAddress24[];
extern char g_Player_CancelPlayerSettingsEntryPackedAddress24[];
extern char g_Player_ConfirmPlayerSettingsEntryPackedAddress24[];
extern char g_Player_SelectNextPlayerSettingsEntryPackedAddress24[];
extern char g_Player_SelectPreviousPlayerSettingsEntryPackedAddress24[];
extern char g_Player_AlternatePlayerSettingsEvent0E07HandlerPackedAddress24[];
extern char g_Player_AlternatePlayerSettingsEvent0E08HandlerPackedAddress24[];
extern char g_Player_OpenAlternatePlayerSettingsScreenPackedAddress24[];
extern char g_Player_FreeAlternatePlayerSettingsScreenPackedAddress24[];
extern char g_Player_CancelAlternatePlayerSettingsEntryPackedAddress24[];
extern char g_Player_ConfirmAlternatePlayerSettingsEntryPackedAddress24[];
extern char g_Player_SelectNextAlternatePlayerSettingsEntryPackedAddress24[];
extern char g_Player_SelectPreviousAlternatePlayerSettingsEntryPackedAddress24[];
RestD_src_638b7747Layout509 D_src_638b7747 = {
    { 3591, 5 },
    (void *)&g_Player_PlayerSettingsEvent0E07HandlerPackedAddress24,
    { 3592, 5 },
    (void *)&g_Player_UpdatePlayerSettingsExitPackedAddress24,
    { 3590, 5 },
    (void *)&g_Player_InitPlayerSettingsScreenPackedAddress24,
    { 3587, 5 },
    (void *)&g_Player_FreePlayerSettingsScreenPackedAddress24,
    { 10, 5 },
    (void *)&g_Player_PlayerSettingsEvent0AHandlerPackedAddress24,
    { 2, 5 },
    (void *)&g_Player_CancelPlayerSettingsEntryPackedAddress24,
    { 1, 5 },
    (void *)&g_Player_ConfirmPlayerSettingsEntryPackedAddress24,
    { 8, 94 },
    (void *)&g_Player_SelectNextPlayerSettingsEntryPackedAddress24,
    { 7, 94 },
    { (void *)&g_Player_SelectPreviousPlayerSettingsEntryPackedAddress24, 0, 0, 0 },
    { 3591, 12 },
    (void *)&g_Player_AlternatePlayerSettingsEvent0E07HandlerPackedAddress24,
    { 3592, 12 },
    (void *)&g_Player_AlternatePlayerSettingsEvent0E08HandlerPackedAddress24,
    { 3590, 12 },
    (void *)&g_Player_OpenAlternatePlayerSettingsScreenPackedAddress24,
    { 3587, 12 },
    (void *)&g_Player_FreeAlternatePlayerSettingsScreenPackedAddress24,
    { 2, 12 },
    (void *)&g_Player_CancelAlternatePlayerSettingsEntryPackedAddress24,
    { 1, 12 },
    (void *)&g_Player_ConfirmAlternatePlayerSettingsEntryPackedAddress24,
    { 8, 454 },
    (void *)&g_Player_SelectNextAlternatePlayerSettingsEntryPackedAddress24,
    { 7, 454 },
    { (void *)&g_Player_SelectPreviousAlternatePlayerSettingsEntryPackedAddress24, 0, 0, 0, 0 },
};
#endif
#if defined(VERSION_EU_X)
RestD_src_638b7747Layout510 D_src_638b7747 = {
    { 3591, 5, 4422680, 3592, 5, 4422688, 3590, 5, 4420432, 3587, 5, 4422632, 10, 5, 4422812, 2, 5, 4422920, 1, 5, 4422820, 8, 98, 4422980, 7, 98, 4423180, 0, 0, 0, 3591, 12, 4423572, 3592, 12, 4423580, 3590, 12, 4421564, 3587, 12, 4423524, 2, 12, 4423700, 1, 12, 4423588, 8, 458, 4423772, 7, 458, 4423964, 0, 0, 0 },
    2096.0002f,
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
RestPlayerDispatchplayersettingseventPointerWords1Record511 g_PlayerDispatchplayersettingseventPointerWords1 = {
    3591,
    5,
    (unsigned int)addrLow_Player_EmptySettingsEntryHook,
    3592,
    5,
    (unsigned int)addrLow_Player_UpdatePlayerSettingsExit,
};
#endif

#if defined(VERSION_US)
RestplayerSettingsEventHandlersUsLayout512 g_playerSettingsEventHandlersUs = {
    { 3590, 5, 4417232, 3587, 5, 4418840, 10, 5, 4419020, 2, 5, 4419128, 1, 5, 4419028, 8, 94, 4419188, 7, 94, 4419372, 0, 0, 0, 3591, 12, 4420140, 3592, 12, 4420148, 3590, 12, 4419700, 3587, 12, 4420092, 2, 12, 4420268, 1, 12, 4420156, 8, 454, 4420340, 7, 454, 4420516, 0, 0, 0 },
    0x2E481CEE,
    { 0, 0, 3592, 9, 4421156, 3590, 9, 4420848, 3591, 9, 4421108, 3587, 9, 4421060, 1, 9, 4421520, 2, 9, 4421460, 0, 0, 0, 3592, 30, 4422128, 3590, 30, 4421880, 3591, 30, 4422088, 3587, 30, 4422040, 1, 30, 4422416, 2, 30, 4422356, 0, 0, 0 },
};
#endif
