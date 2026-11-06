#include "Common/packed_callback_symbols.h"
#include "include_asm.h"
#include "Common/rg.h"

extern char g_encodedCheatTextWords[180];
extern char addrLow_Pak_SelectProfilePrompt[];
extern char addrLow_Pak_SelectProfilePromptWithSavePending[];
#include "Common/resident_event_handler.h"
#include "Common/animation_pool.h"
#include "Common/heap_arena_entry.h"
#include "Engine/Cache/list.h"
#include "Source/ovlgame.h"
#include "Common/objb.h"
#include "types.h"
#include "Common/level_track.h"
#include "Common/audio_callbacks.h"
#include "Common/sharedplayer.h"
#include "Common/packed.h"
#include "Common/vector4f.h"
#include "Common/level_input.h"
#include "Common/runtime_declarations.h"
#include "PFS/CONTROLLER.H"
#include "Common/Lone/controller_si_message_queue.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Common/pakqueuestate.h"
#include "libultra/os/getthreadid.h"
#include "Engine/rumble.h"
#include "Control/control.h"
#include "Ovlgame/ovlgame_address_symbols.h"
#include "Frontend/frontend_address_symbols.h"
#include "Common/actor_definition.h"
#include "Common/results.h"
#include "Common/multiplayeroptions.h"
#include "Render/effect_pool_operations.h"
#include "Common/triple.h"
#include "Ovlgame/effect.h"
#include "Playerai/playerai__playerai.h"
#include "Fx/normalize_vector.h"
#include "../sdk/include/PFS/OVLGAME_INITIALIZERENDERDIRECTION.H"
#include "Ovlgame/direction.h"
#include "Common/render_direction.h"
#include "Common/frontend_clock_state.h"
#include "Common/effectcontribution.h"
#include "Common/level.h"
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Ovlgame/match_initparticlequad.h"
#include "Common/sessionhandlerrow.h"
#include "Common/world.h"
#include "Ovlgame/match.h"
#include "Player/player_getammocapacity.h"
#include "Menu/pickup_drawscaledintensitytilegrid.h"
#include "Common/hud_effects.h"
#include "Onscrn/onscreen_drawscaledmaskedtilegrid.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Ovlgame/hud.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Engine/lists.h"
#include "Common/packed_callback.h"

void Ovlgame_InitializeSceneEffectPool(struct CAnimPool *animationPool) {
    SceneEffect *sceneEffect;
    s32 i;

    List_InitializeIntrusive(&animationPool->FreeList, 744, 748);
    List_InitializeIntrusive(&animationPool->UsedList, 744, 748);
    i = 0;
    sceneEffect = animationPool->DynAnims;
    do {
        List_AppendIntrusive(&animationPool->FreeList, sceneEffect);
        i += 1;
        sceneEffect += 1;
    } while (i < 32);
}

/* Resets the controller and profile state for a new session: reinitialises the input buffers and stream through Rumble_InitPoolNodes_Controller, osCreateMesgQueue, osSetEventMesg_Controller, osContInit, osGetThreadId and osSendMesg_Mutex, then for slots 3 down to 0 clears the slot's three state words, refreshes its pad through Control_DisableControllerPakDe and counts the profiles Ovlgame_ResetControllerProfile accepts in g_connectedControllerProfileCount, remembering the lowest accepted slot in g_firstConnectedControllerPort; finally checks the profile just below slot 0 with mode 4, marks the session reset and returns the remembered slot. */
s16 Ovlgame_InitializeControllerSession(void) {
    s32 i;

    Rumble_InitPoolNodes(&g_controllerRumblePool, g_controllerRumbleNodes, 8);
    g_controllerPakFrontendState = 2;
    osCreateMesgQueue(g_controllerSiMessageQueue, g_controllerSiMessageBuffer, 1);
    osCreateMesgQueue(&g_controllerReadMessageQueue, g_controllerAccessMessages, 1);
    osSetEventMesg(5, g_controllerSiMessageQueue, 1);
    osContInit(g_controllerSiMessageQueue, g_controllerPresenceBits, g_controllerQueryStatus);
    osGetThreadId(0);
    g_controllerAudioThreadId = -1;
    osSendMesg(&g_controllerReadMessageQueue, 0, 1);
    g_firstConnectedControllerPort = -1;
    g_connectedControllerProfileCount = 0;
    for (i = 3; i >= 0; i--) {
        g_controllerPakState[i] = 0;
        g_controllerPakReinitializePending[i] = 0;
        g_controllerPakProbePending[i] = 0;
        Control_DisableControllerPak(i);
        if (Ovlgame_ResetControllerProfile(&g_controllerProfiles[i], i) != 0) {
            g_firstConnectedControllerPort = i;
            g_connectedControllerProfileCount++;
        }
    }
    Ovlgame_ResetControllerProfile(&g_controllerProfiles[i], 4);
    g_controllerInputReady = 1;
    return g_firstConnectedControllerPort;
}

s32 Ovlgame_ResetControllerProfile(ControllerProfile *profile, s32 port) {
    s32 i;
    s32 connected;
    profile->port = port;
    profile->connected = 0;
    profile->pakActive = 0;
    profile->mode = 0;
    profile->reset = 0;
    profile->reservedWordA = 0;
    profile->reservedWordB = 0;
    profile->reservedWordC = 0;
    profile->stickX = 0;
    profile->stickY = 0;
    profile->previousStickX = 0;
    profile->previousStickY = 0;
    profile->inputPreviousButtons = 0;
    profile->inputButtons = 0;
    profile->inputPressedButtons = 0;
    profile->inputHistory[0] = 0;
    profile->inputHistory[1] = 0;
    profile->inputHistory[2] = 0;
    for (i = 0; i < 32; i++) {
        profile->buttonHistory[i].taps = 0;
        profile->buttonHistory[i].age = 0;
        profile->buttonHistory[i].repeat = 48;
        profile->buttonHistory[i].held = 0;
    }
    connected = ((g_controllerReadStatusBytes[port * 4] >> 3) ^ 1) & 1;
    profile->pakAmount = 0;
    profile->pakTimer = 0;
    profile->connected = connected;
    Rumble_InitPoolNodes((char *)&profile->effectPool, (char *)profile->effectNodes, 3);
    return profile->connected;
}

/* Initialises the pool of 32 effect slots in a world record: threads them into a free list (slot 0 has no
 * predecessor, slot 31 no successor), empties the live list, sets up the two shared effect definitions
 * and points every slot at the default definition through SetN64_InitializeEffectSlot. */
void Effect_InitEffectPool(EffectSlotPool *world) {
    s32 i;

    world->free = world->slots;
    world->tail = 0;
    world->head = 0;
    for (i = 0; i < EFFECT_SLOTS - 1; i++) {
        world->slots[i].next = &world->slots[i + 1];
        world->slots[i].prev = (struct EffectSlot *)((u32)world->slots + (i - 1) * sizeof(world->slots[0]));
    }
    world->slots[0].prev = 0;
    world->slots[EFFECT_SLOTS - 1].next = 0;
    Playerai_InitializeCompactAnimationState(&g_defaultEffectDefinition);
    ((ActorDefinitionHeader *)&g_defaultEffectDefinition)->kind = 8;
    ((ActorDefinitionHeader *)&g_defaultEffectDefinition)->flags = 1;
    ((ActorDefinitionHeader *)&g_defaultEffectDefinition)->send = 0;
    Playerai_InitializeCompactAnimationState(&g_boundedEffectDefinition);
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->header.kind = 8;
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->header.flags = 0;
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->header.send = 0;
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->boundsA = g_effectDefinitionDefaultBounds;
    ((EffectDefinitionBounds *)&g_boundedEffectDefinition)->boundsB = g_effectDefinitionDefaultBounds;
    for (i = 0; i < EFFECT_SLOTS; i++) {
        SetN64_InitializeEffectSlot(&world->slots[i]);
    }
}

void Ovlgame_InitializeRenderDirection(RenderSettings *state) {
    state->direction.x = g_defaultEffectDirectionX;
    state->direction.y = g_defaultEffectDirectionY;
    state->direction.z = g_defaultEffectDirectionZ;
    Graphu64_NormalizeVec3(&state->direction.x);
    state->ready = 1;
}

#if defined(VERSION_EU_X)
/* Zero word ending DIRECTION's object; no instruction reads it. */
unsigned int g_ovlgameInitializeRenderDirectionZeroTail[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
unsigned int k_OvlgameInitializerenderdirectionZeroWords[1] = {
    0x00000000,
};
#endif

s32 Match_InitParticleQuad(void) {
    Vtx *vertices = (Vtx *)&g_particleQuadVertices;
    s32 i = 0;
    s32 more;

    vertices[0].v.ob[0] = -1;
    vertices[0].v.ob[2] = 1;
    vertices[0].v.tc[0] = 0;
    vertices[0].v.tc[1] = 0;
    vertices[1].v.ob[0] = 1;
    vertices[1].v.ob[2] = 1;
    vertices[1].v.tc[0] = 1024;
    vertices[1].v.tc[1] = 0;
    vertices[2].v.ob[0] = 1;
    vertices[2].v.ob[2] = -1;
    vertices[2].v.tc[0] = 1024;
    vertices[2].v.tc[1] = 1024;
    vertices[3].v.ob[0] = -1;
    vertices[3].v.ob[2] = -1;
    vertices[3].v.tc[0] = 0;
    vertices[3].v.tc[1] = 1024;
    do {
        vertices[i].v.ob[1] = 0;
        vertices[i].v.flag = 0;
        vertices[i].v.cn[0] = 255;
        vertices[i].v.cn[1] = 255;
        vertices[i].v.cn[2] = 255;
        vertices[i].v.cn[3] = 255;
        i++;
        more = i < 4;
    } while (more);
    return more;
}

/* Resets a match: calls Control_SetControllerMode_Optiontransition with zero, Rumble_FreeAllPoolNodes_Match on g_controllerRumblePool and Playerai_ResetPlayerControllers_Match on
   g_playerViewRenderContext, clears five state words of g_gameSettings.counters, and sets the byte at offset 0x26DC1 of the
   match block to 2 and its word at 0x26DBC to one. */

struct Context;

void Match_ResetMatchControllerState(char *match) {
    CGameStatus *state;

    Control_SetControllerMode(0);
    Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
    Playerai_ResetPlayerControllers(&g_playerViewRenderContext);
    state = &g_gameSettings.counters;
    state->teams = 0;
    state->m_bFragTagOn = 0;
    state->m_bCTFOn = 0;
    state->first = 0;
    state->transitionActive = 0;
    ((GameSession *)match)->phase = 2;
    ((GameSession *)match)->target = 1;
}

/* Asks Scene_FindPlacedObjectsByKey_Match about g_world_AchieveUpdateresultsscreen with a minus-one selector, clears the words of g_gameSettings.counters and puts the object at gameSession into state 0xC with byte 0x26DC1 set to two and the selector, or zero when the lookup failed, stored at 0x26DD8. */
void Match_ResetGameClockAndSelectSpawn(GameSession *gameSession) {
    Shared_Placed spawn;
    s32 spawnSelector;

    spawnSelector = -1;
    if (Scene_FindPlacedObjectsByKey(&g_world, spawnSelector, spawnSelector, &spawn, 1) == 0) {
        spawnSelector = 0;
    }
    g_gameSettings.counters.m_GameTimeFifteenth = 0;
    g_gameSettings.counters.m_GameTimeSeconds = 0;
    g_gameSettings.counters.m_GameTimeMinutes = 0;
    g_gameSettings.counters.m_GameTimeHours = 0;
    gameSession->selectionActive = 0;
    g_gameSettings.counters.first = 0;
    gameSession->phase = 2;
    gameSession->selector = spawnSelector;
    gameSession->target = 12;
}

/* Starts the fade out of the session into the match: keeps key as the session selector when
   Scene_FindPlacedObjectsByKey finds a placed object for it (else 0), restarts the game clock and targets mode 13
   when the local player has a transition pending, otherwise mode 12. */
void Match_StartMatchTransition(GameSession *session, s32 key) {
    Shared_Placed spawn;
    if (Scene_FindPlacedObjectsByKey(&g_world, -1, key, &spawn, 1) == 0) {
        key = 0;
    }
    g_gameSettings.counters.m_GameTimeFifteenth = 0;
    g_gameSettings.counters.m_GameTimeSeconds = 0;
    g_gameSettings.counters.m_GameTimeMinutes = 0;
    g_gameSettings.counters.m_GameTimeHours = 0;
    g_gameSettings.counters.first = 0;
    session->selectionActive = 0;
    session->selector = key;
    if (session->local != 0) {
        if (g_gameSettings.counters.transitionActive != 0) {
            session->phase = 2;
            session->target = 13;
        } else {
            session->phase = 2;
            session->target = 12;
        }
    } else {
        session->phase = 2;
        session->target = 12;
    }
}

/* Initialises the actor world: builds the two list pools (0x20 shapes of 0x54 bytes, 3 tails of 0x1C), links the
 * 96 actors of 0xB8 bytes into the actor list, empties the record list and its 10 cells, links the 100 records of
 * 0x50 bytes into it, clears the mode and cursor words and finishes through Fx_UpdateEffectLists. */
void Hud_InitializeWorldActorPools(RibbonWorld *world) {
    s32 i;

    Lists_InitFromPool(&world->pool, world->shapePool, 84, 32);
    Lists_InitFromPool(&world->timers, world->tailPool, 28, 3);
    Lists_ClearHeader(&world->actorList);
    for (i = 0; i < 96; i++) {
        Lists_Append(&world->actorList, &world->actors[i]);
    }
    List_InitializeIntrusive(&world->recordList, 0, 4);
    for (i = 0; i < 10; i++) {
        List_InitializeIntrusive(&world->cells[i], 0, 4);
    }
    for (i = 0; i < 100; i++) {
        List_AppendIntrusive(&world->recordList, &world->records[i]);
    }
    world->displayList = 0;
    world->remaining = 0;
    Fx_UpdateEffectLists(world);
}

/* Resets the hud: clears the four words at 0x90, runs Hud_EmptyCallback and OnScreen_LoadFontTexture, then fills the two
 * 0x100-byte tables at 0xC8 and 0x1C8 from the pair lists g_hudPrimaryByteLookupSource and g_hudSecondaryByteLookupSource (0x75 pairs each, 0x5C in de). */
void Hud_ResetHudCharTables(Hud *hud) {
#if defined(VERSION_DE)
    s32 pairs = 92;
#else
    s32 pairs = 117;
#endif
    hud->words[0] = 0;
    hud->words[1] = 0;
    hud->words[2] = 0;
    hud->words[3] = 0;
    Hud_EmptyCallback();
    OnScreen_LoadFontTexture();
    Pickup_BuildByteLookup((int)hud, g_hudPrimaryByteLookupSource, pairs, hud->glyphLookup);
    Pickup_BuildByteLookup((int)hud, g_hudSecondaryByteLookupSource, pairs, hud->alternateGlyphLookup);
}

void Hud_EmptyCallback(void) {
}

/* Starts the HUD's two movers: each is reset to (0, -0x28) and (0, -0x14) with its enable word cleared, and
 * given its frame table (g_hudUpperPanelMoverScript, g_hudLowerPanelMoverScript) through OnScreen_StartMoverScript. */
void Hud_StartPanelMovers(Hud *panel) {
    panel->bars[0].enabled = 0;
    OnScreen_InitMover(&panel->bars[0].mover, 0, -40);
    OnScreen_StartMoverScript(&panel->bars[0].mover, &g_hudUpperPanelMoverScript);
    panel->bars[1].enabled = 0;
    OnScreen_InitMover(&panel->bars[1].mover, 0, -20);
    OnScreen_StartMoverScript(&panel->bars[1].mover, &g_hudLowerPanelMoverScript);
}

#if defined(VERSION_EU)
struct {
    unsigned int words0[1724];
    float floats1[1];
    unsigned int words2[1];
    char text3[4];
    unsigned int words4[1848];
} g_overlayObjectLinkWords = {
    {
        0x8E2205D8, 0xA0400080, 0xAE2005E0, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385,
        (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x0000000A, 0x0000FF01,
        (unsigned int)g_pakOwnerChannelLabels, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_UpdateOwnerChannelLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000FFF8,
        0x0000FF01, (unsigned int)g_pakProfileLoadProfileChoiceLabels, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, PACKED_CALLBACK_LOW(Timer_UpdateAlternateActionLabel), 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000006, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x10], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x20], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x30], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x40], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel,
        (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x50], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x60],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        (unsigned int)&g_pakOwnerChannelLabels[0x70], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x80], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x90], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0xA0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0xB0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0xC0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel,
        (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0xD0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0xE0],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        (unsigned int)&g_pakOwnerChannelLabels[0xF0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, (unsigned int)&g_pakOwnerChannelLabels[0x100], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateNoteLabel, (unsigned int)addrLow_Snapshot_SelectNote, 0x00000000, 0x00000000, 0x00011001,
        0x00000003, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Snapshot_UpdateSpaceLabel, 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x0000000A, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_UpdateManagerChannelLabel_Objectdata, (unsigned int)addrLow_Snapshot_HandleMenuAction, 0x00000000,
        0x00000000, 0x00010041, 0x00000004, 0x0000FF01, (unsigned int)g_pakSaveMenuSnapshotChoiceLabels + 0x10, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_SetManagerHeading_Objectdata, (unsigned int)addrLow_Snapshot_CloseNoteBrowser,
        0x00000000, 0x0044F420, 0x00160000, (unsigned int)addrLow_Snapshot_BeginProfileLoad, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Timer_CheckMenuPakChange_Objectdata, 0x00150000,
        0x00000000, 0x00000000, 0x0044F420, 0x00160000, (unsigned int)addrLow_Snapshot_BeginProfileSave, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Timer_CheckMenuPakChange_Objectdata,
        0x00140000, 0x00000000, 0x00000000, 0x0044F420, 0x00160000, (unsigned int)addrLow_Snapshot_BeginBlockLoad, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu,
        (unsigned int)addrLow_Timer_CheckChangedMenuChannel_Objectdata, 0x00150000, 0x00000000, 0x00000000, 0x0044F420, 0x00160000, (unsigned int)addrLow_Snapshot_BeginSnapshotSave, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Timer_CheckChangedMenuChannel_Objectdata, 0x00140000, 0x00000000, 0x00000000, 0x0044F420, 0x00160000, (unsigned int)addrLow_Snapshot_CheckEuropeanSaveAvailability,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Timer_UpdateManagerStatus_Objectdata, 0x00140000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_pakNoteLabelSlots, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_UpdateAlternatePromptLabel_Objectdata, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000014, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_DispatchPreviewHandle, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_difficultyHardText + 0x30, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_FormatPreviewDottedTriple_Objectdata,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000000A, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Timer_UpdatePreviewDepthLabel_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_difficultyHardText + 0x10,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_FormatPreviewPageCount_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        (unsigned int)g_difficultyHardText + 0x20, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_FormatPreviewValue_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014,
        0x0000FF01, (unsigned int)g_pakAlternateActionLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Timer_UpdateAlternateActionLabel_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010040,
        0x007D000A, 0x00010000, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00408A58, 0x00000000, 0x00000000,
        0x00024040, 0x000A0000, 0xFF000000, (unsigned int)g_captureFlagVictimFollowupMessage + 0x40, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Timer_OpenSelectedPrompt_Objectdata, 0x00000000,
        0x0044F7EC, 0x000A0000, (unsigned int)addrLow_Timer_EnableAlternatePrompt_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00080000, 0x00000000,
        0x00000000, 0x0044F7EC, 0x000A0000, PACKED_CALLBACK_LOW(Timer_UpdatePreviewKindLabel), 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00090000,
        0x00000000, 0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_pakPreviewKindLabelProfile,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, PACKED_CALLBACK_LOW(Pak_SelectPromptKindFive), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000032, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040AB6C, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000002,
        0x0000FF01, (unsigned int)g_localizedPakStatusLines, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Menu_FormatLocalizedPakStatus, 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000002, 0x0000FF01, (unsigned int)&g_localizedPakStatusLines[0x10], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040ADC0, 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x00000002, 0x0000FF01, (unsigned int)&g_localizedPakStatusLines[0x20], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00408CAC, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000010, 0x0000FF01, (unsigned int)g_pakAlternateActionLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_UpdateProfileActionLabel_Objectdata, 0x00000000,
        0x00000000, 0x00000000, 0x00010040, 0x007D000A, 0x00010000, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000,
        (unsigned int)addrLow_Pak_ConfirmProfileOrDeleteNote_Objectdata, 0x00000000, 0x00000000, 0x00024040, 0x000A0000, 0xFF000000, (unsigned int)g_captureFlagVictimFollowupMessage + 0x40, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        0x00000000, (unsigned int)addrLow_Pak_OpenProfileActionPrompt_Objectdata, 0x00000000, 0x0044F99C, 0x00090000, (unsigned int)addrLow_Timer_EnableProfilePreview_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044F99C, 0x00090000, (unsigned int)addrLow_Timer_ClearProfilePreview_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x0044F99C, 0x00090000, (unsigned int)addrLow_Timer_DisablePreviewSelection,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_SelectPromptActionHeading_Objectdata, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x0000001E, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040B0D0, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040B1FC,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        0x0040B328, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040B454, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040B580, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000019,
        0x0000FF01, (unsigned int)g_SelectModalPromptLabelStateOtherText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_SelectModalPromptLabel_Objectdata, (unsigned int)addrLow_Pak_ClosePromptByKind_Objectdata, 0x00000000, 0x0044FB4C, 0x00080000,
        (unsigned int)addrLow_Pak_SelectPromptKindZero_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C,
        0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupThree), 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044FB4C, 0x00080000, 0x0040AF0C, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044FB4C, 0x00080000, 0x0040AF20, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, 0x0040AF34, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, 0x0040AF48, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, 0x0040AF5C, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, 0x0040AF70,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000,
        0x0040AF84, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C,
        0x00080000, 0x0040AFD0, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044FB4C, 0x00080000, 0x0040AFEC, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044FB4C, 0x00080000, 0x0040B00C, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, 0x0040B020, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, 0x0040B034, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, 0x0040B070, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000, 0x0040B048,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044FB4C, 0x00080000,
        0x0040B05C, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x00010000,
        0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)&g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][4][0x10], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000028, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_SelectOperationHeading_Objectdata,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Pak_SelectOperationDescription_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_FormatOperationChannelLabel_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014, 0x0000FF01,
        (unsigned int)&g_pakChannelLabelTexts_eu + 0x10, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Pak_OpenPakChannel_Objectdata, 0x00000000, 0x00000000, 0x00010041, 0x00000005,
        0x0000FF01, (unsigned int)&g_pakChannelLabelTexts_eu + 0x20, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Pak_OpenPakStatusPrompt_Objectdata, 0x00000000, 0x00000000, 0x00010041,
        0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_SelectPakLoadHeading_Objectdata, (unsigned int)addrLow_Pak_CancelPakAction_Objectdata, 0x00000000, 0x0044FED0,
        0x00080000, (unsigned int)addrLow_Pak_EnableOperationHeading_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Pak_CheckOperationPakChange_Objectdata, 0x00070000, 0x00000000, 0x00000000,
        0x0044FED0, 0x00080000, (unsigned int)addrLow_Pak_DisableOperationHeading, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Pak_CheckOperationPakChange_Objectdata, 0x00050000, 0x00000000,
        0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        0x0040BCA8, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000023, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040BD24, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040BDA0, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004,
        0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040BE1C, 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000004, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x0040BE98, 0x00000000, 0x00000000, 0x00000000,
        0x00012001, 0x00000023, 0x0000FF01, (unsigned int)g_pakConfirmationDefaultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Frontend_SelectPakConfirmationLabel_Objectdata, (unsigned int)addrLow_Pak_ConfirmPendingOperation_Objectdata, 0x00000000,
        0x00000000, 0x00012001, 0x00000005, 0x0000FF01, (unsigned int)s_nodeDefaultFieldText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Menu_SelectEuropeanPakActionLabel, (unsigned int)addrLow_Timer_CancelPendingOperation_Objectdata,
        0x00000000, 0x00450038, 0x00080000, (unsigned int)addrLow_Pak_SelectPakOperationZero_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, PACKED_CALLBACK_LOW(Menu_SelectPakOperationActionLabel), 0x00070000,
        0x00000000, 0x00000000, 0x00450038, 0x00080000, 0x0040BC38, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, PACKED_CALLBACK_LOW(Menu_SelectPakOperationActionLabel),
        0x00070000, 0x00000000, 0x00000000, 0x00450038, 0x00080000, 0x0040BC54, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu,
        PACKED_CALLBACK_LOW(Menu_SelectPakOperationActionLabel), 0x00070000, 0x00000000, 0x00000000, 0x00450038, 0x00080000, 0x0040BC70, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, PACKED_CALLBACK_LOW(Menu_SelectPakOperationActionLabel), 0x00070000, 0x00000000, 0x00000000, 0x00450038, 0x00080000, 0x0040BC8C,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, PACKED_CALLBACK_LOW(Menu_SelectPakOperationActionLabel), 0x00070000, 0x00000000, 0x00000000, 0x00052880, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x9C],
        (unsigned int)&g_optionFlagsChangedMessageText + 0x60, 0x00000020, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x8C], (unsigned int)&g_optionFlagsChangedMessageText + 0x80, 0x00000080, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x84],
        (unsigned int)&g_optionFlagsChangedMessageText + 0x90, 0x00000100, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x78], (unsigned int)&g_optionFlagsChangedMessageText + 0x70, 0x00000040, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x6C],
        (unsigned int)&g_optionFlagsChangedMessageText + 0xA0, 0x00000200, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x58], (unsigned int)&g_optionFlagsChangedMessageText + 0xB0, 0x00000400, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x4C],
        (unsigned int)&g_optionFlagsChangedMessageText + 0xC0, 0x00000800, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x44], (unsigned int)&g_optionFlagsChangedMessageText + 0xD0, 0x00001000, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x38],
        (unsigned int)&g_optionFlagsChangedMessageText + 0xF0, 0x00004000, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x2C], (unsigned int)&g_optionFlagsChangedMessageText + 0x100, 0x00008000, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x14],
        (unsigned int)&g_encodedCheatCode[0x3C], 0xFFFFFFFF, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderEu.text[0x0], (unsigned int)&g_encodedCheatCode[0x64], 0x0400C7E0, 0x00000001, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x80, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00210041, 0x00000014, 0x0000FF01, (unsigned int)&g_encodedCheatCode[0x18], (unsigned int)addrLow_Encoded_DrawTextEntryCursor_Objectdata, (unsigned int)addrLow_Encoded_UpdateTextEntryCursor_Objectdata,
        (unsigned int)addrLow_Encoded_TextEntryReturnZero_Objectdata, 0x00000000, 0x00000000, 0x00010050, 0x00500014, 0x0601FF07, (unsigned int)g_creditsLocalizedLines + 0x14, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FE07, (unsigned int)g_creditsLocalizedLines + 0x28,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FD07,
        (unsigned int)g_creditsLocalizedLines + 0x3C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01FC07, (unsigned int)g_creditsLocalizedLines + 0x50, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01FB07, (unsigned int)g_creditsLocalizedLines + 0x64, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFF01FA07, (unsigned int)g_creditsLocalizedLines + 0x78, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0x8C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata,
        0x00000000, 0x00000000, 0x00010050, 0x00500008, 0x0601F907, (unsigned int)g_creditsLocalizedLines + 0xA0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0xB4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0xC8,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        (unsigned int)g_creditsLocalizedLines + 0xDC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0xF0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x104, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0x118, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000,
        0x00000000, 0x00010050, 0x00500008, 0x0601F907, (unsigned int)g_creditsLocalizedLines + 0x12C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata,
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x140, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x154, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x168,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        (unsigned int)g_creditsLocalizedLines + 0x17C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x190, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0x1A4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000,
        0x00010050, 0x00500008, 0x0601F908, (unsigned int)g_creditsLocalizedLines + 0x1B8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x1CC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata,
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F906, (unsigned int)g_creditsLocalizedLines + 0x1E0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F905, (unsigned int)g_creditsLocalizedLines + 0x1F4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F904, (unsigned int)g_creditsLocalizedLines + 0x208,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F903,
        (unsigned int)g_creditsLocalizedLines + 0x2F8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_DeletePreviousTextEntryCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFFFAF902, (unsigned int)g_creditsLocalizedLines + 0x30C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Encoded_ApplyCheatCode_Objectdata, 0x00000000, 0x00000000, 0x00011001,
        0x00000014, 0x00000000, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Encoded_SetTextEntryResultLabel_Objectdata, 0x00000000, 0x00000000, 0x00000000,
        0x00310201, 0x00000018, 0x0000FEE2, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu_Objectdata, 0x00000000,
        0x004502D0, 0x00210000, (unsigned int)addrLow_Encoded_ResetTextEntryResult_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x50, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00411001, 0x0000000C, 0x0000FF01, (unsigned int)g_menuOptionInvincibilityDisabledText,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit0Item_Objectdata, (unsigned int)addrLow_Pak_ToggleTextChoice_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        (unsigned int)g_menuOptionInfiniteLivesDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit1Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit1_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, (unsigned int)g_menuOptionAllWeaponsDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit2Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit2_Objectdata, 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, (unsigned int)g_menuOptionUnlimitedAmmoDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit3Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit3_Objectdata, 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionAllSpecialObjectsDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit4Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit4_Objectdata, 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBigHeadModeDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit5Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit5_Objectdata,
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionTinyModeDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit6Item_Objectdata,
        (unsigned int)addrLow_Option_ToggleOptionBit6_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBigHandsFeetModeDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Option_UpdateOptionBit8Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit8_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionStickModeDisabledText,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit7Item_Objectdata, PACKED_CALLBACK_LOW(CMenuProfile_EnableControllerPakAndClearState), 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        (unsigned int)g_menuOptionPenAndInkModeDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit9Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit9_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, (unsigned int)g_menuOptionGouraudModeDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit10Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit10_Objectdata, 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, (unsigned int)g_menuOptionJuansCheatDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit11Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit11_Objectdata, 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionZachAttackCheatDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit12Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit12_Objectdata, 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionAllMapDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit13Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit13_Objectdata,
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBlackoutDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Option_UpdateOptionBit14Item_Objectdata,
        (unsigned int)addrLow_Option_ToggleOptionBit14_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionFrootyStripesDisabledText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Option_UpdateOptionBit15Item_Objectdata, (unsigned int)addrLow_Option_ToggleOptionBit15_Objectdata, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Menu_SetSelectedLevelLabel_Objectdata, (unsigned int)addrLow_Encoded_HandleUnlockedLevelSelection_Objectdata, 0x00000000, 0x00000000, 0x00000201, 0x000000C0, 0x0000FF01,
        (unsigned int)g_captureFlagVictimFollowupMessage + 0xC0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu_Objectdata, 0x00000000, 0x00450798, 0x00140000, 0x0043D430,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00130000, 0x00000000, 0x00000000, 0x8FBF0018, 0x00000000,
        0x00000021, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0xD0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00010081, 0x00000028, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Items_ForwardRulesLock,
        0x00000000, 0x00000000, 0x00010081, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x40, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000,
        (unsigned int)addrLow_Items_HandleSessionOptionPage, 0x00000000, 0x00450A90, 0x00030000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x30],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000,
        (unsigned int)&g_profileMenuLabelWords[0x40], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x00000000, (unsigned int)&g_profileMenuLabelWords[0x50], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x60], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x70], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x80], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x90], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x20], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        0x00000000, (unsigned int)addrLow_CMenuProfile_ResetPlayerControllerProfile_Objectdata, 0x00000000, 0x00450B20, 0x00080000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu,
        (unsigned int)addrLow_CMenuProfile_HasRoundProgress_Objectdata, 0x00070000, 0x00000000, 0x00450D18, 0x00000000, 0x00011001, 0x00000000, 0x0000FF02,
        (unsigned int)&g_languageMenuAlternateTextTable + 0x40, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenPrimaryProfileMenu_Objectdata, 0x00000000, 0x00000000, 0x00010101, 0x00000008,
        0x00000000, (unsigned int)&g_languageMenuAlternateTextTable + 0x50, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_CMenuProfile_BindSelectedDebugField_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00411001,
        0x00000008, 0x0000FE01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_CMenuProfile_FormatProfileQuantityLabel_Objectdata, (unsigned int)addrLow_CMenuProfile_AdjustControllerSelection_Objectdata, 0x00000000, 0x00000000,
        0x00411001, 0x00000002, 0x0000FF01, (unsigned int)g_profileModeZeroLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_CMenuProfile_UpdateProfileModeLabel_Objectdata, (unsigned int)addrLow_CMenuProfile_ToggleProfileMode_Objectdata, 0x00000000,
        0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0x20], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenSecondaryProfileMenu_Objectdata,
        0x00000000, 0x00450C64, 0x00050000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_CMenuProfile_HasSavedRoundProgress_Objectdata, 0x00040000,
        0x00000000, 0x00450DD8, 0x00000460, 0x0000000B, 0x00000000, 0x00000000, 0xC2480000, 0xC4610000,
        0x40000000, 0x40000000, 0x40000000, 0x00000032, 0x00000050, 0x3DB2B8C4, 0x00010000, 0x30000000,
        0x00000000, 0x0000FF01, 0x00000387, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00030000,
        0x00410021, 0x00000000, 0x0000FF01, 0x00450D3C, (unsigned int)addrLow_Menu_DrawMenuModel_Objectdata, (unsigned int)addrLow_CMenuProfile_GameSpeedReturnZero_Objectdata, (unsigned int)addrLow_CMenuProfile_UpdatePlayerAnimationChoice_Objectdata, 0x00000000,
        0x00000000, 0x00010081, 0x00000019, 0x0000FF01, (unsigned int)&g_languageMenuAlternateTextTable + 0x30, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_CMenuProfile_ProfileModeReturnZero_Objectdata, (unsigned int)addrLow_CMenuProfile_OpenTimedPlayerDialog_Objectdata,
        0x00000000, 0x00450D6C, 0x00030000, (unsigned int)addrLow_CMenuProfile_EnableOwnerControllerPak_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_CMenuProfile_HasProfileRoundProgress_Objectdata, 0x00010000,
        0x00000000, 0x00000000, 0x00450D6C, 0x00030000, (unsigned int)addrLow_CMenuProfile_EnableControllerPakAndClearState_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_CMenuProfile_HasProfileRoundProgress_Objectdata,
        0x00010000, 0x00000000, 0x00000000, 0x00010000, 0x30000000, 0x00000000, 0x0000FF01, 0x00000387,
        (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000000, 0x0000FF01,
        (unsigned int)&g_profileMenuLabelWords[0xB0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010101, 0x0000000C,
        0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0xC0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenPrimaryPlayerDialog_Objectdata, 0x00000000, 0x00000000, 0x00010101,
        0x00000000, 0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0xD0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenAlternatePlayerDialog_Objectdata, 0x00000000, 0x00450E20,
        0x00040000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_CMenuProfile_HasDialogRoundProgress_Objectdata, 0x00020000, 0x00000000, 0x00000000,
        0xBF000000, 0xBECCCCCD, 0xBE99999A, 0xBE4CCCCD, 0xBDCCCCCD, 0x00000000, 0x3DCCCCCD, 0x3E4CCCCD,
        0x3E99999A, 0x3ECCCCCD, 0x3F000000, 0x3F19999A, 0x3F333333, 0x3F4CCCCD, 0x3F666666, 0x3F800000,
    },
    { 0.7f },
    {
        0x3F4CCCCD, 0x3F666666, 0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385,
    },
    "\?fff",
    {
        0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000201, 0x0000000C, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x300, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00410041, 0x0000001E, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectOptionRowLabel, (unsigned int)addrLow_Initial_ToggleMenuRowOption_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectOptionRowLabel, (unsigned int)addrLow_Initial_ToggleMenuRowOption_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectOptionRowLabel, (unsigned int)addrLow_Initial_ToggleMenuRowOption_Objectdata, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectOptionRowLabel, (unsigned int)addrLow_Initial_ToggleMenuRowOption_Objectdata, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectOptionRowLabel, (unsigned int)addrLow_Initial_ToggleMenuRowOption_Objectdata, 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectOptionRowLabel, (unsigned int)addrLow_Initial_ToggleMenuRowOption_Objectdata,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectOptionRowLabel,
        (unsigned int)addrLow_Initial_ToggleMenuRowOption_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Items_SelectOptionRowLabel, (unsigned int)addrLow_Initial_ToggleMenuRowOption_Objectdata, 0x00000000, 0x00000000, 0x00010201, 0x0000002D, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC0,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu_Objectdata, 0x00000000, 0x00450F14, 0x000B0000, 0x00000000, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x000A0000, 0x00000000, 0x00451154, 0x00010000, 0x10000000, 0x00000000,
        0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021,
        0x00000008, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x50, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010081, 0x00000000, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x300, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Initial_OpenMatchSetupMenu_Objectdata, 0x00000000,
        0x00000000, 0x00010201, 0x00000038, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu_Objectdata,
        0x00000000, 0x004510C4, 0x00040000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00020000,
        0x00000000, 0x004513B8, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x10,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000036, 0x0000FF01,
        (unsigned int)g_playerNameSuffixByLanguage + 0x20, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogWithControllerPak_Objectdata, 0x00000000, 0x00000000, 0x00010081, 0x00000004,
        0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x30, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogAfterTimerReset_Objectdata, 0x00000000, 0x00000000, 0x00010201,
        0x00000049, 0x0000FF01, (unsigned int)&g_languageMenuAlternateTextTable + 0x10, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Initial_RequestTransitionWithPakDisabled_Objectdata, 0x00000000, 0x00451178,
        0x00050000, (unsigned int)addrLow_Initial_ProbeMenuControllerPak_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00020000, 0x00000000, 0x00000000,
        0x00451178, 0x00050000, (unsigned int)addrLow_Initial_EnableMenuControllerPak_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000,
        0x00000000, 0x00000000, 0x00451274, 0x00010000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000,
        0x00020000, 0x00000000, 0x004513B8, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000384,
        (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000081, 0x0000001E, 0x0000FF01,
        (unsigned int)g_playerNameSuffixByLanguage + 0x10, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Initial_SelectInitialController_Objectdata, 0x00000000, 0x00000000, 0x00010081, 0x0000000C,
        0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x40, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Initial_UpdateMultiplayerAvailability_Objectdata, (unsigned int)addrLow_Initial_OpenLocalPlayerSetup_Objectdata, 0x00000000, 0x00000000, 0x00010081,
        0x0000000C, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x80, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogTopRow_Objectdata, 0x00000000, 0x00000000,
        0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x4B0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogMiddleRow_Objectdata, 0x00000000,
        0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x4A0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogBottomRow_Objectdata,
        0x00000000, 0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x4E0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000,
        (unsigned int)addrLow_Initial_OpenTrackPreviewMenu_Objectdata, 0x00000000, 0x004512BC, 0x00070000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x26640014, 0x00010000, 0x00000000, 0x00000000, 0x00000000,
        0x00000064, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000089, 0x00000028,
        0x00000000, (unsigned int)g_creditsLocalizedLines + 0x320, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Multi_DecreaseGameOverTimer_Objectdata, 0x00000000, 0x00000000, 0x004513E0, 0x00020000,
        (unsigned int)addrLow_Initial_ResetPlayerGameOverTimer_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Multi_CompleteGameOverDelay_Objectdata, 0x00010000, 0x00000000, 0x00000000, 0x0C0A3FB1,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0xB0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00010080, 0x00230016, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x20], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D0,
        0x0043FD00, 0x00000000, 0x00000000, 0x10D60000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D0, 0x0043FD00, 0x00000000, 0x00000000, 0x10D60001, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D0, 0x0043FD00, 0x00000000, 0x00000000, 0x10D60002, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D1, 0x0043FD00, 0x00000000, 0x00000000, 0x10E00000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007D1, 0x0043FD00, 0x00000000, 0x00000000, 0x10E00001,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D1, 0x0043FD00, 0x00000000, 0x00000000,
        0x10E00002, 0x00010000, 0x00024010, 0x00290000, 0x00000000, 0x000007E4, 0x0043FD00, 0x00000000,
        0x00000000, 0x11080000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940000, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x30],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D2, 0x0043FD00, 0x00000000, 0x00000000, 0x10EA0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D2, 0x0043FD00, 0x00000000, 0x00000000, 0x10EA0001, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D2, 0x0043FD00, 0x00000000, 0x00000000, 0x10EA0002, 0x00010000,
        0x00024010, 0x003C0000, 0x00000000, 0x0000080D, 0x0043FD00, 0x00000000, 0x00000000, 0x11320000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007F9, 0x0043FD00, 0x00000000, 0x00000000,
        0x111E0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E5, 0x0043FD00, 0x00000000,
        0x00000000, 0x11090000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940001, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x40],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D3, 0x0043FD00, 0x00000000, 0x00000000, 0x10F40000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D3, 0x0043FD00, 0x00000000, 0x00000000, 0x10F40001, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D3, 0x0043FD00, 0x00000000, 0x00000000, 0x10F40002, 0x00010000,
        0x00024010, 0x003C0000, 0x00000000, 0x0000080F, 0x0043FD00, 0x00000000, 0x00000000, 0x11300000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007F8, 0x0043FD00, 0x00000000, 0x00000000,
        0x111C0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E6, 0x0043FD00, 0x00000000,
        0x00000000, 0x110A0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940002, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x50],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0001, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0002, 0x00010000,
        0x00024010, 0x003C0000, 0x00000000, 0x0000080E, 0x0043FD00, 0x00000000, 0x00000000, 0x11340000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007FC, 0x0043FD00, 0x00000000, 0x00000000,
        0x11200000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E7, 0x0043FD00, 0x00000000,
        0x00000000, 0x110B0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940003, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x60],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0003, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0004, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D4, 0x0043FD00, 0x00000000, 0x00000000, 0x10FE0005, 0x00010000,
        0x00024010, 0x003C0000, 0x00000000, 0x0000080C, 0x0043FD00, 0x00000000, 0x00000000, 0x11330000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007FB, 0x0043FD00, 0x00000000, 0x00000000,
        0x111F0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E8, 0x0043FD00, 0x00000000,
        0x00000000, 0x110C0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00,
        0x00000000, 0x00000000, 0x11940004, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x70],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00750000, 0x00000000,
        0x00000810, 0x0043FD00, 0x00000000, 0x00000000, 0x11310000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007FA, 0x0043FD00, 0x00000000, 0x00000000, 0x111D0000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007E9, 0x0043FD00, 0x00000000, 0x00000000, 0x110D0000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043FD00, 0x00000000, 0x00000000, 0x11940005,
        0x00000000, 0x00010081, 0x0000001E, 0x00000000, (unsigned int)&g_redBloodScoreText[0xC0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Multi_CreateMenuWithDefaultMusicGain_Objectdata,
        0x00000000, 0x00451450, 0x00310000, (unsigned int)addrLow_Multi_EmptyItemHook_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00300000,
        0x00000000, 0x00452544, 0x27A50020, 0x3C07800C, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01,
        0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00451B60, 0x00010000, 0x00444310,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00090000, 0x00000000, 0x00452194, 0x00451B60, 0x00010000,
        (unsigned int)addrLow_Items_PrepareControllerReturn_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00090000, 0x00000000, 0x00000000, 0x02803821,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x20], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus_Objectdata,
        0x00000000, 0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite_Objectdata,
        0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer_Objectdata, 0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385,
        (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01,
        (unsigned int)&g_fragTagOnLabelText[0xA0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus_Objectdata, 0x00000000, 0x00000000, 0x00010000, 0x20010001, 0xFFEC0000,
        0xEC000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite_Objectdata, 0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer_Objectdata, 0x00000000, 0x00010000, 0x50000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x120], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus_Objectdata, 0x00000000, 0x00000000,
        0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite_Objectdata, 0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer_Objectdata,
        0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x1A0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Player_FormatPlayerPartnerStatus_Objectdata, 0x00000000, 0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D,
        (unsigned int)addrLow_Player_DrawPulsingMenuSprite_Objectdata, 0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer_Objectdata, 0x00000000, 0x00451BD0, 0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay_Objectdata, 0x00020000, 0x00000000, 0x00000000, 0x00451C3C, 0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay_Objectdata, 0x00020000, 0x00000000, 0x00000000, 0x00451CA8, 0x00030000,
        (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay_Objectdata, 0x00020000, 0x00000000, 0x00000000, 0x00451D14,
        0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay_Objectdata, 0x00020000, 0x00000000, 0x00000000,
        0x00451BD0, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x000E0000, 0x00000000,
        0x00000000, 0x00451C3C, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x000E0000,
        0x00000000, 0x00000000, 0x00451CA8, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000,
        0x000E0000, 0x00000000, 0x00000000, 0x00451D14, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu,
        0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00451BD0, 0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu_Objectdata, 0x00000000,
        (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00451C3C, 0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00451CA8, 0x00030000,
        (unsigned int)addrLow_Player_ConfigureControllerPakMenu_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00451D14,
        0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x000E0000, 0x00000000, 0x00000000,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x4A0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00400041, 0x0000002A, 0x0000FF01, (unsigned int)g_sceneMaskLabelTables[0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Items_SelectSceneMaskText_Objectdata, (unsigned int)addrLow_Items_CycleSceneMask_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionControlTypeExpertText,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectPlayerOption7BText_Objectdata, (unsigned int)addrLow_Items_AdjustPlayerOption7B_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_playerOptionControlSideLeftText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectPlayerOption7CText_Objectdata, (unsigned int)addrLow_Items_AdjustPlayerOption7C_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_playerOptionLookSpringOnText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectPlayerOption7DText_Objectdata, (unsigned int)addrLow_Items_AdjustPlayerOption7D_Objectdata, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_playerOptionAutoAimOffText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectPlayerOption7EText_Objectdata, (unsigned int)addrLow_Items_AdjustPlayerOption7E_Objectdata, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_bloodColorOffText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectFirstListModeText_Objectdata, (unsigned int)addrLow_Items_AdjustFirstListMode_Objectdata, 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_gameOptionSplitScreenLayoutHorizontalText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectGameOption1FText_Objectdata, (unsigned int)addrLow_Items_AdjustGameOption1F_Objectdata,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_packedGameOptionValueText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_FormatPackedGameOption_Objectdata,
        (unsigned int)addrLow_Items_AdjustPackedGameOption_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionStickHorizontalStepText_eu, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        (unsigned int)addrLow_Items_FormatPlayerOption79Step_Objectdata, (unsigned int)addrLow_Items_AdjustPlayerOption79_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionStickVerticalStepText_eu,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_FormatPlayerOption7AStep_Objectdata, (unsigned int)addrLow_Items_AdjustPlayerOption7A_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_weaponSelectNormalText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_SelectPlayerFlag82Text_Objectdata, (unsigned int)addrLow_Items_TogglePlayerFlag82_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_frontendScreenModePaletteDefault, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Items_UpdateScreenModeMenuItem_Objectdata, (unsigned int)addrLow_Items_RequestScreenModeFade_Objectdata, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_packedButtonOptionStepTextTableEu, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_FormatPackedButtonOption_Objectdata, (unsigned int)addrLow_Pak_AdjustPackedButtonOption_Objectdata, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, (unsigned int)&g_languageMenuAlternateTextTable, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_CItemValue_BindItemValueField, (unsigned int)addrLow_Items_AdjustLanguage_Objectdata, 0x00000000,
        0x00000000, 0x00010201, 0x00000013, 0x0000FF01, (unsigned int)&g_languageMenuAlternateTextTable + 0x10, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu_Objectdata,
        0x00000000, 0x00451F30, 0x00110000, (unsigned int)addrLow_Items_ResetScreenModeFadeCooldown_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00100000,
        0x00000000, 0x00000000, 0x80420013, 0x44820000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01,
        0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x00000008,
        0x0000FF01, (unsigned int)&g_redBloodScoreText[0xA0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000101,
        0x0000005D, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x10, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010101, 0x0000000A, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Pak_StopMusicAndResetMatch_Objectdata, 0x00000000,
        0x00000000, 0x00010101, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x40, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu_Objectdata,
        0x00000000, 0x004521C0, 0x00050000, (unsigned int)addrLow_Pak_SetRecordType_Objectdata, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00040000,
        0x00000000, 0x00452544, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08002001, 0x00000008, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x4E0,
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00410041, 0x00000032, 0x0000FF01,
        (unsigned int)g_volumeZeroValueLabels, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_UpdateFirstVolumeLabel_Objectdata, (unsigned int)addrLow_Pak_AdjustVolumeSlotZero_Objectdata, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_sfxVolumeText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_FormatSfxVolume_Objectdata, (unsigned int)addrLow_Pak_AdjustSfxVolume_Objectdata, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_speechVolumeText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_UpdateThirdVolumeLabel_Objectdata, (unsigned int)addrLow_Pak_AdjustThirdVolume_Objectdata, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_musicPreviewFixedValueText, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, (unsigned int)addrLow_Pak_FormatMusicPreview_Objectdata, (unsigned int)addrLow_Pak_SelectMusicPreview_Objectdata, 0x00000000,
        0x00000000, 0x00410401, 0x00000044, 0x0000FF01, (unsigned int)&g_languageMenuAlternateTextTable + 0x10, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Pak_RestoreAudioAndCloseMenu_Objectdata,
        0x00000000, 0x00452298, 0x00070000, 0x00000000, 0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, 0x00000000, 0x00020000,
        0x00000000, 0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)g_Menu_DrawMenuOptionSpritePackedAddress_eu,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x00000008, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x20],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000028, 0x0000FF01,
        (unsigned int)&g_redBloodScoreText[0x30], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Pak_ResumeMenuAudio_Objectdata, 0x00000000, 0x00000000, 0x00010041, 0x00000000,
        0x0000FF01, (unsigned int)&g_redBloodScoreText[0x40], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_Pak_ReturnCallbackSuccess_Objectdata, 0x00000000, 0x00000000, 0x00010041,
        0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x50], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_pakAllocateMenuSlotHandlers_[0], 0x00000000, 0x00000000,
        0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x60], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_pakAllocateMenuSlotHandlers_[1], 0x00000000,
        0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x80], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_pakAllocateMenuSlotHandlers_[2],
        0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_playerNameSuffixByLanguage + 0x4E0, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000,
        (unsigned int)addrLow_Pak_OpenMusicPreviewMenu_Objectdata, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x80, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu,
        0x00000000, (unsigned int)addrLow_pakAllocateMenuSlotHandlers_[3], 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x90],
        (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_pakAllocateMenuSlotHandlers_[4], 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        (unsigned int)&g_redBloodScoreText[0xA0], (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, (unsigned int)addrLow_pakAllocateMenuSlotHandlers_[5], 0x00000000, 0x004523B8, 0x000B0000, (unsigned int)addrLow_Pak_EnterPlayerOptions_Objectdata,
        (unsigned int)addrLow_Pak_RestoreControllerSetup_Objectdata, (unsigned int)addrLow_Pak_RenderMenuEntryCallback_Objectdata, 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x06210002, 0x00572004,
        0x00000000, 0x00000041, 0x00000000, 0x0000FF01, (unsigned int)g_pakStatusTelsetTexts + 0x50, (unsigned int)g_Menu_DrawMenuItemLabelPackedAddress_eu, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xB4], (unsigned int)addrLow_Setup_DrawNameCursor_Objectdata, (unsigned int)addrLow_Setup_UpdateNameCursor_Objectdata,
        0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xC4], (unsigned int)addrLow_Setup_DrawNameCursor_Objectdata,
        (unsigned int)addrLow_Setup_UpdateNameCursor_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xD4],
        (unsigned int)addrLow_Setup_DrawNameCursor_Objectdata, (unsigned int)addrLow_Setup_UpdateNameCursor_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01,
        (unsigned int)&g_multiplayerSavedPlayerNames[0xE4], (unsigned int)addrLow_Setup_DrawNameCursor_Objectdata, (unsigned int)addrLow_Setup_UpdateNameCursor_Objectdata, 0x00000000, 0x00000000, 0x00000000, 0x00010110, 0x0000000A,
        0x07012008, (unsigned int)g_creditsLocalizedLines + 0x14, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x28, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x3C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x50, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x64, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x78, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x8C,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF92008,
        (unsigned int)g_creditsLocalizedLines + 0xA0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, (unsigned int)g_creditsLocalizedLines + 0xB4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xC8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xDC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xF0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x104, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x118, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x12C,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        (unsigned int)g_creditsLocalizedLines + 0x140, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, (unsigned int)g_creditsLocalizedLines + 0x154, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x168, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x17C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x190, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x1A4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x1B8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x1CC,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        (unsigned int)g_creditsLocalizedLines + 0x1E0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, (unsigned int)g_creditsLocalizedLines + 0x1F4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x208, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x21C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x230, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x244, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x258, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x26C,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        (unsigned int)g_creditsLocalizedLines + 0x280, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F8E0, (unsigned int)g_creditsLocalizedLines + 0x294, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x2A8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x2BC, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x2D0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000,
        (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x2E4, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata,
        0x00000000, (unsigned int)addrLow_Setup_AppendNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x2F8,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_DeleteNameCharacter_Objectdata, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F8E0,
        (unsigned int)g_creditsLocalizedLines + 0x30C, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText_Objectdata, 0x00000000, (unsigned int)addrLow_Setup_CommitPlayerName_Objectdata, 0x00000000, 0x00452570, 0x002D0000, (unsigned int)addrLow_Setup_SetupNameSpinner_Objectdata,
        0x00000000, (unsigned int)g_Menu_DrawMenuEntriesPackedAddress_eu, (unsigned int)addrLow_Setup_HasActiveGameCounters_Objectdata, 0x00050000, 0x00000000, 0x00000000, 0x01210821, 0x8C26B434,
    },
};
#endif

#if defined(VERSION_DE)
struct {
    unsigned int words0[1733];
    float floats1[1];
    unsigned int words2[1];
    char text3[4];
    unsigned int words4[1819];
} k_ObjectdataEncodedWords = {
    {
        (unsigned int)&g_pakProfileGameNameFixed, 0x00442024, (unsigned int)g_Timer_UpdateOwnerChannelLabelEncodedCallback, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385,
        PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x0000000A, 0x0000FF01,
        (unsigned int)g_pakOwnerChannelLabelFixed, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), (unsigned int)g_Timer_UpdateOwnerChannelLabelEncodedCallback, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000FFF8,
        0x0000FF01, (unsigned int)g_pakProfileLoadProfileChoiceLabels, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), (unsigned int)g_Timer_UpdateOperationChoiceLabelEncodedCallback, 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000006, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x4, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x8, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0xC, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote),
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x10, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel),
        PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x14, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x18,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        (unsigned int)g_pakOwnerChannelLabelFixed + 0x1C, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x20, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x24, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x28, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x2C, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote),
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x30, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel),
        PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x34, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x38,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        (unsigned int)g_pakOwnerChannelLabelFixed + 0x3C, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x40, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001,
        0x00000003, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateSpaceLabel), 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x0000000A, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_UpdateManagerChannelLabel), PACKED_CALLBACK_LOW(Snapshot_HandleMenuAction), 0x00000000,
        0x00000000, 0x00010041, 0x00000004, 0x0000FF01, (unsigned int)g_pakSaveMenuSnapshotChoiceLabels + 0x4, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_SetManagerHeading), PACKED_CALLBACK_LOW(Snapshot_CloseNoteBrowser),
        0x00000000, 0x0044E150, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_BeginProfileLoad), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Timer_CheckMenuPakChange), 0x00150000,
        0x00000000, 0x00000000, 0x0044E150, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_BeginProfileSave), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Timer_CheckMenuPakChange),
        0x00140000, 0x00000000, 0x00000000, 0x0044E150, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_BeginBlockLoad), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries),
        PACKED_CALLBACK_LOW(Timer_CheckChangedMenuChannel), 0x00150000, 0x00000000, 0x00000000, 0x0044E150, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_BeginSnapshotSave), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Timer_CheckChangedMenuChannel), 0x00140000, 0x00000000, 0x00000000, 0x0044E150, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_CheckControllerPak),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Timer_UpdateManagerStatus), 0x00140000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_pakNoteLabelSlots, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_UpdateAlternatePromptLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000014, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_DispatchPreviewHandle), 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_difficultyHardText + 0xC, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_FormatPreviewDottedTriple),
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000000A, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Timer_UpdatePreviewDepthLabel), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_difficultyHardText + 0x4,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_FormatPreviewPageCount), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        (unsigned int)g_difficultyHardText + 0x8, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_FormatPreviewValue), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014,
        0x0000FF01, (unsigned int)g_pakAlternateActionLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_UpdateAlternateActionLabel), 0x00000000, 0x00000000, 0x00000000, 0x00010040,
        0x007D000A, 0x00010000, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00408870, 0x00000000, 0x00000000,
        0x00024040, 0x000A0000, 0xFF000000, (unsigned int)g_captureFlagVictimFollowupMessage + 0x10, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Timer_OpenSelectedPrompt), 0x00000000,
        0x0044E51C, 0x000A0000, PACKED_CALLBACK_LOW(Timer_EnableAlternatePrompt), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00080000, 0x00000000,
        0x00000000, 0x0044E51C, 0x000A0000, PACKED_CALLBACK_LOW(Timer_DisableAlternatePrompt), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00090000,
        0x00000000, 0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite),
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_pakPreviewKindLabelProfile,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Timer_UpdatePreviewKindLabel), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000032, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Menu_FormatRightAlignedName), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000002,
        0x0000FF01, (unsigned int)&g_pakDefaultPreviewTypeLabel + 0x8, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Menu_FormatNoteTypeLabel), 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000002, 0x0000FF01, (unsigned int)&g_pakDefaultPreviewTypeLabel + 0xC, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_FormatPreviewFourDigitValue), 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x00000002, 0x0000FF01, (unsigned int)&g_pakDefaultPreviewTypeLabel + 0x10, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Snapshot_UpdateThresholdLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000010, 0x0000FF01, (unsigned int)g_pakAlternateActionLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_UpdateProfileActionLabel), 0x00000000,
        0x00000000, 0x00000000, 0x00010040, 0x007D000A, 0x00010000, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000,
        PACKED_CALLBACK_LOW(Pak_ConfirmProfileOrDeleteNote), 0x00000000, 0x00000000, 0x00024040, 0x000A0000, 0xFF000000, (unsigned int)g_captureFlagVictimFollowupMessage + 0x10, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, PACKED_CALLBACK_LOW(Pak_OpenProfileActionPrompt), 0x00000000, 0x0044E6CC, 0x00090000, PACKED_CALLBACK_LOW(Timer_EnableProfilePreview), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries),
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E6CC, 0x00090000, PACKED_CALLBACK_LOW(Timer_ClearProfilePreview), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x0044E6CC, 0x00090000, PACKED_CALLBACK_LOW(Timer_DisablePreviewSelection),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_SelectPromptActionHeading), 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x0000001E, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupOne), 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupTwo),
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupThree), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupFour), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupFive), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000019,
        0x0000FF01, (unsigned int)g_SelectModalPromptLabelStateOtherText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_SelectModalPromptLabel), PACKED_CALLBACK_LOW(Pak_ClosePromptByKind), 0x00000000, 0x0044E87C, 0x00080000,
        PACKED_CALLBACK_LOW(Pak_SelectPromptKindZero), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C,
        0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindOne), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindTwo), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindThree), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindFour), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindFive), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries),
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindSix), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindSeven),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000,
        PACKED_CALLBACK_LOW(Pak_SelectPromptKindEight), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C,
        0x00080000, PACKED_CALLBACK_LOW(Pak_SelectProfilePrompt), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectProfilePromptWithSavePending), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindTen), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindEleven), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindTwelve), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries),
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindFifteen), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindThirteen),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E87C, 0x00080000,
        PACKED_CALLBACK_LOW(Pak_SelectPromptKindFourteen), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x00010000,
        0x90000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)&g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][4][0x4], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000028, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_SelectOperationHeading),
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Pak_SelectOperationDescription), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_FormatOperationChannelLabel), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014, 0x0000FF01,
        (unsigned int)&g_pakChannelLabelTexts + 0x4, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_OpenPakChannel), 0x00000000, 0x00000000, 0x00010041, 0x00000005,
        0x0000FF01, (unsigned int)&g_pakChannelLabelTexts + 0x8, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_OpenPakStatusPrompt), 0x00000000, 0x00000000, 0x00010041,
        0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_SelectPakLoadHeading), PACKED_CALLBACK_LOW(Pak_CancelPakAction), 0x00000000, 0x0044EC00,
        0x00080000, PACKED_CALLBACK_LOW(Pak_EnableOperationHeading), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Pak_CheckOperationPakChange), 0x00070000, 0x00000000, 0x00000000,
        0x0044EC00, 0x00080000, PACKED_CALLBACK_LOW(Pak_DisableOperationHeading), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Pak_CheckOperationPakChange), 0x00050000, 0x00000000,
        0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Pak_SelectPakOperationTextOne), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000023, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Frontend_SelectPakOperationTextTwo), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Frontend_SelectPakOperationTextThree), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004,
        0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Frontend_SelectPakOperationTextFour), 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000004, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Frontend_SelectPakOperationTextFive), 0x00000000, 0x00000000, 0x00000000,
        0x00012001, 0x00000023, 0x0000FF01, (unsigned int)g_pakConfirmationDefaultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Frontend_SelectPakConfirmationLabel), PACKED_CALLBACK_LOW(Pak_ConfirmPendingOperation), 0x00000000,
        0x00000000, 0x00012001, 0x00000005, 0x0000FF01, (unsigned int)s_nodeDefaultFieldText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Menu_SelectPakOperationActionLabel), PACKED_CALLBACK_LOW(Timer_CancelPendingOperation),
        0x00000000, 0x0044ED68, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationZero), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Pak_CheckPakActionChange), 0x00070000,
        0x00000000, 0x00000000, 0x0044ED68, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationOne), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Pak_CheckPakActionChange),
        0x00070000, 0x00000000, 0x00000000, 0x0044ED68, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationTwo), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries),
        PACKED_CALLBACK_LOW(Pak_CheckPakActionChange), 0x00070000, 0x00000000, 0x00000000, 0x0044ED68, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationThree), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Pak_CheckPakActionChange), 0x00070000, 0x00000000, 0x00000000, 0x0044ED68, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationFour),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Pak_CheckPakActionChange), 0x00070000, 0x00000000, 0x00000000, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0xA8,
        (unsigned int)&g_optionFlagsChangedMessageText + 0x18, 0x00000020, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x98, (unsigned int)&g_optionFlagsChangedMessageText + 0x20, 0x00000080, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x90,
        (unsigned int)&g_optionFlagsChangedMessageText + 0x24, 0x00000100, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x84, (unsigned int)&g_optionFlagsChangedMessageText + 0x1C, 0x00000040, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x78,
        (unsigned int)&g_optionFlagsChangedMessageText + 0x28, 0x00000200, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x64, (unsigned int)&g_optionFlagsChangedMessageText + 0x2C, 0x00000400, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x58,
        (unsigned int)&g_optionFlagsChangedMessageText + 0x30, 0x00000800, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x50, (unsigned int)&g_optionFlagsChangedMessageText + 0x34, 0x00001000, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x44,
        (unsigned int)&g_optionFlagsChangedMessageText + 0x3C, 0x00004000, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x38, (unsigned int)&g_optionFlagsChangedMessageText + 0x40, 0x00008000, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0x20,
        (unsigned int)&g_encodedCheatCode[0x30], 0xFFFFFFFF, 0x00000001, (unsigned int)g_encodedCheatTextWords + 0xC, (unsigned int)&g_encodedCheatCode[0x4C], 0x0400C7E0, 0x00000001, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x20, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00210041, 0x00000014, 0x0000FF01, (unsigned int)&g_encodedCheatCode[0x18], PACKED_CALLBACK_LOW(Encoded_DrawTextEntryCursor), PACKED_CALLBACK_LOW(Encoded_UpdateTextEntryCursor),
        PACKED_CALLBACK_LOW(Encoded_TextEntryReturnZero), 0x00000000, 0x00000000, 0x00010050, 0x00580014, 0x0601FF07, (unsigned int)g_creditsLocalizedLines + 0x8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FE07, (unsigned int)g_creditsLocalizedLines + 0x10,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FD07,
        (unsigned int)g_creditsLocalizedLines + 0x18, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01FC07, (unsigned int)g_creditsLocalizedLines + 0x20, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01FB07, (unsigned int)g_creditsLocalizedLines + 0x28, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFF01FA07, (unsigned int)g_creditsLocalizedLines + 0x30, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0x38, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter),
        0x00000000, 0x00000000, 0x00010050, 0x00580008, 0x0601F907, (unsigned int)g_creditsLocalizedLines + 0x40, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000,
        PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x48, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x50,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        (unsigned int)g_creditsLocalizedLines + 0x58, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x60, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x68, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0x70, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000,
        0x00000000, 0x00010050, 0x00580008, 0x0601F907, (unsigned int)g_creditsLocalizedLines + 0x78, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter),
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x80, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000,
        PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x88, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x90,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        (unsigned int)g_creditsLocalizedLines + 0x98, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0xA0, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0xA8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000,
        0x00010050, 0x00580008, 0x0601F908, (unsigned int)g_creditsLocalizedLines + 0xB0, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0xB8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter),
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F906, (unsigned int)g_creditsLocalizedLines + 0xC0, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000,
        PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F905, (unsigned int)g_creditsLocalizedLines + 0xC8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F904, (unsigned int)g_creditsLocalizedLines + 0xD0,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_InsertTextEntryCharacter), 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F903,
        (unsigned int)g_creditsLocalizedLines + 0x130, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, (unsigned int)addrLow_Frontend_SelectPreviousEquipmentChoice2, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFFFAF902, (unsigned int)g_creditsLocalizedLines + 0x138, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Encoded_ApplyCheatCode), 0x00000000, 0x00000000, 0x00011001,
        0x00000014, 0x00000000, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Encoded_SetTextEntryResultLabel), 0x00000000, 0x00000000, 0x00000000,
        0x00310201, 0x00000018, 0x0000FEE2, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Menu_TryCreateMenu), 0x00000000,
        0x0044F000, 0x00210000, PACKED_CALLBACK_LOW(Encoded_ResetTextEntryResult), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x14, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00411001, 0x0000000C, 0x0000FF01, (unsigned int)g_menuOptionInvincibilityDisabledText,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionInvincibilityItem), PACKED_CALLBACK_LOW(Pak_ToggleTextChoice), 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        (unsigned int)g_menuOptionInfiniteLivesDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionInfiniteLivesItem), PACKED_CALLBACK_LOW(Option_ToggleOptionInfiniteLives), 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, (unsigned int)g_menuOptionAllWeaponsDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionAllWeaponsItem), PACKED_CALLBACK_LOW(Option_ToggleOptionAllWeapons), 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, (unsigned int)g_menuOptionUnlimitedAmmoDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionUnlimitedAmmoItem), PACKED_CALLBACK_LOW(Option_ToggleOptionUnlimitedAmmo), 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionAllSpecialObjectsDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionAllSpecialObjectsItem), PACKED_CALLBACK_LOW(Option_ToggleOptionAllSpecialObjects), 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBigHeadModeDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionBigHeadModeItem), PACKED_CALLBACK_LOW(Option_ToggleOptionBigHeadMode),
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionTinyModeDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionTinyModeItem),
        PACKED_CALLBACK_LOW(Option_ToggleOptionTinyMode), 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBigHandsFeetModeDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Option_UpdateOptionBigHandsFeetModeItem), PACKED_CALLBACK_LOW(Option_ToggleOptionBigHandsFeetMode), 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionStickModeDisabledText,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionStickModeItem), PACKED_CALLBACK_LOW(Option_ToggleOptionStickMode), 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        (unsigned int)g_menuOptionPenAndInkModeDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionPenAndInkModeItem), PACKED_CALLBACK_LOW(Option_ToggleOptionPenAndInkMode), 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, (unsigned int)g_menuOptionGouraudModeDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionGouraudModeItem), PACKED_CALLBACK_LOW(Option_ToggleOptionGouraudMode), 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, (unsigned int)g_menuOptionJuansCheatDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionJuansCheatItem), PACKED_CALLBACK_LOW(Option_ToggleOptionJuansCheat), 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionZachAttackCheatDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionZachAttackCheatItem), PACKED_CALLBACK_LOW(Option_ToggleOptionZachAttackCheat), 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionAllMapDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionAllMapItem), PACKED_CALLBACK_LOW(Option_ToggleOptionAllMap),
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBlackoutDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Option_UpdateOptionBlackoutItem),
        PACKED_CALLBACK_LOW(Option_ToggleOptionBlackout), 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionFrootyStripesDisabledText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Option_UpdateOptionFrootyStripesItem), PACKED_CALLBACK_LOW(Option_ToggleOptionFrootyStripes), 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Menu_SetSelectedLevelLabel), PACKED_CALLBACK_LOW(Encoded_HandleUnlockedLevelSelection), 0x00000000, 0x00000000, 0x00000201, 0x000000C0, 0x0000FF01,
        (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Menu_TryCreateMenu), 0x00000000, 0x0044F4C8, 0x00140000, 0x0043C550,
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00130000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000021, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x34, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00010081, 0x00000028, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Menu_ForwardRulesLock),
        0x00000000, 0x00000000, 0x00010081, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x10, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_HandleSessionOptionPage), 0x00000000, 0x0044F7C0, 0x00030000, 0x00000000, 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0xC],
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000,
        (unsigned int)&g_profileMenuLabelWords[0x10], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x00000000, (unsigned int)&g_profileMenuLabelWords[0x14], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x18], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x1C], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x20], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x24], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x28], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x8],
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(CMenuProfile_ResetPlayerControllerProfile), 0x00000000, 0x0044F850, 0x00090000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(CMenuProfile_HasRoundProgress), 0x00080000, 0x00000000, 0x0044FA6C, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF02, (unsigned int)&g_packedButtonOptionStepText[0x14], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(CMenuProfile_OpenPrimaryProfileMenu), 0x00000000, 0x00000000, 0x00010101,
        0x00000008, 0x00000000, (unsigned int)&g_packedButtonOptionStepText[0x18], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(CMenuProfile_BindSelectedDebugField), 0x00000000, 0x00000000, 0x00000000,
        0x00411001, 0x00000008, 0x0000FE01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(CMenuProfile_FormatProfileQuantityLabel), PACKED_CALLBACK_LOW(CMenuProfile_AdjustControllerSelection), 0x00000000,
        0x00000000, 0x00411001, 0x00000002, 0x0000FF01, (unsigned int)g_profileModeZeroLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(CMenuProfile_UpdateProfileModeLabel), PACKED_CALLBACK_LOW(CMenuProfile_ToggleProfileMode),
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0x8], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000,
        PACKED_CALLBACK_LOW(CMenuProfile_OpenSecondaryProfileMenu), 0x00000000, 0x0044F9B8, 0x00050000, 0x00000000, 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(CMenuProfile_HasSavedRoundProgress),
        0x00040000, 0x00000000, 0x0044FB2C, 0x00000460, 0x0000000B, 0x00000000, 0x00000000, 0xC2480000,
        0xC4610000, 0x40000000, 0x40000000, 0x40000000, 0x00000032, 0x00000050, 0x3DB2B8C4, 0x00010000,
        0x30000000, 0x00000000, 0x0000FF01, 0x00000387, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000,
        0x00030000, 0x00410021, 0x00000000, 0x0000FF01, 0x0044FA90, PACKED_CALLBACK_LOW(Menu_DrawMenuModel), PACKED_CALLBACK_LOW(CMenuProfile_GameSpeedReturnZero), PACKED_CALLBACK_LOW(Items_HandleCharacterPreviewSelectionGerman),
        0x00000000, 0x00000000, 0x00010081, 0x00000019, 0x0000FF01, (unsigned int)&g_packedButtonOptionStepText[0x10], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(CMenuProfile_ProfileModeReturnZero),
        PACKED_CALLBACK_LOW(CMenuProfile_OpenTimedPlayerDialog), 0x00000000, 0x0044FAC0, 0x00030000, PACKED_CALLBACK_LOW(CMenuProfile_EnableOwnerControllerPak), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(CMenuProfile_HasProfileRoundProgress),
        0x00010000, 0x00000000, 0x00000000, 0x0044FAC0, 0x00030000, PACKED_CALLBACK_LOW(CMenuProfile_EnableControllerPakAndClearState), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries),
        PACKED_CALLBACK_LOW(CMenuProfile_HasProfileRoundProgress), 0x00010000, 0x00000000, 0x00000000, 0x00010000, 0x30000000, 0x00000000, 0x0000FF01,
        0x00000387, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000000,
        0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0x2C], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010101,
        0x0000000C, 0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0x30], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(CMenuProfile_OpenPrimaryPlayerDialog), 0x00000000, 0x00000000,
        0x00010101, 0x00000000, 0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0x34], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(CMenuProfile_OpenAlternatePlayerDialog), 0x00000000,
        0x0044FB74, 0x00040000, 0x00000000, 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(CMenuProfile_HasDialogRoundProgress), 0x00020000, 0x00000000,
        0x00000000, 0xBF000000, 0xBECCCCCD, 0xBE99999A, 0xBE4CCCCD, 0xBDCCCCCD, 0x00000000, 0x3DCCCCCD,
        0x3E4CCCCD, 0x3E99999A, 0x3ECCCCCD, 0x3F000000, 0x3F19999A, 0x3F333333, 0x3F4CCCCD, 0x3F666666,
    },
    { 0.7f },
    {
        0x3F4CCCCD, 0x3F666666, 0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385,
    },
    "\?fff",
    {
        0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000201, 0x0000000C, 0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0xC0, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00410041, 0x0000001E, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectToggleRowTextGerman), (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectToggleRowTextGerman), (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectToggleRowTextGerman), (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectToggleRowTextGerman), (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectToggleRowTextGerman), (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectToggleRowTextGerman), (unsigned int)g_initial_ToggleMenuRowOptionEntry,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectToggleRowTextGerman),
        (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Items_SelectToggleRowTextGerman), (unsigned int)g_initial_ToggleMenuRowOptionEntry, 0x00000000, 0x00000000, 0x00010201, 0x0000002D, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Menu_TryCreateMenu), 0x00000000, 0x0044FC68, 0x000B0000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x000A0000, 0x00000000, 0x0044FEA8, 0x00010000, 0x10000000, 0x00000000,
        0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000801,
        0x00000008, 0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0x14, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010081, 0x00000000, 0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0xC0, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Initial_OpenMatchSetupMenu), 0x00000000,
        0x00000000, 0x00010201, 0x00000038, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Menu_TryCreateMenu),
        0x00000000, 0x0044FE18, 0x00040000, 0x00000000, 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00020000,
        0x00000000, 0x0045010C, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite),
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0x4,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000036, 0x0000FF01,
        (unsigned int)&g_defaultPlayerNames[3] + 0x8, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak), 0x00000000, 0x00000000, 0x00010081, 0x00000004,
        0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0xC, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Initial_OpenDialogAfterTimerReset), 0x00000000, 0x00000000, 0x00010201,
        0x00000049, 0x0000FF01, (unsigned int)&g_packedButtonOptionStepText[0x8], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Initial_RequestTransitionWithPakDisabled), 0x00000000, 0x0044FECC,
        0x00050000, PACKED_CALLBACK_LOW(Initial_ProbeMenuControllerPak), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00020000, 0x00000000, 0x00000000,
        0x0044FECC, 0x00050000, PACKED_CALLBACK_LOW(Initial_EnableMenuControllerPak), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000,
        0x00000000, 0x00000000, 0x0044FFC8, 0x00010000, 0x00000000, 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000,
        0x00020000, 0x00000000, 0x0045010C, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000384,
        PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000081, 0x0000001E, 0x0000FF01,
        (unsigned int)&g_defaultPlayerNames[3] + 0x4, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Initial_SelectInitialController), 0x00000000, 0x00000000, 0x00010081, 0x0000000C,
        0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0x10, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Initial_UpdateMultiplayerAvailability), PACKED_CALLBACK_LOW(Initial_OpenLocalPlayerSetup), 0x00000000, 0x00000000, 0x00010081,
        0x0000000C, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x20, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Initial_OpenDialogTopRow), 0x00000000, 0x00000000,
        0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x2C, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Initial_OpenDialogMiddleRow), 0x00000000,
        0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x28, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Initial_OpenDialogBottomRow),
        0x00000000, 0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x38, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000,
        PACKED_CALLBACK_LOW(Initial_OpenTrackPreviewMenu), 0x00000000, 0x00450010, 0x00070000, 0x00000000, 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00000064,
        PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000089, 0x00000028, 0x00000000,
        (unsigned int)g_creditsLocalizedLines + 0x140, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Multi_DecreaseGameOverTimer), 0x00000000, 0x00000000, 0x00450130, 0x00020000, PACKED_CALLBACK_LOW(Items_ResetGameOverTimer),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Multi_CompleteGameOverDelay), 0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x2C], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00010080, 0x00230016, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x8], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000,
        0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D0, 0x0043EE60,
        0x00000000, 0x00000000, 0x10D60000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D0,
        0x0043EE60, 0x00000000, 0x00000000, 0x10D60001, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D0, 0x0043EE60, 0x00000000, 0x00000000, 0x10D60002, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D1, 0x0043EE60, 0x00000000, 0x00000000, 0x10E00000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x000007D1, 0x0043EE60, 0x00000000, 0x00000000, 0x10E00001, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007D1, 0x0043EE60, 0x00000000, 0x00000000, 0x10E00002,
        0x00010000, 0x00024010, 0x00290000, 0x00000000, 0x000007E4, 0x0043EE60, 0x00000000, 0x00000000,
        0x11080000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940000, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0xC], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D2,
        0x0043EE60, 0x00000000, 0x00000000, 0x10EA0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D2, 0x0043EE60, 0x00000000, 0x00000000, 0x10EA0001, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D2, 0x0043EE60, 0x00000000, 0x00000000, 0x10EA0002, 0x00010000, 0x00024010,
        0x003C0000, 0x00000000, 0x0000080D, 0x0043EE60, 0x00000000, 0x00000000, 0x11320000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007F9, 0x0043EE60, 0x00000000, 0x00000000, 0x111E0000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E5, 0x0043EE60, 0x00000000, 0x00000000,
        0x11090000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940001, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x10], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D3,
        0x0043EE60, 0x00000000, 0x00000000, 0x10F40000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D3, 0x0043EE60, 0x00000000, 0x00000000, 0x10F40001, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D3, 0x0043EE60, 0x00000000, 0x00000000, 0x10F40002, 0x00010000, 0x00024010,
        0x003C0000, 0x00000000, 0x0000080F, 0x0043EE60, 0x00000000, 0x00000000, 0x11300000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007F8, 0x0043EE60, 0x00000000, 0x00000000, 0x111C0000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E6, 0x0043EE60, 0x00000000, 0x00000000,
        0x110A0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940002, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x14], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4,
        0x0043EE60, 0x00000000, 0x00000000, 0x10FE0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D4, 0x0043EE60, 0x00000000, 0x00000000, 0x10FE0001, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D4, 0x0043EE60, 0x00000000, 0x00000000, 0x10FE0002, 0x00010000, 0x00024010,
        0x003C0000, 0x00000000, 0x0000080E, 0x0043EE60, 0x00000000, 0x00000000, 0x11340000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007FC, 0x0043EE60, 0x00000000, 0x00000000, 0x11200000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E7, 0x0043EE60, 0x00000000, 0x00000000,
        0x110B0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940003, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x18], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4,
        0x0043EE60, 0x00000000, 0x00000000, 0x10FE0003, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D4, 0x0043EE60, 0x00000000, 0x00000000, 0x10FE0004, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007D4, 0x0043EE60, 0x00000000, 0x00000000, 0x10FE0005, 0x00010000, 0x00024010,
        0x003C0000, 0x00000000, 0x0000080C, 0x0043EE60, 0x00000000, 0x00000000, 0x11330000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007FB, 0x0043EE60, 0x00000000, 0x00000000, 0x111F0000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E8, 0x0043EE60, 0x00000000, 0x00000000,
        0x110C0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000,
        0x00000000, 0x11940004, 0x00000000, 0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x1C], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00024010, 0x00750000, 0x00000000, 0x00000810,
        0x0043EE60, 0x00000000, 0x00000000, 0x11310000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007FA, 0x0043EE60, 0x00000000, 0x00000000, 0x111D0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007E9, 0x0043EE60, 0x00000000, 0x00000000, 0x110D0000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x00000820, 0x0043EE60, 0x00000000, 0x00000000, 0x11940005, 0x00000000,
        0x00010081, 0x0000001E, 0x00000000, (unsigned int)&g_redBloodScoreText[0x30], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Multi_CreateMenuWithDefaultMusicGain), 0x00000000,
        0x004501A0, 0x00310000, PACKED_CALLBACK_LOW(Multi_EmptyItemHook), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00300000, 0x00000000,
        0x00451220, 0x00000000, 0x00090000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385,
        PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x004508B0, 0x00010000, PACKED_CALLBACK_LOW(Items_PrepareMenuReturnDe), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00090000, 0x00000000, 0x00450E9C, 0x004508B0, 0x00010000, PACKED_CALLBACK_LOW(Items_PrepareControllerReturn),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00090000, 0x00000000, 0x00000000, 0x004434A0, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x8], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Player_FormatPlayerPartnerStatus), 0x00000000,
        0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, PACKED_CALLBACK_LOW(Player_DrawPulsingMenuSprite), 0x00000000,
        PACKED_CALLBACK_LOW(Player_RespawnItemPlayer), 0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite),
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x28],
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Player_FormatPlayerPartnerStatus), 0x00000000, 0x00000000, 0x00010000, 0x20010001, 0xFFEC0000, 0xEC000001,
        0x0000012D, PACKED_CALLBACK_LOW(Player_DrawPulsingMenuSprite), 0x00000000, PACKED_CALLBACK_LOW(Player_RespawnItemPlayer), 0x00000000, 0x00010000, 0x50000000, 0x00000000,
        0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000401,
        0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x48], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Player_FormatPlayerPartnerStatus), 0x00000000, 0x00000000, 0x00010000,
        0x20010001, 0x00000000, 0x00000001, 0x0000012D, PACKED_CALLBACK_LOW(Player_DrawPulsingMenuSprite), 0x00000000, PACKED_CALLBACK_LOW(Player_RespawnItemPlayer), 0x00000000,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x68], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Player_FormatPlayerPartnerStatus),
        0x00000000, 0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, PACKED_CALLBACK_LOW(Player_DrawPulsingMenuSprite),
        0x00000000, PACKED_CALLBACK_LOW(Player_RespawnItemPlayer), 0x00000000, 0x00450920, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigurePlayerMenuFlags), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries),
        PACKED_CALLBACK_LOW(Player_UpdatePlayerRespawnDelay), 0x00020000, 0x00000000, 0x00000000, 0x0045098C, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigurePlayerMenuFlags), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Player_UpdatePlayerRespawnDelay), 0x00020000, 0x00000000, 0x00000000, 0x004509F8, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigurePlayerMenuFlags),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Player_UpdatePlayerRespawnDelay), 0x00020000, 0x00000000, 0x00000000, 0x00450A64, 0x00030000,
        PACKED_CALLBACK_LOW(Player_ConfigurePlayerMenuFlags), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Player_UpdatePlayerRespawnDelay), 0x00020000, 0x00000000, 0x00000000, 0x00450920,
        0x00030000, PACKED_CALLBACK_LOW(Player_ConfigureAndProbeControllerPak), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x000E0000, 0x00000000, 0x00000000,
        0x0045098C, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigureAndProbeControllerPak), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x000E0000, 0x00000000,
        0x00000000, 0x004509F8, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigureAndProbeControllerPak), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x000E0000,
        0x00000000, 0x00000000, 0x00450A64, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigureAndProbeControllerPak), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000,
        0x000E0000, 0x00000000, 0x00000000, 0x00450920, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigureControllerPakMenu), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries),
        0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x0045098C, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigureControllerPakMenu), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x004509F8, 0x00030000, PACKED_CALLBACK_LOW(Player_ConfigureControllerPakMenu),
        0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00450A64, 0x00030000,
        PACKED_CALLBACK_LOW(Player_ConfigureControllerPakMenu), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x28, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00400041, 0x0000002F, 0x0000FF01, (unsigned int)g_sceneMaskLabelTables[0], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectSceneMaskText),
        PACKED_CALLBACK_LOW(Items_CycleSceneMask), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionControlTypeExpertText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Items_SelectPlayerOptionControlTypeText), PACKED_CALLBACK_LOW(Items_AdjustPlayerOptionControlType), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionControlSideLeftText,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectPlayerOptionControlSideText), PACKED_CALLBACK_LOW(Items_AdjustPlayerOptionControlSide), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_playerOptionLookSpringOnText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectPlayerOptionLookSpringText), PACKED_CALLBACK_LOW(Items_AdjustPlayerOptionLookSpring), 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_playerOptionAutoAimOffText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectPlayerOptionAutoAimText), PACKED_CALLBACK_LOW(Items_AdjustPlayerOptionAutoAim), 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_gameOptionSplitScreenLayoutHorizontalText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_SelectSplitScreenPreferenceText), PACKED_CALLBACK_LOW(Items_AdjustSplitScreenPreference), 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_packedGameOptionValueText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_FormatPackedGameOption), PACKED_CALLBACK_LOW(Items_AdjustPackedGameOption), 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionStickHorizontalStepText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_FormatPlayerOptionStickHorizontalStep), PACKED_CALLBACK_LOW(Items_AdjustPlayerOptionStickHorizontal),
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionStickVerticalStepText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_FormatPlayerOptionStickVerticalStep),
        PACKED_CALLBACK_LOW(Items_AdjustPlayerOptionStickVertical), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_weaponSelectNormalText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Items_SelectQuickWeaponSelectText), PACKED_CALLBACK_LOW(Items_ToggleQuickWeaponSelect), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_frontendScreenModePaletteDefault,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Items_UpdateScreenModeMenuItem), PACKED_CALLBACK_LOW(Items_RequestScreenModeFade), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_packedButtonOptionStepText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_FormatPackedButtonOption), PACKED_CALLBACK_LOW(Pak_AdjustPackedButtonOption), 0x00000000, 0x00000000, 0x00010201, 0x0000001E,
        0x0000FF01, (unsigned int)&g_packedButtonOptionStepText[0x8], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Menu_TryCreateMenu), 0x00000000, 0x00450C80, 0x000F0000,
        PACKED_CALLBACK_LOW(Items_ResetScreenModeFadeCooldown), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000041, 0x00000008, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x28], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000101, 0x0000005D, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x4, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00010101, 0x0000000A, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, PACKED_CALLBACK_LOW(Pak_StopMusicAndResetMatch), 0x00000000, 0x00000000, 0x00010101, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x10,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Menu_TryCreateMenu), 0x00000000, 0x00450EC0, 0x00050000, PACKED_CALLBACK_LOW(Pak_SetRecordTypeFour), 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00040000, 0x00000000, 0x00451220, 0x00010000, 0x50000000, 0x00000000,
        0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08002001,
        0x00000008, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x38, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00410041, 0x00000032, 0x0000FF01, (unsigned int)g_volumeZeroValueLabelFixed, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_UpdateMusicVolumeLabel), PACKED_CALLBACK_LOW(Pak_AdjustMusicVolume), 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_sfxVolumeText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_FormatSoundEffectsVolume), PACKED_CALLBACK_LOW(Pak_AdjustSoundEffectsVolume),
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_speechVolumeText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), PACKED_CALLBACK_LOW(Pak_UpdateSpeechVolumeLabel),
        PACKED_CALLBACK_LOW(Pak_AdjustSpeechVolume), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_musicPreviewFixedValueText, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        PACKED_CALLBACK_LOW(Pak_FormatMusicPreview), PACKED_CALLBACK_LOW(Pak_SelectMusicPreview), 0x00000000, 0x00000000, 0x00410401, 0x00000044, 0x0000FF01, (unsigned int)&g_packedButtonOptionStepText[0x8],
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_RestoreAudioAndCloseMenu), 0x00000000, 0x00450F98, 0x00070000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x00010000, 0x50000000, 0x00000000,
        0x0000FF01, 0x00000385, PACKED_CALLBACK_LOW(Menu_DrawMenuOptionSprite), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041,
        0x00000008, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x8], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x00000028, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0xC], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_ResumeMenuAudio), 0x00000000,
        0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x10], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_ReturnCallbackSuccess),
        0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x18], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000,
        PACKED_CALLBACK_LOW(Pak_OpenMenuVariantOne_de), 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x20], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel),
        0x00000000, PACKED_CALLBACK_LOW(Pak_OpenMenuVariantTwo_de), 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x38,
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_OpenMusicPreviewMenu), 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        (unsigned int)g_captureFlagVictimFollowupMessage + 0x20, PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_OpenEnterCheatMenu_de), 0x00000000, 0x00000000, 0x00010041, 0x00000000,
        0x0000FF01, (unsigned int)&g_redBloodScoreText[0x24], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_OpenCheatsMenu_de), 0x00000000, 0x00000000, 0x00010041,
        0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x28], PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, PACKED_CALLBACK_LOW(Pak_OpenQuitMenu_de), 0x00000000, 0x004510B8,
        0x000A0000, PACKED_CALLBACK_LOW(Pak_EnterPlayerOptions), PACKED_CALLBACK_LOW(Pak_RestoreControllerSetup), PACKED_CALLBACK_LOW(Pak_RenderMenuEntryCallback), 0x00000000, 0x00020000, 0x00000000, 0x00000000,
        (unsigned int)&g_multiplayerSavedPlayerNames[0xA4], 0x00445B80, 0x00445924, 0x00000000, 0x00000041, 0x00000000, 0x0000FF01, (unsigned int)&s_nodeDefaultFieldText[0x50],
        PACKED_CALLBACK_LOW(Menu_DrawMenuItemLabel), 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01,
        (unsigned int)&g_multiplayerSavedPlayerNames[0xB4], PACKED_CALLBACK_LOW(Setup_DrawNameCursor), PACKED_CALLBACK_LOW(Setup_UpdateNameCursor), 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008,
        0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xB8], PACKED_CALLBACK_LOW(Setup_DrawNameCursor), PACKED_CALLBACK_LOW(Setup_UpdateNameCursor), 0x00000000, 0x00000000, 0x00000000, 0x00210101,
        0x00000008, 0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xBC], PACKED_CALLBACK_LOW(Setup_DrawNameCursor), PACKED_CALLBACK_LOW(Setup_UpdateNameCursor), 0x00000000, 0x00000000, 0x00000000,
        0x00210101, 0x00000008, 0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xC0], PACKED_CALLBACK_LOW(Setup_DrawNameCursor), PACKED_CALLBACK_LOW(Setup_UpdateNameCursor), 0x00000000, 0x00000000,
        0x00000000, 0x00010110, 0x0000000A, 0x07012008, (unsigned int)g_creditsLocalizedLines + 0x8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter),
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x10, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000,
        PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x18, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x20,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008,
        (unsigned int)g_creditsLocalizedLines + 0x28, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x30, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x38, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF92008, (unsigned int)g_creditsLocalizedLines + 0x40, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000,
        0x00000000, 0x00010110, 0x00000004, 0x0701F808, (unsigned int)g_creditsLocalizedLines + 0x48, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter),
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x50, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000,
        PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x58, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x60,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808,
        (unsigned int)g_creditsLocalizedLines + 0x68, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x70, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x78, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF9F808, (unsigned int)g_creditsLocalizedLines + 0x80, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000,
        0x00000000, 0x00010110, 0x00000004, 0x0701F808, (unsigned int)g_creditsLocalizedLines + 0x88, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter),
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x90, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000,
        PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x98, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xA0,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808,
        (unsigned int)g_creditsLocalizedLines + 0xA8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xB0, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xB8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF9F808, (unsigned int)g_creditsLocalizedLines + 0xC0, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000,
        0x00000000, 0x00010110, 0x00000004, 0x0701F808, (unsigned int)g_creditsLocalizedLines + 0xC8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter),
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xD0, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000,
        PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xD8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xE0,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808,
        (unsigned int)g_creditsLocalizedLines + 0xE8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xF0, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xF8, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF9F808, (unsigned int)g_creditsLocalizedLines + 0x100, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000,
        0x00000000, 0x00010110, 0x00000004, 0x0701F8E0, (unsigned int)g_creditsLocalizedLines + 0x108, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter),
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x110, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000,
        PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x118, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText),
        0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x120,
        PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0,
        (unsigned int)g_unlockedLevelResultLabel, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110, 0x00060000,
        0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x128, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_AppendNameCharacter), 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x130, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_DeleteNameCharacter), 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFFF9F8E0, (unsigned int)g_creditsLocalizedLines + 0x138, PACKED_CALLBACK_LOW(Menu_DrawLocalizedMenuItemText), 0x00000000, PACKED_CALLBACK_LOW(Setup_CommitPlayerName), 0x00000000,
        0x00451250, 0x002D0000, PACKED_CALLBACK_LOW(Setup_LoadNameEditBuffer), 0x00000000, PACKED_CALLBACK_LOW(Menu_DrawMenuEntries), PACKED_CALLBACK_LOW(Setup_HasActiveGameCounters), 0x00050000, 0x00000000,
        0x00000000, 0xC6200004, 0x4600010D,
    },
};
#endif
