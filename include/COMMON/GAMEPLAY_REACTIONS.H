#ifndef COMMON_GAMEPLAY_REACTIONS_H
#define COMMON_GAMEPLAY_REACTIONS_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"

/* Actor, interaction and score views used to select reactions and record statistics. */

typedef struct Shared_ReactionActor Shared_ReactionActor;
typedef struct Shared_ReactionPlayer Shared_ReactionPlayer;
typedef struct Shared_ReactionFlags Shared_ReactionFlags;
typedef struct Shared_ReactionInteraction Shared_ReactionInteraction;
typedef struct Shared_ReactionObjectKind Shared_ReactionObjectKind;
typedef struct Shared_ReactionSource Shared_ReactionSource;
typedef struct Shared_ReactionAttribution Shared_ReactionAttribution;
typedef struct Shared_ReactionPlayerIndex Shared_ReactionPlayerIndex;
typedef struct Shared_ReactionMatchState Shared_ReactionMatchState;
typedef struct Shared_ReactionStatistics Shared_ReactionStatistics;
typedef struct Shared_ReactionObjectStatistics Shared_ReactionObjectStatistics;
typedef struct Shared_ReactionPlayerRecord Shared_ReactionPlayerRecord;


typedef struct CDamageInfo_t {
    Shared_ReactionActor *target;
    s32 m_Hits;
    f32 m_Radius;
    s32 flags;
    Shield *m_pNode;
} CDamageInfo;

struct Shared_ReactionObjectKind {
    u8 category;
    char pad0[0x3];
    u16 type;
};

struct Shared_ReactionActor {
    union {
        struct {
            u8 category;
            char pad1[3];
            u16 type;
            char pad6[2];
        };
        Shared_ReactionObjectKind objectKind;
    };
    CVector3 position;
    char pad14[0x58];
    f32 heading;
    f32 height;
    char pad74[0x70];
    u16 team;
    char padE6[0x1A];
    s32 flags;
    char pad104[0x28];
    Shared_ReactionActor *owner;
    char pad130[0x40];
    s32 damageState;
    s32 health;
    char pad178[0x60];
    Shared_ReactionPlayer *player;
};

struct Shared_ReactionPlayer {
    u8 category;
    char pad0[0x7];
    union {
        CVector3 position;
        struct { f32 positionX, positionY, positionZ; };
    };
    u16* sourceModelHandles;
    char pad14[0xCC];
    u16 type;
    char padE4[0x1A];
    s32 flags;
    char pad104[0x6C];
    s32 damageState;
    s32 actorHealth;
    char pad178[0x60];
    Shared_ReactionPlayer *player;
    char pad1DC[0x10C];
    Shared_ReactionActor actor2E8;
    char pad4C4[0x110];
    s32 profileIndex;
    Shared_ReactionStatistics * statistics;
    void *owner; /* 0x5DC: actor that shows the reaction text */
    char pad5E0[0x4];
    s32 health;
    char pad5E8[0x46];
    s16 weaponIndex;
    char pad630[0x20];
    s16 action;
    char pad652[0xB86];
    f32 reactionTimer;
    char pad11DC[4];
    f32 stun;
    char pad11E4[0x34];
    s32 damageToggle;
    char pad121C[0x10];
    s32 reactionFlags;
    char pad1230[0x90];
    f32 reserve; /* 0x12C0: reaction reserve */
    Shared_ReactionPlayer *lastCountRuleVictim;
    Shared_ReactionPlayer *lastSquadVictim;
    Shared_ReactionPlayer *killHistory[8];
    Shared_ReactionPlayer *lastKiller;
    s32 deathReactionVariant;
    s32 killHistoryTimers[8];
    char pad1314[0x24];
    s32 killHistoryIndex;
    char pad1338[0x88];
    s8 hitDirection;
    char pad13C5[0x23];
    s32 messageNext; /* 0x13E8: next slot of messages */
    char messages[4][25]; /* 0x13EC */
    s32 isBot;
    Shared_ReactionPlayerRecord * botRecord;
};

struct Shared_ReactionFlags {
    char pad0[0x20];
    f32 height; /* 0x20 */
    char pad24[0x44 - 0x24];
    u32 flags; /* 0x44 */
    char pad48[0x52 - 0x48];
    u16 flags52;
    char pad54[2];
    u16 mask; /* 0x56: effect objects enabled for this record */
};







struct Shared_ReactionPlayerIndex {
    char pad0[0x5D4];
    s32 profileIndex;
};


struct Shared_ReactionStatistics {
    u16 deaths_self;
    u16 deaths_other;
    u16 score;
    u16 special_kills;
    u16 pad8;
    u16 special_hits;
    u16 kills_special[8];
    u16 deaths_special[8];
    u16 kills_normal[8];
    u16 deaths_normal[8];
    char pad4C[0x38];
    char name[9]; /* 0x84: player name, terminated before counted */
    u8 counted;
    char pad8E[0x1];
    u8 isHuman;
    char pad90[0x2];
    u8 team;
};


struct Shared_ReactionPlayerRecord {
    char pad0[0x4];
    s32 searchNodeKey;
    char pad8[0x31C];
    s32 attackerMemoryTicks;
    Shared_ReactionPlayer *lastAttacker;
};
extern f32 gReactionReserveMaximum;
extern void Playerai_ApplyDamagePacket(Shared_ReactionActor *, void *, Shared_ReactionInteraction *);
extern void Player_PostKillMessages(Shared_ReactionPlayer *, Shared_ReactionPlayer *, Shared_ReactionInteraction *);
#endif
