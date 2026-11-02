#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/FRUSTUM.H"
#include "COMMON/ANIMATION.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/SLOTRECATCV1.H"
#include "MENU/SCROLL.H"
#include "TYPES.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "MENU/SMP_SLIDER.H"
#include "UI/QUAG/N64_ENG.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "DATA/REST_SOURCE_RECORDS.H"

/* SMP_SLIDER.CPP */
/* Stores a mode at offset 0x58 of an object and plays sound 0xE77 for mode 1 or 0xE76 for mode 2
   through SoundElement_PlayFlatSound. */

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_sliderTransitionEventIds, an actor kind at g_sliderTransitionEventActorKinds and a handler at g_sliderTransitionEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

/* Allocates and zeroes a 0x58-byte record, copies the header and five-word block of the record Node_FindWidgetByResourceId finds for the low half of the first argument, links the record Node_FindWidgetByResourceId finds for the second into it with its halfword at 0x18, stores the third argument, and registers it through Node_WrapNodeInParent_SmpButton and Node_ReplaceNodeRefs_SmpButton.
   Adapted from N64Eng_CreateNumericWidget with the record size, tag 0xB63, the tail fields and the dropped N64Eng_SetNumericWidgetValue call changed. */

extern struct Record *Cache_AllocateMemory(s32 size);

extern void Node_ReplaceNodeRefs(struct WidgetReferenceNodeView *node, void *from, void *to);

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_sliderWidgetEventIds, an actor kind at g_sliderWidgetEventActorKinds and a handler at g_sliderWidgetEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

/* Draws the child at 0x8 of window window with the arguments passed by value once Widget_ComputeWidgetBounds resolves the window's rectangle, and when flag 0x200 of the halfword at 0x12 is set it saves the four values N64Eng_GetClipBounds reports, narrows them by the resolved basis through Node_ClampRectToClip_FrontendOpenresourcearchive and installs them through N64Eng_SetClipBounds around the draw, restoring the saved values after it. Adapted from N64Eng_DrawNumericWidgetChildren. */

extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *draw, struct CacheResourceBlockView *hit, struct WidgetLayout *widget, struct t_dldc *ctx);

extern void N64Eng_GetClipBounds(u32 *, u32 *, u32 *, u32 *);

extern s32 Node_ClampRectToClip(struct CacheResourceBlockView *rect, struct CacheResourceBlockView *clip);

extern void Widget_DrawVisibleSiblings(void *, Args);

/* Scrolls up: moves a scroll bar to the previous item through SmpSlider_SetSliderItem unless it is already
   at the first. */

void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode) {
    object->modeState = mode;
    switch (mode) {
    case 1:
        SoundElement_PlayFlatSound(3703);
        break;
    case 2:
        SoundElement_PlayFlatSound(3702);
        break;
    }
}

/* Returns the word at offset 0x58 of a record. */
s32 SmpSlider_GetTransitionMode(s32 *record) {
    return ((SliderTransitionView *)record)->modeState;
}

/* Sets the flag word at offset 0x5C that SmpSlider_DisableTransition clears. */

void SmpSlider_EnableTransition(struct Access_s32_5C *object) {
    object->field = 1;
}

/* Clears the flag word at offset 0x5C that SmpSlider_EnableTransition sets to one. Frontend_InitPlayModeMenu calls it on
   the object SmpFade_CreateFadeWidget has just returned. */

void SmpSlider_DisableTransition(struct Access_s32_5C *object) {
    object->field = 0;
}

s32 SmpSlider_DispatchTransitionEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_sliderTransitionEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_sliderTransitionEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_sliderTransitionEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_sliderTransitionEventActorKinds)) + offset))->value;
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

/* A disabled debug print: takes a target, a format and variable arguments and does nothing beyond
   spilling the variable arguments to their home slots. Matched like the variadic stub Events_IgnoreEvent:
   the leftover float test of its compiled-out body makes the compiler fill the return delay slot
   with the last argument spill. */
void SmpSlider_IgnoreFormattedMessage(void *target, const char *format, ...)
{
    float enabled;

    enabled = 1.0f;
    if (enabled) {
    }
}

s32 SmpSlider_DestroyController(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}

void SmpSlider_RegisterSliderClass(void) {
    SmSmngr_RegisterElementHandlers(2915, g_SmpSlider_DispatchSliderEventAddress, g_SmpSlider_DrawSliderWidgetAddress, 3);
}

MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition) {
    MenuSliderWidget *source;
    s32 context;
    MenuSliderWidget *result;
    MenuSliderWidget *child;

    source = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), sliderWidgetId & 0xFFFF);
    context = Node_GetScreenData(GetMenuScreenOwner());
    result = Cache_AllocateMemory(88);
    XPlus_FillBytes(result, 0, 88);
    *(Header44 *)result = *(Header44 *)source;
    result->widgetKind = 2915;
    *(InstanceHdr *)&result->fields_2C = *(InstanceHdr *)&source->fields_2C;
    child = Node_FindWidgetByResourceId((void*)context, childWidgetId & 0xFFFF);
    result->bar = child;
    result->length = child->itemExtent;
    result->count = initialTransition;
    result->item = 0;
    result->mode = 2;
    Node_WrapNodeInParent(source, result);
    source->activeKind = -1;
    Node_ReplaceNodeRefs(context, source, result);
    return result;
}

/* Returns the word at offset 0x50 of a record. */
s32 SmpSlider_GetSliderItem(s32 *record) {
    return ((Scroll *)record)->item;
}

/* Positions a scroll bar: records the current item at offset 0x50 and stores in the halfword at
   0x18 of the bar object at 0x44 the item scaled from the item count at 0x4C to the track
   length at 0x48. */

void SmpSlider_SetSliderItem(struct Scroll *scroll, s32 item) {
    scroll->item = item;
    scroll->bar->ticksPerQuarter = (f32) item / (f32) scroll->count * (f32) scroll->length;
}

s32 SmpSlider_DispatchSliderEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_sliderWidgetEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_sliderWidgetEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_sliderWidgetEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_sliderWidgetEventActorKinds)) + offset))->value;
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

void SmpSlider_DrawSliderWidget(void *widget, Args args) {
    QuadN64EngDrawNumericWidgetChildren first;
    QuadN64EngDrawNumericWidgetChildren basis;
    QuadN64EngDrawNumericWidgetChildren value;
    QuadN64EngDrawNumericWidgetChildren transformed;
    s32 changed;
    UiWidget *window = widget;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((window->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.x, &value.z, &value.y, &value.w);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.x, transformed.z,
                          transformed.y, transformed.w);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(window->children, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.x, value.z, value.y, value.w);
        }
    }
}

void SmpSlider_DecrementSliderItem(struct Scroll *scroll) {
    if (scroll->item > 0) {
        SmpSlider_SetSliderItem(scroll, scroll->item - 1);
    }
}

void SmpSlider_IncrementSliderItem(struct Scroll *scroll) {
    if (scroll->item < scroll->count) {
        SmpSlider_SetSliderItem(scroll, scroll->item + 1);
    }
}

/* sets the menu's state word at 0x54 to 2 and Walks the item list at offset 8 of a menu and sets the byte at offset 0x10 of every item
   whose kind at 0xE is not 8 to 100. Returns zero. */

s32 SmpSlider_DimSliderItems(struct SmpControlItemListView *menu) {
    struct SmpControlItemView *item;

    menu->state = 2;
    for (item = menu->items; item != 0; item = item->next) {
        if (item->kind != 8) {
            item->alpha = 100;
        }
    }
    return 0;
}

/* sets the menu's state word at 0x54 to 2 and Walks the item list at offset 8 of a menu and sets the byte at offset 0x10 of every item
   whose kind at 0xE is not 8 to 200. Returns zero. */

s32 SmpSlider_HighlightSliderItems(struct SmpControlItemListView *menu) {
    struct SmpControlItemView *item;

    menu->state = 2;
    for (item = menu->items; item != 0; item = item->next) {
        if (item->kind != 8) {
            item->alpha = 200;
        }
    }
    return 0;
}

/* SMP_CONTROLLER_EVENTS.CPP */
#if defined(VERSION_US_REV1)
/* 800E3324_2.CPP */
extern char g_SmpSlider_DimSliderItemsAddress[];
extern char addrLow_SmpSlider_HighlightSliderItems[];
extern char addrLow_SmpList_ResetEntryCommands[];
extern char addrLow_SmpList_HandleIncrementInput[];
extern char addrLow_SmpList_HandleDecrementInput[];
extern char addrLow_SmpList_HandleStopEvent[];
extern char addrLow_SmpList_UpdateSliderMotion[];
extern char addrLow_SmpList_DestroyController[];
RestsmpSliderListEventRecordsUsRev1Record879 g_smpSliderListEventRecordsUsRev1 = {
    3591,
    30000,
    (unsigned int)g_SmpSlider_DimSliderItemsAddress,
    15,
    30000,
    (unsigned int)addrLow_SmpSlider_HighlightSliderItems,
    16,
    30000,
    (unsigned int)addrLow_SmpList_ResetEntryCommands,
    8,
    30000,
    (unsigned int)addrLow_SmpList_HandleIncrementInput,
    7,
    30000,
    (unsigned int)addrLow_SmpList_HandleDecrementInput,
    3587,
    30000,
    (unsigned int)addrLow_SmpList_DestroyController,
    11,
    30000,
    (unsigned int)addrLow_SmpList_HandleStopEvent,
    3592,
    30000,
    (unsigned int)addrLow_SmpList_UpdateSliderMotion,
    { 0x00000000, 0x00000000, 0x00000000 },
};

unsigned int g_listButtonEventTablePrefixUsRev1AlignPad[1] = { 0x00000000 };
#endif
