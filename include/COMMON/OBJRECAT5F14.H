#ifndef COMMON_OBJRECAT5F14_H
#define COMMON_OBJRECAT5F14_H
struct CAnimPool;
#ifndef COMMON_OBJRECAT5F14_BODY_H
#define COMMON_OBJRECAT5F14_BODY_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"






struct EffectDesc;
typedef struct EffectDesc EffectDesc;


struct EffectDesc;
struct EffectDesc {
    u8 id;
    char pad1[7];
    CVector3 position;
    s32 owner;
    s32 count;
    CVector3 direction;
    char pad28[0x28];
    CVector3 color;
    char pad5C[0x10];
    f32 scale;
    char pad70[0x74];
    u16 variant;
};

extern SceneEffect *Animpool_SpawnDescribedSceneEffect(struct CAnimPool *scene, EffectDesc *desc);

extern void *Animpool_AcquireSceneEffect(s32 effectPool, s32 *referenceCount);

struct RecordAnimPoolSpawnAnimationObject;
struct RecordAnimPoolSpawnAnimationObject {
    char pad0[0x1C];
    u16 count;
    u16 angle;
};

struct AnimationPoseRecordView;
typedef struct AnimationPoseRecordView AnimationPoseRecordView;

struct ResourceEntry;
typedef struct ResourceEntry ResourceEntry;

struct EffectAnimPoolUpdateSceneEffects;
typedef struct EffectAnimPoolUpdateSceneEffects EffectAnimPoolUpdateSceneEffects;

struct AnimationPoseRecordView;
struct AnimationPoseRecordView {
    int reservedWord;
    short id;
    char pad4[0x6 - 0x4 - sizeof(short)];
    short frame;
    char pad6[0x8 - 0x6 - sizeof(short)];
    short count;
    char pad8[0xA - 0x8 - sizeof(short)];
    unsigned char flag0;
    char padA[0xB - 0xA - sizeof(unsigned char)];
    unsigned char flag1;
    char padB[0x10 - 0xB - sizeof(unsigned char)];
    int data;
};

struct Six;
struct Six {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
};



struct EffectAnimPoolUpdateSceneEffects;
struct EffectAnimPoolUpdateSceneEffects {
    char pad0[0xE8];
    f32 min[3];
    f32 max[3];
    char pad100[0];
    s32 flags;
    char pad104[0x70];
    s32 busy;
    char pad178[0x2EC - 0x178];
    struct EffectAnimPoolUpdateSceneEffects *next;
    s32 *ref;
};

struct EffectAnimPoolUpdateSceneEffects;



struct RecordAnimPoolSpawnAnimationObject;
typedef struct RecordAnimPoolSpawnAnimationObject RecordAnimPoolSpawnAnimationObject;


extern void Gastate_ReleaseAnimationResource(void *animationState);




struct BitReader;
typedef struct BitReader BitReader;

extern float g_animationFrameAngleScale;




struct BitReader;
struct BitReader {
    u8 *data;
    s32 bitPos;
};

/* The 0x25C-byte region-grid state (Visdata_DecodeRegionGrid fills it): the bit reader on the stream, the grid's origin,
 * the last cell lookup, and one signed code (or stream offset) per cell of the 17x17 grid. */
struct ResourceBitGrid;
typedef struct ResourceBitGrid ResourceBitGrid;
struct ResourceBitGrid {
    BitReader reader;
    s32 originX;
    s32 originY;
    s32 cellState;
    s32 cellValue;
    s16 cells[17 * 17];
};


struct ResourceEntry;
struct ResourceEntry {
    u16 reservedHalf;
    u16 span;
    u16 reservedHalf2;
    u16 count;
};

struct Six;
typedef struct Six Six;

/* The list Animpool_ReleaseSceneEffect appends its record to. */


/* Shared object layout established by effect-pool consumers. */
struct CAnimPool {
    SceneEffect DynAnims[32]; /* 0x0000 */
    IntrusiveList FreeList; /* 0x5F00 */
    IntrusiveList UsedList; /* 0x5F14 */
};

/* Eight-byte easing parameters returned for a motion animation segment. */
typedef struct AnimationBlendEntry {
    u16 frames;
    u8 reserved2[3];
    u8 start;
    u8 reserved6;
    u8 end;
} AnimationBlendEntry;

#endif
#endif
