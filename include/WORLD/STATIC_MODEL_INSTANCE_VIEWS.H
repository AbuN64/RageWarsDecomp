#ifndef WORLD_STATIC_MODEL_INSTANCE_VIEWS_H
#define WORLD_STATIC_MODEL_INSTANCE_VIEWS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include <ultra64.h>
#include "COMMON/MANAGER.H"
struct Access_s32_50 {
    char pad[0x50];
    s32 field;
};
struct OwnerStaticInstanceDrawDistanceFadedModel {
    char pad0[8];
    CVector3 position; /* 0x08 */
    char pad14[4];
    struct StaticModelAnimationDescriptor *descriptor;
    char pad1C[4];
    s32 pairedResource;
    char pad24[4];
    char transform[168];
    s32 flagsD0;
    char padD4[4];
    u16 flagsD8;
    u8 colorFrame;
    char padDB;
    u32 timer;
    s8 fade;
};
struct ModelEffectSpawnState {
    s32 paused;
    u8 pad4[0x18];
    s32 reservedWord1C;
};
struct StaticObject {
    u8 state;
    s8 model;
    char pad2;
    s8 material;
    u16 id;
    char pad6[2];
    CVector3 position;
    void *room;
    s32 *type;
    char pad1C[0x34];
    s32 animationKey;
    s32 animation;
    s32 resource;
    s32 resourceSize;
    s32 *renderResource;
    char pad64[4];
    char matrices[4][0x40];
    char pad168[0xC];
    f32 angle;
    char pad178[4];
    char effect[24];
    f32 scale;
    f32 height;
    u16 flags;
    char pad19E[2];
    f32 scaleTime;
    f32 frameDelta;
    char lights[24];
    s32 scene;
    Gfx *cached;
};
struct ModelOwner {
    char pad0[0x18];
    struct StaticModelMaterialDescriptor *descriptor;
    char pad1C[4];
    s32 pairedResource;
    char pad24[4];
    char transform[168];
    s32 flagsD0;
    char padD4[4];
    u16 flagsD8;
    u8 colorFrame;
};
struct ActorSimpleInstanceSpawnModelEffect {
    u32 pad0[2];
    CVector3 position0;
    u32 pad14[2];
    CVector3 position1;
};
typedef struct ResourceObject23 {
    s8 pad0;
    s8 type;
    char pad2[0x50-2];
    s32 model;
    s32 loadedType;
    s32 resourceName;
    s32 resourceSize;
    CachedResource *blockNode;
} ResourceObject23;
extern char g_simpleObjectModelResourceTagData;
extern const char g_simpModelText[];
extern const char g_simpModelsIndexText[];
#endif
