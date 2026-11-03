#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/RECORD.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "UI/QUAG/N64_ENG.H"
#include "UI/QUAG/N64_ENG.H"
#include "COMMON/STATEPAIR.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "include_asm.h"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"

extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *draw, struct CacheResourceBlockView *hit, struct WidgetLayout *widget, struct t_dldc *ctx);





extern void Widget_DrawVisibleSiblings(void *, Args);

s32 N64Eng_DispatchNumericWidgetEvent(struct Tree *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_numericWidgetEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_numericWidgetEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_numericWidgetEventIds)) + offset))->value == eventId) {
                actor_kind = eventTarget->id;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_numericWidgetEventActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(eventTarget, eventId, eventCode, eventValue, repeatCount);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}

void N64Eng_DrawNumericWidgetChildren(void *widget, Args args) {
    QuadN64EngDrawNumericWidgetChildren first;
    QuadN64EngDrawNumericWidgetChildren basis;
    QuadN64EngDrawNumericWidgetChildren value;
    QuadN64EngDrawNumericWidgetChildren transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((((Widget *)widget)->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.x, &value.z, &value.y, &value.w);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.x, transformed.z,
                          transformed.y, transformed.w);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(((struct Tree *)widget)->child, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.x, value.z, value.y, value.w);
        }
    }
}

extern void N64Eng_SetNumericWidgetValue(struct RecordN64EngCreateNumericWidget *widget, s32 value);

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

extern unsigned int Smos_GetControlRepeatLimit(void);

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

s32 N64Eng_HandleNumericIncrement(void *widgetStorage, s32 unused1, s32 unused2, s32 eventValue, s32 fifth) {
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

s32 N64Eng_HandleNumericDecrement(void *widgetStorage, s32 unused1, s32 unused2, s32 eventValue, s32 fifth) {
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
int N64Eng_CancelSelectionRepeat(void *object, int unused, unsigned int event, int subcode) {
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

