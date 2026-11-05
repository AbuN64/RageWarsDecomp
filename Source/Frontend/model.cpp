#include "include_asm.h"
#include "Common/menu_model_preview.h"
#include "Common/sharedplayer.h"
#include "Common/world.h"
#include "types.h"
#include "Frontend/model_setmodelpreviewposition.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Frontend/frontend.h"

/* unit MODEL.CPP */
/* Stores a count in a record and, when it is positive, the handle Scene_FindModelIdIndex returns for
   g_world_AchieveUpdateresultsscreen and that count at offset 0x34; otherwise the handle is -1. Returns the handle. */
s32 Model_SetPreviewModel(struct RecordFrontendSetPreviewModel *record, s32 count) {
    record->count = count;
    record->handle = -1;
    if (count > 0) {
        record->handle = Scene_FindModelIdIndex(&g_world, count);
    }
    return record->handle;
}

/* Returns the count field of the record. */
s32 Model_GetModelRecordCount(s32 *record) {
    return ((struct RecordFrontendSetPreviewModel *)record)->count;
}

/* Stores the preview render flags of the model object. */
void Model_SetPreviewRenderFlags(struct ObjectB8 *object, s32 value) {
    object->value = value;
}

/* Returns the preview position vector of the model object by value. */
struct Triple Model_GetPreviewPosition(struct ModelPreviewPositionView *object) {
    return object->vector;
}

/* Stores the preview position vector of the model object. */
void Model_SetModelPreviewPosition(struct ModelPreviewPositionView *object, struct Triple vector) {
    object->vector = vector;
}
