#ifndef ENGINE_INSTANCE_STATINST_H
#define ENGINE_INSTANCE_STATINST_H
extern int g_staticObjectResourceSerial;
#include "types.h"

struct PackedPlacedPropDefinition;
struct PlacedPropRecord;
extern int Statinst_FindPlacedPropIndex(void *wanted,int key);
extern int Statinst_GetPropModelIndex(char *object);
extern s32 Statinst_GetPropGeometryIndex(struct ObjA *object);
extern s32 *Statinst_CollectPropResources(void *prop, s32 model, s32 geometryVariant, s32 *nextResource);
extern void Statinst_DrawModel(struct ObjA *owner);
extern void Statinst_RegisterGeometryResources(void *owner);
extern s32 Statinst_UpdateDistanceFade(void *prop, s32 cameraAddress);
extern void Statinst_DrawDistanceFadedModel(struct ObjA *owner);
extern void Statinst_DispatchAttachmentEvents(void *object, s32 all);
extern void Statinst_InitializePlacedProp(struct ObjA *prop, struct PackedPlacedPropDefinition *record, s32 owner, char *segments, f32 spacing);
extern void Statinst_InitPlacedProp(struct ObjA *prop, struct PlacedPropRecord *record, s32 owner, char *segments);
#endif
