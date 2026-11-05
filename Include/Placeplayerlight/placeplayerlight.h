#ifndef PLACEPLAYERLIGHT_PLACEPLAYERLIGHT_H
#define PLACEPLAYERLIGHT_PLACEPLAYERLIGHT_H
#include "Common/vector.h"
#include "types.h"
#include "Ai/player_light_pattern_names.h"
/* Dynamic light descriptor: Gdynlight_AccumulateLightDirections reads the u16 radius; the rest is the light colour. */
typedef struct DynLightPattern {
    u16 radius;
    u16 unk2;
    u8 color[4];
} DynLightPattern;
extern s32 g_hudCountInitialMoverScript[];
extern s32 g_hudLivesInitialMoverScript[];
extern s32 g_hudScoreInitialMoverScript[];
extern s32 g_hudSquadInitialMoverScript[];
extern s32 g_hudStatusWidgetSlideInMoverScript[];
extern s32 g_hudStatusWidgetLeftMoverScript[];
extern s32 g_hudStatusWidgetRightMoverScript[];
extern s32 g_hudStatusWidgetCenterMoverScript[];
extern DynLightPattern g_playerAlternateModeLightPattern;
extern DynLightPattern g_playerSecondaryLightPattern;
extern s32 k_PlaceplayerlightData[];
extern CVector3 g_playerRideBaseOffset;
extern DynLightPattern PLAYER_MODE_LIGHT_PATTERN;
extern DynLightPattern PLAYER_EFFECT_LIGHT_PATTERN;

#endif
