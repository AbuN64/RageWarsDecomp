#include "COMMON/AIPROFILE.H"
#include "AI/CTEAMSELECT.H"
#include "AI/PLAYER/PLAYERAI_BUILDFORCEMARKERTRANSFORM.H"
#include "AI/PLAYER/PLAYER_RESETPLAYERFORROUND.H"
#include "ANIMPOOL/ANIMPOOL_SPAWNDESCRIBEDSCENEEFFECT.H"
#include "CBARREL/BARREL_SPAWNFLAGGEDEFFECTS.H"
#include "CTEAMSELECT/PLAYER_RESETPLAYERFORROUND_DATA.H"
#include "FRONTEND/PLAYER.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "GOBJINST/GOBJINST_FINDNEARESTBONEBOUNDS.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"
#include "PLACEPLAYERLIGHT/PLACEPLAYERLIGHT.H"
#include "PLAYERAI/PLAYERAI__PLAYERAI.H"
#include "PLAYER_UPDATEPLAYERCAMERA/PLAYER_UPDATEPLAYERCAMERA.H"
#include "POOLS/POOLS.H"
#include "RENDER/CONTROL_CYCLEACTORSNAPSHOTMODE.H"

#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/WORLD.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
#include "RENDER/PLAYER_SPAWN_PLACEMENT.H"
#include "ENGINE/CINEMA/CINEMA.H"
extern f32 g_respawnPlayerInitialPartScale;
#if defined(VERSION_US_REV1)
/* ROM offsets of the actor part tables: each version names its own copies. */
extern u8 g_Gobjinst_BuildActorTransformAddressUsRev1[];
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressUsRev1
extern u8 g_Playerai_ApplyRangedPitchToMatrixAddressUsRev1[];
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressUsRev1
extern u8 g_playerDamageReactionCallbackAddressUsRev1[];
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressUsRev1
extern u8 g_Playerai_ApplyLinkedProjectileStatusAddressUsRev1[];
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressUsRev1
extern u8 g_Player_DrawPlayerBodyAndWeaponAddressUsRev1[];
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressUsRev1
extern u8 g_Player_BuildWeaponHandTransformAddressUsRev1[];
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressUsRev1
#elif defined(VERSION_US)
extern u8 g_Gobjinst_BuildActorTransformAddressUs[];
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressUs
extern u8 g_Playerai_ApplyRangedPitchToMatrixAddressUs[];
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressUs
extern u8 g_playerDamageReactionCallbackAddressUs[];
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressUs
extern u8 g_Playerai_ApplyLinkedProjectileStatusAddressUs[];
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressUs
extern u8 g_Player_DrawPlayerBodyAndWeaponAddressUs[];
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressUs
extern u8 g_Player_BuildWeaponHandTransformAddressUs[];
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressUs
#elif defined(VERSION_DE)
extern u8 g_Gobjinst_BuildActorTransformAddressDe[];
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressDe
extern u8 g_Playerai_ApplyRangedPitchToMatrixAddressDe[];
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressDe
extern u8 g_playerDamageReactionCallbackAddressDe[];
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressDe
extern u8 g_Playerai_ApplyLinkedProjectileStatusAddressDe[];
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressDe
extern u8 g_Player_DrawPlayerBodyAndWeaponAddressDe[];
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressDe
extern u8 g_Player_BuildWeaponHandTransformAddressDe[];
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressDe
#elif defined(VERSION_EU)
extern u8 g_Gobjinst_BuildActorTransformAddressEu[];
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressEu
extern u8 g_Playerai_ApplyRangedPitchToMatrixAddressEu[];
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressEu
extern u8 g_playerDamageReactionCallbackAddressEu[];
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressEu
extern u8 g_Playerai_ApplyLinkedProjectileStatusAddressEu[];
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressEu
extern u8 g_Player_DrawPlayerBodyAndWeaponAddressEu[];
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressEu
extern u8 g_Player_BuildWeaponHandTransformAddressEu[];
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressEu
#elif defined(VERSION_EU_X)
extern u8 g_Gobjinst_BuildActorTransformAddressEuX[];
#define ACTORPART_T28C g_Gobjinst_BuildActorTransformAddressEuX
extern u8 g_Playerai_ApplyRangedPitchToMatrixAddressEuX[];
#define ACTORPART_T290 g_Playerai_ApplyRangedPitchToMatrixAddressEuX
extern u8 g_playerDamageReactionCallbackAddressEuX[];
#define ACTORPART_T280 g_playerDamageReactionCallbackAddressEuX
extern u8 g_Playerai_ApplyLinkedProjectileStatusAddressEuX[];
#define ACTORPART_T288 g_Playerai_ApplyLinkedProjectileStatusAddressEuX
extern u8 g_Player_DrawPlayerBodyAndWeaponAddressEuX[];
#define ACTORPART_ACTION g_Player_DrawPlayerBodyAndWeaponAddressEuX
extern u8 g_Player_BuildWeaponHandTransformAddressEuX[];
#define ACTORPART_PART1_T28C g_Player_BuildWeaponHandTransformAddressEuX
#endif

extern void Actor_RequestActorState(void *, void *, s32);
extern void Weaponai_ApplyWeaponSwitch(void *, void *);

#include "MENU/INITVIEW.H"
#include "ACHIEVE/ACHIEVE.H"
/* Initialises an actor and its embedded part at 0x2E8: sets the shared table pointers and flag bits (one flag
 * depends on g_frontendScreenStatus.settings.local), runs the part setup calls, then copies the view's position into the actor. */
void Player_InitActorParts(SharedPlayer *player, LevelPlacedActorRecord *rec, s32 mode, s32 index) {
    char *actor = (char *)player;
    Player *record = (Player *)player;
    u32 flags;
    u32 t1, t2, t3;
    InitView *view;
    record->actorParts[0].controller = actor;
    Gobjinst_InitializePlacedActor(actor, rec, (void *)mode, 0);
    record->actorParts[0].controller = actor;
    t1 = record->actorParts[0].flags | 0x100000;
    t2 = t1 | 0x10000;
    t3 = t2 | 0x1000000;
    flags = t3 | 0x2000000;
    record->actorParts[0].flags = flags;
    if (g_frontendScreenStatus.settings.local == 0) {
        record->actorParts[0].flags = flags | 0x10000000;
    }
    record->actorParts[0].controllerUpdate = ACTORPART_T28C;
    record->actorParts[0].table290 = ACTORPART_T290;
    record->actorParts[0].table280 = ACTORPART_T280;
    record->actorParts[0].table288 = ACTORPART_T288;
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
    record->actorParts[1].table288 = ACTORPART_T288;
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
#define FIELD(type, base, off) (*(type *)((char *)(base) + (off)))
extern char g_localPlayerProfiles[];
extern void *g_currentStagePreset;
extern char g_roundStartModeSpecificDialogTable[], g_playerMenuDialogTable[], g_roundStartDefaultDialogTable[];
struct RespawnPlayer;
extern s32 Control_IsSnapshotActive(void);



extern u32 Player_GetLevelProgress(void *, s32);



/* Resets a player/actor record for a new run: marks it active, stores the character, picks up the HUD
 * object, clears the per-slot counters and weapon tables, selects the start mode from the multiplayer setting
 * and zeroes the per-player entries of the two global tables. */
extern u8 g_gameControllerMode; /* MIXED Player_ResetPlayerForRound */
void Player_ResetPlayerForRound(void *actor, s32 character) {
    s32 i;
    unsigned long counterAddress;
    unsigned long counterAddress2;
    s32 openFlag = 0;
    char *globals;
    Control_IsSnapshotActive();
    FIELD(s32, actor, 1488) = 1;
    FIELD(s32, actor, 1504) = character;
    if (FIELD(s32, actor, 5200) == 0) {
        FIELD(void *, actor, 1500) = Pools_RecycleModel(&g_frontendScreenStatus);
        if (FIELD(s32, &g_frontendScreenStatus, 6340) != 0) {
            FIELD(s32, actor, 5200) = 1;
        }
    } else {
        FIELD(s32, actor, 1500) = 0;
    }
    TeamSelect_ResetWeaponWheel((char *)&((SharedPlayer *)actor)->views5E8.view938_128.strokes);
    TeamSelect_ResetTeamWheel((char *)&((SharedPlayer *)actor)->views5E8.viewCCC_164.teamWheel);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    for (i = 1; i < 22; i++) {
        FIELD(u8, actor, 1538 + i * 2) = 0;
        FIELD(s8, actor, 1539 + i * 2) = -1;
    }
    FIELD(u8, actor, 1538) = 1;
    FIELD(u8, actor, 1539) = 0;
    FIELD(u8, actor, 1545) = 2;
    FIELD(u8, actor, 1546) = 1;
    FIELD(u8, actor, 1547) = 1;
    FIELD(u8, actor, 1544) = 1;
    FIELD(u8, actor, 1558) = 1;
    FIELD(u8, actor, 1542) = 1;
    FIELD(u8, actor, 1559) = 4;
    FIELD(u8, actor, 1543) = 5;
    FIELD(u8, actor, 1566) = 1;
    FIELD(u8, actor, 1567) = 6;
#endif
    FIELD(s16, actor, 1512) = 0;
    i = 5;
    counterAddress = (unsigned long)actor + i;
    do {
        *(u8 *)(counterAddress + ((char *)&((Shared_ActorView *)0)->eventCounters[0] - (char *)0)) = 0;
        counterAddress--;
    } while (--i >= 0);
    i = 5;
    counterAddress2 = (unsigned long)actor + i;
    do {
        *(u8 *)(counterAddress2 + ((char *)&((Shared_ActorView *)0)->eventCounters[1] - (char *)0)) = 0;
        counterAddress2--;
    } while (--i >= 0);
    if (g_frontendScreenStatus.settings.local != 0) {
        if (g_gameControllerMode == 1 && FIELD(s32, actor, 5200) == 0) {
            u32 value = Player_GetLevelProgress(g_localPlayerProfiles + FIELD(s32, actor, 1492) * sizeof(Profile), FIELD(s8, FIELD(void *, actor, 1496), 128));
            FIELD(s32, actor, 4924) = ((value & 0xFF) >> 1) + 1;
        }
        if (g_gameControllerMode == 4 && FIELD(s32, actor, 5200) == 0 && g_currentStagePreset != 0) {
            FIELD(s32, actor, 4924) = FIELD(u8, g_currentStagePreset, 40);
        }
        FIELD(s16, actor, 1514) = 1;
    } else {
        FIELD(s16, actor, 1514) = 3;
    }
    FIELD(s32, actor, 5064) = 0;
    Player_ResetPlayerWeapons((struct RespawnPlayer *)actor);
    FIELD(s32, actor, 1648) = 0;
    FIELD(s32, actor, 1652) = 0;
    FIELD(s32, actor, 2156) = -1;
    FIELD(s32, actor, 2160) = -1;
    for (i = 0; i < 8; i++) {
        ((Player *)actor)->profile->roundCounts[2][i] = 0;
        ((Player *)actor)->profile->roundCounts[3][i] = 0;
        ((Player *)actor)->profile->roundCounts[0][i] = 0;
        ((Player *)actor)->profile->roundCounts[1][i] = 0;
    }
    FIELD(s16, FIELD(void *, actor, 1496), 0) = 0;
    FIELD(s16, FIELD(void *, actor, 1496), 2) = 0;
    FIELD(s16, FIELD(void *, actor, 1496), 4) = 0;
    FIELD(s16, FIELD(void *, actor, 1496), 6) = 0;
    FIELD(s16, FIELD(void *, actor, 1496), 10) = 0;
    FIELD(s16, FIELD(void *, actor, 1496), 8) = 0;
    FIELD(u8, FIELD(void *, actor, 1496), 141) = 0;
    FIELD(u8, FIELD(void *, actor, 1496), 142) = 0;
    FIELD(u8, FIELD(void *, actor, 1496), 143) = 0;
    FIELD(u8, FIELD(void *, actor, 1496), 144) = 0;
    FIELD(s32, actor, 1592) = 0;
    FIELD(s32, actor, 1596) = 1;
    FIELD(s32, actor, 1600) = 0;
    FIELD(s32, actor, 2152) = 1;
    Player_ResetRespawnedPlayer((struct RespawnPlayer *)actor);
    globals = (char *)&g_gameSettings;
    if (FIELD(u8, globals, 29) != 0) {
        FIELD(s32, actor, 5096) = 0;
    }
    if (openFlag != 0) {
        char *table;
        if (FIELD(u8, globals, 29) != 0) {
            FIELD(u8, FIELD(void *, actor, 1496), 128) = 0;
            FIELD(s32, actor, 1504) = 0;
            FIELD(s32, actor, 2140) = 1;
            table = g_roundStartModeSpecificDialogTable;
            if (FIELD(s32, globals, 1532) == 0) {
                table = g_playerMenuDialogTable;
            }
        } else {
            table = g_roundStartDefaultDialogTable;
        }
        Menu_OpenDialog((char *)&((GameplayCamera *)FIELD(void *, actor, 1500))->messageList, table, actor, FIELD(s32, actor, 1688), FIELD(s32, actor, 1492));
    }
    g_playerHitCounts[FIELD(s32, actor, 1492)] = 0;
    g_playerCountedShots[FIELD(s32, actor, 1492)] = 0;

}
#ifndef FIELD
#define FIELD(type, base, off) (*(type *)((char *)(base) + (off)))
#endif


extern u32 g_activeActorKind;
extern void Playerai_LoadActorModel(void *actor);
extern void Playerai_UpdateCharacterModel(void *);

extern void Link_DispatchObjectLinks(void *, s32, void *);
/* Prepares an actor's per-run HUD state: runs the mode-specific setup when the session byte is set, resets
 * the record at 0x878 to its defaults, lays out the nine on-screen widgets at 0xE2C..0x10C0 (position, then
 * their string tables), the two score fields and the 0x10FC panel, and copies the parent's four-word block. */
typedef struct { s32 a, b, c, d; } HudQuad;
void Player_InitActorHudState(SharedPlayer *actor) {
    char *session = (char *)&g_gameSettings;
    char *hud;
    char *widget;
    s32 enabled;
    if (FIELD(u8, session, 29) != 0) {
        Playerai_LoadActorModel(actor);
        Playerai_UpdateCharacterModel(actor);
        if (FIELD(u8, FIELD(void *, actor, 1496), 145) == 0 && FIELD(u8, session, 13) == 1) {
            Achieve_ApplyProfileWeaponUnlocks(actor);
        }
    }
    hud = (char *)&actor->views5E8.view878_158.effect;
    FIELD(s32, hud, 180) = 0;
    FIELD(s32, hud, 8) = 0;
    FIELD(s32, hud, 184) = 0;
    FIELD(s32, hud, 4) = -1;
    FIELD(s32, actor, 2168) = -1;
    FIELD(s32, hud, 168) = 0;
    FIELD(s32, hud, 156) = 0;
    FIELD(s32, hud, 164) = 0;
    FIELD(f32, hud, 172) = 437.5f;
    FIELD(f32, hud, 176) = (-675.0f);
    FIELD(f32, hud, 144) = 0.25f;
    FIELD(f32, hud, 148) = 0.1875f;
    FIELD(f32, hud, 152) = 0.25f;
    FIELD(f32, hud, 160) = 1.5707965f;
    FIELD(s32, actor, 4528) = 0;
    Control_SetProfileMode((void *)FIELD(s32, actor, 1688), 1);
    FIELD(s32, actor, 1656) = 0;
    FIELD(s32, actor, 1660) = 0;
    FIELD(s32, actor, 1664) = 0;
    FIELD(s32, actor, 1668) = 0;
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[0];
    OnScreen_InitMover(widget, 120, 96);
    OnScreen_StartMoverScript(widget, g_hudStatusWidgetMoverScriptOne);
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[1];
    OnScreen_InitMover(widget, 190, 96);
    OnScreen_StartMoverScript(widget, g_hudStatusWidgetMoverScriptTwo);
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[2];
    OnScreen_InitMover(widget, 260, 96);
    OnScreen_StartMoverScript(widget, g_hudStatusWidgetMoverScriptThree);
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[3];
    OnScreen_InitMover(widget, 28, 96);
    OnScreen_StartMoverScript(widget, g_hudStatusWidgetMoverScriptFour);
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[4];
    OnScreen_InitMover(widget, -64, 16);
    OnScreen_StartMoverScript(widget, g_hudLivesInitialMoverScript);
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[5];
    OnScreen_InitMover(widget, 40, 16);
    OnScreen_StartMoverScript(widget, k_PlaceplayerlightEncodedWords);
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[9];
    OnScreen_InitMover(widget, -82, 16);
    OnScreen_StartMoverScript(widget, g_hudScoreInitialMoverScript);
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[10];
    FIELD(f32, actor, 4220) = 255.0f;
    OnScreen_InitMover(widget, -82, 68);
    OnScreen_StartMoverScript(widget, g_hudCountInitialMoverScript);
    widget = (char *)&((Shared_ActorView *)actor)->hudMovers[11];
    OnScreen_InitMover(widget, -82, 68);
    OnScreen_StartMoverScript(widget, g_hudSquadInitialMoverScript);
    OnScreen_InitMover((char *)&((Shared_ActorView *)actor)->hudMovers[7], 24, (s16)((u16)g_hudReferenceViewportHeight + 96));
    OnScreen_InitMover((char *)&((Shared_ActorView *)actor)->hudMovers[8], 24, (s16)((u16)g_hudReferenceViewportHeight + 96));
    OnScreen_InitMover((char *)&((Shared_ActorView *)actor)->hudMovers[12], 100, 100);
    FIELD(s32, actor, 4548) = 0;
    FIELD(s32, actor, 1980) = 0;
    FIELD(s32, actor, 4404) = FIELD(s32, actor, 1508);
    if (FIELD(void *, actor, 1500) != 0) {
        *(HudQuad *)(&((Shared_ActorView *)actor)->cameraOrientation) = *(HudQuad *)(&((GameplayCamera *)FIELD(void *, actor, 1500))->orientation);
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
        FIELD(s32, actor, 1516) = g_activeActorKind;
    }
    FIELD(s32, actor, 4648) = 0;
    FIELD(s32, actor, 4644) = 0;
    Cinema_ClearPlaybackFlag();
    if (FIELD(void *, actor, 20) != 0) {
        Link_DispatchObjectLinks(FIELD(void *, actor, 20), 1, actor);
    }
    Cinema_SetPlaybackFlag();
}
#include "TYPES.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "COMMON/LEVEL_ACTOR.H"
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
    int reservedWordI;
    char pad13E8[0x1450 - 0x13E8];
    int isBot;
    void *brain;
} RespawnPlayer;
static inline int isOnline(void) {
    return g_frontendScreenStatus.settings.local;
}
extern unsigned int g_gameLoopFrameCount;


extern void Playerai_InitializePlayerHealth(struct RespawnPlayer *);
extern int SetN64_IsModeThirteen(void);



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
    player->reservedWordI = 0;
    player->reservedWordF = 0;
    if (SetN64_IsModeThirteen() != 0 && g_frontendScreenStatus.settings.local == 0 && g_gameLoopFrameCount > 10 && player->state < 11) {
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
