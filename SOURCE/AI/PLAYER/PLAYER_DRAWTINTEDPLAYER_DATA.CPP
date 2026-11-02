#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "RENDER/WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA.H"
#include "TYPES.H"

f32 Graphu64_ApproachValue(f32, f32, s32);

void Playerai_UpdateReactionReserve(void *player) {
    if ((((struct PlayerTintBlendStateView *) ((s8 *) player))->health) != 0) {
        (((struct PlayerTintBlendStateView *) ((s8 *) player))->reactionReserve) = Graphu64_ApproachValue((((struct PlayerTintBlendStateView *) ((s8 *) player))->reactionReserve), g_playerReactionReserveTarget, g_playerReactionReserveApproachRate);
    }
}

#include "COMMON/GAMEPLAY_REACTIONS.H"
#include "RENDER/SHARED_REACTIONINTERACTION.H"
extern void Barrel_FillDamagePacket(Shared_ReactionInteraction *, s32, s32, f32, s32, s32);

void Playerai_AddReactionReserve(Shared_ReactionPlayer *actor, f32 amount, s32 source) {
    Shared_ReactionInteraction packet;
    f32 value;
    f32 limited;
    value = actor->reserve + amount;
    limited = gReactionReserveMaximum;
    if (!(limited <= value)) {
        limited = value;
    }
    actor->reserve = limited;
    if (gReactionReserveMaximum <= limited) {
        Barrel_FillDamagePacket(&packet, source, 0x40000, 25.599998f, 128, 0);
        Playerai_ApplyDamagePacket((Shared_ReactionActor *)actor, &actor->damageState, &packet);
    }
}
