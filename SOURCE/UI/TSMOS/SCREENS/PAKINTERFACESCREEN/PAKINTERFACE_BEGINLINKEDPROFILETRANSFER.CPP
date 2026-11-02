#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Resets the selected player menu record, updates the initiating player state and refreshes the team labels. */


extern void SmpOverlay_SetSlotValue(s32, s32, s32);
extern void PAKInterface_RefreshPlayerPanel(s32);
extern void PAKInterface_UpdatePlayerControlRows(s32);
void PAKInterface_BeginLinkedProfileTransfer(s32 player)
{
  s32 selected = g_pakProfileScreenState->links[0].player;
  StatePAKInterfaceBeginLinkedProfileTransfer *slot;
  StatePAKInterfaceBeginLinkedProfileTransfer *selected_slot;
  SmpOverlay_SetSlotValue(g_pakProfileScreenState->root, selected, 0);
  slot = (StatePAKInterfaceBeginLinkedProfileTransfer *) (((char *) g_pakProfileScreenState) + (player * sizeof(PakProfilePanelState)));
  slot->state = 17;
  slot->reset = 0;
  selected_slot = (StatePAKInterfaceBeginLinkedProfileTransfer *) (((char *) g_pakProfileScreenState) + (selected * sizeof(PakProfilePanelState)));
  slot = selected_slot;
  slot->display = 2;
  slot->state = 2;
  slot->next = 13;
  slot->step = 3;
  PAKInterface_RefreshPlayerPanel(selected);
  PAKInterface_UpdatePlayerControlRows(-1);
}
