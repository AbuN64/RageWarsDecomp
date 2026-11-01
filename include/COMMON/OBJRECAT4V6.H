#ifndef COMMON_OBJRECAT4V6_H
#define COMMON_OBJRECAT4V6_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
extern f32 g_initialVoiceUnitScale;

extern float g_spatialSoundRangeSquared;

struct AudioVoiceRecordView;
typedef struct AudioVoiceRecordView AudioVoiceRecordView;

struct AudioVoiceRecordView;
struct AudioVoiceRecordView {
    s32 index;
    char pad04[4];
    s32 f08;
    s32 f0C;
    char pad10[4];
    s32 f14;
    char pad18[0x14];
    f32 f2C;
    char pad30[4];
    f32 f34;
    s16 f38;
    s16 f3A;
    char pad3C[4];
    s32 f40;
    CVector3 position; /* +0x44, Channel_InitializeVoiceMix */
    u8 reserved50[8];
    s32 f58;
    s32 f5C;
    u8 reserved60[0x14];
    s16 envelope[4]; /* +0x74 */
    u8 reserved7C[4];
    f32 envelopeValue, envelopeStep; /* +0x80, +0x84 */
    u8 reserved88[0x1C];
    s32 fA4;
    s32 soundId; /* +0xA8 */
    s32 fAC;
    struct GameAudioContext *owner; /* probe 20261019T012703451174Z */
    s32 fB4;
    f32 fB8;
    s32 fBC;
    s32 fC0;
    s32 fC4;
    f32 fC8; /* per-slot volume scale, 0xC8 */
};

struct VoiceRecordHolder;


struct AudioVoiceStopKeySlotView;
typedef struct AudioVoiceStopKeySlotView AudioVoiceStopKeySlotView;



struct AudioVoiceKeySlotView;
struct AudioVoiceKeySlotView {
    char pad0[8];
    s32 used;
    char pad[0x9C];
    s32 value;
    char pad2[0x20];
};

struct AudioSelectedHandleView;
typedef struct AudioSelectedHandleView AudioSelectedHandleView;

struct AudioVoiceKeySlotView;
typedef struct AudioVoiceKeySlotView AudioVoiceKeySlotView;

struct AudioSelectedHandleView;
struct AudioSelectedHandleView {
    char pad[0x102];
    s16 local;
};

struct VoiceKeyTable;


struct VoiceRecordHolder;
typedef struct VoiceRecordHolder VoiceRecordHolder;

struct AudioSoundPlayerOwnerView;
typedef struct AudioSoundPlayerOwnerView AudioSoundPlayerOwnerView;



struct AudioSoundPlayerOwnerView;
struct AudioSoundPlayerOwnerView {
    char pad[0x84];
    char sound[88];
    s16 samples[20];
    char pad2[(0x104 - 0xDC) - 40];
    s32 key;
};

struct AudioSoundPlayerOwnerView;
struct AudioVoiceStopKeySlotView;
struct AudioVoiceStopKeySlotView {
    s32 index;
    s32 state;
    s32 used;
    char pad0[4];
    s32 key;
    char pad1[0x3C];
    s32 flag;
    char pad2[0x54];
    s32 value;
    s32 active;
    struct AudioSoundPlayerOwnerView *owner;
    char pad3[0x18];
};

extern int g_peakActiveVoiceCount;

struct IntegerStateB4;

struct AudioVoiceSoundSlotView;
struct AudioVoiceSoundSlotView {
    char pad0[0xA8];
    s32 flags;
    char padaC[8];
    char *owner;
    char end[20];
};

struct AudioVoiceSecondarySlotView;
typedef struct AudioVoiceSecondarySlotView AudioVoiceSecondarySlotView;


struct AudioVoiceKeyedSlotView;
struct AudioVoiceKeyedSlotView {
    int id;
    char pad4[0x9C];
    int keyA;
    char padA4[8];
    int keyB;
    char padB0[0x1C];
};

struct AudioVoiceKeyedSlotView;
typedef struct AudioVoiceKeyedSlotView AudioVoiceKeyedSlotView;

struct VoiceKeyPairTable;


extern float g_distancePitchRestFactor;

struct VoiceKeyTable;
typedef struct VoiceKeyTable VoiceKeyTable;




struct Slots;
struct Slots {
    char pad0[0x60];
    s16 ids[16];
};


struct AudioVoiceSecondarySlotView;
struct AudioVoiceSecondarySlotView {
    s32 index;
    s32 state;
    s32 used;
    char pad0[4];
    s32 key;
    char pad1[0x3C];
    s32 flag;
    char pad2[0x54];
    s32 other;
    s32 active;
    AudioSoundPlayerOwnerView *owner;
    s32 value;
    char pad3[0x14];
};

extern float g_voicePlaybackTimeThreshold;

struct Slots;
typedef struct Slots Slots;

/* A voice waiting in the context queue; the queue head is a sentinel node inside the context. */
typedef struct VoiceQueueNode {
    struct VoiceQueueNode *prev;
    struct VoiceQueueNode *next;
    char pad8[0x38];
    s16 priority;
} VoiceQueueNode;

struct AudioVoiceContextView;
struct AudioVoiceContextView {
    char pad0[0x7C];
    Slots slots;
    char padFC[0x104 - 0xFC];
    s32 frame;
    char pad108[0x134 - 0x108];
    s32 track;
    char pad138[0x13C - 0x138];
    VoiceQueueNode queue; /* 0x13C: sentinel of the queue of voices waiting for a slot */
    char pad180[0x2B98 - 0x180];
    s32 result;
};

struct AudioVoiceContextView;
struct ViewChannelUpdateVoicePlayback;



extern float g_voiceAttenuationOutputScale;

struct AudioVoiceControlSlotView;
struct AudioVoiceControlSlotView {
    s32 index;
    s32 state;
    s32 used;
    s32 releaseMarker;
    s32 key;
    char pad14[0x24];
    s16 priority;
    s16 channel;
    char pad3C[0x14];
    s32 flag;
    char pad2[0x50];
    s32 mask;
    s32 value;
    s32 active;
    AudioSoundPlayerOwnerView *owner;
    s32 releaseMarkerB;
    char padB8[0x14];
};

extern float g_voiceDistanceAttenuationConstants;


struct AudioVoiceControlSlotView;
typedef struct AudioVoiceControlSlotView AudioVoiceControlSlotView;

struct AudioVoiceFlagsPoolView;
struct AudioVoiceFlagsPoolView {
    AudioSelectedHandleView *header;
    AudioVoiceControlSlotView slots[17];
};


struct AudioVoiceSoundSlotView;
typedef struct AudioVoiceSoundSlotView AudioVoiceSoundSlotView;

extern void Audio_PlayVoiceSound(AudioVoiceSoundSlotView *base, s16 index);



extern s32 Audio_GetVoiceSoundState(AudioVoiceSoundSlotView *voicePool, s16 slotIndex);




struct VoiceSecondaryKeyTable;
typedef struct VoiceSecondaryKeyTable VoiceSecondaryKeyTable;


struct AudioSelectedHandleView;
struct VoiceStopKeyTable;

struct VoiceSecondaryKeyTable;

extern float g_distancePitchInitialFactor;



struct AudioVoiceFlagsPoolView;
typedef struct AudioVoiceFlagsPoolView AudioVoiceFlagsPoolView;

extern float g_voicePitchTableBase;


struct Emitter;

extern float g_voicePoolInitialUnitScale;


struct VoiceStopKeyTable;
typedef struct VoiceStopKeyTable VoiceStopKeyTable;


struct IntegerStateB4;
typedef struct IntegerStateB4 IntegerStateB4;

struct AudioVoiceContextView;
typedef struct AudioVoiceContextView AudioVoiceContextView;

struct ViewChannelUpdateVoicePlayback;
typedef struct ViewChannelUpdateVoicePlayback ViewChannelUpdateVoicePlayback;

extern float g_distancePitchFactorBounds;

struct Emitter;
typedef struct Emitter Emitter;


struct VoiceKeyPairTable;
typedef struct VoiceKeyPairTable VoiceKeyPairTable;

#endif
