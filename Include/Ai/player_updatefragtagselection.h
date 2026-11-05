#ifndef AI_PLAYER_UPDATEFRAGTAGSELECTION_H
#define AI_PLAYER_UPDATEFRAGTAGSELECTION_H
#include "types.h"
#include "Common/small_records.h"

struct Block;
struct Block {
    u8 pad000[0x100];
    s32 flags;
    u8 pad104[0x1DC];
    s32 value;
};
typedef struct Block Block;

struct PlayerSettingsOwnerView;
struct PlayerSettingsOwnerView {
    char pad[0x5D8];
    struct PlayerOptions *settings; /* its name text comes first */
};

struct CachedPlayerModelView;
struct CachedPlayerModelView {
    char pad0[0x8];
    f32 positionX;
    char pad8[0x10 - 0x8 - sizeof(f32)];
    f32 positionZ;
    char pad10[0xC4 - 0x10 - sizeof(f32)];
    s32 resourceKey;
    char padC4[0xD0 - 0xC4 - sizeof(s32)];
    s32 resourceFlags;
    char padD0[0x100 - 0xD0 - sizeof(s32)];
    s32 renderFlags;
    char pad100[0x1D8 - 0x100 - sizeof(s32)];
    void * player;
};
typedef struct CachedPlayerModelView CachedPlayerModelView;

#include "types.h"

struct Round;
struct Root;
struct Shared_World;
extern s32 Player_CheckScoreLimit(struct Round *world);
extern s32 Player_CheckTotalScoreWin(struct Root *world);
extern s32 Player_CheckTeamPointWin(struct Shared_World *world);
#endif
