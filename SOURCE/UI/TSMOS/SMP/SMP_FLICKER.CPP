#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "include_asm.h"
#include "COMMON/FRUSTUM.H"
#include "COMMON/ANIMATION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/INTEGERSTATE530.H"
#include <ultra64.h>
#include "TYPES.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "UI/TSMOS/SMP/SMP_FLICKER.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "SCENE/CACHE_FREEMEMORY.H"

#if defined(VERSION_US)
#include "COMMON/ANIMATION.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
/* Per-frame step of a menu widget flicker: while the effect is armed (state 1) the timer counts down to 0 (capped at 50); at 0 a roll below 2 in 100
   starts the flicker (flag set, current entry shown on the widget, sound 0xE75). While flickering each frame spends one hold count of the current
   entry and moves on to the next entry; after the last one the effect is re-rolled and the timer rewinds to 50. Returns 0. */
s32 SmpFlicker_UpdateFlicker(FlickerUpdateState *flicker) {
 s32 entry,timer,next;
 FlickerUpdateState *widgetOwner = flicker;
 if(flicker->armed==1) {
  if(flicker->flickering==0) {
   timer=flicker->timer-1<0?0:flicker->timer-1>50?50:flicker->timer-1;
   widgetOwner->timer=timer;
   if(timer<=0 && Graphu64_NextRandom()%100<2) {
    widgetOwner->flickering=1;
    widgetOwner->target->value=widgetOwner->entryValues[widgetOwner->entryIndex];
    SoundElement_PlayFlatSound(3701);
   }
  } else {
   flicker->target->value=flicker->restoreValue;
   flicker->entryHoldCounts[flicker->entryIndex]--;
   entry=flicker->entryIndex;
   if(flicker->entryHoldCounts[entry]<=0 || entry+1>=flicker->entryCount) {
    next=entry+1; flicker->entryIndex=next;
    if(flicker->entryCount<=next) {
     SmpFlicker_InitFlicker(flicker,-1);
     flicker->target->value=flicker->restoreValue;
     flicker->timer=50;
    } else {
     widgetOwner->target->value=widgetOwner->entryValues[next];
     SoundElement_PlayFlatSound(3701);
    }
   }
  }
 }
 return 0;
}
#endif

#if defined(VERSION_EU)
#include "COMMON/ANIMATION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/INTEGERSTATE530.H"
#include "TYPES.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "UI/TSMOS/SMP/SMP_FLICKER.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "RESMGR/resmgr_string_memory.H"
/* Per-frame step of a menu widget flicker: while the effect is armed (state 1) the timer counts down to 0 (capped at 50); at 0 a roll below 2 in 100
   starts the flicker (flag set, current entry shown on the widget, sound 0xE75). While flickering each frame spends one hold count of the current
   entry and moves on to the next entry; after the last one the effect is re-rolled and the timer rewinds to 50. Returns 0. */
s32 SmpFlicker_UpdateFlicker(FlickerUpdateState *flicker) {
 s32 entry,timer,next;
 FlickerUpdateState *widgetOwner = flicker;
 if(flicker->armed==1) {
  if(flicker->flickering==0) {
   timer=flicker->timer-1<0?0:flicker->timer-1>50?50:flicker->timer-1;
   widgetOwner->timer=timer;
   if(timer<=0 && Graphu64_NextRandom()%100<2) {
    widgetOwner->flickering=1;
    widgetOwner->target->value=widgetOwner->entryValues[widgetOwner->entryIndex];
    SoundElement_PlayFlatSound(3701);
   }
  } else {
   flicker->target->value=flicker->restoreValue;
   flicker->entryHoldCounts[flicker->entryIndex]--;
   entry=flicker->entryIndex;
   if(flicker->entryHoldCounts[entry]<=0 || entry+1>=flicker->entryCount) {
    next=entry+1; flicker->entryIndex=next;
    if(flicker->entryCount<=next) {
     SmpFlicker_InitFlicker(flicker,-1);
     flicker->target->value=flicker->restoreValue;
     flicker->timer=50;
    } else {
     widgetOwner->target->value=widgetOwner->entryValues[next];
     SoundElement_PlayFlatSound(3701);
    }
   }
  }
 }
 return 0;
}
#endif

#if defined(VERSION_DE)
#include "COMMON/ANIMATION.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
/* Per-frame step of a menu widget flicker: while the effect is armed (state 1) the timer counts down to 0 (capped at 50); at 0 a roll below 2 in 100
   starts the flicker (flag set, current entry shown on the widget, sound 0xE75). While flickering each frame spends one hold count of the current
   entry and moves on to the next entry; after the last one the effect is re-rolled and the timer rewinds to 50. Returns 0. */
s32 SmpFlicker_UpdateFlicker(FlickerUpdateState *flicker) {
 s32 entry,timer,next;
 FlickerUpdateState *widgetOwner = flicker;
 if(flicker->armed==1) {
  if(flicker->flickering==0) {
   timer=flicker->timer-1<0?0:flicker->timer-1>50?50:flicker->timer-1;
   widgetOwner->timer=timer;
   if(timer<=0 && Graphu64_NextRandom()%100<2) {
    widgetOwner->flickering=1;
    widgetOwner->target->value=widgetOwner->entryValues[widgetOwner->entryIndex];
    SoundElement_PlayFlatSound(3701);
   }
  } else {
   flicker->target->value=flicker->restoreValue;
   flicker->entryHoldCounts[flicker->entryIndex]--;
   entry=flicker->entryIndex;
   if(flicker->entryHoldCounts[entry]<=0 || entry+1>=flicker->entryCount) {
    next=entry+1; flicker->entryIndex=next;
    if(flicker->entryCount<=next) {
     SmpFlicker_InitFlicker(flicker,-1);
     flicker->target->value=flicker->restoreValue;
     flicker->timer=50;
    } else {
     widgetOwner->target->value=widgetOwner->entryValues[next];
     SoundElement_PlayFlatSound(3701);
    }
   }
  }
 }
 return 0;
}
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "RESMGR/resmgr_string_memory.H"
/* Per-frame step of a menu widget flicker: while the effect is armed (state 1) the timer counts down to 0 (capped at 50); at 0 a roll below 2 in 100
   starts the flicker (flag set, current entry shown on the widget, sound 0xE75). While flickering each frame spends one hold count of the current
   entry and moves on to the next entry; after the last one the effect is re-rolled and the timer rewinds to 50. Returns 0. */
s32 SmpFlicker_UpdateFlicker(FlickerUpdateState *flicker) {
 s32 entry,timer,next;
 FlickerUpdateState *widgetOwner = flicker;
 if(flicker->armed==1) {
  if(flicker->flickering==0) {
   timer=flicker->timer-1<0?0:flicker->timer-1>50?50:flicker->timer-1;
   widgetOwner->timer=timer;
   if(timer<=0 && Graphu64_NextRandom()%100<2) {
    widgetOwner->flickering=1;
    widgetOwner->target->value=widgetOwner->entryValues[widgetOwner->entryIndex];
    SoundElement_PlayFlatSound(3701);
   }
  } else {
   flicker->target->value=flicker->restoreValue;
   flicker->entryHoldCounts[flicker->entryIndex]--;
   entry=flicker->entryIndex;
   if(flicker->entryHoldCounts[entry]<=0 || entry+1>=flicker->entryCount) {
    next=entry+1; flicker->entryIndex=next;
    if(flicker->entryCount<=next) {
     SmpFlicker_InitFlicker(flicker,-1);
     flicker->target->value=flicker->restoreValue;
     flicker->timer=50;
    } else {
     widgetOwner->target->value=widgetOwner->entryValues[next];
     SoundElement_PlayFlatSound(3701);
    }
   }
  }
 }
 return 0;
}
#endif

s32 Graphu64_NextRandom(void);

/* Allocates and initializes an object, attaches its resource and owner value, then registers it with the resource. */



extern struct Record *Cache_AllocateMemory(s32 size);




extern void Node_InsertWidgetBefore(struct Tree *node, struct Tree *added);


void SmpFlicker_InitFlicker(FlickerUpdateState *flicker, s32 sampleCount);

void SmpFlicker_EnableFlicker(struct StateBlock *object);

/* Initializes a flicker effect and randomizes each element's intensity. */
void SmpFlicker_InitFlicker(FlickerUpdateState *flicker, s32 sampleCount) {
    s32 i;
    s32 sampleValue;
    s32 offset;
    int randomValueDrop;
    flicker->flickering = 0;
    flicker->entryIndex = 0;
    if (sampleCount > 0) {
        flicker->entryCount = sampleCount;
    } else {
        flicker->entryCount = (s32) (Graphu64_NextRandom() % 5 + 1);
    }
    for (i = 0; i < flicker->entryCount; i++) {
        flicker->entryHoldCounts[i] = (s32) (Graphu64_NextRandom() % 3 + 1);
        sampleValue = (offset = Graphu64_NextRandom() % 40 + 30, flicker->restoreValue - offset) < 0 ? 0 : ((offset = Graphu64_NextRandom() % 40 + 30, flicker->restoreValue - offset) >= 256 ? 0xFF : (offset = randomValueDrop = Graphu64_NextRandom() % 40 + 30, flicker->restoreValue - offset));
        flicker->entryValues[i] = sampleValue;
    }
}

void SmpFlicker_RegisterFlickerClass(void) {
    SmSmngr_RegisterElementHandlers(2914, g_SmpFlicker_DispatchEventAddress, g_SmpFlicker_IgnoreEventAddress, 3);
}

MenuResourceWidget *SmpFlicker_CreateFlickerWidget(s32 widgetResourceId, s32 ownerValue)
{
  ResourceSmpFlickerCreateFlickerWidget *r;
  MenuResourceWidget *p;
  int kind;
  r = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), widgetResourceId & 65535);
  Node_GetScreenData(GetMenuScreenOwner());
  p = Cache_AllocateMemory(136);
  XPlus_FillBytes(p, 0, 136);
  p->b = (kind = 2914);
  p->resource = r;
  p->owner.value = ownerValue;
  p->c = 8;
  p->a = kind;
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  /* The low byte of the owner word sits at its address on a little-endian host, not 3 bytes in. */
  p->resource->value = p->owner.bytes[0];
#else
  p->resource->value = p->owner.bytes[3];
#endif
  SmpFlicker_InitFlicker(p, -1);
  SmpFlicker_EnableFlicker(p);
  Node_InsertWidgetBefore(r, p);
  return p;
}

/* Calls SmpFlicker_InitFlicker_SmpFlicker on an object, marks it busy at offset 0x44 and copies the low byte of the
   current entry of the word array at 0x4C, selected by the index at 0x74, into offset 0x10 of the
   object at 0x78. */





/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_flickerWidgetEventIds, an actor kind at g_flickerWidgetEventActorKinds and a handler at g_flickerWidgetEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */






/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

/* Sets the word at offset 0x84 of an object to one. */


void SmpFlicker_EnableFlicker(struct StateBlock *object) {
    object->flickerPending = 1;
}

/* Copies the byte at offset 0x83 of an object into offset 0x10 of the object at 0x78, and clears
   the pending word at 0x84 that SmpFlicker_EnableFlicker sets and SmpFlicker_IsFlickerIdle tests. */




void SmpFlicker_RestoreFlickerValue(struct FlickerRestoreView *source) {
    struct ResourceSmpFlickerCreateFlickerWidget *target = source->target;
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    /* value is the low byte of the word at 0x80, which a little-endian host holds at 0x80. */
    u8 value = *((u8 *) source + 0x80);
#else
    u8 value = source->value;
#endif

    source->pending = 0;
    target->value = value;
}

/* Returns one when nothing is pending at offset 0x84 of an object, and otherwise whether the word
   at offset 0x44 is zero; SmpFlicker_EnableFlicker sets the pending word and SmpFlicker_RestoreFlickerValue clears it. */


s32 SmpFlicker_IsFlickerIdle(struct FlickerActivityView *object) {
    if (object->pending == 0) {
        return 1;
    }
    return object->busy == 0;
}

void SmpFlicker_StartFlicker(struct FlickerStartView *object, s32 count) {
    SmpFlicker_InitFlicker(object, count);
    object->busy = 1;
    object->target->value = object->entries[object->index];
}

s32 SmpFlicker_DispatchEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_flickerWidgetEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_flickerWidgetEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_flickerWidgetEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_flickerWidgetEventActorKinds)) + offset))->value;
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

/* Does nothing: an unreferenced empty stub whose only code stores the argument registers a1 to a3
   to their home stack slots. */


void SmpFlicker_IgnoreEvent(s32 unused0, struct Triple unused1) {
}

s32 SmpFlicker_DestroyController(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}
