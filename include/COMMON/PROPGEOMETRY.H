#ifndef COMMON_PROPGEOMETRY_H
#define COMMON_PROPGEOMETRY_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include <ultra64.h>
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/MANAGER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PROBE.H"
struct StaticObject;





extern float g_simpleObjectScaleTransitionTiming;


extern float g_simpleObjectAlternateScaleTransitionTarget;





struct ActorSimpleInstanceSpawnModelEffect;
typedef struct ActorSimpleInstanceSpawnModelEffect ActorSimpleInstanceSpawnModelEffect;


struct PropGeometry;
typedef struct PropGeometry PropGeometry;



struct PackedPlacedPropDefinition;
struct PackedPlacedPropDefinition {
    s32 value;
    f32 scale;
    u16 id;
    u16 segment;
    u16 flags;
    u16 model;
    s16 height;
    s8 extents[6];
    u8 placement;
    u8 cellX;
    u8 cellZ;
};

struct ModelOwner;
typedef struct ModelOwner ModelOwner;


struct PlacedPropRecord;
struct PlacedPropRecord {
    s32 value;
    CVector3 position;
    CVector3 scale;
    char pad1C[0];
    u16 extents[6];
    u16 id;
    u16 segment;
    u16 model;
    u8 flags;
    s8 rotation[4];
};

struct PropGeometry;
struct PropGeometry {
    s32 kind;
    char pad4[4];
    f32 radius;
    char padC[2];
    s8 variant;
    char padF[3];
    u8 material;
    char pad13[0xD];
    f32 speed;
    u32 radiusSquared;
};

struct PlacedProp;
struct PropGeometry;
struct PlacedProp {
    u8 state;
    char pad1[3];
    u16 id;
    char pad6[2];
    CVector3 position;
    void *segment;
    struct PropGeometry *model;
    s32 owner;
    char pad20[8];
    char transform[64];
    char matrix[64];
    s32 reservedWord;
    s32 reservedWord1;
    s32 reservedWord2;
    s32 reservedWord3;
    CVector3 min;
    CVector3 max;
    s32 key;
    s32 surfaceType;
    u16 flags;
    u8 colorFrame;
    char padDB;
    s32 animationTimer;
    u8 fade;
    char padE1[0xE8 - 0xE1];
};

struct PlacedProp;
typedef struct PlacedProp PlacedProp;

struct StaticModelAnimationDescriptor;
typedef struct StaticModelAnimationDescriptor StaticModelAnimationDescriptor;


struct StaticModelAnimationDescriptor;
struct StaticModelAnimationDescriptor {
    char pad0[0xE];
    s8 key;
    s8 key2;
    char pad10[2];
    s8 argument;
    char pad13[0x24 - 0x13];
    s32 period;
};

struct StaticModelAnimationDescriptor;
struct OwnerStaticInstanceDrawDistanceFadedModel;




extern float g_simpleObjectViewEffectScale;



struct ModelEffectSpawnState;
typedef struct ModelEffectSpawnState ModelEffectSpawnState;

struct ModelEffectSpawnState;



struct StaticObject;

struct StaticModelMaterialDescriptor;
struct StaticModelMaterialDescriptor {
    char pad0[0xE];
    s8 key;
    char padF[3];
    s8 argument;
};
struct StaticModelMaterialDescriptor;
struct ModelOwner;


struct StaticObject;
typedef struct StaticObject StaticObject;

extern f32 g_staticObjectSharedAngle;

struct ActorSimpleInstanceSpawnModelEffect;

struct PlacedPropRecord;
typedef struct PlacedPropRecord PlacedPropRecord;

extern float g_simpleObjectAlternateScaleTransitionFactor;




struct PackedPlacedPropDefinition;
typedef struct PackedPlacedPropDefinition PackedPlacedPropDefinition;

extern float g_simpleObjectAlternateScaleTransitionTiming;


struct OwnerStaticInstanceDrawDistanceFadedModel;
typedef struct OwnerStaticInstanceDrawDistanceFadedModel OwnerStaticInstanceDrawDistanceFadedModel;





extern char g_Simpinst_BuildLitGeometryResourceAddress;
extern char g_simpObjectIndexText[];
extern char s_litVerticesText;

typedef struct ResourceOwner { u8 pad0[0x1c]; s32 key; u8 pad20[0x88]; s32 index; s32 selected; s32 size; void *resource; } ResourceOwner;
extern char s_statModelsIndexText[];
extern char s_statModelText[];
extern char g_Geometry_ExpandBasicModelAddressDe[];

extern char s_staticObjectResourceTag[];

extern s32 Geometry_GetViewEffect(void);
#endif
