#include "include_asm.h"

#include "COMMON/WORLD.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/OPTIONEDITSTATE.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "../../../../sdk/include/AUDIO/sprintf.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/SOUNDINFO.H"
#include "MENU/PAK/MODEL.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"
#include "MENU/MENU_CREATEMENUFROMPARAMETERS.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"
#include "OVLGAME/MATCH.H"

#if defined(VERSION_US_REV1)
/* Edits a byte, integer, or float option and propagates it to the active resource records. */
 /* extern */
 /* extern */
 /* extern */
 /* extern */
 /* extern */

s32 Pak_AdjustModelField(OptionEditState *label, OptionEditState *menu, s32 third, s32 wrap, s32 fieldOffset, s32 step, s32 maximum, f32 displayDivisor) {
    s32 modelIndex;
    s32 countValue;
    s32 textAddress;
    s32 modelRecordIndexOrLimit;
    s32 length;
    u8 *fieldAddress;
    s32 fieldValue;
    OptionEditState *modelOwner;
    OptionEditState *selectedObject;
    ResourceManagerState *resourceManager;
    char *modelRecord;
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
                Libc_FormatString(textAddress + length, &g_pakFormatInt06, (s32) ((f32) fieldValue / displayDivisor));
                if (g_modelEditorApplyToAllRecords != 0) {
                    resourceManager = SetN64_GetPackSection(g_modelEditPack, 0);
                    modelRecordIndexOrLimit = 0;
                    countValue = resourceManager->count;
                    resourceManager=&((OptionEditContext *)(resourceManager))->modelRecords;
                    if (countValue > 0) {
                        do {
                            modelRecord = (char *)resourceManager + modelRecordIndexOrLimit * 100;
                            fieldAddress = modelRecord + fieldOffset;
                            switch(wrap) {
                            case 0: *fieldAddress=fieldValue;break;
                            case 1: *(s32 *)fieldAddress=fieldValue;break;
                            case 2: *(f32 *)fieldAddress=fieldValue;break;
                            }
                            modelRecordIndexOrLimit += 1;
                        } while (modelRecordIndexOrLimit < countValue);
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
#include "COMMON/GAME_SESSION.H"



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
extern s32 Pak_AdjustModelField(OptionEditState *, OptionEditState *, s32, s32, s32, s32, s32, f32);

void Pak_AdjustModelByteZero(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 0, 0, 1, 0xFF, (1.0f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 0, 1, 1, 0xFF and the pooled constant (1.0f). */

void Pak_AdjustModelByteOne(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 0, 1, 1, 0xFF, (1.0f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 0, 2, 1, 0xFF and the pooled constant (1.0f). */

void Pak_AdjustModelByteTwo(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 0, 2, 1, 0xFF, (1.0f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 1, 8, 0xA, 0x7D0 and the pooled constant (1.0f). */

void Pak_AdjustModelWordAt08(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 1, 8, 10, 2000, (1.0f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 2, 0x10, 0x66, 0xA000 and the pooled constant (10.239999771118164f). */

void Pak_AdjustModelFloatAt10(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 2, 16, 102, 0xA000, (10.239999771118164f));
}

/* Forwards its three arguments to Pak_AdjustModelField with 2, 0x14, 1, 0xB4 and the pooled constant
   (1.0f). */

void Pak_AdjustModelFloatAt14(void *first, void *second, void *third) {
    Pak_AdjustModelField(first, second, third, 2, 20, 1, 180, (1.0f));
}
#endif
