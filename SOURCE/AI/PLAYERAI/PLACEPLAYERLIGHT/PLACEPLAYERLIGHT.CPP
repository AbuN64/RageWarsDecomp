#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"

/* Player light patterns, model ids, HUD mover scripts and the ride/jump tuning, laid out in link order. */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)

#include "AI/PLAYER_LIGHT_PATTERN_NAMES.H"

/* Dynamic light descriptor: Gdynlight_AccumulateLightDirections reads the u16 radius; the rest is the light colour. */
typedef struct DynLightPattern {
    u16 radius;
    u16 unk2;
    u8 color[4];
} DynLightPattern;

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

s32 g_hudStatusWidgetMoverScriptFour[5] = { MOVER_SLIDE, 28, -32, 2, MOVER_END };
s32 k_hudStatusWidgetMoverScriptSetPos[4] = { MOVER_SET, 120, 96, MOVER_END };
s32 k_hudStatusWidgetMoverScriptRise[6] = { MOVER_SLIDE, 120, 68, 2, MOVER_STOP, MOVER_END };

/* Per ammo widget: initial position, then the standard-screen and alternate-screen slide-away scripts. */
s32 g_hudStatusWidgetMoverScriptOne[4] = { MOVER_SET, 120, 96, MOVER_END };
s32 g_playerAmmoFirstMoverScript[12] = {
    MOVER_SLIDE, 120, -32, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 k_playerAmmoFirstMoverScriptAlternate[12] = {
    MOVER_SLIDE, 120, -46, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 g_hudStatusWidgetMoverScriptTwo[4] = { MOVER_SET, 190, 96, MOVER_END };
s32 k_playerAmmoSecondMoverScriptStandard[12] = {
    MOVER_SLIDE, 190, -32, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 g_playerAmmoSecondMoverScript[12] = {
    MOVER_SLIDE, 190, -46, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 g_hudStatusWidgetMoverScriptThree[4] = { MOVER_SET, 260, 96, MOVER_END };
s32 g_playerAmmoThirdMoverScriptStandard[12] = {
    MOVER_SLIDE, 260, -32, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};
s32 g_playerAmmoThirdMoverScriptAlternate[12] = {
    MOVER_SLIDE, 260, -46, 2, MOVER_WAIT, 96, MOVER_FALL, 0x4CCCC, MOVER_WAIT, 96, MOVER_STOP, MOVER_END,
};

s32 g_hudLivesInitialMoverScript[4] = { MOVER_SET, 16, 16, MOVER_END };
s32 g_hudLivesMoverScript[5] = { MOVER_SLIDE, 16, 16, 2, MOVER_END };
s32 k_PlaceplayerlightEncodedWords[4] = { MOVER_SET, 40, 16, MOVER_END };
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

#endif
