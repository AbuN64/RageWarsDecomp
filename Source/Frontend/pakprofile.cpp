#include "Common/playerprofiles.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "include_asm.h"
#include "Frontend/pakmenu.h"
#include "Common/shared_gameslot.h"
#include "Common/name.h"
#include "types.h"
#include "Frontend/menuimage.h"
#include "Common/screen.h"
#include "Common/runtime_declarations.h"
#include "Common/math_helpers.h"
#include "Common/selectionscreenstate.h"
#include "Frontend/pakinterface_updateplayerpanelanimations.h"
#include "Render/soundelement_playflatsound.h"
#include "Common/shared_menureply.h"
#include "Common/animation.h"
#include "Frontend/pakinterface_findreadytransferplayer.h"
#include "Pakinterfacescreen/pakinterface_refreshplayerpanel.h"
#include "Common/pak_player_panel.h"
#include "Frontend/frontend_resetlinkedlocalprofile.h"
#include "Ai/playerprofile.h"
#include "Pakinterfacescreen/pakinterface_relabelslotrows.h"
#include "Frontend/frontend_findprofileowner.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend_setplayerprofilelink.h"
#include "Scene/cache_freememory.h"
#include "Common/aiprofile.h"
#include "Frontend/frontend_dispatchpakprofileevent.h"
#include "Tsmos/tsmos_settimerstate.h"

/* unit FRONTEND_CREATEPAKPROFILESCREENDE.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
#define Frontend_CreatePakProfileScreen Frontend_CreatePakProfileScreenEu
#elif defined(VERSION_DE)
#define Frontend_CreatePakProfileScreen Frontend_CreatePakProfileScreenDe
#elif defined(VERSION_EU_X)
#define Frontend_CreatePakProfileScreen Frontend_CreatePakProfileScreenEux
#endif
/* GameSprite ids of the setup screen: the first column is the id in the US rev 1 and EU builds. */
#if defined(VERSION_DE)
#define SPRITE_285 641
#elif defined(VERSION_EU_X)
#define SPRITE_285 650
#else
#define SPRITE_285 645
#endif
#if defined(VERSION_DE)
#define SPRITE_2FB 670
#elif defined(VERSION_EU_X)
#define SPRITE_2FB 768
#else
#define SPRITE_2FB 763
#endif
#if defined(VERSION_DE)
#define SPRITE_2A2 759
#elif defined(VERSION_EU_X)
#define SPRITE_2A2 679
#else
#define SPRITE_2A2 674
#endif
#if defined(VERSION_DE)
#define SPRITE_286 642
#elif defined(VERSION_EU_X)
#define SPRITE_286 651
#else
#define SPRITE_286 646
#endif
#if defined(VERSION_DE)
#define SPRITE_287 643
#elif defined(VERSION_EU_X)
#define SPRITE_287 652
#else
#define SPRITE_287 647
#endif
#if defined(VERSION_DE)
#define SPRITE_2FC 671
#elif defined(VERSION_EU_X)
#define SPRITE_2FC 769
#else
#define SPRITE_2FC 764
#endif
#if defined(VERSION_DE)
#define SPRITE_2A3 760
#elif defined(VERSION_EU_X)
#define SPRITE_2A3 680
#else
#define SPRITE_2A3 675
#endif
#if defined(VERSION_DE)
#define SPRITE_2FD 758
#elif defined(VERSION_EU_X)
#define SPRITE_2FD 770
#else
#define SPRITE_2FD 765
#endif
#if defined(VERSION_DE)
#define SPRITE_2FA 761
#elif defined(VERSION_EU_X)
#define SPRITE_2FA 767
#else
#define SPRITE_2FA 762
#endif
#if defined(VERSION_DE)
#define SPRITE_293 649
#elif defined(VERSION_EU_X)
#define SPRITE_293 653
#else
#define SPRITE_293 659
#endif
#if defined(VERSION_DE)
#define SPRITE_296 647
#elif defined(VERSION_EU_X)
#define SPRITE_296 656
#else
#define SPRITE_296 662
#endif
#if defined(VERSION_DE)
#define SPRITE_288 644
#elif defined(VERSION_EU_X)
#define SPRITE_288 654
#else
#define SPRITE_288 648
#endif
#if defined(VERSION_DE)
#define SPRITE_2A1 648
#elif defined(VERSION_EU_X)
#define SPRITE_2A1 655
#else
#define SPRITE_2A1 673
#endif
#if defined(VERSION_DE)
#define SPRITE_295 645
#elif defined(VERSION_EU_X)
#define SPRITE_295 657
#else
#define SPRITE_295 661
#endif
#if defined(VERSION_DE)
#define SPRITE_289 650
#elif defined(VERSION_EU_X)
#define SPRITE_289 658
#else
#define SPRITE_289 649
#endif
#if defined(VERSION_DE)
#define SPRITE_297 660
#elif defined(VERSION_EU_X)
#define SPRITE_297 669
#else
#define SPRITE_297 663
#endif
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Frontend/menu_image.h"
#include "Frontend/smp_overlay.h"
#include "Tsmos/tsmos_activatecontrollerstate.h"
#include "Note/pak_probestatus.h"
#include "Pakinterfacescreen/pakinterface_resolveplayerpakstate.h"
#include "Menuimage/menuimage.h"
#include "Menu/menu.h"
#include "Match_reason/match_reason.h"
#include "Results/achieve_selectpostresultscreen.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Pakinterfacescreen/pakinterface_relabelslotrows.h"
#include "Pakinterfacescreen/pakinterface_refreshplayerpanel.h"
#include "Control/control.h"
#include "Ai/playerprofile.h"
#include "Frontend/screen.h"
#include "Tsmos/tsmos_settimerstate.h"
#include "Cache/cache_allocatememory.h"
#include "Smp/smp_flicker.h"
#include "Frontend/frontend_address_symbols.h"

/* Creates the match setup block g_pakProfileScreenState for screen screen: allocates and clears it, loads its sprites and centres the two banner rows, links every player slot, shows the header for the game mode, resets each player's menu state, records and name entries, then starts each player in the state the mode needs (team handoff for mode 5, memory-card check for mode 6, the host for mode 7) and starts the menu music. Returns zero. */
s32 Frontend_CreatePakProfileScreen(void *screen) {
    PakMenuController *block;
    Shared_Game *globals;
    MenuWidget *GameSprite;
    MenuWidget *row;
    s32 rest;
    s32 i;
    s32 j;

    block = Cache_AllocateMemory(sizeof(PakMenuController));
    g_pakProfileScreenState = block;
    block->window = screen;
    Frontend_InitMenuImage(block->menu, 103, 0, 0, 0);
    g_pakProfileScreenState->list = SmpOverlay_CreateOverlayNode(screen, 4);
    SmpOverlay_ShowSlotById(screen, 0, SPRITE_285);
    SmpOverlay_ShowSlotById(screen, 1, SPRITE_285);
    SmpOverlay_ShowSlotById(screen, 2, SPRITE_285);
    SmpOverlay_ShowSlotById(screen, 3, SPRITE_285);
    for (i = 0; i < 4; i++) {
        g_pakProfileScreenState->selected[i] = 0;
    }
    g_pakProfileScreenState->ready = 1;
    g_pakProfileScreenState->timer = 4;
    g_pakProfileScreenState->top = Node_FindWidgetByResourceId(screen, SPRITE_2FB);
    g_pakProfileScreenState->top->x -= g_pakProfileScreenState->top->w;
    g_pakProfileScreenState->topStep = g_pakProfileScreenState->top->w / 4;
    rest = g_pakProfileScreenState->top->w - g_pakProfileScreenState->topStep * 4;
    g_pakProfileScreenState->top->x += rest;
    g_pakProfileScreenState->bottom = Node_FindWidgetByResourceId(screen, SPRITE_2A2);
    g_pakProfileScreenState->bottom->x += g_pakProfileScreenState->bottom->w;
    g_pakProfileScreenState->bottomStep = g_pakProfileScreenState->bottom->w / 4;
    rest = g_pakProfileScreenState->bottom->w - g_pakProfileScreenState->bottomStep * 4;
    g_pakProfileScreenState->bottom->x -= rest;
    Node_FindWidgetByResourceId(screen, SPRITE_286)->alpha = 110;
    g_pakProfileScreenState->music = SmpFlicker_CreateFlickerWidget(SPRITE_287, 0xFF);
    g_pakProfileScreenState->title = Node_FindWidgetByResourceId(screen, SPRITE_287);
    Widget_SetWidgetFlag08(g_pakProfileScreenState->title, 0);
    g_pakProfileScreenState->players[0].sprite = Node_FindWidgetByResourceId(screen, SPRITE_2FC);
    g_pakProfileScreenState->players[1].sprite = Node_FindWidgetByResourceId(screen, SPRITE_2A3);
    g_pakProfileScreenState->players[2].sprite = Node_FindWidgetByResourceId(screen, SPRITE_2FD);
    g_pakProfileScreenState->players[3].sprite = Node_FindWidgetByResourceId(screen, SPRITE_2FA);
    g_pakProfileScreenState->phase = g_pakProfileRequestedPhase;
    for (i = 0; i < 4; i++) {
        g_pakProfileScreenState->links[i].player = -1;
        g_pakProfileScreenState->links[i].entry = 0;
        g_pakProfileScreenState->links[i].state = 2;
    }
    switch (g_pakProfileScreenState->phase) {
    case 5:
        GameSprite = Node_FindWidgetByResourceId(screen, SPRITE_293);
        Widget_SetWidgetFlag08(GameSprite, 1);
        GameSprite->alpha = 0xFF;
        break;
    case 6:
        GameSprite = Node_FindWidgetByResourceId(screen, SPRITE_296);
        Widget_SetWidgetFlag08(GameSprite, 1);
        GameSprite->alpha = 0xFF;
        break;
    case 4:
        GameSprite = Node_FindWidgetByResourceId(screen, SPRITE_288);
        Widget_SetWidgetFlag08(GameSprite, 1);
        GameSprite->alpha = 0xFF;
        break;
    case 0:
        GameSprite = Node_FindWidgetByResourceId(screen, SPRITE_2A1);
        Widget_SetWidgetFlag08(GameSprite, 1);
        GameSprite->alpha = 0xFF;
        break;
    case 3:
        GameSprite = Node_FindWidgetByResourceId(screen, SPRITE_295);
        Widget_SetWidgetFlag08(GameSprite, 1);
        GameSprite->alpha = 0xFF;
        break;
    case 1:
        GameSprite = Node_FindWidgetByResourceId(screen, SPRITE_289);
        Widget_SetWidgetFlag08(GameSprite, 1);
        GameSprite->alpha = 0xFF;
        for (i = 0; i < 4; i++) {
            if (g_localPlayerProfiles[i].player >= 0) {
                if (g_localPlayerProfiles[i].fresh == 1) {
                    g_localPlayerProfiles[i].player = -1;
                    g_localPlayerProfiles[i].fresh = 0;
                }
                if (g_localPlayerProfiles[i].player >= 0) {
                    g_pakProfileScreenState->links[i].player = 0;
                    g_pakProfileScreenState->links[i].entry = i;
                    g_pakProfileScreenState->links[i].state = 1;
                }
            }
        }
        PAKInterface_RelabelSlotRows(-1);
        break;
    case 7:
        break;
    case 2:
        GameSprite = Node_FindWidgetByResourceId(screen, SPRITE_297);
        Widget_SetWidgetFlag08(GameSprite, 1);
        GameSprite->alpha = 0xFF;
        break;
    }
    for (i = 0; i < 4; i++) {
        g_pakProfileScreenState->players[i].state = 0;
        g_pakProfileScreenState->players[i].menu = 0;
        g_pakProfileScreenState->players[i].back = -1;
        PAKInterface_RefreshPlayerPanel(i);
        Control_EnableControllerPak(i);
        for (j = 0; j < 4; j++) {
            Player_InitializeProfile(&g_pakProfileScreenState->players[i].records[j]);
        }
        for (j = 0; j < 16; j++) {
            XPlus_FillMemory(g_pakProfileScreenState->players[i].noteTexts[j].name, 0, 20);
            XPlus_FillMemory(g_pakProfileScreenState->players[i].noteTexts[j].size, 0, 10);
        }
        XPlus_FillMemory(g_pakProfileScreenState->players[i].codes[2], 0, 10);
        XPlus_FillMemory(g_pakProfileScreenState->players[i].codes[1], 0, 10);
        XPlus_FillMemory(g_pakProfileScreenState->players[i].codes[0], 0, 10);
        g_pakProfileScreenState->players[i].slot = 0;
        g_pakProfileScreenState->players[i].choice = 0;
        for (j = 0; j < 4; j++) {
            g_pakProfileScreenState->players[i].used[j] = 2;
            g_pakProfileScreenState->players[i].notes[j] = 0;
        }
        g_pakProfileScreenState->players[i].record = 0;
        g_pakProfileScreenState->players[i].host = 0;
        g_pakProfileScreenState->players[i].profile = 0;
        g_pakProfileScreenState->players[i].sub = 0;
        g_pakProfileScreenState->players[i].next = -1;
        g_pakProfileScreenState->players[i].port = -1;
    }
    g_pakProfileScreenState->focus = -1;
    switch (g_pakProfileScreenState->phase) {
    case 5:
        for (i = 0; i < 4; i++) {
            g_pakProfileScreenState->players[i].state = 14;
        }
        for (i = 0; i < 4; i++) {
            globals = &g_gameSettings;
            if (g_localPlayerProfiles[i].fresh == 0 && g_localPlayerProfiles[i].player >= 0 && globals->playerSettings[i].enabled == 1 &&
                globals->playerSettings[i].locked == 0) {
                g_pakProfileScreenState->players[g_localPlayerProfiles[i].player].back = 2;
                g_pakProfileScreenState->players[g_localPlayerProfiles[i].player].state = 2;
                g_pakProfileScreenState->players[g_localPlayerProfiles[i].player].next = 6;
            }
        }
        for (i = 0; i < 4; i++) {
            PAKInterface_RefreshPlayerPanel(i);
        }
        break;
    case 6:
        if (g_pakProfileOperationPhase == 0) {
            for (i = 0; i < 4; i++) {
                Note_ProbeStatus(i);
                switch (Note_GetStatus(i)) {
                case -4:
                case -3:
                case -1:
                case 0:
                    g_pakProfileScreenState->players[i].back = 2;
                    g_pakProfileScreenState->players[i].state = 2;
                    g_pakProfileScreenState->players[i].next = 4;
                    PAKInterface_RefreshPlayerPanel(i);
                    break;
                }
            }
        } else {
            Note_ProbeStatus(g_pakProfileControllerPort);
            switch (Note_GetStatus(g_pakProfileControllerPort)) {
            case -4:
            case -3:
            case -1:
            case 0:
                g_pakProfileScreenState->players[g_pakProfileControllerPort].back = 2;
                g_pakProfileScreenState->players[g_pakProfileControllerPort].state = 2;
                g_pakProfileScreenState->players[g_pakProfileControllerPort].next = 4;
                PAKInterface_RefreshPlayerPanel(g_pakProfileControllerPort);
                break;
            }
        }
        break;
    case 7:
        g_pakProfileScreenState->players[0].back = 2;
        g_pakProfileScreenState->players[0].state = 2;
        g_pakProfileScreenState->players[0].next = 13;
        g_pakProfileScreenState->players[0].sub = 6;
        PAKInterface_RefreshPlayerPanel(0);
        break;
    }
    Frontend_RequestScreenMode(0);
    Tsmos_DeactivateControllerState();
    Tsmos_SetTimerState(0);
    SoundElement_PlayFlatSound(3704);
    return 0;
}
#endif

/* Runs the block g_pakProfileScreenState points to on event 1: in phase 3 at 0x4C it counts each player's timer
   at 0x14 of its 2920-byte record at 0x58 down and, when one expires, marks it -1 and resets that
   player through Note_ProbeStatus and PAKInterface_ResolvePlayerPakState between Tsmos_DeactivateControllerState and Tsmos_ActivateControllerState; then it
   advances the menu at 0x8 with Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition while Frontend_GetMenuImageState reports 1, and
   once it reports 2 in phase 5 at 0x54 calls MarkMenuEventHandled and moves on through Frontend_ContinueCupOrOpenResults,
   Frontend_OpenControllerModeResults or Achieve_SelectPostResultScreen as the cartridge's jump table k_pakProfileScreenExitJumpTable chooses for option
   byte g_gameControllerMode up to 4. Returns zero. */
s32 Frontend_UpdatePakScreenExit(void *element, void *eventId, s32 event) {
    s32 i;
    u32 option;

    if (event != 1) {
        return 0;
    }
    if (g_pakProfileScreenState->ready == 3) {
        for (i = 0; i < 4; i++) {
            if (g_pakProfileScreenState->players[i].back > 0 && --g_pakProfileScreenState->players[i].back == 0) {
                g_pakProfileScreenState->players[i].back = -1;
                Tsmos_DeactivateControllerState();
                Note_ProbeStatus(i);
                PAKInterface_ResolvePlayerPakState(i);
                Tsmos_ActivateControllerState();
            }
        }
    }
    if (Frontend_GetMenuImageState(g_pakProfileScreenState->menu) != 1) {
        return 0;
    }
    Frontend_DrawMenuImage(g_pakProfileScreenState->menu);
    Frontend_AdvanceMenuImageTransition(g_pakProfileScreenState->menu);
    if (Frontend_GetMenuImageState(g_pakProfileScreenState->menu) != 2) {
        return 0;
    }
    if (g_pakProfileScreenState->phase != 5) {
        return 0;
    }
    MarkMenuEventHandled();
    option = g_gameSettings.controllerMode;
    switch (option) {
        case 0:
            Frontend_ContinueCupOrOpenResults();
            break;
        case 2:
            Frontend_OpenControllerModeResults();
            break;
        case 1:
        case 3:
        case 4:
            Achieve_SelectPostResultScreen();
            break;
        default:
            break;
    }
    return 0;
}

/* unit FRONTEND_UPDATEPAKSCREENPANELS.CPP */
/* Animates the two menu panels through open, close and countdown states and updates the active team menu. */
s32 Frontend_UpdatePakScreenPanels(s32 element, s32 eventId, s32 event) {
    s32 readyState;
    s32 openFramesLeft;
    s32 closeFramesLeft;
    s32 unusedPanelState;
    s32 unusedPanelTimer;
    s32 unusedPanelResult;
    MenuWidget *closeTop;
    MenuWidget *closeBottom;
    MenuWidget *openTop;
    MenuWidget *openBottom;

    if (g_selectionMessageStage < 2) {
        readyState = g_pakProfileScreenState->ready;
        switch (readyState) {
        case 1:
            openTop = g_pakProfileScreenState->top;
            openTop->x = (u16) (openTop->x + (u16) g_pakProfileScreenState->topStep);
            openBottom = g_pakProfileScreenState->bottom;
            openBottom->x = (u16) (openBottom->x - (u16) g_pakProfileScreenState->bottomStep);
            openFramesLeft = g_pakProfileScreenState->timer - 1;
            g_pakProfileScreenState->timer = openFramesLeft;
            if (openFramesLeft <= 0) {
                SoundElement_PlayFlatSound(3705);
                /* title is the panel's item handle, kept untyped in the animation state */
                Widget_SetWidgetFlag08((SlotSelectionWidget *) g_pakProfileScreenState->title, 1);
                SmpFlicker_StartFlicker(g_pakProfileScreenState->music, 4);
                g_pakProfileScreenState->ready = 4;
                g_pakProfileScreenState->timer = 4;
            }
            break;
        case 2:
            closeTop = g_pakProfileScreenState->top;
            closeTop->x = (u16) (closeTop->x - (u16) g_pakProfileScreenState->topStep);
            closeBottom = g_pakProfileScreenState->bottom;
            closeBottom->x = (u16) (closeBottom->x + (u16) g_pakProfileScreenState->bottomStep);
            closeFramesLeft = g_pakProfileScreenState->timer - 1;
            g_pakProfileScreenState->timer = closeFramesLeft;
            if (closeFramesLeft <= 0) {
                g_pakProfileScreenState->ready = 3;
                MarkMenuEventHandled();
                SmXlate_SwitchScreen(g_pakProfileScreenState->focus);
                return 0;
            }
            break;
        case 3:
            Tsmos_ActivateControllerState();
            break;
        case 4:
            g_pakProfileScreenState->timer = RW_CLAMP(g_pakProfileScreenState->timer - 1, 0, g_pakProfileScreenState->timer);
            if ((g_pakProfileScreenState->timer <= 0) && (SmpFlicker_IsFlickerIdle(g_pakProfileScreenState->music) != 0)) {
                SmpFlicker_RestoreFlickerValue(g_pakProfileScreenState->music);
                g_pakProfileScreenState->ready = 3;
            }
            break;
        case 5:
            SoundElement_PlayFlatSound(3704);
            g_pakProfileScreenState->ready = 2;
            g_pakProfileScreenState->timer = 4;
            Widget_SetWidgetFlag08((SlotSelectionWidget *) g_pakProfileScreenState->title, 0);
            break;
        }
        if (g_pakProfileScreenState->ready == 3) PAKInterface_UpdatePlayerPanelAnimations(event);
    }
    return 0;
}

/* unit FRONTEND_HANDLEPAKPROFILEINPUT.CPP */
/* Dispatch player-slot events using the current shared menu controller and
 * its measured 0xB68-byte player records. */
s32 Frontend_HandlePakProfileInput(s32 a,s32 b,u32 event,s32 key){
    s32 index=event&65535;
    if((event>>16)==3){
        switch(g_pakProfileScreenState->phase){
            case 6:
            if(key==10){
                s32 state;
                state=g_pakProfileScreenState->players[index].state;
                if(state==4){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].back=2;
                    g_pakProfileScreenState->players[index].state=2;
                    g_pakProfileScreenState->players[index].next=state;
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 4:
            switch(key){
                case 11:
                case 13:
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].back=2;
                    g_pakProfileScreenState->players[index].state=2;
                    g_pakProfileScreenState->players[index].next=4;
                    PAKInterface_RefreshPlayerPanel(index);
                }
                break;
                case 10:
                {
                    s32 state;
                    state=g_pakProfileScreenState->players[index].state;
                    if(state==4){
                        MarkMenuEventHandled();
                        g_pakProfileScreenState->players[index].back=2;
                        g_pakProfileScreenState->players[index].state=2;
                        g_pakProfileScreenState->players[index].next=state;
                        PAKInterface_RefreshPlayerPanel(index);
                    }
                    break;
                }
            }
            break;
            case 0:
            if(key==11||key==13){
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].back=2;
                    g_pakProfileScreenState->players[index].state=2;
                    g_pakProfileScreenState->players[index].next=12;
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 3:
            if(key==11||key==13){
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].back=2;
                    g_pakProfileScreenState->players[index].state=2;
                    g_pakProfileScreenState->players[index].next=13;
                    g_pakProfileScreenState->players[index].sub=5;
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 1:
            if(key==11||key==13){
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].state=14;
                    if(PAKInterface_FindReadyTransferPlayer()>=0){
                        g_pakProfileScreenState->players[index].back=2;
                        g_pakProfileScreenState->players[index].state=2;
                        g_pakProfileScreenState->players[index].next=13;
                        g_pakProfileScreenState->players[index].sub=6;
                    }
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 2:
            if(key==11||key==13){
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].state=14;
                    if(PAKInterface_FindReadyTransferPlayer()>=0){
                        g_pakProfileScreenState->players[index].back=2;
                        g_pakProfileScreenState->players[index].state=2;
                        g_pakProfileScreenState->players[index].next=13;
                        g_pakProfileScreenState->players[index].sub=3;
                    }
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 5:
            case 7:
            break;
        }
    }
    return 0;
}

/* unit FRONTEND_RESETLINKEDLOCALPROFILE.CPP */
/* When link slot i of the screen g_pakProfileScreenState points to is set,
   passes the 400-byte record i of g_localPlayerProfiles to Player_InitializeProfile, marks the slot done with 2 and calls
   PAKInterface_RelabelSlotRows_FrontendResetlinkedlocalprofile with -1. */


void Frontend_ResetLinkedLocalProfile(s32 index) {
    if (g_pakProfileScreenState->links[index].state == 1) {
        Player_InitializeProfile(&g_localPlayerProfiles[index]);
        g_pakProfileScreenState->links[index].state = 2;
        PAKInterface_RelabelSlotRows(-1);
    }
}

/* unit FRONTEND_FINDPROFILEOWNER.CPP */
/* Returns the index of the first of four 400-byte records in g_profileSlotResetWord whose byte at offset 4
   equals the second argument and whose first word equals the first, or -1 when none does. */
s32 Frontend_FindProfileOwner(s32 id, s32 kind) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_profileSlotResetWord[i].kind == kind && g_profileSlotResetWord[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* unit FRONTEND_CHECKOWNEDPROFILEIDS.CPP */
#include <platform_sdk.h>
#include "Frontend/frontend_checkownedprofileids.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"
#include "Ui/X_files/x_plus.h"

/* Checks that every active player on the selected team has the configured value. */
s32 Frontend_CheckOwnedProfileIds(s32 player) {
    s32 profileOffset;
    s32 profileIndex;
    s32 allMatch;
    allMatch = 1;
    profileIndex = 0;
    profileOffset = 0;
    do {
        if ((*(g_profileSlotEnabledFlags + profileOffset) == 0) && (*(*g_profileSlotIndices + profileOffset) == player) && (((struct LinkedProfileOwnerRecord *)((char *)g_profileSlotResetWord + profileOffset))->id != g_pakProfileScreenState->players[player].profile)) {
            allMatch = 0;
        }
        profileIndex += 1;
        profileOffset += 400;
    } while (profileIndex < 4);
    return allMatch;
}

/* unit FRONTEND_DISPATCHPAKPROFILEEVENT.CPP */
/* Fills link entry i of the screen g_pakProfileScreenState points to with
   two values and marks it set. */
void Frontend_SetPlayerProfileLink(s32 first, s32 second, s32 index) {
    g_pakProfileScreenState->links[index].player = first;
    g_pakProfileScreenState->links[index].entry = second;
    g_pakProfileScreenState->links[index].state = 1;
}

/* Event handler placeholder: ignores the event and returns zero. */
s32 Frontend_ReturnProfileEventZero(void) {
    return 0;
}

/* Releases the object g_pakProfileScreenState holds through Cache_FreeMemory, clears g_pakProfileScreenState, calls
   Tsmos_ActivateControllerState and Tsmos_SetTimerState with 1, and returns zero. */
s32 Frontend_DestroyPakProfileScreen(void) {
    Cache_FreeMemory(g_pakProfileScreenState);
    g_pakProfileScreenState = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetTimerState(1);
    return 0;
}

/* Handles a packed message for a player in g_pakProfileScreenState: when the player (low half) is in state 12, the
   message type (high half) is 3 and the argument is 4 or 5, moves the player to phase 2 with a zero
   timer; always returns 0. */
int Frontend_ResetNameRepeatOnEvent(int element, int eventId, unsigned int message, int arg) {
    PakNameRepeatView *p = (PakNameRepeatView *)((char *)g_pakProfileScreenState + (message & 0xFFFF) * sizeof(PakProfilePanelState));

    if (p->state == 12 && (message >> 16) == 3 && arg < 6 && arg >= 4) {
        p->timer = 0;
        p->phase = 2;
    }
    return 0;
}

#if !(defined(VERSION_US))
/* Calls the handler registered for event (tables g_pakProfileHandlerEvents, g_pakProfileHandlerKinds, g_pakProfileHandlers). A row matches when its event equals event and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */


s32 Frontend_DispatchPakProfileEvent(void *eventTarget, s32 event, s32 eventValue, s32 eventData, s32 eventContext) {
    PakProfileEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    struct MenuWidget *actor;

    if (g_pakProfileHandlers != 0) {
        wildcard = 30000;
        entry = &g_pakProfileHandlers;
        index = 0;
        do {
            if (g_pakProfileHandlerEvents[index].value == event) {
                actor = eventTarget;
                actor_kind = actor->resource;
                table_kind = g_pakProfileHandlerKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, event, eventValue, eventData, eventContext);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
#endif
