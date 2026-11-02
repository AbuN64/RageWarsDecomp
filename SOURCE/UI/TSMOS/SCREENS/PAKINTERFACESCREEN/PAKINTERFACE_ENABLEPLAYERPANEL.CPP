#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Marks entry i of the 150-byte records g_playerSettingsRecords and sets the words at offsets 0x6C and 0x58
   of entry i of the 2920-byte records g_pakProfileScreenState points to to 2. */



void PAKInterface_EnablePlayerPanel(s32 index) {
    struct PakPlayerPanelView *entry;

    g_gameSettings.playerSettings[index].enabled = 1;
    entry = (struct PakPlayerPanelView *)((char *)g_pakProfileScreenState + index * sizeof(PakProfilePanelState));
    entry->second = 2;
    entry->first = 2;
}
