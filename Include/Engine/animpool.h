#ifndef ENGINE_ANIMPOOL_H
#define ENGINE_ANIMPOOL_H
#include "types.h"


struct SceneStreamPair;
struct BitReader;
extern struct SceneStreamPair g_cameraVolumeBoundsMinZ;
struct CAnimPool; extern void Animpool_UpdateSceneEffects(struct CAnimPool *scene, s32 world);
extern s32 CBitReader_ReadBits(struct BitReader *, s32);
#endif
