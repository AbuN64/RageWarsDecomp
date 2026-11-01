#include "MENU/HOLDERRECAT1CV2.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "MENU/ITEMS/ITEMS_CYCLESCENEMASK.H"
#include "RENDER/SETN64_UPDATEFADETRANSITION.H"

/* Clears the word held in g_controllerPakProbeState. */
extern s32 g_controllerPakProbeState;

/* Returns the name the object at offset 0x5D8 of an actor's owner holds, falling back to
   g_playerPartnerNameFallback when the actor has no owner or the owner has no such object. */






/* Updates the selected menu option in response to the current input state. */
unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);

 /* extern */
 /* extern */
 /* extern */
extern char g_combinedControllerProfile;





/* Replaces the signed byte at offset 0x7B of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 1, 0, 1 and 1, returning zero. Adapted from Items_AdjustPlayerOption7E with the settings byte made the signed byte at 0x7B. */









extern s32 Menu_AdjustValue(struct MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap);

/* Points an option field at the text g_playerOption7BText0 when the signed byte at offset 0x7B of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) is zero and at g_playerOption7BText1 when it is one, returning zero. Adapted from Items_SelectPlayerOption7EText with the settings byte made the signed byte at 0x7B and the texts changed. */













/* Replaces the byte at offset 0x7C of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 1, 0, 1 and 1, and returns zero. */









/* Points a field's text at g_playerOption7CText0 when the byte at offset 0x7C of the settings the second argument's owner holds (or of the defaults g_playerPartnerNameFallback without an owner or settings) is zero, at g_playerOption7CText1 when it is one, and leaves it otherwise, returning zero. Adapted from Items_SelectPlayerFlag82Text with the settings pointer checked for null, the byte offset 0x7C, and a nested test over the texts g_playerOption7CText0 and g_playerOption7CText1 changed. */












/* Replaces the byte at offset 0x7D of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 1, 0, 1 and 1, and returns zero. Adapted from Items_AdjustPlayerOption7C with the settings byte 0x7D changed. */









/* Points an option field at the text g_playerOption7DText0 when the byte at offset 0x7D of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) is zero and at g_playerOption7DText1 when it is one, returning zero. */













/* Replaces the byte at offset 0x7E of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 1, 0, 1 and 1, and returns zero. Adapted from Items_AdjustPlayerOption7C with the settings byte 0x7E changed. */









/* Points an option field at the text g_playerOption7EText0 when the byte at offset 0x7E of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) is zero and at g_playerOption7EText1 when it is one, returning zero. Adapted from Items_SelectPlayerOption7DText with the settings byte 0x7E and the texts g_playerOption7EText0 and g_playerOption7EText1 changed. */













/* Replaces the option byte g_particleSpriteViewMode with what Menu_AdjustValue returns for the second argument, that
   byte, 1, 0, 2 and 1, and returns zero. */




/* Replaces the option byte g_gameSettingsTwoPlayerScreenPreference with what Menu_AdjustValue returns for the second argument, that
   byte, 1, 0, 1 and 1, and returns zero. */

/* Updates the menu item visibility and text for the current configuration. */


                                /* extern */


void Items_ResetScreenModeFadeCooldown(void) {
    g_controllerPakProbeState = 0;
}

char *Items_GetPlayerSettingsText(struct PlayerSettingsTextHolder *actor) {
    char *name = g_playerPartnerNameFallback.text;

    if (actor->owner != 0 && actor->owner->settings != 0) {
        name = actor->owner->settings->text;
    }
    return name;
}

s32 Items_CycleSceneMask(void) {
 if(((s32 (*)(char *))Control_IsLeftPressed)(&g_combinedControllerProfile)) {
 switch(g_gameSettings.sceneMask) {
 case 8: g_gameSettings.sceneMask=32; break;
 case 16: g_gameSettings.sceneMask=8; break;
 case 32: g_gameSettings.sceneMask=16; break;
 }
 }
 if(((s32 (*)(char *))Control_IsRightPressed)(&g_combinedControllerProfile) || Control_IsAButtonPressed(&g_combinedControllerProfile)) {
 switch(g_gameSettings.sceneMask) {
 case 8: g_gameSettings.sceneMask=16; break;
 case 16: g_gameSettings.sceneMask=32; break;
 case 32: g_gameSettings.sceneMask=8; break;
 }
 }
 return 0;
}

/* Sets bit 24 of the item's flags when g_gameSessionMode is 8 (clears it otherwise) and points the item at the text table for the configuration g_gameOptions (8, 0x10 or 0x20); returns 0. */
s32 Items_SelectSceneMaskText(SceneMaskLabelItem *item) {
    if (g_gameSession.mode == 8) {
        item->flags |= 0x01000000;
    } else {
        item->flags &= ~0x01000000;
    }
    switch (g_gameSettings.sceneMask) {
    case 8:
        item->table = g_sceneMaskLabelTable8;
        break;
    case 16:
        item->table = g_sceneMaskLabelTable0x10;
        break;
    case 32:
        item->table = g_sceneMaskLabelTable0x20;
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOption7B(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7B = Menu_AdjustValue(holder, settings->option7B, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOption7BText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7B) {
    case 0:
        field->text = &g_playerOption7BText0;
        break;
    case 1:
        field->text = &g_playerOption7BText1;
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOption7C(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7C = Menu_AdjustValue(holder, settings->option7C, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOption7CText(struct PakActionLabelView *field, struct PlayerSettingsTextHolder *holder) {
    s32 result = 0;
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    if (settings->option7C != 0) {
        if (settings->option7C == 1) {
            field->text = g_playerOption7CText1;
        }
    } else {
        field->text = g_playerOption7CText0;
    }
    return result;
}

s32 Items_AdjustPlayerOption7D(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7D = Menu_AdjustValue(holder, settings->option7D, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOption7DText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7D) {
    case 0:
        field->text = &g_playerOption7DText0;
        break;
    case 1:
        field->text = &g_playerOption7DText1;
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOption7E(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7E = Menu_AdjustValue(holder, settings->option7E, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOption7EText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7E) {
    case 0:
        field->text = &g_playerOption7EText0;
        break;
    case 1:
        field->text = &g_playerOption7EText1;
        break;
    }
    return 0;
}

s32 Items_AdjustFirstListMode(void *first, void *second) {
    u8 *option = &g_gameSettings.bloodMode;

    *option = Menu_AdjustValue(second, *option, 1, 0, 2, 1);
    return 0;
}

s32 Items_SelectFirstListModeText(struct PakActionLabelView *field) {
    switch (g_gameSettings.bloodMode) {
    case 0:
        field->text = g_bloodModeText0;
        break;
    case 1:
        field->text = g_bloodModeText1;
        break;
    case 2:
        field->text = g_bloodModeText2;
        break;
    default:
        return 0;
    }
    return 0;
}

s32 Items_AdjustGameOption1F(void *first, void *second) {
    u8 *option = &g_gameSettings.twoPlayerScreenPreference;

    *option = Menu_AdjustValue(second, *option, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectGameOption1FText(MenuOptionLabelView *textRow) {
    s32 unusedResult;

    if ((SetN64_IsModeThirteen() != 0) && (g_gameSettings.local == 0)) {
        textRow->flags = textRow->flags & 0xFEFFFFFF;
    } else {
        textRow->flags = textRow->flags | 0x01000000;
    }
    switch (g_gameSettings.twoPlayerScreenPreference) {                           /* irregular */
    case 0:
        textRow->label = &g_gameOptionOneFZeroText;
        break;
    case 1:
        textRow->label = &g_gameOptionOneFOneText;
        break;
    }
    return 0;
}
