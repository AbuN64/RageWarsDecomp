#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Counts how many of the four 2920-byte entries g_pakProfileScreenState points to have a word at offset 0x58 that is neither zero nor 0x11.
   Adapted from PAKInterface_CountActivePlayerPanels with the extra 0x11 exclusion changed. */



s32 PAKInterface_CountUnfinishedPlayerPanels(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_pakProfileScreenState->players[i].state != 0 && g_pakProfileScreenState->players[i].state != 17) {
            count++;
        }
    }
    return count;
}
