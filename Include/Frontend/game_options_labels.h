#ifndef FRONTEND_GAME_OPTIONS_LABELS_H
#define FRONTEND_GAME_OPTIONS_LABELS_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Frontend/options_list_declarations.h"
#if defined(VERSION_DE)
enum { OPTIONS_HAS_FIRST_LIST = 0, OPTIONS_RESOURCE_SHIFT = 4 };
#else
enum { OPTIONS_HAS_FIRST_LIST = 1, OPTIONS_RESOURCE_SHIFT = 0 };
extern char *g_optionsRedLabel, *g_optionsGreenLabel, *g_optionsResolutionLoRezChoiceLabels[], *g_optionsResolutionHiRezChoiceLabels[], *g_optionsResolutionLetterboxChoiceLabels[];
#endif
static inline char *gameOptionsLabel(s32 index) {
#if defined(VERSION_DE)
switch (index) { case 3: return (char *)g_optionsLowResolutionLabels[0]; case 4: return (char *)g_optionsHighResolutionLabels; case 5: return (char *)g_optionsLetterboxLabels; }
#else
switch (index) { case 0: return g_toggleListClearLabel[0]; case 1: return g_optionsRedLabel; case 2: return g_optionsGreenLabel; case 3: return g_optionsResolutionLoRezChoiceLabels; case 4: return g_optionsResolutionHiRezChoiceLabels; case 5: return g_optionsResolutionLetterboxChoiceLabels; }
#endif
return 0;
}
#endif
