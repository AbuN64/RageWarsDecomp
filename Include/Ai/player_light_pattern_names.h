#ifndef AI_PLAYER_LIGHT_PATTERN_NAMES_H
#define AI_PLAYER_LIGHT_PATTERN_NAMES_H

/* The player effect and mode light patterns carry a different symbol name in each build. */
#if defined(VERSION_DE)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternGerman
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternGerman
#elif defined(VERSION_EU)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternEuropean
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternEuropean
#elif defined(VERSION_EU_X)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternWords
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternEuropeanX
#elif defined(VERSION_US)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternUs
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternUs
#elif defined(VERSION_US_REV1)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPattern
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPattern
#endif

#endif
