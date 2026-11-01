#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/REQUESTRECAT10.H"
#include "TYPES.H"
#include "include_asm.h"
#include "COMMON/CHARACTERSELECTIONROOT.H"

/* KEY.CPP */
/* Returns the index of the first of the seventeen 0x70-byte slots of g_frontendKeyUnlockEntries whose leading word equals the argument, or zero when none does. */

extern struct FrontendKeySlotEntry g_frontendKeyUnlockEntries[];

s32 Key_FindKeyIndex(s32 key) {
    s32 index = 0;
    s32 found = 0;
    s32 i;

    for (i = 0; i < 17 && !found; i++) {
        if (g_frontendKeyUnlockEntries[i].key == key) {
            found = 1;
            index = i;
        }
    }
    return index;
}

extern s_CharacterData g_frontendKeyEntries[];

/* Returns the index of the first of the seventeen 0x70-byte slots of g_frontendKeyEntries whose leading word equals the argument, or zero when none does. Adapted from Key_FindKeyIndex_Key with the slot word g_frontendKeyEntries changed. */

/* Returns the second word of the first of the seventeen 0x70-byte slots of g_frontendKeyEntries whose leading word equals the argument, or zero when none does.
   Adapted from Key_FindCharacterPreviewRow with the returned index changed to the slot's second word g_frontendKeyUnlockEntries. */

s32 Key_FindCharacterPreviewRow(s32 key) {
    s32 index = 0;
    s32 found = 0;
    s32 i;

    for (i = 0; i < 17 && !found; i++) {
        if (g_frontendKeyEntries[i].id == key) {
            found = 1;
            index = i;
        }
    }
    return index;
}

s32 Key_GetCharacterPreviewModel(s32 key) {
    s32 value = 0;
    s32 found = 0;
    s32 i;

    for (i = 0; i < 17 && !found; i++) {
        if (g_frontendKeyEntries[i].id == key) {
            found = 1;
            value = g_frontendKeyEntries[i].value;
        }
    }
    return value;
}
