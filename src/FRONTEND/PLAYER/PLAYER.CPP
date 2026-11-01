#include "include_asm.h"
#include "COMMON/SCREEN.H"
#include "COMMON/VIDEO_DIMENSIONS.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "FRONTEND/WIDGET_FINDWIDGETATPOINT.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "TYPES.H"
#include "FRONTEND/ENTRYRECAT4D4.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"
#include "FRONTEND/MENU_IMAGE.H"
#include "FRONTEND/EQUIP_ACTIVATEEQUIPMENTPANEL.H"
#include "FRONTEND/PLAYER.H"
#include <PR/gbi.h>

/* 800E1FC0.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_PlayerWords2_Player.c */
const float g_PlayerWords2[1] = {
    1.0f,
};
#endif

/* 800E1FC4.CPP */
const float g_PlayerWords1[7] = {
    0.0035f, 5.0f, -1.0e+02f, 28.0f, 12.0f, -3.0f,
    -18.0f,
};

/* 8043A0B0_6.CPP */

/* Player_CreateFourPlayerResults_Player.CPP */
extern struct FourPlayerResultsScreen *g_equipmentAndResultsScreen;
extern Shared_PlayerSettingsRecord g_playerSettings[];
extern struct PlayerSettingsOptionRow g_characterPortraitRecords[];
extern struct StateFlags g_equipmentPanelWidgetIds[][19];
extern f32 g_fourPlayerBadgeScale;
extern struct Record *Cache_AllocateMemory(s32 size);
extern void *SmpOverlay_CreateOverlayNode(void *, s32);
extern void SmpOverlay_ShowSlotById(void *, s32, s32);
extern MenuWidget *Node_FindWidgetByResourceId(void *, s32);
extern void Widget_SetWidgetFlag08(void *object, int enabled);
extern s32 Key_FindKeyIndex(s32);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern void Tsmos_DeactivateControllerState(void);
extern struct StateFlags g_equipmentPrimaryWidgetIds[][19];
extern s32 SmpFlicker_IsFlickerIdle(struct FlickerActivityView *object);
extern void SmpFlicker_RestoreFlickerValue(struct FlickerRestoreView *source);
extern void SmpFlicker_StartFlicker(struct FlickerStartView *object, s32 count);
extern void SmXlate_SwitchScreen(s32);
extern void Tsmos_ActivateControllerState(void);

/* Construct the four-player results/loadout menu and animate its panels into view. */
s32 Player_CreateFourPlayerResults(void *window) {
#if defined(VERSION_DE)
    enum { slotResource = 198, leftResource = 204, rightResource = 244,
           titleResource = 201, messageResource = 199 };
#elif defined(VERSION_EU_X)
    enum { slotResource = 204, leftResource = 210, rightResource = 250,
           titleResource = 207, messageResource = 205 };
#else
    enum { slotResource = 200, leftResource = 206, rightResource = 246,
           titleResource = 203, messageResource = 201 };
#endif
    s32 player;
    s32 delta;
    struct FourPlayerResultsScreen *screen;
    MenuWidget *widget;
    MenuWidget *bar;
    s32 row;
    CVector3 scale;
    Shared_PlayerSettingsRecord *config;

    g_equipmentAndResultsScreen = Cache_AllocateMemory(sizeof(struct FourPlayerResultsScreen));
    g_equipmentAndResultsScreen->window = window;
    g_equipmentAndResultsScreen->menu = SmpOverlay_CreateOverlayNode(window, 4);
    SmpOverlay_ShowSlotById(window, 0, slotResource);
    SmpOverlay_ShowSlotById(window, 1, slotResource);
    SmpOverlay_ShowSlotById(window, 2, slotResource);
    SmpOverlay_ShowSlotById(window, 3, slotResource);
    scale.x = g_fourPlayerBadgeScale;
    scale.y = g_fourPlayerBadgeScale;
    scale.z = g_fourPlayerBadgeScale;
    for (player = 0; player < 4; player++) {
        Shared_PlayerSettingsRecord *config;
        g_equipmentAndResultsScreen->panels[player].state = 0;
        g_equipmentAndResultsScreen->panels[player].selection = 5;
        bar = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentPanelWidgetIds[player][1].value);
        g_equipmentAndResultsScreen->panels[player].item = bar;
        bar->alpha = 100;
        Widget_SetWidgetFlag08(bar, 0);
        widget = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentPanelWidgetIds[player][0].value);
        widget->alpha = 110;
        config = &g_playerSettings[player];
        if (config->enabled == 1) {
            row = Key_FindKeyIndex(config->character);
            scale.x = g_characterPortraitRecords[row].scale[player];
            scale.y = g_characterPortraitRecords[row].scale[player];
            scale.z = g_characterPortraitRecords[row].scale[player];
            Preview_InitModelPreview(&g_equipmentAndResultsScreen->panels[player], 9, config->character + 911, 75, 24000, scale, g_characterPortraitRecords[row].position[player], g_characterPortraitRecords[row].distance[player], g_characterPortraitRecords[row].light[player]);
        }
    }
    g_equipmentAndResultsScreen->state = 1;
    g_equipmentAndResultsScreen->timer = 4;
    g_equipmentAndResultsScreen->leftArrow = Node_FindWidgetByResourceId(window, leftResource);
    g_equipmentAndResultsScreen->leftArrow->x = (u16)g_equipmentAndResultsScreen->leftArrow->x - (u16)g_equipmentAndResultsScreen->leftArrow->width;
    g_equipmentAndResultsScreen->leftStep = g_equipmentAndResultsScreen->leftArrow->width / 4;
    delta = g_equipmentAndResultsScreen->leftArrow->width - g_equipmentAndResultsScreen->leftStep * 4;
    g_equipmentAndResultsScreen->leftArrow->x = (u16)g_equipmentAndResultsScreen->leftArrow->x + delta;
    g_equipmentAndResultsScreen->rightArrow = Node_FindWidgetByResourceId(window, rightResource);
    g_equipmentAndResultsScreen->rightArrow->x = (u16)g_equipmentAndResultsScreen->rightArrow->x + (u16)g_equipmentAndResultsScreen->rightArrow->width;
    g_equipmentAndResultsScreen->rightStep = g_equipmentAndResultsScreen->rightArrow->width / 4;
    delta = g_equipmentAndResultsScreen->rightArrow->width - g_equipmentAndResultsScreen->rightStep * 4;
    g_equipmentAndResultsScreen->rightArrow->x = (u16)g_equipmentAndResultsScreen->rightArrow->x - delta;
    Node_FindWidgetByResourceId(window, titleResource)->alpha = 110;
    g_equipmentAndResultsScreen->resource = SmpFlicker_CreateFlickerWidget(messageResource, 0xFF);
    widget = Node_FindWidgetByResourceId(window, messageResource);
    g_equipmentAndResultsScreen->message = widget;
    Widget_SetWidgetFlag08(widget, 0);
    screen = g_equipmentAndResultsScreen;
    for (player = 0; player < 4; player++) {
        config = &g_playerSettings[player];
        if (config->enabled == 1) {
            switch (config->character) {
            case 14:
            case 17:
            case 18:
                screen->panels[player].mode = 0;
                break;
            default:
                screen->panels[player].mode = 2;
                break;
            }
        }
    }
    Frontend_ResetEquipmentFromCharacter();
    for (player = 0; player < 4; player++) {
        config = &g_playerSettings[player];
        if (config->enabled == 1) {
            Equip_ActivateEquipmentPanel(player);
        }
    }
    g_equipmentAndResultsScreen->next = -1;
    Tsmos_DeactivateControllerState();
    return 0;
}

extern s32 Frontend_InitModelPreviewTransform(void *, s32, CVector3, CVector3);
extern void Frontend_SetPreviewRotation(void *, CVector3);
extern void Frontend_SetPreviewRotationSpeed(void *, CVector3);
#if defined(VERSION_EU)
/* eu keeps these two floats elsewhere: g_matchResult5027TextEu/g_matchResult5011TextEu name its string tables */
#define g_matchResult5027TextEu g_fourPlayerBadgeScaleEu
#define g_matchResult5011TextEu g_fourPlayerBadgeSecondYEu
#endif
extern f32 g_matchResult5027TextEu;
extern f32 g_fourPlayerBadgeAngularVelocity;
extern f32 g_matchResult5011TextEu;
extern f32 g_fourPlayerBadgeUpperY;
extern f32 g_fourPlayerBadgeLowerY;
/* Initialize four rotating result badges and reveal enabled player cards. */
s32 Player_StartFourPlayerResults(void) {
    CVector3 scale;
    CVector3 position;
    CVector3 rotation;
    CVector3 angularVelocity;
    struct FourPlayerResultsScreen *screen;
    MenuWidget *widget;
    s32 i;
    s32 baseAngle;
    s32 badgeOffset;
    Shared_PlayerSettingsRecord *config;
    Tsmos_SetModeOneFlag(1);
    i = 0;
    badgeOffset = ((char *)&((struct FourPlayerResultsScreen *)0)->badges - (char *)0);
    scale.x = g_matchResult5027TextEu;
    scale.y = g_matchResult5027TextEu;
    scale.z = g_matchResult5027TextEu;
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;
    angularVelocity.x = 0;
    angularVelocity.z = 0;
    position.x = 0;
    position.y = 0;
    angularVelocity.y = g_fourPlayerBadgeAngularVelocity;
    position.z = g_fourPlayerBadgeDepth;
    baseAngle = i;
    for (; i < 4; i++) {
        switch (i) {
        case 0:
            position.y = g_fourPlayerBadgeBaseY;
            break;
        case 1:
            position.y = g_matchResult5011TextEu;
            break;
        case 2:
            position.y = g_fourPlayerBadgeUpperY;
            break;
        case 3:
            position.y = g_fourPlayerBadgeLowerY;
            break;
        }
        rotation.y = (f32)(baseAngle + Graphu64_NextRandom() % 10);
        baseAngle += 45;
        Frontend_InitModelPreviewTransform((u8 *)g_equipmentAndResultsScreen + badgeOffset, 0, scale, position);
        Frontend_SetPreviewRotation((u8 *)g_equipmentAndResultsScreen + badgeOffset, rotation);
        Frontend_SetPreviewRotationSpeed((u8 *)g_equipmentAndResultsScreen + badgeOffset, angularVelocity);
        badgeOffset += sizeof(g_equipmentAndResultsScreen->badges[0]);
    }
    for (i = 0; i < 4; i++) {
        config = &g_playerSettings[i];
        if (config->enabled == 1) {
            widget = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_fourPlayerResultsWidgetIds[i * 38]);
            Widget_SetWidgetFlag40(widget, 0);
            widget->alpha = 35;
            screen = g_equipmentAndResultsScreen;
            switch (screen->panels[i].mode) {
            case 0:
                Frontend_SelectEquipmentColumn(i, screen->panels[i].selection = 5);
                break;
            case 1:
                screen->panels[i].selection = 0;
                Frontend_SelectEquipmentColumn(i, 0);
                break;
            case 2:
                screen->panels[i].selection = 0;
                Frontend_SelectEquipmentColumn(i, 0);
                break;
            }
        }
    }
    SoundElement_PlayFlatSound(3704);
    return 0;
}

/* Advance the four-player results screen one frame: slide the arrows, count the timer down, step the state. */
s32 Player_UpdateFourPlayerResults(void) {
    s32 i;
    s32 player;
    s32 left;
    s32 timer;
    struct FourPlayerResultsScreen *screen;
    switch (g_equipmentAndResultsScreen->state) {
    case 1:
        g_equipmentAndResultsScreen->leftArrow->x = (u16)g_equipmentAndResultsScreen->leftArrow->x + (u16)g_equipmentAndResultsScreen->leftStep;
        g_equipmentAndResultsScreen->rightArrow->x = (u16)g_equipmentAndResultsScreen->rightArrow->x - (u16)g_equipmentAndResultsScreen->rightStep;
        g_equipmentAndResultsScreen->timer--;
        if (g_equipmentAndResultsScreen->timer <= 0) {
            SoundElement_PlayFlatSound(3705);
            Widget_SetWidgetFlag08(g_equipmentAndResultsScreen->message, 1);
            SmpFlicker_StartFlicker(g_equipmentAndResultsScreen->resource, 4);
            g_equipmentAndResultsScreen->state = 4;
            g_equipmentAndResultsScreen->timer = 4;
        }
        break;
    case 2:
        g_equipmentAndResultsScreen->leftArrow->x = (u16)g_equipmentAndResultsScreen->leftArrow->x - (u16)g_equipmentAndResultsScreen->leftStep;
        g_equipmentAndResultsScreen->rightArrow->x = (u16)g_equipmentAndResultsScreen->rightArrow->x + (u16)g_equipmentAndResultsScreen->rightStep;
        g_equipmentAndResultsScreen->timer--;
        if (g_equipmentAndResultsScreen->timer <= 0) {
            g_equipmentAndResultsScreen->state = 3;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(g_equipmentAndResultsScreen->next);
            return 0;
        }
        break;
    case 3:
        Tsmos_ActivateControllerState();
        return 0;
    case 4:
        screen = g_equipmentAndResultsScreen;
        timer = screen->timer;
        left = timer - 1;
        if (left >= 0) {
            left = timer - (timer < left ^ 1);
        } else {
            left = 0;
        }
        screen->timer = left;
        if (g_equipmentAndResultsScreen->timer <= 0) {
            if (SmpFlicker_IsFlickerIdle(g_equipmentAndResultsScreen->resource)) {
                SmpFlicker_RestoreFlickerValue(g_equipmentAndResultsScreen->resource);
                g_equipmentAndResultsScreen->state = 3;
            }
        }
        return 0;
    case 5:
        SoundElement_PlayFlatSound(3704);
        g_equipmentAndResultsScreen->state = 2;
        g_equipmentAndResultsScreen->timer = 4;
        Widget_SetWidgetFlag08(g_equipmentAndResultsScreen->message, 0);
        for (player = 0; player < 4; player++) {
            for (i = 0; i < 5; i++) {
                Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentPrimaryWidgetIds[player][i].value), 0);
            }
            Widget_SetWidgetFlag08(g_equipmentAndResultsScreen->panels[player].item, 0);
        }
        break;
    case 6:
    case 7:
        break;
    }
    return 0;
}

extern Gfx *g_displayListCursor;
extern s32 g_hudReferenceViewportWidth;
extern void Preview_DrawModelPreview(struct ModelPreview *self);
extern s32 Model_GetModelRecordCount(s32 *record);
#if defined(VERSION_DE)
extern void Frontend_DrawResultModelPreviewDe(char *);
#else
extern void Preview_DrawMenuModelItem(struct MenuModelItem *item);
#endif
extern struct MenuPlayerScissorRect g_menuPlayerScissorRects[];
/* Draw callback of the four-player results screen: on draw event 1 in state 3 it resets the fill colour g_menuModelFillEnabled
   and the colour table g_menuModelFillColor, scissors the display list to each active panel rectangle in g_menuPlayerScissorRects and draws
   the panel, then clips to the full screen and draws the badge of every panel whose state is 1. Returns zero. */
s32 Player_DrawFourPlayerResults(void *window, void *item, s32 event) {
    s32 i;
    if (event == 1 && g_equipmentAndResultsScreen->state == 3) {
        g_menuModelFillEnabled = 0;
        g_menuModelFillColor[0] = 255.0f;
        g_menuModelFillColor[1] = 255.0f;
        g_menuModelFillColor[2] = 255.0f;
        g_menuModelFillColor[3] = 255.0f;
        for (i = 0; i < 4; i++) {
            if (g_equipmentAndResultsScreen->panels[i].state == 1 || g_equipmentAndResultsScreen->panels[i].state == 2) {
                gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, g_menuPlayerScissorRects[i].left, g_menuPlayerScissorRects[i].top, g_menuPlayerScissorRects[i].right, g_menuPlayerScissorRects[i].bottom);
                Preview_DrawModelPreview(&g_equipmentAndResultsScreen->panels[i]);
            }
        }
        gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
        for (i = 0; i < 4; i++) {
            if (g_equipmentAndResultsScreen->panels[i].state == 1 && Model_GetModelRecordCount(g_equipmentAndResultsScreen->badges[i]) != 0) {
                g_menuModelFillEnabled = 1;
                g_menuModelFillColor[3] = 150.0f;
#if defined(VERSION_DE)
                Frontend_DrawResultModelPreviewDe(g_equipmentAndResultsScreen->badges[i]);
#else
                Preview_DrawMenuModelItem(g_equipmentAndResultsScreen->badges[i]);
#endif
                g_menuModelFillEnabled = 0;
                g_menuModelFillColor[3] = 255.0f;
            }
        }
    }
    return 0;
}

/* s_mitetText_Player.CPP */
#if defined(VERSION_US)
/* ROM-grounded data for us; supplied-list member has no us-rev1 placement. */
unsigned int s_mitetText[4] = {
    0x52595F4D, 0x49544554, 0x00000400, 0x3F800000,
};
#endif
