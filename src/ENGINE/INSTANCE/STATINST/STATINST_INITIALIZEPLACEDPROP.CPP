#include "COMMON/WORLD.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PROPGEOMETRY.H"
#include "COMMON/MANAGER.H"
#include "TYPES.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
extern s32 g_gameFrameCounter;

/* Initialises a placed prop from its compact record: resets its state and owner, loads its model and
 * caches the squared model radius, places it on the grid by multiplying the record's byte cell
 * coordinates by the caller's cell spacing and its packed height by 5.12, mirrors either axis for
 * flags 0x10 and 0x20, turns it by the quarter turn the low two bits of the same byte select, builds
 * scale and position into a matrix copied into the object, sets its bounding box either as a fixed
 * cube for flag 0x40 or from the record's six signed extents at a tenth of a cell with a half-unit
 * margin, copies the position, links its path segment and takes the next colour key and colour
 * frame. This is the compact-record twin of Statinst_InitializePlacedPropFullRecord_eu, which does the same work from a record
 * carrying full floats. The rounded literals are the cartridge's: 5.12 is 0x40A3D70A, 102.4 is
 * 0x42CCCCCC and 10.24 is 0x4123D70A. */




/* The record is packed into 0x1C bytes: the cell coordinates, the height and the six extents are
 * bytes scaled on the way in, where Statinst_InitializePlacedPropFullRecord_eu's record carries the same quantities as floats. */





extern s32 g_defaultCameraSurfaceType[];



extern void Insthdr_ResetInstanceRenderIndices(PlacedProp *, PackedPlacedPropDefinition *, s32, char *);
extern PropGeometry *Scene_GetActorDefinition(void *, s32);
extern void ScaleMatrixLocal(char *, f32, f32, f32);
extern void TranslateMatrix(char *, f32, f32, f32);
extern void SwapMatrixUpForward(char *);
extern void CopyMatrix(char *, char *);
extern void Graphu64_ConvertMatrixToFixed(char *, char *);

#if defined(VERSION_DE)
extern s32 InstHdr_GetActorType(void *);
#endif
static inline s32 advancePropKey(void) {
    s32 next;

    next = g_staticObjectResourceSerial + 1;
    g_staticObjectResourceSerial = next;
    if (next == 0x3FFFFF) {
        g_staticObjectResourceSerial = 0x380000;
    }
    return g_staticObjectResourceSerial;
}

void Statinst_InitializePlacedProp(PlacedProp *prop, PackedPlacedPropDefinition *record, s32 owner, char *segments, f32 spacing) {
    char matrix[64];
    CVector3 position;
    PropGeometry *model;
    f32 turn;
    f32 x;
    f32 z;

    Insthdr_ResetInstanceRenderIndices(prop, record, owner, segments);
    prop->state = 0;
    prop->id = record->id;
    prop->owner = owner;
    prop->reservedWord = -1;
    prop->reservedWord1 = 0;
    prop->reservedWord2 = 0;
    prop->reservedWord3 = 0;
    turn = 0.0f;
    prop->model = Scene_GetActorDefinition(&g_world, record->model);
    prop->fade = 16;
    prop->animationTimer = 0;
    model = prop->model;
    model->radiusSquared = model->radius * model->radius;
    x = record->cellX * spacing;
    position.x = x;
    if (record->placement & 0x10) {
        position.x = -x;
    }
    z = record->cellZ * spacing;
    position.z = z;
    if (record->placement & 0x20) {
        position.z = -z;
    }
    position.y = record->height * 5.119999886f;
    switch (record->placement & 3) {
    case 0:
        turn = 0.0f;
        break;
    case 1:
        turn = 1.570796490f;
        break;
    case 2:
        turn = 3.141592979f;
        break;
    case 3:
        turn = 4.712389469f;
        break;
    }
    prop->flags = record->flags;
    BuildYawMatrix(matrix, turn);
    ScaleMatrixLocal(matrix, record->scale, record->scale, record->scale);
    TranslateMatrix(matrix, position.x, position.y, position.z);
    SwapMatrixUpForward(matrix);
    if (prop->flags & 0x40) {
        prop->min.x = position.x - 102.3999939f;
        prop->min.y = position.y - 102.3999939f;
        prop->min.z = position.z - 102.3999939f;
        prop->max.x = position.x + 102.3999939f;
        prop->max.y = position.y + 102.3999939f;
        prop->max.z = position.z + 102.3999939f;
        prop->surfaceType = g_defaultCameraSurfaceType[0];
    } else {
        prop->min.x = position.x + record->extents[0] * 10.23999977f - 0.5f;
        prop->min.y = position.y + record->extents[2] * 10.23999977f - 0.5f;
        prop->min.z = position.z + record->extents[4] * 10.23999977f - 0.5f;
        prop->max.x = position.x + record->extents[1] * 10.23999977f + 0.5f;
        prop->max.y = position.y + record->extents[3] * 10.23999977f + 0.5f;
        prop->max.z = position.z + record->extents[5] * 10.23999977f + 0.5f;
        prop->surfaceType = record->value;
    }
    CopyMatrix(prop->matrix, matrix);
    Graphu64_ConvertMatrixToFixed(matrix, prop->transform);
    prop->position = position;
    if (record->segment == 0xFFFF) {
        prop->segment = 0;
    } else {
        prop->segment = segments + record->segment * 32;
    }
    prop->key = advancePropKey() << 10;
    prop->colorFrame = (u8)g_gameFrameCounter - 1;
#if defined(VERSION_DE)
    if ((u32)(InstHdr_GetActorType(prop) - 9) < 2) {
        prop->flags |= 0x50;
    }
#endif
}
