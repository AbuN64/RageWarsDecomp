#include "Render/movingai.h"
#include "Multi/initial.h"
#include "Common/aiprofile.h"
#include "Ai/cteamselect.h"
#include "Ai/Player/playerai_buildforcemarkertransform.h"
#include "Ai/Player/player_resetplayerforround.h"
#include "Animpool/animpool_spawndescribedsceneeffect.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Cteamselect/player_resetplayerforround_data.h"
#include "Frontend/player.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Gobjinst/gobjinst_findnearestbonebounds.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Placeplayerlight/placeplayerlight.h"
#include "Playerai/playerai__playerai.h"
#include "Player_updateplayercamera/player_updateplayercamera.h"
#include "Pools/pools.h"
#include "Render/control_cycleactorsnapshotmode.h"
#include "Common/gameplay_transition.h"
#include "Common/gameplay_camera.h"
#include "Common/sharedplayer.h"
#include "Common/vector4f.h"
#include "Common/shared_gameslot.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Common/world.h"
#include "Common/runtime_declarations.h"
#include "Common/triple.h"
#include "Render/player_spawn_placement.h"
#include "Engine/Cinema/cinema.h"
#include "Common/frontend_clock_state.h"
#include "Render/setn64_updatefadetransition.h"
#include "include_asm.h"
#include "Common/player_pool_and_inode_cache_views.h"
#include "types.h"
#include "Common/resultsoptionsscreen.h"
#include "Weapons/player_movement_interfaces.h"
#include "Menu/pak_load.h"
#include "Ai/Player/player_placeplayerforround.h"
#include "Ai/playerprofile.h"
#include "Player/player_getammocapacity.h"
#include "Ovlgame/ovlgame_address_symbols.h"
#include "Common/stagepreset.h"
#include "Common/playerprofiles.h"
#include "Common/gameplay_settings.h"
#include "Menu/Items/game_and_player_options.h"
#include "Common/game_session.h"
#include "Ovlgame/ovlgame_initializeplayerpool.h"
#include "Common/heap_arena_entry.h"
#include "Common/snapshot_actor.h"
#include "Ai/Nav/scaled_initplayerstate.h"
#include "Fx/contpad_initcontrollerinput.h"
#include "Ui/X_files/x_plus.h"
#include "Engine/Cache/list.h"
#include "Weapons/actor_requestactorstate.h"
#include "Ai/Player/player_buildplayerviewtransform.h"
#include "Cache/cache_allocateresourceat.h"
#include "Player/player_resetplayerforround.h"
#include "Source/itemmenu.h"
#include "Common/pakqueuestate.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/objb.h"
#include "Common/actor_definition.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Ai/Player/player_startplayeranimation.h"
#include "Audio/voice.h"
#include "Player/playerai_initializeplayerhealth.h"
#include "Voice/voice.h"

#if defined(VERSION_US_REV1)
/* ROM offsets of the actor part tables: each version names its own copies. */
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddress
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddress
#define ACTORPART_T280 g_playerDamageReactionCallbackAddress
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddress
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddress
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddress
#elif defined(VERSION_US)
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressUs
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressUs
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressUs
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressUs
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressUs
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressUs
#elif defined(VERSION_DE)
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressDe
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressDe
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressDe
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressDe
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressDe
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressDe
#elif defined(VERSION_EU)
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressEu
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressEu
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressEu
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressEu
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressEu
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressEu
#elif defined(VERSION_EU_X)
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressEuX
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressEuX
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressEuX
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressEuX
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressEuX
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressEuX
#endif

#include "Menu/initview.h"
#include "Achieve/achieve.h"
/* Initialises an actor and its embedded part at 0x2E8: sets the shared table pointers and flag bits (one flag
 * depends on g_frontendScreenStatus.settings.local), runs the part setup calls, then copies the view's position into the actor. */
void Player_InitActorParts(SharedPlayer *player, LevelPlacedActorRecord *rec, s32 mode, s32 index) {
    char *actor = (char *)player;
    Player *record = (Player *)player;
    u32 flags;
    InitView *view;
    record->actorParts[0].controller = actor;
    Gobjinst_InitializePlacedActor(actor, rec, (void *)mode, 0);
    record->actorParts[0].controller = actor;
    {
        u32 withPart = record->actorParts[0].flags | 0x100000;
        u32 withShadow = withPart | 0x10000;
        u32 withContact = withShadow | 0x1000000;

        flags = withContact | 0x2000000;
    }
    record->actorParts[0].flags = flags;
    if (g_frontendScreenStatus.settings.local == 0) {
        record->actorParts[0].flags = flags | 0x10000000;
    }
    record->actorParts[0].controllerUpdate = ACTORPART_T28C;
    record->actorParts[0].table290 = ACTORPART_T290;
    record->actorParts[0].table280 = ACTORPART_T280;
    record->actorParts[0].projectileContactCallback = (void (*)(LevelActor *, s32 *, void *))ACTORPART_T288;
    if (g_frontendScreenStatus.settings.local != 0) {
        record->actorParts[0].update = ACTORPART_ACTION;
    }
    record->actorParts[1].controller = actor;
    Gobjinst_InitializePlacedActor(((char *)&((SharedPlayer *)actor)->views1C.view2E8_27.weapon), rec, (void *)mode, 0);
    record->actorParts[1].controllerUpdate = ACTORPART_PART1_T28C;
    record->actorParts[1].animationMarker = -1;
    record->actorParts[1].flags |= 0x200000;
    record->actorParts[1].scale.x = g_respawnPlayerInitialPartScale;
    record->actorParts[1].scale.y = g_respawnPlayerInitialPartScale;
    record->actorParts[1].scale.z = g_respawnPlayerInitialPartScale;
    record->actorParts[1].controller = actor;
    record->actorParts[1].table280 = ACTORPART_T280;
    record->actorParts[1].projectileContactCallback = (void (*)(LevelActor *, s32 *, void *))ACTORPART_T288;
    record->selectedAction = -1;
    record->actorParts[1].flags &= 0xFFFEFFFF;
    Actor_RequestActorState(((char *)&((SharedPlayer *)actor)->views1C.view2E8_27.weapon), ((char *)&((SharedPlayer *)actor)->views1C.view458_29.ammo), 0);
    Weaponai_ApplyWeaponSwitch(((char *)&((SharedPlayer *)actor)->views1C.view2E8_27.weapon), ((char *)&((SharedPlayer *)actor)->views1C.view458_29.ammo));
    Player_UpdatePlayerCamera(actor, actor);
    if (record->camera != 0) {
        Cinema_UpdateSequenceTrack(record->camera);
    }
    record->actorParts[0].scale.x = ((InitView *)record->actorParts[0].definition)->x;
    record->actorParts[0].scale.y = ((InitView *)record->actorParts[0].definition)->y;
    record->actorParts[0].scale.z = ((InitView *)record->actorParts[0].definition)->z;
    view = (InitView *)record->actorParts[0].definition;
    view->flags &= ~4;
}
struct RespawnPlayer;

/* Resets a player/actor record for a new run: marks it active, stores the character, picks up the HUD
 * object, clears the per-slot counters and weapon tables, selects the start mode from the multiplayer setting
 * and zeroes the per-player entries of the two global tables. */
void Player_ResetPlayerForRound(void *actor, s32 character, s32 force_active) {
    s32 i;
    Shared_Game *globals;
    s32 openFlag = 0;
    unsigned long counterAddress, counterAddress2;
    Control_IsSnapshotActive();
    ((Player *)actor)->actorState = 1;
    ((Player *)actor)->state = character;
    if (((Player *)actor)->computer == 0) {
        ((Player *)actor)->camera = Pools_RecycleModel(&g_frontendScreenStatus);
        if (g_frontendScreenStatus.modes.remoteSession != 0) {
            ((Player *)actor)->computer = 1;
        }
    } else {
        ((Player *)actor)->camera = 0;
    }
    TeamSelect_ResetWeaponWheel((char *)&((SharedPlayer *)((Player *)actor))->views5E8.view938_128.strokes);
    TeamSelect_ResetTeamWheel((char *)&((SharedPlayer *)((Player *)actor))->views5E8.viewCCC_164.teamWheel);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    for (i = 1; i < 22; i++) {
        ((Player *)actor)->actions[i][0] = 0;
        ((Player *)actor)->actions[i][1] = -1;
    }
    ((Player *)actor)->actions[0][0] = 1;
    ((Player *)actor)->actions[0][1] = 0;
    ((Player *)actor)->actions[3][1] = 2;
    ((Player *)actor)->actions[4][0] = 1;
    ((Player *)actor)->actions[4][1] = 1;
    ((Player *)actor)->actions[3][0] = 1;
    ((Player *)actor)->actions[10][0] = 1;
    ((Player *)actor)->actions[2][0] = 1;
    ((Player *)actor)->actions[10][1] = 4;
    ((Player *)actor)->actions[2][1] = 5;
    ((Player *)actor)->actions[14][0] = 1;
    ((Player *)actor)->actions[14][1] = 6;
#endif
    (*(s16 *)((char *)((Player *)actor) + 1512)) = 0;
    i = 5;
    counterAddress = (unsigned long)((Player *)actor) + i;
    do {
        *(u8 *)(counterAddress + ((char *)&((Player *)0)->eventCounters[0] - (char *)0)) = 0;
        counterAddress--;
    } while (--i >= 0);
    i = 5;
    counterAddress2 = (unsigned long)((Player *)actor) + i;
    do {
        *(u8 *)(counterAddress2 + ((char *)&((Player *)0)->eventCounters[1] - (char *)0)) = 0;
        counterAddress2--;
    } while (--i >= 0);
    if (g_frontendScreenStatus.settings.local != 0) {
        if (g_gameControllerMode == 1 && ((Player *)actor)->computer == 0) {
            u32 value = Player_GetLevelProgress(&g_localPlayerProfiles[((Player *)actor)->slot], ((Player *)actor)->profile->character);
            ((Player *)actor)->countdown = ((value & 0xFF) >> 1) + 1;
        }
        if (g_gameControllerMode == 4 && ((Player *)actor)->computer == 0 && g_currentStagePreset != 0) {
            ((Player *)actor)->countdown = g_currentStagePreset->laps;
        }
        ((Player *)actor)->respawnHealth = 1;
    } else {
        ((Player *)actor)->respawnHealth = 3;
    }
    ((Player *)actor)->overkill = 0;
    Player_ResetPlayerWeapons((struct RespawnPlayer *)((Player *)actor));
    ((Player *)actor)->damageCooldown = 0;
    ((Player *)actor)->europeanEffectTimer = 0;
    ((Player *)actor)->animation = -1;
    ((Player *)actor)->secondEffectId = -1;
    for (i = 0; i < 8; i++) {
        ((Player *)actor)->profile->roundCounts[2][i] = 0;
        ((Player *)actor)->profile->roundCounts[3][i] = 0;
        ((Player *)actor)->profile->roundCounts[0][i] = 0;
        ((Player *)actor)->profile->roundCounts[1][i] = 0;
    }
    ((Player *)actor)->profile->roundTotals[0] = 0;
    ((Player *)actor)->profile->roundTotals[1] = 0;
    ((Player *)actor)->profile->roundTotals[2] = 0;
    ((Player *)actor)->profile->roundTotals[3] = 0;
    ((Player *)actor)->profile->roundTotals[5] = 0;
    ((Player *)actor)->profile->roundTotals[4] = 0;
    ((Player *)actor)->profile->roundFlags[0] = 0;
    ((Player *)actor)->profile->roundFlags[1] = 0;
    ((Player *)actor)->profile->bonus = 0;
    ((Player *)actor)->profile->state90 = 0;
    ((Player *)actor)->trackEventBits = 0;
    ((Player *)actor)->roundStateB = 1;
    ((Player *)actor)->roundStateC = 0;
    ((Player *)actor)->reservedWord868 = 1;
    Player_ResetRespawnedPlayer((struct RespawnPlayer *)((Player *)actor));
    globals = &g_gameSettings;
    if (globals->local != 0) {
        ((Player *)actor)->scoreResetFlag = 0;
    }
    if (openFlag != 0) {
        char *table;
        if (globals->local != 0) {
            ((Player *)actor)->profile->character = 0;
            ((Player *)actor)->state = 0;
            ((Player *)actor)->playerStateDirty = 1;
            table = g_roundStartModeSpecificDialogTable;
            if (globals->counters.teams == 0) {
                table = g_playerMenuDialogTable;
            }
        } else {
            table = g_roundStartDefaultDialogTable;
        }
        Menu_OpenDialog((char *)&((Player *)actor)->camera->messageList, table, (void *)((Player *)actor), ((Player *)actor)->weaponAnimation, ((Player *)actor)->slot);
    }
    g_playerHitCounts[((Player *)actor)->slot] = 0;
    g_playerCountedShots[((Player *)actor)->slot] = 0;

}

/* Prepares a player's per-run HUD state: runs the mode-specific setup when the session flag is set, resets
 * the HUD effect record to its defaults, lays out the on-screen widgets (position, then their string tables),
 * zeroes the two score fields and the panel, and copies the following camera's orientation. */
void Player_InitActorHudState(SharedPlayer *actor) {
    char *widget;
    char *hud;
    s32 enabled;
    struct Shared_Game *settings = &g_gameSettings;
    if (settings->local != 0) {
        Playerai_LoadActorModel(actor);
        Playerai_UpdateCharacterModel(actor);
        if (((Player *)actor)->profile->sessionApplied == 0 && settings->controllerMode == 1) {
            Achieve_ApplyProfileWeaponUnlocks(actor);
        }
    }
    hud = (char *)&actor->views5E8.view878_158.effect;
    (*(s32 *)((char *)hud + 180)) = 0;
    (*(s32 *)((char *)hud + 8)) = 0;
    (*(s32 *)((char *)hud + 184)) = 0;
    (*(s32 *)((char *)hud + 4)) = -1;
    (*(s32 *)((char *)actor + 2168)) = -1;
    (*(s32 *)((char *)hud + 168)) = 0;
    (*(s32 *)((char *)hud + 156)) = 0;
    (*(s32 *)((char *)hud + 164)) = 0;
    (*(f32 *)((char *)hud + 172)) = 437.5f;
    (*(f32 *)((char *)hud + 176)) = (-675.0f);
    (*(f32 *)((char *)hud + 144)) = 0.25f;
    (*(f32 *)((char *)hud + 148)) = 0.1875f;
    (*(f32 *)((char *)hud + 152)) = 0.25f;
    (*(f32 *)((char *)hud + 160)) = 1.5707965f;
    (*(s32 *)((char *)actor + 4528)) = 0;
    Control_SetProfileMode((void *)(*(s32 *)((char *)actor + 1688)), 1);
    (*(s32 *)((char *)actor + 1656)) = 0;
    (*(s32 *)((char *)actor + 1660)) = 0;
    (*(s32 *)((char *)actor + 1664)) = 0;
    (*(s32 *)((char *)actor + 1668)) = 0;
    widget = (char *)&((Player *)actor)->hudMovers[0];
    OnScreen_InitMover(widget, 120, 96);
    OnScreen_StartMoverScript(widget, g_hudStatusWidgetLeftMoverScript);
    widget = (char *)&((Player *)actor)->hudMovers[1];
    OnScreen_InitMover(widget, 190, 96);
    OnScreen_StartMoverScript(widget, g_hudStatusWidgetCenterMoverScript);
    widget = (char *)&((Player *)actor)->hudMovers[2];
    OnScreen_InitMover(widget, 260, 96);
    OnScreen_StartMoverScript(widget, g_hudStatusWidgetRightMoverScript);
    widget = (char *)&((Player *)actor)->hudMovers[3];
    OnScreen_InitMover(widget, 28, 96);
    OnScreen_StartMoverScript(widget, g_hudStatusWidgetSlideInMoverScript);
    widget = (char *)&((Player *)actor)->hudMovers[4];
    OnScreen_InitMover(widget, -64, 16);
    OnScreen_StartMoverScript(widget, g_hudLivesInitialMoverScript);
    widget = (char *)&((Player *)actor)->hudMovers[5];
    OnScreen_InitMover(widget, 40, 16);
    OnScreen_StartMoverScript(widget, k_PlaceplayerlightData);
    widget = (char *)&((Player *)actor)->hudMovers[9];
    OnScreen_InitMover(widget, -82, 16);
    OnScreen_StartMoverScript(widget, g_hudScoreInitialMoverScript);
    widget = (char *)&((Player *)actor)->hudMovers[10];
    (*(f32 *)((char *)actor + 4220)) = 255.0f;
    OnScreen_InitMover(widget, -82, 68);
    OnScreen_StartMoverScript(widget, g_hudCountInitialMoverScript);
    widget = (char *)&((Player *)actor)->hudMovers[11];
    OnScreen_InitMover(widget, -82, 68);
    OnScreen_StartMoverScript(widget, g_hudSquadInitialMoverScript);
    OnScreen_InitMover((char *)&((Player *)actor)->hudMovers[7], 24, (s16)((u16)g_hudReferenceViewportHeight + 96));
    OnScreen_InitMover((char *)&((Player *)actor)->hudMovers[8], 24, (s16)((u16)g_hudReferenceViewportHeight + 96));
    OnScreen_InitMover((char *)&((Player *)actor)->hudMovers[12], 100, 100);
    (*(s32 *)((char *)actor + 4548)) = 0;
    (*(s32 *)((char *)actor + 1980)) = 0;
    (*(s32 *)((char *)actor + 4404)) = (*(s32 *)((char *)actor + 1508));
    if ((*(void * *)((char *)actor + 1500)) != 0) {
        *(CQuatern *)(&((Player *)actor)->cameraOrientation) = *(CQuatern *)(&((GameplayCamera *)(*(void * *)((char *)actor + 1500)))->orientation);
    }
    Playerai_InitializeMovementAndAim(actor);
    enabled = 0;
    if (Cinema_IsSequenceActive() == 0) {
        enabled = enabled < (u32)(g_activeActorKind ^ 0x3E7);
    }
    if (g_world.visibilityEnabled != 0) {
        enabled = 1;
    }
    if (enabled != 0) {
        ((Player *)actor)->model = g_activeActorKind;
    }
    ((Player *)actor)->projectiles[1] = 0;
    ((Player *)actor)->projectiles[0] = 0;
    Cinema_ClearPlaybackFlag();
    if (actor->views0.view14_6.model != 0) {
        Link_DispatchObjectLinks(actor->views0.view14_6.model, 1, actor);
    }
    Cinema_SetPlaybackFlag();
}
#include "types.h"
#include "Common/player_pool_and_inode_cache_views.h"
#include "Common/level_actor.h"
#include "Weaponai/weaponai_drawredmarkerquad_weapon.h"
#include "Player/playerai_applydamageovertime_player_updatefragtagselection_data.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Player/playerai_initializeplayerhealth.h"
#include "Actor/actor_updateactorstateanimation.h"
#include "Ai/playerprofile.h"
#include "Ovlgame/ovlgame_address_symbols.h"
#include "Common/stagepreset.h"
#include "Common/playerprofiles.h"
#include "Ai/Devices/Movingai/movingai.h"
#include "Ai/player_death_playerai.h"
#include "Common/viewflags.h"
/* Phase1 source candidate; contract holds and immutable inputs in per-function JSON. */
/** Reset a player for a new life: restore health, clear status timers and effects, and drop any carried object. */
typedef struct RespawnPair {
    signed char kind;
    signed char state;
} RespawnPair;
typedef struct RespawnPlayer {
    char pad0[0x38];
    int moving;
    char pad3C[0x174 - 0x3C];
    int maxHealth;
    char pad178[0x5D4 - 0x178];
    int character;
    char pad5D8[0x5E4 - 0x5D8];
    int health;
    char pad5E8[0x5EA - 0x5E8];
    short state;
    char pad5EC[0x602 - 0x5EC];
    RespawnPair effects[22];
    char pad62E[0x670 - 0x62E];
    float bob;
    char pad674[0x698 - 0x674];
    void *anim;
    char pad69C[0x11B4 - 0x69C];
    int reservedWordA;
    int movementBlocked;
    char pad11BC[0x11D8 - 0x11BC];
    int recoil;
    char pad11DC[0x11E4 - 0x11DC];
    int reservedWordB;
    LevelActor *carried;
    int reservedWordC;
    char pad11F0[0x11FC - 0x11F0];
    int reservedWordD;
    char pad1200[0x1210 - 0x1200];
    int reservedWordE;
    char pad1214[0x12C0 - 0x1214];
    float fade;
    char pad12C4[0x13C8 - 0x12C4];
    int sequenceRunEndActive;
    char pad13CC[0x13D4 - 0x13CC];
    int reservedWordF;
    int heldActor;
    int reservedWordG;
    int reservedWordH;
    int attachedSpecialEffectCount;
    char pad13E8[0x1450 - 0x13E8];
    int isBot;
    void *brain;
} RespawnPlayer;
static inline int isOnline(void) {
    return g_frontendScreenStatus.settings.local;
}

static inline void releaseState(LevelActor *carried, s32 *state) {
    if (state != 0) {
        Barrel_StopActorLoopingSound(carried, state);
        *state |= 0x20;
    }
}
void Player_ResetRespawnedPlayer(struct RespawnPlayer *player) {
    int i;
    LevelActor *carried;

    Playerai_ClearDamageTimers(player);
    player->moving = 0;
    player->fade = g_respawnPlayerInitialFade;
    Control_SetProfileMode(player->anim, 1);
    if (g_frontendScreenStatus.settings.local != 0) {
        Playerai_InitializePlayerHealth(player);
    } else {
        if (player->isBot == 0) {
            player->health = g_characterHealthBonuses[player->character].value + 25600;
        } else {
            player->health = 25600;
        }
        player->maxHealth = player->health;
    }
    player->bob = g_respawnPlayerInitialBob;
    Playerai_InitializeMovementAndAim(player);
    player->recoil = 0;
    player->reservedWordD = 0;
    player->reservedWordH = 0;
    player->reservedWordE = 0;
    player->reservedWordC = 0;
    player->reservedWordB = 0;
    player->heldActor = 0;
    player->reservedWordG = 0;
    player->attachedSpecialEffectCount = 0;
    player->reservedWordF = 0;
    if (SetN64_IsModeThirteen() != 0 && g_frontendScreenStatus.settings.local == 0 && (u32)g_gameLoopFrameCount > 10U && player->state < 11) {
        SoundElement_PlayDialogGroup(g_playerStateDialogGroups[player->state]);
    }
    if (isOnline()) {
        Player_ResetPlayerWeapons(player);
    }
    player->reservedWordA = 0;
    player->movementBlocked = 0;
    player->sequenceRunEndActive = 0;
    if (player->isBot != 0) {
        Nav_ResetPlayerState(player->brain);
    }
    for (i = 1; i < 22; i++) {
        if (player->effects[i].state == 3 || player->effects[i].state == 7) {
            player->effects[i].kind = 0;
            player->effects[i].state = -1;
        }
    }
    carried = player->carried;
    if (carried != 0) {
        releaseState(carried, &carried->behaviorFlags);
        carried->flags &= ~0x2000;
        carried->flags &= ~0x100;
        Animpool_ReleaseSceneEffect(player->carried);
        player->carried = 0;
    }
}

/* Starts a player's run: in a multiplayer session (g_gameSettings.local) picks the lap count from the chosen track through Player_GetLevelProgress_MatchGetresulttext in mode 1 or from the loaded course in mode 4 for a human player, sets the run type at 0x5EA (1, or 3 in single player), clears 0x13C8 and 0x85C around Player_ResetRespawnedPlayer, then starts its vehicle through Player_PlacePlayerAtSpawnPoint with model 0xC1D for a computer player in state 12 during stage 9 and its own model otherwise, doubled when g_playerCount is two or more. */


void Player_PlacePlayerForRound(SharedPlayer *player) {
    s32 scale;

    scale = (g_playerCount >= 2) * 2;
    if (g_gameSettings.local != 0) {
        if (g_gameControllerMode == 1 && player->views1450.view1450_1.computer == 0) {
            player->views133C.view133C_1.laps = ((u8)Player_GetLevelProgress(&g_localPlayerProfiles[player->views1C.view5D4_46.slot], player->views5D8.view5D8_1.record->characterId) >> 1) + 1;
        }
        if (g_gameControllerMode == 4 && player->views1450.view1450_1.computer == 0 && g_currentStagePreset != 0) {
            player->views133C.view133C_1.laps = g_currentStagePreset->laps;
        }
        player->views5E8.view5EA_4.runType = 1;
    } else {
        player->views5E8.view5EA_4.runType = 3;
    }
    player->views13C8.view13C8_1.w13C8 = 0;
    Player_ResetRespawnedPlayer(player);
    player->views5E8.view85C_120.w85C = 0;
    if (player->views5DC.view5E0_9.state == 12 && player->views1450.view1450_1.computer != 0 && g_activeLinkSequenceId == 9) {
        Player_PlacePlayerAtSpawnPoint(player, 3101, scale, 1);
    } else {
        Player_PlacePlayerAtSpawnPoint(player, player->views5E8.view5EC_6.model, scale, 1);
    }
}

/* Ends a human player's run. Outside a networked session (or as its local host) the countdown at 0x133C ticks
 * down and, on reaching zero, clears humanWon and calls Playerai_EndRound on the menu data. Then a human player with
 * countdown left respawns with the chosen model (scaled when two or more players are in) and resets; otherwise
 * the run is settled through Player_SetPlayerState, except for a local idle player whose profile has no bonus. */
void Player_UpdateRunEndPlayer(struct Player *player)
{
    s32 modelScale = (g_playerCount >= 2) * 2;

    if (!(g_playerViewRenderContext.game.flags & 2) || g_playerViewRenderContext.game.local) {
        if ((g_playerViewRenderContext.game.controllerMode == 1 || g_playerViewRenderContext.game.controllerMode == 4) && player->computer == 0) {
            if (player->countdown > 0) {
                player->countdown--;
            }
            if (player->countdown == 0) {
                g_playerViewRenderContext.game.humanWon = 0;
                Playerai_EndRound(&g_playerViewRenderContext);
            }
        }
    }
    {
        Shared_Game *game = &g_playerViewRenderContext.game;

        if ((game->controllerMode == 1 || game->controllerMode == 4) && player->computer == 0) {
            if (player->countdown <= 0) {
                if (game->local && player->animationDone == 0 && player->profile->bonus == 0) {
                    return;
                }
                Player_SetPlayerState(player, player, 18);
            } else {
                Player_PlacePlayerAtSpawnPoint(player, player->model, modelScale, 1);
                Player_ResetRespawnedPlayer(player);
            }
        } else {
            Player_SetPlayerState(player, player, 18);
        }
        player->resetState = 0;
    }
}

/* Resets a 0x44-byte record: clears it through XPlus_FillMemory, initialises the two lists at offsets
   0xC and 0x20 through List_InitializeIntrusive with 0x16DC and 0x16E0, and clears the words at 0 to 8 and
   0x34 to 0x40. */

/* Refreshes every instance owned by the holder and clears their pending flag. */

s32 SetN64_IsModeThirteen(void);

/* Sets the byte at offset 0x78 of the object at 0x5D8 of an actor, calls Player_ResetPlayerForRound with the
   actor, its second argument and one, then Actor_RequestActorState_Damageai on offsets 0x2E8 and 0x458 with two and
   Player_PlacePlayerAtSpawnPoint with g_playerSpawnSelector, zero and one. */
void Player_InitializePlayerPool(CPlayerPool *pool, s32 count, s32 force_active) {
    s32 i;
    s32 j;
    s32 entry_offset;
    s32 attribute_offset;
    s32 player_index;
    s32 object_offset;
    s32 roster_index;
    u8 object_id;
    void *owner;
    char *object;
    char *entry;
    char *global;
    char *state;

    List_InitializeIntrusive(&pool->m_FreeList, 5852, 5856);
    List_InitializeIntrusive(&pool->m_ActiveList, 5852, 5856);
    Control_SetControllerMode(0);
    Cache_DrainAndCompactResources(0);
    global = (char *)&g_gameSettings;

    if (pool->m_pmePlayers != 0) {
        Cache_ReleaseResource(0, pool->m_pmePlayers);
        pool->m_pmePlayers = 0;
        pool->m_Players = 0;
        pool->count = 0;
    }

    if (count == 0) {
        return;
    }

    Player_AllocPlayerList(pool, count);
    for (i = 0; i < pool->count; i++) {
        List_AppendIntrusive(&pool->m_FreeList, pool->m_Players + i * sizeof(SharedPlayer));
    }

    for (i = 0; i < pool->count; i++) {
        entry = (char *)&((Shared_Game *)global)->playerSettings[i];
        if (((CPlayerOptions *)(entry))->talsetPosse != 0) {
            ((CPlayerOptions *)(entry))->active = 0;
        }
    }

    entry = (char *)&((Shared_Game *)global)->defaults;
    if (((GameModeEnableView *)(global))->local != 0) {
        if (pool->count <= 0) {
            goto initialized;
        }
        i = 0;
        player_index = i;
        attribute_offset = i;
        entry_offset = 208;
        object_offset = i;
initialize_object:
            entry = global + entry_offset;
            object = pool->m_Players + object_offset;
            ((struct Player *)(object))->computer = ((CPlayerOptions *)(entry))->isBot;
            ((struct Player *)(object))->actorState = 0;
            if (((struct Player *)(object))->computer != 0) {
                ContPad_InitControllerInput((char *)&((SharedPlayer *)object)->views5E8.view688_33.body, g_botControllerProfile);
                ((struct Player *)(object))->slot = ((CPlayerOptions *)(entry))->controller;
            } else {
                ContPad_InitControllerInput((char *)&((SharedPlayer *)object)->views5E8.view688_33.body, (u8 *)g_controllerProfiles + attribute_offset);
                ((struct Player *)(object))->slot = i;
            }
            owner = ((struct Player *)(object))->controller;
            ((struct Player *)(object))->profile = (AiProfile *)entry;
            object_id = ((CPlayerOptions *)(entry))->characterSkin;
            ((struct Player *)(object))->firstHandle = 0;
            ((struct Player *)(object))->secondHandle = 0;
            ((struct Player *)(object))->model = 0;
            ((struct Player *)(object))->reservedWord5F0 = 0;
            ((struct Player *)(object))->reservedWord864 = 0;
            ((struct Player *)(object))->reservedWord868 = 0;
            ((struct Player *)(object))->actorParts[0].controller = object;
            ((struct Player *)(object))->playerId = object_id;
            Scaled_InitPlayerState(owner, object);
            ((struct Player *)(object))->overkill = 0;
            ((struct Player *)(object))->projectileBase = player_index;
            ((struct Player *)(object))->projectileIndex = 0;
            ((struct Player *)(object))->reactionFlags = 0;
            ((struct Player *)(object))->reservedWord11CC = 0;
            ((struct Player *)(object))->reservedWord1218 = 0;
            for (j = 0; j < 8; j++) {
                ((Player *)object)->reset12CC[j] = 0;
                ((Player *)object)->reset12F4[j] = 0;
            }
            ((struct Player *)(object))->reservedWord1338 = -1;
            ((struct Player *)(object))->reservedWord12C4 = 0;
            ((struct Player *)(object))->reservedWord12C8 = 0;
            ((struct Player *)(object))->reservedWord1334 = 0;
            ((struct Player *)(object))->animationTable = g_playerActionStateHandlers;
            ((struct Player *)(object))->reservedWord11E8 = 0;
            Playerai_InitializeMovementAndAim(object);
            ((struct Player *)(object))->pickupEffectToggle = 0;
            ((struct Player *)(object))->pendingBonus = 0;
            ItemMenu_ResetEntries(&((Player *)object)->itemMenu);
            if (((CPlayerOptions *)(entry))->active != 0) {
                Player_ResetPlayerForRound(object, ((CPlayerOptions *)(entry))->character, 1);
                List_RemoveIntrusive(&pool->m_FreeList, object);
                List_PrependIntrusive(&pool->m_ActiveList, object);
            }
            player_index += 2;
            attribute_offset += 548;
            entry_offset += 150;
            object_offset += 5864;
            if (++i < pool->count) {
                goto initialize_object;
            }
    } else {
        object = pool->m_Players;
        roster_index = ((CPlayerOptions *)(entry))->controller;
        ((struct Player *)(object))->computer = ((CPlayerOptions *)(entry))->isBot;
        ((struct Player *)(object))->actorState = 0;
        if (((struct Player *)(object))->computer != 0) {
            ContPad_InitControllerInput((char *)&((SharedPlayer *)object)->views5E8.view688_33.body, g_botControllerProfile);
            ((struct Player *)(object))->slot = ((CPlayerOptions *)(entry))->controller;
        } else {
            ContPad_InitControllerInput((char *)&((SharedPlayer *)object)->views5E8.view688_33.body, &g_controllerProfiles[roster_index]);
            ((struct Player *)(object))->slot = roster_index;
        }
        owner = ((struct Player *)(object))->controller;
        ((struct Player *)(object))->profile = (AiProfile *)entry;
        object_id = ((CPlayerOptions *)(entry))->characterSkin;
        ((struct Player *)(object))->firstHandle = 0;
        ((struct Player *)(object))->secondHandle = 0;
        ((struct Player *)(object))->model = 0;
        ((struct Player *)(object))->reservedWord5F0 = 0;
        ((struct Player *)(object))->reservedWord864 = 0;
        ((struct Player *)(object))->reservedWord868 = 0;
        ((struct Player *)(object))->actorParts[0].controller = object;
        ((struct Player *)(object))->playerId = object_id;
        Scaled_InitPlayerState(owner, object);
        ((struct Player *)(object))->overkill = 0;
        ((struct Player *)(object))->projectileBase = roster_index * 2;
        ((struct Player *)(object))->projectileIndex = 0;
        ((struct Player *)(object))->reactionFlags = 0;
        ((struct Player *)(object))->reservedWord11CC = 0;
        ((struct Player *)(object))->reservedWord1218 = 0;
        for (j = 0; j < 8; j++) {
            ((Player *)object)->reset12CC[j] = 0;
            ((Player *)object)->reset12F4[j] = 0;
        }
        ((struct Player *)(object))->reservedWord1338 = -1;
        ((struct Player *)(object))->reservedWord12C4 = 0;
        ((struct Player *)(object))->reservedWord12C8 = 0;
        ((struct Player *)(object))->reservedWord1334 = 0;
        ((struct Player *)(object))->animationTable = g_playerActionStateHandlers;
        ((struct Player *)(object))->reservedWord11E8 = 0;
        Playerai_InitializeMovementAndAim(object);
        ((struct Player *)(object))->pickupEffectToggle = 0;
        ((struct Player *)(object))->pendingBonus = 0;
        ItemMenu_ResetEntries(&((Player *)object)->itemMenu);
        Player_ResetPlayerForRound(object, ((CPlayerOptions *)(entry))->character, force_active);
        List_RemoveIntrusive(&pool->m_FreeList, object);
        List_PrependIntrusive(&pool->m_ActiveList, object);
    }

initialized:
    state = &g_playerViewRenderContext.game.counters;
    ((PlayerPoolModeStateView *)(state))->fragTagMode = 1;
    ((PlayerPoolModeStateView *)(state))->ctfMode = 3;
}

void Player_ResetMenuPool(struct MenuPlayerPoolRecord *record) {
    XPlus_FillMemory(record, 0, 68);
    List_InitializeIntrusive(&record->m_FreeList, 5852, 5856);
    List_InitializeIntrusive(&record->m_ActiveList, 5852, 5856);
    record->m_pmePlayers = 0;
    record->m_Players = 0;
    record->word8 = 0;
    record->m_bEnteredAdonSaveLocation = 0;
    record->m_bAdonSaveLocationMenuEnabled = 0;
    record->m_TeamTriangleTimer = 0;
    record->m_TriangleSpin = 0;
}

void Player_RefreshActivePlayerSceneState(CPlayerPool *pool) {
    void *message;
    s32 floorPolygonResult;
    struct IntPair *model;
    struct IntPair *modelValue;
    Player *actor;
    if ((SetN64_IsModeThirteen() != 0) && (Control_IsSnapshotActive() != 0)) {
        Control_RestoreActorSnapshot();
        Control_DeactivateActorSnapshot();
    }
    actor = pool->m_ActiveList.head;
    if (actor != 0) {
        do {
            Player_InitActorHudState(actor);
            floorPolygonResult = Scene_FindFloorPolygon(&g_world, &actor->pos);
            actor->actorParts[1].model = floorPolygonResult;
            actor->actorParts[0].model = floorPolygonResult;
            Player_UpdatePlayerCamera(actor, actor);
            message = actor->camera;
            if (message != 0) {
                Cinema_UpdateSequenceTrack(message);
            }
            model = actor->definition;
            model->second = model->second & ~4;
            modelValue = actor->definition;
            modelValue->second = modelValue->second & ~4;
            actor = actor->next;
        } while (actor != 0);
    }
}
void Player_InitializePlayerFromRecord(char *player, s32 slot, PlayerSettingsRecordView *record) {
    s32 i;
    s32 computer;
    u8 team;

    computer = record->computer;
    ((Player *)player)->actorState = 0;
    ((Player *)player)->computer = computer;
    if (computer != 0) {
        ContPad_InitControllerInput((char *)&((SharedPlayer *)player)->views5E8.view688_33.body, g_botControllerProfile);
        ((Player *)player)->slot = record->slot;
    } else {
        ContPad_InitControllerInput((char *)&((SharedPlayer *)player)->views5E8.view688_33.body, &g_controllerProfiles[slot]);
        ((Player *)player)->slot = slot;
    }
    ((Player *)player)->profile = (void *)record;
    team = record->team;
    ((Player *)player)->firstHandle = 0;
    ((Player *)player)->secondHandle = 0;
    ((Player *)player)->model = 0;
    ((Player *)player)->reservedWord5F0 = 0;
    ((Player *)player)->reservedWord864 = 0;
    ((Player *)player)->reservedWord868 = 0;
    ((Player *)player)->actorParts[0].controller = player;
    player[3] = team;
    Scaled_InitPlayerState((s32)((Player *)player)->controller, player);
    ((Player *)player)->overkill = 0;
    ((Player *)player)->projectileBase = slot * 2;
    ((Player *)player)->projectileIndex = 0;
    ((Player *)player)->reactionFlags = 0;
    ((Player *)player)->reservedWord11CC = 0;
    ((Player *)player)->reservedWord1218 = 0;
    for (i = 0; i < 8; i++) {
        ((Player *)player)->reset12CC[i] = 0;
        ((Player *)player)->reset12F4[i] = 0;
    }
    ((Player *)player)->reservedWord1338 = -1;
    ((Player *)player)->reservedWord12C4 = 0;
    ((Player *)player)->reservedWord12C8 = 0;
    ((Player *)player)->reservedWord1334 = 0;
    ((Player *)player)->animationTable = g_playerActionStateHandlers;
    ((Player *)player)->reservedWord11E8 = 0;
    Playerai_InitializeMovementAndAim(player);
    ((Player *)player)->pickupEffectToggle = 0;
    ((Player *)player)->pendingBonus = 0;
    ItemMenu_ResetEntries(&((Player *)player)->itemMenu);
}

void Player_ActivatePlayerAtSpawn(struct PlayerSpawnActivationActor *actor, s32 character) {
    actor->part->active = 1;
    Player_ResetPlayerForRound(actor, character, 1);
    Actor_RequestActorState(&actor->firstEffect, &actor->secondEffect, 2);
    Player_PlacePlayerAtSpawnPoint(actor, g_gameSession.selector, 0, 1);
}

/* Releases the two handles at offsets 0x11BC and 0x11C0 of an object: each goes to SoundVoicePool_StopNode
   with what SoundVoicePool_GetGlobalState returns, and each is then cleared. */
void Player_ReleaseObjectHandles(struct ItemsHandleOwner *object) {
    SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), object->first);
    object->first = 0;
    SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), object->second);
    object->second = 0;
}

/* Stores the second argument at 0x5E0 of the actor, calls Playerai_InitializePlayerHealth and Player_ResetPlayerWeapons on it, then starts sound g_world_AchieveUpdateresultsscreen for it through Scene_ChangeInstanceModel with 0x66, g_fragTagModelId or its type's entry of g_characterModelIds chosen by the options g_gameSettings.local and g_resultExitPending. */
void Player_StartPlayerAnimation(Player *animatedPlayer, s32 animationState) {
    s32 modelResource;

    animatedPlayer->state = animationState;
    Playerai_InitializePlayerHealth(animatedPlayer);
    Player_ResetPlayerWeapons(animatedPlayer);
    if (g_gameSettings.local == 0) {
        modelResource = 102;
    } else if (g_resultExitPending != 0 && ((AiProfile *)animatedPlayer->profile)->bonus != 0) {
        modelResource = g_fragTagModelId;
    } else {
        modelResource = g_characterModelIds[((ActorDefinitionHeader *)animatedPlayer->definition)->character];
        animatedPlayer->playerId = ((AiProfile *)animatedPlayer->profile)->variant;
    }
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, animatedPlayer, modelResource, animatedPlayer->animation);
}
