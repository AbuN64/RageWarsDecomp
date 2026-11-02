#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "COMMON/NAME.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/MENURECAT24.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "FRONTEND/FRONTEND_CHECKOWNEDPROFILEIDS.H"

/* Updates a player menu state from controller status, available saves, and the current menu phase. */


extern s32 Note_GetStatus(s32);
extern s32 Note_FindNoteByName(void *, s32, s32 *);
extern s32 PAKInterface_ReadRecordsNote(s32, s32);
extern void PAKInterface_RefreshPlayerPanel(s32);
void PAKInterface_ResolvePlayerPakState(s32 player)
{
  s32 random;
  s32 done = 1;
  s32 result;
  s32 status = Note_GetStatus(player);
  short one = done;
  do
  {
    switch (status)
    {
      case -4:

      case -3:

      case -1:
        g_pakProfileScreenState->players[player].state = 3;
        break;

      case 0:
        if (g_pakProfileScreenState->phase == 6)
      {
        g_pakProfileScreenState->players[player].state = g_pakProfileScreenState->players[player].next;
      }
      else
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        if (Note_FindNoteByName(((g_pakProfileGameNames)[g_languageIndex]), player, &result) == one)
#else
        if (Note_FindNoteByName((g_pakProfileGameNameFixed), player, &result) == one)
#endif
      {
        if (PAKInterface_ReadRecordsNote(player, result) == one)
        {
          g_pakProfileScreenState->players[player].state = g_pakProfileScreenState->players[player].next;
          switch (g_pakProfileScreenState->phase)
          {
            case 0:
              if (PAKInterface_FindEmptyProfileSlot(player) == (-1))
            {
              g_pakProfileScreenState->players[player].state = 24;
            }
              break;

            case 7:
              if (PAKInterface_AreProfileSlotsEmpty(player) == one)
            {
              g_pakProfileScreenState->players[player].state = 15;
            }
              break;

            case 2:
              if (PAKInterface_AreProfileSlotsEmpty(player) == one)
            {
              g_pakProfileScreenState->players[player].state = 25;
            }
            else
              if ((g_pakProfileScreenState->players[player].host == one) && (PAKInterface_FindEmptyProfileSlot(player) == (-1)))
            {
              g_pakProfileScreenState->players[player].state = 24;
            }
              break;

            case 5:
              if (Frontend_CheckOwnedProfileIds(player) == 0)
            {
              g_pakProfileScreenState->players[player].state = 21;
            }
              break;

          }

        }
      }
      else
      {
        switch (g_pakProfileScreenState->phase)
        {
          case 0:

          case 1:

          case 7:
            random = Graphu64_NextRandom();
            g_pakProfileScreenState->players[player].state = 15;
            g_pakProfileScreenState->players[player].profile = (random % 9999999) + 1;
            break;

          case 5:
            g_pakProfileScreenState->players[player].state = 21;
            break;

          case 4:
            g_pakProfileScreenState->players[player].state = g_pakProfileScreenState->players[player].next;
            break;

          case 2:

          case 3:
            g_pakProfileScreenState->players[player].state = 25;
            break;

        }

      }
        break;

      case -5:

      case -2:

      default:
        g_pakProfileScreenState->players[player].state = one;
        break;

    }

  }
  while (done == 0);
  PAKInterface_RefreshPlayerPanel(player);
}
