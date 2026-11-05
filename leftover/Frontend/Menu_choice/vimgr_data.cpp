#include "Common/packed_callback.h"
#include "Data/Overlays/Menu/linktables_addresses.h"
#include "Multi/multi_address_symbols.h"
extern void *g_menuAbbreviationAndFtLabelSlots[2];
#include "Common/resident_event_handler.h"
#include "Common/osviscale.h"
#include "types.h"
#include "Frontend/frontend_address_symbols.h"
#if defined(VERSION_US_REV1)
struct {
    s32 event;
    s32 actorKind;
} g_VimgrWords2 __attribute__((aligned(4))) = {
    3590,
    3
};
typedef char g_VimgrWords2SizeCheck[(sizeof(g_VimgrWords2) == 8) ? 1 : -1];
char g_VimgrPointerWords1[4] __attribute__((aligned(4))) = "\000B< ";
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_MenuEventHandlersPointerWords_usrev1_E521C[5] = {
    { 3587, 3, (ResidentEventHandler)(void *)PACKED_CALLBACK_LOW(Frontend_DestroyPlayModeMenu2) }, { 2, 3, (ResidentEventHandler)(void *)PACKED_CALLBACK_LOW(Frontend_ConsumePlayModeEvent2) }, { 1, 3, (ResidentEventHandler)(void *)PACKED_CALLBACK_LOW(Frontend_TabOptionsEvent02PlayModeEvent01Handler) }, { 10, 3, (ResidentEventHandler)(void *)PACKED_CALLBACK_LOW(Frontend_HandlePlayModeShortcut2) }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
unsigned int g_VimgrWords_usrev1_E5258[10] = {
    0x00000E03, 0x00000020, (unsigned int)g_playerSettingsSlotNumberFormat + 0x4, (unsigned int)g_menuAbbreviationAndFtLabelSlots + 0x4, (unsigned int)g_menuAbbreviationAndFtLabelSlots, (unsigned int)g_playerSettingsSlotNumberFormat + 0x8, (unsigned int)g_menuAbbreviationAndFtLabelSlots, (unsigned int)g_playerSettingsSlotNumberFormat + 0x8,
    (unsigned int)g_menuAbbreviationAndFtLabelSlots + 0x4, (unsigned int)g_playerSettingsSlotNumberFormat + 0x4,
};
#endif
