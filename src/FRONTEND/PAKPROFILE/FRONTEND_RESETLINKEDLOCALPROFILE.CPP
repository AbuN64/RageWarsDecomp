#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_RESETLINKEDLOCALPROFILE.H"

/* When slot i of the 12-byte records at offset 0x2DF8 of the table g_pakProfileScreenState points to is set,
   passes the 400-byte record i of g_localPlayerProfiles to Player_InitializeProfile, marks the slot done with 2 and calls
   PAKInterface_RelabelSlotRows_FrontendResetlinkedlocalprofile with -1. */






extern struct PlayerRecord g_localPlayerProfiles[];
extern void Player_InitializeProfile(void *profileStorage);
extern void PAKInterface_RelabelSlotRows(s32);

void Frontend_ResetLinkedLocalProfile(s32 index) {
    if (g_pakProfileScreenState->links[index].state == 1) {
        Player_InitializeProfile(&g_localPlayerProfiles[index]);
        g_pakProfileScreenState->links[index].state = 2;
        PAKInterface_RelabelSlotRows(-1);
    }
}
