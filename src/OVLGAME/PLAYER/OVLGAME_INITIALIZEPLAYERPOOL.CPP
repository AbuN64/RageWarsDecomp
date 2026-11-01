#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "COMMON/VECTOR4F.H"
#include "MENU/ITEMS/GAME_AND_PLAYER_OPTIONS.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "COMMON/GAME_SESSION.H"
#include "OVLGAME/OVLGAME_INITIALIZEPLAYERPOOL.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/WORLD.H"
#include "COMMON/S1.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AI/NAV/SCALED_INITPLAYERSTATE.H"
#include "RENDER/PLAYER_SPAWN_PLACEMENT.H"
#include "FX/CONTPAD_INITCONTROLLERINPUT.H"
#include "UI/X_FILES/X_PLUS.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "ENGINE/CINEMA/CINEMA.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

extern char g_controllerProfiles[];



extern char g_matchRoundCounters[];

extern void Cache_DrainAndCompactResources(s32);


extern void Player_AllocPlayerList(CPlayerPool *, s32);
extern s32 g_playerActionStateHandlers[];
extern void Player_ResetPlayerForRound(void *actor, s32 character, s32 active);



/* Resets a 0x44-byte record: clears it through XPlus_FillMemory, initialises the two lists at offsets
   0xC and 0x20 through List_InitializeIntrusive with 0x16DC and 0x16E0, and clears the words at 0 to 8 and
   0x34 to 0x40. */

/* Refreshes every instance owned by the holder and clears their pending flag. */



void Player_UpdatePlayerCamera(Shared_ActorView *, Shared_ActorView *);

                 /* extern */

                            /* extern */

                            /* extern */
                           /* extern */
                           /* extern */
                    /* extern */
s32 SetN64_IsModeThirteen(void);

                            /* extern */
void Player_InitActorHudState(Shared_ActorView *);

/* Sets the byte at offset 0x78 of the object at 0x5D8 of an actor, calls Player_ResetPlayerForRound with the
   actor, its second argument and one, then Actor_RequestActorState_Damageai on offsets 0x2E8 and 0x458 with two and
   Player_PlacePlayerAtSpawnPoint with g_playerSpawnSelector, zero and one. */







void Player_InitializePlayerPool(CPlayerPool *pool, s32 count, s32 force_active) {
    extern void ItemMenu_ResetEntries(CItemMenu *);
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
            ((struct Shared_ActorView *)(object))->remote = ((CPlayerOptions *)(entry))->isBot;
            ((struct Shared_ActorView *)(object))->actorState = 0;
            if (((struct Shared_ActorView *)(object))->remote != 0) {
                ContPad_InitControllerInput((char *)&((SharedPlayer *)object)->views5E8.view688_33.body, g_botControllerProfile);
                ((struct Shared_ActorView *)(object))->mode = ((CPlayerOptions *)(entry))->controller;
            } else {
                ContPad_InitControllerInput((char *)&((SharedPlayer *)object)->views5E8.view688_33.body, g_controllerProfiles + attribute_offset);
                ((struct Shared_ActorView *)(object))->mode = i;
            }
            owner = ((struct Shared_ActorView *)(object))->owner;
            ((struct Shared_ActorView *)(object))->controls = (Shared_ControlView *)entry;
            object_id = ((CPlayerOptions *)(entry))->characterSkin;
            ((struct Shared_ActorView *)(object))->weaponSoundHandle = 0;
            ((struct Shared_ActorView *)(object))->weaponLoopSoundHandle = 0;
            ((struct Shared_ActorView *)(object))->spawn = 0;
            ((struct Shared_ActorView *)(object))->reservedWord5F0 = 0;
            ((struct Shared_ActorView *)(object))->reservedWord864 = 0;
            ((struct Shared_ActorView *)(object))->reservedWord868 = 0;
            ((struct Shared_ActorView *)(object))->self = object;
            ((struct Shared_ActorView *)(object))->id = object_id;
            Scaled_InitPlayerState(owner, object);
            ((struct Shared_ActorView *)(object))->special = 0;
            ((struct Shared_ActorView *)(object))->projectileBase = player_index;
            ((struct Shared_ActorView *)(object))->projectileIndex = 0;
            ((struct Shared_ActorView *)(object))->impulseFlags = 0;
            ((struct Shared_ActorView *)(object))->reservedWord11CC = 0;
            ((struct Shared_ActorView *)(object))->reservedWord1218 = 0;
            for (j = 0; j < 8; j++) {
                ((Shared_ActorView *)object)->reset12CC[j] = 0;
                ((Shared_ActorView *)object)->reset12F4[j] = 0;
            }
            ((struct Shared_ActorView *)(object))->reservedWord1338 = -1;
            ((struct Shared_ActorView *)(object))->reservedWord12C4 = 0;
            ((struct Shared_ActorView *)(object))->reservedWord12C8 = 0;
            ((struct Shared_ActorView *)(object))->reservedWord1334 = 0;
            ((struct Shared_ActorView *)(object))->animationStateTable = g_playerActionStateHandlers;
            ((struct Shared_ActorView *)(object))->reservedWord11E8 = 0;
            Playerai_InitializeMovementAndAim(object);
            ((struct Shared_ActorView *)(object))->pickupEffectToggle = 0;
            ((struct Shared_ActorView *)(object))->reservedHalf16D8 = 0;
            ItemMenu_ResetEntries(&((Shared_ActorView *)object)->record);
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
        ((struct Shared_ActorView *)(object))->remote = ((CPlayerOptions *)(entry))->isBot;
        ((struct Shared_ActorView *)(object))->actorState = 0;
        if (((struct Shared_ActorView *)(object))->remote != 0) {
            ContPad_InitControllerInput((char *)&((SharedPlayer *)object)->views5E8.view688_33.body, g_botControllerProfile);
            ((struct Shared_ActorView *)(object))->mode = ((CPlayerOptions *)(entry))->controller;
        } else {
            ContPad_InitControllerInput((char *)&((SharedPlayer *)object)->views5E8.view688_33.body, g_controllerProfiles + roster_index * sizeof(ControllerProfile));
            ((struct Shared_ActorView *)(object))->mode = roster_index;
        }
        owner = ((struct Shared_ActorView *)(object))->owner;
        ((struct Shared_ActorView *)(object))->controls = (Shared_ControlView *)entry;
        object_id = ((CPlayerOptions *)(entry))->characterSkin;
        ((struct Shared_ActorView *)(object))->weaponSoundHandle = 0;
        ((struct Shared_ActorView *)(object))->weaponLoopSoundHandle = 0;
        ((struct Shared_ActorView *)(object))->spawn = 0;
        ((struct Shared_ActorView *)(object))->reservedWord5F0 = 0;
        ((struct Shared_ActorView *)(object))->reservedWord864 = 0;
        ((struct Shared_ActorView *)(object))->reservedWord868 = 0;
        ((struct Shared_ActorView *)(object))->self = object;
        ((struct Shared_ActorView *)(object))->id = object_id;
        Scaled_InitPlayerState(owner, object);
        ((struct Shared_ActorView *)(object))->special = 0;
        ((struct Shared_ActorView *)(object))->projectileBase = roster_index * 2;
        ((struct Shared_ActorView *)(object))->projectileIndex = 0;
        ((struct Shared_ActorView *)(object))->impulseFlags = 0;
        ((struct Shared_ActorView *)(object))->reservedWord11CC = 0;
        ((struct Shared_ActorView *)(object))->reservedWord1218 = 0;
        for (j = 0; j < 8; j++) {
            ((Shared_ActorView *)object)->reset12CC[j] = 0;
            ((Shared_ActorView *)object)->reset12F4[j] = 0;
        }
        ((struct Shared_ActorView *)(object))->reservedWord1338 = -1;
        ((struct Shared_ActorView *)(object))->reservedWord12C4 = 0;
        ((struct Shared_ActorView *)(object))->reservedWord12C8 = 0;
        ((struct Shared_ActorView *)(object))->reservedWord1334 = 0;
        ((struct Shared_ActorView *)(object))->animationStateTable = g_playerActionStateHandlers;
        ((struct Shared_ActorView *)(object))->reservedWord11E8 = 0;
        Playerai_InitializeMovementAndAim(object);
        ((struct Shared_ActorView *)(object))->pickupEffectToggle = 0;
        ((struct Shared_ActorView *)(object))->reservedHalf16D8 = 0;
        ItemMenu_ResetEntries(&((Shared_ActorView *)object)->record);
        Player_ResetPlayerForRound(object, ((CPlayerOptions *)(entry))->character, force_active);
        List_RemoveIntrusive(&pool->m_FreeList, object);
        List_PrependIntrusive(&pool->m_ActiveList, object);
    }

initialized:
    state = g_matchRoundCounters;
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

                         /* extern */

void Player_RefreshActivePlayerSceneState(CPlayerPool *pool) {
    void *message;
    s32 floorPolygonResult;
    struct IntPair *model;
    struct IntPair *modelValue;
    Shared_ActorView *actor;
    if ((SetN64_IsModeThirteen() != 0) && (Control_IsSnapshotActive() != 0)) {
        Control_RestoreActorSnapshot();
        Control_DeactivateActorSnapshot();
    }
    actor = pool->m_ActiveList.head;
    if (actor != 0) {
        do {
            Player_InitActorHudState(actor);
            floorPolygonResult = Scene_FindFloorPolygon(&g_world, &actor->position);
            actor->weapon.model = floorPolygonResult;
            actor->modelId = floorPolygonResult;
            Player_UpdatePlayerCamera(actor, actor);
            message = actor->message;
            if (message != 0) {
                Cinema_UpdateSequenceTrack(message);
            }
            model = actor->model;
            model->second = model->second & ~4;
            modelValue = actor->model;
            modelValue->second = modelValue->second & ~4;
            actor = actor->next;
        } while (actor != 0);
    }
}
void Player_InitializePlayerFromRecord(char *player, s32 slot, PlayerSettingsRecordView *record) {
    extern void ItemMenu_ResetEntries(CItemMenu *);
    s32 i;
    s32 computer;
    u8 team;

    computer = record->computer;
    ((Shared_ActorView *)player)->actorState = 0;
    ((Shared_ActorView *)player)->remote = computer;
    if (computer != 0) {
        ContPad_InitControllerInput((char *)&((SharedPlayer *)player)->views5E8.view688_33.body, g_botControllerProfile);
        ((Shared_ActorView *)player)->mode = record->slot;
    } else {
        ContPad_InitControllerInput((char *)&((SharedPlayer *)player)->views5E8.view688_33.body, g_controllerProfiles + slot * sizeof(ControllerProfile));
        ((Shared_ActorView *)player)->mode = slot;
    }
    ((Shared_ActorView *)player)->controls = (void *)record;
    team = record->team;
    ((Shared_ActorView *)player)->weaponSoundHandle = 0;
    ((Shared_ActorView *)player)->weaponLoopSoundHandle = 0;
    ((Shared_ActorView *)player)->spawn = 0;
    ((Shared_ActorView *)player)->reservedWord5F0 = 0;
    ((Shared_ActorView *)player)->reservedWord864 = 0;
    ((Shared_ActorView *)player)->reservedWord868 = 0;
    ((Shared_ActorView *)player)->self = player;
    player[3] = team;
    Scaled_InitPlayerState((s32)((Shared_ActorView *)player)->owner, player);
    ((Shared_ActorView *)player)->special = 0;
    ((Shared_ActorView *)player)->projectileBase = slot * 2;
    ((Shared_ActorView *)player)->projectileIndex = 0;
    ((Shared_ActorView *)player)->impulseFlags = 0;
    ((Shared_ActorView *)player)->reservedWord11CC = 0;
    ((Shared_ActorView *)player)->reservedWord1218 = 0;
    for (i = 0; i < 8; i++) {
        ((Shared_ActorView *)player)->reset12CC[i] = 0;
        ((Shared_ActorView *)player)->reset12F4[i] = 0;
    }
    ((Shared_ActorView *)player)->reservedWord1338 = -1;
    ((Shared_ActorView *)player)->reservedWord12C4 = 0;
    ((Shared_ActorView *)player)->reservedWord12C8 = 0;
    ((Shared_ActorView *)player)->reservedWord1334 = 0;
    ((Shared_ActorView *)player)->animationStateTable = g_playerActionStateHandlers;
    ((Shared_ActorView *)player)->reservedWord11E8 = 0;
    Playerai_InitializeMovementAndAim(player);
    ((Shared_ActorView *)player)->pickupEffectToggle = 0;
    ((Shared_ActorView *)player)->reservedHalf16D8 = 0;
    ItemMenu_ResetEntries(&((Shared_ActorView *)player)->record);
}

void Player_ActivatePlayerAtSpawn(struct PlayerSpawnActivationActor *actor, s32 character) {
    actor->part->active = 1;
    Player_ResetPlayerForRound(actor, character, 1);
    Actor_RequestActorState(&actor->firstEffect, &actor->secondEffect, 2);
    Player_PlacePlayerAtSpawnPoint(actor, g_gameSession.selector, 0, 1);
}
