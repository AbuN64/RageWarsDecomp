#include "include_asm.h"
#include "MENU/OPTIONEDITSTATE.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "ENGINE/DEFS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SOUNDINFO.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "COMMON/VOLUME_MENU_RESOURCES.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/MENU_CREATEMENUFROMPARAMETERS.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"
#include "VOLUME/PAK_FORMATMUSICPREVIEW_DATA.H"

/* 80444EC0_15.CPP */
/* Shows the fixed sound value text when g_menuMusicPreviewSelection is zero. Otherwise
 * formats its current value into the alternate text (the current menu
 * language's line in the EU builds), two bytes before the line length
 * reported by the text item helper. */


#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* The menu language byte; read as an array element, which keeps the read after the text store. */
extern u8 g_languageIndex[];
extern char g_musicPreviewValueFormat_eu[];
#define VALUE_TEXT g_musicPreviewValueText_eu
#define VALUE_FORMAT g_musicPreviewValueFormat_eu
#else
#define VALUE_TEXT ((u8 **)&g_musicPreviewValueText)
#define VALUE_FORMAT g_musicPreviewValueFormat_de
#endif

s32 Pak_FormatMusicPreview(LayeredText *field) {
    char *text;
    if (g_menuMusicPreviewSelection == 0) {
        field->text = &g_musicPreviewFixedValueText;
    } else {
        field->text = VALUE_TEXT;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (char *)field->text[g_languageIndex[0]];
#else
        text = (char *)*VALUE_TEXT;
#endif
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2),
                        VALUE_FORMAT, g_menuMusicPreviewSelection);
    }
    return 0;
}

/* 80444EC0_16.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Pak_OpenMusicPreviewMenu(void *first, void *second, void *third) {
    SoundElement_DisablePeriodicSound();
    g_menuSavedAudioSelection = SoundElement_GetMusicPlaybackEnabled();
    SoundElement_SetMusicPlaybackEnabled(g_menuMusicPreviewSelection);
    SoundElement_DisableMusicGainOverride();
    SoundElement_SetVoiceMixValue(1);
    g_musicPreviewMenuActive = 1;
    Control_ClearMenuControlFlag();
    Menu_AllocateMenu(third, second, g_musicPreviewMenuResource);
    return 1;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Restarts sound: calls SoundElement_DisablePeriodicSound, records what SoundElement_GetMusicPlaybackEnabled returns in g_menuSavedAudioSelection, passes
   g_menuMusicPreviewSelection to SoundElement_SetMusicPlaybackEnabled, calls SoundElement_DisableMusicGainOverride and SoundElement_SetVoiceMixValue with 1, sets g_musicPreviewMenuActive,
   calls Control_ClearMenuControlFlag and then Menu_AllocateMenu with the third argument, the second and g_musicPreviewMenuResource_PakOpenmusicpreviewmenu.
   Returns one. */

s32 Pak_OpenMusicPreviewMenu(void *first, void *second, void *third) {
    SoundElement_DisablePeriodicSound();
    g_menuSavedAudioSelection = SoundElement_GetMusicPlaybackEnabled();
    SoundElement_SetMusicPlaybackEnabled(g_menuMusicPreviewSelection);
    SoundElement_DisableMusicGainOverride();
    SoundElement_SetVoiceMixValue(1);
    g_musicPreviewMenuActive = 1;
    Control_ClearMenuControlFlag();
    Menu_AllocateMenu(third, second, g_musicPreviewMenuResource);
    return 1;
}
#endif

/* 80444EC0_17.CPP */
#if defined(VERSION_US_REV1)
/* Toggles the owner at offset 0x1C of the second argument between states 1 and 2 through its word
   at 0x5D0, leaving any other state alone; returns zero. */

s32 Pak_ToggleOwnerMode(void *unused, struct Holder *holder) {
    struct MusicPreviewOwnerView *owner = holder->owner;

    if (owner == 0) {
        return 0;
    }
    if (owner->value == 1) {
        owner->value = 2;
    } else if (owner->value == 2) {
        owner->value = 1;
    }
    return 0;
}

/* Points a field's text at g_ownerModeOneText when the owner at offset 0x1C of the second argument has its
   word at 0x5D0 equal to one, and at g_ownerModeOtherText otherwise; returns zero, doing nothing without an
   owner. */

s32 Pak_UpdateOwnerModeText(struct PakActionLabelView *field, struct Holder *holder) {
    if (holder->owner == 0) {
        return 0;
    }
    if (holder->owner->value == 1) {
        field->text = g_ownerModeOneText;
    } else {
        field->text = g_ownerModeOtherText;
    }
    return 0;
}

/* Replaces g_playerViewRenderingEnabled with what Menu_AdjustValue returns for the second argument, g_playerViewRenderingEnabled, 1, 0, 1 and 1,
   and returns zero. */


s32 Pak_AdjustOwnerNotificationOption(void *first, void *second) {
    g_playerViewRenderingEnabled = Menu_AdjustValue(second, g_playerViewRenderingEnabled, 1, 0, 1, 1);
    return 0;
}
#endif
