#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "COMMON/FRUSTUM.H"
#include "include_asm.h"
#include "COMMON/ANIMATION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/INTEGERSTATE530.H"
#include "MENU/SCROLL.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "UI/QUAG/N64_ENG.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RESMGR/resmgr_string_memory.H"
#include "DATA/REST_SOURCE_RECORDS.H"

/* SMP_BUTTON.CPP */
/* Allocates and zeroes a 0x118-byte record, copies the header and five-word block of the record Node_FindWidgetByResourceId finds for the low half of the first argument, links the record Node_FindWidgetByResourceId finds for the second into it, clears the words at 0x110 and 0x114, and registers it through Node_WrapNodeInParent_SmpButton and Node_ReplaceNodeRefs_SmpButton. Adapted from SmpSlider_CreateSliderWidget with the record size 0x118, the tag 0xB64 and the tail fields changed. */

extern void Node_ReplaceNodeRefs(WidgetReferenceNodeView *node, void *from, void *to);
extern struct Record *Cache_AllocateMemory(s32 size);

/* Appends to a menu: passes the next free 20-byte entry at offset 0x48, selected by the count at
   0x114, to XPlus_CopyString_ResultsFillprofileweaponrows and increments the count. SmpButton_SelectListEntry_PlayerInitplayersettingsscreen selects an entry. */

extern u8 *XPlus_CopyString(u8 *, u8 *);

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_listButtonEventIds, an actor kind at g_listButtonEventActorKinds and a handler at g_listButtonEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

/* Draws the child at 0x8 of window widget with the arguments passed by value once Widget_ComputeWidgetBounds resolves the window's rectangle, and when flag 0x200 of the halfword at 0x12 is set it saves the four values N64Eng_GetClipBounds reports, narrows them by the resolved basis through Node_ClampRectToClip_FrontendOpenresourcearchive and installs them through N64Eng_SetClipBounds around the draw, restoring the saved values after it. Adapted from N64Eng_DrawNumericWidgetChildren. */

extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *draw, struct CacheResourceBlockView *hit, struct WidgetLayout *widget, struct t_dldc *ctx);

extern void N64Eng_GetClipBounds(u32 *, u32 *, u32 *, u32 *);

extern s32 Node_ClampRectToClip(struct CacheResourceBlockView *rect, struct CacheResourceBlockView *clip);

extern void Widget_DrawVisibleSiblings(void *, Args);

/* When the fourth argument is one, advances a menu's selection at offset 0x110 to the next of its
   0x114 entries, wrapping to the first, points word 0x38 of its owner at 0x44 to the selected
   20-byte entry at 0x48 and plays sound 0xE81. Returns zero. */

/* When the fourth argument is one, moves a menu's selection at offset 0x110 to the previous of its
   0x114 entries, wrapping to the last, points word 0x38 of its owner at 0x44 to the selected 20-byte
   entry at 0x48 and plays sound 0xE81. Returns zero. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_buttonWidgetEventIds, an actor kind at g_buttonWidgetEventActorKinds and a handler at g_buttonWidgetEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

/* Calls SoundElement_PlayFlatSound with 0xE74 and sets the byte at 0x10 of every child in the list at 0x8 of list whose halfword at 0xE is not 8 to 100, returning zero. Adapted from N64Eng_SetLinkedCommand100WithSound with both stores to 0x5C and 0x48 removed. */

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

/* Returns the word at offset 0x110 of a record. */
s32 SmpButton_GetListSelection(s32 *record) {
    return ((MenuListWidget *)record)->index;
}

/* Selects entry i of the 20-byte records at offset 0x48 of an object: records the index at 0x110
   and points word 0x38 of the object at 0x44 to that record. SmpButton_GetListSelection returns the index. */

void SmpButton_SelectListEntry(struct MenuListWidget *menu, s32 index) {
    menu->index = index;
    menu->owner->selected = &menu->entries[index];
}

void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text) {
    XPlus_CopyString(menu->entries[menu->count].text, text);
    menu->count++;
}

s32 SmpButton_DispatchListEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_listButtonEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_listButtonEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_listButtonEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_listButtonEventActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}

void SmpButton_DrawListWidget(Shared_Item *widget, Args args) {
    QuadN64EngDrawNumericWidgetChildren first;
    QuadN64EngDrawNumericWidgetChildren basis;
    QuadN64EngDrawNumericWidgetChildren value;
    QuadN64EngDrawNumericWidgetChildren transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((widget->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.x, &value.z, &value.y, &value.w);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.x, transformed.z,
                          transformed.y, transformed.w);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(widget->label, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.x, value.z, value.y, value.w);
        }
    }
}

/* Walks the item list at offset 8 of a menu and sets the byte at offset 0x10 of every item
   whose kind at 0xE is not 8 to 100. Returns zero. */

s32 SmpButton_DimListItems(struct SmpControlItemListView *menu) {
    struct SmpControlItemView *item;

    for (item = menu->items; item != 0; item = item->next) {
        if (item->kind != 8) {
            item->alpha = 100;
        }
    }
    return 0;
}

/* Walks the item list at offset 8 of a menu and sets the byte at offset 0x10 of every item
   whose kind at 0xE is not 8 to 200. Returns zero. */

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
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_buttonWidgetEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_buttonWidgetEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_buttonWidgetEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_buttonWidgetEventActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}

void SmpButton_DrawButtonWidget(Shared_Item *widget, Args args) {
    QuadN64EngDrawNumericWidgetChildren first;
    QuadN64EngDrawNumericWidgetChildren basis;
    QuadN64EngDrawNumericWidgetChildren value;
    QuadN64EngDrawNumericWidgetChildren transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((widget->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.x, &value.z, &value.y, &value.w);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.x, transformed.z,
                          transformed.y, transformed.w);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(widget->label, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.x, value.z, value.y, value.w);
        }
    }
}

/* Walks the item list at offset 8 of a menu and sets the byte at offset 0x10 of every item
   whose kind at 0xE is not 8 to 100. Returns zero. */

s32 SmpButton_DimButtonItems(struct SmpControlItemListView *menu) {
    struct SmpControlItemView *item;

    for (item = menu->items; item != 0; item = item->next) {
        if (item->kind != 8) {
            item->alpha = 100;
        }
    }
    return 0;
}

/* Walks the item list at offset 8 of a menu and sets the byte at offset 0x10 of every item
   whose kind at 0xE is not 8 to 200. Returns zero. */

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
    void *p;

    SoundElement_PlayFlatSound(3700);
    p = button->root;
    if (p != 0) {
        do {
            if ((u16)((NodeMenuCreateOverlayNode *)p)->kind != 8) {
                ((NodeMenuCreateOverlayNode *)p)->alpha = 100;
            }
            p = (NodeMenuCreateOverlayNode *)((NodeMenuCreateOverlayNode *)p)->words_00[1];
        } while (p != 0);
    }
    return 0;
}

int SmpButton_DestroyButtonController(void *object)
{
    Cache_FreeMemory(object);
    return 0;
}

/* SMPBUTTON_DISPATCHLISTEVENT_DATA.CPP */
/* g_listButtonEventHandlerRecordsUsRev1_SmpbuttonDispatchlisteventData.CPP */
#if defined(VERSION_US_REV1)
extern char g_SmpButton_DimListItemsAddress[];
extern char g_SmpButton_HighlightListItemsAddress[];
extern char g_SmpButton_DimListItemsWithSoundAddress[];
extern char g_SmpButton_SelectNextListEntryAddress[];
extern char g_SmpButton_SelectPreviousListEntryAddress[];
extern char g_SmpButton_DestroyListControllerAddress[];
RestlistButtonEventHandlerRecordsUsRev1Record451 g_listButtonEventHandlerRecordsUsRev1 = {
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

/* g_buttonEventHandlerRecordsUsRev1_SmpbuttonDispatchlisteventData.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E3300_unclaimed_E4054 */
extern char g_Menu_UpdateSixChoiceMenuAddress[];
RestsixChoiceMenuUpdateEventRecordUsRev1Record452 g_sixChoiceMenuUpdateEventRecordUsRev1 = {
    3592,
    27,
    (unsigned int)g_Menu_UpdateSixChoiceMenuAddress,
};

extern char g_SmpButton_DimButtonItemsAddress[];
extern char g_SmpButton_HighlightButtonItemsAddress[];
extern char g_SmpButton_DimButtonItemsWithSoundAddress[];
extern char g_SmpButton_DestroyButtonControllerAddress[];
RestbuttonEventHandlerRecordsUsRev1Record453 g_buttonEventHandlerRecordsUsRev1 = {
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
