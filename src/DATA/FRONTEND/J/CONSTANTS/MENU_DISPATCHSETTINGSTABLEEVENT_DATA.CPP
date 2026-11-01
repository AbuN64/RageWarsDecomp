#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_Menu_CancelScrollingChoiceScreenPackedAddress242[];
extern char g_Menu_CancelTitleButtonScreenPackedAddress242[];
extern char g_Menu_CreateTitleButtonScreenPackedAddress242[];
extern char g_Menu_FreeScrollingChoiceScreenPackedAddress242[];
extern char g_Menu_FreeTitleButtonScreenPackedAddress242[];
extern char g_Menu_HandleScrollingChoicePackedAddress242[];
extern char g_Menu_HandleTitleButtonChoicePackedAddress242[];
extern char g_Menu_UpdateScrollingChoiceScreenPackedAddress242[];
extern char g_Menu_UpdateTitleButtonScreenPackedAddress242[];
extern char g_Menu_WrapScrollingChoiceNodesPackedAddress242[];
extern char g_Menu_WrapTitleButtonScreenNodesPackedAddress24[];
#include "include_asm.h"
#include "DATA/OVL1_J/MENU_DISPATCHSETTINGSTABLEEVENT_DATA.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
extern char g_Menu_UpdateScrollingChoiceScreenPackedAddress242[];
extern char g_Player_DispatchAlternatePlayerSettingsEventAddress[];
extern char g_Menu_WrapScrollingChoiceNodesPackedAddress242[];
extern char g_Menu_FreeScrollingChoiceScreenPackedAddress242[];
extern char g_Menu_HandleScrollingChoicePackedAddress242[];
extern char g_Menu_CancelScrollingChoiceScreenPackedAddress242[];
extern char g_Menu_UpdateTitleButtonScreenPackedAddress242[];
extern char g_Menu_CreateTitleButtonScreenPackedAddress242[];
extern char g_Menu_WrapTitleButtonScreenNodesPackedAddress24[];
extern char g_Menu_FreeTitleButtonScreenPackedAddress242[];
extern char g_Menu_HandleTitleButtonChoicePackedAddress242[];
extern char g_Menu_CancelTitleButtonScreenPackedAddress242[];
RestD_src_846838eaLayout505 D_src_846838ea = {
    { 3592, 9 },
    (void *)&g_Menu_UpdateScrollingChoiceScreenPackedAddress242,
    { 3590, 9 },
    (unsigned int)(g_Player_DispatchAlternatePlayerSettingsEventAddress + 148),
    { 3591, 9 },
    (void *)&g_Menu_WrapScrollingChoiceNodesPackedAddress242,
    { 3587, 9 },
    (void *)&g_Menu_FreeScrollingChoiceScreenPackedAddress242,
    { 1, 9 },
    (void *)&g_Menu_HandleScrollingChoicePackedAddress242,
    { 2, 9 },
    { (void *)&g_Menu_CancelScrollingChoiceScreenPackedAddress242, 0, 0, 0 },
    { 3592, 30 },
    (void *)&g_Menu_UpdateTitleButtonScreenPackedAddress242,
    { 3590, 30 },
    (void *)&g_Menu_CreateTitleButtonScreenPackedAddress242,
    { 3591, 30 },
    (void *)&g_Menu_WrapTitleButtonScreenNodesPackedAddress24,
    { 3587, 30 },
    (void *)&g_Menu_FreeTitleButtonScreenPackedAddress242,
    { 1, 30 },
    (void *)&g_Menu_HandleTitleButtonChoicePackedAddress242,
    { 2, 30 },
    { (void *)&g_Menu_CancelTitleButtonScreenPackedAddress242, 0, 0, 0 },
};
#endif
#if defined(VERSION_EU_X)
extern char g_Player_DispatchAlternatePlayerSettingsEventAddress[];
extern char g_Menu_DispatchScrollingChoiceEventAddress[];
RestD_src_846838eaLayout506 D_src_846838ea = {
    { 3592, 9 },
    (unsigned int)(g_Player_DispatchAlternatePlayerSettingsEventAddress + 456),
    { 3590, 9 },
    (unsigned int)(g_Player_DispatchAlternatePlayerSettingsEventAddress + 148),
    { 3591, 9 },
    (unsigned int)(g_Player_DispatchAlternatePlayerSettingsEventAddress + 408),
    { 3587, 9 },
    (unsigned int)(g_Player_DispatchAlternatePlayerSettingsEventAddress + 360),
    { 1, 9 },
    (unsigned int)(g_Player_DispatchAlternatePlayerSettingsEventAddress + 820),
    { 2, 9 },
    (unsigned int)(g_Player_DispatchAlternatePlayerSettingsEventAddress + 760),
    { 0, 0, 0, 3592, 30 },
    (unsigned int)(g_Menu_DispatchScrollingChoiceEventAddress + 392),
    { 3590, 30 },
    (unsigned int)(g_Menu_DispatchScrollingChoiceEventAddress + 144),
    { 3591, 30 },
    (unsigned int)(g_Menu_DispatchScrollingChoiceEventAddress + 352),
    { 3587, 30 },
    (unsigned int)(g_Menu_DispatchScrollingChoiceEventAddress + 304),
    { 1, 30 },
    (unsigned int)(g_Menu_DispatchScrollingChoiceEventAddress + 680),
    { 2, 30 },
    (unsigned int)(g_Menu_DispatchScrollingChoiceEventAddress + 620),
    { 0, 0, 0 },
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
RestMenuDispatchsettingstableeventPointerWords1Record507 g_MenuDispatchsettingstableeventPointerWords1 = {
    3592,
    9,
    (unsigned int)g_Menu_SettingsTableEvent0E08HandlerPackedAddress24,
    3590,
    9,
    (unsigned int)g_Menu_SettingsTableEvent0E06HandlerPackedAddress24,
    3591,
    9,
    (unsigned int)g_Menu_SettingsTableEvent0E07HandlerPackedAddress24,
    3587,
    9,
    (unsigned int)g_Menu_SettingsTableEvent0E03HandlerPackedAddress24,
    1,
    9,
    (unsigned int)g_Menu_SettingsTableEvent01HandlerPackedAddress24,
    2,
    9,
    (unsigned int)g_Menu_SettingsTableEvent02HandlerPackedAddress24,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif
