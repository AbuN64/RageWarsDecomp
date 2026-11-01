#ifndef AI_PLAYER_LIGHT_PATTERN_NAMES_H
#define AI_PLAYER_LIGHT_PATTERN_NAMES_H

/* The player effect and mode light patterns carry a different symbol name in each build. */
#if defined(VERSION_DE)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternGerman
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternGerman
#elif defined(VERSION_EU)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternUs
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternEuropean
#elif defined(VERSION_US)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternUs
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternUs
#else
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternUsRev1
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternUsRev1
#endif

#endif
