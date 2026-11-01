#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OSVISCALE.H"
#include "TYPES.H"
#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
/* 800E4610.CPP */
/* ROM-grounded data: src/rw_menu_event_match_E5210_us_rev1.c */
struct {
    s32 event;
    s32 actorKind;
} g_VimgrWords2 __attribute__((aligned(4))) = {
    3590,
    3
};
typedef char g_VimgrWords2SizeCheck[(sizeof(g_VimgrWords2) == 8) ? 1 : -1];
char g_VimgrPointerWords1[4] __attribute__((aligned(4))) = "\000B< ";
#endif
extern char g_Frontend_TabOptionsEvent02PlayModeEvent01HandlerPackedAddress24[];
extern char g_Frontend_DestroyPlayModeMenuPackedAddress242[];
extern char g_Frontend_HandlePlayModeShortcutPackedAddress242[];
extern char g_Frontend_ConsumePlayModeEventPackedAddress242[];
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_MenuEventHandlersPointerWords7[5] = {
    { 3587, 3, (ResidentEventHandler)(void *)&g_Frontend_DestroyPlayModeMenuPackedAddress242 }, { 2, 3, (ResidentEventHandler)(void *)&g_Frontend_ConsumePlayModeEventPackedAddress242 }, { 1, 3, (ResidentEventHandler)(void *)&g_Frontend_TabOptionsEvent02PlayModeEvent01HandlerPackedAddress24 }, { 10, 3, (ResidentEventHandler)(void *)&g_Frontend_HandlePlayModeShortcutPackedAddress242 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
/* 800E4658.CPP */
unsigned int g_VimgrWords1[10] = {
    0x00000E03, 0x00000020, 0x800D74F0, 0x800D74FC, 0x800D74F8, 0x800D74F4, 0x800D74F8, 0x800D74F4,
    0x800D74FC, 0x800D74F0,
};
#endif
