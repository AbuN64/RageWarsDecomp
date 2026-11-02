#include "include_asm.h"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WORLD.H"
#include "TYPES.H"
#include "FRONTEND/MODEL_SETMODELPREVIEWPOSITION.H"

/* Stores a count in a record and, when it is positive, the handle Scene_FindModelIdIndex returns for
   g_world_AchieveUpdateresultsscreen and that count at offset 0x34; otherwise the handle is -1. Returns the handle. */


extern s32 Scene_FindModelIdIndex(struct Shared_World *, s32);

s32 Model_SetPreviewModel(struct RecordFrontendSetPreviewModel *record, s32 count) {
    record->count = count;
    record->handle = -1;
    if (count > 0) {
        record->handle = Scene_FindModelIdIndex(&g_world, count);
    }
    return record->handle;
}

/* Returns the word at offset 0x0 of a record. */
s32 Model_GetModelRecordCount(s32 *record) {
    return ((struct RecordFrontendSetPreviewModel *)record)->count;
}

/* Stores a value into the word at offset 0xB8 of an object. */


void Model_SetPreviewRenderFlags(struct ObjectB8 *object, s32 value) {
    object->value = value;
}

/* Returns by value the three-word vector at offset 0x10 of an object. */


struct Triple Model_GetPreviewPosition(struct ModelPreviewPositionView *object) {
    return object->vector;
}

/* Stores a three-word vector passed by value into offset 0x10 of an object. */


void Model_SetModelPreviewPosition(struct ModelPreviewPositionView *object, struct Triple vector) {
    object->vector = vector;
}


