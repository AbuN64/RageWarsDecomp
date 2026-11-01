#ifndef COMMON_LISTNODE_H
#define COMMON_LISTNODE_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"

struct ListNode;
struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
    unsigned char pad08[0xB4];
    s32 valueBC;
};

struct ListNode;
typedef struct ListNode ListNode;

struct ListNode;

struct AudioPendingFlagsNode;
typedef struct AudioPendingFlagsNode AudioPendingFlagsNode;

struct AudioPendingFlagsNode;
struct AudioPendingFlagsNode {
    struct AudioPendingFlagsNode *prev;
    struct AudioPendingFlagsNode *next;
    char pad8[0xA4];
    s32 flags;
};

struct Lists;


struct AudioChannelVoiceNode;
typedef struct AudioChannelVoiceNode AudioChannelVoiceNode;

extern void Audio_ResolveInstrumentSectionOne(void *instrument, s16 index);

struct AudioSpatialVoiceManagerView;
typedef struct AudioSpatialVoiceManagerView AudioSpatialVoiceManagerView;


struct AudioVoiceListLinks;
typedef struct AudioVoiceListLinks AudioVoiceListLinks;

struct Lists;
typedef struct Lists Lists;

struct AudioPendingSoundLinks;
typedef struct AudioPendingSoundLinks AudioPendingSoundLinks;

struct AudioPrioritizedSoundNode;
struct AudioPrioritizedSoundNode {
    struct AudioPrioritizedSoundNode *prev;
    struct AudioPrioritizedSoundNode *next;
    char pad8[0x14];
    s32 timer;
    char pad20[0x20];
    s16 priority;
    char pad42[6];
    s32 owner;
    CVector3 position;
};

struct AudioPendingSoundLinks;
struct AudioPrioritizedSoundNode;
struct AudioPendingSoundLinks {
    struct AudioPrioritizedSoundNode *prev;
    struct AudioPrioritizedSoundNode *next;
};

struct AudioDispatchBusySlot;
typedef struct AudioDispatchBusySlot AudioDispatchBusySlot;

struct AudioDispatchBusySlot;
struct AudioDispatchBusySlot {
    char pad0[0xAC];
    s32 busy;
    char padB0[0x1C];
};

struct AudioScene;
struct AudioScene {
    char pad0[0x1DBC];
    AudioDispatchBusySlot entries[1];
    char pad1E88[0x2A84 - 0x1E88];
    s32 selection;
    s32 previousSelection;
    char pad2A8C[0x28];
    s16 activeSelection;
    s16 pendingSelection;
};
struct AudioSpatialVoiceManagerView;
struct AudioScene;


struct AudioVoiceListLinks;


extern float g_listenerPanCenterAndRange;

struct NodeAudioWorldRecyclePendingSoundsExceptKey;
struct NodeAudioWorldRecyclePendingSoundsExceptKey {
    struct NodeAudioWorldRecyclePendingSoundsExceptKey *prev;
    struct NodeAudioWorldRecyclePendingSoundsExceptKey *next;
    char pad08[0xB0 - 0x8];
    s32 key;
};

struct NodeAudioWorldRecyclePendingSoundsExceptKey;
struct AudioPendingSoundListOwner;
struct AudioPendingSoundListOwner {
    s32 reservedWord;
    struct NodeAudioWorldRecyclePendingSoundsExceptKey *activePrev;
    struct NodeAudioWorldRecyclePendingSoundsExceptKey *activeNext;
    char pad0C[0xD8 - 0xC];
    struct NodeAudioWorldRecyclePendingSoundsExceptKey *otherPrev;
};

struct Glyphs;
struct Glyphs {
    char pad0[0x10];
    s32 bitmaps[1];
};

struct Font;
struct Glyphs;
struct Font {
    char pad0[0xC];
    struct Glyphs *glyphs;
};
struct SoundContext;
struct Font;
struct SoundContext {
    char pad0[0x7C];
    struct Font *font;
    char pad80[4];
    char textures[0xDC - 0x84];
    s16 slots[16];
    char padFC[0x104 - 0xFC];
    s32 frame;
    s32 sequence;
    char pad10C[0x1DB8 - 0x10C];
    char cells[1];
};

struct SlotAudioIsSoundInstanceLimitReached;
struct SlotAudioIsSoundInstanceLimitReached {
    int id;
    char pad[0xC8];
};

struct Cache;
typedef struct Cache Cache;

extern float g_listenerPanCenterRadiusConstants;

struct NodeAudioWorldRecyclePendingSoundsByIdentifier;
struct NodeAudioWorldRecyclePendingSoundsByIdentifier {
    struct NodeAudioWorldRecyclePendingSoundsByIdentifier *prev;
    struct NodeAudioWorldRecyclePendingSoundsByIdentifier *next;
    s32 unused;
    s32 value;
};


struct SlotAudioIsSoundInstanceLimitReached;
typedef struct SlotAudioIsSoundInstanceLimitReached SlotAudioIsSoundInstanceLimitReached;

struct AudioInstanceLimitOwner;
struct AudioInstanceLimitOwner {
    char pad[0x102];
    short owner;
    char pad104[0x1E64 - 0x104];
    SlotAudioIsSoundInstanceLimitReached slots[17];
};


struct AudioInstrumentPackView;
typedef struct AudioInstrumentPackView AudioInstrumentPackView;

struct AudioSoundCell;

struct NodeAudioWorldRecyclePendingSoundsByIdentifier;
typedef struct NodeAudioWorldRecyclePendingSoundsByIdentifier NodeAudioWorldRecyclePendingSoundsByIdentifier;

struct NodeAudioWorldRecyclePendingSoundsByIdentifier;


struct EntryAudioWorldDispatchPendingSounds;
struct EntryAudioWorldDispatchPendingSounds {
    struct EntryAudioWorldDispatchPendingSounds *prev;
    struct EntryAudioWorldDispatchPendingSounds *next;
    char body[16];
    s32 frame;
    s32 delay;
    char pad20[0x40 - 0x20];
    s16 glyph;
    s16 font;
    s16 style;
    s16 pad46;
    s32 sequence;
    char pad4C[0xA8 - 0x4C];
    s32 reservedWordA8;
};

struct AudioQueuedSoundNode;
struct AudioQueuedSoundNode {
    struct AudioQueuedSoundNode *prev;
    struct AudioQueuedSoundNode *next;
    char channel[4];
    s32 volume;
    char pad10[4];
    s32 handle;
    s32 frame;
    s32 sample;
    s32 gainA;
    s32 gainB;
    s16 pitch;
    char pad2A[2];
    s32 time;
    char pad30[0x10];
    s16 priority;
    s16 group;
    s16 volume16;
    char pad46[2];
    s32 voice;
    Vec3Words position;
    s32 pad58;
    u8 pan;
    char pad5D[0x4F];
    s32 flags;
    char padB0[4];
    s32 padB4;
    char padB8[0x10];
    s32 mix;
};

struct LinkAudioWorldQueuePrioritizedSound;
struct AudioQueuedSoundNode;
struct LinkAudioWorldQueuePrioritizedSound {
    struct AudioQueuedSoundNode *prev;
    struct AudioQueuedSoundNode *next;
};



struct AudioSoundCell;
typedef struct AudioSoundCell AudioSoundCell;

struct AudioInstanceLimitOwner;
typedef struct AudioInstanceLimitOwner AudioInstanceLimitOwner;



struct LinkAudioWorldQueuePrioritizedSound;
typedef struct LinkAudioWorldQueuePrioritizedSound LinkAudioWorldQueuePrioritizedSound;

struct AudioPriorityQueueManagerView;

struct NodeAudioWorldRecyclePendingSoundsExceptKey;
typedef struct NodeAudioWorldRecyclePendingSoundsExceptKey NodeAudioWorldRecyclePendingSoundsExceptKey;

struct AudioPriorityQueueManagerView;
typedef struct AudioPriorityQueueManagerView AudioPriorityQueueManagerView;

struct AudioChannelVoiceNode;
struct AudioChannelVoiceNode {
    ListLink link;
    Header header;
};

struct ChannelSet;
struct ChannelSet {
    s32 owner;
    ListLink free;
    Header freeHeader;
    ListLink active;
    Header activeHeader;
    AudioChannelVoiceNode voices[32];
};



struct AudioQueuedSoundNode;
typedef struct AudioQueuedSoundNode AudioQueuedSoundNode;

struct EntryAudioWorldDispatchPendingSounds;
struct ListHead;
struct ListHead {
    struct EntryAudioWorldDispatchPendingSounds *prev;
    struct EntryAudioWorldDispatchPendingSounds *next;
};

struct ListHead;
typedef struct ListHead ListHead;

struct Cache;
struct SoundContext;
struct Cache {
    struct SoundContext *context;
    ListHead pending;
    char padC[0xD8 - 0xC];
    ListHead done;
};



struct AudioPendingSoundListOwner;
typedef struct AudioPendingSoundListOwner AudioPendingSoundListOwner;


struct EntryAudioWorldDispatchPendingSounds;
typedef struct EntryAudioWorldDispatchPendingSounds EntryAudioWorldDispatchPendingSounds;


struct AudioPrioritizedSoundNode;
typedef struct AudioPrioritizedSoundNode AudioPrioritizedSoundNode;


struct LinkPair;
typedef struct LinkPair LinkPair;

struct Glyphs;
typedef struct Glyphs Glyphs;

struct SoundContext;
typedef struct SoundContext SoundContext;


struct LinkPair;

struct AudioInstrumentPackView;

struct ChannelSet;
typedef struct ChannelSet ChannelSet;

extern s16 SoundInfo_GetGroup(void *);
extern s16 SoundInfo_GetSample(void *);
extern s8 SoundInfo_GetPitch(void *);
struct RecordD90;
extern s16 Channel_SelectVoiceSlot(struct RecordD90 *, s32, s32, s16, s32);
#endif
