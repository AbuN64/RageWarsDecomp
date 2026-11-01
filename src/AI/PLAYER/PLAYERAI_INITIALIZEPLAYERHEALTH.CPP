#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/PARTICLE_COLLISION_PROBE_RESULT.H"
#include "include_asm.h"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJRECV5.H"
#include "TYPES.H"

/* Runs a player's hold on a carried object: while the player has a view at 0x5DC, one frame in five
   on average it tints the view through Gsky_StartFade_PlayeraiInitializeplayerhealth with a random alpha below 7.5 and plays effect
   g_frontendScreenStatus at the view's position; the hold time at 0x1D4 counts down by the frame time g_frameElapsedTime,
   and once it runs out or the hold flag at 0x5E4 is clear the player drops flag 0x800000, is released
   through Player_SetPlayerState, and lets go of the object at 0x13D8 through Barrel_FillDamagePacket_PlayeraiInitializeplayerhealth (flags 0x30200 when
   the object is a carried actor with option 0x200, 0x4600 otherwise) before forgetting it and applying
   the result through Playerai_ApplyDamagePacket. */









#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/INTEGERSTATE244.H"
#include "DATA/WEAPON_CALLBACKS/PLAYERAI_INITIALIZEPLAYERHEALTH.H"

extern void Gsky_StartEmitter(char *, f32, f32, f32, f32, s32, Triple);
extern void Barrel_FillDamagePacket(Slot *, Held *, s32, f32, s32, s32);
extern void Playerai_ApplyDamagePacket(SharedPlayer *, char *, Slot *);

void Playerai_UpdateHazardDamage(SharedPlayer *player) {
    Slot hit;
    FadeEmitterView *view;
    Held *owner;
    f32 alpha;
    s32 level;

    if (player->views5DC.view5DC_2.view != 0 && 80.0f < Graphu64_RandomFloat(100.0f)) {
        view = player->views5DC.view5DC_2.view;
        alpha = Graphu64_RandomFloat(7.5f);
        level = (u32) alpha;
        Gsky_StartFade(view, 0xFF, 0xFF, 0, 0, (u8) level, 3, 7);
        Gsky_StartEmitter(&g_frontendScreenStatus, 0.0f, 204.79999f, 0.0f, 512.0f, 0, view->position);
    }
    player->views1C.view1D4_21.holdTime -= g_frameElapsedTime;
    if (player->views1C.view1D4_21.holdTime <= 0.0f || player->views5E4.view5E4_4.holding == 0) {
        owner = 0;
        if (player->views13D8.view13D8_1.held->type == 1 && (player->views13D8.view13D8_1.held->flags & 0x300000)) {
            owner = player->views13D8.view13D8_1.held;
        }
        player->views1C.view100_9.flags &= ~0x800000;
        Player_SetPlayerState(player, player, 2);
        if (owner->options & 0x200) {
            Barrel_FillDamagePacket(&hit, player->views13D8.view13D8_1.held, 0x30200, 25.599998f, 128, 0);
        } else {
            Barrel_FillDamagePacket(&hit, player->views13D8.view13D8_1.held, 17920, 25.599998f, 128, 0);
        }
        player->views13D8.view13D8_1.held = 0;
        Playerai_ApplyDamagePacket(player, player->views1C.view170_16.body, &hit);
    }
}







extern void **g_collisionCurrentActor;


extern void Player_UpdateViewAngles(void *, void *, void *);
extern Shared_Quad Playerai_ComputeAimRotation(void *, void **, Shared_Quad *);
extern f32 Graphu64_GetPointDistance(f32 *, f32 *);
extern s32 CCollision_SweepPoint(void *, CVector3, CVector3, void *);
extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
extern f32 Graphu64_GetHorizontalAngle(CVector3 *);











void Playerai_UpdateTargetFacing(void *player, void *body) {
    Shared_Quad aimRotation;
    Shared_Quad aimWords;
    CVector3 toTarget;
    void *aimTarget;
    f32 targetAngle;
    f32 *position;
    f32 comparisonAngle;

    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    if (((Shared_ActorView *)player)->targeting != 0) {
        aimRotation = Playerai_ComputeAimRotation(player, &aimTarget, &aimWords);
        if (aimTarget != 0) {
            position = &((Shared_ActorView *)player)->position.vector.x;
            if (!(g_playerTargetFacingDistanceLimits[1] < Graphu64_GetPointDistance(position, &((Shared_ActorView *)aimTarget)->position.vector.x))) {
                if (CCollision_SweepPoint(player, ((Shared_ActorView *)player)->position.vector,
                                     ((Shared_ActorView *)aimTarget)->position.vector,
                                     &g_particleCollisionProbeResult) == 0 ||
                    *g_collisionCurrentActor == aimTarget) {
                    Graphu64_SubtractVectors(&toTarget, &((Shared_ActorView *)aimTarget)->position.vector, (CVector3 *)position);
                    targetAngle = Graphu64_GetHorizontalAngle(&toTarget);
                    Graphu64_WrapPeriodicValue(&targetAngle);
                    Graphu64_WrapPeriodicValue(&((LevelActor *)body)->yaw);
                    comparisonAngle = ((LevelActor *)body)->yaw;
                    if (g_playerTargetFacingPositiveWrapThreshold < comparisonAngle) {
                        if (targetAngle < g_playerTargetFacingNegativeWrapThreshold) {
                            targetAngle += g_playerTargetFacingYawPeriod;
                        } else {
                            goto positive;
                        }
                    } else {
positive:
                        comparisonAngle = targetAngle;
                        if (g_playerTargetFacingTurnThreshold < comparisonAngle &&
                            ((LevelActor *)body)->yaw < g_playerTargetFacingBodyYawThreshold) {
                            ((LevelActor *)body)->yaw =
                                ((LevelActor *)body)->yaw + g_playerTargetFacingBodyYawPeriod;
                        }
                    }
                    Graphu64_EaseValueToward(&((LevelActor *)body)->yaw, targetAngle, g_playerTargetFacingEaseRate);
                }
            }
        }
    }
}

#include "TYPES.H"

typedef struct { u8 pad0[0x18]; s32 health; u8 pad1C[0xE0]; f32 x, y, z; } ActorTemplate;
typedef struct { u8 pad0[0x80]; s8 kind; u8 pad81[0xE]; u8 special; u8 pad90[4]; u8 boosted; } PlayerInfo;
typedef struct {
    u8 pad0[3]; s8 alpha; u8 pad4[0x14]; ActorTemplate *model;
    u8 pad1C[0x34]; f32 x, y, z; u8 pad5C[0x118]; s32 health;
    u8 pad178[0x45C]; s32 slot; PlayerInfo *info; s32 pad5DC;
    s32 modelId; s32 maxHealth; u8 pad5E8[0xE68]; s32 bot;
} BonusPlayer;
typedef struct { s32 value; u8 pad4[0x18C]; } PlayerBonus;
struct Shared_World;
extern void *Scene_FindActorDefinition(struct Shared_World *, s32, s32);

/* g_resultExitPending and g_selectedProfileHealthOptionEnabled are game option words, read through an option view. */
typedef struct { s32 enabled; } GameOption;
static inline s32 optionEnabled(GameOption *option) {
    return option->enabled;
}
static inline ActorTemplate *findModel(s32 kind, s32 id) {
    return Scene_FindActorDefinition(&g_world, kind, id);
}
static inline s32 startHealth(BonusPlayer *player) {
    s32 health;
    s8 kind;
    if (optionEnabled((GameOption *)&g_gameSettings.counters.enabled) && player->info->boosted != 0) {
        kind = player->info->kind;
        if (kind == 11) health = 0x19000;
        else if (kind == 12) health = 0x19000;
        else if (kind == 14) health = 76800;
        else if (kind == 13) health = 76800;
        else health = player->model->health << 8;
    } else {
        health = player->model->health << 8;
    }
    if (g_gameSettings.controllerMode == 1 && player->bot == 0) health += ((PlayerBonus *)g_characterHealthBonuses)[player->slot].value;
    return health;
}
void Playerai_InitializePlayerHealth(BonusPlayer *player) {
    ActorTemplate *model;
    s32 id;
    id = player->modelId;
    if (optionEnabled((GameOption *)&g_gameSettings.counters.m_bFragTagOn) && player->info->special == 1) id = 19;
    model = findModel(11, id);
    if (model == 0) {
        model = findModel(11, -1);
        if (model == 0) model = findModel(-1, -1);
    }
    player->model = model;
    player->x = model->x; player->y = model->y; player->z = model->z;
    if (optionEnabled((GameOption *)&g_gameSettings.counters.m_bFragTagOn) && player->info->special != 0) {
        player->maxHealth = 2560;
        player->health = 2560;
        return;
    }
    player->maxHealth = startHealth(player);
    player->health = startHealth(player);
    player->alpha = 0xFF;
}
