#ifndef ENGINE_INSTANCE_GOBJINST_H
#define ENGINE_INSTANCE_GOBJINST_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/ACTORRESOURCEHEADER.H"
#include "COMMON/PROBE.H"

struct HorizontalMovementSurfaceView {
    char pad0[0x52];
    u16 flags;
    char pad54[9];
    u8 strength;
    char pad5e[1];
    s8 x;
    s8 y;
    s8 z;
};

struct ActorHorizontalMovementView {
    u8 kind;
    char pad1[0x1f];
    f32 vertical;
    char pad24[4];
    CVector3 current;
    char pad34[4];
    s32 flags;
    char pad3c[0x30];
    f32 yaw;
};

extern char g_actorDefinitionTable[];

extern void Gobjinst_MoveActorWithContactCallback(char *, CVector3 *);

extern void Gobjinst_RestartAnimation(void *actorAnimationState);

extern void Gobjinst_NoOperation(void);

extern s32 Gobjinst_GetAnimationSectionDelta(struct LevelActor *actor, s32 deltaIndex);

extern void Gobjinst_NoOperationAnimationHook(void);

extern void Gobjinst_NoOperationAnimationHookUs(void);

extern void Gobjinst_NoOperationAnimationHookAlternateUs(void);

extern float g_boneTwistImpulseCurve[];

extern void GameObject_BuildQuaternionTranslationMatrix(f32 *m, f32 *q, f32 *t);

extern void Gobjinst_InterpolatePoseTranslation(void *outVector, f32 t, void *a, void *b);

extern void Gobjinst_PackAffineMatrixWords(f32 *src, PackedMatrixWords *dst);

extern void Gobjinst_SampleBoneTranslation(void *poseTrack, s32 boneIndex, void *outTranslation);

extern void Gobjinst_SampleBoneRotation(void *poseTrack, s32 boneIndex, CQuatern *outRotation);

extern void Gobjinst_InterpolatePoseRotation(void *cQuatern, f32 t, void *a, void *b);
#endif
