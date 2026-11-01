#include "MENU/TEAMMENU.H"
#include "AI/CTEAMSELECT.H"

void Cteamselect_InitTeamChoices(Shared_MenuItemList *list) {
    s32 i;
    f32 scale = g_teamWheelChoiceScale;
    f32 value = g_teamWheelInitialSlotScale;

    list->selection = -1;
    for (i = 0; i < 4; i++) {
        list->records[i].index = i;
        list->records[i].enabled = 1;
        list->records[i].image = 0;
        list->records[i].value = value;
        list->records[i].angle = i * scale;
    }
}
