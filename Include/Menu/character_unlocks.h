#ifndef MENU_CHARACTER_UNLOCKS_H
#define MENU_CHARACTER_UNLOCKS_H
#include "types.h"
struct CharacterVariantSelectionEntry;
extern void Menu_CyclePlayerCharacterVariant(int, struct CharacterVariantSelectionEntry *);
extern void Menu_ApplySlotValueGfx(int player, int choice);
#endif
