#include "Common/rotation_extraction.h"
#include "Common/gfx_initializefrontendservices.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Menu/widget_records.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/menu_screen_elements.h"
#include "Common/record.h"
#include "Common/texture.h"
#include "Ui/Quag/N64_Eng.h"
#include "Menu/Gfx/rect.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Menu/gfx.h"
#include "Common/resident_event_handler.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/widget_tree.h"
#include "Common/statepair.h"
#include "Common/shared_menureply.h"
#include "Render/soundelement_playflatsound.h"
#include "include_asm.h"
#include "Scene/cache_freememory.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Ui/smos.h"
#include "Frontend/widget_drawtextwidget.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Ui/n64eng.h"
#include "Data/Ui/numeric_widget_event_table.h"
#include "Ui/ui_address_symbols.h"
#include "Data/Ui/ribbon_blend_resource_data.h"
#include "System/engine_data_source.h"
#include "Data/rest_source_records.h"

/** Sets the clip rectangle of numeric widgets: left, top, right and bottom edges. */
void N64Eng_SetClipBounds(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom) {
    g_numericWidgetClipLeft = left;
    g_numericWidgetClipTop = top;
    g_numericWidgetClipRight = right;
    g_numericWidgetClipBottom = bottom;
}

void N64Eng_GetClipBounds(s32 *leftOut, s32 *topOut, s32 *rightOut, s32 *bottomOut) {

    *leftOut = g_numericWidgetClipLeft;
    *topOut = g_numericWidgetClipTop;
    *rightOut = g_numericWidgetClipRight;
    *bottomOut = g_numericWidgetClipBottom;
}

f64 N64Eng_GetTimeSeconds(void) {
    return
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
Gfx_GetConvertedCounterRatio
#else
Gfx_GetNormalizedCounter
#endif
() - (0.0);
}

/** Perform no operation. */
void N64Eng_RenderNoop(void) {
}

void N64Eng_ResetRenderState(void) { Rect_ResetRenderState(); }

/** Copy the global two-word record into the two output pointers. */
void N64Eng_GetScreenSize(int *widthOut, int *heightOut) {
    *widthOut = g_hudReferenceViewportWidth;
    *heightOut = g_hudReferenceViewportHeight;
}

int N64Eng_GetFrameCounter(void) {
    return g_uiFrameCounter;
}

/** Increment the global counter g_uiFrameCounter. */
void N64Eng_AdvanceFrameCounter(void) {
    g_uiFrameCounter += 1;
}

void N64Eng_RegisterNumericWidgetClass(void) {
    SmSmngr_RegisterElementHandlers(2917, N64Eng_DispatchNumericWidgetEvent_Address, N64Eng_DrawNumericWidgetChildren_Address, 3);
}

#ifdef VERSION_DE
const unsigned int g_N64EngData[2] = {
    0x00000000, 0x0000000F,
};
#endif
#ifdef VERSION_EU
const unsigned int g_N64EngData[2] = {
    0x00000000, 0x00000000,
};
#endif
#ifdef VERSION_EU_X
const unsigned int g_N64EngData[2] = {
    0x00000000, 0x74000000,
};
#endif
#ifdef VERSION_US
const unsigned int g_N64EngData[2] = {
    0x00000000, 0x50414354,
};
#endif
#ifdef VERSION_US_REV1
const unsigned int g_N64EngData[2] = {
    0x00000000, 0x20626F72,
};
#endif

s32 N64Eng_DispatchNumericWidgetEvent(struct Tree *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    ResidentEventHandlerEntry *handlerEntry;

    for (handlerEntry = (ResidentEventHandlerEntry *)&g_numericWidgetEventIds; handlerEntry->handler != 0; handlerEntry++) {
        if (handlerEntry->event == eventId) {
            s32 actorKind = eventTarget->id;
            if (handlerEntry->actorKind == actorKind || handlerEntry->actorKind == ANY_ACTOR_KIND) {
                return handlerEntry->handler(eventTarget, eventId, eventCode, eventValue, repeatCount);
            }
        }
    }
    return 0;
}

void N64Eng_DrawNumericWidgetChildren(void *widget, Args args) {
    struct WidgetRect first;
    struct WidgetRect basis;
    struct WidgetRect value;
    struct WidgetRect transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((((Widget *)widget)->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.left, &value.top, &value.right, &value.bottom);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.left, transformed.top,
                          transformed.right, transformed.bottom);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(((struct Tree *)widget)->child, *(sm_dldc *)&args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.left, value.top, value.right, value.bottom);
        }
    }
}

void N64Eng_DecrementNumericWidget(void *widgetStorage)
{
    RecordN64EngCreateNumericWidget *object = widgetStorage;
  s32 currentValue;
  s32 wrappingValue;
  s32 nextValue;
  if ((object->wrapEnabled) == 0)
  {
    currentValue = object->value;
    if ((object->minimumValue) < currentValue)
    {
      nextValue = currentValue - 1;
      goto block_7;
    }
  }
  else
  {
    wrappingValue = object->value;
    if (wrappingValue == (object->minimumValue))
    {
      object->value = object->maximumValue;
    }
    else
    {
      object->value = wrappingValue - 1;
    }
    nextValue = object->value;
    block_7:
    N64Eng_SetNumericWidgetValue(object, nextValue);

  }
}

void N64Eng_IncrementNumericWidget(void *widgetStorage);

void N64Eng_IncrementNumericWidget(void *widgetStorage)
{
    RecordN64EngCreateNumericWidget *object = widgetStorage;
  s32 currentValue;
  s32 wrappingValue;
  s32 nextValue;
  if ((object->wrapEnabled) == 0)
  {
    currentValue = object->value;
    if (currentValue < (object->maximumValue))
    {
      nextValue = currentValue + 1;
      goto block_7;
    }
  }
  else
  {
    wrappingValue = object->value;
    if (wrappingValue == (object->maximumValue))
    {
      object->value = object->minimumValue;
    }
    else
    {
      object->value = wrappingValue + 1;
    }
    nextValue = object->value;
    block_7:
    N64Eng_SetNumericWidgetValue(object, nextValue);
  }
}

/** Reset the object state and mark non-type-eight linked records. */
int N64Eng_SetLinkedCommand100(struct CommandListController *object) {
    struct LinkedCommandEntry *record = object->entries;
    object->state = 2;
    object->progress = 0;
    while (record != 0) {
        if (record->kind != 8) {
            record->command = 100;
        }
        record = record->next;
    }
    return 0;
}

int N64Eng_SetLinkedCommand200(struct CommandListController *object) {
    struct LinkedCommandEntry *record = object->entries;
    object->state = 2;
    object->progress = 0;
    while (record != 0) {
        if (record->kind != 8) {
            record->command = 200;
        }
        record = record->next;
    }
    return 0;
}

s32 N64Eng_SetLinkedCommand100WithSound(struct CommandListController *commandListController) {
    struct LinkedCommandEntry *p;

    commandListController->state = 2;
    commandListController->progress = 0;
    SoundElement_PlayFlatSound(3700);
    p = commandListController->entries;
    if (p != 0) {
        do {
            if (p->kind != 8) {
                p->command = 100;
            }
            p = p->next;
        } while (p != 0);
    }
    return 0;
}

s32 N64Eng_HandleNumericIncrement(void *widgetStorage, s32 eventId, s32 eventPayload, s32 eventValue, s32 fifth) {
    RecordN64EngCreateNumericWidget *object = widgetStorage;
    s32 repeatMagnitude;

    repeatMagnitude = XMath_AbsoluteInteger(fifth);
    if (repeatMagnitude < (s32)Smos_GetControlRepeatLimit()) {
        object->stepState = 2;
        object->repeatCount = 0;
    }
    if (eventValue != 1) {
        return 0;
    }
    object->stepState = eventValue;
    N64Eng_IncrementNumericWidget(object);
    SoundElement_PlayFlatSound(3713);
    return 0;
}

s32 N64Eng_HandleNumericDecrement(void *widgetStorage, s32 eventId, s32 eventPayload, s32 eventValue, s32 fifth) {
    RecordN64EngCreateNumericWidget *object = widgetStorage;
    s32 repeatMagnitude;

    repeatMagnitude = XMath_AbsoluteInteger(fifth);
    if (repeatMagnitude < (s32)Smos_GetControlRepeatLimit()) {
        object->stepState = 2;
        object->repeatCount = 0;
    }
    if (eventValue != 1) {
        return 0;
    }
    object->stepState = 0;
    N64Eng_DecrementNumericWidget(object);
    SoundElement_PlayFlatSound(3713);
    return 0;
}

/** Apply state two for event class three when the subcode is six or seven. */
int N64Eng_CancelSelectionRepeat(void *object, int eventKind, unsigned int event, int subcode) {
    struct CommandListController *controller = object;
    if ((event >> 16) == 3 && subcode < 8 && subcode >= 6) {
        controller->state = 2;
        controller->progress = 0;
    }
    return 0;
}

/* Counts ticks while the controller state is 0 or 1; after ten, steps the list selection backward (state 0) or forward (state 1). Returns 0. */
s32 TickSelectionRepeat(void *widget) {
    struct CommandListController *cmd = widget;

    switch (cmd->state) {
    case 0:
        if (++cmd->progress > 10) {
            N64Eng_DecrementNumericWidget(cmd);
        }
        break;
    case 1:
        if (++cmd->progress > 10) {
            N64Eng_IncrementNumericWidget(cmd);
        }
        break;
    case 2:
        break;
    }
    return 0;
}

s32 N64Eng_FreeNumericWidget(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
extern char g_N64engData[12];
#endif

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern NumericWidgetEventTable g_engDispatchNumericWidgetEventWords;
#endif
#if defined(VERSION_EU)
NumericWidgetEventTable g_engDispatchNumericWidgetEventWords = {
    {
        { 0xe07, 30000, N64Eng_SetLinkedCommand100_EventHandlerAddress },
        { 0xf, 30000, N64Eng_SetLinkedCommand200_EventHandlerAddress },
        { 0x10, 30000, N64Eng_SetLinkedCommand100WithSound_EventHandlerAddress },
        { 0x8, 30000, N64Eng_HandleNumericIncrement_EventHandlerAddress },
        { 0x7, 30000, N64Eng_HandleNumericDecrement_EventHandlerAddress },
        { 0xe03, 30000, N64Eng_FreeNumericWidget_EventHandlerAddress },
        { 0xb, 30000, N64Eng_CancelSelectionRepeat_EventHandlerAddress },
        { 0xe08, 30000, TickSelectionRepeat_EventHandlerAddress },
        { 0x0, 0, 0 },
    },
    0x0,
};
#endif
#if defined(VERSION_EU_X)
NumericWidgetEventTable g_engDispatchNumericWidgetEventWords = {
    {
        { 0xe07, 30000, N64Eng_SetLinkedCommand100_EventHandlerAddress },
        { 0xf, 30000, N64Eng_SetLinkedCommand200_EventHandlerAddress },
        { 0x10, 30000, N64Eng_SetLinkedCommand100WithSound_EventHandlerAddress },
        { 0x8, 30000, N64Eng_HandleNumericIncrement_EventHandlerAddress },
        { 0x7, 30000, N64Eng_HandleNumericDecrement_EventHandlerAddress },
        { 0xe03, 30000, N64Eng_FreeNumericWidget_EventHandlerAddress },
        { 0xb, 30000, N64Eng_CancelSelectionRepeat_EventHandlerAddress },
        { 0xe08, 30000, TickSelectionRepeat_EventHandlerAddress },
        { 0x0, 0, 0 },
    },
    0x496e7669,
};
#endif
#if defined(VERSION_US)
NumericWidgetEventTable g_engDispatchNumericWidgetEventWords = {
    {
        { 0xe07, 30000, N64Eng_SetLinkedCommand100_EventHandlerAddress },
        { 0xf, 30000, N64Eng_SetLinkedCommand200_EventHandlerAddress },
        { 0x10, 30000, N64Eng_SetLinkedCommand100WithSound_EventHandlerAddress },
        { 0x8, 30000, N64Eng_HandleNumericIncrement_EventHandlerAddress },
        { 0x7, 30000, N64Eng_HandleNumericDecrement_EventHandlerAddress },
        { 0xe03, 30000, N64Eng_FreeNumericWidget_EventHandlerAddress },
        { 0xb, 30000, N64Eng_CancelSelectionRepeat_EventHandlerAddress },
        { 0xe08, 30000, TickSelectionRepeat_EventHandlerAddress },
        { 0x0, 0, 0 },
    },
    0x400,
};
#endif
#endif

#if defined(VERSION_US_REV1)
extern EventHandlerRecord g_numericWidgetEventIds_StorageWords[9];
#endif

#if defined(VERSION_DE)
FrontendRibbonResourceData g_frontendShutdownStateDe = {
    0, 0, 0, 1, 0, 1,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    {
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 1.5450846f, 4.7552824f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -4.04508448f, 2.93892598f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -4.04508448f, -2.93892598f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 1.5450846f, -4.7552824f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -0.0f, -0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, -0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 1.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, -1.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
    },
};
#endif

#if !(defined(VERSION_US_REV1))
char *k_FxSpawnimpactmarkData[6] = {
    g_ribbonBlendResources + 0xC, g_ribbonBlendResources + 0x34, g_ribbonBlendResources + 0x5C, g_ribbonBlendResources + 0xD4, g_ribbonBlendResources + 0x14C, g_ribbonBlendResources + 0x174,
};
#endif



unsigned int g_FxSpawnimpactmarkData[2] = {
    0x00000000, 0x00000000,
};

#if !(defined(VERSION_DE))
const char k_InitfrontendmenusData[23] =
    "..\\DATA\\TScredData.exp\000";
#endif

#if defined(VERSION_EU)
EngineRuntimeIoState g_xplusRandomStateBlockEu = {
    1, "\2775\004\363\000\000\000\000?5\004\363", 0, 0x12345678, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    { 0, 0, 0, 0, 0 }, "\000\000\000\000\000\000\000\000\000\000\000\000",
    0, { 0, 0 }, { 0.0f, 100000000.0f, -100000000.0f }, { 0.0f, 100000000.0f, -100000000.0f }, { 0.0f, 100000000.0f, -100000000.0f },
    0, 0, 480, 360
};
#endif
#if defined(VERSION_EU_X)
EngineRuntimeIoState g_xplusRandomStateBlockEuX = {
    1, "s\000\000\000Bullet r", 0, 0x12345678, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    { 0, 0, 0, 0, 0 }, " pack\000\000\000bull",
    0, { 0, 0 }, { 0.0f, 100000000.0f, -100000000.0f }, { 0.0f, 100000000.0f, -100000000.0f }, { 0.0f, 100000000.0f, -100000000.0f },
    0, 0, 480, 360
};
#endif

#if defined(VERSION_EU)
FrontendRibbonResourceData g_tsmosFloatWordTable = {
    0, 0, 0, 1, 0, 1,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    {
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 1.5450846f, 4.7552824f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -4.04508448f, 2.93892598f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -4.04508448f, -2.93892598f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 1.5450846f, -4.7552824f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -0.0f, -0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, -0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 1.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, -1.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
    },
};
#endif

#if defined(VERSION_EU_X)
FrontendRibbonResourceData g_tsmosUpdateFrontendWritable = {
    0, 0, 0, 1, 0, 1,
    { 0x61, 0x6D, 0x70, 0x69, 0x72, 0x65, 0x2E, 0x2E },
    {
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 1.5450846f, 4.7552824f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -4.04508448f, 2.93892598f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -4.04508448f, -2.93892598f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 1.5450846f, -4.7552824f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 5.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { -0.0f, -0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, -0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 1.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, -1.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
        { { 0.0f, 0.0f, 0.0f }, { 0x00000000, 0x00000000 } },
    },
};
#endif

#if defined(VERSION_US)
XPlusWritableWords_usLayout g_xPlusWritableWordsUs = {
    1,
    "ECOILT\000\000",
    0x04000000,
    0,
    0x12345678,
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    "MPACT_FLESHe\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    { 1e+08f, -1e+08f, 0.0f, 1e+08f, -1e+08f, 0.0f, 1e+08f, -1e+08f, 0.0f, 0.0f },
    { 480, 360 }
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
extern char g_N64engEncodedTextWords[12];
#endif

#if defined(VERSION_US_REV1)
extern char s_petrText[4];
#endif
