#ifndef TYPES_H
#define TYPES_H
#include <ultra64.h>
#include <PR/sched.h>

struct ControllerProfile;











typedef struct IntrusiveList IntrusiveList;

/* A doubly linked list threaded through its nodes: head and tail are the end nodes, prevOffset and
   nextOffset are the byte offsets of the previous and next links inside each node, and count is the
   number of nodes. */
struct IntrusiveList {
    void *head;
    void *tail;
    s32 prevOffset;
    s32 nextOffset;
    s32 count;
};

struct IntrusiveList;

extern s32 Libsn_ReadPortWord(s32 portAddress);

extern void Scaled_ResetBehaviorState(void *object);

struct CloseAttackBrain;

extern s32 Nav_SelectCloseAttackPickupGoal(struct CloseAttackBrain *closeAttackBrain);

extern s32 Nav_SelectChaseObjectGoal(void *actor);

struct AiController;

extern s32 Nav_SelectStationaryObjectGoal(struct AiController *controller);

extern void Nav_ResetPatrolRouteSelection(void *object);

extern void Nav_SelectFlaggedRoamingGoal(void *actor);

struct AimPlayer;

extern void Playerai_DispatchWeaponFireEffect(struct AimPlayer *aimPlayer, s32 effect);

extern s32 Player_HasAmmoForMode(void *, s32);

extern void Playerai_StopSecondaryAttachedSound(void *player);

struct LevelActor;

extern void Player_ZeroBodyVelocity(void *unusedContext, struct LevelActor *actor);

extern void Player_UpdateJumpAirMotion(void *player, void *body);

extern void Player_BeginLateralLeap(void *movementState, void *actorMotion);

extern void Player_AbsorbImpact(void *player, struct LevelActor *actor);

extern void Player_DampMotion(void *actorState, void *levelActor);

extern void Player_ResetMovementInput(void *motionPlayerState, struct LevelActor *actor);

extern void Player_ResetObjectVelocity(void *unused, void *object);

extern void Player_InitializeProfileSlot(s32 profileIndex);

extern void Cinema_SetResponse(float responseValue);

extern void Cinema_SetLoopMode(int loopMode);

extern void Cinema_SetViewport(int viewportWidth, int viewportHeight, int viewportLeft, int viewportTop);

extern void Cinema_InitializeSequenceOnce(s32 unused);

extern s32 Gobjinst_RequestAnimationIndex(void *levelActor, s32 animationIndex, s32 allowDuringBlend);

extern s32 Cache_EvictResource(s32 unused0, s32 unused1, s32 keep_recent);

extern void *Cache_AllocateHeapWithEviction(s32 unusedCache, u32 byteCount, s32 allocatorSelection, u32 evictionFlags);

extern void Cache_ClearResourceSlotProtection(s32, s32);

extern void List_DropIntrusiveHead(IntrusiveList *list);

struct RecordD90;

extern s32 Audio_ReleaseMatchingExclusiveVoice(struct RecordD90 *record, s16 value, s16 id);

extern void Audio_SetVoiceTrackId(void *voice, int newTrackId);

extern void SoundElement_PlayDialogGroup(s32 callback);

extern void SoundElement_StopAudioExceptKey(s32 retainedKey);

extern void SoundElement_SetMusicPlaybackEnabled(s32 a);

extern void SoundElement_SetClampedAudioLevel(f32 level);

extern int Control_IsLeftPressed(struct ControllerProfile *object);

extern int Control_IsRightPressed(struct ControllerProfile *object);

extern s32 Control_AcquireControllerLock(s32 block);

extern int Control_IsControllerPakEnabled(int controllerPort);

extern void Control_SetControllerMode(s32 a);
struct RangeNode;
extern void Gdynlight_ReleaseLight(IntrusiveList *a, struct RangeNode *b);

extern void Graphu64_WrapPeriodicValue(f32 *value);

extern void Graphu64_NormalizeQuaternion(f32 *rotation);

extern f32 Graphu64_RandomFloat(f32 range);

extern f32 Graphu64_ArcCos(f32 cosineValue);

extern f32 Graphu64_IntegrateBoundedValue(f32 value, f32 velocity, f32 limit);

extern f32 Graphu64_DecayToZero(f32 value, f32 rate);

extern f32 Graphu64_RandomBetween(f32 shakeMin, f32 shakeMax);

extern void Gregion_DesaturateColor(u8 amount, u8 r, u8 g, u8 b, u8 *outR, u8 *outG, u8 *outB);

extern void Map_ResetFramePool(void *batch);

extern int Particle_HasSurfaceFlag(void *particle);

extern void Particle_StopSound(void *a);

extern void Rumble_RecycleFinishedEffectNodes(void *pool);

struct Shared_World;
struct CVector3_t;
extern s32 Scene_FindFloorPolygon(struct Shared_World *, struct CVector3_t *);

extern s32 Scene_GetModelSectionTwoRecord(void *world, s32 modelIndex);

extern void Sched_HandleRspCompletion(void *object);


extern void __scAppendList(OSSched *scheduler, void *task);

extern void __scYield(void *scheduler);

extern int SetN64_CompareByteStrings(u8 *a, u8 *b);

struct GameSession;

extern void SetN64_SetTransitionTarget(struct GameSession *object, int value);

extern void SetN64_ResetPlayerItems(s32 sessionAddress, s32 selectionKey);

extern void SetN64_InitializeFrontendScreenState(struct GameSession *gameSession);

extern s32 DispatchElementEvent(s32 id, s32 event, s32, s32, s32);

extern s32 SmSmngr_DispatchPrimaryScreenEvent(s32 event, s32, s32, s32);

extern f32 XMath_EvaluateSine(f32 angle);

extern void XMath_EvaluateSineCosine(f32 angle, f32 *sinOut, f32 *cosOut);

extern f32 XMath_EvaluateArcTangentTwo(f32 y, f32 x);

extern void XMath_MultiplyMatrices(s32 matrix, s32 leftMatrix, s32 rightMatrix);

extern s32 XMath_AbsoluteInteger(s32 value);

extern void XMath_EvaluateCosine(f32 angle);

extern f32 XMath_EvaluateArcSine(f32 x);

extern s32 XPlus_ParseDecimalInteger(u8 *s);

extern void N64Eng_GetScreenSize(int *widthOut, int *heightOut);

extern void Tsmos_SetModeOneFlag(s32 enabled);

extern void OnScreen_DrawTextGlyphs(u8 *text, f32 x, f32 y, f32 width, f32 height, s32 shadow, s32 alpha, s32 language);

extern void OnScreen_GetImageDimensions(s32 resourceId, s32 imageIndex, s32 *widthOut, s32 *heightOut);

extern void OnScreen_SetTextColors(int red, int green, int blue, int shadowRed, int shadowGreen, int shadowBlue);

extern void OnScreen_SetTextScale(float scaleX, float scaleY);

extern s32 Pickup_ApplyAmmo(void *player, void *pickupEntry);

extern s32 Pickup_ApplyLifePoints(void *player, void *pickup);

struct ActorPickupCanCollect;

struct MultiChannelItemEffect;

extern s32 Pickup_ApplyAmmoBundle(struct ActorPickupCanCollect *player, struct MultiChannelItemEffect *ammoBundle);


#include "libultra/audio/seqp.h"


extern void __setUsptFromTempo(void *sequencePlayer, f32 tempo);








extern float Math_Cosf(float x);

extern float Gu_Sinf(float x);

extern unsigned int Control_StopMotorEu(void *motorContext);






typedef struct Block40 Block40;

struct Block40 {
    u8 bytes[40];
};


struct Block40;

extern unsigned int Control_StartMotorEu(void *motorContext);

typedef struct __OSContRamReadFormat __OSContRamReadFormat;

struct __OSContRamReadFormat {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u16 address;
    u8 data[32];
    u8 datacrc;
};

struct __OSContRamReadFormat;





struct Triple;


extern u32 Control_StopMotorDe(struct Triple *);

extern u32 Control_StopMotorEuX(struct Triple *);

#endif
