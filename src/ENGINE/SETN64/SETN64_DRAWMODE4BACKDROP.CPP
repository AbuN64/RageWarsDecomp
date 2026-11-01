#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/AIPROFILE.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/WORLD.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "RENDER/TIMED_SESSION_TRANSITIONS.H"
#include "ENGINE/SETN64.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

/* Clears the map-view-active flag, emits a set-color-image display list command for the current frame
 * buffer, then draws image 0x389 scaled to fill the screen dimensions over the image's returned width
 * and height, when both are nonzero. */





extern Gfx *g_displayListCursor;

#include "COMMON/DISPLAY.H"

extern s32 g_hudReferenceViewportWidth;



extern void SetN64_HandleSessionTransitionInput(s32 session, s32 cancelTarget, s32 target);

extern void SetN64_ResetSessionPlayerPools(void *session, s32 count, s32 force_active);

extern void Scene_LoadLevelResources(void *, s32, s32);

extern void SmXlate_SwitchScreen(s32 index);


/* Cinema_SetResponse_Setn64Drawmode4backdrop: types.abi.declared: reuse existing C; propagated semantic conflicts remain named */

/* Scene_ResetTransitionViewport: types.declaration: solved callee prototype */


void SetN64_ResetMode4Effects(void) {
    g_mode4TextureEffectState = 0;
    Textload_SetTextureEffect(0U);
}

void SetN64_AdvanceToModeEight(struct GameSession *session) {
    s32 eight;
    eight = 8;
    SetN64_CheckTimedSessionTransition(session, 12.0f, eight, eight);
}

void SetN64_DrawMode4Backdrop(void) {
    s32 width;
    s32 height;
    Gfx *cmd;

    g_geometryFogEffectEnabled = 0;
    width = 0;
    height = 0;
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)g_currentRenderFrame->colorImage);
    OnScreen_GetImageDimensions(905, 0, &width, &height);
    if ((width != 0) && (height != 0)) {
        Onscrn_SetupSpriteMode(250);
        OnScreen_DrawSpriteResource(905, 0, 0, 0, (f32)g_hudReferenceViewportWidth / (f32)width, (f32)g_hudReferenceViewportHeight / (f32)height, 1);
    }
}

void SetN64_ResetMode5Items(s32 sessionAddress) {
    Scene_ResetTransitionViewport();
    ((s32 (*)(s32, s32))SetN64_ResetPlayerItems)(sessionAddress, 90);
}

void SetN64_HandleMode5Input(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 7, 7);
}

void SetN64_DrawMode5Session(s32 session) {
    SetN64_DrawSessionWithAttractTimeout(session);
    SetN64_OnMode5DrawComplete(session);
}

/** Perform no operation. */
void SetN64_InitializeMode6(void) {
}

/** Perform no operation. */
void SetN64_UpdateMode6(void) {
}

/** Perform no operation. */
void SetN64_DrawMode6(void) {
}

/** Thin wrapper calling SoundElement_SetMusicPlaybackEnabled with a fixed argument. */
void SetN64_SetMode7AudioState(void) {
    SoundElement_SetMusicPlaybackEnabled(16);
}

void SetN64_HandleMode7Transition(struct GameSession *session) {
    SetN64_CheckTimedSessionTransition(session, 20.0f, 9, 8);
}

void SetN64_InitializeMode8Scene(void *owner) {
    SetN64_ResetSessionPlayerPools(owner, 0, 0);
    Scene_LoadLevelResources(&g_world, 0, 0);
    g_gameSettings.counters.transitionActive = 0;
    SmXlate_SwitchScreen(24);
    SoundElement_SetMusicPlaybackEnabled(52);
}

void SetN64_UpdateMode8(void) {
}

/** Thin wrapper around SetN64_DrawSessionWithRoundTimeout. */
void SetN64_DrawMode8Session(GameSession *session) {
    SetN64_DrawSessionWithRoundTimeout(session);
}

/* SetN64_ResetPlayerItems_Setn64Drawmode4backdrop: types.abi.declared: reuse existing C; propagated semantic conflicts remain named */


                                                  /* size = 0x18 */

void SetN64_ResetMode9Items(s32 sessionAddress) {
    g_modeFourFrameCounter += 1;
    Scene_ResetTransitionViewport();
    Cinema_SetResponse(0.5f);
    SetN64_ResetPlayerItems(sessionAddress, 111);
}

void SetN64_HandleMode9Input(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 7, 8);
}

void SetN64_DrawMode9Session(void *session) {
    SetN64_DrawSessionWithAttractTimeout(session);
}

void SetN64_ResetMode11Items(s32 sessionAddress) {
    Scene_ResetTransitionViewport();
    ((s32 (*)(s32, s32))SetN64_ResetPlayerItems)(sessionAddress, 111);
}
