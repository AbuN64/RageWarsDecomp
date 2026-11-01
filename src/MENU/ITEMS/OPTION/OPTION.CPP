#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/RG.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "OVLGAME/SHAREDRECAT224.H"

extern s32 g_gameSettings;
extern s32 g_menuOptionAvailabilityFlags;

/* Updates the option item's flag bit and selects its associated text pointer. */
s32 Option_UpdateOptionBit0Item(TextBoundsText *optionItem) {
    if (g_menuOptionAvailabilityFlags & 1) {
        optionItem->flags |= 0x01000000;
    } else {
        optionItem->flags &= 0xFEFFFFFF;
    }
    if (g_gameSettings & 1) {
        optionItem->text = &g_menuOptionBit0EnabledText;
    } else {
        optionItem->text = &g_menuOptionBit0DisabledText;
    }
    return 0;
}


/* Toggles bit 1 of the settings flag word g_gameSettings and returns 0. */
s32 Option_ToggleOptionBit1(void) {
    g_gameSettings ^= 2;
    return 0;
}

#if !(defined(VERSION_US_REV1))
s32 Option_UpdateOptionBit1Item(TextBoundsText *item) {
    extern s32 g_gameSettings, g_menuOptionAvailabilityFlags;
    extern s32 g_menuOptionBit1EnabledText, g_menuOptionBit1DisabledText;
    if (g_menuOptionAvailabilityFlags & 2) item->flags |= 0x01000000; else item->flags &= 0xFEFFFFFF;
    if (g_gameSettings & 2) item->text = &g_menuOptionBit1EnabledText; else item->text = &g_menuOptionBit1DisabledText;
    return 0;
}
#endif

#if defined(VERSION_US_REV1)
extern s32 g_menuOptionBit1EnabledText;
extern s32 g_menuOptionBit1DisabledText;

/* Updates the option item's flag bit and selects its associated text pointer. */
s32 Option_RefreshOptionBit1Item(struct MenuOptionLabel *optionItem) {
    if (g_menuOptionAvailabilityFlags & 2) {
        optionItem->flags |= 0x01000000;
    } else {
        optionItem->flags &= 0xFEFFFFFF;
    }
    if (g_gameSettings & 2) {
        optionItem->text = &g_menuOptionBit1EnabledText;
    } else {
        optionItem->text = &g_menuOptionBit1DisabledText;
    }
    return 0;
}
#endif

/* Toggles bit 4 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit2(void) {
    g_gameSettings ^= 4;
    return 0;
}

/* Refreshes option item item from bit 0x4 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit2EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit2DisabledText otherwise; returns zero. */



s32 Option_UpdateOptionBit2Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x4) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x4) {
        item->label = g_menuOptionBit2EnabledText;
    } else {
        item->label = g_menuOptionBit2DisabledText;
    }
    return 0;
}

/* Toggles bit 8 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit3(void) {
    g_gameSettings ^= 8;
    return 0;
}

/* Refreshes option item item from bit 0x8 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit3EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit3DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit3Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x8) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x8) {
        item->label = g_menuOptionBit3EnabledText;
    } else {
        item->label = g_menuOptionBit3DisabledText;
    }
    return 0;
}

/* Toggles bit 0x10 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit4(void) {
    g_gameSettings ^= 0x10;
    return 0;
}

/* Refreshes option item item from bit 0x10 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit4EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit4DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit4Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x10) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x10) {
        item->label = g_menuOptionBit4EnabledText;
    } else {
        item->label = g_menuOptionBit4DisabledText;
    }
    return 0;
}

/* Toggles bit 0x20 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit5(void) {
    g_gameSettings ^= 0x20;
    return 0;
}

/* Refreshes option item item from bit 0x20 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit5EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit5DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit5Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x20) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x20) {
        item->label = g_menuOptionBit5EnabledText;
    } else {
        item->label = g_menuOptionBit5DisabledText;
    }
    return 0;
}

/* Toggles bit 0x40 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit6(void) {
    g_gameSettings ^= 0x40;
    return 0;
}

/* Refreshes option item item from bit 0x40 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit6EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit6DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit6Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x40) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x40) {
        item->label = g_menuOptionBit6EnabledText;
    } else {
        item->label = g_menuOptionBit6DisabledText;
    }
    return 0;
}

/* Toggles bit 0x80 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit7(void) {
    g_gameSettings ^= 0x80;
    return 0;
}

/* Refreshes option item item from bit 0x80 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit7EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit7DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit7Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x80) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x80) {
        item->label = g_menuOptionBit7EnabledText;
    } else {
        item->label = g_menuOptionBit7DisabledText;
    }
    return 0;
}

/* Toggles bit 0x100 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit8(void) {
    g_gameSettings ^= 0x100;
    return 0;
}

/* Refreshes option item item from bit 0x100 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit8EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit8DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit8Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x100) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x100) {
        item->label = g_menuOptionBit8EnabledText;
    } else {
        item->label = g_menuOptionBit8DisabledText;
    }
    return 0;
}

/* Toggles bit 0x200 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit9(void) {
    g_gameSettings ^= 0x200;
    return 0;
}

/* Refreshes option item item from bit 0x200 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit9EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit9DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit9Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x200) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x200) {
        item->label = g_menuOptionBit9EnabledText;
    } else {
        item->label = g_menuOptionBit9DisabledText;
    }
    return 0;
}

/* Toggles bit 0x400 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit10(void) {
    g_gameSettings ^= 0x400;
    return 0;
}

/* Refreshes option item item from bit 0x400 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit10EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit10DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit10Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x400) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x400) {
        item->label = g_menuOptionBit10EnabledText;
    } else {
        item->label = g_menuOptionBit10DisabledText;
    }
    return 0;
}

/* Toggles bit 0x800 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit11(void) {
    g_gameSettings ^= 0x800;
    return 0;
}

/* Refreshes option item item from bit 0x800 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit11EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit11DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit11Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x800) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x800) {
        item->label = g_menuOptionBit11EnabledText;
    } else {
        item->label = g_menuOptionBit11DisabledText;
    }
    return 0;
}

/* Toggles bit 0x1000 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit12(void) {
    g_gameSettings ^= 0x1000;
    return 0;
}

/* Refreshes option item item from bit 0x1000 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit12EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit12DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit12Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x1000) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x1000) {
        item->label = g_menuOptionBit12EnabledText;
    } else {
        item->label = g_menuOptionBit12DisabledText;
    }
    return 0;
}

/* Toggles bit 0x2000 of the option word g_gameSettings and returns zero; the functions after it in this
   run each toggle the next bit. */

s32 Option_ToggleOptionBit13(void) {
    g_gameSettings ^= 0x2000;
    return 0;
}

/* Refreshes option item item from bit 0x2000 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit13EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit13DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit13Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x2000) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x2000) {
        item->label = g_menuOptionBit13EnabledText;
    } else {
        item->label = g_menuOptionBit13DisabledText;
    }
    return 0;
}

/* Toggles bit 0x4000 of the option word g_gameSettings and returns zero; it is one of a run of
   functions that each toggle one bit of that word. */

s32 Option_ToggleOptionBit14(void) {
    g_gameSettings ^= 0x4000;
    return 0;
}

/* Refreshes option item item from bit 0x4000 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit14EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit14DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit14Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x4000) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x4000) {
        item->label = g_menuOptionBit14EnabledText;
    } else {
        item->label = g_menuOptionBit14DisabledText;
    }
    return 0;
}

/* Toggles bit 0x8000 of the option word g_gameSettings and returns zero; it is one of a run of
   functions that each toggle one bit of that word. */

s32 Option_ToggleOptionBit15(void) {
    g_gameSettings ^= 0x8000;
    return 0;
}

/* Refreshes option item item from bit 0x8000 of the option words: the item's flag 0x1000000 at 0x8
   follows the bit in g_menuOptionAvailabilityFlags, and its text pointer at 0x14 becomes g_menuOptionBit15EnabledText when the bit is
   set in g_gameSettings and g_menuOptionBit15DisabledText otherwise; returns zero. Adapted from Option_UpdateOptionBit2Item with the bit changed. */



s32 Option_UpdateOptionBit15Item(struct MenuOptionLabelView *item) {
    if (g_menuOptionAvailabilityFlags & 0x8000) {
        item->flags |= 0x1000000;
    } else {
        item->flags &= ~0x1000000;
    }
    if (g_gameSettings & 0x8000) {
        item->label = g_menuOptionBit15EnabledText;
    } else {
        item->label = g_menuOptionBit15DisabledText;
    }
    return 0;
}





