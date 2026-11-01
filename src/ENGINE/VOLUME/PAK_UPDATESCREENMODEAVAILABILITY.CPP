#include "include_asm.h"

#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENURECAT20V1.H"
#include "TYPES.H"
#include "COMMON/NODERECAT2A8.H"
#include "FRONTEND/SCREEN_VIDEO_MODE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TEXTURE_REQUEST.H"

/* 804453C4_7.CPP */
/* Sets bit 23 of the flag word at offset 8 of a record unless Defs_GetMemorySize reports 0x400000 for
   it, in which case the bit is cleared; then stores what Frontend_GetScreenModePalette_Playeroption returns at offset 0x14.
   Returns zero. */

extern s32 Defs_GetMemorySize(struct MenuTextResultView *);
extern s32 Frontend_GetScreenModePalette();

s32 Pak_UpdateScreenModeAvailability(struct MenuTextResultView *record) {
    if (Defs_GetMemorySize(record) != 0x400000) {
        record->flags |= 0x800000;
    } else {
        record->flags &= ~0x800000;
    }
    record->value = Frontend_GetScreenModePalette();
    return 0;
}

/* Calls Frontend_StartScreenModeFade_PakUpdatescreenmodeavailability and returns zero. */

s32 Pak_StartScreenModeFade(void) {
    Frontend_StartScreenModeFade();
    return 0;
}

/* 804453C4_8.CPP */
#if defined(VERSION_US_REV1)
/* Flips g_textureVariationBypassEnabled between zero and one and returns zero. */

s32 Pak_ToggleTextureVariationBypass(void) {
    g_textureVariationBypassEnabled = g_textureVariationBypassEnabled == 0;
    return 0;
}

/* Points a field's text at g_textureVariationBypassEnabledLabels when the option g_textureVariationBypassEnabled is set and at g_textureVariationBypassDisabledLabels otherwise, and returns
   zero: the label an option menu shows for that option. */

s32 Pak_UpdateTextureVariationBypassText(struct PakActionLabelView *field) {
    if (g_textureVariationBypassEnabled != 0) {
        field->text = g_textureVariationBypassEnabledLabels;
    } else {
        field->text = g_textureVariationBypassDisabledLabels;
    }
    return 0;
}
#endif
