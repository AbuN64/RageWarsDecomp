#include "MENU/TEAMMENU.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Runs a player's team selection menu each frame unless a menu is paused (Cinema_IsSequenceActive): while the
   game is ending (g_matchEndingTeamWheelClose) an open menu is closed through TeamSelect_CloseTeamWheel; a closed menu opens through
   Cteamselect_InitTeamChoices when team selection g_teamScoringEnabled is on and the player has no team yet (0xFF at 0x92 of its
   controls); while it is open the player is held (0x11B4, 0x11B8) and shielded for 2, and the team slot
   under the stick (Cteamselect_GetFourWayStickSlot) becomes the hovered entry at 0x70, moving the cursor at 0x6C and
   choosing the entry's team for the player unless the entry is disabled or flagged 0x8000; the menu
   then slides open at 0.25 per frame, and once Cteamselect_TryConfirmTeamChoice confirms a choice it releases the player,
   announces the chosen team with its message and sound, and slides closed, the menu's spin at 0x14
   turning while it is shown. */











#ifdef VERSION_EU
#elif defined(VERSION_EU_X)
#endif
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "ENGINE/AUDIO/CHANNEL.H"
extern s32 g_matchEndingTeamWheelClose;
extern void TeamSelect_CloseTeamWheel(TeamMenu *);
extern void Cteamselect_InitTeamChoices(TeamMenu *, s32, SharedPlayer *);
extern s32 Cteamselect_GetFourWayStickSlot(SharedPlayer *);
extern s32 Cteamselect_TryConfirmTeamChoice(TeamMenu *, SharedPlayer *);

void Cteamselect_UpdateTeamWheel(TeamMenu *menu, SharedPlayer *player, void *unused) {
    s32 held;
    s32 slot;
    Entry *entry;
    u16 team;

    if (Cinema_IsSequenceActive() != 0) {
        return;
    }
    if (g_matchEndingTeamWheelClose != 0 && menu->state != 0) {
        TeamSelect_CloseTeamWheel(menu);
        return;
    }
    held = player->views5E8.view698_35.controller->rawButtons & 0x8000;
    if (menu->state == 0 || menu->state == 3) {
        if (g_gameSettings.counters.teams == 0 || player->views5D8.view5D8_1.record->team != 0xFF) {
            goto run;
        }
        Cteamselect_InitTeamChoices(menu, held, player);
        menu->state = 1;
    }
    player->views5E8.view11B4_136.locked = 1;
    player->views5E8.view11B8_138.frozen = 1;
    player->views5E8.view670_31.shield = 2.0f;
    slot = Cteamselect_GetFourWayStickSlot(player);
    if (slot != menu->hover) {
        if (slot != -1) {
            entry = (Entry *) ((char *) menu + slot * sizeof(TeamMenuSlotView));
            team = entry->team;
            if (entry->enabled == 0) {
                goto run;
            }
            if ((s16) team < 0) {
                menu->hover = -1;
                goto run;
            }
            if (slot != menu->cursor) {
                menu->cursor = slot;
            }
            player->views5D8.view5D8_1.record->team = team;
        }
        menu->hover = slot;
    }
run:
    switch (menu->state) {
    case 1:
        menu->open += g_frameElapsedTime * 0.25f;
        if (1.0f <= menu->open) {
            menu->open = 1.0f;
            menu->state = 2;
        }
        break;
    case 2:
        if (Cteamselect_TryConfirmTeamChoice(menu, player) == 0) {
            break;
        }
        menu->state = 3;
        player->views5E8.view11B4_136.locked = 0;
        player->views5E8.view11B8_138.frozen = 0;
        switch (player->views5D8.view5D8_1.record->team) {
        case 0:
#ifdef VERSION_EU
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team0SelectedNoticesEu[g_frontendScreenStatus.settings.language]);
#elif defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team0SelectedNoticesEuX[g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team0SelectedNotice);
#endif
            SoundElement_PlayFlatSound(742);
            break;
        case 1:
#ifdef VERSION_EU
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team1SelectedNoticesEu[g_frontendScreenStatus.settings.language]);
#elif defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team1SelectedNoticesEuX[g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team1SelectedNotice);
#endif
            SoundElement_PlayFlatSound(740);
            break;
        case 2:
#ifdef VERSION_EU
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team2SelectedNoticesEu[g_frontendScreenStatus.settings.language]);
#elif defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team2SelectedNoticesEuX[g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team2SelectedNotice);
#endif
            SoundElement_PlayFlatSound(744);
            break;
        case 3:
#ifdef VERSION_EU
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team3SelectedNoticesEu[g_frontendScreenStatus.settings.language]);
#elif defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team3SelectedNoticesEuX[g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_team3SelectedNotice);
#endif
            SoundElement_PlayFlatSound(748);
            break;
        }
        /* fall through */
    case 3:
        menu->open -= g_frameElapsedTime * 0.25f;
        if (menu->open <= 0.0f) {
            menu->open = 0.0f;
            menu->state = 0;
        }
        break;
    }
    if (menu->state != 0) {
        menu->spin += g_frameElapsedTime * 0.52359885f;
    }
}
