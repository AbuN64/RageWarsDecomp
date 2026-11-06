#include "Common/shared_gameslot.h"
#include "Ai/cteamselect.h"
#include "Engine/debug_value_labels.h"
#include "include_asm.h"
#include "Volume/g_pakformatspacedint2digits.h"
#include "Volume/g_pakformatspacedint3digits.h"
#include "Data/rest_source_records.h"
#include "Volume/pak_formatmusicpreview_data.h"
#include "Menu/player_settings_text.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/frontend_video_mode.h"
#include "Frontend/screen_video_mode.h"
#include "Engine/defs.h"
#include "Common/world.h"
#include "Menu/optioneditstate.h"
#include <platform_sdk.h>
#include "AUDIO/sprintf.H"
#include "Render/setn64_getpacksection.h"
#include "Common/soundinfo.h"
#include "Menu/Pak/model.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Ovlgame/match.h"
#include "Menu/model.h"
#include "Common/game_session.h"
#include "Menu/menu_box.h"
#if defined(VERSION_US_REV1)
#include "Engine/Volume/g_menuboxcorners.h"
#endif
#if defined(VERSION_US_REV1)
#include "Data/Overlays/Debug/Constants/s_persontext.h"
#endif
#include "Data/Overlays/Debug/constants.h"
#include "Engine/cheats.h"
#if defined(VERSION_US_REV1)
#include "Engine/Cheats/s_weaponvistext.h"
#endif
#if defined(VERSION_US_REV1)
#include "Engine/Cheats/s_editfogtext.h"
#endif
#include "Data/Overlays/Debug/constants_addresses.h"
#if defined(VERSION_US_REV1)
#include "Engine/Cheats/s_ambgreentext.h"
#endif
#if defined(VERSION_US_REV1)
#include "Engine/Cheats/s_dirgreentext.h"
#endif
#if defined(VERSION_US_REV1)
#include "Engine/Cheats/s_allregionstext.h"
#endif
#if defined(VERSION_US_REV1)
#include "Data/Overlays/Debug/Constants/pak_updatechoicetext_data.h"
#endif
#include "Engine/volume.h"
#include "Common/volume_menu_resources.h"
#include "Engine/Audio/voice.h"
#include "Common/shared_gameslot.h"
#include "Common/snapshot_actor.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/textlayermetrics.h"
#include "Common/triple.h"
#include "Common/gameplay_sound_table.h"
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Common/shared_gameslot.h"
#endif
#endif
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Menu/menu_createmenufromparameters.h"
#endif
#endif
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Volume/g_pakformatspacedint2digits.h"
#endif
#endif
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Volume/g_pakformatspacedint3digits.h"
#endif
#endif
#include "Common/pak_enter_player_options.h"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Common/shared_gameslot.h"
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Engine/defs.h"
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Menu/menu_createmenufromparameters.h"
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Volume/g_pakformatspacedint2digits.h"
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Volume/g_pakformatspacedint3digits.h"
#endif
#include "Menu/pak_preview_views.h"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Common/pak_menu.h"
#endif
#include "Menu/built_menu.h"
#include "Common/texture_request.h"
#include "Frontend/screen.h"
#include "Multi/setup_setupnamespinner.h"
#include "Menu/Pak/pak_menu_entries.h"
#include "Audio/voice.h"
#include "Common/player_item_inventory.h"
#include "Menu/menu_event_handlers.h"
#include "Ovlgame/menu_handlesessionoptionpage.h"

/* G_PAKFORMATSPACEDINT2DIGITS.CPP */

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
const char g_volumePositiveStepPaddedFormat[6] =
    "  %2d";
#endif

/* G_PAKFORMATSPACEDINT3DIGITS.CPP */

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
const char g_volumeNegativeStepPaddedFormat[5] =
    " %3d";
#endif

/* PAK_FORMATMUSICPREVIEW_DATA.CPP */

#if defined(VERSION_US)
const char g_musicPreviewValueFormat_de[4] = "%2d";
#endif
#if defined(VERSION_DE)
const char g_musicPreviewPaddedIntFormatText[4] = "%2d\000";
#endif

#if defined(VERSION_DE)
extern float g_musicPreviewScaleTriple[3];
#endif

#if defined(VERSION_US_REV1)
const unsigned char g_musicPreviewPaddedIntFormat[4] = {
    0x25, 0x32, 0x64, 0x00,
};
#endif

/* PLAYEROPTION.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char k_playerOptionPaddedDecimalText[6] =
    "  %2d";
#endif

/* PAK_UPDATETHIRDVOLUMELABEL_DATA.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_volumeLabelSpacedStepFormat[5] =
    " %3d";
#endif

/* PAK_FORMATMUSICPREVIEW_DATA.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char k_pakFormatmusicpreviewDataConstantWords[4] =
    "%2d";
#endif

#if defined(VERSION_EU_X)
extern unsigned int k_pakFormatMusicPreviewLayout[3];
#endif

#if defined(VERSION_EU)
extern unsigned int k_pakFormatMusicPreviewPackedWords[3];
#endif

/* G_PAKFORMATINTZEROPADDEDSIXDIGITS.CPP */

#if defined(VERSION_US_REV1)
const char g_menuScaledLabelValueFormat[5] =
    "%06d";
#endif

/* PAK_SYNCPRIMARYBYTEOPTION_DATA.CPP */

#if defined(VERSION_US_REV1)
const char k_pakSyncprimarybyteoptionDataTextBytes[5] = "%03d";
#endif

/* MODEL.CPP */


#if defined(VERSION_US_REV1)
/* Edits a byte, integer, or float option and propagates it to the active resource records. */
s32 Pak_AdjustModelField(OptionEditState *label, OptionEditState *menu, s32 third, s32 wrap, s32 fieldOffset, s32 step, s32 maximum, f32 displayDivisor) {
    s32 modelIndex;
    s32 recordIndex;
    s32 modelRecordIndexOrLimit;
    s32 textAddress;
    s32 length;
    u8 *fieldAddress;
    s32 fieldValue;
    OptionEditState *modelOwner;
    OptionEditState *selectedObject;
    OptionEditContext *modelPack;
    ModelEditRecord *record;
    s32 recordCount;
    fieldValue = 0;
    if (Control_IsStartPressed(menu->controller) != 0) {
        return Menu_TryCreateMenu(label, menu, third);
    }
    selectedObject = menu->selectedObject;
    if (selectedObject != NULL) {
        modelOwner = selectedObject->modelOwner;
        if (modelOwner != NULL) {
            modelIndex = modelOwner->modelIndex;
            if (modelIndex != 0) {
                fieldAddress = Scene_GetModelRecordByIndexPointer(&g_world, modelIndex) + fieldOffset;
                switch (wrap) { /* irregular */
                case 0:
                    fieldValue = *fieldAddress;
                    fieldValue = Menu_AdjustValue(menu, fieldValue, step, 0, maximum, 1);
                    *fieldAddress = fieldValue;
                    break;
                case 1:
                    fieldValue = *(s32 *)fieldAddress;
                    fieldValue = Menu_AdjustValue(menu, fieldValue, step, 0, maximum, wrap);
                    *(s32 *)fieldAddress = fieldValue;
                    break;
                case 2:
                    fieldValue = (s32)*(f32 *)fieldAddress;
                    modelRecordIndexOrLimit = maximum;
                    fieldValue = Menu_AdjustValue(menu, fieldValue, step, 0, modelRecordIndexOrLimit, 1);
                    *(f32 *)fieldAddress = fieldValue;
                    break;
                }
                textAddress = *label->textAddressPointer;
                length=Menu_CountLineChars(label);
                length-=6;
                Libc_FormatString(textAddress + length, &g_menuScaledLabelValueFormat, (s32) ((f32) fieldValue / displayDivisor));
                if (g_modelEditorApplyToAllRecords != 0) {
                    modelPack = (OptionEditContext *)SetN64_GetPackSection(g_modelEditPack, 0);
                    modelRecordIndexOrLimit = 0;
                    recordCount = modelPack->count;
                    record = modelPack->records;
                    if (recordCount > 0) {
                      do {
                        fieldAddress = record[modelRecordIndexOrLimit].bytes + fieldOffset;
                        switch (wrap) {
                        case 0: *fieldAddress = fieldValue; break;
                        case 1: *(s32 *)fieldAddress = fieldValue; break;
                        case 2: *(f32 *)fieldAddress = fieldValue; break;
                        }
                        modelRecordIndexOrLimit += 1;
                      } while (modelRecordIndexOrLimit < recordCount);
                    }
                }
            }
        }
    }
    return 0;
}
#endif

/* Calls SoundElement_SetMusicPlaybackEnabled with -1, SoundElement_DisableMusicGainOverride, SoundElement_StopMusic and Match_ResetMatchControllerState on g_gameSession, and
   returns one. */

s32 Pak_StopMusicAndResetMatch(void) {
    SoundElement_SetMusicPlaybackEnabled(-1);
    SoundElement_DisableMusicGainOverride();
    SoundElement_StopMusic();
    Match_ResetMatchControllerState(&g_gameSession);
    return 1;
}

/* Stores 4 into the first halfword of a record. */
void Pak_SetRecordTypeFour(s16 *record) {
    record[0] = 4;
}

#if defined(VERSION_US_REV1)
/* Forwards its three arguments to Pak_AdjustModelField with 0, 0, 1, 0xFF and the pooled constant (1.0f). */
void Pak_AdjustDebugRed(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 0, 0, 1, 0xFF, (1.0f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 0, 1, 1, 0xFF and the pooled constant (1.0f). */
void Pak_AdjustDebugGreen(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 0, 1, 1, 0xFF, (1.0f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 0, 2, 1, 0xFF and the pooled constant (1.0f). */
void Pak_AdjustDebugBlue(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 0, 2, 1, 0xFF, (1.0f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 1, 8, 0xA, 0x7D0 and the pooled constant (1.0f). */
void Pak_AdjustDebugThickness(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 1, 8, 10, 2000, (1.0f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 2, 0x10, 0x66, 0xA000 and the pooled constant (10.239999771118164f). */
void Pak_AdjustDebugFarClip(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 2, 16, 102, 0xA000, (10.239999771118164f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 2, 0x14, 1, 0xB4 and the pooled constant
   (1.0f). */
void Pak_AdjustDebugFieldOfView(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 2, 20, 1, 180, (1.0f));
}
#endif

/* G_PAKENCODEDWORDS.CPP */

#if defined(VERSION_US_REV1)
extern unsigned int g_PakEncodedWords[1];
#endif

/* G_MENUBOXCORNERS.CPP */
#if defined(VERSION_US_REV1)
extern float g_menuBoxCameraOffset[3];
extern char g_artsendModeOnText[28];
unsigned int g_artsendModeOnTextPointer[1] = {
    (unsigned int)&g_artsendModeOnText[4],
};
extern char s_artsendModeOffText[24];
#endif

/* S_PERSONTEXT.CPP */
#if defined(VERSION_US_REV1)
void *g_artsendModeOffTextPointer[1] = {
    s_artsendModeOffText,
};

extern char s_personText[24];
#endif

/* PAK_UPDATEOWNERMODETEXT_DATA.CPP */
#if defined(VERSION_US_REV1)
void *g_pakUpdateOwnerModeTextData[1] = {
    s_personText,
};

extern char s_thirdPersonDebugText[24];
#endif

/* S_WEAPONHIDDENTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_thirdPersonDebugText_PointerWord[1] = {
    (void *)&s_thirdPersonDebugText,
};

extern char s_weaponHiddenText[24];
#endif

/* S_WEAPONVISTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_weaponHiddenText_PointerWord[1] = {
    (void *)&s_weaponHiddenText,
};

extern char s_weaponVisText[24];
#endif

/* S_SHADOWSTEXT.CPP */
#if defined(VERSION_US_REV1)
void *g_weaponVisTextPointer[1] = {
    s_weaponVisText,
};

extern char s_shadowsText[24];
#endif

/* S_SHADOWSOFFTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_shadowsText_PointerWord[1] = {
    (void *)&s_shadowsText,
};

extern char s_shadowsOffText[24];
#endif

/* S_EDITFOGTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_shadowsOffText_PointerWord[1] = {
    (void *)&s_shadowsOffText,
};

extern char s_editFogText[12];
#endif

/* G_EDITFOGTEXTPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_editFogTextPointer[1] = {
    s_editFogText,
};
#endif

/* S_EDITLIGHTTEXT.CPP */

#if defined(VERSION_US_REV1)
extern char s_editLightText[12];
#endif

/* S_INFINITEAMMOTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_editLightText_PointerWord[1] = {
    (void *)&s_editLightText,
};

extern char s_infiniteAmmoText[24];
#endif

/* S_INFINITEAMMOOFFTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_infiniteAmmoText_PointerWord[1] = {
    (void *)&s_infiniteAmmoText,
};

extern char s_infiniteAmmoOffText[24];
#endif

/* S_FANCYLIGHTINGTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_infiniteAmmoOffText_PointerWord[1] = {
    (void *)&s_infiniteAmmoOffText,
};

extern char s_fancyLightingText[24];
#endif

/* S_FANCYLIGHTINGOFFTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_fancyLightingText_PointerWord[1] = {
    (void *)&s_fancyLightingText,
};

extern char s_fancyLightingOffText[24];
#endif

/* G_DEBUGCOLORTHICKNESSLABELS.CPP */

#if defined(VERSION_US_REV1)
DebugColorThicknessLabels g_debugColorThicknessLabels = {
    (unsigned int)s_fancyLightingOffText,
    {
        0x72, 0x65, 0x64, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x00, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugColorThicknessLabels.redText[0],
    {
        0x67, 0x72, 0x65, 0x65, 0x6E, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x00, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugColorThicknessLabels.greenText[0],
    {
        0x62, 0x6C, 0x75, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x00, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugColorThicknessLabels.blueText[0],
    {
        0x74, 0x68, 0x69, 0x63, 0x6B, 0x6E, 0x65, 0x73, 0x73, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x00, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugColorThicknessLabels.thicknessText[0],
};
#endif

/* S_FARCLIPTEXT.CPP */

#if defined(VERSION_US_REV1)
extern char s_farClipText[20];
#endif

/* G_DEBUGFIELDOFVIEWLABEL.CPP */

#if defined(VERSION_US_REV1)
DebugFieldOfViewLabel g_debugFieldOfViewLabel = {
    (unsigned int)s_farClipText,
    {
        0x66, 0x6F, 0x76, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x00, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugFieldOfViewLabel.fieldOfViewText[0],
};
#endif

/* S_AFFECTALLREGIONSTEXT.CPP */

#if defined(VERSION_US_REV1)
extern char s_affectAllRegionsText[20];
#endif

/* G_DEBUGAMBIENTCOLORLABEL.CPP */

#if defined(VERSION_US_REV1)
DebugColorLabel g_debugAmbientColorLabel = {
    (unsigned int)s_affectAllRegionsText,
    {
        0x61, 0x6D, 0x62, 0x20, 0x72, 0x65, 0x64, 0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugAmbientColorLabel.redText[0],
};
#endif

/* S_AMBGREENTEXT.CPP */

#if defined(VERSION_US_REV1)
extern char s_ambGreenText[16];
#endif

/* G_AMBGREENTEXTPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_ambGreenTextPointer[1] = {
    s_ambGreenText,
};
#endif

/* S_AMBBLUETEXT.CPP */

#if defined(VERSION_US_REV1)
extern char s_ambBlueText[16];
#endif

/* G_DEBUGDIRECTIONALCOLORLABEL.CPP */

#if defined(VERSION_US_REV1)
DebugColorLabel g_debugDirectionalColorLabel = {
    (unsigned int)s_ambBlueText,
    {
        0x64, 0x69, 0x72, 0x20, 0x72, 0x65, 0x64, 0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugDirectionalColorLabel.redText[0],
};
#endif

/* S_DIRGREENTEXT.CPP */

#if defined(VERSION_US_REV1)
extern char s_dirGreenText[16];
#endif

/* G_DIRGREENANDBLUELABELTEXT.CPP */
#if defined(VERSION_US_REV1)
void *g_dirGreenTextPointer[1] = {
    s_dirGreenText,
};

extern char g_dirBlueLabelText[16];
#endif

/* S_ALLREGIONSTEXT.CPP */

#if defined(VERSION_US_REV1)
void * g_SAllregionstextEncodedWords[1] = {
    (void *)&g_dirBlueLabelText,
};

extern char s_allRegionsText[12];
#endif

/* PAK_UPDATECHOICETEXT_DATA.CPP */
#if defined(VERSION_US_REV1)
void *g_pakUpdateChoiceTextData[1] = {
    s_allRegionsText,
};

extern char g_singleRegionText[16];
#endif

/* OPTION_DATA.CPP */
#if defined(VERSION_US_REV1)
void *g_singleRegionTextPointer[1] = {
    g_singleRegionText,
};

extern char s_sendAllLinksText[16];
#endif

/* G_DEBUGLEVELLABEL.CPP */

#if defined(VERSION_US_REV1)
struct {
    unsigned int titleTextPointer;
    unsigned char levelText[24];
    unsigned int levelTextPointer;
} g_debugLevelLabel = {
    (unsigned int)s_sendAllLinksText,
    {
        0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugLevelLabel.levelText[0],
};
#endif

/* S_LODCHGDISTTEXT.CPP */

#if defined(VERSION_US_REV1)
extern char s_lodChgDistText[24];
#endif

/* S_GLOBALSCALERTEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_lodChgDistText_PointerWord[1] = {
    (void *)&s_lodChgDistText,
};

extern char s_globalScalerText[24];
#endif

/* S_MUSICNONETEXT.CPP */

#if defined(VERSION_US_REV1)
void * s_globalScalerText_PointerWord[1] = {
    (void *)&s_globalScalerText,
};

extern char s_musicNoneText[24];
#endif

/* G_DEBUGLABELBLANKSTORAGE.CPP */

#if defined(VERSION_US_REV1)
struct {
    unsigned int titleTextPointer;
    unsigned char blankText[48];
    unsigned int blankTextPointer;
} g_debugLabelBlankStorage = {
    (unsigned int)s_musicNoneText,
    {
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,
    },
    (unsigned int)&g_debugLabelBlankStorage.blankText[0],
};
#endif

/* PAK_TOGGLETEXTCHOICE_DATA.CPP */

#if defined(VERSION_US_REV1)
struct {
    s32 g_modelEditorApplyToAllRecords;
    s32 g_menuSavedAudioSelection;
    s32 g_musicPreviewMenuActive;
    s32 g_menuMusicPreviewSelection;
    s32 g_menuBinaryChoice;
} g_pakToggleTextChoiceData __attribute__((aligned(4))) = {
    0,
    -1,
    0,
    16,
    1
};
typedef char g_pakToggleTextChoiceDataSizeCheck[(sizeof(g_pakToggleTextChoiceData) == 20) ? 1 : -1];
#endif

/* PAK_RESUMEMENUAUDIO.CPP */


/* Passes what SoundVoicePool_GetGlobalState returns to SoundVoicePool_Resume, then calls SoundElement_DisableMusicGainOverride and SoundElement_EnablePeriodicSound,
   and returns one. */
struct SoundVoicePool;

s32 Pak_ResumeMenuAudio(void) {
    SoundVoicePool_Resume(SoundVoicePool_GetGlobalState());
    SoundElement_DisableMusicGainOverride();
    SoundElement_EnablePeriodicSound();
    return 1;
}

/* Returns one. Nothing in the cartridge image calls it or stores its address as a word. */
s32 Pak_ReturnCallbackSuccess(void) {
    return 1;
}

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_pauseInventoryMenuResource,
   and returns one. */

s32 Pak_AllocateMenuFirst(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_pauseInventoryMenuResource);
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogBottomRowResource,
   and returns one. */

s32 Pak_AllocateMenuSecond(void *first, void *second, void *third) {
#if defined(VERSION_EU)
    Menu_AllocateMenu(third, second, g_pauseOptionsMenuResource_eu);
#elif defined(VERSION_EU_X)
    Menu_AllocateMenu(third, second, g_pauseOptionsMenuResource_eu_x);
#else
    Menu_AllocateMenu(third, second, g_initialDialogBottomRowResource);
#endif
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogTopRowResource,
   and returns one. */

s32 Pak_AllocateMenuThird(void *first, void *second, void *third) {
#if defined(VERSION_EU)
    Menu_AllocateMenu(third, second, g_initialDialogBottomRowResource);
#elif defined(VERSION_EU_X)
    Menu_AllocateMenu(third, second, g_initialDialogBottomRowResource);
#else
    Menu_AllocateMenu(third, second, g_initialDialogTopRowResource);
#endif
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_initialDialogMiddleRowResource,
   and returns one. */

s32 Pak_AllocateMenuFourth(void *first, void *second, void *third) {
#if defined(VERSION_EU)
    Menu_AllocateMenu(third, second, g_initialDialogTopRowResource);
#elif defined(VERSION_EU_X)
    Menu_AllocateMenu(third, second, g_initialDialogTopRowResource);
#else
    Menu_AllocateMenu(third, second, g_initialDialogMiddleRowResource);
#endif
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_volumeSettingsMenuResource,
   and returns one. */

s32 Pak_AllocateMenuFifth(void *first, void *second, void *third) {
#if defined(VERSION_EU)
    Menu_AllocateMenu(third, second, g_initialDialogMiddleRowResource);
#elif defined(VERSION_EU_X)
    Menu_AllocateMenu(third, second, g_initialDialogMiddleRowResource);
#else
    Menu_AllocateMenu(third, second, g_volumeSettingsMenuResource);
#endif
    return 1;
}
#endif

/* PAK_RESTOREAUDIOANDCLOSEMENU.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)

/* Stops sound for a menu, restores the saved music playback state and control flag, and returns what Menu_TryCreateMenu gives for the three arguments. */
s32 Pak_RestoreAudioAndCloseMenu(void *first, void *second, void *third) {
    SoundElement_StopAudioExceptKey(-1);
    SoundElement_SetVoiceMixValue(0);
    if (g_musicPreviewMenuActive != 0) {
        SoundElement_EnableMusicGainOverride();
    }
    SoundElement_SetMusicPlaybackEnabled(g_menuSavedAudioSelection);
    Control_SetMenuControlFlag();
    return Menu_TryCreateMenu(first, second, third);
}

/* Adjusts the third volume setting through Menu_AdjustValue in steps of 8, skipping the value 247 so it lands on 248. */
s32 Pak_AdjustSpeechVolume(void *first, void *second) {
    u8 *option = &g_gameSettings.volume[2];
    s32 value = *option;

    value = Menu_AdjustValue(second, value, 8, 0, 0xFF, 0);
    if (value == 247) {
        value = 248;
    }
    *option = value;
    return 0;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Stops sound for a menu: calls SoundElement_StopAudioExceptKey with -1 and SoundElement_SetVoiceMixValue with zero, calls
   SoundElement_EnableMusicGainOverride when g_musicPreviewMenuActive is set, passes g_menuSavedAudioSelection to SoundElement_SetMusicPlaybackEnabled, calls Control_SetMenuControlFlag and
   returns what Menu_TryCreateMenu gives for the three arguments. */
s32 Pak_RestoreAudioAndCloseMenu(void *first, void *second, void *third) {
    SoundElement_StopAudioExceptKey(-1);
    SoundElement_SetVoiceMixValue(0);
    if (g_musicPreviewMenuActive != 0) {
        SoundElement_EnableMusicGainOverride();
    }
    SoundElement_SetMusicPlaybackEnabled(g_menuSavedAudioSelection);
    Control_SetMenuControlFlag();
    return Menu_TryCreateMenu(first, second, third);
}

/* Replaces the option byte g_soundEffectsVolumeOption_PakFormatvolumeslotone with what Menu_AdjustValue returns for the second argument, that byte, 8, 0, 0xFF and 0, turning 0xF7 into 0xF8, and returns zero. */
s32 Pak_AdjustSpeechVolume(void *first, void *second) {
    u8 *option = &g_gameSettings.volume[2];
    s32 value = *option;

    value = Menu_AdjustValue(second, value, 8, 0, 0xFF, 0);
    if (value == 247) {
        value = 248;
    }
    *option = value;
    return 0;
}
#endif

/* PAK_UPDATETHIRDVOLUMELABEL.CPP */

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define VOLUME_BYTE g_gameSettings.volume[2]
#else
#define VOLUME_BYTE g_gameSettings.volume[2]
#endif
/* Shows one of three fixed volume texts for steps zero, fifteen and minus
 * sixteen from the option byte g_soundEffectsVolumeOption_PakFormatvolumeslotone. Other steps are formatted into
 * the alternate text with the positive or negative format. */
s32 Pak_UpdateSpeechVolumeLabel(LayeredText *field) {
    s32 step = (VOLUME_BYTE - 128) / 8;
    char *text;

    if (step == 0) {
        field->text = &g_speechVolumeNeutralLabel;
    } else if (step == 15) {
        field->text = &g_speechVolumeMaximumLabel;
    } else if (step == -16) {
        field->text = &g_speechVolumeMinimumLabel;
    } else if (step > 0) {
        field->text = (u8 **)&g_speechVolumeText;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepFormat, step);
#else
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepPaddedFormat, step);
#endif
    } else {
        field->text = (u8 **)&g_speechVolumeText;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepFormat, step);
#else
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepPaddedFormat, step);
#endif
    }
    return 0;
}

#endif

/* Keep this source unit's macros local to its body. */
#undef VOLUME_BYTE

/* PAK_ADJUSTVOLUMESLOTZERO.CPP */



/* Adjusts the volume in steps of eight and starts a sound preview when no preview is playing. */

s32 Pak_AdjustMusicVolume(void *entry, void *menu) {
    s32 volume;
    volume = g_gameSettings.volume[0];
    volume = Menu_AdjustValue(menu, volume, 8, 0, 0xFF, 0);
    if(volume==247)volume=248;
    g_gameSettings.volume[0]=volume;
    if (SoundElement_GetMusicPlaybackEnabled() <= 0) {
        SoundElement_SetMusicPlaybackEnabled(1);
    }
    return 0;
}

/* PAK_UPDATEFIRSTVOLUMELABEL.CPP */

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define VOLUME_BYTE g_gameSettings.volume[0]
#else
#define VOLUME_BYTE g_gameSettings.volume[0]
#endif
/* Selects a localized volume label and formats an intermediate value.
 * DE/US-rev1 source and proofs remain preserved separately. */

/* Points a field's text at one of g_volumeZeroNeutralLabelFixed, g_volumeZeroMaximumLabelFixed or g_volumeZeroMinimumLabelFixed when the option byte g_gameSettingsVolumeBytes measured from 0x80 in steps of eight is zero, fifteen or minus sixteen, and otherwise at g_volumeZeroValueLabelFixed with the step formatted into it, returning zero. */
s32 Pak_UpdateMusicVolumeLabel(LayeredText *field) {
    s32 step = (VOLUME_BYTE - 128) / 8;
    char *text;

    if (step == 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroNeutralLabels;
#else
        field->text = &g_volumeZeroNeutralLabelFixed;
#endif
    } else if (step == 15) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroMaximumLabels;
#else
        field->text = &g_volumeZeroMaximumLabelFixed;
#endif
    } else if (step == -16) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroMinimumLabels;
#else
        field->text = &g_volumeZeroMinimumLabelFixed;
#endif
    } else if (step > 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroValueLabels;
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepFormat, step);
#else
        field->text = (u8 **)&g_volumeZeroValueLabelFixed;
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepPaddedFormat, step);
#endif
    } else {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text = g_volumeZeroValueLabels;
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepFormat, step);
#else
        field->text = (u8 **)&g_volumeZeroValueLabelFixed;
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepPaddedFormat, step);
#endif
    }
    return 0;
}

#endif

/* Keep this source unit's macros local to its body. */
#undef VOLUME_BYTE

/* PAK_ADJUSTVOLUMESLOTONE.CPP */


/* Replaces the option byte g_soundEffectsVolumeOption with what Menu_AdjustValue returns for the second argument, that byte, 8, 0, 0xFF and 0, turning 0xF7 into 0xF8, and returns zero. */
s32 Pak_AdjustSoundEffectsVolume(void *first, void *second) {
    u8 *option = &g_gameSettings.volume[1];
    s32 value = *option;

    value = Menu_AdjustValue(second, value, 8, 0, 0xFF, 0);
    if (value == 247) {
        value = 248;
    }
    *option = value;
    return 0;
}

/* PAK_FORMATVOLUMESLOTONE.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Pak_FormatSoundEffectsVolume(struct Field *field) {
    s32 step = (g_gameSettings.volume[1] - 128) / 8;
    char *text;

    if (step == 0) {
        field->text = g_soundEffectsVolumeNeutralLabel;
    } else if (step == 15) {
        field->text = g_soundEffectsVolumeMaximumLabel;
    } else if (step == -16) {
        field->text = g_soundEffectsVolumeMinimumLabel;
    } else if (step > 0) {
        field->text = g_sfxVolumeText;
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepFormat, step);
    } else {
        field->text = g_sfxVolumeText;
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepFormat, step);
    }
    return 0;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Points a field's text at one of g_soundEffectsVolumeNeutralLabel, g_soundEffectsVolumeMaximumLabel or g_soundEffectsVolumeMinimumLabel when the option byte g_soundEffectsVolumeOption measured from 0x80 in steps of eight is zero, fifteen or minus sixteen, and otherwise at g_sfxVolumeText with the step formatted into it, returning zero. */
s32 Pak_FormatSoundEffectsVolume(struct Field *field) {
    s32 step = (g_gameSettings.volume[1] - 128) / 8;
    char *text;

    if (step == 0) {
        field->text = &g_soundEffectsVolumeNeutralLabel;
    } else if (step == 15) {
        field->text = &g_soundEffectsVolumeMaximumLabel;
    } else if (step == -16) {
        field->text = &g_soundEffectsVolumeMinimumLabel;
    } else if (step > 0) {
        field->text = &g_sfxVolumeText;
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumePositiveStepPaddedFormat, step);
    } else {
        field->text = &g_sfxVolumeText;
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_volumeNegativeStepPaddedFormat, step);
    }
    return 0;
}
#endif

/* PAK_SELECTMUSICPREVIEW.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Pak_SelectMusicPreview(s32 unusedEvent, Shared_PakMenu *pThis) {
    s32 selection = g_menuMusicPreviewSelection;
    if (pThis->owner->inputFlags & 0x20202) {
        selection--;
        if (selection < 0) {
            selection = 22;
        } else if (selection == 14) {
            selection = 11;
        }
    }
    if (pThis->owner->inputFlags & 0x4D101) {
        selection++;
        if (selection >= 23) {
            selection = 0;
        } else if (selection == 12) {
            selection = 15;
        }
    }
    g_menuMusicPreviewSelection = selection;
    SoundElement_SetMusicPlaybackEnabled(selection);
    return 0;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Cycles a menu selection from directional input while skipping reserved entries. */
s32 Pak_SelectMusicPreview(s32 entry, struct PakControllerRequestView *menu) {
    s32 musicSelection;
    musicSelection = g_menuMusicPreviewSelection;
    if (menu->inner->buttons & 0x20202) {
        musicSelection -= 1;
        if (musicSelection < 0) {
            musicSelection = 22;
        } else if (musicSelection == 14) {
            musicSelection = 11;
        }
    }
    if (menu->inner->buttons & 0x4D101) {
        musicSelection += 1;
        if (musicSelection >= 23) {
            musicSelection = 0;
        } else if (musicSelection == 12) {
            musicSelection = 15;
        }
    }
    g_menuMusicPreviewSelection = musicSelection;
    SoundElement_SetMusicPlaybackEnabled(musicSelection);
    return 0;
}
#endif

/* PAK_OPENMUSICPREVIEWMENU.CPP */

/* Shows the fixed sound value text when g_menuMusicPreviewSelection is zero. Otherwise
 * formats its current value into the alternate text (the current menu
 * language's line in the EU builds), two bytes before the line length
 * reported by the text item helper. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* The menu language byte selects the localized preview text. */
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
        text = field->text[g_gameSettings.language];
#else
        text = (char *)*VALUE_TEXT;
#endif
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2),
                        VALUE_FORMAT, g_menuMusicPreviewSelection);
    }
    return 0;
}

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

#if defined(VERSION_US_REV1)
/* Toggles the owner of the second argument between states 1 and 2 through its
   state word, leaving any other state alone; returns zero. */

s32 Pak_ToggleOwnerMode(void *entry, struct Holder *holder) {
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

/* Points a field's text at g_ownerModePersonViewText when the owner of the second argument has its
   state word equal to one, and at g_ownerModeOtherText otherwise; returns zero, doing nothing without an
   owner. */

s32 Pak_UpdateOwnerModeText(struct PakActionLabelView *field, struct Holder *holder) {
    if (holder->owner == 0) {
        return 0;
    }
    if (holder->owner->value == 1) {
        field->text = g_ownerModePersonViewText;
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

/* Keep this source unit's macros local to its body. */
#undef VALUE_FORMAT
#undef VALUE_TEXT

/* PAK_UPDATESCREENMODEAVAILABILITY.CPP */


/* Menu item flag set while the screen mode needs the expansion pak. */
#define MENU_ITEM_FLAG_UNAVAILABLE 0x800000

/* Marks a record unavailable unless Defs_GetMemorySize reports the base RAM size for
   it, in which case the mark is cleared; then stores what Frontend_GetScreenModePalette_Playeroption returns in the record's value field.
   Returns zero. */




s32 Pak_UpdateScreenModeAvailability(struct MenuBuildEntry *record) {
    if (Defs_GetMemorySize() != 0x400000) {
        record->flags |= 0x800000;
    } else {
        record->flags &= ~MENU_ITEM_FLAG_UNAVAILABLE;
    }
    record->resource = Frontend_GetScreenModePalette();
    return 0;
}

/* Calls Frontend_StartScreenModeFade_PakUpdatescreenmodeavailability and returns zero. */

s32 Pak_StartScreenModeFade(void) {
    Frontend_StartScreenModeFade();
    return 0;
}

#if defined(VERSION_US_REV1)
/* Flips g_textureVariationBypassEnabled between zero and one and returns zero. */

s32 Pak_ToggleTextureVariationBypass(void) {
    g_textureVariationBypassEnabled = g_textureVariationBypassEnabled == 0;
    return 0;
}

/* Points a field's text at g_textureVariationBypassEnabledLabels when the option g_textureVariationBypassEnabled is set and at g_textureVariationBypassDisabledLabels otherwise, and returns
   zero: the label an option menu shows for that option. */

s32 Pak_UpdateTextureVariationBypassText(struct PakActionLabelView *field) {
    if (g_textureVariationBypassEnabled != 0) {
        field->text = g_textureVariationBypassEnabledLabels;
    } else {
        field->text = g_textureVariationBypassDisabledLabels;
    }
    return 0;
}
#endif

/* Keep this source unit's macros local to its body. */
#undef MENU_ITEM_FLAG_UNAVAILABLE

/* PAK_ENTERPLAYEROPTIONS.CPP */

/* Sets a player state to 2, then in multiplayer (g_gameSettings.local) clears and otherwise sets bit 0x800000 in both of its actor's visibility masks at 0x80 and 0xA8, and refreshes the audio state through SoundVoicePool_GetGlobalState and SoundVoicePool_Pause with that mask. */

void Pak_EnterPlayerOptions(PlayerOptionsEntry *player) {
    s32 mask;

    player->state = 2;
    Control_SaveControllerSetup();
    mask = 0x800000;
    if (g_gameSettings.local != 0) {
        mask = 0xFF7FFFFF;
        player->actor->mask80 &= mask;
        player->actor->maskA8 &= mask;
    } else {
        player->actor->mask80 |= mask;
        player->actor->maskA8 |= mask;
    }
    SoundVoicePool_Pause(SoundVoicePool_GetGlobalState());
}

/* Calls Control_RestoreControllerSetup_FrontendDestroypausemenu and nothing else. */

void Pak_RestoreControllerSetup(void) {
    Control_RestoreControllerSetup();
}

/* Calls Menu_DrawMenuEntries and nothing else. */

void Pak_RenderMenuEntryCallback(struct MenuStyle *menu, s8 *member) {
    Menu_DrawMenuEntries(menu, member);
}

/* VOLUME.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
s32 Volume_AllocateMenuOne_eu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_pauseInventoryMenuList);
    return 1;
}

s32 Volume_AllocateMenuTwo_eu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_pauseOptionsMenuResource_eu);
    return 1;
}

s32 Volume_AllocateMenuThree_eu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogBottomRowResource);
    return 1;
}

s32 Volume_AllocateMenuFour_eu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogTopRowResource);
    return 1;
}

s32 Volume_AllocateMenuFive_eu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_initialDialogMiddleRowResource);
    return 1;
}

s32 Volume_AllocateMenuSix_eu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_volumeSettingsMenuList);
    return 1;
}
#endif

/* OPTION.CPP */
#if defined(VERSION_US_REV1)
s32 Pak_ToggleTextChoice(void) {
    g_modelEditorApplyToAllRecords ^= 1;
    return 0;
}
/* Points a field's text at g_modelEditorApplyToAllEnabledText when the option g_modelEditorApplyToAllRecords is set and at g_modelEditorApplyToAllDisabledText otherwise, and returns
   zero: the label an option menu shows for that option. */
s32 Pak_UpdateChoiceText(struct PakActionLabelView *field) {
    if (g_modelEditorApplyToAllRecords != 0) {
        field->text = g_modelEditorApplyToAllEnabledText;
    } else {
        field->text = g_modelEditorApplyToAllDisabledText;
    }
    return 0;
}
/* Keeps an option field and the remembered byte g_playerModelLighting[0].ambient[index] in step, giving a field still at -1 the remembered value and otherwise remembering the field low byte, then mirrors it into g_savedPlayerModelLighting[index] and formats it into the field text with s_menuByteOptionValueFormat three bytes before the length Menu_CountLineChars reports, returning zero. */

s32 Pak_SyncPrimaryByteOption(struct Field *field, s32 index) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_playerModelLighting[0].ambient[index];
    } else {
        g_playerModelLighting[0].ambient[index] = (u8)field->value;
    }
    g_savedPlayerModelLighting[index] = g_playerModelLighting[0].ambient[index];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_playerModelLighting[0].ambient[0] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedPlayerModelLighting[0] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncAmbientRed(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_playerModelLighting[0].ambient[0];
    } else {
        g_playerModelLighting[0].ambient[0] = (u8)field->value;
    }
    g_savedPlayerModelLighting[0] = g_playerModelLighting[0].ambient[0];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_playerModelLighting[0].ambient[1] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedPlayerModelLighting[1] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncAmbientGreen(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_playerModelLighting[0].ambient[1];
    } else {
        g_playerModelLighting[0].ambient[1] = (u8)field->value;
    }
    g_savedPlayerModelLighting[1] = g_playerModelLighting[0].ambient[1];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_playerModelLighting[0].ambient[2] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedPlayerModelLighting[2] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncAmbientBlue(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_playerModelLighting[0].ambient[2];
    } else {
        g_playerModelLighting[0].ambient[2] = (u8)field->value;
    }
    g_savedPlayerModelLighting[2] = g_playerModelLighting[0].ambient[2];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_secondaryMenuByteOptions[index] in step, giving a field still at -1 the remembered value and otherwise remembering the field low byte, then mirrors it into g_savedSecondaryMenuByteOptions[index] and formats it into the field text with s_menuByteOptionValueFormat three bytes before the length Menu_CountLineChars reports, returning zero. */
s32 Pak_SyncSecondaryByteOption(struct Field *field, s32 index) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_secondaryMenuByteOptions[index];
    } else {
        g_secondaryMenuByteOptions[index] = (u8)field->value;
    }
    g_savedSecondaryMenuByteOptions[index] = g_secondaryMenuByteOptions[index];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_secondaryMenuByteOptions[0] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedSecondaryMenuByteOptions[0] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncDirectionalRed(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_secondaryMenuByteOptions[0];
    } else {
        g_secondaryMenuByteOptions[0] = (u8)field->value;
    }
    g_savedSecondaryMenuByteOptions[0] = g_secondaryMenuByteOptions[0];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_secondaryMenuByteOptions[1] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedSecondaryMenuByteOptions[1] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncDirectionalGreen(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_secondaryMenuByteOptions[1];
    } else {
        g_secondaryMenuByteOptions[1] = (u8)field->value;
    }
    g_savedSecondaryMenuByteOptions[1] = g_secondaryMenuByteOptions[1];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_secondaryMenuByteOptions[2] in step, giving a field still at -1 the remembered value and otherwise remembering the field's low byte, then mirrors it into g_savedSecondaryMenuByteOptions[2] and formats it into the field's text with s_menuByteOptionValueFormat three bytes before the length Menu_CountLineChars reports, returning zero. */
s32 Pak_SyncDirectionalBlue(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_secondaryMenuByteOptions[2];
    } else {
        g_secondaryMenuByteOptions[2] = (u8)field->value;
    }
    g_savedSecondaryMenuByteOptions[2] = g_secondaryMenuByteOptions[2];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
#endif

/* PAK_ADJUSTMENUCHOICE.CPP */

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

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_pakAdjustMenuChoiceResourceA,
   and returns one. */

s32 Pak_OpenMenuChoiceFirstMenu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_pakAdjustMenuChoiceResourceA);
    return 1;
}

/* Calls Menu_AllocateMenu with the third argument, the second argument and the resource g_pakAdjustMenuChoiceResourceB,
   and returns one. */

s32 Pak_OpenMenuChoiceSecondMenu(void *first, void *second, void *third) {
    Menu_AllocateMenu(third, second, g_pakAdjustMenuChoiceResourceB);
    return 1;
}
#endif

/* Retained data for this translation unit. */
#if defined(VERSION_DE)
float g_musicPreviewScaleTriple[3] = {
    6.0f, 0.0035211267f, 64.0f,
};
#endif
#if defined(VERSION_EU_X)
unsigned int k_pakFormatMusicPreviewLayout[3] = {
    0x0000004B, 0x00000014, 0x00000028,
};
#endif
#if defined(VERSION_EU)
unsigned int k_pakFormatMusicPreviewPackedWords[3] = {
    0x4A0D4A67, 0x4A178744, 0xC8250F0F,
};
#endif
#if defined(VERSION_US_REV1)
unsigned int g_PakEncodedWords[1] = {
    0x00000028,
};
#endif
#if defined(VERSION_US_REV1)
float g_menuBoxCameraOffset[3] = {
    0.0f, 0.0f, -550.0f,
};
#endif
#if defined(VERSION_US_REV1)
char g_artsendModeOnText[28] = "_SMEartsend mode  :    on";
#endif
#if defined(VERSION_US_REV1)
char s_artsendModeOffText[24] = "artsend mode  :   off";
#endif
#if defined(VERSION_US_REV1)
char s_personText[24] = "person        :   1st";
#endif
#if defined(VERSION_US_REV1)
char s_thirdPersonDebugText[24] = "person        :   3rd";
#endif
#if defined(VERSION_US_REV1)
char s_weaponHiddenText[24] = "weapon        :hidden";
#endif
#if defined(VERSION_US_REV1)
char s_weaponVisText[24] = "weapon        :   vis";
#endif
#if defined(VERSION_US_REV1)
char s_shadowsText[24] = "3d shadows    :    on";
#endif
#if defined(VERSION_US_REV1)
char s_shadowsOffText[24] = "3d shadows    :   off";
#endif
#if defined(VERSION_US_REV1)
char s_editFogText[12] = "edit fog";
#endif
#if defined(VERSION_US_REV1)
char s_editLightText[12] = "edit light";
#endif
#if defined(VERSION_US_REV1)
char s_infiniteAmmoText[24] = "infinite ammo :    on";
#endif
#if defined(VERSION_US_REV1)
char s_infiniteAmmoOffText[24] = "infinite ammo :   off";
#endif
#if defined(VERSION_US_REV1)
char s_fancyLightingText[24] = "fancy lighting:    on";
#endif
#if defined(VERSION_US_REV1)
char s_fancyLightingOffText[24] = "fancy lighting:   off";
#endif
#if defined(VERSION_US_REV1)
char s_farClipText[20] = "far clip        ";
#endif
#if defined(VERSION_US_REV1)
char s_affectAllRegionsText[20] = "affect all regions";
#endif
#if defined(VERSION_US_REV1)
char s_ambGreenText[16] =
    "amb green 000\000\000";
#endif
#if defined(VERSION_US_REV1)
char s_ambBlueText[16] =
    "amb blue  000\000\000";
#endif
#if defined(VERSION_US_REV1)
char s_dirGreenText[16] =
    "dir green 000\000\000";
#endif
#if defined(VERSION_US_REV1)
char g_dirBlueLabelText[16] = "dir blue  000";
#endif
#if defined(VERSION_US_REV1)
char s_allRegionsText[12] = "all regions";
#endif
#if defined(VERSION_US_REV1)
char g_singleRegionText[16] = "single region";
#endif
#if defined(VERSION_US_REV1)
char s_sendAllLinksText[16] = "send all links";
#endif
#if defined(VERSION_US_REV1)
char s_lodChgDistText[24] = "lod chg dist  :      ";
#endif
#if defined(VERSION_US_REV1)
char s_globalScalerText[24] = "global scaler :      ";
#endif
#if defined(VERSION_US_REV1)
char s_musicNoneText[24] = "music         :  none";
#endif
