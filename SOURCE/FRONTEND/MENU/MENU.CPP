#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "include_asm.h"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/LABEL.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/REQUESTRECAT10.H"
#include "FRONTEND/MENU_DISPATCHSELECTIONMENUEVENT.H"

/* Enables mode 1 through Tsmos_SetModeOneFlag, places the menu model at (17, -10, -50) with uniform scale 0.14, zero rotation and a (0, 5, 0) offset, then issues request 0xE78 through SoundElement_PlayFlatSound; returns zero. */





/* The hub spells g_profileStatisticsScreen as the padded menu block; this unit reaches the model name at +0x08
 * through its own view, so each use casts back to it. */
extern void Frontend_InitModelPreviewTransform(char *model, s32 modelId, CVector3 scale, CVector3 position);
extern void Frontend_SetPreviewRotation(char *model, CVector3 rotation);
extern void Frontend_SetPreviewRotationSpeed(char *model, CVector3 offset);

s32 Menu_PositionSelectionMenuModel(void) {
    CVector3 scale;
    CVector3 position;
    CVector3 rotation;
    CVector3 offset;

    Tsmos_SetModeOneFlag(1);
    scale.x = 0.14f;
    scale.y = 0.14f;
    scale.z = 0.14f;
    rotation.x = 0.0f;
    rotation.y = 0.0f;
    rotation.z = 0.0f;
    offset.x = 0.0f;
    offset.y = 5.0f;
    offset.z = 0.0f;
    position.x = 17.0f;
    position.y = -10.0f;
    position.z = -50.0f;
    Frontend_InitModelPreviewTransform(((FrontendPreviewMenuView *) g_profileStatisticsScreen)->model, 0, scale, position);
    Frontend_SetPreviewRotation(((FrontendPreviewMenuView *) g_profileStatisticsScreen)->model, rotation);
    Frontend_SetPreviewRotationSpeed(((FrontendPreviewMenuView *) g_profileStatisticsScreen)->model, offset);
    SoundElement_PlayFlatSound(3704);
    return 0;
}

#include <PR/gbi.h>
#include "COMMON/VIDEO_DIMENSIONS.H"
extern s32 Model_GetModelRecordCount(s32 *record);
extern void Preview_DrawMenuModelItem(struct MenuModelItem *item);
extern Gfx *g_displayListCursor;
extern s32 g_hudReferenceViewportWidth;
/* Draw callback of the menu block: on draw event 1 in state 3 it clears the fill mode g_menuModelFillEnabled, sets the fill
 * colour g_menuModelFillColor to opaque white, scissors the display list to the full screen and, when the block record at
 * +0x08 holds a model, draws it once in fill mode 1 at alpha 210, then restores the fill state. Returns zero. */
s32 Menu_DrawMenuBlockModel(void *window, void *item, s32 event) {
    if (event == 1 && g_profileStatisticsScreen->menuPhase == 3) {
        g_menuModelFillEnabled = 0;
        g_menuModelFillColor[0] = 255.0f;
        g_menuModelFillColor[1] = 255.0f;
        g_menuModelFillColor[2] = 255.0f;
        g_menuModelFillColor[3] = 255.0f;
        gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
        if (Model_GetModelRecordCount(&g_profileStatisticsScreen->record) != 0) {
            g_menuModelFillEnabled = 1;
            g_menuModelFillColor[3] = 210.0f;
            Preview_DrawMenuModelItem(&g_profileStatisticsScreen->record);
            g_menuModelFillEnabled = 0;
            g_menuModelFillColor[3] = 255.0f;
        }
    }
    return 0;
}

/* On event 3 with value 0, calls MarkMenuEventHandled, hands Focus_AdvanceActiveSlot_Menu the cursor word the hub
   names activeSlot at +0x10C of the menu block g_profileStatisticsScreen points to, calls Focus_ShowUnlockedEntries with 0x6E,
   Focus_RefreshProfileStatistics and Focus_RefreshUnlockedFocusLabel, and clears the hub's focus word at +0x0EC. Returns zero. */

extern void MarkMenuEventHandled();


s32 Menu_HandleNextProfileEvent(void *first, void *second, u32 event, s32 value) {
    if ((event >> 16) == 3 && value == 0) {
        MarkMenuEventHandled();
        Focus_AdvanceActiveSlot(&g_profileStatisticsScreen->activeSlot);
        Focus_ShowUnlockedEntries(110);
        Focus_RefreshProfileStatistics();
        Focus_RefreshUnlockedFocusLabel();
        g_profileStatisticsScreen->focus = 0;
    }
    return 0;
}

s32 Menu_BeginSelectionMenuExit(void) {
    MarkMenuEventHandled();
    g_profileStatisticsScreen->menuPhase = 5;
    g_profileStatisticsScreen->reservedWord = 4;
    return 0;
}

/* Calls MarkMenuEventHandled with the arguments it was given and returns zero. */

s32 Menu_ConsumeSelectionMenuEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_selectionMenuHandlerEvents, an actor kind at g_selectionMenuHandlerKinds and a handler at g_selectionMenuHandlers: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */



extern s32 g_selectionMenuHandlerEvents;
extern s32 g_selectionMenuHandlerKinds;
extern WidgetEventHandler g_selectionMenuHandlers;

s32 Menu_DispatchSelectionMenuEvent(void *actor, s32 event, s32 eventValue, s32 eventData, s32 eventContext) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_selectionMenuHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_selectionMenuHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_selectionMenuHandlerEvents)) + offset))->value == event) {
                actor_kind = ((struct MenuActorInputView *) ((char *) actor))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_selectionMenuHandlerKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(actor, event, eventValue, eventData, eventContext);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}



