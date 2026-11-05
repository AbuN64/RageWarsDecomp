#include "Audio/sequence_timing_records.h"
#include "Common/resident_event_handler.h"
#include "Common/frustum.h"
#include "Common/animation.h"
#include "Common/vector4f.h"
#include "Menu/smp_records.h"
#include "Menu/widget_records.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/menu_screen_elements.h"
#include "Common/archive_chunk_images.h"
#include "Menu/scroll.h"
#include "types.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Menu/smp_slider.h"
#include "Ui/Quag/N64_Eng.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/cache_freememory.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Data/rest_source_records.h"
#include "Menu_choice/frontend_initplaymodemenu.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Common/selectionscreenstate.h"
#include "Ui/ui_address_symbols.h"
#include "Frontend/widget_drawtextwidget.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Ui/smp_list.h"
#include "Frontend/frontend.h"

/* Stores the transition mode of an object and plays sound 0xE77 for mode 1 or 0xE76 for mode 2
   through SoundElement_PlayFlatSound. */

/* Dispatches event eventId to the first row of this widget's event handler table whose event matches and whose actor kind
   equals the widget's actor kind or is ANY_ACTOR_KIND; returns that handler's result, or 0 when no row matches. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

/* Allocates a zeroed slider widget that copies the header of the widget found for the first resource id, links the widget found for the second as its owner, stores the third argument and registers it in place of the source widget. */

/* Dispatches event eventId to the first row of this widget's event handler table whose event matches and whose actor kind
   equals the widget's actor kind or is ANY_ACTOR_KIND; returns that handler's result, or 0 when no row matches. */

/* Draws the child widget of the window with the arguments passed by value once Widget_ComputeWidgetBounds resolves the window rectangle; when the window clips its children it saves the current clip bounds, narrows them to the resolved rectangle for the draw and restores them afterwards. */

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

/* Returns the transition mode of a record. */
s32 SmpSlider_GetTransitionMode(s32 *record) {
    return ((SliderTransitionView *)record)->modeState;
}

/* Sets the transition flag that SmpSlider_DisableTransition clears. */

void SmpSlider_EnableTransition(struct Access_s32_5C *object) {
    object->field = 1;
}

/* Clears the transition flag that SmpSlider_EnableTransition sets to one. Frontend_InitPlayModeMenu calls it on
   the object SmpFade_CreateFadeWidget has just returned. */

void SmpSlider_DisableTransition(struct Access_s32_5C *object) {
    object->field = 0;
}

s32 SmpSlider_DispatchTransitionEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    ResidentEventHandlerEntry *handlerEntry;

    for (handlerEntry = (ResidentEventHandlerEntry *)&g_sliderTransitionEventIds; handlerEntry->handler != 0; handlerEntry++) {
        if (handlerEntry->event == eventId) {
            s32 actorKind = ((struct MenuWidget *)widget)->resource;
            if (handlerEntry->actorKind == actorKind || handlerEntry->actorKind == ANY_ACTOR_KIND) {
                return handlerEntry->handler(widget, eventId, eventData0, eventData1, eventData2);
            }
        }
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

/* Returns the item the scroll bar currently shows. */
s32 SmpSlider_GetSliderItem(s32 *record) {
    return ((Scroll *)record)->item;
}

/* Positions a scroll bar: records the current item and moves the bar to the item's place along the track, scaling the item
   by the item count to the track length. */

void SmpSlider_SetSliderItem(struct Scroll *scroll, s32 item) {
    scroll->item = item;
    scroll->bar->ticksPerQuarter = (f32) item / (f32) scroll->count * (f32) scroll->length;
}

s32 SmpSlider_DispatchSliderEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    ResidentEventHandlerEntry *handlerEntry;

    for (handlerEntry = (ResidentEventHandlerEntry *)&g_sliderWidgetEventIds; handlerEntry->handler != 0; handlerEntry++) {
        if (handlerEntry->event == eventId) {
            s32 actorKind = ((struct MenuWidget *)widget)->resource;
            if (handlerEntry->actorKind == actorKind || handlerEntry->actorKind == ANY_ACTOR_KIND) {
                return handlerEntry->handler(widget, eventId, eventData0, eventData1, eventData2);
            }
        }
    }
    return 0;
}

void SmpSlider_DrawSliderWidget(void *widget, Args args) {
    struct WidgetRect first;
    struct WidgetRect basis;
    struct WidgetRect value;
    struct WidgetRect transformed;
    s32 changed;
    UiWidget *window = widget;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((window->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.left, &value.top, &value.right, &value.bottom);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.left, transformed.top,
                          transformed.right, transformed.bottom);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(window->children, *(sm_dldc *)&args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.left, value.top, value.right, value.bottom);
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

/* Puts the menu into state 2 and dims every item whose kind is not 8 to alpha 100. Returns zero. */

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

/* Puts the menu into state 2 and highlights every item whose kind is not 8 with alpha 200. Returns zero. */

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

#if defined(VERSION_US_REV1)
SmpSliderListEventRecords g_smpSliderListEventRecords = {
    3591,
    30000,
    (unsigned int)g_SmpSlider_DimSliderItemsAddress,
    15,
    30000,
    (unsigned int)&SmpSlider_HighlightSliderItems,
    16,
    30000,
    (unsigned int)&SmpList_ResetEntryCommands,
    8,
    30000,
    (unsigned int)&SmpList_HandleIncrementInput,
    7,
    30000,
    (unsigned int)&SmpList_HandleDecrementInput,
    3587,
    30000,
    (unsigned int)&SmpList_DestroyController,
    11,
    30000,
    (unsigned int)&SmpList_HandleStopEvent,
    3592,
    30000,
    (unsigned int)&SmpList_UpdateSliderMotion,
    { 0x00000000, 0x00000000, 0x00000000 },
};

/* Zero word after the list button event table; no instruction reads it. */
unsigned int g_listButtonEventTableZeroTail[1] = { 0x00000000 };
#endif
