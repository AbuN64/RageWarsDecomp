#ifndef AI_PLAYERAI_H
#define AI_PLAYERAI_H
#include "types.h"
#include "Common/gameplay_reactions.h"
#include "Common/approachlocation.h"
#include "Common/globals.h"
#include "Common/shared_debugfield.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/menu_ui_providers.h"
struct Shared_ReactionPlayer;
struct Shared_ReactionPlayerIndex;
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
    struct Shared_ReactionPlayer *projectileOwner;
    char pad12C[0xA8];
    struct Shared_ReactionPlayer *player;
};
struct Shared_ReactionAttribution {
    u8 kind;
    char pad0[0x3];
    u16 type;
    char pad4[0xFA];
    s32 flags;
    char pad100[0xD4];
    struct Shared_ReactionPlayerIndex * creditedPlayer;
};
struct Shared_ReactionObjectStatistics {
    char pad0[0x38];
    s32 primaryReactionCount;
    s32 secondaryReactionCount;
};

extern const float g_playerDamageStunIncrement[4];
#endif
