#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Takes a free slot from PAKInterface_FindEmptyPlayerLink and fills it with two values, marking it set, as
   Frontend_SetPlayerProfileLink does for an index; returns one, or zero when no slot is free. */






s32 PAKInterface_AddPlayerProfileLink(s32 first, s32 second) {
    s32 result = 0;
    s32 index = PAKInterface_FindEmptyPlayerLink();
    s32 taken;

    if (index >= 0) {
        taken = 1;
        result = taken;
        g_pakProfileScreenState->links[index].player = first;
        g_pakProfileScreenState->links[index].entry = second;
        g_pakProfileScreenState->links[index].state = result;
    }
    taken = result;
    return taken;
}
