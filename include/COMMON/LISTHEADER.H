#ifndef COMMON_LISTHEADER_H
#define COMMON_LISTHEADER_H
struct Shared_Actor;
#ifndef COMMON_LISTHEADER_BODY_H
#define COMMON_LISTHEADER_BODY_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct NavigationPlatform;
extern struct NavigationPlatform *g_navigationPlatformActors;

struct ListLinkHeader;
struct ListLinkHeader {
    ListLink *head;
    ListLink *tail;
    int count;
};

struct ListHeader;
typedef struct ListHeader ListHeader;

struct ListHeader;
struct ListHeader {
    void *head;
    void *tail;
    s32 count;
};

extern s16 Lists_ChooseWeightedEntry(s16 *weightedEntries);

struct Lists18;
typedef struct Lists18 Lists18;

struct ParticleAmmoRewardView;
typedef struct ParticleAmmoRewardView ParticleAmmoRewardView;

struct LinkTriggerMessageView;
struct LinkTriggerMessageView {
    char pad0[0x4];
    u16 platformIndex;
    char pad4[0xA - 0x4 - sizeof(u16)];
    u16 sequenceId;
    char padA[0x11 - 0xA - sizeof(u16)];
    u8 messageKind;
    char pad11[0x12 - 0x11 - sizeof(u8)];
    u8 messageState;
};

extern void Link_SetActorStateBit(void *object);

struct Trigger;
typedef struct Trigger Trigger;


struct ListLinkHeader;
typedef struct ListLinkHeader ListLinkHeader;

struct Lists18;
struct Lists18 {
    ListLinkHeader active;
    ListLinkHeader inactive;
};

extern void Link_SetTriggerTrackCallback(int unused0, int unused1, void *trigger);

extern void Link_ClearActorStateBit(struct Shared_Actor *actor);

struct WeightedTable;
struct WeightedTable {
    s16 count;
    s16 entries[25][2]; /* 24 choices and the terminating entry */
    s16 reserved; /* Complete 0x68-byte caller storage. */
};

struct ParticleOwnerActorView;
typedef struct ParticleOwnerActorView ParticleOwnerActorView;

struct ParticleOwnerActorView;
struct ParticleOwnerActorView {
    char pad0[0x4];
    u16 kindId;
    char pad4[0x118 - 0x4 - sizeof(u16)];
    char * def;
    char pad118[0x12C - 0x118 - sizeof(char*)];
    char * owner;
    char pad12C[0x1B8 - 0x12C - sizeof(char*)];
    s8 stateByte2;
    char pad1B8[0x1B9 - 0x1B8 - sizeof(s8)];
    s8 stateByte0;
    char pad1B9[0x1BA - 0x1B9 - sizeof(s8)];
    s8 stateByte1;
};

struct ParticleFinishSoundView;
typedef struct ParticleFinishSoundView ParticleFinishSoundView;

struct ParticleChildEffectActorView;
struct ParticleChildEffectActorView {
    char pad0[8];
    CVector3 position;
    char pad14[8];
    CVector3 facing;
    char pad28[0x34];
    s32 flags;
    char pad60[0xB8];
    ActorDefinitionFlagsView *def;
    char pad11C[0x10];
    void *owner;
    s32 effectEntries;
    s32 effectEntryCount;
    char pad138[0x48];
    f32 offsetX;
    f32 offsetY;
    s32 angle;
};

extern void Lists_InitFromPool(ListHeader *lists, void *pool, s32 stride, s32 count);

struct ParticleFinishSoundView;
struct ParticleFinishSoundView {
    unsigned char padding_0[190];
    u16 firstSoundId;
    unsigned char padding_C0[2];
    u16 secondSoundId;
};



extern void Link_SetTriggerTrack(void *trigger);

struct LinkTriggerMessageView;
typedef struct LinkTriggerMessageView LinkTriggerMessageView;

struct ParticleChildEffectActorView;
typedef struct ParticleChildEffectActorView ParticleChildEffectActorView;

struct Trigger;
struct Trigger {
    s32 mask;
    u16 actor;
    u16 trackArgument;
    u16 action;
    u16 owner;
    union {
        s32 word;
        struct {
            u16 messageArgument;
            u8 state;
            u8 id;
        } bytes;
    } flags;
    u8 sound;
    u8 table;
    u8 entry;
    u8 pad13;
};

struct WeightedTable;
typedef struct WeightedTable WeightedTable;

struct ParticleAmmoRewardView;
struct ParticleAmmoRewardView {
    char pad0[0x59C];
    s32 resetFlag;
    char pad59C[0x5A4 - 0x59C - sizeof(s32)];
    s32 ammoType;
    char pad5A4[0x5A8 - 0x5A4 - sizeof(s32)];
    s32 ammoAmount;
};


struct ActorMotionState;
struct Player;
extern s32 Action_ShowTriggerMessage(struct NavigationPlatform *object, struct ActorMotionState *guard, struct Player *actor);

extern void SoundElement_StopAudioBySecondaryValue(s32);
extern CVector3 g_particleZeroVector;

#endif
#endif
