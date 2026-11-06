#include "Menu/Items/Option/option_symbols.h"
#include "Menu/built_menu.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/rg.h"
#include "Ovlgame/confirming_controller.h"
#include "Common/shared_gameslot.h"
#include "Menu/Items/Option/option_symbols.h"

/* Updates the option item's flag bit and selects its associated text pointer. */
s32 Option_UpdateOptionInvincibilityItem(TextBoundsText *optionItem) {
    if (g_menuOptionAvailabilityFlags & 1) {
        optionItem->flags |= 0x01000000;
    } else {
        optionItem->flags &= 0xFEFFFFFF;
    }
    if (g_gameSettingsOptionFlags & 1) {
        optionItem->text = &g_menuOptionInvincibilityEnabledText;
    } else {
        optionItem->text = &g_menuOptionInvincibilityDisabledText;
    }
    return 0;
}

/* Toggles bit 1 of the settings flag word g_gameSettings and returns 0. */
s32 Option_ToggleOptionInfiniteLives(void) {
    g_gameSettingsOptionFlags ^= 2;
    return 0;
}

#if !(defined(VERSION_US_REV1))
s32 Option_UpdateOptionInfiniteLivesItem(TextBoundsText *item) {
    if (g_menuOptionAvailabilityFlags & 2) item->flags |= 0x01000000; else item->flags &= 0xFEFFFFFF;
    if (g_gameSettingsOptionFlags & 2) item->text = &g_menuOptionInfiniteLivesEnabledText; else item->text = &g_menuOptionInfiniteLivesDisabledText;
    return 0;
}
#endif

#if defined(VERSION_US_REV1)

/* Updates the option item's flag bit and selects its associated text pointer. */
s32 Option_RefreshOptionInfiniteLivesItem(struct MenuOptionLabel *optionItem) {
    if (g_menuOptionAvailabilityFlags & 2) {
        optionItem->flags |= 0x01000000;
    } else {
        optionItem->flags &= 0xFEFFFFFF;
    }
    if (g_gameSettingsOptionFlags & 2) {
        optionItem->text = &g_menuOptionInfiniteLivesEnabledText;
    } else {
        optionItem->text = &g_menuOptionInfiniteLivesDisabledText;
    }
    return 0;
}
#endif

/* Toggles bit 4 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionAllWeapons(void) {
    g_gameSettingsOptionFlags ^= 4;
    return 0;
}

/* Refreshes option item item from bit 0x4 of the option words: the item's availability flag
   follows the bit in g_menuOptionAvailabilityFlags, and its label becomes g_menuOptionAllWeaponsEnabledText when the bit is
   set in g_gameSettings and g_menuOptionAllWeaponsDisabledText otherwise; returns zero. */



s32 Option_UpdateOptionAllWeaponsItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x4) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x4) {
        item->resource = (s32)(g_menuOptionAllWeaponsEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionAllWeaponsDisabledText);
    }
    return 0;
}

/* Toggles bit 8 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionUnlimitedAmmo(void) {
    g_gameSettingsOptionFlags ^= 8;
    return 0;
}

/* Refreshes option item item from bit 0x8 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionUnlimitedAmmoEnabledText when the bit is
   set in g_gameSettings and g_menuOptionUnlimitedAmmoDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionUnlimitedAmmoItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x8) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x8) {
        item->resource = (s32)(g_menuOptionUnlimitedAmmoEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionUnlimitedAmmoDisabledText);
    }
    return 0;
}

/* Toggles bit 0x10 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionAllSpecialObjects(void) {
    g_gameSettingsOptionFlags ^= 0x10;
    return 0;
}

/* Refreshes option item item from bit 0x10 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionAllSpecialObjectsEnabledText when the bit is
   set in g_gameSettings and g_menuOptionAllSpecialObjectsDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionAllSpecialObjectsItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x10) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x10) {
        item->resource = (s32)(g_menuOptionAllSpecialObjectsEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionAllSpecialObjectsDisabledText);
    }
    return 0;
}

/* Toggles bit 0x20 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionBigHeadMode(void) {
    g_gameSettingsOptionFlags ^= 0x20;
    return 0;
}

/* Refreshes option item item from bit 0x20 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBigHeadModeEnabledText when the bit is
   set in g_gameSettings and g_menuOptionBigHeadModeDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionBigHeadModeItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x20) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x20) {
        item->resource = (s32)(g_menuOptionBigHeadModeEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionBigHeadModeDisabledText);
    }
    return 0;
}

/* Toggles bit 0x40 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionTinyMode(void) {
    g_gameSettingsOptionFlags ^= 0x40;
    return 0;
}

/* Refreshes option item item from bit 0x40 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionTinyModeEnabledText when the bit is
   set in g_gameSettings and g_menuOptionTinyModeDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionTinyModeItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x40) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x40) {
        item->resource = (s32)(g_menuOptionTinyModeEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionTinyModeDisabledText);
    }
    return 0;
}

/* Toggles bit 0x80 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionStickMode(void) {
    g_gameSettingsOptionFlags ^= 0x80;
    return 0;
}

/* Refreshes option item item from bit 0x80 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionStickModeEnabledText when the bit is
   set in g_gameSettings and g_menuOptionStickModeDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionStickModeItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x80) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x80) {
        item->resource = (s32)(g_menuOptionStickModeEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionStickModeDisabledText);
    }
    return 0;
}

/* Toggles bit 0x100 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionBigHandsFeetMode(void) {
    g_gameSettingsOptionFlags ^= 0x100;
    return 0;
}

/* Refreshes option item item from bit 0x100 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBigHandsFeetModeEnabledText when the bit is
   set in g_gameSettings and g_menuOptionBigHandsFeetModeDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionBigHandsFeetModeItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x100) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x100) {
        item->resource = (s32)(g_menuOptionBigHandsFeetModeEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionBigHandsFeetModeDisabledText);
    }
    return 0;
}

/* Toggles bit 0x200 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionPenAndInkMode(void) {
    g_gameSettingsOptionFlags ^= 0x200;
    return 0;
}

/* Refreshes option item item from bit 0x200 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionPenAndInkModeEnabledText when the bit is
   set in g_gameSettings and g_menuOptionPenAndInkModeDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionPenAndInkModeItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x200) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x200) {
        item->resource = (s32)(g_menuOptionPenAndInkModeEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionPenAndInkModeDisabledText);
    }
    return 0;
}

/* Toggles bit 0x400 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionGouraudMode(void) {
    g_gameSettingsOptionFlags ^= 0x400;
    return 0;
}

/* Refreshes option item item from bit 0x400 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionGouraudModeEnabledText when the bit is
   set in g_gameSettings and g_menuOptionGouraudModeDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionGouraudModeItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x400) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x400) {
        item->resource = (s32)(g_menuOptionGouraudModeEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionGouraudModeDisabledText);
    }
    return 0;
}

/* Toggles bit 0x800 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionJuansCheat(void) {
    g_gameSettingsOptionFlags ^= 0x800;
    return 0;
}

/* Refreshes option item item from bit 0x800 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionJuansCheatEnabledText when the bit is
   set in g_gameSettings and g_menuOptionJuansCheatDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionJuansCheatItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x800) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x800) {
        item->resource = (s32)(g_menuOptionJuansCheatEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionJuansCheatDisabledText);
    }
    return 0;
}

/* Toggles bit 0x1000 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionZachAttackCheat(void) {
    g_gameSettingsOptionFlags ^= 0x1000;
    return 0;
}

/* Refreshes option item item from bit 0x1000 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionZachAttackCheatEnabledText when the bit is
   set in g_gameSettings and g_menuOptionZachAttackCheatDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionZachAttackCheatItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x1000) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x1000) {
        item->resource = (s32)(g_menuOptionZachAttackCheatEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionZachAttackCheatDisabledText);
    }
    return 0;
}

/* Toggles bit 0x2000 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */
s32 Option_ToggleOptionAllMap(void) {
    g_gameSettingsOptionFlags ^= 0x2000;
    return 0;
}

/* Refreshes option item item from bit 0x2000 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionAllMapEnabledText when the bit is
   set in g_gameSettings and g_menuOptionAllMapDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionAllMapItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x2000) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x2000) {
        item->resource = (s32)(g_menuOptionAllMapEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionAllMapDisabledText);
    }
    return 0;
}

/* Toggles bit 0x4000 of the option word g_gameSettings and returns zero; it is one of a run of
   functions that each toggle one bit of that word. */
s32 Option_ToggleOptionBlackout(void) {
    g_gameSettingsOptionFlags ^= 0x4000;
    return 0;
}

/* Refreshes option item item from bit 0x4000 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBlackoutEnabledText when the bit is
   set in g_gameSettings and g_menuOptionBlackoutDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionBlackoutItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x4000) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x4000) {
        item->resource = (s32)(g_menuOptionBlackoutEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionBlackoutDisabledText);
    }
    return 0;
}

/* Toggles bit 0x8000 of the option word g_gameSettings and returns zero; it is one of a run of
   functions that each toggle one bit of that word. */
s32 Option_ToggleOptionFrootyStripes(void) {
    g_gameSettingsOptionFlags ^= 0x8000;
    return 0;
}

/* Refreshes option item item from bit 0x8000 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionFrootyStripesEnabledText when the bit is
   set in g_gameSettings and g_menuOptionFrootyStripesDisabledText otherwise; returns zero. Adapted from Option_UpdateOptionAllWeaponsItem with the bit changed. */



s32 Option_UpdateOptionFrootyStripesItem(struct MenuBuildEntry *item) {
    if (g_menuOptionAvailabilityFlags & 0x8000) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettingsOptionFlags & 0x8000) {
        item->resource = (s32)(g_menuOptionFrootyStripesEnabledText);
    } else {
        item->resource = (s32)(g_menuOptionFrootyStripesDisabledText);
    }
    return 0;
}
