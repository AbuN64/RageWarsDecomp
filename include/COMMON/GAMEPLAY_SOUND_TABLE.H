#ifndef COMMON_GAMEPLAY_SOUND_TABLE_H
#define COMMON_GAMEPLAY_SOUND_TABLE_H
#include "TYPES.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
typedef struct GameplaySoundEntry { s32 *sound; s32 hook; } GameplaySoundEntry;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern GameplaySoundEntry g_gameplayEventMessageTable[];
extern f32 g_gameplaySoundTable, g_triggerSoundWeightEu;
#else
extern GameplaySoundEntry g_gameplaySoundTable[];
extern f32 k_gameplaySoundWeight_de, k_triggerSoundWeight_de;
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define gameplaySoundValue(index) (g_gameplayEventMessageTable[index].sound[g_frontendScreenStatus.settings.language])
#else
#define gameplaySoundValue(index) (*g_gameplaySoundTable[index].sound)
#endif
static inline s32 gameplaySoundHook(s32 index) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_gameplayEventMessageTable[index].hook;
#else
    return g_gameplaySoundTable[index].hook;
#endif
}
static inline f32 gameplaySoundWeight(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_gameplaySoundTable;
#else
    return k_gameplaySoundWeight_de;
#endif
}
static inline f32 triggerSoundWeight(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_triggerSoundWeightEu;
#else
    return k_triggerSoundWeight_de;
#endif
}
#endif
