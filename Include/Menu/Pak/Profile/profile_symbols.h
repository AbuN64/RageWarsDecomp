#ifndef MENU_PAK_PROFILE_PROFILE_SYMBOLS_H
#define MENU_PAK_PROFILE_PROFILE_SYMBOLS_H
#include "Frontend/frontend_address_symbols.h"
#include "types.h"
extern s32 g_controllerPakPromptKind;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char g_pakProfileValueFormat[];
#else
#endif
#if (defined(VERSION_EU) || defined(VERSION_EU_X))
extern char g_pakProfileChannelValueFormat[];
extern char *g_pakAlternateChannelLabelTexts[];
#endif
#if (!(defined(VERSION_EU) || defined(VERSION_EU_X)))
extern u8 *g_pakAlternateChannelLabelTexts[];
#endif
#endif
