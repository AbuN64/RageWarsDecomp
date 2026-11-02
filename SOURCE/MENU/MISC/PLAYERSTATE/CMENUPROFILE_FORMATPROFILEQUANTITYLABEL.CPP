#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "TYPES.H"
#include "ENGINE/DEFS.H"


#include "COMMON/SHARED_MENUSELECTION.H"


#include "COMMON/GAMEPLAY_MOVEMENT.H"


#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/PLAYERSETTINGS.H"

struct Field;

extern char *g_profileQuantityDefaultLabels[];
extern char *g_profileQuantityFirstChoiceLabels[];
extern char *g_profileQuantitySecondChoiceLabels[];
extern char *g_profileQuantityThirdChoiceLabels[];
extern char *g_profileQuantityZeroLabels[];
extern char *g_profileQuantityTenLabels[];
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
extern char *g_profileQuantityDefaultLabelsEuStorage[];
#define PROFILE_QUANTITY_DEFAULT_LABELS_EU g_profileQuantityDefaultLabelsEuStorage
#else
extern char *PROFILE_QUANTITY_DEFAULT_LABELS_EU[];
#endif
extern char g_profileAlternateQuantityFormat[];
#else
extern char g_profileQuantityFormat[];
#endif
extern s32 Menu_CountLineChars(struct Field *);

s32 CMenuProfile_FormatProfileQuantityLabel(struct Field *field, Shared_MenuHandle *holder) {
    s32 value = holder->owner->views5D8.view5D8_9.profile->quantity;
    char *text;

    if (value == 0) {
        field->text = g_profileQuantityZeroLabels;
    } else if (value == 10) {
        field->text = g_profileQuantityTenLabels;
    } else {
        switch (holder->selection->index) {
        case 0:
        default:
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            field->text = PROFILE_QUANTITY_DEFAULT_LABELS_EU;
#else
            field->text = g_profileQuantityDefaultLabels;
#endif
            break;
        case 1:
            field->text = g_profileQuantityFirstChoiceLabels;
            break;
        case 2:
            field->text = g_profileQuantitySecondChoiceLabels;
            break;
        case 3:
            field->text = g_profileQuantityThirdChoiceLabels;
            break;
        }
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = field->text[g_languageIndex];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_profileAlternateQuantityFormat, value);
#else
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_profileQuantityFormat, value);
#endif
    }
    return 0;
}
