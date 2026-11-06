#include "Common/resident_event_handler.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/frustum.h"
#include "include_asm.h"
#include "Common/animation.h"
#include "Menu/smp_records.h"
#include "Menu/widget_records.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/menu_screen_elements.h"
#include "Menu/scroll.h"
#include "Common/menu_overlay.h"
#include "Common/name.h"
#include "types.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Ui/Quag/N64_Eng.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/cache_freememory.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Data/rest_source_records.h"
#include "Ui/Tsmos/Smp/smp_button.h"
#include "Common/selectionscreenstate.h"
#include "Ui/ui_address_symbols.h"
#include "Ui/X_files/x_plus.h"
#include "Frontend/widget_drawtextwidget.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Frontend/frontend.h"

/* Allocates a zeroed list widget that copies the header of the widget found for the first resource id, makes the widget found for the second its owner with no entries, and registers it in place of the source widget. */

/* Appends to a menu: passes the next free menu entry record, selected by the entry count, to XPlus_CopyString_ResultsFillprofileweaponrows and increments the count. SmpButton_SelectListEntry_PlayerInitplayersettingsscreen selects an entry. */

/* Dispatches event eventId to the first row of this widget's event handler table whose event matches and whose actor kind
   equals the widget's actor kind or is ANY_ACTOR_KIND; returns that handler's result, or 0 when no row matches. */

/* Draws the child widget of the window with the arguments passed by value once Widget_ComputeWidgetBounds resolves the window rectangle; when the window clips its children it saves the current clip bounds, narrows them to the resolved rectangle for the draw and restores them afterwards. */

/* When the fourth argument is one, advances the menu selection to the next entry, wrapping to the first, points the owner at the selected entry and plays the selection sound. Returns zero. */

/* When the fourth argument is one, moves the menu selection to the previous entry, wrapping to the last, points the owner at the selected entry and plays the selection sound. Returns zero. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

/* Dispatches event eventId to the first row of this widget's event handler table whose event matches and whose actor kind
   equals the widget's actor kind or is ANY_ACTOR_KIND; returns that handler's result, or 0 when no row matches. */

/* Plays the menu click sound, dims every child of the list except the kind-8 ones, and returns zero. */

/* Releases the supplied object through Cache_FreeMemory and returns zero. */

MenuListWidget *SmpButton_CreateListWidget(s32 listWidgetId, s32 itemWidgetId) {
    MenuListWidget *source;
    void *context;
    MenuListWidget *result;
    void *child;

    source = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), listWidgetId & 0xFFFF);
    context = Node_GetScreenData(GetMenuScreenOwner());
    result = Cache_AllocateMemory(280);
    XPlus_FillBytes(result, 0, 280);
    *(Header44 *)result = *(Header44 *)source;
    result->widgetKind = 2916;
    *(InstanceHdr *)&result->fields_2C = *(InstanceHdr *)&source->fields_2C;
    child = Node_FindWidgetByResourceId(context, itemWidgetId & 0xFFFF);
    result->owner = child;
    result->index = 0;
    result->count = 0;
    Node_WrapNodeInParent(source, result);
    source->activeKind = -1;
    Node_ReplaceNodeRefs(context, source, result);
    return result;
}

/* Returns the index of the selected entry of a menu list. */
s32 SmpButton_GetListSelection(s32 *record) {
    return ((MenuListWidget *)record)->index;
}

/* Selects entry index of the menu list: records the index and makes that entry the owner's selected entry.
   SmpButton_GetListSelection returns the index. */

void SmpButton_SelectListEntry(struct MenuListWidget *menu, s32 index) {
    menu->index = index;
    menu->owner->selected = &menu->entries[index];
}

void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text) {
    XPlus_CopyString(menu->entries[menu->count].text, text);
    menu->count++;
}

s32 SmpButton_DispatchListEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    s32 i;

    /* The table ends at the first entry without a handler. */
    for (i = 0; g_listButtonEventIds[i].handler != 0; i++) {
        if (g_listButtonEventIds[i].event == eventId) {
            s32 actorKind = ((struct MenuWidget *)widget)->resource;

            if (g_listButtonEventIds[i].actorKind == actorKind || g_listButtonEventIds[i].actorKind == ANY_ACTOR_KIND) {
                return g_listButtonEventIds[i].handler(widget, eventId, eventData0, eventData1, eventData2);
            }
        }
    }
    return 0;
}

void SmpButton_DrawListWidget(Shared_Item *widget, Args args) {
    struct WidgetRect first;
    struct WidgetRect basis;
    struct WidgetRect value;
    struct WidgetRect transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((widget->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.left, &value.top, &value.right, &value.bottom);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.left, transformed.top,
                          transformed.right, transformed.bottom);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(widget->label, *(sm_dldc *)&args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.left, value.top, value.right, value.bottom);
        }
    }
}

/* Walks the menu items and sets the alpha of every item
   whose kind is not 8 to 100. Returns zero. */

s32 SmpButton_DimListItems(struct SmpControlItemListView *menu) {
    struct SmpControlItemView *item;

    for (item = menu->items; item != 0; item = item->next) {
        if (item->kind != 8) {
            item->alpha = 100;
        }
    }
    return 0;
}

/* Walks the menu items and sets the alpha of every item
   whose kind is not 8 to 200. Returns zero. */

s32 SmpButton_HighlightListItems(struct SmpControlItemListView *menu) {
    struct SmpControlItemView *item;

    for (item = menu->items; item != 0; item = item->next) {
        if (item->kind != 8) {
            item->alpha = 200;
        }
    }
    return 0;
}

s32 SmpButton_DimListItemsWithSound(struct SmpControlItemListView *list) {
    struct SmpControlItemView *p;

    SoundElement_PlayFlatSound(3700);
    p = list->items;
    if (p != 0) {
        do {
            if (p->kind != 8) {
                p->alpha = 100;
            }
            p = p->next;
        } while (p != 0);
    }
    return 0;
}

s32 SmpButton_SelectNextListEntry(struct MenuKeyListView *menu, void *second, void *third, s32 active) {
    struct SmpButtonOwnerView *owner;

    if (active == 1) {
        owner = menu->owner;
        if (++menu->index >= menu->count) {
            menu->index = 0;
        }
        owner->selected = &menu->entries[menu->index];
        SoundElement_PlayFlatSound(3713);
        return 0;
    }
    return 0;
}

s32 SmpButton_SelectPreviousListEntry(struct MenuKeyListView *menu, void *second, void *third, s32 active) {
    struct SmpButtonOwnerView *owner;

    if (active == 1) {
        owner = menu->owner;
        if (--menu->index < 0) {
            menu->index = menu->count - 1;
        }
        owner->selected = &menu->entries[menu->index];
        SoundElement_PlayFlatSound(3713);
        return 0;
    }
    return 0;
}

s32 SmpButton_DestroyListController(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}

void SmpButton_RegisterButtonClass(void) {
    SmSmngr_RegisterElementHandlers(2913, g_SmpButton_DispatchButtonEventAddress, g_SmpButton_DrawButtonWidgetAddress, 3);
}

void SmpButton_WrapButtonWidget(s32 widgetResourceId) {
    RecordSmpButtonWrapButtonWidget *source;
    void *context;
    RecordSmpButtonWrapButtonWidget *result;

    source = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), widgetResourceId & 0xFFFF);
    context = Node_GetScreenData(GetMenuScreenOwner());
    result = Cache_AllocateMemory(68);
    XPlus_FillBytes(result, 0, 68);
    *(Header44 *)result = *(Header44 *)source;
    result->kind = 2913;
    *(InstanceHdr *)&result->fields_2C = *(InstanceHdr *)&source->fields_2C;
    Node_WrapNodeInParent(source, result);
    source->resource = -1;
    Node_ReplaceNodeRefs(context, source, result);
}

void SmpButton_EnsureButtonWrapper(RecordSmpButtonEnsureButtonWrapper *source) {
    void *context;
    RecordSmpButtonEnsureButtonWrapper *result;

    if (source->kind == 2913) {
        return;
    }
    context = Node_GetScreenData(GetMenuScreenOwner());
    result = Cache_AllocateMemory(68);
    XPlus_FillBytes(result, 0, 68);
    *(Header44 *)result = *(Header44 *)source;
    result->kind = 2913;
    *(InstanceHdr *)&result->fields_2C = *(InstanceHdr *)&source->fields_2C;
    Node_WrapNodeInParent(source, result);
    source->resource = -1;
    Node_ReplaceNodeRefs(context, source, result);
}

s32 SmpButton_DispatchButtonEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    s32 i;

    /* The table ends at the first entry without a handler. */
    for (i = 0; g_buttonWidgetEventIds[i].handler != 0; i++) {
        if (g_buttonWidgetEventIds[i].event == eventId) {
            s32 actorKind = ((struct MenuWidget *)widget)->resource;

            if (g_buttonWidgetEventIds[i].actorKind == actorKind || g_buttonWidgetEventIds[i].actorKind == ANY_ACTOR_KIND) {
                return g_buttonWidgetEventIds[i].handler(widget, eventId, eventData0, eventData1, eventData2);
            }
        }
    }
    return 0;
}

void SmpButton_DrawButtonWidget(Shared_Item *widget, Args args) {
    struct WidgetRect first;
    struct WidgetRect basis;
    struct WidgetRect value;
    struct WidgetRect transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((widget->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.left, &value.top, &value.right, &value.bottom);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.left, transformed.top,
                          transformed.right, transformed.bottom);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(widget->label, *(sm_dldc *)&args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.left, value.top, value.right, value.bottom);
        }
    }
}

/* Walks the menu items and sets the alpha of every item
   whose kind is not 8 to 100. Returns zero. */

s32 SmpButton_DimButtonItems(struct SmpControlItemListView *menu) {
    struct SmpControlItemView *item;

    for (item = menu->items; item != 0; item = item->next) {
        if (item->kind != 8) {
            item->alpha = 100;
        }
    }
    return 0;
}

/* Walks the menu items and sets the alpha of every item
   whose kind is not 8 to 200. Returns zero. */

s32 SmpButton_HighlightButtonItems(struct SmpControlItemListView *menu) {
    struct SmpControlItemView *item;

    for (item = menu->items; item != 0; item = item->next) {
        if (item->kind != 8) {
            item->alpha = 200;
        }
    }
    return 0;
}

s32 SmpButton_DimButtonItemsWithSound(MenuOverlayOwnerView *button) {
    void *node;

    SoundElement_PlayFlatSound(3700);
    node = button->root;
    if (node != 0) {
        do {
            if ((u16)((NodeMenuCreateOverlayNode *)node)->kind != 8) {
                ((NodeMenuCreateOverlayNode *)node)->alpha = 100;
            }
            node = (NodeMenuCreateOverlayNode *)((NodeMenuCreateOverlayNode *)node)->words_00[1];
        } while (node != 0);
    }
    return 0;
}

int SmpButton_DestroyButtonController(void *object)
{
    Cache_FreeMemory(object);
    return 0;
}

#if defined(VERSION_US_REV1)
ListButtonEventHandlerRecords g_listButtonEventHandlerRecords = {
    3591,
    30000,
    (unsigned int)g_SmpButton_DimListItemsAddress,
    15,
    30000,
    (unsigned int)g_SmpButton_HighlightListItemsAddress,
    16,
    30000,
    (unsigned int)g_SmpButton_DimListItemsWithSoundAddress,
    8,
    30000,
    (unsigned int)g_SmpButton_SelectNextListEntryAddress,
    7,
    30000,
    (unsigned int)g_SmpButton_SelectPreviousListEntryAddress,
    3587,
    30000,
    (unsigned int)g_SmpButton_DestroyListControllerAddress,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif

#if defined(VERSION_US_REV1)
PakActionMenuUpdateEventRecord g_pakActionMenuUpdateEventRecord = {
    3592,
    27,
    (unsigned int)addrLow_Menu_UpdatePakActionMenu,
};

RestButtonEventHandlerRecordsUsRev1Record g_smpButtonDimHighlightEventHandlers = {
    3591,
    30000,
    (unsigned int)g_SmpButton_DimButtonItemsAddress,
    15,
    30000,
    (unsigned int)g_SmpButton_HighlightButtonItemsAddress,
    16,
    30000,
    (unsigned int)g_SmpButton_DimButtonItemsWithSoundAddress,
    3587,
    30000,
    (unsigned int)g_SmpButton_DestroyButtonControllerAddress,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif
