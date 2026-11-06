#include "Menu/smp_records.h"
#include "Common/resident_event_handler.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "include_asm.h"
#include "Common/frustum.h"
#include "Common/animation.h"
#include "Menu/smp_records.h"
#include "Common/menu_screen_elements.h"
#include <platform_sdk.h>
#include "types.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Ui/Tsmos/Smp/smp_flicker.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Scene/cache_freememory.h"

#if defined(VERSION_US)
#include "Common/animation.h"
#include "types.h"
#include "Render/soundelement_playflatsound.h"
/* Per-frame step of a menu widget flicker: while the effect is armed the timer counts down to 0 (capped at 50); at 0 a roll below 2 in 100
   starts the flicker (flag set, current entry shown on the widget, flicker sound). While flickering each frame spends one hold count of the current
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
#include "Common/animation.h"
#include "Common/menu_screen_elements.h"
#include "types.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Ui/Tsmos/Smp/smp_flicker.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "types.h"
#include "Render/soundelement_playflatsound.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Frontend/node_insertwidgetbefore.h"
/* Per-frame step of a menu widget flicker: while the effect is armed the timer counts down to 0 (capped at 50); at 0 a roll below 2 in 100
   starts the flicker (flag set, current entry shown on the widget, flicker sound). While flickering each frame spends one hold count of the current
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
#include "Common/animation.h"
#include "Render/soundelement_playflatsound.h"
/* Per-frame step of a menu widget flicker: while the effect is armed the timer counts down to 0 (capped at 50); at 0 a roll below 2 in 100
   starts the flicker (flag set, current entry shown on the widget, flicker sound). While flickering each frame spends one hold count of the current
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
#include "Render/soundelement_playflatsound.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Common/selectionscreenstate.h"
#include "Frontend/frontend.h"
/* Per-frame step of a menu widget flicker: while the effect is armed the timer counts down to 0 (capped at 50); at 0 a roll below 2 in 100
   starts the flicker (flag set, current entry shown on the widget, flicker sound). While flickering each frame spends one hold count of the current
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
  ResourceSmpFlickerCreateFlickerWidget *resourceWidget;
  MenuResourceWidget *flickerWidget;
  int kind;
  resourceWidget = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), widgetResourceId & 65535);
  Node_GetScreenData(GetMenuScreenOwner());
  flickerWidget = Cache_AllocateMemory(136);
  XPlus_FillBytes(flickerWidget, 0, 136);
  flickerWidget->b = (kind = 2914);
  flickerWidget->resource = resourceWidget;
  flickerWidget->owner.value = ownerValue;
  flickerWidget->c = 8;
  flickerWidget->a = kind;
  /* The low byte of the big-endian owner word is its last byte. */
  flickerWidget->resource->value = flickerWidget->owner.bytes[3];
  SmpFlicker_InitFlicker(flickerWidget, -1);
  SmpFlicker_EnableFlicker(flickerWidget);
  Node_InsertWidgetBefore(resourceWidget, flickerWidget);
  return flickerWidget;
}

/* Calls SmpFlicker_InitFlicker on an object, marks it busy and copies the low byte of the
   current entry of its value array, selected by the current index, into the value of the
   linked object. */

/* Dispatches event eventId to the first row of this widget's event handler table whose event matches and whose actor kind
   equals the widget's actor kind or is ANY_ACTOR_KIND; returns that handler's result, or 0 when no row matches. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

/* Marks the flicker as pending. */

void SmpFlicker_EnableFlicker(struct StateBlock *object) {
    object->flickerPending = 1;
}

/* Copies the saved flicker value into the target widget and clears the pending flag
   that SmpFlicker_EnableFlicker sets and SmpFlicker_IsFlickerIdle tests. */

void SmpFlicker_RestoreFlickerValue(struct FlickerRestoreView *source) {
    struct ResourceSmpFlickerCreateFlickerWidget *target = source->target;
    u8 value = source->value;

    source->pending = 0;
    target->value = value;
}

/* Returns one when nothing is pending, and otherwise whether the busy word
   is zero; SmpFlicker_EnableFlicker sets the pending word and SmpFlicker_RestoreFlickerValue clears it. */

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
    s32 i;

    /* The table ends at the first entry without a handler. */
    for (i = 0; g_flickerWidgetEventIds[i].handler != 0; i++) {
        if (g_flickerWidgetEventIds[i].event == eventId) {
            s32 actorKind = ((struct MenuWidget *)widget)->resource;

            if (g_flickerWidgetEventIds[i].actorKind == actorKind || g_flickerWidgetEventIds[i].actorKind == ANY_ACTOR_KIND) {
                return g_flickerWidgetEventIds[i].handler(widget, eventId, eventData0, eventData1, eventData2);
            }
        }
    }
    return 0;
}

/* Does nothing: an unreferenced empty stub that ignores its arguments. */

void SmpFlicker_IgnoreEvent(s32 widget, struct Triple eventData) {
}

s32 SmpFlicker_DestroyController(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}
