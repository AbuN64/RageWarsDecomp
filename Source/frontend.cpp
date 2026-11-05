#include "include_asm.h"
#include "Common/screen.h"
#include "Common/selectionscreenstate.h"
#include "Common/label.h"
#include "Render/soundelement_playflatsound.h"
#include "types.h"
#include "Common/menu_screen_elements.h"
#include "Common/shared_menureply.h"
#include "Common/menu_screen_setup.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Ui/Tsmos/Screens/scenariosetupscreen.h"
#include "Frontend/smp_overlay.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/menu_options_and_results.h"
#include "Common/gameplay_settings.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/level_goal.h"
#include "Common/active.h"
#include "Common/shared_gameslot.h"
#include "Frontend/stage_placestageopponents.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Achieve/achieve.h"
#include "Frontend/screen.h"
#include "Ui/Tsmos/TSMOS.h"
#include "Ui/X_files/x_plus.h"
#include "Random/random_setuprandomteams.h"
#include "Common/stagepreset.h"
#include "Common/playerprofiles.h"
#include "LIBC.H"
#include "Camera/camera_address_symbols.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Common/osviscale.h"
#include "Common/frontend_video_mode.h"
#include "Common/widget_tree.h"
#include "Frontend/frontend_updateslidergeometry.h"
#include "menu.h"
#include "Frontend/frontend_returnwithoutaction.h"
#include "Common/player_join_requests.h"
#include "Common/characterselectionroot.h"
#include "Frontend/frontend_address_symbols.h"

/* unit SLOT.CPP */
#if defined(VERSION_US_REV1) || defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "Common/selectionscreenstate.h"
#include "Common/label.h"
#include "Common/animation.h"
#include "types.h"
#include "Frontend/smp_overlay.h"
#include "Smp_overlay/smp_overlay.h"

/* Resource ids of this screen are numbered per version: de -4, eu-x 4 relative to us. */
static inline s32 slotRes(s32 id) {
#if defined(VERSION_DE)
    return id - 4;
#elif defined(VERSION_EU_X)
    return id + 4;
#else
    return id;
#endif
}

/* Builds the player-selection menu block for one menu tree: it allocates the block
 * with a 528-byte window request, remembers the tree and the pool SmpOverlay_CreateOverlayNode_Slot returns for it,
 * arms the tree's four option groups with id 513, hands the pool back to SmpOverlay_SetObjectValue, and
 * keeps the windows 492, 491, 486, 563, 510, 512, 511 and their lookup results in the block. The
 * window geometry is nudged by whole groups of four pixels so each window snaps to a 4-pixel grid;
 * the menu item window 488 and the two label windows 496/497 get fixed alpha bytes 110/120, window
 * 493 gets 110, and window 511 is cleared before the block is handed to Focus_AdvanceActiveSlot_Menu. */
s32 Frontend_CreateSlotSelectionMenu(void *menuTree) {
    SlotSelectionWidget *item;
    s32 shift;
    s32 adjust;

    g_profileStatisticsScreen = (SlotSelectionMenuBlock *) Cache_AllocateMemory(528);
    g_profileStatisticsScreen->root = menuTree;
    g_profileStatisticsScreen->list = SmpOverlay_CreateOverlayNode((s32) menuTree, 4);
    SmpOverlay_ShowSlotById((s32) menuTree, 0, slotRes(513));
    SmpOverlay_ShowSlotById((s32) menuTree, 1, slotRes(513));
    SmpOverlay_ShowSlotById((s32) menuTree, 2, slotRes(513));
    SmpOverlay_ShowSlotById((s32) menuTree, 3, slotRes(513));
    SmpOverlay_SetObjectValue((struct Object6C *) g_profileStatisticsScreen->list, 1);

    g_profileStatisticsScreen->menuPhase = 1;
    g_profileStatisticsScreen->reservedWord = 4;
    g_profileStatisticsScreen->item492 = Node_FindWidgetByResourceId(menuTree, slotRes(492));
    g_profileStatisticsScreen->item492->x = g_profileStatisticsScreen->item492->x - g_profileStatisticsScreen->item492->w;
    shift = g_profileStatisticsScreen->item492->w;
    if (shift < 0) {
        shift += 3;
    }
    g_profileStatisticsScreen->round492 = shift >> 2;
    adjust = g_profileStatisticsScreen->item492->w - ((shift >> 2) << 2);
    g_profileStatisticsScreen->item492->x = g_profileStatisticsScreen->item492->x + adjust;

    g_profileStatisticsScreen->item491 = Node_FindWidgetByResourceId(menuTree, slotRes(491));
    g_profileStatisticsScreen->item491->x = g_profileStatisticsScreen->item491->x + g_profileStatisticsScreen->item491->w;
    shift = g_profileStatisticsScreen->item491->w;
    if (shift < 0) {
        shift += 3;
    }
    g_profileStatisticsScreen->round491 = shift >> 2;
    adjust = g_profileStatisticsScreen->item491->w - ((shift >> 2) << 2);
    g_profileStatisticsScreen->item491->x = g_profileStatisticsScreen->item491->x - adjust;

    Node_FindWidgetByResourceId(menuTree, slotRes(488))->alpha = 110;
    g_profileStatisticsScreen->lookup486 = SmpFlicker_CreateFlickerWidget((s32)slotRes(486), 255);

    item = Node_FindWidgetByResourceId(menuTree, slotRes(486));
    g_profileStatisticsScreen->item486 = item;
    Widget_SetWidgetFlag08(item, 0);

    item = Node_FindWidgetByResourceId(menuTree, slotRes(563));
    g_profileStatisticsScreen->item563 = item;
    Widget_SetWidgetFlag08(item, 0);

    Node_FindWidgetByResourceId(menuTree, slotRes(496))->alpha = 110;
    Node_FindWidgetByResourceId(menuTree, slotRes(497))->alpha = 120;

    item = Node_FindWidgetByResourceId(menuTree, slotRes(512));
    g_profileStatisticsScreen->item512 = item;
    Widget_SetWidgetFlag08(item, 0);

    g_profileStatisticsScreen->style = 0;
    g_profileStatisticsScreen->reservedWord1 = 27;
    item = Node_FindWidgetByResourceId(menuTree, slotRes(511));
    g_profileStatisticsScreen->item511 = item;
    Widget_SetWidgetFlag08(item, 0);

    g_profileStatisticsScreen->item511->alpha = 0;
    g_profileStatisticsScreen->reservedWord2 = 25;
    item = Node_FindWidgetByResourceId(menuTree, slotRes(510));
    g_profileStatisticsScreen->item510 = item;

    g_profileStatisticsScreen->player = 0;
    g_profileStatisticsScreen->activeSlot = -1;
    Focus_AdvanceActiveSlot(&g_profileStatisticsScreen->activeSlot);
    Focus_RefreshProfileStatistics();
    Focus_ShowUnlockedEntries(g_profileStatisticsScreen->style);
    Node_FindWidgetByResourceId(menuTree, slotRes(493))->alpha = 110;
    g_profileStatisticsScreen->focus = 0;
    return 0;
}
#endif

/* Steps the record screen's transition state machine: slides the two panels in or out, swaps the
   visible item groups as each phase's timer runs out, and while idle (state 3) pulses the cursor's
   style from the elapsed time and moves the cursor to the node now under focus. */
s32 Frontend_AnimateSlotSelectionMenu(s32 element, s32 eventId, s32 animationStep) {
    NodeFrontendAnimateSlotSelectionMenu *node;

    switch (((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state) {
    case 1:
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->left->x += ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->leftStep;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->right->x -= ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->rightStep;
        if (--((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer <= 0) {
            SoundElement_PlayFlatSound(3705);
            Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupA, 1);
            SmpFlicker_StartFlicker(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->fade, 4);
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 4;
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer = 4;
        }
        break;
    case 2:
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->left->x -= ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->leftStep;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->right->x += ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->rightStep;
        if (--((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer <= 0) {
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 3;
            MarkMenuEventHandled();
            Menu_ReturnToPreviousScreen();
            return 0;
        }
        break;
    case 4:
        if (SmpFlicker_IsFlickerIdle(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->fade) != 0) {
            SmpFlicker_RestoreFlickerValue(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->fade);
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 6;
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer = 4;
            Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupB, 1);
            Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupC, 1);
        }
        break;
    case 5:
        SoundElement_PlayFlatSound(3704);
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 2;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer = 4;
        Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupB, 0);
        Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupC, 0);
        Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupA, 0);
        break;
    case 6:
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->styleValue += ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->styleStep;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupC->style += ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->alphaStep;
        Focus_ShowUnlockedEntries(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->styleValue);
        if (--((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer <= 0) {
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupC->style = 100;
            Focus_ShowUnlockedEntries(110);
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 3;
            Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->cursor, 1);
        }
        break;
    case 7:
        break;
    }

    if (((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state == 3) {
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->clock += animationStep;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->cursor->style = Math_Cosf((f32) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->clock * 0.0033333334f) * 30.0f + 220.0f;
        node = SmpOverlay_GetSlotValue(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->handle, 0);
        if (node != ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->focus) {
            SoundElement_PlayFlatSound(3710);
            if (((FrontendPanelTransitionView *) g_profileStatisticsScreen)->focus != 0) {
                ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->focus->style = 110;
            }
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->focus = node;
            node->style = 225;
            Focus_RefreshUnlockedFocusLabel();
            Focus_UpdateFocusCaption();
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->cursor->x = node->x - 2;
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->cursor->y = node->y;
        }
    }
    return 0;
}

#if !(defined(VERSION_EU) || defined(VERSION_US))
unsigned int k_SlotZeroWords[1] = {
    0x00000000,
};
#endif
#if defined(VERSION_EU) || defined(VERSION_US)
const unsigned int k_SlotZeroWords[1] = {
    0x00000000,
};
#endif

/* unit SETUP.CPP */
/* Opens the screen g_setupScreen: allocates its 0x470-byte state for the window, sets up the list,
   the left and right arrows (shifted by their width and snapped to 4 pixels), the labels and
   items of the window with their alpha and visibility, resets the selection and the counters at
   g_selectionMessageReply.ready, clears the pending flag at 0x91 of the eight g_playerSettings_Achieve records, places the four
   character models (ids 0xEA6 to 0xEA9, x 0, -6, -13, -19) and a fifth model 0xEA6, then issues
   request 0xE78 through SoundElement_PlayFlatSound and calls Menu_InitializeOptionsScene; returns zero. */

#if defined(VERSION_DE)
#define ID_2FE 762
#define ID_2FF 764
#define ID_300 763
#define ID_301 765
#define ID_303 767
#define ID_306 770
#define ID_308 772
#define ID_309 773
#define ID_30A 775
#define ID_30B 776
#define ID_30C 774
#define ID_30D 777
#define ID_30E 778
#define ID_30F 779
#define ID_310 780
#define ID_35D 857
#elif defined(VERSION_EU_X)
#define ID_2FE 771
#define ID_2FF 772
#define ID_300 568
#define ID_301 773
#define ID_303 775
#define ID_306 778
#define ID_308 780
#define ID_309 781
#define ID_30A 783
#define ID_30B 784
#define ID_30C 782
#define ID_30D 785
#define ID_30E 787
#define ID_30F 786
#define ID_310 788
#define ID_35D 865
#else
#define ID_2FE 766
#define ID_2FF 767
#define ID_300 768
#define ID_301 769
#define ID_303 771
#define ID_306 774
#define ID_308 776
#define ID_309 777
#define ID_30A 778
#define ID_30B 779
#define ID_30C 780
#define ID_30D 781
#define ID_30E 782
#define ID_30F 783
#define ID_310 784
#define ID_35D 861
#endif

s32 CScenarioSetup_OpenScenarioSetupScreen(void *window) {
    SetupModelVector scale;
    SetupModelVector position;
    SetupModelVector rotation;
    SetupModelVector offset;
    MenuWidget *item1, *item2, *item3, *item4, *item5, *item6, *item7, *item8;
    MenuWidget *opacityItem;
    f32 z;
    ListScreenRecord *record;
    s32 i;
    s32 x;
    s32 id;

    g_setupScreen = Cache_AllocateMemory(sizeof(SetupScreen));
    g_setupScreen->window = window;
    g_setupScreen->list = SmpOverlay_CreateOverlayNode(window, 4);
    SmpOverlay_ShowSlotById(window, 0, ID_2FF);
    SmpOverlay_ShowSlotById(window, 1, ID_2FF);
    SmpOverlay_ShowSlotById(window, 2, ID_2FF);
    SmpOverlay_ShowSlotById(window, 3, ID_2FF);
    g_setupScreen->screenState = 1;
    g_setupScreen->pulsePhase = 0;
    g_setupScreen->stateCountdown = 4;

    item1 = Node_FindWidgetByResourceId(window, ID_306);
    g_setupScreen->left = item1;
    item1->x -= item1->width;
    g_setupScreen->leftCount = g_setupScreen->left->width / 4;
    x = g_setupScreen->left->width - g_setupScreen->leftCount * 4;
    g_setupScreen->left->x += x;

    item2 = Node_FindWidgetByResourceId(window, ID_30F);
    g_setupScreen->right = item2;
    item2->x += item2->width;
    g_setupScreen->rightCount = g_setupScreen->right->width / 4;
    x = g_setupScreen->right->width - g_setupScreen->rightCount * 4;
    g_setupScreen->right->x -= x;

    opacityItem = Node_FindWidgetByResourceId(window, ID_30A);
    opacityItem->alpha = 110;
    item3 = Node_FindWidgetByResourceId(window, ID_35D);
    g_setupScreen->widget35D = item3;
    item3->alpha = 65;
    Widget_SetWidgetFlag08(g_setupScreen->widget35D, 0);
    g_setupScreen->text3E4 = SmpFlicker_CreateFlickerWidget(ID_303, 110);
    item4 = Node_FindWidgetByResourceId(window, ID_301);
    g_setupScreen->widget301 = item4;
    Widget_SetWidgetFlag08(item4, 0);
    g_setupScreen->label = Node_FindWidgetByResourceId(window, ID_30E);
    g_setupScreen->widget310 = Node_FindWidgetByResourceId(window, ID_310);
    ScenarioSetup_HideSetupCatalogue();
    g_setupScreen->selection = 0;
    g_setupScreen->category = 0;
    ScenarioSetup_RefreshSelectedArenaLabel();
    ScenarioSetup_LoadSetupArenaLabel();
    g_selectionMessageReply.ready = 0;
    g_selectionMessageReply.value = -1;
    g_setupScreen->widget308 = Node_FindWidgetByResourceId(window, ID_308);
    opacityItem = Node_FindWidgetByResourceId(window, ID_309);
    opacityItem->alpha = 110;
    g_setupScreen->reservedWord3 = 0;
    item5 = Node_FindWidgetByResourceId(window, ID_30B);
    g_setupScreen->widget30B = item5;
    item5->alpha = 140;
    Widget_SetWidgetFlag08(g_setupScreen->widget30B, 1);
    item6 = Node_FindWidgetByResourceId(window, ID_30D);
    g_setupScreen->widget30D = item6;
    item6->alpha = 140;
    Widget_SetWidgetFlag08(g_setupScreen->widget30D, 0);
    item7 = Node_FindWidgetByResourceId(window, ID_30C);
    g_setupScreen->widget30C = item7;
    item7->alpha = 0xFF;
    g_setupScreen->widget2FE = Node_FindWidgetByResourceId(window, ID_2FE);
    item8 = Node_FindWidgetByResourceId(window, ID_300);
    g_setupScreen->widget300 = item8;
    Widget_SetWidgetFlag08(item8, 1);
    Tsmos_DeactivateControllerState();
    g_setupScreen->controllerActivated = 0;
    g_setupScreen->reservedWord1 = 0;
    g_setupScreen->reservedWord2 = -1;

    for (i = 0; i < 8; i++) {
        record = &g_playerSettings[i];
        if (record->m_IsBot == 1) {
            record->active = 0;
            record->m_IsBot = 0;
        }
    }
    Tsmos_SetMenuModelFlag(1);

    x = 0;
    id = 0;
    scale.value.x = g_setupRowPreviewScale;
    scale.value.y = g_setupRowPreviewScale;
    scale.value.z = g_setupRowPreviewScale;
    rotation.value.x = 0.0f;
    rotation.value.y = 0.0f;
    rotation.value.z = 0.0f;
    offset.value.x = 0.0f;
    offset.value.y = g_setupRowPreviewYOffset;
    offset.value.z = 0.0f;
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            x = 0;
            id = 3750;
            break;
        case 1:
            x = -6;
            id = 3751;
            break;
        case 2:
            x = -13;
            id = 3752;
            break;
        case 3:
            x = -19;
            id = 3753;
            break;
        }
        position.value.x = x;
        position.value.y = g_setupRowPreviewY;
        z = g_setupPreviewDepth;
        position.value.z = z;
        Frontend_InitModelPreviewTransform(&g_setupScreen->models[i].initial, id, scale.words, position.words);
        Frontend_SetPreviewRotation(&g_setupScreen->models[i].rotation, rotation.words);
        Frontend_SetPreviewRotationSpeed(&g_setupScreen->models[i].offset, offset.words);
    }
    scale.value.x = g_setupExtraPreviewScale;
    scale.value.y = g_setupExtraPreviewScale;
    scale.value.z = g_setupExtraPreviewScale;
    position.value.z = z;
    position.value.x = g_setupExtraPreviewX;
    position.value.y = g_setupExtraPreviewY;
    Frontend_InitModelPreviewTransform(&g_setupScreen->models[4].initial, 3750, scale.words, position.words);
    Frontend_SetPreviewRotation(&g_setupScreen->models[4].rotation, rotation.words);
    Frontend_SetPreviewRotationSpeed(&g_setupScreen->models[4].offset, offset.words);
    SoundElement_PlayFlatSound(3704);
    Menu_InitializeOptionsScene();
    return 0;
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)

#endif

/* unit SETUPRESULTS.CPP */
#include <PR/gbi.h>
#include <platform_sdk.h>
#include "Common/sharedtrackobjectprefix.h"
#include "Common/sessionhandlerrow.h"
#include "Common/menu_screen_elements.h"
#include "Common/cheatcode.h"
#include "Engine/control.h"
#include "types.h"
#include "Frontend/scenario_result_rows.h"
#include "Ui/Tsmos/Screens/scenariosetupscreen.h"
#include "Preview/preview.h"
#include "Frontend/frontend_address_symbols.h"

/* Draw callback of the versus results screen g_setupScreen: on draw event 1 in states 3, 8 or 9 it
   sets the fill g_menuModelFillEnabled to blended white, restores the full-screen clip, and at alpha 210 draws
   the four player panels (on screen 0x14 with no pending pause) and the tie panel at 0x308 unless a
   winner is set, then resets the fill. On update event 0 (unless GetMenuScreenOwner reports 0x19) it
   plays the winner's voice on the twentieth frame, raises the banner blink six frames later, and
   fades the two banner sprites out by 30 per frame before hiding them. Returns zero. */
s32 Frontend_DrawSetupResultPanels(void *element, void *eventId, s32 event) {
    s32 i;
    s32 alpha;

    if (event == 1 && (((struct VersusResultsScreen *)g_setupScreen)->state == 3 || ((struct VersusResultsScreen *)g_setupScreen)->state == 8 || ((struct VersusResultsScreen *)g_setupScreen)->state == 9)) {
        /* Both stores are kept: the first writes the mode field of the same word as the fill-enabled flag. */
        ((struct MenuRenderFill *)&g_menuModelFillEnabled)->mode = 0;
        g_menuModelFillEnabled = 1;
        g_menuModelFillColor[0] = 255.0f;
        g_menuModelFillColor[1] = 255.0f;
        g_menuModelFillColor[2] = 255.0f;
        g_menuModelFillColor[3] = 255.0f;
        gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, g_hudReferenceViewportWidth - 1, g_hudReferenceViewportHeight - 1);
        g_menuModelFillColor[3] = 210.0f;
        if (GetMenuScreenOwner() == 20 && g_selectionMessageReply.ready == 0) {
            for (i = 0; i < 4; i++) {
#if defined(VERSION_DE)

#if defined(VERSION_DE)
Preview_DrawMenuModelItem
#else
Frontend_DrawResultModelPreviewDe
#endif
(((struct VersusResultsScreen *)g_setupScreen)->panels[i]);
#else

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Preview_DrawMenuModelItem
#else
Preview_DrawMenuModelItem_Setupresults
#endif
(((struct VersusResultsScreen *)g_setupScreen)->panels[i]);
#endif
            }
        }
        if (((struct VersusResultsScreen *)g_setupScreen)->winner == 0) {
#if defined(VERSION_DE)

#if defined(VERSION_DE)
Preview_DrawMenuModelItem
#else
Frontend_DrawResultModelPreviewDe
#endif
(((struct VersusResultsScreen *)g_setupScreen)->tie);
#else

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Preview_DrawMenuModelItem
#else
Preview_DrawMenuModelItem_Setupresults
#endif
(((struct VersusResultsScreen *)g_setupScreen)->tie);
#endif
        }
        g_menuModelFillEnabled = 0;
        g_menuModelFillColor[3] = 255.0f;
    }
    if (event == 0 && GetMenuScreenOwner() != 25) {
        if (((struct VersusResultsScreen *)g_setupScreen)->frames < 20) {
            if (++((struct VersusResultsScreen *)g_setupScreen)->frames == 20 && ((struct VersusResultsScreen *)g_setupScreen)->winner > 0) {
                Menu_SetOptionsSceneSelection(ScenarioSetup_ResolveArenaFromSelection(ScenarioSetup_CategoryToList(((struct VersusResultsScreen *)g_setupScreen)->winnerSlot), ((struct VersusResultsScreen *)g_setupScreen)->winner) + 601);
                ((struct VersusResultsScreen *)g_setupScreen)->blinkDelay = 0;
            }
        }
        if (((struct VersusResultsScreen *)g_setupScreen)->blinkDelay != -1) {
            if (++((struct VersusResultsScreen *)g_setupScreen)->blinkDelay >= 6) {
                ((struct VersusResultsScreen *)g_setupScreen)->blinking = 1;
                ((struct VersusResultsScreen *)g_setupScreen)->blinkDelay = -1;
            }
        }
        if (((struct VersusResultsScreen *)g_setupScreen)->blinking == 1) {
            alpha = ((struct VersusResultsScreen *)g_setupScreen)->banner->value;
            alpha -= 30;
            if (alpha <= 0) {
                ((struct VersusResultsScreen *)g_setupScreen)->blinking = 0;
                Widget_SetWidgetFlag08(((struct VersusResultsScreen *)g_setupScreen)->bannerShadow, 0);
                Widget_SetWidgetFlag08(((struct VersusResultsScreen *)g_setupScreen)->banner, 0);
                alpha = 0xFF;
            }
            ((struct VersusResultsScreen *)g_setupScreen)->banner->value = alpha;
            ((struct VersusResultsScreen *)g_setupScreen)->bannerShadow->value = alpha;
        }
    }
    return 0;
}

/* unit STAGE.CPP */
/* Prepares a match: stops the current screen, starts screen 2, resets the eight player status
   records (clearing bytes 0x94 and 0x95 and, for human slots, the team byte 0x92) while counting
   active humans, clears the match counters, and outside mode 0 looks up the stage default for the
   first active player through Achieve_CopyPreset and resets the round state. It then runs the setup of
   the current rule set g_currentResultMode, copies each active human's name and the five profile bytes at 0x189
   of their player record into status bytes 0x7B, 0x7D, 0x79, 0x7A and 0x82, sets the game mode (team mode 2 falls back to 1 with fewer than two
   humans) and, when SoundElement_GetMusicPlaybackEnabled allows, picks a random arena 0x38 to 0x3B. */


void Stage_StartConfiguredMatch(void) {
    u8 *settings;
    u8 *config;
    struct MatchPlayerStatus *status;
    s32 humans;
    s32 i;
    s32 first;
    CGameStatus *match;

    MarkMenuEventHandled();
    SmXlate_SwitchScreen(2);
    Tsmos_RequestFrontendShutdown();
    humans = 0;
    settings = (u8 *)&g_gameSettings;
    for (i = 0; i < 8; i++) {
        status = (struct MatchPlayerStatus *)((u8 *)&((Shared_Game *)settings)->playerSettings[i]);
        status->lives = 0;
        status->score = 0;
        if (status->computer == 0) {
            status->team = 0xFF;
        }
        if (status->computer == 0 && status->joined == 1) {
            humans++;
        }
    }
    match = &g_gameSettings.counters;
    match->enabled = 0;
    match->m_bPhoenixRoomActive = 0;
    g_currentStagePreset = 0;
    if (settings[13] != 0) {
        first = 0;
        while (((struct MatchPlayerStatus *)((u8 *)&((Shared_Game *)settings)->playerSettings[first]))->joined == 0) {
            first++;
        }
        status = (struct MatchPlayerStatus *)((u8 *)&((Shared_Game *)settings)->playerSettings[first]);
        switch (settings[13]) {
        case 1:
            g_currentStagePreset = Achieve_CopyPreset(g_selectedLevelId, 0, status->kind);
            break;
        case 2:
            g_currentStagePreset = Achieve_CopyPreset(g_selectedLevelId, 1, 0);
            break;
        case 3:
            g_currentStagePreset = Achieve_CopyPreset(g_selectedLevelId, 3, 0);
            break;
        case 4:
            g_currentStagePreset = Achieve_CopyPreset(g_selectedLevelId, 2, 0);
            break;
        }
        g_gameSettings.counters.humanWon = 0;
        Stage_PlaceStageOpponents();
    }
    switch (g_currentResultMode.kind) {
    case 0:
        Random_StartCaptureTheFlagMatch();
        break;
    case 1:
        Random_StartFragTagMatch();
        break;
    case 2:
        Random_StartIndividualMatch();
        break;
    case 3:
        Random_StartTeamMatch();
        break;
    }
    for (i = 0; i < 4; i++) {
        status = (struct MatchPlayerStatus *)((u8 *)&((Shared_Game *)settings)->playerSettings[i]);
        if (status->joined == 1 && status->computer == 0) {
            XPlus_CopyString(status->name, g_localPlayerProfiles[i].name);
            if (settings[13] != 0) {
                status->team = 0;
            } else {
                status->team = 0xFF;
            }
            status->profileFirst = g_localPlayerProfiles[i].setting[0];
            status->profileSecond = g_localPlayerProfiles[i].setting[1];
            status->profileThird = g_localPlayerProfiles[i].setting[2];
            status->profileFourth = g_localPlayerProfiles[i].setting[3];
            status->profileFifth = g_localPlayerProfiles[i].setting[4];
        }
    }
    config = (u8 *)&g_gameSettings;
    if (config[1408] == 2 && humans >= 2) {
        Frontend_RequestScreenMode(1);
    } else {
        Frontend_RequestScreenMode(config[1408]);
    }
    if (SoundElement_GetMusicPlaybackEnabled() != 0) {
        SoundElement_SetMusicPlaybackEnabled(Graphu64_NextRandom() % 4 + 56);
    }
}

/* Places the computer opponents of the stage entry g_currentStagePreset: first frees the player settings
   records still marked joined and locked, then for each of the entry's seven opponent records with a
   nonzero kind places it through Random_AddStageOpponent and, by kind, sets the returned slot's controlMode
   and the match counters: kind 12 sets 2 with enabled, timer 100 and cooldown -1; 13 sets 1 with
   enabled; 16 sets 2; 14 sets 1 with enabled for the first such opponent and 0 afterwards; 15 sets 1
   with enabled and clears m_nTalsetLives; any other kind sets 0 and, once a kind 15 opponent was placed,
   marks the slot active. */
void Stage_PlaceStageOpponents(void) {
    CGameStatus *match;
    Shared_PlayerSettingsRecord *player;
    s32 boss;
    s32 escorted;
    s32 i;
    s32 slot;
    s32 on;
    Shared_Game *game;

    boss = 0;
    escorted = 0;
    match = &g_gameSettings.counters;
    for (i = 0; i < 8; i++) {
        player = &g_gameSettings.playerSettings[i];
        if (player->enabled == 1 && player->locked == player->enabled) {
            player->enabled = 0;
            player->locked = 0;
        }
    }
    for (i = 0; i < 7; i++) {
        on = 1;
        game = &g_gameSettings;
        if (g_currentStagePreset->opponents[i][0] == 0) {
            continue;
        }
        switch (g_currentStagePreset->opponents[i][0]) {
        case 12:
            match->enabled = on;
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            (game->playerSettings + slot)->controlMode = 2;
            match->m_nBastilleShield = 100;
            match->m_nBastilleTimer = -1;
            break;
        case 13:
            match->enabled = on;
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            (game->playerSettings + slot)->controlMode = on;
            break;
        case 16:
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            (game->playerSettings + slot)->controlMode = 2;
            break;
        case 14:
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            if (boss == 0) {
                boss = 1;
                match->enabled = on;
                (game->playerSettings + slot)->controlMode = on;
            } else {
                (game->playerSettings + slot)->controlMode = 0;
            }
            break;
        case 15:
            escorted = 1;
            match->enabled = on;
            match->m_nTalsetLives = 0;
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            (game->playerSettings + slot)->controlMode = on;
            break;
        default:
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            game->playerSettings[slot].controlMode = 0;
            if (escorted) {
                game->playerSettings[slot].active = on;
            }
            break;
        }
    }
}

/* unit K_FRONTENDENCODEDWORDS.CPP */
#if defined(VERSION_US)
extern unsigned int k_FrontendEncodedWords[3];
#endif

/* unit SCREEN.CPP */
#include <platform_sdk.h>
#include "Common/boot_tv_type.h"
#include "Frontend/screen.h"
#include "Frontend/screen_video_mode.h"
#include "Common/g_frontendkeepcurrentvideomodeonce.h"
#include "Common/g_selectionmessagestage.h"
#include "Resources/frontend_applyvideomode_data.h"
#include "Frontend/frontend_address_symbols.h"

/* Selects the video mode and applies framebuffer and display configuration; the mode-to-word-array cast preserves configuration-store and mode-load scheduling. */
s32 Defs_GetMemorySize();

void Frontend_SetVideoModeAndViewports(unsigned, int, int, int, int, int);
static inline void Frontend_ApplyVideoConfig(int a,int b,int c,int d,int e) {
        g_frontendViDitherFilterEnabled = a;
        g_geometryAntialiasingEnabled = b;
        g_frontendVideoModeVariantBit = c;
        g_geometryTextureFilterOverride = d;
        g_geometryTexturePerspectiveOverride = e;
}
static inline void Frontend_ApplyHudReferenceViewport(s32 *videoMode) {
        g_hudReferenceViewportWidth = (s32) videoMode[0];
        g_hudReferenceViewportHeight = (s32) videoMode[1];
        Frontend_SetVideoModeAndViewports(videoMode[0], videoMode[1], videoMode[2], videoMode[3], videoMode[4], videoMode[5]);
}
void Frontend_ApplyVideoMode(void) {
    char *unusedPointer;
    s32 featureCommands;
    s32 unusedValue;
    s32 unusedValue1;
    struct FrontendVideoModeParameters *videoMode;
    videoMode = NULL;
    g_frontendStartupState = 2;
    if (g_frontendCurrentVideoModeIndex == -1) {
        if (Defs_GetMemorySize() != 0x400000) {
            g_frontendCurrentVideoModeIndex = 1;
        } else {
            g_frontendCurrentVideoModeIndex = 0;
        }
        g_frontendSavedVideoModeIndex = (u8)g_frontendCurrentVideoModeIndex;
    }
    switch(g_consoleTvType) {
    case 1: videoMode=&((struct FrontendVideoModeParameters *)g_frontendRegionVideoModes)[g_frontendCurrentVideoModeIndex];break;
    case 0:case 2:videoMode=&g_frontendDefaultVideoModes[g_frontendCurrentVideoModeIndex];break;
    }
    if (videoMode != NULL) {
        FrontendRenderConfig config=g_frontendVideoModeRenderConfigs[g_frontendCurrentVideoModeIndex];
        Frontend_ApplyVideoConfig(config.viDitherFilterEnabled,config.antialiasingEnabled,config.videoModeVariant,config.textureFilterOverride,config.texturePerspectiveOverride);
        Frontend_ApplyHudReferenceViewport((s32 *)videoMode);
        featureCommands = 128;
        if (g_frontendViDitherFilterEnabled != 0) {
            featureCommands = 64;
        }
        osViSetSpecialFeatures(featureCommands);
        osViSetSpecialFeatures(32);
        osViSetSpecialFeatures(2);
    }
}

/* VI start registers (hStart, vStart) hold the first pixel/line in the high half and the last in the low half. The
   ROM reads the halves through a stack copy, so a little-endian host keeps the low half at the first address. */
typedef union VideoInterval {
    u32 packed;
    struct {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        u16 last, first;
#else
        u16 first, last;
#endif
    } half;
} VideoInterval;
typedef union VideoHorizontal {
    u32 packed;
    struct {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        u32 last : 16; s32 first : 16;
#else
        s32 first : 16; u32 last : 16;
#endif
    } edge;
} VideoHorizontal;
/* Resizes the selected VI mode (table g_videoModeLabels[g_frontendVideoModeId], copied to g_frontendVideoMode) to width x height around its
 * horizontal and field centres moved by (x, y), shrinks the active area by the borders, rescales X and Y, clamps the
 * last pixel and lines to the original mode and applies it. */
void Frontend_SetVideoViewport(s32 width, s32 height, s32 x, s32 y, s32 borderX, s32 borderY) {
    VideoInterval vertical[2];
    VideoInterval originalVertical[2];
    u16 centerY[2];
    Modep *mode = &g_frontendVideoMode;
    VideoHorizontal horizontal, originalHorizontal;
    u32 scaleY;
    s32 centerX, scaleX;

    Libc_CopyBytes(mode, &g_videoModeLabels[(s16)g_frontendVideoModeId], 80);
    horizontal.packed = mode->comRegs.hStart;
    vertical[0].packed = mode->fldRegs[0].vStart;
    originalHorizontal = horizontal;
    centerX = ((s16)horizontal.edge.last - horizontal.edge.first) / 2 + horizontal.edge.first - x;
    centerY[0] = vertical[0].half.first + ((s16)vertical[0].half.last - (s16)vertical[0].half.first) / 2;
    scaleY = mode->fldRegs[0].yScale;
    horizontal.edge.first = centerX - width / 2 + borderX / 2;
    horizontal.edge.last = centerX + width / 2 - borderX * 2;
    vertical[1].packed = mode->fldRegs[1].vStart;
    centerY[1] = vertical[1].half.first + ((s16)vertical[1].half.last - (s16)vertical[1].half.first) / 2;
    centerY[0] -= y;
    vertical[0].half.first = centerY[0] - height / 2 + borderY / 2;
    vertical[0].half.last = centerY[0] + height / 2 - borderY * 2;
    scaleY &= 0xFFFF0000;
    scaleY |= (((height << 11) /
        ((s16)vertical[0].half.last - (s16)vertical[0].half.first)) & 0xFFFF);
    originalVertical[0].packed = mode->fldRegs[0].vStart;
    centerY[1] -= y;
    vertical[1].half.first = centerY[1] - height / 2 + borderY / 2;
    vertical[0].half.last -= 3;
    vertical[1].half.last = centerY[1] + height / 2 - borderY * 2;
    originalVertical[1].packed = mode->fldRegs[1].vStart;
    vertical[1].half.last -= 3;
    scaleX = (width << 10) / ((s16)horizontal.edge.last - horizontal.edge.first);
    if ((s16)originalVertical[0].half.last < (s16)vertical[0].half.last) vertical[0].half.last = originalVertical[0].half.last;
    if ((s16)originalVertical[1].half.last < (s16)vertical[1].half.last) vertical[1].half.last = originalVertical[1].half.last;
    if ((s16)originalHorizontal.edge.last < (s16)horizontal.edge.last) horizontal.edge.last = originalHorizontal.edge.last;
    mode->fldRegs[0].yScale = scaleY;
    mode->fldRegs[1].yScale = scaleY;
    mode->fldRegs[0].origin = 0;
    mode->fldRegs[1].origin = width * 2;
    mode->comRegs.width = width;
    mode->comRegs.xScale = scaleX;
    mode->comRegs.hStart = horizontal.packed;
    mode->fldRegs[0].vStart = vertical[0].packed;
    mode->fldRegs[1].vStart = vertical[1].packed;
    osViSetMode(mode);
}

/* Cycles the video mode within the memory budget and chooses dimensions large enough for both active buffers. */
void Frontend_AdvanceVideoMode(void)
{
  int region = 0;
  int budget;
  int memory;
  int w;
  int h;
  int *mode;
  switch (g_consoleTvType)
  {
    case 0:
    case 2:
      region = 1;
      break;
    case 1:
      break;
  }
  mode = (int *) (&g_frontendRegionVideoModes[region][g_frontendCurrentVideoModeIndex]);
  memory = Defs_GetMemorySize();
  budget = 63072;
  if (memory != 0x400000)
  {
    budget = 172800;
  }
  if (!g_frontendKeepCurrentVideoModeOnce)
  {
    g_frontendCurrentVideoModeIndex = (g_frontendCurrentVideoModeIndex + 1) % g_frontendVideoModeCounts[region];
    while ((mode[0] * mode[1]) > budget)
    {
      g_frontendCurrentVideoModeIndex = (g_frontendCurrentVideoModeIndex + 1) % g_frontendVideoModeCounts[region];
    }
  }
  else
  {
    g_frontendKeepCurrentVideoModeOnce = 0;
  }
  memory = g_frontendRegionVideoModes[region][g_frontendActiveVideoModeIndex].width;
  w = g_frontendRegionVideoModes[region][g_frontendCurrentVideoModeIndex].width;
  if (w < memory)
  {
    w = g_frontendRegionVideoModes[region][g_frontendActiveVideoModeIndex].width;
  }
  g_hudReferenceViewportWidth = w;
  h = g_frontendRegionVideoModes[region][g_frontendCurrentVideoModeIndex].height;
  if (h < g_frontendRegionVideoModes[region][g_frontendActiveVideoModeIndex].height)
  {
    h = g_frontendRegionVideoModes[region][g_frontendActiveVideoModeIndex].height;
  }
  g_hudReferenceViewportHeight = h;
}
/* Stores its argument in g_frontendCurrentVideoModeIndex, which Frontend_GetCurrentVideoModeIndex_de returns, and calls Frontend_ApplyVideoMode. */
void Frontend_ApplyScreenModeValue(s32 value) {
    g_frontendCurrentVideoModeIndex = value;
    Frontend_ApplyVideoMode();
}
/* Gives g_selectionMessageStage the value 0x14 when it is still zero. */
void Frontend_StartScreenModeFade(void) {
    if (g_selectionMessageStage == 0) {
        g_selectionMessageStage = 20;
    }
}
/* Detects the storage configuration and updates the cached selection. */
void Frontend_UpdateScreenMode(void) {
    if (g_frontendCurrentVideoModeIndex == -1) {
        if (Defs_GetMemorySize() != 0x400000) {
            g_frontendCurrentVideoModeIndex = 1;
        } else {
            g_frontendCurrentVideoModeIndex = 0;
        }
        g_frontendSavedVideoModeIndex = (u8)g_frontendCurrentVideoModeIndex;
    }
    if ((g_selectionMessageStage < 5) && (g_frontendActiveVideoModeIndex != g_frontendCurrentVideoModeIndex)) {
        Frontend_ApplyVideoMode();
        g_frontendActiveVideoModeIndex = g_frontendCurrentVideoModeIndex;
    }
}
/* Returns the palette for the current screen mode g_frontendCurrentVideoModeIndex: modes 1, 2 and 3 have their own, mode 0
   and anything else use the first. */
int *Frontend_GetScreenModePalette(void) {
    switch (g_frontendCurrentVideoModeIndex) {
    case 0:
    default:
        return &g_frontendScreenModePaletteDefault;
    case 1:
        return &g_frontendScreenModeHiRezLabel;
    case 2:
        return &g_frontendScreenModeHiRezLetterboxLabel;
    case 3:
        return &g_frontendScreenModeLoRezLetterboxLabel;
    }
}
/* Requests a new value when no change is pending: if g_selectionMessageStage is zero and the value differs from
   g_frontendCurrentVideoModeIndex, remembers the old value in g_frontendActiveVideoModeIndex, stores the new one, sets g_frontendKeepCurrentVideoModeOnce and starts
   the 0x14-tick countdown g_selectionMessageStage. */
void Frontend_RequestScreenMode(s32 value) {
    if (g_selectionMessageStage == 0 && value != g_frontendCurrentVideoModeIndex) {
        g_frontendKeepCurrentVideoModeOnce = 1;
        g_frontendActiveVideoModeIndex = g_frontendCurrentVideoModeIndex;
        g_frontendCurrentVideoModeIndex = value;
        g_selectionMessageStage = 20;
    }
}
/* Returns the word held in g_frontendCurrentVideoModeIndex. */
s32 Frontend_GetScreenMode(void) {
    return g_frontendCurrentVideoModeIndex;
}
/* Selects the video mode and resets viewport dimensions on the linked views. */
struct VideoViewList {
    FrontendScreenViewport *head;
    char reserved[0x1C];
    FrontendScreenViewport defaultView;
};

void Frontend_SetVideoModeAndViewports(unsigned width, int viewportHeight, int offsetX, int offsetY, int borderX, int borderY) {
    int flags = 0;
    int region = 0;
    FrontendScreenViewport *node;
    float height;

    switch (g_consoleTvType) {
    case 0: region = 1; break;
    case 1: break;
    case 2: region = 2; break;
    }
    if (width > 320) flags |= 4;
    if (g_frontendVideoModeVariantBit) flags |= 2;
    if (width > 320) flags |= 1;
    g_frontendVideoModeId = VideoModeIds[region][flags];
    Frontend_SetVideoViewport(width, viewportHeight, offsetX, offsetY, borderX, borderY);
    node = &((struct VideoViewList *)&g_gameplayCameraList)->defaultView;
    if (node) {
        node->width = g_hudReferenceViewportWidth;
        height = g_hudReferenceViewportHeight;
        node->x = 0;
        node->y = 0;
        node->height = height;
    }
    node = ((struct VideoViewList *)&g_gameplayCameraList)->head;
    while (node) {
        node->x = 0;
        node->y = 0;
        node->width = g_hudReferenceViewportWidth;
        node->height = g_hudReferenceViewportHeight;
        node = node->next;
    }
}

/* unit SLIDER.CPP */
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1) || defined(VERSION_DE) || defined(VERSION_EU)
/* Slider widget message handler: clamps the current value into range, then dispatches on the
   message to get/set the value, range, step or user word, adjusts by one step, or posts the new
   value to the parent. */
#include "types.h"
#include "Common/runtime_declarations.h"

s32 Frontend_HandleSliderMessage(Slider *slider, s32 msg, s32 valueOrUpperBound, s32 notifyOrLowerBound) {
    Slider *widget = slider;

    if (widget->value < widget->min) {
        widget->value = widget->min;
    }
    if (widget->value > widget->max) {
        widget->value = widget->max;
    }

    switch (msg) {
        case 5:
        case 8:
            if (notifyOrLowerBound != 0) {
                s32 v = widget->value + widget->step;
                s32 hi = widget->max;
                widget->value = v;
                if (hi < v) {
                    widget->value = hi;
                }
            }
            break;

        case 6:
        case 7:
            if (notifyOrLowerBound != 0) {
                s32 v = widget->value - widget->step;
                s32 lo = widget->min;
                widget->value = v;
                if (v < lo) {
                    widget->value = lo;
                }
            }
            break;

        case 4096:
            return widget->value;

        case 4098:
            return widget->min;

        case 4099:
            return widget->max;

        case 4102:
            return widget->step;

        case 4104:
            return widget->flags;

        case 4101:
            if (valueOrUpperBound >= widget->min && valueOrUpperBound <= widget->max) {
                widget->value = valueOrUpperBound;
            }
            break;

        case 4100:
            if (widget->min < valueOrUpperBound) {
                widget->max = valueOrUpperBound;
            }
            if (notifyOrLowerBound < widget->max) {
                widget->min = notifyOrLowerBound;
            }
            break;

        case 4103:
            if (valueOrUpperBound < (widget->max - widget->min)) {
                widget->step = valueOrUpperBound;
            }
            break;

        case 4105:
            widget->flags = valueOrUpperBound;
            break;

        default:
            return 0;
    }

    Frontend_UpdateSliderGeometry((Slider *)widget);
    Menu_RouteElementEvent(GetMenuScreenOwner(), 4106, slider->parentId, widget->value, 0);
    MarkMenuEventHandled();
    return 0;
}
#endif

#if !(defined(VERSION_US))
/** Perform no work. */
void Frontend_ReturnWithoutAction(void) {
}
#endif

/* Lays out a slider from its value: scales value - min over max - min onto the track span, then
   for a vertical slider (flag 1) sets the fill's y and height and centres the thumb vertically on
   that edge, and for a horizontal slider sets the fill's width and moves the thumb from the fill's
   x by that edge less half its width. */
void Frontend_UpdateSliderGeometry(Slider *slider) {
    s32 pos;

    if (slider->flags & 1) {
        pos = (slider->bottom - slider->top) * (slider->value - slider->min) / (slider->max - slider->min);
        slider->fill->y = pos;
        slider->fill->height = slider->bottom - pos;
        if (slider->thumb != 0) {
            slider->thumb->y = pos - slider->thumb->height / 2;
        }
    } else {
        pos = (slider->right - slider->left) * (slider->value - slider->min) / (slider->max - slider->min);
        slider->fill->width = pos;
        if (slider->thumb != 0) {
            slider->thumb->x = slider->fill->x - (pos - slider->thumb->width / 2);
        }
    }
}

/* unit KEY.CPP */
/* Returns the index of the first of the seventeen key slots of g_frontendKeyUnlockEntries whose leading word equals the argument, or zero when none does. */
s32 Key_FindKeyIndex(s32 key) {
    s32 index = 0;
    s32 found = 0;
    s32 i;

    for (i = 0; i < 17 && !found; i++) {
        if (g_frontendKeyUnlockEntries[i].key == key) {
            found = 1;
            index = i;
        }
    }
    return index;
}

/* Returns the index of the first of the seventeen key slots of g_frontendKeyEntries whose leading word equals the argument, or zero when none does. */

/* Returns the second word of the first of the seventeen key slots of g_frontendKeyEntries whose leading word equals the argument, or zero when none does. */
s32 Key_FindCharacterPreviewRow(s32 key) {
    s32 index = 0;
    s32 found = 0;
    s32 i;

    for (i = 0; i < 17 && !found; i++) {
        if (g_frontendKeyEntries[i].id == key) {
            found = 1;
            index = i;
        }
    }
    return index;
}

s32 Key_GetCharacterPreviewModel(s32 key) {
    s32 value = 0;
    s32 found = 0;
    s32 i;

    for (i = 0; i < 17 && !found; i++) {
        if (g_frontendKeyEntries[i].id == key) {
            found = 1;
            value = g_frontendKeyEntries[i].value;
        }
    }
    return value;
}

/* unit FRONTEND.CPP */
#if defined(VERSION_US)
#include "Common/resident_event_handler.h"
#include "Common/multiplayeroptions.h"
#include "Frontend/frontend_address_symbols.h"

s32 Frontend_DispatchPakProfileEventUs(ActorDefinitionHeader *actor, s32 event, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    s32 index;
    index = 0;
    if (g_pakProfileHandlerEvents[index].handler != 0) {
        do {
            if (g_pakProfileHandlerEvents[index].event == event) {
                if (g_pakProfileHandlerEvents[index].actorKind == actor->character || g_pakProfileHandlerEvents[index].actorKind == 30000) {
                    return g_pakProfileHandlerEvents[index].handler(actor, event, eventPayload, eventValue, eventExtra);
                }
            }
            index++;
        } while (g_pakProfileHandlerEvents[index].handler != 0);
    }
    return 0;
}
#endif

#if defined(VERSION_US)
/* Stale tag text "gHdrR"; no instruction reads it. */
extern char g_frontendStaleTagText[8];
#endif

/* unit FRONTEND.CPP */
#if defined(VERSION_US)
#include "Common/ccollisionsetup_t.h"
#include "Common/runtime_declarations.h"
#include "Common/effectrender.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Common/legacy_collision_actor.h"
#include "frontend_symbols.h"
#include "Frontend/frontend.h"
/* The collision setup table CCollision_Initialize hands to CCollision_ApplySetupTable (through its KUSEG alias
 * g_collisionSetupTableResource): one row per collision info, ended by an empty row. */
CCollisionSetup_t g_collisionSetupTable[36] = {
    { &g_collisionInfoSlotsB[11].info, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[3].info, 0x3C552B, 5, 2, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[14].info, 0x3C5529, 2, 2, 2, -2100.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[0].info, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[6].info, 0x3C5729, 5, 2, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)(unsigned int)&g_pagerPageCounters[8], 0x3C5D29, 5, 2, 2, -69.119995f, 0.0f, 0.0f, 0.0f, 0.08f },
    { &g_particleCollisionProbeResult[15].info, 0x3C5529, 5, 2, 2, 0.0f, 0.0f, 0.9f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[9].info, 0x2C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[2].info, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[11].info, 0x3C5309, 5, 6, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[5].info, 0x3C5729, 0, 0, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[1].info, 0x3C5308, 5, 3, 2, -2303.9998f, 0.3f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[10].info, 0x3C5308, 5, 3, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[12].info, 0x3C5108, 5, 2, 2, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[4].info, 0x3C5109, 5, 2, 2, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[12].info, 0x3C5309, 5, 6, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[13].info, 0x3C5108, 5, 2, 2, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[15].info, 0x344108, 0, 3, 3, -1235.4816f, 0.5f, 0.25f, 0.0f, 0.25f },
    { &g_particleCollisionProbeResult[6].info, 0x110108, 1, 3, 3, -4941.9263f, 0.7083334f, 0.1f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[10].info, 0x345309, 0, 3, 3, -1535.9999f, 0.6f, 1.0f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[8].info, 0x305109, 0, 3, 3, 0.0f, 0.6f, 1.0f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[16].info, 0x10, 0, 0, 0, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[8].info, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[5].info, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[4].info, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[1].info, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[0].info, 0x1C000, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[9].info, 0x204408, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[3].info, 0x1C000, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[16].info, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[13].info, 0x0, 0, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_particleCollisionProbeResult[7].info, 0x341508, 2, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[7].info, 0x141508, 2, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[14].info, 0x101508, 1, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { &g_collisionInfoSlotsB[2].info, 0x105529, 5, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0 },
};
#endif

/* Retained data for this translation unit. */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const float k_SetupEncodedWords[7] = {
    0.018f, 5.0f, 13.0f, -5.0e+01f, 0.04f, 17.0f,
    -1.0e+01f,
};
#endif
