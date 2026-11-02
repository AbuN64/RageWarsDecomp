#include "include_asm.h"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/GAME_SESSION.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/SESSIONHANDLERROW.H"
#include "ENGINE/SETN64.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/CACHE_ALLOCATERESOURCE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GROUP.H"
#include "COMMON/STATERECAT34.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/OBJRECAT20V1.H"
#include "COMMON/LEVEL.H"
#include "CAMERA/CCINEMA_RESETSEQUENCECONTEXT.H"
#include "OVLGAME/MATCH_INITPARTICLEQUAD.H"
#include "ENGINE/SETN64.H"
#include "RENDER/SETN64_UPDATEFADETRANSITION.H"
#include "../../sdk/include/AUDIO/sprintf.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "UI/X_FILES/X_PLUS.H"
#include "OVLGAME/NOTE_RELEASERENDERBUFFERS.H"
#include "RESMGR/TSMOS_UPDATEFRONTEND.H"
#include "TEXTURE/AUDIOMGR_INITHEAP.H"

void SetN64_InitFrameRing(RenderState *state) {
    u32 i, count, previous, next;
    CGameStatus *counters;
    Frame *view;
    osCreateMesgQueue(&g_gameSchedulerMessageQueue, (s32)g_gameSchedulerMessages, 4096);
    XPlus_FillMemory(g_schedulerThreadStack, 7, 0x2000);
    Sched_InitializeSchedulerThread((void *)&g_systemScheduler, (s32)(g_schedulerThreadStack + 0x2000), g_schedulerThreadPriority, 0, 1);
    osScAddClient(&g_systemScheduler, &g_gameSchedulerClient, &g_gameSchedulerMessageQueue);
    state->handle = -1;
    SetN64_BeginSessionFadeIn(state);
    g_displayListCursor = 0;
    guMtxIdent((void *)&g_skyEffectProjectionMatrix);
    if (g_systemBootMarkerComparison) {
        Control_ResetActorSnapshot();
        Items_ResetGameOptions(&g_gameSettings);
    }
    i = 0;
    CCinema_ResetSequenceContext();
    Match_InitParticleQuad();
    Ovlgame_InitializeRenderDirection(&state->settings);
    count = g_renderFrameBufferCount;
    state->transitionBlocked = 0;
    state->enabled = 1;
    state->reservedTransitionState = 0;
    state->clockPaused = 0;
    counters = &g_gameSettings.counters;
    counters->first = 0;
    counters->m_bCreditsSeenOnce = 0;
    view = state->ring.views;
    if (count) do {
        previous = count - 1;
        previous = (i + previous) % count;
        next = count + 1;
        next = (i + next) % count;
        view->done.type = 2;
        view->colorImage = g_colorImageBuffers[i];

        view->previous = &state->ring.views[previous];
        view->next = &state->ring.views[next];
        SetN64_ClearFrameDirection(view++);
        ++i;
        count = g_renderFrameBufferCount;

    } while (i < count);
    SetN64_AdvanceDisplayFrame(&state->ring.display);
    SoundElement_InitializeContext();
}

#include "COMMON/GAME_SESSION.H"
#include "COMMON/DISPLAY.H"
#include "COMMON/MENURECAT24.H"
#include "COMMON/BOOT_TV_TYPE.H"
#include "SYSTEM/VIMGR.H"
#if defined(VERSION_EU)
extern void System_CreateVideoManagerEu(s32 pri);
#endif
#include "COMMON/RECORDRECAT1C.H"
extern struct RenderBufferResources g_renderResourceRecord; /* the render buffer record */
extern s16 *g_gameSchedulerMessage;
extern s32 g_schedulerRetracesSinceSwap;
extern s32 g_schedulerSwapPending;
extern s32 g_schedulerFrameQueueWriteIndex;
extern s32 g_schedulerQueuedFrameCount;
extern s32 g_schedulerFrameQueueReadIndex;
extern s32 g_schedulerPendingFramebuffer;
#if defined(VERSION_US_REV1)
extern char addrLow_Tengine_QueryArtsendOverride[];
extern char g_debugLinkNotificationQueue[];
extern void Libultra_SetDebugLinkCallback(void *segment);
#endif
extern void Pools_ResetPlayers(void *players);
extern void Player_ResetMenuPool(void *menu);
extern void CCollision_Initialize(void);
extern s32 Defs_ReadResourceWord(s32 size);
extern void Scene_LoadSceneResources(Shared_World *world, s32 resource);
extern s16 Ovlgame_InitializeControllerSession(void);
extern void Hud_ResetHudCharTables(void *hud);
extern void SetN64_BeginModeTransition(GameSession *session, s32 targetMode);
extern void SetN64_UpdateGameMode(void *session);
extern void SetN64_UpdateFrameTiming(void *session);
/* The game settings record and its round counters. */
static inline Shared_Game *currentGame(void) {
    return &g_gameSettings;
}
static inline CGameStatus *gameStatus(void) {
    return &g_gameSettings.counters;
}
/* Main game thread: brings up video and the overlays, clears the frame buffers, starts the menu and
   player state, then serves the scheduler's messages forever. */
void SetN64_RunGameLoop(GameSession *session) {
    u32 i;
    s16 *msg;
    Audiomgr_InitHeap();
#if defined(VERSION_EU)
    System_CreateVideoManagerEu(254);
#else
    System_CreateVideoManager(254);
#endif
    osViBlack(1);
#if defined(VERSION_US) || defined(VERSION_US_REV1)
    if (g_consoleTvType != 1 && g_consoleTvType != 2) {
#else
    if (g_consoleTvType != 0) {
#endif
        for (;;) {
        }
    }
    Note_ClearRenderRecord(&g_renderResourceRecord);
    Note_AllocateRenderBuffers(&g_renderResourceRecord);
    osViSwapBuffer((s32)g_colorImageBuffers[0]);
    osViBlack(0);
    if (g_consoleTvType == 0) {
        g_displayedFramebufferAndRefreshRate[1] = 50.0f;
    } else {
        g_displayedFramebufferAndRefreshRate[1] = 60.0f;
    }
    g_gameSchedulerMessage = 0;
    g_gameModeTransitionFrames = 2;
    g_schedulerRetracesSinceSwap = 0;
    g_lastFrameRetraceCount = 0;
    g_previousFrameRetraceCount = 0;
    g_secondPreviousFrameRetraceCount = 0;
    g_thirdPreviousFrameRetraceCount = 0;
    g_schedulerSwapPending = 0;
    g_schedulerFrameQueueWriteIndex = 0;
    g_schedulerQueuedFrameCount = 0;
    g_schedulerFrameQueueReadIndex = 0;
    g_displayedFramebufferAndRefreshRate[0] = 0.0f;
    g_schedulerPendingFramebuffer = 0;
    SetN64_InitFrameRing((RenderState *)session);
#if defined(VERSION_US_REV1)
    Libultra_SetDebugLinkCallback(addrLow_Tengine_QueryArtsendOverride);
    osSendMesg((OSMesgQueue *)g_debugLinkNotificationQueue, (OSMesg)0xBEEFDEAD, 0);
#endif
    for (i = 0; i < g_renderFrameBufferCount; i++) {
        XPlus_FillMemory(g_colorImageBuffers[i], 0, g_hudReferenceViewportWidth * g_hudReferenceViewportHeight * 2);
    }
    Pools_ResetPlayers(session->players);
    Player_ResetMenuPool(session->menu);
    CCollision_Initialize();
    session->resource = Defs_ReadResourceWord(24) & 0x3FFFFFFF;
    Pools_ResetActorPools(session->players, 0);
    Player_InitializePlayerPool(session->menu, 0, 0);
    Scene_LoadSceneResources(&g_world, session->resource);
    if (g_controllerPresenceBits[0] == 0) {
        Ovlgame_InitializeControllerSession();
    }
    Hud_ResetHudCharTables(&session->hud);
    Note_AllocateScratchBuffer();
    Tsmos_InitFrontendOnce();
    SmXlate_SwitchScreen(2);
    g_frontendEntryState = 3;
    g_pakScanActive = 0;
    g_pakRecheckRequested = 0;
    g_pakRequestLatched = 0;
    g_pakUsable = 1;
    g_pakProbeRequested = 0;
    Control_EnableAllControllerPaks();
    gameStatus()->transitionActive = 0;
    SetN64_BeginModeTransition(session, 0);
    for (;;) {
        Shared_Game *game = currentGame();
        osRecvMesg(&g_gameSchedulerMessageQueue, (OSMesg *)&g_gameSchedulerMessage, 1);
        msg = g_gameSchedulerMessage;
        switch (*msg) {
        case 1:
            SetN64_UpdateGameMode(session);
            break;
        case 2:
            if (msg == &session->ring.frames[0].done.type) {
                g_currentTaskFrame = &session->ring.frames[0];
            } else if (msg == &session->ring.frames[1].done.type) {
                g_currentTaskFrame = &session->ring.frames[1];
            } else if (msg == &session->ring.frames[2].done.type) {
                g_currentTaskFrame = &session->ring.frames[2];
            }
            if (session->mode == 20) {
                g_gameModeTransitionFrames++;
            } else {
                SetN64_UpdateFrameTiming(session);
            }
            /* The ROM keeps only the hoisted &g_gameSettings of this test: the store is dead (the next receive overwrites msg). */
            if (game->flags) {
                msg = 0;
            }
            break;
        case 4:
            g_systemBootMarker = 0;
            Control_ResetControllerProfiles();
            Control_SetControllerMode(0);
            session->fastFade = 1;
            session->transitionBlocked = 1;
            SetN64_SetTransitionTarget(session, 20);
            break;
        }
    }
}

#include <PR/abi.h>
#include "TYPES.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include <PR/gbi.h>

#include "COMMON/DISPLAY.H"
extern UnitVp g_fullScreenViewports[];
extern s32 g_lightingBufferIndex;

#include "COMMON/VIDEO_DIMENSIONS.H"
/* Starts the frame display list in the current ring buffer: segment 0, the two setup lists, the depth image, a
 * full-screen viewport (SCREEN_WD x SCREEN_HT) in g_fullScreenViewports_Setn64[g_lightingBufferIndex] and a full-screen scissor. */
void SetN64_BeginFrameDisplayList(void *world) {
    UnitVp *viewport;
    g_displayListCursor = g_gameSession.ring.current->commands;
    gSPSegment(g_displayListCursor++, 0, 0);
    gSPDisplayList(g_displayListCursor++, &g_cameraViewDisplayListFirst);
    gSPDisplayList(g_displayListCursor++, &g_cameraViewDisplayListSecond_de);
    viewport = &g_fullScreenViewports[g_lightingBufferIndex];
    gDPSetDepthImage(g_displayListCursor++, g_depthImageBuffer);
    viewport->vscale[0] = SCREEN_WD * 2;
    viewport->vscale[1] = SCREEN_HT * 2;
    viewport->vscale[2] = 1023;
    viewport->vscale[3] = 0;
    viewport->vtrans[0] = SCREEN_WD * 2;
    viewport->vtrans[1] = SCREEN_HT * 2;
    viewport->vtrans[2] = 0;
    viewport->vtrans[3] = 0;
    gSPViewport(g_displayListCursor++, viewport);
    gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
}

/* rspboot text is 0xD0 bytes: it ends where the first graphics microcode text (g_graphicsMicrocodeText) starts. */
extern u64 g_graphicsMicrocodeText[], g_graphicsMicrocodeData[], g_alternateGraphicsMicrocodeText[], g_alternateGraphicsMicrocodeData[], g_graphicsTaskYieldBuffer[];
extern u32 g_gameFrameCounter, g_gameLoopFrameCount;
extern void Sched_SendSchedulerTask(void *, OSScTask *);
/* Fills the frame's graphics task (and the second one when the frame is dual), hands them to the scheduler,
   then advances the ring and gives the next frame the other pair of command buffers. */
void SetN64_SubmitFrameTasks(Display *display, Frame *frame)
{
    OSScTask *task;
    task = &frame->task;
    {
        s32 size, bytes;
        u64 *base;
        task->list.t.data_ptr = (u64 *)frame->commands;
        bytes = frame->commandBytes;
        size = g_graphicsMicrocodeTextSize;
        task->list.t.type = 1;
        task->list.t.ucode_boot = rspbootTextStart;
        base = g_graphicsMicrocodeDataSize;
        task->list.t.ucode_boot_size = (u8 *)rspbootTextEnd - (u8 *)rspbootTextStart;
        task->list.t.ucode_size = 0x1000;
        task->list.t.ucode_data_size = 0x800;
        task->list.t.yield_data_ptr = g_graphicsTaskYieldBuffer;
        task->list.t.yield_data_size = 3072;
        task->list.t.ucode = g_graphicsMicrocodeText;
        task->list.t.ucode_data = g_graphicsMicrocodeData;
        task->list.t.flags = 0;
        task->list.t.dram_stack = 0;
        task->list.t.dram_stack_size = 0;
        task->list.t.output_buff = base;
        task->list.t.output_buff_size = (u64 *)((u8 *)base + size);
        task->list.t.data_size = bytes;
    }
    frame->task.next = 0;
    task->msgQ = &g_gameSchedulerMessageQueue;
    task->msg = &frame->done;
    task->framebuffer = frame->colorImage;
    if (frame->dual) task->flags = 3; else task->flags = 0x23;
    if (frame->dual) {
        s32 size, bytes;
        u64 *base;
        task = &frame->secondTask;
        task->list.t.data_ptr = (u64 *)frame->secondCommands;
        bytes = frame->secondCommandBytes;
        size = g_graphicsMicrocodeTextSize;
        task->list.t.type = 1;
        task->list.t.ucode_boot = rspbootTextStart;
        base = g_graphicsMicrocodeDataSize;
        task->list.t.ucode_boot_size = (u8 *)rspbootTextEnd - (u8 *)rspbootTextStart;
        task->list.t.ucode_size = 0x1000;
        task->list.t.ucode_data_size = 0x800;
        task->list.t.yield_data_ptr = g_graphicsTaskYieldBuffer;
        task->list.t.yield_data_size = 3072;
        task->list.t.ucode = g_alternateGraphicsMicrocodeText;
        task->list.t.ucode_data = g_alternateGraphicsMicrocodeData;
        task->list.t.flags = 0;
        task->list.t.dram_stack = 0;
        task->list.t.dram_stack_size = 0;
        task->list.t.output_buff = base;
        task->list.t.output_buff_size = (u64 *)((u8 *)base + size);
        task->list.t.data_size = bytes;
        frame->secondTask.next = 0;
        task->flags = 0x23;
        task->msgQ = &g_gameSchedulerMessageQueue;
        task->msg = &frame->done;
        task->framebuffer = frame->colorImage;
    }
    osWritebackDCacheAll();
    Sched_SendSchedulerTask(&g_systemScheduler, &frame->task);
    if (frame->dual) Sched_SendSchedulerTask(&g_systemScheduler, &frame->secondTask);
    g_gameFrameCounter++;
    g_gameLoopFrameCount++;
    g_lightingBufferIndex ^= 1;
    display->current = &display->frames[g_gameFrameCounter % g_renderFrameBufferCount];
    display->current->commands = g_lightingBufferIndex ? g_displayListBufferOne : g_displayListBufferZero;
    display->current->secondCommands = g_lightingBufferIndex ? g_secondaryDisplayListBufferZero : g_secondaryDisplayListBufferOne;
}
