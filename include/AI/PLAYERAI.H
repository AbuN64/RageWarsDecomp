#ifndef AI_PLAYERAI_H
#define AI_PLAYERAI_H
#include "TYPES.H"
#include "COMMON/GAMEPLAY_REACTIONS.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/GLOBALS.H"
#include "COMMON/SHARED_DEBUGFIELD.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "COMMON/MENU_UI_PROVIDERS.H"
struct Shared_ReactionSource {
    u8 kind;
    char pad0[0x3];
    u16 type;
    char pad4[0x2];
    f32 positionX;
    char pad8[0x4];
    f32 positionZ;
    char pad10[0xEC];
    s32 flags;
    char pad100[0x28];
    Shared_ReactionPlayer *projectileOwner;
    char pad12C[0xA8];
    Shared_ReactionPlayer *player;
};
struct Shared_ReactionAttribution {
    u8 kind;
    char pad0[0x3];
    u16 type;
    char pad4[0xFA];
    s32 flags;
    char pad100[0xD4];
    Shared_ReactionPlayerIndex * creditedPlayer;
};
struct Shared_ReactionMatchState {
    char pad0[0x18B4];
    s32 flagModeEnabled;
};
struct Shared_ReactionObjectStatistics {
    char pad0[0x38];
    s32 primaryReactionCount;
    s32 secondaryReactionCount;
};

extern const float g_playerDamageStunIncrement[4];
#endif
