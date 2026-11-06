#include "Frontend/menuimage.h"
#include "Camera/camera_address_symbols.h"
#include "Common/gameplay_settings.h"
#include "include_asm.h"
#include "Frontend/results_player_panels.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/screen.h"
#include "Common/world.h"
#include "Frontend/equip_loadequipmentselections.h"
#include "Frontend/menu_image.h"
#include "Frontend/equip_activateequipmentpanel.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/cache_freememory.h"

/* unit MENU_IMAGE.CPP */
/* Clears the 22 owned-equipment flags of each of the 4 player records in
   g_playerSettings_Achieve; for each active player it looks up the player's model kind through Scene_FindActorDefinition and marks each of its 8 slot ids at least 1219 as owned (the owned flag indexed by the id less 1219), then refreshes the player's loadout columns through Equip_LoadEquipmentSelections. */
void Frontend_ResetEquipmentFromCharacter(void) {
    Shared_PlayerSettingsRecord *record;
    struct Model *model;
    s32 id;
    s32 i;
    s32 player;

    for (player = 0; player < 4; player++) {
        record = &g_playerSettings[player];
        for (i = 0; i < 22; i++) {
            record->weapons[i] = 0;
        }
        if (record->enabled == 1) {
            model = Scene_FindActorDefinition(&g_world, 11, record->character);
            for (i = 0; i < 8; i++) {
                id = model->slots[i];
                if (id >= 1219) {
                    record->weapons[id - 1219] = 1;
                }
            }
            Equip_LoadEquipmentSelections(player);
        }
    }
}

/* Counts how many of the four panel entries g_equipmentAndResultsScreen points to have their active word equal to one. */
s32 Frontend_CountActiveEquipmentPanels(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_equipmentAndResultsScreen->panels[i].state == 1) {
            count++;
        }
    }
    return count;
}

/* Moves the cursor of player p's entry of g_equipmentAndResultsScreen to column c: unless c is 5 it
   hides the item whose id g_equipmentPrimaryWidgetIds[p][c] names in the screen window, shows the item
   g_equipmentSecondaryWidgetIds[p][c] names with alpha 0x96, stores c as the entry's selection and redraws that
   column through Equip_ShowEquipChoice with the entry's value for it. */
void Frontend_SelectEquipmentColumn(s32 player, s32 column) {
    struct ResourceSmpFlickerCreateFlickerWidget *item;

    if (column != 5) {
        item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentPrimaryWidgetIds[player][column].value);
        Widget_SetWidgetFlag08(item, 1);
    }
    item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentSecondaryWidgetIds[player][column].value);
    Widget_SetWidgetFlag40(item, 1);
    item->value = 150;
    g_equipmentAndResultsScreen->panels[player].selection = column;
    Equip_ShowEquipChoice(player, column, g_equipmentAndResultsScreen->panels[player].values[column]);
}

/* Releases the object g_equipmentAndResultsScreen holds through Cache_FreeMemory, clears g_equipmentAndResultsScreen, calls
   Tsmos_ActivateControllerState and Tsmos_SetMenuModelFlag with 2, and returns zero. */
s32 Frontend_FreeEquipmentScreen(void) {
    Cache_FreeMemory(g_equipmentAndResultsScreen);
    g_equipmentAndResultsScreen = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetMenuModelFlag(2);
    return 0;
}

/* Handles an input event for the entry of g_equipmentAndResultsScreen the low half of the third argument
   selects: when that entry is active, the high half is 3 and the fourth argument is zero, it calls
   MarkMenuEventHandled, resets the entry through Equip_LoadEquipmentSelections, redraws its six columns and then its
   selected column through Equip_ShowEquipChoice, and plays sound 0xE7C; it always returns zero. Written
   from the assembly; the entries are an array member of the screen so each column offset is
   summed before the base is added. */
s32 Frontend_RestoreEquipmentSelections(void *first, void *second, u32 event, s32 held) {
    s32 index;
    s32 i;

    index = event & 0xFFFF;
    if (g_equipmentAndResultsScreen->panels[index].state != 1) {
        return 0;
    }
    if ((event >> 16) != 3) {
        return 0;
    }
    if (held != 0) {
        return 0;
    }
    MarkMenuEventHandled();
    Equip_LoadEquipmentSelections(index);
    for (i = 0; i < 6; i++) {
        Equip_ShowEquipChoice(index, i, g_equipmentAndResultsScreen->panels[index].values[i]);
    }
    Equip_ShowEquipChoice(index, g_equipmentAndResultsScreen->panels[index].selection,
                  g_equipmentAndResultsScreen->panels[index].values[g_equipmentAndResultsScreen->panels[index].selection]);
    SoundElement_PlayFlatSound(3708);
    return 0;
}

/* Calls MarkMenuEventHandled and, when the fourth argument is one and the entry of g_equipmentAndResultsScreen the third argument selects has a nonzero state word with its active word equal to one, plays sound 0xE7B through SoundElement_PlayFlatSound and calls Equip_MoveEquipmentColumn with the entry index and 1, returning zero. */
s32 Frontend_SelectPreviousEquipmentColumn(void *first, void *second, s32 slot, s32 active) {
    u16 index;

    MarkMenuEventHandled();
    if (active == 1) {
        index = slot;
        if (g_equipmentAndResultsScreen->panels[index].mode != 0 && g_equipmentAndResultsScreen->panels[index].state == active) {
            SoundElement_PlayFlatSound(3707);
            Equip_MoveEquipmentColumn(index, 1);
            return 0;
        }
    }
    return 0;
}

/* Calls MarkMenuEventHandled and, when the fourth argument is one and the entry of g_equipmentAndResultsScreen the third argument selects has a nonzero state word with its active word equal to one, plays sound 0xE7B through SoundElement_PlayFlatSound and calls Equip_MoveEquipmentColumn with the entry index and -1, returning zero. */
s32 Frontend_SelectNextEquipmentColumn(void *first, void *second, s32 slot, s32 active) {
    u16 index;

    MarkMenuEventHandled();
    if (active == 1) {
        index = slot;
        if (g_equipmentAndResultsScreen->panels[index].mode != 0 && g_equipmentAndResultsScreen->panels[index].state == active) {
            SoundElement_PlayFlatSound(3707);
            Equip_MoveEquipmentColumn(index, -1);
            return 0;
        }
    }
    return 0;
}

/* Calls MarkMenuEventHandled and, when the fourth argument is one and the entry of g_equipmentAndResultsScreen the third argument selects is in mode two (its state word) with its word at 0x4B0 equal to one, plays sound 0xE7B through SoundElement_PlayFlatSound and calls Equip_CycleEquipmentChoice with the entry index and -1, returning zero. */
s32 Frontend_SelectPreviousEquipmentChoice(void *first, void *second, s32 slot, s32 active) {
    u16 index;

    MarkMenuEventHandled();
    if (active == 1) {
        index = slot;
        if (g_equipmentAndResultsScreen->panels[index].mode == 2 && g_equipmentAndResultsScreen->panels[index].state == active) {
            SoundElement_PlayFlatSound(3707);
            Equip_CycleEquipmentChoice(index, -1);
            return 0;
        }
    }
    return 0;
}

/* Calls MarkMenuEventHandled and, when the fourth argument is one and the entry of g_equipmentAndResultsScreen the third argument selects is in mode two (its state word) with its word at 0x4B0 equal to one, plays sound 0xE7B through SoundElement_PlayFlatSound and calls Equip_CycleEquipmentChoice with the entry index and 1, returning zero. */
s32 Frontend_SelectNextEquipmentChoice(void *first, void *second, s32 slot, s32 active) {
    u16 index;

    MarkMenuEventHandled();
    if (active == 1) {
        index = slot;
        if (g_equipmentAndResultsScreen->panels[index].mode == 2 && g_equipmentAndResultsScreen->panels[index].state == active) {
            SoundElement_PlayFlatSound(3707);
            Equip_CycleEquipmentChoice(index, 1);
            return 0;
        }
    }
    return 0;
}

/* Cancels a player's selection or schedules the menu transition according to the current selection state. */
int Frontend_CancelEquipmentSelection(int a,int b,unsigned int player) {
 MarkMenuEventHandled();player &= 0xFFFF;
 switch(g_equipmentAndResultsScreen->panels[player].state) {
 case 1:g_equipmentAndResultsScreen->state=5;g_equipmentAndResultsScreen->timer=4;g_equipmentAndResultsScreen->next=7;break;
 case 2:g_equipmentAndResultsScreen->panels[player].state=0;SmpOverlay_SetSlotValue(g_equipmentAndResultsScreen->menu,player,0);Preview_SetPreviewTransformUpdate(g_equipmentAndResultsScreen->panels[player].previewTransform,1);Equip_ActivateEquipmentPanel(player);break;
 }
 return 0;
}

/* Calls the handler registered for eventId (tables g_equipmentEventIds, g_equipmentEventActorKinds, g_equipmentEventHandlers). A row matches when its event equals eventId and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 Frontend_DispatchEquipmentEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    EquipmentEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_equipmentEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_equipmentEventHandlers;
        index = 0;
        do {
            if (g_equipmentEventIds[index].value == eventId) {
                actor = eventTarget;
                actor_kind = actor->resource;
                table_kind = g_equipmentEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, eventId, eventCode, eventValue, repeatCount);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

#include <PR/gbi.h>
#include <platform_sdk.h>
#include "Common/sessionhandlerrow.h"
#include "Common/triple.h"
#include "Common/runtime_declarations.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Tsmos/tsmos_activatecontrollerstate.h"
#include "Smp_overlay/smp_overlay.h"
#include "Preview/frontend_drawmodelpreview.h"
#include "Scene/scene_drawtransitioncoloroverlay.h"
#include "Node/node_replacewidgetlinks.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Frontend/frontend_drawmodelpreview.h"
/* A menu's title image: image id, RGB tint words, animation frame and a shown flag. */
void Frontend_DrawMenuImage(MenuImageState *menu) {
    s32 frame;
    float b, a;
    float *screen;
    if (menu->state == 1) {
        frame = menu->frame;
        screen = g_fallbackScreenMessageEmitter;
        OnScreen_SetupTextRendering();
        Geometry_SetModePreset(21);
        b = 1.0f;
        a = b;
        switch (g_frontendCurrentVideoModeIndex) {
        case 0:
            a = b;
            break;
        case 1:
            a = 1.6901408f;
            b = 1.6216216f;
            break;
        case 2:
            a = 1.6901408f;
            b = 1.0810812f;
            break;
        }
        gDPSetEnvColor(g_displayListCursor++, (u8)menu->color[0], (u8)menu->color[1], (u8)menu->color[2], 0xFF);
        gDPSetPrimColor(g_displayListCursor++, 0, 0, 0xE0, 0, 0, 0xFF);
        OnScreen_DrawSpriteResource(menu->resource, frame, (s16)(s32)screen[169], (s16)(s32)screen[170],
                         a * 9.0f, b * 4.0f, 1);
    }
}

#if defined(VERSION_EU_X)
unsigned int k_menuImageFragment[3] = {
    0x000000FF, 0x00000000, 0x00000010,
};
#endif

#if defined(VERSION_DE)
unsigned int k_MenuImageEncodedWords[3] = {
    0x3FD85689, 0x3FCF914C, 0x3FD85689,
};
#endif
