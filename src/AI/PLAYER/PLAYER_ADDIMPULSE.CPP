#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "RENDER/S1.H"

/* Decreases a float field at offset 0x12C0 by the given amount, clamps it from below at a floor, and when it reaches the floor builds and dispatches an event. Adapted from Playerai_AddReactionReserve, with the add, the clamp direction, the constant, the third argument (a field plus 0x1900), and a duplicated clamp assignment (which keeps the constant reloaded rather than held in a register) changed. */

extern void Barrel_FillDamagePacket(void *packet, void *damageSource, s32 damage, f32 radius, s32 damageFlags, s32 shield);
extern void Playerai_ApplyDamagePacket(void *attacker, void *damageState, void *packet);






void Player_DrainReserveAndDamage(void *actor, f32 amount, void *damageSource) {
    Slot damage;
    f32 reserveValue;
    f32 clampedReserve;

    reserveValue = ((Shared_ActorView *)actor)->reserve - amount;
    clampedReserve = g_playerReserveBounds_de[1];
    if (!(reserveValue <= clampedReserve)) {
        if (actor != 0) {
            clampedReserve = reserveValue;
        } else {
            clampedReserve = reserveValue;
        }
    }
    reserveValue = g_playerReserveBounds_de[1];
    ((Shared_ActorView *)actor)->reserve = clampedReserve;
    if (clampedReserve <= reserveValue) {
        Barrel_FillDamagePacket(&damage, damageSource, ((LevelActor *)actor)->active + 6400, 25.599998f, 128, 0);
        Playerai_ApplyDamagePacket(actor, &((LevelActor *)actor)->behaviorFlags, &damage);
    }
}

/** Adds the argument scaled by g_playerImpulseScale to the object's float at 0x11DC and sets bit 0x2000 in its word at 0x122C. */






void Player_AddImpulse(void *actorView, f32 amount) {
    ((Shared_ActorView *)actorView)->impulse = ((Shared_ActorView *)actorView)->impulse + amount * g_playerImpulseScale;
    ((Shared_ActorView *)actorView)->impulseFlags = ((Shared_ActorView *)actorView)->impulseFlags | 0x2000;
}
