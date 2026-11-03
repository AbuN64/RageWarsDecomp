#include "COMMON/PLAYERPROFILES.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "include_asm.h"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "FRONTEND/MENUIMAGE.H"

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
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHARED_GAMESLOT.H"

/* Creates the match setup block g_pakProfileScreenState for screen screen: allocates and clears it, loads its sprites and centres the two banner rows, links every player slot, shows the header for the game mode, resets each player's menu state, records and name entries, then starts each player in the state the mode needs (team handoff for mode 5, memory-card check for mode 6, the host for mode 7) and starts the menu music. Returns zero. */





extern s32 g_pakProfileControllerPort;
extern s32 g_pakProfileOperationPhase;

extern struct Record *Cache_AllocateMemory(s32 size);
extern void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth);
extern void *SmpOverlay_CreateOverlayNode(void *, s32);
extern void SmpOverlay_ShowSlotById(void *, s32, s32);
extern void Widget_SetWidgetFlag08(void *object, int enabled);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern void PAKInterface_RelabelSlotRows(s32);
extern void PAKInterface_RefreshPlayerPanel(s32);
extern void Control_EnableControllerPak(s32);
extern void Player_InitializeProfile(void *profileStorage);
extern void Note_ProbeStatus(s32);
extern s32 Note_GetStatus(s32);
extern void Frontend_RequestScreenMode(s32);
extern void Tsmos_DeactivateControllerState(void);
extern void Tsmos_SetTimerState(s32);

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





extern void Tsmos_DeactivateControllerState(void);
extern void Tsmos_ActivateControllerState(void);
extern void Note_ProbeStatus(s32);
extern void PAKInterface_ResolvePlayerPakState(s32);
extern s32 Frontend_GetMenuImageState(s32 *record);
extern void Frontend_DrawMenuImage(struct MenuImage *menu);
extern void MarkMenuEventHandled();
extern void Frontend_ContinueCupOrOpenResults(void);
extern void Frontend_OpenControllerModeResults(void);
extern void Achieve_SelectPostResultScreen(void);

s32 Frontend_UpdatePakScreenExit(void *unused0, void *unused1, s32 event) {
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
    if (option >= 5) {
        goto done;
    }
    switch (option) {
        case 0: goto option_a;
        case 1: goto option_c;
        case 2: goto option_b;
        case 3: goto option_c;
        case 4: goto option_c;
        }
option_a:
    Frontend_ContinueCupOrOpenResults();
    return 0;
option_b:
    Frontend_OpenControllerModeResults();
    return 0;
option_c:
    Achieve_SelectPostResultScreen();
done:
    return 0;
}
