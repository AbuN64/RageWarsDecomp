#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#include "DATA/OVL1_J/ACHIEVE_CREATERESULTSSCREEN_DATA.H"

/* g_AchieveCreateresultsscreenWords1_AchieveCreateresultsscreenData.CPP */
/* ROM-grounded data: rodata/writable/800E5830 */
s32 g_AchieveCreateresultsscreenWords1[1] = {
    0,
};

/* g_AchieveCreateresultsscreenPointerWords1_AchieveCreateresultsscreenData.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char g_Menu_DispatchTitleButtonEventAddress[];
RestD_src_e3e7c440Record462 D_src_e3e7c440 = {
    3592,
    18,
    (unsigned int)(g_Menu_DispatchTitleButtonEventAddress + 4812),
    3591,
    18,
    (unsigned int)(g_Menu_DispatchTitleButtonEventAddress + 4380),
    3590,
    18,
    (unsigned int)(g_Menu_DispatchTitleButtonEventAddress + 152),
    3587,
    18,
    (unsigned int)(g_Menu_DispatchTitleButtonEventAddress + 4332),
    2,
    18,
    (unsigned int)(g_Menu_DispatchTitleButtonEventAddress + 5284),
    1,
    18,
    (unsigned int)(g_Menu_DispatchTitleButtonEventAddress + 5084),
    3594,
    18,
    (unsigned int)(g_Menu_DispatchTitleButtonEventAddress + 4388),
    { 0, 0, 0, 0, 0xe07, 6 },
};
#endif
#if defined(VERSION_EU)
RestD_src_e3e7c440Record463 D_src_e3e7c440 = {
    3592,
    18,
    0x00439B58,
    3591,
    18,
    0x004399A8,
    3590,
    18,
    0x00438880,
    3587,
    18,
    0x00439978,
    2,
    18,
    0x00439D30,
    1,
    18,
    0x00439C68,
    3594,
    18,
    0x004399B0,
    { 0x00000000, 0x00000000, 0x00000000, 0x0002FFFF, 0x00200800, 0x7FFF4000 },
};
#endif
#if defined(VERSION_EU_X)
RestD_src_e3e7c440Record464 D_src_e3e7c440 = {
    3592,
    18,
    0x00439C88,
    3591,
    18,
    0x00439AD8,
    3590,
    18,
    0x004389B0,
    3587,
    18,
    0x00439AA8,
    2,
    18,
    0x00439E60,
    1,
    18,
    0x00439D98,
    3594,
    18,
    0x00439AE0,
    { 0x00000000, 0x00000000, 0x00000000, 0x8C6A0008, 0xACC80000, 0xACC90004 },
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
RestAchieveCreateresultsscreenPointerWords1Record465 g_AchieveCreateresultsscreenPointerWords1 = {
    3592,
    18,
    (unsigned int)g_Achieve_UpdateResultSelectionMessagePackedAddress24_AchieveCreateresultsscreenData,
    3591,
    18,
    (unsigned int)g_Achieve_ResultScreenReturnZeroPackedAddress24_AchieveCreateresultsscreenData,
};
#endif

#if defined(VERSION_US)
RestAchieveCreateresultsscreenPointerWordsTailUsRecord466 g_AchieveCreateresultsscreenPointerWordsTailUs = {
    3590,
    18,
    0x00437C30,
    3587,
    18,
    0x00438C84,
    2,
    18,
    0x0043903C,
    1,
    18,
    0x00438F74,
    3594,
    18,
    0x00438CBC,
    { 0x00000000, 0x00000000, 0x00000000, 0x4E452E48, 0x1CE8002B, 0x433A5C50 },
};
#endif
