#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Reorders the four 400-byte player records g_localPlayerProfiles by the players' choices: copies all four to
   the buffer at 0x2E28 of the block g_pakProfileScreenState points to and resets each through Player_InitializeProfile,
   copies back the record each player chose (index at 0xB28 of its 2920-byte record at 0x58) into
   that player's place, and then places every unchosen buffered record whose owner byte 0xD is not
   negative into the first place whose owner byte is still negative, all through XPlus_CopyBytes. */







extern struct RecordPAKInterfaceReassignLocalProfiles g_localPlayerProfiles[];
extern void Player_InitializeProfile(void *profileStorage);

void PAKInterface_ReassignLocalProfiles(void) {
    s32 used[4];
    s32 size;
    s32 chosen;
    s32 i;
    s32 j;

    size = 400;
    XPlus_CopyBytes(g_pakProfileScreenState->packet.saved, g_localPlayerProfiles, 1600);
    for (i = 0; i < 4; i++) {
        Player_InitializeProfile(&g_localPlayerProfiles[i]);
        used[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        chosen = g_pakProfileScreenState->players[i].port;
        if (chosen >= 0) {
            XPlus_CopyBytes(&g_localPlayerProfiles[i], &g_pakProfileScreenState->packet.saved[chosen], size);
            used[chosen] = 1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (used[i] != 0 || g_pakProfileScreenState->packet.saved[i].player < 0) {
            continue;
        }
        for (j = 0; j < 4; j++) {
            if (g_localPlayerProfiles[j].owner < 0) {
                XPlus_CopyBytes(&g_localPlayerProfiles[j], &g_pakProfileScreenState->packet.saved[i], size);
                break;
            }
        }
    }
}
