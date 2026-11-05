#include "Common/menu_screen_setup.h"
#include "Common/resident_event_handler.h"
#include "include_asm.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/sharedplayer.h"
#include "Common/selectionscreenstate.h"
#include "Common/label.h"
#include "types.h"
#include "Render/soundelement_playflatsound.h"
#include "Common/aiprofile.h"
#include "Common/player_join_requests.h"
#include "Frontend/menu_dispatchselectionmenuevent.h"
#include "Common/sessionhandlerrow.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/screen.h"
#include "Common/runtime_declarations.h"

/* unit MENU.CPP */
/* Enables mode 1 through Tsmos_SetMenuModelFlag, places the menu model at (17, -10, -50) with uniform scale 0.14, zero rotation and a (0, 5, 0) offset, then issues request 0xE78 through SoundElement_PlayFlatSound; returns zero. */

s32 Menu_PositionSelectionMenuModel(void) {
    SetupModelVector scale;
    SetupModelVector position;
    SetupModelVector rotation;
    SetupModelVector offset;

    Tsmos_SetMenuModelFlag(1);
    scale.value.x = 0.14f;
    scale.value.y = 0.14f;
    scale.value.z = 0.14f;
    rotation.value.x = 0.0f;
    rotation.value.y = 0.0f;
    rotation.value.z = 0.0f;
    offset.value.x = 0.0f;
    offset.value.y = 5.0f;
    offset.value.z = 0.0f;
    position.value.x = 17.0f;
    position.value.y = -10.0f;
    position.value.z = -50.0f;
    Frontend_InitModelPreviewTransform(((FrontendPreviewMenuView *) g_profileStatisticsScreen)->model, 0, scale.words, position.words);
    Frontend_SetPreviewRotation(((FrontendPreviewMenuView *) g_profileStatisticsScreen)->model, rotation.words);
    Frontend_SetPreviewRotationSpeed(((FrontendPreviewMenuView *) g_profileStatisticsScreen)->model, offset.words);
    SoundElement_PlayFlatSound(3704);
    return 0;
}

#include <PR/gbi.h>
#include "Common/video_dimensions.h"
#include "Preview/preview.h"
#include "Model/model.h"
#include "Frontend/frontend.h"
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

/* On event 3 with value 0, calls MarkMenuEventHandled, hands Focus_AdvanceActiveSlot_Menu the menu block's active slot
   (from g_profileStatisticsScreen), calls Focus_ShowUnlockedEntries with 0x6E,
   Focus_RefreshProfileStatistics and Focus_RefreshUnlockedFocusLabel, and clears the menu block's focus word. Returns zero. */
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

/* Calls the handler registered for event (tables g_selectionMenuHandlerEvents, g_selectionMenuHandlerKinds, g_selectionMenuHandlers). A row matches when its event equals event and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
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
            if ((*(s32 *) (((char *) (&g_selectionMenuHandlerEvents)) + offset)) == event) {
                actor_kind = ((struct MenuWidget *) ((char *) actor))->resource;
                table_kind = (*(s32 *) (((char *) (&g_selectionMenuHandlerKinds)) + offset));
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
