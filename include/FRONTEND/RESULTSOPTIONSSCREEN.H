#ifndef FRONTEND_RESULTSOPTIONSSCREEN_H
#define FRONTEND_RESULTSOPTIONSSCREEN_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"

/* Picks a menu element id from row and whether amount is set, hides the 0x14B child of that element and stores 0x64 and the value Results_GetWeaponIconValue reports for weaponId into its 0x14A child; on eu-x every element id in this menu is renumbered 4 higher. */

extern ResultsOptionsScreen *g_trialCatalogueScreen;

#if defined(VERSION_DE)
enum { ID_SHIFT = -4, OPTION_SHIFT = -2 };
#elif defined(VERSION_EU_X)
enum { ID_SHIFT = 4, OPTION_SHIFT = 4 };
#else
enum { ID_SHIFT = 0, OPTION_SHIFT = 0 };
#endif
#endif
