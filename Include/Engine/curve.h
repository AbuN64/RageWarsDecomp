#ifndef ENGINE_CURVE_H
#define ENGINE_CURVE_H
#include "types.h"
extern u32 g_curvePredictorBitWindow;
extern u32 g_curveSampleBitWindow;
extern s32 g_curvePredictorBitCount;
extern s32 g_curvePredictorShortLagCoefficients[4];
extern s32 g_curvePredictorLongLagCoefficients[4];
extern s32 g_curveSampleBitCount_de;

/* The words after g_pointLightSavedBufferOffset (the point light buffer offset Defs_ToggleSavedFlag restores, its
   own scalar global); the ambient and directional light colour bytes of the force marker follow. */
typedef struct SavedFlagToggleStorage {
#if defined(VERSION_DE)
    unsigned char colorBytes[32];
#else
    unsigned int words[3];
    unsigned char colorBytes[20];
#endif
} SavedFlagToggleStorage;
extern SavedFlagToggleStorage g_savedFlagToggleStorage;

/* us-rev1: the four words after the view-player option word g_playerViewRenderingEnabled, before g_pointLightSavedBufferOffset. */
typedef struct EnemyMixWordsAndLights {
    unsigned int words[4];
} EnemyMixWordsAndLights;
extern EnemyMixWordsAndLights g_enemyMixWordsAndLights;
#endif
