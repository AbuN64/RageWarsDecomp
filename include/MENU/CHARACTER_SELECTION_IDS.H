#ifndef MENU_CHARACTER_SELECTION_IDS_H
#define MENU_CHARACTER_SELECTION_IDS_H
#include "TYPES.H"
#if defined(VERSION_DE)
enum { CHARACTER_EMPTY_SLOT = 127 };
#elif defined(VERSION_EU_X)
enum { CHARACTER_EMPTY_SLOT = 133 };
#else
enum { CHARACTER_EMPTY_SLOT = 129 };
#endif
#endif
