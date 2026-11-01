#ifndef ENGINE_AUDIO_CHANNEL_H
#define ENGINE_AUDIO_CHANNEL_H
struct Channel;
#ifndef COMMON_CHANNEL_INNER_H
#define COMMON_CHANNEL_INNER_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"

typedef struct AudioVolumeMix {
    s32 frame, reserved4;
    s32 left, right;
    u8 reserved10[0xC];
    f32 attenuation, baseAttenuation, spareAfterBaseAttenuation;
    s16 priority, channel;
    u8 reserved2C[8];
    CVector3 position;
    void *tracked;
    s8 curve;
    u8 reserved45[0x1F];
} AudioVolumeMix;

struct ScreenMessageOwner;
extern void Gsky_ReleaseScreenMessageRendering(struct ScreenMessageOwner *owner);


extern float k_screenMessageChannelLevelScale;



extern float k_screenMessageWaveLevelScale;

extern float k_floorSurfaceLowerDistance;

extern void Gsky_SetShakeChannel(struct Channel *channel, float inputLevel, int waveMode);




extern void Gsky_StartFadeModeOne(char *object);


struct Channel;
struct Channel {
    s32 mode;
    f32 level;
    s32 state[3]; /* 0x08..0x10 */
};

struct Channel;
struct CameraShakeRecordView;
struct CameraShakeRecordView {
    char pad[8];
    Triple triple;
    f32 value;
    struct Channel channels[3];
};


extern void Gsky_InitializeShakeRecord(void *channelRecord);


struct IntegerStateF24;
typedef struct IntegerStateF24 IntegerStateF24;


extern float k_screenMessageInitialNearestDistance;


extern float k_screenMessageWaveDefault;

extern int Gsky_StartFadeModeTwo(void *outputStorage);



struct ScreenMessagePool;
extern void Gsky_ActivateMessagePool(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool);

extern void Gsky_ReleaseMessageBuffer(void *bufferOwner);

extern s32 Gsky_UpdateShakeRecord(s32 waveRecord);



struct IntegerStateF24;
struct IntegerStateF24 {
    unsigned char padding_0[3864];
    s32 allocationHandle;
    s32 allocationSize;
    s32 allocationCount;
};





struct Wave;
struct Wave {
    s32 kind;
    char pad4[0xC - 4];
    f32 amplitude;
    f32 phase;
};

extern float k_floorSurfaceDistanceScale;

extern double k_screenMessageScaleDivisorStep;




extern void Gsky_FloorSurfaceNoOp(void);


extern void Gsky_InitializeShakeChannel(void *channelStorage);


extern float k_screenMessageWavePhaseScale;


struct Wave;
extern f32 Gsky_SampleShakeWave(struct Wave *wave);

struct NodeGskyActivateMessagePool;

extern float k_floorShakeTargetHorizontal;

extern void Gsky_AllocateMessageBuffer(void *messageBuffer, s32 count);




struct CameraShakeRecordView;
extern void Gsky_SetShakeRecord(struct CameraShakeRecordView *record, f32 first, f32 second, f32 third, f32 value, s32 mode, Triple triple);


extern void Gsky_AllocateScreenMessageStorage(void *screenMessageOwner, int count);

extern float k_floorSurfaceUpperDistance;

extern void Gsky_UpdateFloorSurface(void *gameplayCamera);

extern void Gsky_ViewportUpdateNoOp(void);






/* Allocation buffer used by message storage constructors. */
typedef struct MessageBuffer {
    s32 *allocation;
    s32 first;
    s32 count;
} MessageBuffer;

/* On-screen message recycling and distribution share these list owners. */
struct ScreenMessageOwner {
    s32 allocation; /* 0x00 */
    s32 allocationSize; /* 0x04 */
    s32 count; /* 0x08 */
    u8 padding00C[0x40 - 0xC];
    u8 rendering; /* 0x40 */
    u8 padding041[0xF18 - 0x41];
    MessageBuffer storage; /* 0xF18 */
    IntrusiveList activeMessages; /* 0xF24 */
    u8 paddingF38[0x1200 - 0xF38];
    s32 state; /* 0x1200 */
    s32 reservedWord; /* the owner initialized by Pools_ResetPlayers_Channel is0x1208 */
};
struct ScreenMessagePool {
    u8 padding000[4];
    struct ScreenMessagePool *next; /* 0x04, g_gameplayCameraList_Channel chain */
    u8 padding008[0xE38];
    IntrusiveList freeMessages; /* 0xE40 */
};

struct CCameraText_t;
extern CCameraText *Camera_PostScreenMessage(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool, u8 *text);

#endif
#endif
