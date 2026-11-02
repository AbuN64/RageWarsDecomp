#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "include_asm.h"
#include "COMMON/LEVEL_GOAL.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/WORLD.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/ACTIVE.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "ACHIEVE/ACHIEVE.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "FRONTEND/MENUIMAGE.H"

extern MatchScoreScreen *g_matchResultBadgeScreen;
extern Shared_Rec3 g_playerSettings[8];
extern void Widget_SetWidgetFlag08(void *object, int enabled);

/* Calls InitFrontendMenus and Tsmos_DeactivateControllerState, then SmXlate_SwitchScreen with 0x11. */
#if defined(VERSION_EU)
extern void Tsmos_InitializeEuropeanFrontend(void);
#else
extern void InitFrontendMenus(void);
#endif

extern void Tsmos_DeactivateControllerState(void);

extern void SmXlate_SwitchScreen(s32);

/* Clears the words at offsets 0x78 and 0x54 of g_matchRoundCounters, then calls SmXlate_SwitchScreen with 0x14
   unless ScenarioSetup_IsCupSelected_MatchReason and ScenarioSetup_StartRandomCupStage both report something, in which case it calls
   Stage_StartConfiguredMatch. */




extern s32 ScenarioSetup_StartRandomCupStage(void);

extern void Stage_StartConfiguredMatch(void);

/* Reports why a match ended: time running out on a timed match, the score limit (Player_CheckScoreLimit),
   the rule set's own target (Player_CheckTeamPointWin_PlayerUpdatefragtagselection for rule set 0, the Frag Tag limit Player_CheckTotalScoreWin_MatchReason for
   rule set 1), or otherwise whether the last-player-standing check reached its end. */

extern MatchResultsGameSettingsView g_matchEndingTeamWheelClose;



extern s32 Player_CheckScoreLimit(World *world);

extern s32 Player_CheckTotalScoreWin(World *world);

extern s32 Player_CheckTeamPointWin(World *world);

/* For each of the 8 occupied slots without the pending-remove flag, runs its two release callbacks. */









extern void Frontend_AwardMatchAchievements(s32 player, s32 *awarded);


/* Refreshes each of 8 configured participants: for each slot, reads the participant id at offset
   0xF0 + slot*4 of g_matchResultBadgeScreen; when it is not -1 and the id's 150-byte record in g_playerSettings_Achieve has
   its byte at 0x91 clear, stores Achieve_AwardMilestoneCompletion(id) at offset 0x32C of g_matchResultBadgeScreen, calls
   Achieve_AwardAllMilestoneAchievement(id, &g_matchResultBadgeScreen[0x110 + id*8]), and calls Achieve_UpdateUnlockTiers(id). */





/* When the object g_matchResultBadgeScreen points to has a target at 0x32C and its word at 0x328 set, runs
   Preview_DrawMenuModelItem on offset 0x20 of it with g_menuModelFillEnabled set and g_menuModelFillAlpha raised to g_resultBadgeDrawParameters[1],
   then clears g_menuModelFillEnabled and sets g_menuModelFillAlpha to g_resultBadgeDefaultAlpha. */







extern void Preview_DrawMenuModelItem(struct MenuModelItem *item);

/* Draws player p's badge on the screen g_matchResultBadgeScreen: looks up the group item the third argument
   names in the screen window, picks its child 0x26C, 0x26B or 0x26A for kinds 1 to 3 and 0x26D
   otherwise, shows it with alpha 0x96, and sets its frame at 0x2C from the rank byte at 0x92 of
   the player's 150-byte record in g_playerSettings_Achieve, the cartridge's jump table jtbl_Frontend_ShowResultRankBadge sending
   ranks 0 to 4 to frame 0x63, 0x62, 0x61 or 0x5F or to hiding it again with frame 0x60, which any
   higher rank also gets. */


/* Hides the four child items of a selected menu panel. */



                            /* extern */


#if defined(VERSION_DE)
enum { ITEM0 = 616, ITEM1 = 615, ITEM2 = 614, ITEM3 = 613 };
#elif defined(VERSION_EU_X)
enum { ITEM0 = 625, ITEM1 = 624, ITEM2 = 623, ITEM3 = 622 };
#else
enum { ITEM0 = 621, ITEM1 = 620, ITEM2 = 619, ITEM3 = 618 };
#endif

/* Releases the object g_matchResultBadgeScreen holds through Cache_FreeMemory, clears g_matchResultBadgeScreen and returns zero. */



/* Handles event 1 on the screen g_matchResultBadgeScreen: unless Frontend_GetMenuImageState reports its menu in state 1 it
   calls Frontend_DrawResultSelectionPreview; otherwise it advances the menu with Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition and,
   once Frontend_GetMenuImageState reports 2, acts on the choice at 0x1C: choice 0 hides the window argument,
   calls MarkMenuEventHandled, clears g_resultReplayPending and g_resultExitPending and leaves for screen 0xF when option
   g_gameControllerMode is set, otherwise through Stage_StartConfiguredMatch when ScenarioSetup_IsCupSelected_MatchReason and ScenarioSetup_StartRandomCupStage both
   agree or for screen 0x14; choice 1 calls Frontend_RequestScreenMode_AchieveUpdateresultsscreen(0), shows the window, stops the objects
   at g_frontendScreenStatus and 0x48 before it, releases g_world_AchieveUpdateresultsscreen through Scene_LoadLevelResources and sets the word at
   0x17F0 of g_frontendScreenStatus to 8. Returns zero. */








extern s32 Frontend_GetMenuImageState(s32 *record);

extern void Frontend_DrawMenuImage(struct MenuImage *menu);




extern void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);

extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);

extern void Scene_LoadLevelResources(void *, s32, s32);

extern void MarkMenuEventHandled();

/* Runs one frame of the screen g_matchResultBadgeScreen's confirmation prompt while g_selectionMessageStage is not positive:
   on the first frame it marks the prompt open at 0x320 and asks Menu_SetFocusedElement for message 0x238,
   or 0x237 when Widget_ListHasFlag100_AchieveUpdateresultsscreen rejects the object loaded for 0x238, then calls Tsmos_ActivateControllerState. Once
   the choice word g_selectionMessageReply[1] reads one it clears it and either enables the prompt's object at
   0xE4 and records the choice at 0x328, when the pending action g_selectionMessageReply[0] is -1, or disables
   the object, clears 0x328 and hands the pending action to SmXlate_SwitchScreen through MarkMenuEventHandled.
   Returns zero. On eu-x both message ids are renumbered 5 higher. */






extern s32 g_selectionMessageReply[];

extern s32 Widget_ListHasFlag100(struct WidgetNode *node);

extern void Menu_SetFocusedElement(s32);

extern void Tsmos_ActivateControllerState(void);

#if defined(VERSION_DE)
enum { CONFIRM_MESSAGE = 564, FALLBACK_MESSAGE = 563 };
#elif defined(VERSION_EU_X)
enum { CONFIRM_MESSAGE = 573, FALLBACK_MESSAGE = 572 };
#else
enum { CONFIRM_MESSAGE = 568, FALLBACK_MESSAGE = 567 };
#endif

void Frontend_InitMatchResultsMenu(void) {

#if defined(VERSION_EU)
Tsmos_InitializeEuropeanFrontend
#else
InitFrontendMenus
#endif
();
    Tsmos_DeactivateControllerState();
    SmXlate_SwitchScreen(17);
}

void Frontend_ContinueCupOrOpenResults(void) {
    CGameStatus *state = &g_gameSettings.counters;

    state->m_bCTFOn = 0;
    state->m_bFragTagOn = 0;
    if (ScenarioSetup_IsCupSelected() == 0 || ScenarioSetup_StartRandomCupStage() == 0) {
        SmXlate_SwitchScreen(20);
    } else {
        Stage_StartConfiguredMatch();
    }
}

void Frontend_OpenControllerModeResults(void) {
    CGameStatus *state = &g_gameSettings.counters;

    state->m_bCTFOn = 0;
    state->m_bFragTagOn = 0;
    SmXlate_SwitchScreen(15);
}

s32 Frontend_GetMatchEndReason(void) {
    MatchTimeSettingView *settings;
    settings = &g_matchEndingTeamWheelClose.settings;
    if (settings->timeSetting > 0 && g_matchEndingTeamWheelClose.rules.timeLeft == 0.0f) {
        return MATCH_END_TIME_UP;
    }
    if (Player_CheckScoreLimit((World *)&g_playerViewRenderContext) != 0) {
        return MATCH_END_SCORE_LIMIT;
    }
    switch (g_currentResultMode.kind) {
    case 0:
        if (Player_CheckTeamPointWin((World *)&g_playerViewRenderContext) != 0) {
            return MATCH_END_POINT_TARGET;
        }
        break;
    case 1:
        if (Player_CheckTotalScoreWin((World *)&g_playerViewRenderContext) != 0) {
            return MATCH_END_TAG_LIMIT;
        }
        break;
    }
    return g_matchEndingTeamWheelClose.rules.lastStanding == 1;
}

void Frontend_AwardResultAchievements(void)
{
  s32 i;
  MatchScoreScreen *obj;
  int absentPlayer;
  Shared_Rec3 *recs;
  for (i = 0; i < 8; i++)
  {
    s32 val;
    absentPlayer = -1;
    obj = g_matchResultBadgeScreen;
    recs = g_playerSettings;
    val = obj->players[i];
    if (val == absentPlayer)
    {
      continue;
    }
    if ((recs + val)->flag != 0)
    {
      continue;
    }
    Frontend_AwardMatchAchievements(val, obj->icons[val]);
    recs = g_playerSettings;
    Achieve_UpdateUnlockTiers(val);
  }

}

void Frontend_AwardResultMilestones(void) {
    s32 id;
    s32 i;
    Shared_Rec3 *record;

    for (i = 0; i < 8; i += 1) {
        id = g_matchResultBadgeScreen->players[i];
        if (id == -1) {
            continue;
        }
        record = &g_playerSettings[id];
        if (record->flag != 0) {
            continue;
        }
        g_matchResultBadgeScreen->selection = Achieve_AwardMilestoneCompletion(id);
        Achieve_AwardAllMilestoneAchievement(id, g_matchResultBadgeScreen->icons[id]);
        Achieve_UpdateUnlockTiers(id);
    }
}

void Frontend_DrawResultSelectionPreview(void) {
    MatchScoreScreen *state = g_matchResultBadgeScreen;
    f32 *level;

    if (state->selection != -1 && state->dirty != 0) {
        level = &g_menuModelFillColor[3];
        g_menuModelFillEnabled = 1;
        *level = g_resultBadgeDrawParameters[1];
#if defined(VERSION_DE)
        Frontend_DrawResultModelPreviewDe((char *)&state->pad20);
#else
        Preview_DrawMenuModelItem((char *)&state->pad20);
#endif
        g_menuModelFillEnabled = 0;
        *level = g_resultBadgeDefaultAlpha;
    }
}

void Frontend_ShowResultRankBadge(s32 player, s32 kind, unsigned short group) {
    MenuWidget *item;
    MenuWidget *parent;
    Shared_Rec3 *record;
    u32 rank;
    s32 id;
    s32 frame;
    record = &g_playerSettings[player];
    parent = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, group);
    switch (kind) {
    case 0:
    default:
#if defined(VERSION_DE)
        id = 616;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 621;
#elif defined(VERSION_EU_X)
        id = 625;
#endif
        break;
    case 1:
#if defined(VERSION_DE)
        id = 615;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 620;
#elif defined(VERSION_EU_X)
        id = 624;
#endif
        break;
    case 2:
#if defined(VERSION_DE)
        id = 614;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 619;
#elif defined(VERSION_EU_X)
        id = 623;
#endif
        break;
    case 3:
#if defined(VERSION_DE)
        id = 613;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 618;
#elif defined(VERSION_EU_X)
        id = 622;
#endif
        break;
    }
    item = Node_FindWidgetByResourceId(parent, id);
    Widget_SetWidgetFlag08(item, 1);
    item->alpha = 150;
    rank = record->rank;
    switch (rank) {
    case 0:
        frame = 99;
        break;
    case 1:
        frame = 98;
        break;
    case 2:
        frame = 97;
        break;
    case 3:
        frame = 95;
        break;
    case 4:
        frame = 96;
        break;
    default:
        Widget_SetWidgetFlag08(item, 0);
        frame = 96;
        break;
    }
    item->value = frame;
}

void Frontend_HideResultBadgeGroup(s32 screenAddress) {
    MenuWidget *root;
    s32 badgeIndex;
    s32 playerIndex;

    root = Node_FindWidgetByResourceId(g_matchResultBadgeScreen->window, screenAddress & 0xFFFF);
    playerIndex = 0;
    do {
        switch(playerIndex) {
        case 0: badgeIndex=ITEM0; break;
        case 1: badgeIndex=ITEM1; break;
        case 2: badgeIndex=ITEM2; break;
        case 3: badgeIndex=ITEM3; break;
        default: badgeIndex=ITEM0; break;
        }
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(root, badgeIndex), 0);
        playerIndex += 1;
    } while (playerIndex < 4);
}

s32 Frontend_DestroyMatchResults(void) {
    Cache_FreeMemory(g_matchResultBadgeScreen);
    g_matchResultBadgeScreen = 0;
    return 0;
}

s32 Frontend_UpdateMatchResultsTransition(void *window, void *unused1, s32 event) {
    s32 state;
    char *object;
    s32 next;

    if (event != 1) {
        return 0;
    }
    state = Frontend_GetMenuImageState(g_matchResultBadgeScreen);
    if (state == event) {
        Frontend_DrawMenuImage(g_matchResultBadgeScreen);
        Frontend_AdvanceMenuImageTransition(g_matchResultBadgeScreen);
        if (Frontend_GetMenuImageState(g_matchResultBadgeScreen) != 2) {
            return 0;
        }
        if (g_matchResultBadgeScreen->active != 0) {
            if (g_matchResultBadgeScreen->active != state) {
                return 0;
            }
            Frontend_RequestScreenMode(0);
            Widget_SetWidgetFlag08(window, 1);
            object = &g_frontendScreenStatus;
            Pools_ResetActorPools(object, 0);
            Player_InitializePlayerPool(object - ((char *)&((Shared_MenuData *)0)->object - (char *)0), 0, 0);
            Scene_LoadLevelResources(&g_world, 0, 0);
            ((MatchMenuObjects *)(object))->transition = 8;
        } else {
            Widget_SetWidgetFlag08(window, 0);
            MarkMenuEventHandled();
            if (g_gameSettings.controllerMode == 0) {
                g_resultReplayPending = 0;
                g_resultExitPending = 0;
                if (ScenarioSetup_IsCupSelected() != 0 && ScenarioSetup_StartRandomCupStage() != 0) {
                    Stage_StartConfiguredMatch();
                    return 0;
                }
                next = 20;
            } else {
                g_resultReplayPending = 0;
                g_resultExitPending = 0;
                next = 15;
            }
            SmXlate_SwitchScreen(next);
            return 0;
        }
    } else {
        Frontend_DrawResultSelectionPreview();
    }
    return 0;
}

s32 Frontend_HandleResultsConfirmation(s32 context) {
    s32 *choice;
    s32 taken;
    s32 message;

    if (g_selectionMessageStage <= 0) {
        if (g_matchResultBadgeScreen->phase == 0) {
            g_matchResultBadgeScreen->phase = 1;
            if (Widget_ListHasFlag100(Node_FindWidgetByResourceId(context, CONFIRM_MESSAGE)) == 0) {
                message = CONFIRM_MESSAGE;
            } else {
                message = FALLBACK_MESSAGE;
            }
            Menu_SetFocusedElement(message);
            Tsmos_ActivateControllerState();
        }
        choice = &g_selectionMessageReply[1];
        taken = choice[0];
        if (taken == 1) {
            choice[0] = 0;
            if (choice[-1] != -1) {
                Widget_SetWidgetFlag08(g_matchResultBadgeScreen->buttonAddress, 0);
                g_matchResultBadgeScreen->dirty = 0;
                MarkMenuEventHandled();
                SmXlate_SwitchScreen(choice[-1]);
                return 0;
            }
            Widget_SetWidgetFlag08(g_matchResultBadgeScreen->buttonAddress, 1);
            g_matchResultBadgeScreen->dirty = taken;
        }
    }
    return 0;
}

#if defined(VERSION_US)
unsigned int k_MatchReasonEncodedWords[1] = {
    0x10000B00,
};
#endif

#if defined(VERSION_EU)
unsigned int k_MatchReasonEncodedWordsBlock2[1] = {
    0x00CC00CD,
};
#endif

#if defined(VERSION_DE)
#if defined(VERSION_DE)
void *k_MatchReasonEncodedWordsBlock1[1] = {
    (char *)&g_lastResumedPoolSoundHandle + 0x4,
};
#endif
#endif
