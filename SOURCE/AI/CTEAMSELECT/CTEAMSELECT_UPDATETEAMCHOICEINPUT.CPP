#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "MENU/TEAMMENU.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

s32 Cteamselect_TryConfirmTeamChoice(void *menu, void *player) {
    if (((((struct ControllerButtonFlagsView *) ((s8 *) ((struct TeamMenuPlayerLinksView *) ((s8 *) player))->controller))->buttons) & 0x8000) && ((((struct Record *) ((s8 *) ((struct TeamMenuPlayerLinksView *) ((s8 *) player))->options))->team) != 0xFF)) {
        (((struct Object6C *) ((s8 *) menu))->value) = -1;
        return 1;
    }
    return 0;
}
extern void Cteamselect_InitTeamChoices(void *teamMenu, s32 heldButtons, void *player);
extern s32 Cteamselect_GetFourWayStickSlot(void *object);
void Cteamselect_UpdateTeamChoiceInput(char *menu, void *player) {
    s32 flags;
    s32 state;
    s32 result;
    s32 value;
    char *entry;
    flags = ((struct ControllerButtonFlagsView *) ((TeamWeaponRuntimePlayerView *) player)->controller)->buttons & 0x8000;
    state = *(s32 *)menu;
    if ((state == 0) || (state == 3)) {
        if ((g_gameSettings.counters.teams != 0) &&
            (((struct Record *) ((TeamWeaponRuntimePlayerView *) player)->options)->team == 0xFF)) {
            Cteamselect_InitTeamChoices((void *)menu, flags, player);
            *(s32 *)menu = 1;
        } else {
            return;
        }
    }
    ((TeamWeaponRuntimePlayerView *)(player))->shieldDuration = g_teamWheelPlayerShieldDuration;
    ((TeamWeaponRuntimePlayerView *)(player))->locked = 1;
    ((TeamWeaponRuntimePlayerView *)(player))->lockState = 1;
    result = Cteamselect_GetFourWayStickSlot(player);
    if (result != ((TeamMenuSelectionPairView *)(menu))->hover) {
        if (result != -1) {
            entry = (char *)menu + result * sizeof(TeamMenuSlotView);
            value = ((Entry *)(entry))->team;
            if (((Entry *)(entry))->enabled != 0) {
                if ((s16)value < 0) {
                    ((TeamMenuSelectionPairView *)(menu))->hover = -1;
                    return;
                }
                if (result != ((TeamMenuSelectionPairView *)(menu))->cursor) {
                    ((TeamMenuSelectionPairView *)(menu))->cursor = result;
                }
                ((struct Record *) ((TeamWeaponRuntimePlayerView *) player)->options)->team = value;
            } else {
                return;
            }
        }
        ((TeamMenuSelectionPairView *)(menu))->hover = result;
    }
}
