#ifndef COMMON_GAMEPLAY_TRANSITION_H
#define COMMON_GAMEPLAY_TRANSITION_H
#include "types.h"
#include "Common/pickup_entry_tables.h"
#include "onscrn.h"
#include "Common/hud_effects.h"

#include "Common/sharedplayer.h"
#include "Common/level_actor.h"

struct AmmoBundleDefinition;
struct Shared_PickupAmmoDefinition;
/* Player-transition records from origin/legacy shared headers. */

#include "Common/aiprofile.h"

typedef struct Shared_ProjectileView Shared_ProjectileView;
struct Shared_ProjectileView {
    char pad0[0x14];
    s32 source; /* 0x14 */
    char pad18[0x184];
    u16 flags; /* 0x19C */
    char pad19E[0x32];
    s32 stateFlags; /* 0x1D0 */
};

typedef struct Shared_PlayerSettingsView Shared_PlayerSettingsView;
struct Shared_PlayerSettingsView {
    char pad0[0x80];
    s8 character; /* 0x80 */
    char pad81[0x14];
    u8 active; /* 0x95 */
    char pad96[0x46A];
    s32 effect; /* 0x500 */
    char pad504[0xA0];
    s32 state; /* 0x5A4 */
};

#include "Common/gameplay_settings.h"
#include "Ai/Player/player_resetplayerforround.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Ovlgame/ovlgame_initializeplayerpool.h"

typedef struct Shared_ModelView Shared_ModelView;
struct Shared_ModelView {
    s32 unused; /* 0x0 */
    s32 flags; /* 0x4 */
};

typedef struct Shared_SpecialObjectView Shared_SpecialObjectView;
struct Shared_SpecialObjectView {
    char pad0[0x170];
    char segment[100]; /* 0x170 */
    s32 reset; /* 0x1D4 */
};

typedef struct Shared_GlobalPlayers Shared_GlobalPlayers;
struct Shared_GlobalPlayers {
    s32 unused; /* 0x0 */
    char *players; /* 0x4 */
    s32 count; /* 0x8 */
    char controller[20]; /* 0xC */
    char effects; /* 0x20 */
    char pad21[0x3];
};

typedef struct Shared_PickupAmmoDefinition Shared_PickupAmmoDefinition;
struct Shared_PickupAmmoDefinition {
    void **labelSlot; /* entry of g_pickupLabelDirectory naming the ammo item */
    s16 id; /* lookup key */
    s16 sharedMessageId;
    s16 reserved8[2];
    s16 firstAmmoDrop;
    s16 secondAmmoDrop;
    s16 thirdAmmoDrop;
    s16 reserved12;
    void *applyEntry; /* g_pickup_ApplyAmmoBundleEntry */
};
extern struct Shared_PickupAmmoDefinition g_pickupAmmoDefinitions[16]; /* item records, looked up by id */

typedef struct Shared_HeightBonuses Shared_HeightBonuses;
struct Shared_HeightBonuses {
    f32 spawn; /* 0x0 */
    f32 projectile; /* 0x4 */
};
#endif
