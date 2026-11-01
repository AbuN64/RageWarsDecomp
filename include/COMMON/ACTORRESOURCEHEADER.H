#ifndef COMMON_ACTORRESOURCEHEADER_H
#define COMMON_ACTORRESOURCEHEADER_H
#include "TYPES.H"
/* Section one of the resource selected by an actor's resource key. */
/* Section zero of the resource selected by an actor's resource key. */
typedef struct ActorResourceHeader {
    u8 headerPrefix[30];
    u16 particleScale; /* Float encoded in its high sixteen bits. */
} ActorResourceHeader;
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"

/* Variable-stride model section 5: parent, render bits and event mask read by Gastate. */
typedef struct ModelBoneRecord {
    u8 reserved0[0x64];
    s8 parent;
    u8 flags;
    u8 reserved66[6];
    u32 eventMask;
} ModelBoneRecord;
/* The impact-twist solver builds its ancestor chain at +0x14. */
typedef struct ActorBoneTwistState {
    u8 reserved0[0x12];
    s8 count;
    u8 reserved13;
    s8 ancestorBones[32];
    s8 state;
} ActorBoneTwistState;

struct ResourceLookupPointerView;
struct ResourceLookupPointerView {
    u32 pad0[3];
    void **value;
};

extern float g_maskedModelViewEffectTuning;

struct BodyGobjinstApplyBoneTwistImpulse;
typedef struct BodyGobjinstApplyBoneTwistImpulse BodyGobjinstApplyBoneTwistImpulse;



struct LevelActor;

extern float g_affinePackUnsignedThresholdsTranslationZ;



struct Node75;

extern float g_maskedModelViewEffectScale;



struct ObjectList;
typedef struct ObjectList ObjectList;


struct Camera;
typedef struct Camera Camera;

struct BodyGobjinstApplyBoneTwistImpulse;
struct BodyGobjinstApplyBoneTwistImpulse {
    char pad0[0x30];
    CVector3 velocity;
};



struct ActorMatrixPackFlagsView;
struct ActorMatrixPackFlagsView {
    char pad0[0x17C];
    s32 matrixPackFlags;
};

struct ObjectList;
struct ObjectList {
    char pad0[4];
    char *objects;
    s32 count;
};

struct ActorEffectFlagsView;
struct ActorEffectFlagsView {
    char pad0[0x2E0];
    unsigned int effectFlags;
};

extern float g_affinePackUnsignedThresholdsTranslationXY;

struct Scratch;
struct Scratch {
    f32 first[4];
    f32 second[4];
    f32 in[4];
    f32 out[4];
    CVector3 position;
    f32 positionPadding;
    char matrix[64];
};

struct BoneTwistSourceView;
struct BoneTwistSourceView {
    char pad0[0x12];
    s8 charges;
    char pad13;
    s8 owner;
    char pad15[3];
    CVector3 position;
};


struct Scratch;
typedef struct Scratch Scratch;


struct ActorMatrixPackFlagsView;
typedef struct ActorMatrixPackFlagsView ActorMatrixPackFlagsView;

struct Camera;
struct Camera {
    char pad0[8];
    s32 matrices;
    char pad1[4];
    s32 style;
};


struct BoneTwistSourceView;
typedef struct BoneTwistSourceView BoneTwistSourceView;


extern float g_actorDefaultOffsetValue;

extern float g_affinePackUnsignedThresholdsRowZero;


struct ActorAnimationResourceView;
typedef struct ActorAnimationResourceView ActorAnimationResourceView;

struct ActorAnimationResourceView;
struct ActorAnimationResourceView {
    char pad0[0x8];
    CVector3 position;
    char pad14[0xC4 - 0x14];
    s32 resource;
    char padC8[8];
    s32 resourceFlags;
    char padD4[0x100 - 0xD4];
    s32 flags;
    f32 animationTime;
    char pad108[0x1D8 - 0x108];
    char * owner;
};

struct ResourceLookupPointerView;
typedef struct ResourceLookupPointerView ResourceLookupPointerView;


extern float g_affinePackUnsignedThresholdsRowThree;

struct AnimInfo;
typedef struct AnimInfo AnimInfo;








struct RecGobjinstSampleBoneTranslation;


struct AnimInfo;
struct AnimInfo {
    char * boneIndexPairs;
    char pad0[0x4 - 0x0 - sizeof(char*)];
    char * initialOrientations;
    void *translationFrames; /* 0x8 */
    void * rotationFrames;
    char padC[0x10 - 0xC - sizeof(void*)];
    s32 rotationFirst;
    char pad10[0x14 - 0x10 - sizeof(s32)];
    s32 rotationNext;
    s32 translationFirst; /* 0x18 */
    s32 translationNext; /* 0x1C */
    f32 frameBlend;
};


extern float g_affinePackUnsignedThresholdsRowTwo;

struct ActorEffectFlagsView;
typedef struct ActorEffectFlagsView ActorEffectFlagsView;

struct Shared_CollisionActor;

extern float g_affinePackUnsignedThresholdsRowOne;


extern void Gobjinst_EuropeNoOperation(void);
extern void Gobjinst_EuropeAlternateNoOperation(void);
extern void Gobjinst_EuropeExtendedNoOperation(void);
extern void Gobjinst_EuropeExtendedAlternateNoOperation(void);
/* Section five of an actor frame resource describes its rendering mode. */
struct ActorFrameMetadata {
    u8 reserved0[0x6E];
    u8 renderMode; /* 0x6E */
};

extern void Graphu64_MultiplyMatrices(f32 *, f32 *, f32 *);
extern void Geometry_DrawResourceModel(s32, s32, void *, s32, void *, s32, s32);

extern CVector3 *Region_GetNodeEdgeCross(CVector3 *out, Node75 *node);

extern char g_unitScaleMultiplierAnimObjectInfoRev1Text;
extern char g_Geometry_ExpandExtendedModelAddress;
extern char s_animModelIndexText;
extern char s_animatedModelText;
#endif
