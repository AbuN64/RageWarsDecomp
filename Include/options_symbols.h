#ifndef OPTIONS_SYMBOLS_H
#define OPTIONS_SYMBOLS_H
#include "types.h"
struct OptionsCommitContext;
#if (defined(VERSION_US) || defined(VERSION_US_REV1))
extern struct OptionsCommitContext *g_optionsPage;
extern char *g_optionsRedLabel;
extern char *g_optionsGreenLabel;
extern char *g_optionsResolutionLoRezChoiceLabels[];
extern char *g_optionsResolutionHiRezChoiceLabels[];
#endif
#endif
