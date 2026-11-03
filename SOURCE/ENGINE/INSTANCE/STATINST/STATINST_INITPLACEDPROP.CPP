#include "COMMON/OBJB.H"
#include "COMMON/WORLD.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/PROPGEOMETRY.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON.H"
extern s32 g_gameFrameCounter;

/* Initialises a placed prop from its record: resets its state and owner, loads its model and caches the squared model radius, builds its rotation from the record's packed quaternion, scale and position into a matrix copied into the object, sets its bounding box either as a fixed cube for flag 0x40 or from the record's six extents through Menu_ExpandFloatHighWord with a half-unit margin, copies the position, links its path segment and takes the next colour key and colour frame. The fixed cube is written through do-while(0) vector macros, which the stores' order needs, and 102.4 is the cartridge's rounded 0x42CCCCCC. */



extern void Insthdr_ResetInstanceRenderIndices(ObjA *, PlacedPropRecord *, s32, char *);
extern PropGeometry *Scene_GetActorDefinition(void *, s32);

extern void MatrixFromQuaternion(f32 *q, f32 *m);
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

void Statinst_InitPlacedProp(ObjA *prop, PlacedPropRecord *record, s32 owner, char *segments) {
    f32 rotation[4];
    char matrix[64];
    PropGeometry *model;

    Insthdr_ResetInstanceRenderIndices(prop, record, owner, segments);
    prop->state = 0;
    prop->id = record->id;
    prop->owner = owner;
    prop->renderIndex = -1;
    prop->renderState[0] = 0;
    prop->renderState[1] = 0;
    prop->renderState[2] = 0;
    prop->descriptor = Scene_GetActorDefinition(&g_world, record->model);
    prop->fade = 16;
    prop->timer = 0;
    model = (PropGeometry *)prop->descriptor;
    model->radiusSquared = model->radius * model->radius;
    prop->flagsD8 = record->flags;
    rotation[0] = record->rotation[0] * 0.007874016f;
    rotation[1] = record->rotation[1] * 0.007874016f;
    rotation[2] = record->rotation[2] * 0.007874016f;
    rotation[3] = record->rotation[3] * 0.007874016f;
    Graphu64_NormalizeQuaternion(rotation);
    MatrixFromQuaternion(rotation, matrix);
    ScaleMatrixLocal(matrix, record->scale.x, record->scale.y, record->scale.z);
    TranslateMatrix(matrix, record->position.x, record->position.y, record->position.z);
    SwapMatrixUpForward(matrix);
    if (prop->flagsD8 & 0x40) {
        do { (prop->bounds.min).x = (record->position).x - (102.399994f); (prop->bounds.min).y = (record->position).y - (102.399994f); (prop->bounds.min).z = (record->position).z - (102.399994f); } while (0);
        do { (prop->bounds.max).x = (record->position).x + (102.399994f); (prop->bounds.max).y = (record->position).y + (102.399994f); (prop->bounds.max).z = (record->position).z + (102.399994f); } while (0);
        prop->surfaceType = g_defaultCameraSurfaceType;
    } else {
        prop->bounds.min.x = RW_BITS_TO_FLOAT(record->extents[0]) + record->position.x - 0.5f;
        prop->bounds.min.y = RW_BITS_TO_FLOAT(record->extents[1]) + record->position.y - 0.5f;
        prop->bounds.min.z = RW_BITS_TO_FLOAT(record->extents[2]) + record->position.z - 0.5f;
        prop->bounds.max.x = RW_BITS_TO_FLOAT(record->extents[3]) + record->position.x + 0.5f;
        prop->bounds.max.y = RW_BITS_TO_FLOAT(record->extents[4]) + record->position.y + 0.5f;
        prop->bounds.max.z = RW_BITS_TO_FLOAT(record->extents[5]) + record->position.z + 0.5f;
        prop->surfaceType = record->value;
    }
    CopyMatrix(prop->matrix, matrix);
    Graphu64_ConvertMatrixToFixed(matrix, prop->transform);
    prop->position = record->position;
    if (record->segment == 0xFFFF) {
        prop->segment = 0;
    } else {
        prop->segment = segments + record->segment * 32;
    }
    prop->flagsD0 = advancePropKey() << 10;
    prop->colorFrame = (u8)g_gameFrameCounter - 1;
#if defined(VERSION_DE)
    if ((u32)(InstHdr_GetActorType(prop) - 9) < 2) {
        prop->flagsD8 |= 0x50;
    }
#endif
}
