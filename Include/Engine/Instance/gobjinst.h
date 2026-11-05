#ifndef ENGINE_INSTANCE_GOBJINST_H
#define ENGINE_INSTANCE_GOBJINST_H
#include "Render/player_controller_reset_views.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Ai/ai_shared_symbols.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/actorresourceheader.h"
#include "Common/probe.h"
#include "Common/level_actor.h"
#include "Common/vector.h"

struct BoneTwistAxis {
    char pad[0x18];
    CVector3 value;
};
typedef struct BoneTwistAxis BoneTwistAxis;

struct SpawnedEffectMotionView {
    unsigned char pad0[0x150];
    f32 radius;
    f32 height;
};
typedef struct SpawnedEffectMotionView SpawnedEffectMotionView;

struct MenuPanelRoot {
    char pad0[0xCC];
    s32 resource;
    char padD0[4];
    s32 resourceSize;
    s32 selected;
    s32 selectedResource;
    s32 window;
};
typedef struct MenuPanelRoot MenuPanelRoot;

struct AttachmentEventTableView {
    char pad0[0x4];
    s32 entryCount;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    char entries;
};
typedef struct AttachmentEventTableView AttachmentEventTableView;

typedef struct ActorAnimationEventTable ActorAnimationEventTable;
struct ActorAnimationEventTable {
    int entrySize;
    int entryCount;
    u8 records[0]; /* Variable-stride model/event records follow the two-word header. */
};

struct Table {
    s32 reservedWord;
    s32 count;
    s32 deltas[1];
};
typedef struct Table Table;


struct CollisionQuery;
struct CollisionState;
struct LitModelResourceHeader;
struct FixedPointMatrix;
struct WeightedTable;
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

extern void Gobjinst_PackAffineMatrixWords(f32 *src, struct FixedPointMatrix *dst);

extern void Gobjinst_SampleBoneTranslation(void *poseTrack, s32 boneIndex, void *outTranslation);

extern void Gobjinst_SampleBoneRotation(void *poseTrack, s32 boneIndex, CQuatern *outRotation);

extern void Gobjinst_InterpolatePoseRotation(void *cQuatern, f32 t, void *a, void *b);
struct LevelActor;
struct CVector3_t;
void GameObject_DrawBlobShadow(struct LevelActor *actor, struct CVector3_t *offset, s32 raised);
struct ActorInstanceHeader {
    s32 w[2];
    CVector3 position;
    s32 remaining[15];
};
s32 Gobjinst_ProbeActorMovement(struct ActorInstanceHeader *actorState, struct CVector3_t position, char **out);
extern struct CollisionQuery g_portalModeCollisionQuery;
extern struct CollisionQuery g_portalNoModelFlagCollisionQuery;
extern struct CollisionQuery g_portalAlternateCollisionQuery;
extern int Insthdr_GetModelCollisionFlag1(void *actorStorage);
extern s32 Insthdr_IsInactiveOrCollisionOption4(void *actor);
extern int Insthdr_GetModelCollisionFlag8(void *actorStorage);
struct CCollisionResults;
extern struct CCollisionResults g_currentActorInstance;
extern int InstHdr_GetActorMotionIndex(void *record);
extern void *g_actorTypeOperations[];
extern void g_Gobjinst_DrawTeamMaskedModelAddress();
extern CQuatern Insthdr_BuildActorGroundRotation(char *);
extern void Gastate_ResetAnimationReference(void *record);
extern void Gobjinst_QueueAnimation(void *actorStorage, unsigned int animationIndex);

extern void Lists_ClearWeightedTable(struct WeightedTable *);
void Gobjinst_InitializeActor(char *obj, s32 model, s32 kind, s32 surfaceType, void *info, s32 effect, s32 owner, f32 heading, CVector3 pos, s32 flags, CVector3 extent, CVector3 offset, s32 trailingUnused);
/* Head of a lit-model resource: layout 1 stores the model object and its vertex colour block elsewhere in the resource
 * (offsets measured from the head); any other layout stores the model object inline, starting at the second offset word. */
typedef struct LitModelResourceHeader {
    s32 layout;
    s32 objectOffset;
    s32 vertexColorOffset;
} LitModelResourceHeader;

/* The model object of a layout-1 lit-model resource. */
static inline char *LitModel_Object(struct LitModelResourceHeader *header) {
    return (char *)header + header->objectOffset;
}

/* The vertex colour block of a layout-1 lit-model resource. */
static inline char *LitModel_VertexColors(struct LitModelResourceHeader *header) {
    return (char *)header + header->vertexColorOffset;
}

#endif
