#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/PAK_PREVIEW_VIEWS.H"
#include "MENU/OPTIONEDITSTATE.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/RUNTIME_DECLARATIONS.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/PAK_MENU.H"

s32 Pak_SelectMusicPreview(s32 unusedEvent, Shared_PakMenu *pThis) {
    s32 selection = g_menuMusicPreviewSelection;
    if (pThis->owner->inputFlags & 0x20202) {
        selection--;
        if (selection < 0) {
            selection = 22;
        } else if (selection == 14) {
            selection = 11;
        }
    }
    if (pThis->owner->inputFlags & 0x4D101) {
        selection++;
        if (selection >= 23) {
            selection = 0;
        } else if (selection == 12) {
            selection = 15;
        }
    }
    g_menuMusicPreviewSelection = selection;
    SoundElement_SetMusicPlaybackEnabled(selection);
    return 0;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Cycles a menu selection from directional input while skipping reserved entries. */
 /* extern */
s32 Pak_SelectMusicPreview(s32 unused, struct PakControllerRequestView *menu) {
    s32 musicSelection;
    musicSelection = g_menuMusicPreviewSelection;
    if (menu->inner->buttons & 0x20202) {
        musicSelection -= 1;
        if (musicSelection < 0) {
            musicSelection = 22;
        } else if (musicSelection == 14) {
            musicSelection = 11;
        }
    }
    if (menu->inner->buttons & 0x4D101) {
        musicSelection += 1;
        if (musicSelection >= 23) {
            musicSelection = 0;
        } else if (musicSelection == 12) {
            musicSelection = 15;
        }
    }
    g_menuMusicPreviewSelection = musicSelection;
    SoundElement_SetMusicPlaybackEnabled(musicSelection);
    return 0;
}
#endif
