#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Copies the block's chosen 400-byte record for the place at slot linkIndex into g_localPlayerProfiles[linkIndex]: when
   the place is claimed (id != -1), copies the owning player's chosen slot into the record and marks
   the record's owned-slot byte, then always stamps the record's place-id byte. */







extern char g_localPlayerProfiles[];




void PAKInterface_LoadLinkedPlayerProfile(s32 linkIndex) {
    char *record;
    s32 place;
    s32 owner;

    place = g_pakProfileScreenState->links[linkIndex].player;
    owner = g_pakProfileScreenState->links[linkIndex].entry;
    record = &g_localPlayerProfiles[linkIndex * 400];
    if (place != -1) {
        XPlus_CopyBytes(record, g_pakProfileScreenState->players[place].slots[owner], 400);
        ((struct LinkedProfileOwnerRecord *)record)->slot = (s8) owner;
    }
    ((struct LinkedProfileOwnerRecord *)record)->place = (s8) place;
}
