#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "include_asm.h"
#include "FRONTEND/ENTRYRECAT4D4.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SCREEN.H"
#include "COMMON/WORLD.H"
#include "FRONTEND/EQUIP_LOADEQUIPMENTSELECTIONS.H"
#include "FRONTEND/MENU_IMAGE.H"
#include "FRONTEND/EQUIP_ACTIVATEEQUIPMENTPANEL.H"
#include "FRONTEND/WIDGET_FINDWIDGETATPOINT.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"

extern FourPlayerResultsScreen *g_equipmentAndResultsScreen;

/* Clears the 22 owned bytes at 0x4C of each of the 4 player records (150 bytes apart) in
   g_playerSettings_Achieve; for each active player (byte 0x78 == 1) it looks up the player's model kind (byte
   0x80) through Scene_FindActorDefinition and marks each of its 8 slot ids at least 0x4C3 as owned (byte 0x4C
   plus the id less 0x4C3), then refreshes the player's loadout columns through Equip_LoadEquipmentSelections. */




extern u8 g_playerSettings[];

extern struct Model *Scene_FindActorDefinition(Shared_World *, s32, s32);

/* Counts how many of the four 0x4D0-byte entries g_equipmentAndResultsScreen points to have the word at offset
   0x4B0 equal to one. */




/* Moves the cursor of player p's 0x4D0-byte entry of g_equipmentAndResultsScreen to column c: unless c is 5 it
   hides the item whose id g_equipmentPrimaryWidgetIds[p * 19 + c] names in the screen window, shows the item
   g_equipmentSecondaryWidgetIds[p * 19 + c] names with alpha 0x96, stores c as the entry's selection and redraws that
   column through Equip_ShowEquipChoice with the entry's value for it. */











extern struct StateFlags g_equipmentPrimaryWidgetIds[];

extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);

extern void Widget_SetWidgetFlag08(void *object, int enabled);


/* Releases the object g_equipmentAndResultsScreen holds through Cache_FreeMemory, clears g_equipmentAndResultsScreen, calls
   Tsmos_ActivateControllerState and Tsmos_SetModeOneFlag with 2, and returns zero. */



extern void Tsmos_ActivateControllerState(void);

/* Handles an input event for the 0x4D0-byte entry of g_equipmentAndResultsScreen the low half of the third argument
   selects: when that entry is active, the high half is 3 and the fourth argument is zero, it calls
   MarkMenuEventHandled, resets the entry through Equip_LoadEquipmentSelections, redraws its six columns and then its
   selected column through Equip_ShowEquipChoice, and plays sound 0xE7C; it always returns zero. Written
   from the assembly; the entries are an array member of the screen so each column offset is
   summed before the base is added. */









/* Calls MarkMenuEventHandled and, when the fourth argument is one and the 0x4D0-byte entry of g_equipmentAndResultsScreen the third argument selects has a nonzero word at 0x4D4 (four bytes past the entry) with its word at 0x4B0 equal to one, plays sound 0xE7B through SoundElement_PlayFlatSound and calls Equip_MoveEquipmentColumn with the entry index and 1, returning zero. */





/* Calls MarkMenuEventHandled and, when the fourth argument is one and the 0x4D0-byte entry of g_equipmentAndResultsScreen the third argument selects has a nonzero word at 0x4D4 (four bytes past the entry) with its word at 0x4B0 equal to one, plays sound 0xE7B through SoundElement_PlayFlatSound and calls Equip_MoveEquipmentColumn with the entry index and -1, returning zero. Adapted from Frontend_SelectPreviousEquipmentColumn with the second Equip_MoveEquipmentColumn argument changed from 1 to -1. */





/* Calls MarkMenuEventHandled and, when the fourth argument is one and the 0x4D0-byte entry of g_equipmentAndResultsScreen the third argument selects is in mode two (the word at 0x4D4, four bytes past the entry) with its word at 0x4B0 equal to one, plays sound 0xE7B through SoundElement_PlayFlatSound and calls Equip_CycleEquipmentChoice with the entry index and -1, returning zero. */





/* Calls MarkMenuEventHandled and, when the fourth argument is one and the 0x4D0-byte entry of g_equipmentAndResultsScreen the third argument selects is in mode two (the word at 0x4D4, four bytes past the entry) with its word at 0x4B0 equal to one, plays sound 0xE7B through SoundElement_PlayFlatSound and calls Equip_CycleEquipmentChoice with the entry index and 1, returning zero. Adapted from Frontend_SelectPreviousEquipmentChoice with the second Equip_CycleEquipmentChoice argument changed from -1 to 1. */





/* Cancels a player's selection or schedules the menu transition according to the current selection state. */




extern void SmpOverlay_SetSlotValue(void *, int, int);

extern void Preview_SetPreviewTransformUpdate(struct Object49C *object, s32 value);

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_equipmentEventIds, an actor kind at g_equipmentEventActorKinds and a handler at g_equipmentEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*EquipmentEventHandler)(void *, s32, s32, s32, s32);

extern EquipmentEventHandler g_equipmentEventHandlers;

void Frontend_ResetEquipmentFromCharacter(void) {
    u8 *record;
    struct Model *model;
    s32 id;
    s32 i;
    s32 player;
    u8 *entry;

    for (player = 0; player < 4; player++) {
        record = &g_playerSettings[player * 150];
        i = 21;
        entry = record + sizeof(((Shared_PlayerSettingsRecord *)0)->weapons) - 1;
        do {
            entry[76] = 0;
            i -= 1;
            entry -= 1;
        } while (i >= 0);
        if (record[120] == 1) {
            model = Scene_FindActorDefinition(&g_world, 11, (s8) record[128]);
            for (i = 0; i < 8; i++) {
                id = model->slots[i];
                if (id >= 1219) {
                    (record + (id - 1219))[76] = 1;
                }
            }
            Equip_LoadEquipmentSelections(player);
        }
    }
}

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

void Frontend_SelectEquipmentColumn(s32 player, s32 column) {
    struct ResourceSmpFlickerCreateFlickerWidget *item;

    if (column != 5) {
        item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentPrimaryWidgetIds[player * 19 + column].value);
        Widget_SetWidgetFlag08(item, 1);
    }
    item = Node_FindWidgetByResourceId(g_equipmentAndResultsScreen->window, g_equipmentSecondaryWidgetIds[player][column].value);
    Widget_SetWidgetFlag40(item, 1);
    item->value = 150;
    g_equipmentAndResultsScreen->panels[player].selection = column;
    Equip_ShowEquipChoice(player, column, g_equipmentAndResultsScreen->panels[player].values[column]);
}

s32 Frontend_FreeEquipmentScreen(void) {
    Cache_FreeMemory(g_equipmentAndResultsScreen);
    g_equipmentAndResultsScreen = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetModeOneFlag(2);
    return 0;
}

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

int Frontend_CancelEquipmentSelection(int a,int b,unsigned int player) {
 MarkMenuEventHandled();player &= 0xFFFF;
 switch(g_equipmentAndResultsScreen->panels[player].state) {
 case 1:g_equipmentAndResultsScreen->state=5;g_equipmentAndResultsScreen->timer=4;g_equipmentAndResultsScreen->next=7;break;
 case 2:g_equipmentAndResultsScreen->panels[player].state=0;SmpOverlay_SetSlotValue(g_equipmentAndResultsScreen->menu,player,0);Preview_SetPreviewTransformUpdate(g_equipmentAndResultsScreen->panels[player].pad0,1);Equip_ActivateEquipmentPanel(player);break;
 }
 return 0;
}

s32 Frontend_DispatchEquipmentEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    EquipmentEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_equipmentEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_equipmentEventHandlers;
        index = 0;
        do {
            if (g_equipmentEventIds[index].value == eventId) {
                actor = eventTarget;
                actor_kind = actor->input;
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
#include <ultra64.h>
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
extern struct MenuModelScreen g_fallbackScreenMessageEmitter[];
/* A menu's title image: image id, RGB tint words, animation frame and a shown flag. */
typedef struct MenuImage {
    s32 image;
    s32 red;
    s32 green;
    s32 blue;
    s32 reservedWord;
    s32 frame;
    s32 shown;
} MenuImage;
void Frontend_DrawMenuImage(MenuImage *menu) {
    s32 frame;
    float b, a;
    float *screen;
    if (menu->shown == 1) {
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
        gDPSetEnvColor(g_displayListCursor++, (u8)menu->red, (u8)menu->green, (u8)menu->blue, 0xFF);
        gDPSetPrimColor(g_displayListCursor++, 0, 0, 0xE0, 0, 0, 0xFF);
        OnScreen_DrawSpriteResource(menu->image, frame, (s16)(s32)screen[169], (s16)(s32)screen[170],
                         a * 9.0f, b * 4.0f, 1);
    }
}

#if defined(VERSION_EU_X)
unsigned int k_MenuImageEncodedWordsBlock1[3] = {
    0x000000FF, 0x00000000, 0x00000010,
};
#endif

#if defined(VERSION_DE)
unsigned int k_MenuImageEncodedWords[3] = {
    0x3FD85689, 0x3FCF914C, 0x3FD85689,
};
#endif
