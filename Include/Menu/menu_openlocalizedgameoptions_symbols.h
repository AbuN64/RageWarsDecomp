#ifndef MENU_MENU_OPENLOCALIZEDGAMEOPTIONS_SYMBOLS_H
#define MENU_MENU_OPENLOCALIZEDGAMEOPTIONS_SYMBOLS_H
#include "types.h"
struct ResidentEventHandlerEntry;
struct OptionsCommitContext;
#if (defined(VERSION_DE))
extern struct ResidentEventHandlerEntry g_joinOptionsEventHandlers[];
#endif
#if (defined(VERSION_EU) || defined(VERSION_EU_X))
extern u8 *g_optionsOffLabels[];
extern char *g_optionsResolutionLoRezChoiceLabels[];
extern char *g_optionsResolutionHiRezChoiceLabels[];
extern struct CompactOptionsCommitContext *g_gameOptionsScreenState;
#endif
#if (defined(VERSION_EU))
extern struct OptionsCommitContext *g_optionsPage;
#endif
#endif
