#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/INTEGERSTATE2C.H"
#include "COMMON/INTEGERSTATE244.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AI/NAV/PORTAL_LOADCOLLISIONTABLE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern f32 Barrel_GetSignedAngleToPoint(void *actor, struct CVector3_t point);

/* Runs a computer player's engagement timer: while the countdown at 0x2E4 is positive it rerolls the
   wait at 0x2E8 as the config's base at 8 plus a random share (scale g_timedActionWaitRandomScale) of its spread at 0xC
   and counts down; at zero it counts the opponents in range through Particle_CountOwnerListOneEffects (three counting as
   the whole wait) and either flags waiting at 0x23C while fewer than the wait or starts pursuit with
   the countdown at -1 and a wait from the config's 0x24 and 0x28 (scale g_alternatingActionWaitRandomScale); during pursuit
   the wait runs down, ends early once the player is within g_alternatingActionTargetRange of its target on the target's
   height, and when it reaches zero flags 0x240 and acts through Portal_InitializeRandomActionSettings. Written in the style of
   Portal_UpdateMeterGatedActionBurst with the random scale loaded into a local first. */






extern char g_actorParticleEffectSystem;

extern s32 Particle_CountOwnerListOneEffects(char *, void *);

struct EffectSystem;
extern void Particle_AverageOwnerEffectPositions(struct EffectSystem *, void *, CVector3 *);

extern f32 Graphu64_GetSquaredDistance(CVector3 *, CVector3 *);

struct LevelActor;
extern void Particle_FindNearestForeignEffectDistance(struct EffectSystem *effectSystem, struct LevelActor *actor, f32 *distanceOut);

extern f32 Portal_GetEngagementDistance(void *controller);


extern f32 Barrel_GetSignedAngleToPoint(void *actor, struct CVector3_t point);

void Portal_DispatchActorBehavior(void *controller)
{
    /* Dispatch the current actor mode through its per-type behavior table. */
    void *state;
    s32 mode;
    s32 type;
    Shared_ActorView *actor;

    state = controller;
    if (state == 0) {
        return;
    }
    actor = *(Shared_ActorView **)state;
    if (0.0f < actor->stun) {
        return;
    }

    mode = actor->weapon.gear;
    type = actor->selectedAction;
    mode -= 1;
    {
        u32 dispatch = *(&g_actorBehaviorDispatchModes + mode + type * 2);
        if (dispatch >= 9) {
            return;
        }
        switch (dispatch) {
        case 0: goto case_0;
        case 1: goto case_0;
        case 2: goto case_0;
        case 3: goto case_0;
        case 4: goto case_1;
        case 5: goto case_3;
        case 6: goto case_5;
        case 7: goto case_4;
        case 8: goto case_2;
        }
    }
case_0:
        Portal_UpdateTimedActionBurst(state, (char *)&((AiConfig *)&g_actorBehaviorActionConfigs)[type] + mode * ((char *)&((AiConfig *)0)->alternateDelayBase - (char *)0));
        goto dispatched;
case_1:
        Portal_UpdateHeldActionBurst(state, (char *)&((AiConfig *)&g_actorBehaviorActionConfigs)[type] + mode * ((char *)&((AiConfig *)0)->alternateDelayBase - (char *)0));
        goto dispatched;
case_2:
        ((CountedEffectActionState *)state)->actionFlagFrames = 1;
        goto dispatched;
case_3:
        Portal_UpdateAlternatingActionBursts(state, &((AiConfig *)&g_actorBehaviorActionConfigs)[type]);
        goto dispatched;
case_4:
        Portal_UpdateCountedEffectAction(state, &((AiConfig *)&g_actorBehaviorActionConfigs)[type]);
        goto dispatched;
case_5:
        Portal_UpdateMeterGatedActionBurst(state, &((AiConfig *)&g_actorBehaviorActionConfigs)[type]);
case_6:
case_7:
case_8:
dispatched:

    if (((CountedEffectActionState *)state)->actionFlagFrames > 0) {
        ((Shared_ActorView *)(*(void **)state))->unk_0x06B0 |= 0x4000;
        ((Shared_ActorView *)(*(void **)state))->actionFlags |= 0x4000;
        ((CountedEffectActionState *)state)->actionFlagFrames -= 1;
    }
}

void Portal_UpdateAlternatingActionBursts(AiController *controller, AiConfig *aiConfig)
{
    s32 v0;
    f32 f20;
    f32 f1;
    f32 randomBurstScale;
    s32 s1;

    v0 = controller->alternateCountdown;
    if (v0 > 0) {
        v0 = v0 - 1;
        controller->alternateCountdown = v0;
        if (v0 == 0) {
            f20 = g_actionBurstRandomRange;
            if (Graphu64_RandomFloat(f20) < g_actionBurstAlternateChance) {
                controller->alternateCountdown = -1;
                controller->actionDelay = aiConfig->alternateDelayBase;
                controller->actionDelay = (s32) ((f32) controller->actionDelay
                    + (Graphu64_RandomFloat(f20) * (f32) aiConfig->alternateDelaySpread));
                controller->actionDuration = aiConfig->alternateDurationBase;
                controller->actionDuration = (s32) ((f32) controller->actionDuration
                    + (Graphu64_RandomFloat(f20) * (f32) aiConfig->alternateDurationSpread));
            } else {
                controller->alternateCountdown = aiConfig->alternateCountdownBase;
                controller->alternateCountdown = (s32) ((f32) controller->alternateCountdown
                    + (Graphu64_RandomFloat(f20) * (f32) aiConfig->alternateCountdownSpread));
            }
        }
    }
    if (controller->alternateCountdown == -1) {
        v0 = controller->actionDuration - 1;
        controller->actionDuration = v0;
        if (v0 == 0) {
            f20 = g_actionBurstRestartRandomRange;
            controller->alternateCountdown = aiConfig->alternateCountdownBase;
            controller->alternateCountdown = (s32) ((f32) controller->alternateCountdown
                + (Graphu64_RandomFloat(f20) * (f32) aiConfig->alternateCountdownSpread));
            controller->actionDelay = aiConfig->primaryDelayBase;
            controller->actionDelay = (s32) ((f32) controller->actionDelay
                + (Graphu64_RandomFloat(f20) * (f32) aiConfig->primaryDelaySpread));
            controller->actionDuration = aiConfig->primaryDurationBase;
            f1 = (f32) controller->actionDuration
                + (Graphu64_RandomFloat(f20) * (f32) aiConfig->primaryDurationSpread);
            controller->actionFlagFrames = 0;
            controller->actionDuration = (s32) f1;
        } else {
            controller->actionFlagFrames = 1;
        }
    }
    v0 = controller->actionDelay;
    if (v0 > 0) {
        controller->actionDelay = v0 - 1;
        return;
    }
    if (controller->actionFlagFrames > 0) {
        s1 = aiConfig->alternateDelayBase;
        randomBurstScale = Graphu64_RandomFloat(g_actionBurstAlternateDelayRandomRange);
        if (1) {
            f20 = g_actionBurstAlternateAngleLimit;
            s1 = (s32) ((f32) s1 + (randomBurstScale * (f32) aiConfig->alternateDelaySpread));
        }
    } else {
        s1 = aiConfig->primaryDelayBase;
        s1 = (s32) ((f32) s1 + (Graphu64_RandomFloat(g_actionBurstPrimaryDelayRandomRange) * (f32) aiConfig->primaryDelaySpread));
        f20 = g_actionBurstPrimaryAngleLimit;
    }
    {
        AiTarget *p = controller->target;
        Player *q = p->player;
        if (!(f20 < Barrel_GetSignedAngleToPoint(controller->player,
                                    q->pos))) {
            controller->fireRequested = 1;
            controller->actionDelay = s1;
        }
    }
}

void Portal_UpdateCountedEffectAction(CountedEffectActionState *controller, CountedEffectActionConfig *config) {
    s32 count;
    char *target;
    CVector3 pos;
    f32 range;
    f32 scale;

    if (controller->phaseCountdown > 0) {
        scale = g_timedActionWaitRandomScale;
        controller->waitTimer = config->firstWaitBase;
        controller->waitTimer =
            (f32) controller->waitTimer
            + Graphu64_RandomFloat(scale) * (f32) config->firstWaitSpread;
        controller->phaseCountdown -= 1;
        return;
    }
    if (controller->phaseCountdown == 0) {
        count = Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem, *(void **) controller);
        if (count == 3) {
            controller->waitTimer = count;
        }
        if (count < controller->waitTimer) {
            controller->effectCountShortfallFlag = 1;
            return;
        }
        controller->phaseCountdown = -1;
        scale = g_alternatingActionWaitRandomScale;
        controller->waitTimer = config->secondWaitBase;
        controller->waitTimer =
            (f32) controller->waitTimer
            + Graphu64_RandomFloat(scale) * (f32) config->secondWaitSpread;
        return;
    }
    controller->waitTimer -= 1;
    target = ((struct ActionTargetPlayerView *) controller->targetView)->player;
    Particle_AverageOwnerEffectPositions(&g_actorParticleEffectSystem, *(void **) controller, &pos);
    range = g_alternatingActionTargetRange;
    pos.y = ((Player *)target)->pos.y;
    if (Graphu64_GetSquaredDistance(&pos, &((Player *)(target))->pos) < range) {
        controller->waitTimer = 0;
    }
    if (controller->waitTimer == 0) {
        controller->actionFlagFrames = 1;
        Portal_InitializeRandomActionSettings(controller, config);
    }
}

void Portal_UpdateMeterGatedActionBurst(void *object, void *settings) {
    AiController *controller = object;
    AiConfig *aiConfig = settings;
    s32 timer;
    s32 minus_one;
    Player *record;
    f32 distance;

    if (controller == 0) {
        return;
    }

    timer = controller->alternateCountdown;
    if (timer == 0) {
        f32 value;

        Particle_FindNearestForeignEffectDistance(&g_actorParticleEffectSystem, controller->player, &value);
        if (value < g_meterActionEffectDistanceLimit) {
            f32 k = g_meterActionChanceBase;
            f32 threshold = Graphu64_RandomFloat(g_meterActionChanceRandomRange) + k;

            if ((f32) aiConfig->meterThreshold < threshold) {
                s32 base = aiConfig->alternateDurationBase;
                controller->actionFlagFrames =
                    (s32) ((f32) base + Graphu64_RandomFloat(k) * (f32) aiConfig->alternateDurationSpread);
            }
            controller->alternateCountdown = aiConfig->meterCooldownBase;
            controller->alternateCountdown =
                (s32) ((f32) controller->alternateCountdown +
                       Graphu64_RandomFloat(k) * (f32) aiConfig->meterCooldownSpread);
            controller->alternateCountdown += controller->actionFlagFrames;
        }
    } else {
        controller->alternateCountdown = timer - 1;
    }

    timer = controller->actionDelay;
    if (timer > 0) {
        controller->actionDelay = timer - 1;
        return;
    }
    minus_one = -1;
    if (timer == minus_one) {
        controller->fireRequested = 1;
        controller->actionDuration += minus_one;
    } else {
        record = controller->target->player;
        distance = Barrel_GetSignedAngleToPoint(controller->player,
                                 record->pos);
        if (Portal_GetEngagementDistance(controller) < distance) {
            return;
        }
        controller->fireRequested = 1;
        controller->actionDelay = minus_one;
    }
    if (controller->actionDuration == 0) {
        controller->fireRequested = 0;
        Portal_InitializeRandomActionSettings(controller, aiConfig);
    }
}

void Portal_LoadCollisionTable(void *resourcePack) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s4;
    s32 base2;
    char *tbl;
    CollisionQuery *src;
    char *dst;

    s2 = 0;
    tbl = &g_actorBehaviorActionConfigs;
    s4 = 0;
    do {
        s0 = 0;
        base2 = s2 * 2;
        s1 = s4;
        do {
            src = SetN64_GetPackSection(resourcePack, base2 + s0);
            dst = (char *)(s1 + (s32)tbl);
            *(CollisionQuery *)dst = *src;
            s0 += 1;
            s1 += 28;
        } while (s0 < 2);
        s2 += 1;
        s4 += 56;
    } while (s2 < 22);
}

void Portal_UpdateTimedActionBurst(void *controller, void *settings) {
    s32 timer;
    s32 minus_one;
    Player *record;
    f32 distance;

    if (controller == 0) {
        return;
    }
    Portal_UpdateRandomActionPulse(controller, settings);
    timer = ((AiController *)controller)->actionDelay;
    if (timer > 0) {
        ((AiController *)controller)->actionDelay = timer - 1;
        return;
    }
    minus_one = -1;
    if (timer == minus_one) {
        ((AiController *)controller)->fireRequested = 1;
        ((AiController *)controller)->actionDuration += minus_one;
    } else {
        record = ((AiController *)controller)->target->player;
        distance = Barrel_GetSignedAngleToPoint(((AiController *)controller)->player, record->pos);
        if (Portal_GetEngagementDistance(controller) < distance) {
            return;
        }
        ((AiController *)controller)->fireRequested = 1;
        ((AiController *)controller)->actionDelay = minus_one;
    }
    if (((AiController *)controller)->actionDuration == 0) {
        ((AiController *)controller)->fireRequested = 0;
        Portal_InitializeRandomActionSettings(controller, settings);
    }
}

void Portal_UpdateHeldActionBurst(void *controller, void *settings) {
    AiController *brain = controller;
    s32 timer;
    Player *record;
    f32 distance;

    if (controller == 0) {
        return;
    }
    Portal_UpdateRandomActionPulse(controller, settings);
    timer = brain->actionDelay;
    if (timer > 0) {
        brain->actionDelay = timer - 1;
        return;
    }
    if (timer == 0) {
        brain->fireRequested = 1;
        brain->actionDuration -= 1;
    }
    if (brain->actionDuration != 0) {
        return;
    }
    brain->actionDelay = -1;
    record = brain->target->player;
    distance = Barrel_GetSignedAngleToPoint(brain->player, record->pos);
    if (Portal_GetEngagementDistance(controller) < distance) {
        brain->fireRequested = 1;
        return;
    }
    brain->fireRequested = 0;
    Portal_InitializeRandomActionSettings(controller, settings);
}

void Portal_UpdateRandomActionPulse(void *controller, void *settings) {
    AiController *o = controller;
    AiConfig *i = settings;
    s32 timer = o->alternateCountdown;

    if (timer == 0) {
        if (o->fireRequested == 0 && o->actionFlagFrames <= 0) {
            f32 k = g_actionPulseChanceBase;
            f32 threshold = Graphu64_RandomFloat(g_actionPulseChanceRandomRange) + k;

            if ((f32) i->pulseChancePercent < threshold) {
                o->actionFlagFrames = 1;
                Portal_InitializeRandomActionSettings(controller, settings);
            }
            o->alternateCountdown = i->alternateCountdownBase;
            o->alternateCountdown =
                (s32) ((f32) o->alternateCountdown +
                       Graphu64_RandomFloat(k) * (f32) i->alternateCountdownSpread);
        }
    } else {
        o->alternateCountdown = timer - 1;
    }
}

void Portal_InitializeRandomActionSettings(void *object, void *settings) {
    AiController *controller = object;
    AiConfig *aiConfig = settings;
    f32 k = g_actionSettingsRandomRange;

    controller->actionDelay = aiConfig->primaryDelayBase;
    controller->actionDelay = (s32) ((f32) controller->actionDelay + (Graphu64_RandomFloat(k) * (f32) aiConfig->primaryDelaySpread));
    controller->actionDuration = aiConfig->primaryDurationBase;
    controller->actionDuration = (s32) ((f32) controller->actionDuration + (Graphu64_RandomFloat(k) * (f32) aiConfig->primaryDurationSpread));
    if (aiConfig->pulseChancePercent == 100) {
        controller->actionFlagFrames = 1;
    }
}
