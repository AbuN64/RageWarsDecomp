#ifndef GEOMETRY_GEOMETRY_DRAWBLENDPARTS_H
#define GEOMETRY_GEOMETRY_DRAWBLENDPARTS_H
void Geometry_QueueDirectModel(s32 model, void *matrix, void *lights, s32 textures, s32 pass);
void Geometry_UnlockMaterialResources(void **modelResource);
#endif
