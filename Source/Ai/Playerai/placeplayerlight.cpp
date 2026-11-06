#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/multiplayeroptions.h"
#include "Ai/player_light_pattern_names.h"
#include "Engine/gdynlight.h"
#include "onscrn.h"
#include "Placeplayerlight/placeplayerlight.h"

/* Player light patterns, model ids, HUD mover scripts and the ride/jump tuning, laid out in link order. */


/* Opcodes of the HUD mover scripts run by OnScreen_UpdateMoverScript. */
enum {
    MOVER_END = 0,   /* unknown opcode: the mover goes idle */
    MOVER_SET = 1,   /* x, y: jump to position */
    MOVER_WAIT = 2,  /* frames */
    MOVER_SLIDE = 3, /* x, y, frames: ease toward target */
    MOVER_FALL = 4,  /* 16.16 acceleration: accelerate down the screen until off it */
    MOVER_STOP = 6   /* mover off */
};

DynLightPattern PLAYER_EFFECT_LIGHT_PATTERN = { 1023, 64, { 0xFF, 0xFF, 0x80, 0xFF } };
DynLightPattern g_playerSecondaryLightPattern = { 511, 128, { 0xFF, 0xFF, 0x80, 0xFF } };
DynLightPattern PLAYER_MODE_LIGHT_PATTERN = { 1023, 64, { 0x0F, 0xFA, 0xFF, 0xFF } };
DynLightPattern g_playerAlternateModeLightPattern = { 1023, 64, { 0x00, 0x00, 0x00, 0xFF } };

s32 g_characterModelIds[17] = {
    1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120, 1120,
};
/* g_playerDeathEffectModelIds is element 1 of this array. */
s32 g_playerSpecialModelIds[2] = { 1121, 1122 };
s32 g_fragTagModelId = 1123;

#if defined(VERSION_DE)
/* Read as bytes at +3 and +7 by Items_HandleCharacterPreviewSelectionGerman (g_characterPreviewRightChoices/LeftChoices). */
s32 g_characterPreviewChoiceWordsDe[3] = { 17, 17, 3 };
#endif

s32 g_hudStatusWidgetSlideInMoverScript[5] = { MOVER_SLIDE, 28, -32, 2, MOVER_END };
s32 k_hudStatusWidgetMoverScriptSetPos[4] = { MOVER_SET, 120, 96, MOVER_END };
s32 k_hudStatusWidgetMoverScriptRise[6] = { MOVER_SLIDE, 120, 68, 2, MOVER_STOP, MOVER_END };

/* Per ammo widget: initial position, then the standard-screen and alternate-screen slide-away scripts. */
s32 g_hudStatusWidgetLeftMoverScript[4] = { MOVER_SET, 120, 96, MOVER_END };
s32 g_playerAmmoCounterAMoverScript[12] = {
    MOVER_SLIDE, 120, -32, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 k_playerAmmoCounterAAlternateMoverScript[12] = {
    MOVER_SLIDE, 120, -46, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 g_hudStatusWidgetCenterMoverScript[4] = { MOVER_SET, 190, 96, MOVER_END };
s32 k_playerAmmoCounterBStandardMoverScript[12] = {
    MOVER_SLIDE, 190, -32, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 g_playerAmmoCounterBMoverScript[12] = {
    MOVER_SLIDE, 190, -46, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 g_hudStatusWidgetRightMoverScript[4] = { MOVER_SET, 260, 96, MOVER_END };
s32 g_playerAmmoCounterCMoverScriptStandard[12] = {
    MOVER_SLIDE, 260, -32, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 g_playerAmmoCounterCMoverScriptAlternate[12] = {
    MOVER_SLIDE, 260, -46, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};

s32 g_hudLivesInitialMoverScript[4] = { MOVER_SET, 16, 16, MOVER_END };
s32 g_hudLivesMoverScript[5] = { MOVER_SLIDE, 16, 16, 2, MOVER_END };
s32 k_PlaceplayerlightData[4] = { MOVER_SET, 40, 16, MOVER_END };
s32 k_hudLivesMoverScriptSlideOut[12] = {
    MOVER_SLIDE, -40, 16, 2, MOVER_WAIT, 96, MOVER_SLIDE, 40, 16, 4, MOVER_STOP, MOVER_END,
};
s32 g_hudScoreInitialMoverScript[4] = { MOVER_SET, -82, 16, MOVER_END };
s32 g_hudScoreMoverScript[7] = { MOVER_SLIDE, -82, 16, 1, MOVER_WAIT, 96, MOVER_END };
s32 g_hudCountInitialMoverScript[4] = { MOVER_SET, -82, 68, MOVER_END };
s32 g_hudCountMoverScript[11] = {
    MOVER_SLIDE, -82, 68, 1, MOVER_WAIT, 96, MOVER_SLIDE, -82, 68, 1, MOVER_END,
};
s32 g_hudSquadInitialMoverScript[4] = { MOVER_SET, -82, 68, MOVER_END };
s32 g_hudSquadMoverScript[11] = {
    MOVER_SLIDE, -82, 68, 1, MOVER_WAIT, 96, MOVER_SLIDE, -82, 68, 1, MOVER_END,
};

CVector3 g_playerRideOffset = { 0.0f, 16.0f, 0.0f };
CVector3 g_playerRideBaseOffset = { 0.16f, 0.16f, 0.16f };
f32 g_playerAnimatedSpriteScaleX = 2.0f;
SharedMovement g_playerJumpMovementParameters = {
    10.24f, 30.72f, 13.44f, 10.24f, 35.84f, 13.44f, 0.0f, 0.0f, { 0, 0 }, 0,
};
/* First field (acceleration) of g_playerRideMovementParameters[0]; the rest of the struct follows in the next object. */
f32 g_playerRideMovementParameters = 4.608f;


#if defined(VERSION_US_REV1)
const float g_playerMountedMovementSpeedConstantsUsRevisionOne[1] = {
    34.559998f,
};
#endif

#if defined(VERSION_US_REV1)
float g_playerTuningFloatTriplesUsRevisionOne[16] = {
    1.7280002f, 2.7648f, 20.736f, 1.0368001f, 0.0f, 0.0f,
    0.0f, 2.88f, 21.599998f, 1.08f, 1.7280002f, 12.960001f,
    0.64800006f, 0.0f, 0.0f, 0.0f,
};
#endif

#if defined(VERSION_US_REV1)
float g_playerMovementTuningProfileOneUsRevisionOne[8] = {
    10.24f, 30.72f, 13.44f, 10.24f,
    35.84f, 13.44f, 0.0f, 0.0f,
};
#endif
