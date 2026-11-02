#include "TYPES.H"
#include "COMMON/GAME_SESSION.H"
#include <ultra64.h>
#include <PR/gbi.h>

/* Builds and submits the current frame, records its timing, and advances the fade transition. */
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/GROUP.H"
#include "COMMON/RESOURCELOCKSTATE.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/FRUSTUM.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/TRIPLE.H"
#include "CAMERA/CCINEMA_UPDATESEQUENCE.H"
#include "FRONTEND/SCREEN_VIDEO_MODE.H"
#include "ENGINE/SETN64.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "SYSTEM/TEXTLOAD_RESETTEXTURECACHE.H"
#include "SYSTEM/DEFS_TOGGLESAVEDFLAG.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
extern void Camera_UpdateViewportLayoutAndBounds(RaceViewportState *);
extern void SetN64_DrawColorRectangle(void *, u8 *, s32,s32,s32,s32);
extern void SetN64_ClearDepthRect(void *, s32,s32,s32,s32,s32);
extern void SetN64_SubmitFrameTasks(TimingWorld *,Frame *);
static __inline__ s32 hasFadeMode(u8 *mode) { return *mode != 0; }
void SetN64_BuildAndSubmitSessionFrame(TimingWorld *world) {
    u8 color[4];
    void (*draw)(TimingWorld *);
    f32 updatedFade;
    f32 fadeLimit;
    f32 fade;
    f32 step;
    f32 speed;
    f32 fadeOutSpeed;
    f32 nextFade;
    f32 elapsed;
    s32 alpha;
    u32 previousMode;
    u32 listBytes;
    u32 maxListBytes;
    u64 start;
    u64 end;
    u64 duration;
    u64 startTime;
    u8 fadeMode;

    start = osGetTime();
    previousMode = (u32) start;
    startTime = start;
    g_currentTaskFrame = g_gameSession.ring.current;
    Cache_SelectResourceSlot(0, g_lightingBufferIndex);
    TextLoad_ResetTextureCache();
    Geometry_InitializeModelRenderState();
    SetN64_BeginFrameDisplayList(world);
    Defs_ToggleSavedFlag();
    Control_TrackControllerPakChanges();
    Camera_UpdateViewportLayoutAndBounds(&world->viewport);
    SetN64_CommitSessionInputs(world);
    draw = g_sessionDrawHandlers[world->currentMode].draw;
    if (draw != 0) {
        draw(world);
    }
    if (g_currentTaskFrame->dual == 0) {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        fadeLimit = world->fade;
        alpha = 0xFF;
        if (!(fadeLimit < 0.0f)) {
            alpha = 0;
            if (!(g_sessionFrameFadeLimit < fadeLimit)) {
                alpha = 0xFF;
                if (!(fadeLimit < 0.0f)) {
                    alpha = ~(s32) (fadeLimit * g_sessionFrameFadeAlphaScale);
                }
            }
        }
        color[3] = alpha;
        SetN64_DrawColorRectangle(world, &color[0], 0, 0, g_hudReferenceViewportWidth, g_hudReferenceViewportHeight);
    }
    if (g_selectionMessageStage != 0) {
        if (g_selectionMessageStage == 20) {
            Frontend_AdvanceVideoMode();
        }
        SetN64_ClearDepthRect(world, 0, 480, 0, 360, 0);
        gDPSetScissorFrac(g_displayListCursor++,0,0,0,0x77C,0x59C);
        gDPSetColorImage(g_displayListCursor++,G_IM_FMT_RGBA,G_IM_SIZ_16b,480,g_currentTaskFrame->colorImage);
        gDPSetCycleType(g_displayListCursor++,G_CYC_FILL);
        gDPSetCombineLERP(g_displayListCursor++,0,0,0,SHADE,0,0,0,SHADE,0,0,0,SHADE,0,0,0,SHADE);
        gDPSetRenderMode(g_displayListCursor++,G_RM_NOOP,G_RM_NOOP2);
        gDPSetFillColor(g_displayListCursor++,0x10001);
        gDPFillRectangle(g_displayListCursor++,0,0,480,360);
        g_selectionMessageStage--;
    }
    gDPFullSync(g_displayListCursor++);
    gSPEndDisplayList(g_displayListCursor++);
    maxListBytes = g_maximumDisplayListBytes;
    listBytes = (u8 *)g_displayListCursor - (u8 *)g_currentTaskFrame->commands;
    g_currentTaskFrame->commandBytes = listBytes;
    if (maxListBytes < listBytes) {
        maxListBytes = listBytes;
    }
    g_maximumDisplayListBytes = maxListBytes;
    g_currentTaskFrame->dual = 0;
    g_currentTaskFrame->ticks = (s32) g_frameTimingTicks;
    end = osGetTime();
    duration = ((end - startTime) << 6) / 3;
    elapsed = (f32)duration;
    rwFrameBuildSeconds = elapsed * g_frameBuildTickScale;
    if (Cache_FinishResourceSlot(0) != 0) {
        SetN64_SubmitFrameTasks(world, g_currentTaskFrame);
    } else {
        osSendMesg(&g_gameSchedulerMessageQueue, &g_currentTaskFrame->done, 1);
    }
    if (hasFadeMode(&world->fadeMode)) {
        speed = g_sessionFrameFadeRate;
        if(world->fadeFast) speed = g_sessionFrameFastFadeRate;
        fadeOutSpeed = speed;
        fadeMode = world->fadeMode;
        if (fadeMode != 1) {
            if (fadeMode == 2) {
                fade = world->fade;
                step = 0.0f;
                if (fade > step) {
                    speed = g_frameElapsedTime;
                    updatedFade = fade - (fadeOutSpeed * speed);
                    world->fade = updatedFade;
                    if (updatedFade < step) {
                        world->fade = 0.0f;
                    }
                } else {
                    world->fade = fade - g_sessionFrameFadeHoldStep;
                }
                if (world->fade < g_sessionFrameFadeTransitionThreshold) {
                    previousMode = world->currentMode;
                    world->currentMode = 20;
                    world->fade = 0;
                    world->fadeMode = 1;
                    world->previousMode = previousMode;
                }
            }
        } else {
            step = g_frameElapsedTime;
            fade = world->fade;
            if (step < g_sessionFrameMinimumFadeStep) {
                nextFade = fade + (speed * g_sessionFrameMinimumFadeStep);
            } else {
                nextFade = fade + (speed * step);
            }
            fadeLimit = g_sessionFrameFadeMaximum;
            world->fade = nextFade;
            if (fadeLimit <= nextFade) {
                world->fadeMode = 0;
                world->fade = fadeLimit;
                world->fadeFast = 0;
            }
        }
    }
    CCinema_UpdateSequence();
}
