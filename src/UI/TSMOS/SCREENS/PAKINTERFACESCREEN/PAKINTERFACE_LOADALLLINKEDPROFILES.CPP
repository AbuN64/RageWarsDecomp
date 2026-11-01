#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/PAKMENU.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Counts how many of the four 2920-byte entries g_pakProfileScreenState points to have a non-zero word at
   offset 0x58. */



s32 PAKInterface_CountActivePlayerPanels(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_pakProfileScreenState->players[i].state != 0) {
            count++;
        }
    }
    return count;
}

typedef struct { char pad[12]; s8 profileEntryIndex, linkedPlayerIndex; char rest[386]; } MatchProfile58;
extern MatchProfile58 g_localPlayerProfiles[];

void PAKInterface_LoadAllLinkedProfiles(void) {
    s32 i = 0; s32 none = -1;
    do {
        s32 player = g_pakProfileScreenState->links[i].player;
        s32 entry = g_pakProfileScreenState->links[i].entry;
        MatchProfile58 *dst = &g_localPlayerProfiles[i];
        if (player != none) { XPlus_CopyBytes(dst, g_pakProfileScreenState->players[player].slots[entry], 400); dst->profileEntryIndex = entry; }
        else { dst->linkedPlayerIndex = player; }
        i++;
    } while (i < 4);
}
