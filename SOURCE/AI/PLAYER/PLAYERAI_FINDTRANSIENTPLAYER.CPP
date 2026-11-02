#include "COMMON/OBJRECV5.H"
#include <PR/abi.h>
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AI/PLAYER/PLAYER_MODEL_AND_HELD_WEAPON_RENDERING.H"

/* Draws the marker over a player that is alive at 0x5E4: loads the player's matrix from its table at
   0x1640 (the first entry while Tsmos_IsFrontendActive reports a shared view, otherwise the entry for the current
   view g_lightingBufferIndex), sets the render and geometry modes, fills the five vertices of a green pyramid in
   g_playerAimMarkerVertices and emits them with its four triangles. Adapted from Player_DrawRedMarkerPrism with the pyramid, the
   colour and the matrix selection changed. */
extern s32 g_lightingBufferIndex;


extern Gfx *g_displayListCursor;

extern s32 Tsmos_IsFrontendActive(void);


extern s32 Geometry_SetModePreset(s32);

extern void Geometry_SetCombineMode(u32);

/* Scales damage by ownership and player state and suppresses friendly damage when configured. */



extern f32 g_playerDamageFixedPointScale, g_playerDamageBaseScale, g_playerDamageDifficultyScale, g_playerDamagePrimaryFixedPointScale, g_playerDamagePrimaryModeScale, g_playerDamageSecondaryFixedPointScale, g_playerDamageSecondaryModeScale, g_playerDamageAndDistanceConstants;


extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);

extern void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState);



extern s32 InstHdr_CanActorReceiveInteraction(void *actor);




#if defined(VERSION_US_REV1)
#endif

extern void Gsky_LoadProjectionMatrix(void *cameraAddress);

extern void Player_DrawHeadsUpDisplay(void *player, void *view);


extern void Player_DrawMatchCountdown(void *, void *);

/* Returns the leading team: for each player in the list from 0x20 it adds the player's kills of the
   seven other players (the shorts at 0x3C of its stats at 0x5D8) to the total of its team byte at
   0x92, returning 0 at once for a player without a team (0xFF), then returns the first team 0 to 4
   with the highest total. */
s32 Playerai_FindHighestScoringPlayerIndex(struct CPlayerPool_t *game) {
    s32 total0;
    s32 total1;
    s32 total2;
    s32 total3;
    s32 total4;
    char *player;
    char *stats;
    s32 self;
    s32 other;
    s32 best;
    s32 leader;

    total4 = 0;
    total3 = 0;
    total2 = 0;
    total1 = 0;
    total0 = 0;
    for (player = game->m_ActiveList.head; player != 0; player = (char *)((struct Shared_ActorView *)(player))->next) {
        self = (u32) (player - game->m_Players) / 5864;
        for (other = 0; other < 8; other++) {
            if (other == self) {
                continue;
            }
            stats = (char *)((struct Shared_ActorView *)(player))->controls;
            switch (((Record *)(stats))->team) {
            case 0xFF:
                return 0;
            case 0:
                total0 += ((Stats *) stats)->kills[other];
                break;
            case 1:
                total1 += ((Stats *) stats)->kills[other];
                break;
            case 2:
                total2 += ((Stats *) stats)->kills[other];
                break;
            case 3:
                total3 += ((Stats *) stats)->kills[other];
                break;
            case 4:
                total4 += ((Stats *) stats)->kills[other];
                break;
            }
        }
    }
    do {
        best = leader = -1;
    } while (0);
    if (best < total0) {
        best = total0;
        leader = 0;
    }
    if (best < total1) {
        best = total1;
        leader = 1;
    }
    if (best < total2) {
        best = total2;
        leader = 2;
    }
    if (best < total3) {
        best = total3;
        leader = 3;
    }
    if (best < total4) {
        best = total4;
        leader = 4;
    }
    return leader;
}

/** Return the animation-table offset selected by the actor state. */
s32 Playerai_SelectCharacterSound(struct Shared_ActorView *player, s32 baseSoundId) {
    s32 *types = &g_fragTagModelId;
    u16 type = player->kind;
    char *state;
    s32 offset;

    if (type == types[0]) {
        switch (g_gameSettings.counters.m_nFragTagSkin) {
        case 0:
            offset = 1300;
            break;
        case 1:
            offset = 1500;
            break;
        case 2:
            offset = 1400;
            break;
        default:
            g_gameSettings.counters.m_nFragTagSkin = 0;
            offset = 1300;
            break;
        }
    } else if (type == types[-2]) {
        offset = 400;
    } else if (type == types[-1]) {
        offset = 1000;
    } else {
        state = (char *)player->controls;
        switch (((struct Shared_ControlView *)(state))->mode) {
        default:
            ((struct Shared_ControlView *)(state))->mode = 0;
        case 0:
            offset = 0;
            break;
        case 1:
            offset = 1100;
            break;
        case 2:
            offset = 200;
            break;
        case 3:
            offset = 300;
            break;
        case 4:
            offset = 1200;
            break;
        case 5:
            offset = 100;
            break;
        case 6:
            offset = 600;
            break;
        case 7:
            offset = 900;
            break;
        case 8:
            offset = 800;
            break;
        case 9:
        case 15:
            offset = 700;
            break;
        case 10:
            offset = 500;
            break;
        case 11:
            offset = 1600;
            break;
        case 12:
            offset = 1700;
            break;
        case 13:
        case 16:
            offset = 1800;
            break;
        case 14:
            offset = 1900;
            break;
        }
    }
    return baseSoundId + offset;
}

void Playerai_DrawAimMarker(Player16C0 *player) {
    s32 green;
    s32 alpha;

    if (player->alive != 0) {
        if (Tsmos_IsFrontendActive() != 0) {
            gSPMatrix(g_displayListCursor++, (u32) &player->markers[0], G_MTX_LOAD);
        } else {
            gSPMatrix(g_displayListCursor++, (u32) &player->markers[g_lightingBufferIndex], G_MTX_LOAD);
        }
        gDPPipeSync(g_displayListCursor++);
        Geometry_InvalidateMaterialKeys();
        Geometry_SetModePreset(14);
        Geometry_SetCombineMode(28);
        green = 200;
        alpha = 150;
        gSPGeometryMode(g_displayListCursor++, G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | 0x80, 0);
        gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_SHADING_SMOOTH);
        g_playerAimMarkerVertices[0].x = 0;
        g_playerAimMarkerVertices[0].y = 0;
        g_playerAimMarkerVertices[0].z = 0;
        g_playerAimMarkerVertices[0].flag = 0;
        g_playerAimMarkerVertices[0].s = 0;
        g_playerAimMarkerVertices[0].t = 0;
        g_playerAimMarkerVertices[0].r = 0;
        g_playerAimMarkerVertices[0].g = green;
        g_playerAimMarkerVertices[0].b = 0;
        g_playerAimMarkerVertices[0].a = alpha;
        g_playerAimMarkerVertices[1].x = 20;
        g_playerAimMarkerVertices[1].y = 40;
        g_playerAimMarkerVertices[1].z = 20;
        g_playerAimMarkerVertices[1].flag = 0;
        g_playerAimMarkerVertices[1].s = 0;
        g_playerAimMarkerVertices[1].t = 0;
        g_playerAimMarkerVertices[1].r = 0;
        g_playerAimMarkerVertices[1].g = green;
        g_playerAimMarkerVertices[1].b = 0;
        g_playerAimMarkerVertices[1].a = alpha;
        g_playerAimMarkerVertices[2].x = -20;
        g_playerAimMarkerVertices[2].y = 40;
        g_playerAimMarkerVertices[2].z = 20;
        g_playerAimMarkerVertices[2].flag = 0;
        g_playerAimMarkerVertices[2].s = 0;
        g_playerAimMarkerVertices[2].t = 0;
        g_playerAimMarkerVertices[2].r = 0;
        g_playerAimMarkerVertices[2].g = green;
        g_playerAimMarkerVertices[2].b = 0;
        g_playerAimMarkerVertices[2].a = alpha;
        g_playerAimMarkerVertices[3].x = -20;
        g_playerAimMarkerVertices[3].y = 40;
        g_playerAimMarkerVertices[3].z = -20;
        g_playerAimMarkerVertices[3].flag = 0;
        g_playerAimMarkerVertices[3].s = 0;
        g_playerAimMarkerVertices[3].t = 0;
        g_playerAimMarkerVertices[3].r = 0;
        g_playerAimMarkerVertices[3].g = green;
        g_playerAimMarkerVertices[3].b = 0;
        g_playerAimMarkerVertices[3].a = alpha;
        g_playerAimMarkerVertices[4].x = 20;
        g_playerAimMarkerVertices[4].y = 40;
        g_playerAimMarkerVertices[4].z = -20;
        g_playerAimMarkerVertices[4].flag = 0;
        g_playerAimMarkerVertices[4].s = 0;
        g_playerAimMarkerVertices[4].t = 0;
        g_playerAimMarkerVertices[4].r = 0;
        g_playerAimMarkerVertices[4].g = green;
        g_playerAimMarkerVertices[4].b = 0;
        g_playerAimMarkerVertices[4].a = alpha;
        gSPVertex(g_displayListCursor++, (u32) g_playerAimMarkerVertices, 5, 0);
        gSP1Triangle(g_displayListCursor++, 0, 1, 2, 0);
        gSP1Triangle(g_displayListCursor++, 0, 1, 4, 0);
        gSP1Triangle(g_displayListCursor++, 0, 2, 3, 0);
        gSP1Triangle(g_displayListCursor++, 0, 3, 4, 0);
    }
}

void Playerai_CreditDamageSource(TransientDamagePlayerView *damagedPlayer, TransientPlayerDamagePacket *damagePacket) {
    f32 damageScale;
    f32 scaledDamage;
    u8 sourceKind;
    u8 difficulty;
    TransientDamagePlayerView *damageSource;
    TransientDamagePlayerView *projectileOwner;
    TransientDamagePlayerView *creditedPlayer;

    damageSource = damagePacket->source;
    creditedPlayer = 0;
    if (damageSource != 0) {
        sourceKind = damageSource->actorKind;
        if (sourceKind != 1) {
            if (sourceKind == 2) {
                projectileOwner = damageSource->projectileOwner;
                if ((projectileOwner != 0) && (projectileOwner->actorKind == 1)) {
                    if (projectileOwner->flags & 0x300000) {
                        creditedPlayer = projectileOwner;
                        if (creditedPlayer == damagedPlayer) {
                            damagePacket->amount = (s32) ((f32) damagePacket->amount * g_playerDamageFixedPointScale * g_playerDamageBaseScale * g_playerDamageDifficultyScale);
                        }
                    } else if (projectileOwner->objectId == 1036) {
                        creditedPlayer = projectileOwner->player;
                    }
                }
            }
        } else if (damageSource->flags & 0x300000) {
            creditedPlayer = damageSource->player;
        }
    } else {
        creditedPlayer = damagedPlayer;
    }
    if (creditedPlayer != 0) {
        if (creditedPlayer->computerControlled != 0) {
            difficulty = creditedPlayer->profile->difficulty;
            switch (difficulty) { /* irregular */
            case 2:
                break;
            default:
                creditedPlayer->profile->difficulty = 0U;
                /* fallthrough */
            case 0:
                scaledDamage = (f32) damagePacket->amount * g_playerDamagePrimaryFixedPointScale;
                scaledDamage *= g_playerDamagePrimaryModeScale;
                damagePacket->amount = (s32) (scaledDamage * g_playerDamageAndDistanceConstants);
                break;
            case 1:
                scaledDamage = (f32) damagePacket->amount * g_playerDamageSecondaryFixedPointScale;
                scaledDamage *= g_playerDamageSecondaryModeScale;
                damagePacket->amount = (s32) (scaledDamage * g_playerDamageAndDistanceConstants);
                break;
            }
        }
        { CGameStatus *state=(&g_gameSettings.counters);
        if ((state->teams != 0) && (((Shared_Game *)((u8 *)state - ((char *)&((Shared_Game *)0)->counters - (char *)0)))->multiplayerRuleBytes[0] == 0) && ((creditedPlayer->computerControlled == 0) || (damagedPlayer->computerControlled == 0)) && (damagedPlayer->profile->reservedByte == creditedPlayer->profile->reservedByte)) {
            damagePacket->amount = 0;
        }}
    }
}

void Playerai_RotatePlayerPoseBuffers(struct CPlayerPool_t *playerPool) {
    void *node;

    if (*(void **)playerPool != 0) {
        Cache_MarkResourceInUse(0, *(void **)playerPool);
    }

    node = playerPool->m_ActiveList.head;
    if (node != 0) {
        u8 *base = (u8 *)&g_gameSettings;

        do {
            Gobjinst_RotatePoseMatrixBuffers(node);
            Gobjinst_RotatePoseMatrixBuffers(&((struct Shared_ActorView *)(node))->weapon);
            Playerai_DrawCachedModelAndShadow(node, 0);
            if (base[29] != 0) {
                Gobjinst_BuildAnimatedPose(node, 1);
            }
            node = ((struct Shared_ActorView *)(node))->next;
        } while (node != 0);
    }
}

void Playerai_UpdatePlayerRenderResources(struct CPlayerPool_t *playerPool, void *world) {
    void *node;
    int scale;
    s32 count1;
    s32 count2;
    char *entry;

    node = playerPool->m_ActiveList.head;
    if (node != 0) {
        do {
            ((TransientPlayerResetView *)(node))->floorClearance = 0;
            ((TransientPlayerResetView *)(node))->scanClearedWord = 0;
            if (InstHdr_CanActorReceiveInteraction(node) != 0) {
                if (node) {
                    count1 = ((TransientPlayerWorldCounts *)(world))->itemCount1;
                } else {
                    count1 = ((TransientPlayerWorldCounts *)(world))->itemCount1;
                }
                if (count1 != 512) {
                    scale = 4;
                    ((TransientWorldPlayerSlotView *)(((s32)world + count1 * scale)))->itemSlots = node;
                    ((TransientPlayerWorldCounts *)(world))->itemCount1 = count1 + 1;
                }
                count1 = 2888;
                count2 = ((IntegerStateB4C *)world)->itemCount2;
                if (count2 != 128) {
                    ((struct TransientWorldItemSlotView *) (entry = (char *) (((s32) world) + (count2 * 4))))->secondItemSlots = node;
                    ((IntegerStateB4C *)world)->itemCount2 = count2 + 1;
                }
            }
            node = ((TransientPlayerResetView *)(node))->nextPlayer;
        } while (node != 0);
    }
}

void Playerai_DrawPlayersForView(void *world, void *view) {
    WorldPlayerHeadView *object;
    PlayerViewModeView *argument;
    PlayerViewListNode *cur;

    Geometry_BeginModelBatch();
    object = world;
    cur = object->players;
    if (cur != 0) {
        do {
            argument = view;
            if (cur->view != view ||
                argument->viewMode == 1 ||
                Cinema_IsSequenceFlagTwoSet() != 0) {
                Player_DrawPlayerModel(cur, view);
            }
            cur = cur->next;
        } while (cur != 0);
    }
    Geometry_FlushModelBatch();
}

/* Removes entity from list if owned by specific owner, with version-specific check. */
void Playerai_DrawViewPlayer(void *world, void *view) {
    WorldPlayerHeadView *object;
    PlayerViewModeView *argument;
    PlayerViewRenderListNode *viewPlayer;

#if defined(VERSION_US_REV1)
    if (g_playerViewRenderingEnabled != 0) {
        object = world;
        object = world;
    viewPlayer = object->players;
        if (viewPlayer != 0) {
            do {
                argument = view;
                if (viewPlayer->view == view &&
                    argument->viewMode == 0 &&
                    viewPlayer->modelKind != g_fragTagModelId) {
                    Player_DrawHeldWeapon(viewPlayer, view);
                }
                viewPlayer = viewPlayer->next;
            } while (viewPlayer != 0);
        }
    }
#else
    object = world;
    viewPlayer = object->players;
    if (viewPlayer != 0) {
        do {
            argument = view;
            if (viewPlayer->view == view &&
                argument->viewMode == 0 &&
                viewPlayer->modelKind != g_fragTagModelId) {
                Player_DrawHeldWeapon(viewPlayer, view);
            }
            viewPlayer = viewPlayer->next;
        } while (viewPlayer != 0);
    }
#endif
}

/* Notifies the entity list associated with roundContext about entity and calls a handler for each owner. */
void Playerai_UpdateViewPlayerProjection(void *roundContext, void *entity) {
    Round *round = roundContext;
    Shared_ActorView *viewPlayer;

#if defined(VERSION_US_REV1)
    if (g_playerViewRenderingEnabled != 0) {
#endif
        Gsky_LoadProjectionMatrix(entity);
        viewPlayer = round->players;
        if (viewPlayer != 0) {
            do {
                if (viewPlayer->message == entity) {
                    Player_DrawHeadsUpDisplay(viewPlayer, entity);
                }
                viewPlayer = viewPlayer->next;
            } while (viewPlayer != 0);
        }
#if defined(VERSION_US_REV1)
    }
#endif
}

void Playerai_DrawViewMatchCountdown(void *roundContext, void *viewState) { Player_DrawMatchCountdown(roundContext, viewState); }

int Playerai_GetFirstPlayer(void *world) {
    Context *context = world;
    return (int)context->head;
}

void *Playerai_FindTransientPlayer(struct Context *context) {
    CGameStatus *base = (&g_gameSettings.counters);
    Shared_ActorView *record;

    if (base->m_bFragTagOn != 0 && base->m_FragTagFlipTimer != 0) {
        return 0;
    }
    record = (void *)context->head;
    if (record != 0) {
        do {
            if (record->controls->transientFlag == 1) {
                return record;
            }
            record = record->next;
        } while (record != 0);
    }
    return 0;
}
