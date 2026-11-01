#ifndef AUDIO_VOICE_AND_SPATIAL_SOURCE_VIEWS_H
#define AUDIO_VOICE_AND_SPATIAL_SOURCE_VIEWS_H
#include "TYPES.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
struct SoundSlotHandleView {
    char pad0[0xDC];
    s16 soundId;
};
struct VoiceMatchingKeyView {
    char pad0[0x104];
    int voiceKey;
};
struct VoiceRecordHolder {
    char pad0[0x4];
    AudioVoiceRecordView record;
};
struct VoiceKeyTable {
    AudioSelectedHandleView *header;
    AudioVoiceKeySlotView slots[17];
};
struct IntegerStateB4 {
    s32 slotIndex;
    s32 handle;
    unsigned char padding_8[8];
    s32 frame;
    unsigned char padding_14[60];
    s32 tracked;
    unsigned char padding_54[88];
    s32 done;
    s32 context;
};
struct VoiceKeyPairTable {
    AudioSelectedHandleView *owner;
    char pad4[8];
    AudioVoiceKeyedSlotView slots[16];
};
typedef struct SoundEnvelope {
    u16 flags;
    u16 initial;
    u16 target;
    s16 frames;
    u32 reserved8;
} __attribute__((packed)) SoundEnvelope;
struct ViewChannelUpdateVoicePlayback {
    s32 slot;
    s32 handle;
    s32 reserved8;
    s32 reservedC;
    s32 frame;
    char pad14[4];
    s32 finished;
    u8 pad1C[0xC];
    s16 priority; /* 0x28 */
    u8 pad2A[2];
    f32 time;
    char pad30[0x38 - 0x30];
    s16 reserved38;
    s16 reserved3A;
    char pad3C[0x44 - 0x3C];
    Triple position;
    Triple *tracked;
    s8 distanceMode; /* 0x54 */
    u8 reserved55[0x74 - 0x55];
    u16 volumeInitial; /* 0x74 */
    u16 reserved76;
    u16 volumeTarget; /* 0x78 */
    u16 reserved7A;
    s16 volumeDelay; /* 0x7C */
    u8 reserved7E[2];
    f32 volume; /* 0x80 */
    f32 volumeStep; /* 0x84 */
    s32 sweeping; /* 0x88 */
    SoundEnvelope envelope; /* 0x8C */
    f32 value; /* 0x98 */
    f32 step; /* 0x9C */
    s32 hold;
    s32 flags;
    s32 trackId;
    s32 done;
    struct AudioVoiceContextView *context;
    s32 reservedB4;
    char padB8[4];
    s32 followTrack;
    s32 fixed; /* 0xC0 */
    s32 attenuate; /* 0xC4 */
    f32 volumeScale; /* 0xC8 */
};
struct VoiceStopKeyTable {
    struct AudioSelectedHandleView *header;
    AudioVoiceStopKeySlotView slots[17];
};
struct VoiceSecondaryKeyTable {
    AudioSelectedHandleView *header;
    AudioVoiceSecondarySlotView slots[17];
};
struct Emitter {
    char pad0[0x34];
    f32 level;
    char pad38[0xC];
    f32 x;
    f32 y;
    f32 z;
    char pad50[8];
    f32 distance;
    f32 lastDistance;
    char pad60[0x48];
    s32 id;
    char padAC[4];
    void *scene;
    char padB4[0xC];
    s32 reset;
};
/* Position and attenuation curve of a spatial sound source. */
typedef struct SoundSpatialSource {
    u8 reserved0[0x34];
    CVector3 position;
    u8 reserved40[4];
    s8 curve;
} SoundSpatialSource;
struct ViewChannelUpdateVoicePitch {
    s32 slot;
    char pad4[0xC];
    VoicePitchMotion motion;
    char pad38[0x60 - 0x38];
    VoicePitchAngles angles;
    f32 pitch;
    f32 pitchStep;
    char pad74[0xA4 - 0x74];
    s32 flags;
    char padA8[0xB0 - 0xA8];
    struct VoicePitchChannelContext *context;
    char padB4[4];
    f32 scale;
};
struct VoiceChannelUpdateVoicePan {
    s32 index;
    char pad4[0xC];
    VoiceVolumeParameters params;
    char position[68];
    s32 sweeping;
    char pad8C[4];
    u16 target;
    char pad92[2];
    s16 delay;
    char pad96[2];
    f32 value;
    f32 step;
    char padA0[4];
    s32 flags;
    char padA8[8];
    struct AudioOwnerView *owner;
    char padB4[0xC];
    s32 fixed;
};
#endif
