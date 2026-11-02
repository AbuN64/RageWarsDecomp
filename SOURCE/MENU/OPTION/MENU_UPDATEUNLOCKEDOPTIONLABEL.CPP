#include "TYPES.H"
#include "COMMON/RG.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView (*(s32 *)&g_gameSettings)

extern s32 g_menuOptionAvailabilityFlags;
s32 Menu_UpdateUnlockedOptionLabel(struct MenuOptionLabel *label, s32 optionMask, s32 *enabledText, s32 *disabledText) {
    if (g_menuOptionAvailabilityFlags & optionMask) label->flags |= 0x01000000;
    else label->flags &= 0xFEFFFFFF;
    if (g_gameSettingsView & optionMask) label->text = enabledText;
    else label->text = disabledText;
    return 0;
}
