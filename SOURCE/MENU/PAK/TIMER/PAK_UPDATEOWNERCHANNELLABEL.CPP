#include "ENGINE/DEFS.H"
#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/RECORDRECATCV1.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/PAK_MENU.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "ENGINE/DEFS.H"
#include "MENU/MENU_CREATEMENUFROMPARAMETERS.H"
extern s32 g_pakUseScannedChannel;
extern char *g_unlockedLevelResultLabel[];


s32 Timer_UpdateOwnerChannelLabel(struct Field *field, Shared_PakMenu *pThis) {
    char *text;
    char **strings;
    s32 value;
    if (g_pakUseScannedChannel != 0) {
        field->text = g_unlockedLevelResultLabel;
    } else {
        value = pThis->owner->controllerPort;
        strings = g_pakOwnerChannelLabels;
        field->text = strings;
        text = strings[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 1), g_pakChannelNumberFormat, value + 1);
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Uses the fixed option text while the mode flag is set. Otherwise formats
 * one more than the holder's signed option byte into the editable text,
 * one byte before the length returned by the item text helper. */
extern s32 g_pakUseScannedChannel;
extern char *g_unlockedLevelResultLabel[];


#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Timer_UpdateOwnerChannelLabel(LayeredText *field, struct Shared_PakMenu *holder) {
    char *text;
    s32 value;
    if (g_pakUseScannedChannel != 0) {
        field->text = g_unlockedLevelResultLabel;
    } else {
        value = holder->owner->controllerPort;
        field->text = (u8 **)&g_pakOwnerChannelLabelFixed;
        text = (char *)*(u8 **)&g_pakOwnerChannelLabelFixed;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 1),
                        g_pakFormatInt1, value + 1);
    }
    return 0;
}

#endif
#endif
