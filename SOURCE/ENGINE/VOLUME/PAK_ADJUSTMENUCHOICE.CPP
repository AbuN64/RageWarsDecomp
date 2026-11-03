#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENURECAT20V1.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VOLUME_MENU_RESOURCES.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

#if defined(VERSION_US_REV1)
/* Points a field's text at g_ownerNotificationEnabledLabels when the option g_playerViewRenderingEnabled is set and at g_ownerNotificationDisabledLabels otherwise, and returns
   zero: the label an option menu shows for that option. */



s32 Pak_UpdateOwnerNotificationOptionText(struct PakActionLabelView *field) {
    if (g_playerViewRenderingEnabled != 0) {
        field->text = g_ownerNotificationEnabledLabels;
    } else {
        field->text = g_ownerNotificationDisabledLabels;
    }
    return 0;
}

/* Replaces g_menuBinaryChoice with what Menu_AdjustValue returns for the second argument, g_menuBinaryChoice, 1, 0, 1 and 1,
   and returns zero. */


s32 Pak_AdjustMenuChoice(void *first, void *second) {
    g_menuBinaryChoice = Menu_AdjustValue(second, g_menuBinaryChoice, 1, 0, 1, 1);
    return 0;
}

/* Points a field's text at g_menuChoiceEnabledLabels when the option g_menuBinaryChoice is set and at g_menuChoiceDisabledLabels otherwise, and returns
   zero: the label an option menu shows for that option. */



s32 Pak_UpdateMenuChoiceText(struct PakActionLabelView *field) {
    if (g_menuBinaryChoice != 0) {
        field->text = g_menuChoiceEnabledLabels;
    } else {
        field->text = g_menuChoiceDisabledLabels;
    }
    return 0;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_pakAdjustMenuChoiceResourceFirst,
   and returns one. */

s32 Pak_OpenMenuChoiceFirstMenu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_pakAdjustMenuChoiceResourceFirst);
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_pakAdjustMenuChoiceResourceSecond,
   and returns one. */

s32 Pak_OpenMenuChoiceSecondMenu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_pakAdjustMenuChoiceResourceSecond);
    return 1;
}
#endif
