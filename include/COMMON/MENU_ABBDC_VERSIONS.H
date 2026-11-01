#ifndef COMMON_MENU_ABBDC_VERSIONS_H
#define COMMON_MENU_ABBDC_VERSIONS_H
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
/* PAL menu text tables select the current language; constant and table bases follow each cartridge. */
#if defined(VERSION_EU)
#elif defined(VERSION_EU_X)
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define MENU_LANGUAGE g_languageIndex
#else
#define MENU_LANGUAGE 0
#endif
#endif
