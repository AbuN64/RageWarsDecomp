#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Places player p's chosen record into a free place: when the flag word for the chosen slot (index
   at 0xAEC of the player's 2920-byte record at 0x58, flags from 0xAF0) is 1, it takes the first of
   the four 12-byte places at 0x2DF8 of the block g_pakProfileScreenState points to whose id is -1, records it in
   the entry PAKInterface_FindEmptyPlayerLink returns (id 0, value the place, word 8 set to 1), copies the chosen
   400-byte slot from 0x18 of the player's record into that place of g_localPlayerProfiles through
   XPlus_CopyBytes, marks p as its owner at 0xD, clears the player's word at 0x4 and relabels through
   PAKInterface_RelabelSlotRows_FrontendResetlinkedlocalprofile(-1), returning 1; otherwise it returns 0. */









extern struct RecordPAKInterfaceReassignLocalProfiles g_localPlayerProfiles[];
extern void PAKInterface_RelabelSlotRows(s32);

s32 PAKInterface_JoinChosenProfile(s32 player) {
    struct RecordPAKInterfaceReassignLocalProfiles *record;
    s32 chosen;
    s32 place;
    s32 found;
    s32 entry;
    s32 result;
    s32 i;

    chosen = g_pakProfileScreenState->players[player].chosen;
    result = 0;
    if (g_pakProfileScreenState->players[player].used[chosen] == 1) {
        found = -1;
        for (i = 0; i < 4 && found == -1; i++) {
            if (g_pakProfileScreenState->links[i].player == -1) {
                found = i;
            }
        }
        place = found;
        if (place >= 0) {
            entry = PAKInterface_FindEmptyPlayerLink();
            if (entry >= 0) {
                g_pakProfileScreenState->links[entry].player = 0;
                g_pakProfileScreenState->links[entry].entry = place;
                g_pakProfileScreenState->links[entry].state = 1;
            }
            record = &g_localPlayerProfiles[found];
            XPlus_CopyBytes(record, g_pakProfileScreenState->players[player].slots[chosen], 400);
            record->owner = player;
            g_pakProfileScreenState->players[player].sub = 0;
            place = -1;
            PAKInterface_RelabelSlotRows(place);
            result = 1;
        }
    }
    return result;
}
