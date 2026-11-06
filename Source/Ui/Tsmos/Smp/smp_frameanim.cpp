#include "Common/resident_event_handler.h"
#include "Common/frustum.h"
#include "Common/animation.h"
#include "Common/menu_screen_elements.h"
#include "types.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Menu/smpframeanim_registerframeanimclass.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "include_asm.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Menu/smp_frameanim.h"
#include "Scene/cache_freememory.h"
#include "Menu/frame_sequence.h"
#include "Data/rest_source_records.h"
#include "Common/selectionscreenstate.h"
#include "Ui/ui_address_symbols.h"
#include "Frontend/node_insertwidgetbefore.h"
#include "Ui/Tsmos/Smp/smp_flicker.h"
#include "Menu/smp_slider.h"
#include "Ui/smp_updatefadeprogress.h"
#include "Frontend/frontend.h"

/* Advances a frame sequence after its duration expires, honoring pause, forward/reverse, ping-pong and finite/infinite loop modes, and publishes the selected frame to its target. Reuses the matched FrameSequence contract from SmpFrameAnim_HasSequenceFlags. */

/* Tests whether any of the given playback mode bits are set; SmpFrameAnim_UpdateFrameSequence asks it about bit 1
   (forward), 0x10 (ping-pong), 0x20 (counted loop) and 8 (loop) on every tick. */

s32 SmpFrameAnim_UpdateFrameSequence(struct FrameSequence *sequence, s32 eventId, s32 elapsed) {
    if (SmpFrameAnim_HasSequenceFlags(sequence, 4) == 0) {
        sequence->elapsed += elapsed;
        sequence->target->archiveHandle = sequence->frames[sequence->frame];
        if (sequence->elapsed > sequence->duration) {
            sequence->elapsed = 0;
            if (SmpFrameAnim_HasSequenceFlags(sequence, 1)) {
                if (sequence->frame < sequence->count - 1) {
                    sequence->frame++;
                } else if (SmpFrameAnim_HasSequenceFlags(sequence, 16)) {
                    SmpFrameAnim_ClearSequenceFlags(sequence, 1);
                    SmpFrameAnim_AddSequenceFlags(sequence, 2);
                    SmpFrameAnim_SetSequenceFrame(sequence, sequence->count - 2);
                } else if (SmpFrameAnim_HasSequenceFlags(sequence, 32)) {
                    if (sequence->loops > 0) {
                        sequence->loops--;
                        SmpFrameAnim_SetSequenceFrame(sequence, 0);
                    }
                } else if (SmpFrameAnim_HasSequenceFlags(sequence, 8)) {
                    SmpFrameAnim_SetSequenceFrame(sequence, 0);
                }
            } else {
                if (sequence->frame > 0) {
                    sequence->frame--;
                } else if (SmpFrameAnim_HasSequenceFlags(sequence, 16)) {
                    SmpFrameAnim_ClearSequenceFlags(sequence, 2);
                    SmpFrameAnim_AddSequenceFlags(sequence, 1);
                    SmpFrameAnim_SetSequenceFrame(sequence, 1);
                } else if (SmpFrameAnim_HasSequenceFlags(sequence, 32)) {
                    if (sequence->loops > 0) {
                        sequence->loops--;
                        SmpFrameAnim_SetSequenceFrame(sequence, sequence->count - 1);
                    }
                } else if (SmpFrameAnim_HasSequenceFlags(sequence, 8)) {
                    SmpFrameAnim_SetSequenceFrame(sequence, sequence->count - 1);
                }
            }
        }
    }
    return 0;
}

/* Creates a frame animation for widget id of the current screen: finds the widget through
   Node_FindWidgetByResourceId, allocates and clears a 0x64-byte animation, sets its type fields, widget and
   -1-terminated frame list, counts the frames, initialises its playback state through
   SmpFrameAnim_AddSequenceFlags, SmpFrameAnim_SetSequenceFrame, SmpFrameAnim_SetSequenceDuration and SmpFrameAnim_SetLoopCount, attaches it to the widget through
   Node_InsertWidgetBefore and returns it. */

void SmpFrameAnim_RegisterFrameAnimClass(void) {
    SmSmngr_RegisterElementHandlers(2911, g_SmpFrameAnim_DispatchEventAddress, g_SmpFrameAnim_IgnoreEventAddress, 3);
}

Animation *SmpFrameAnim_CreateFrameSequence(s32 id, s32 *frames) {
    s32 widget;
    Animation *anim;

    widget = (s32)Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), (u16)id);
    Node_GetScreenData(GetMenuScreenOwner());
    anim = Cache_AllocateMemory(100);
    XPlus_FillBytes(anim, 0, 100);
    anim->kindB = 2911;
    anim->flags = 8;
    anim->kindA = 2911;
    anim->widget = widget;
    anim->reservedWordA = 0;
    anim->frames = frames;
    anim->reservedWordB = 0;
    anim->count = 0;
    while (frames[anim->count] != -1) {
        anim->count++;
    }
    SmpFrameAnim_AddSequenceFlags(anim, 1);
    SmpFrameAnim_SetSequenceFrame(anim, 0);
    SmpFrameAnim_SetSequenceDuration(anim, 0);
    SmpFrameAnim_SetLoopCount(anim, 0);
    Node_InsertWidgetBefore(widget, anim);
    return anim;
}

/* Dispatches event eventId to the first row of this widget's event handler table whose event matches and whose actor kind
   equals the widget's actor kind or is ANY_ACTOR_KIND; returns that handler's result, or 0 when no row matches. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

/* SmpFrameAnim_UpdateFrameSequence advances a frame sequence: it adds elapsed time to the sequence timer and, once that
   exceeds the frame duration, moves the frame index through the -1 terminated frame array. SmpFrameAnim_CreateFrameSequence resets the index through here after counting the frames. */

void SmpFrameAnim_SetSequenceFrame(struct FrameSequence *sequence, s32 frame) {
    sequence->frame = frame;
}

/* Sets how long each frame of a sequence is shown; SmpFrameAnim_UpdateFrameSequence advances the frame once the
   accumulated time exceeds this. SmpFrameAnim_CreateFrameSequence clears it when it builds the sequence. */

void SmpFrameAnim_SetSequenceDuration(struct FrameSequence *sequence, s32 duration) {
    sequence->duration = duration;
}

/* Returns a frame sequence's current frame index, which SmpFrameAnim_SetSequenceFrame sets. */

s32 SmpFrameAnim_GetSequenceFrame(struct FrameSequence *sequence) {
    return sequence->frame;
}

/* Returns how many frames a sequence holds, counted by SmpFrameAnim_CreateFrameSequence up to the -1 terminator. */

s32 SmpFrameAnim_GetFrameCount(struct FrameSequence *sequence) {
    return sequence->count;
}

/* Sets how many more times a counted-loop sequence repeats; SmpFrameAnim_UpdateFrameSequence decrements it each
   time the sequence wraps and stops when it reaches zero. SmpFrameAnim_CreateFrameSequence clears it on creation. */

void SmpFrameAnim_SetLoopCount(struct FrameSequence *sequence, s32 loops) {
    sequence->loops = loops;
}

/* Returns how many more times a counted-loop sequence repeats, which SmpFrameAnim_SetLoopCount sets. */

s32 SmpFrameAnim_GetLoopCount(struct FrameSequence *sequence) {
    return sequence->loops;
}

/* Sets playback mode bits in a frame sequence; SmpFrameAnim_CreateFrameSequence sets bit 1 and SmpFrameAnim_UpdateFrameSequence sets
   bit 2 when it reverses a ping-pong sequence. */

void SmpFrameAnim_AddSequenceFlags(struct FrameSequence *sequence, s32 bits) {
    sequence->flags |= bits;
}

/* Clears playback mode bits in a frame sequence; SmpFrameAnim_AddSequenceFlags sets them and SmpFrameAnim_UpdateFrameSequence clears
   bit 1 or 2 when it reverses a ping-pong sequence. */

void SmpFrameAnim_ClearSequenceFlags(struct FrameSequence *sequence, s32 bits) {
    sequence->flags &= ~bits;
}

/* Tests whether any of the given playback mode bits are set; SmpFrameAnim_UpdateFrameSequence asks it about bit 1
   (forward), 0x10 (ping-pong), 0x20 (counted loop) and 8 (loop) on every tick. */

s32 SmpFrameAnim_HasSequenceFlags(struct FrameSequence *sequence, s32 bits) {
    return (sequence->flags & bits) != 0;
}

/* EU and EU-X lay this table out inside a larger record. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define FRAME_ANIM_EVENTS ((ResidentEventHandlerEntry *)&g_smpEventHandlerTables)
#else
#define FRAME_ANIM_EVENTS g_smpEventHandlerTables
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* EU walks the handler column and reads the event and actor-kind columns at the same row offset. */
s32 SmpFrameAnim_DispatchEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    ResidentEventHandler *handler;
    s32 offset;
    s32 wildcard;
    s32 actorKind;
    s32 tableKind;

    if (g_frameAnimationEventHandlers != 0) {
        wildcard = ANY_ACTOR_KIND;
        handler = &g_frameAnimationEventHandlers;
        offset = 0;
        do {
            if (*(s32 *)((char *)&FRAME_ANIM_EVENTS[0].event + offset) == eventId) {
                actorKind = ((struct MenuWidget *)widget)->resource;
                tableKind = *(s32 *)((char *)&FRAME_ANIM_EVENTS[0].actorKind + offset);
                if (tableKind == actorKind || tableKind == wildcard) {
                    return (*handler)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            handler = (ResidentEventHandler *)((char *)handler + sizeof(ResidentEventHandlerEntry));
            offset += sizeof(ResidentEventHandlerEntry);
        } while (*handler != 0);
    }
    return 0;
}
#else
s32 SmpFrameAnim_DispatchEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    s32 i;

    /* The table ends at the first entry without a handler. */
    for (i = 0; FRAME_ANIM_EVENTS[i].handler != 0; i++) {
        if (FRAME_ANIM_EVENTS[i].event == eventId) {
            s32 actorKind = ((struct MenuWidget *)widget)->resource;

            if (FRAME_ANIM_EVENTS[i].actorKind == actorKind || FRAME_ANIM_EVENTS[i].actorKind == ANY_ACTOR_KIND) {
                return FRAME_ANIM_EVENTS[i].handler(widget, eventId, eventData0, eventData1, eventData2);
            }
        }
    }
    return 0;
}
#endif

/* Does nothing: an unreferenced empty stub that ignores its arguments. */

void SmpFrameAnim_IgnoreEvent(s32 widget, struct Triple eventData) {
}

s32 SmpFrameAnim_DestroyController(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}

#if defined(VERSION_US_REV1)
SmpFrameControllerEventRecords g_smpFrameControllerEventRecords = {
    3587,
    30000,
    (unsigned int)&SmpFrameAnim_DestroyController,
    3592,
    30000,
    (unsigned int)&SmpFrameAnim_UpdateFrameSequence,
    { 0x00000000, 0x00000000, 0x00000000 },
};
SmpControllerEventRecordTails g_smpControllerEventRecordTails = {
    { 199, 179, 181, 3587, 30000 },
    (void *)&SmpFlicker_DestroyController,
    { 3592, 30000 },
    { (void *)&SmpFlicker_UpdateFlicker, 0, 0, 0 },
    { 154, 158, 159, 3587, 30000 },
    (void *)&SmpSlider_DestroyController,
    { 3592, 30000 },
    { (void *)&Smp_UpdateFadeProgress, 0, 0, 0, (void *)&g_selection_HandleCharacterVariantCycleEntry },
    { 3594, 7 }
};
#endif
