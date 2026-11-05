#ifndef COMMON_LISTHEADER_H
#define COMMON_LISTHEADER_H
struct ListHeader;
struct ListLink;
struct Shared_Actor;
#ifndef COMMON_LISTHEADER_BODY_H
#define COMMON_LISTHEADER_BODY_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Actionai/action_updatebreakableproximity.h"
struct NavigationPlatform;
extern struct NavigationPlatform *g_navigationPlatformActors;

struct ListLinkHeader;
struct ListLinkHeader {
    struct ListLink *head;
    struct ListLink *tail;
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

extern void Link_SetActorStateBit(struct Shared_Actor *object);

struct Trigger;
typedef struct Trigger Trigger;


struct ListLinkHeader;
typedef struct ListLinkHeader ListLinkHeader;

struct Lists18;
struct Lists18 {
    ListLinkHeader active;
    ListLinkHeader inactive;
};


extern void Link_ClearActorStateBit(struct Shared_Actor *actor);

struct WeightedTable;
struct WeightedTable {
    s16 count;
    s16 entries[25][2]; /* 24 choices and the terminating entry */
    s16 reserved; /* Complete 0x68-byte caller storage. */
};





extern void Lists_InitFromPool(struct ListHeader *lists, void *pool, s32 stride, s32 count);





struct LinkTriggerMessageView;
typedef struct LinkTriggerMessageView LinkTriggerMessageView;


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



struct ActorMotionState;
struct Player;


extern void SoundElement_StopAudioBySecondaryValue(s32);
extern CVector3 g_particleZeroVector;

#endif
#endif
