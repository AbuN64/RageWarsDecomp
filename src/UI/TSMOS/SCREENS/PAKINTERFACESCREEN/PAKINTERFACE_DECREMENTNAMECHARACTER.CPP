#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "TYPES.H"

extern void *SmpOverlay_GetSlotValue(s32, s32);

/* Steps the selected name character of an entry back by one, wrapping below the printable range to 'Z'. */
void PAKInterface_DecrementNameCharacter(s32 player) {
    u8 value;

    g_pakProfileScreenState->selected[player] = 0;
    SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
    if (g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available == 0) {
        g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available = 65;
    }
    value = g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available;
    value--;
    if (value < 32) {
        value = 90;
    }
    g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available = value;
}
