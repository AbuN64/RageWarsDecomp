#ifndef COMMON_SHAREDRECV4_H
#define COMMON_SHAREDRECV4_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
typedef void ( *SharedRecV4)(void *, signed int, void *);

struct AudioPhysicalVoiceStealView;
typedef struct AudioPhysicalVoiceStealView AudioPhysicalVoiceStealView;

struct AudioFreeVoiceUpdateView;
typedef struct AudioFreeVoiceUpdateView AudioFreeVoiceUpdateView;

struct AudioVoiceAllocationUpdate;
typedef struct AudioVoiceAllocationUpdate AudioVoiceAllocationUpdate;

struct AudioIntegerControlUpdate;
typedef struct AudioIntegerControlUpdate AudioIntegerControlUpdate;

struct AudioFreeVoiceUpdateView;
struct AudioFreeVoiceUpdateView {
    char pad0[0x4];
    s32 delta;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    s16 type;
    char pad8[0xC - 0x8 - sizeof(s16)];
    void * pvoice;
};


struct AudioPitchControlUpdate;
typedef struct AudioPitchControlUpdate AudioPitchControlUpdate;

typedef void ( *SharedRecV7)(void *, signed int, void *);

struct AudioAllocatedPhysicalVoiceView;
typedef struct AudioAllocatedPhysicalVoiceView AudioAllocatedPhysicalVoiceView;

struct AudioVoiceAllocationUpdate;
struct AudioVoiceAllocationUpdate {
    struct AudioVoiceAllocationUpdate *next;
    s32 delta;
    s16 type;
    union {
        f32 f;
        s32 i;
    } data;
    union {
        f32 f;
        s32 i;
    } moredata;
};

typedef void ( *SharedRecV5)(void *, signed int, void *);

struct SoundPlayerEventStateView;
struct SoundPlayerEventStateView {
    u8 padding000[0x14];
    ALEventQueue events; /* 0x14 */
    u8 padding028[0x14];
    s32 frameSampleCount;
    s32 eventTime;
};


struct AudioIntegerControlUpdate;
struct AudioIntegerControlUpdate {
    s32 next;
    char pad0[0x4 - 0x0 - sizeof(s32)];
    s32 delta;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    s16 type;
    char pad8[0xC - 0x8 - sizeof(s16)];
    s32 value;
};

struct Limit;
struct AudioPhysicalVoiceStealView;
struct AudioPhysicalVoiceStealView {
    struct AudioPhysicalVoiceStealView *next;
    char pad4[4];
    struct Limit *vvoice;
    char padC[0xCC];
    s32 offset;
};

typedef void ( *SharedRecV8)(void *, signed int, void *);

struct AudioPitchControlUpdate;
struct AudioPitchControlUpdate {
    s32 next;
    char pad0[0x4 - 0x0 - sizeof(s32)];
    s32 delta;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    s16 type;
    char pad8[0xC - 0x8 - sizeof(s16)];
    f32 pitch;
};

struct SoundPlayerEventStateView;
typedef struct SoundPlayerEventStateView SoundPlayerEventStateView;

#endif
