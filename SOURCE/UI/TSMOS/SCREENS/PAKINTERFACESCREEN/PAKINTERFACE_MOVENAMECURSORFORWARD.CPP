#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Marks a player's record as ready for the next round: clears its pending counters, and on mode 1 advances its tier, gives the newly reached tier its default entry and flags the acquired handle for the notice sent to 0xE74. */

extern void *SmpOverlay_GetSlotValue(s32, s32);







s32 PAKInterface_MoveNameCursorForward(s32 unusedA, s32 unusedB, s32 index, s32 mode)
{
  s32 slot = index & 0xFFFF;
  s32 offset = slot * 2920;
  void *handle;
  if ((g_pakProfileScreenState->players[slot].state) == 12)
  {
    handle = SmpOverlay_GetSlotValue((s32)g_pakProfileScreenState->list, slot);
    g_pakProfileScreenState->players[slot].nameTimer = 0;
    g_pakProfileScreenState->players[slot].namePhase = 2;
    if (mode == 1)
    {
      s32 tier = (g_pakProfileScreenState->players[slot].nameCursor) + 1;
      if (tier < 7)
      {
        g_pakProfileScreenState->players[slot].nameCursor = tier;
      }
      {
        if (g_pakProfileScreenState->players[slot].name[g_pakProfileScreenState->players[slot].nameCursor].available == 0) {
          g_pakProfileScreenState->players[slot].name[g_pakProfileScreenState->players[slot].nameCursor].available = 65;
        }
      }
      ((struct WidgetFlagsView *)(handle))->alpha = 0xFF;
      SoundElement_PlayFlatSound(3700);
    }
  }
 do { return 0; } while (0);
}
