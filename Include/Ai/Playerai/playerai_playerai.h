#ifndef AI_PLAYERAI_PLAYERAI_PLAYERAI_H
#define AI_PLAYERAI_PLAYERAI_PLAYERAI_H
#include "types.h"
#include "Common/small_records.h"
struct Cursor;
extern ApproachLocation *Playerai_GetRouteCursorPoint(struct Cursor *cursor);
#include "types.h"
#include "Common/small_records.h"

struct MenuSettings;
struct MenuSettings {
    u32 flags;
    s32 optionFlags; /* +4: toggled menu option bits */
    u8 reservedBytes[0x1D - 8];
    u8 local; /* +0x1D: local-player input flag */
    u8 reservedBytes1[0x581 - 0x1E];
    u8 language;
};
typedef struct MenuSettings MenuSettings;

#include "types.h"
#include "Common/small_records.h"
#include "Render/player_controller_reset_views.h"
#include "Common/gameplay_reactions.h"

struct Cursor;

extern void Playerai_ApplyDamagePacket(struct Shared_ReactionActor *attacker, void *damageState, struct Shared_ReactionInteraction *packet);
extern void Playerai_EmptyWeaponEffectHook(void *effect, void *player);

#endif
