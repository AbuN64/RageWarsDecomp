#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/FRUSTUM.H"
#include "COMMON/ANIMATION.H"
#include "COMMON/INTEGERSTATE530.H"
#include "TYPES.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "MENU/SMPFRAMEANIM_REGISTERFRAMEANIMCLASS.H"
#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "MENU/SMP_FRAMEANIM.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "MENU/FRAME_SEQUENCE.H"
#include "DATA/REST_SOURCE_RECORDS.H"

/* SMP_FRAMEANIM.CPP */
/* Advances a frame sequence after its duration expires, honoring pause, forward/reverse, ping-pong and finite/infinite loop modes, and publishes the selected frame to its target. Reuses the matched FrameSequence contract from SmpFrameAnim_HasSequenceFlags. */

/* Tests whether any of the given playback mode bits are set; SmpFrameAnim_UpdateFrameSequence_SmpFrameanim asks it about bit 1
   (forward), 0x10 (ping-pong), 0x20 (counted loop) and 8 (loop) on every tick. */

s32 SmpFrameAnim_UpdateFrameSequence(struct FrameSequence *sequence, s32 unused, s32 elapsed) {
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

extern struct Record *Cache_AllocateMemory(s32 size);

extern void Node_InsertWidgetBefore(struct Tree *node, struct Tree *added);

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

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_smpEventHandlerTables, an actor kind at g_frameAnimationEventActorKinds and a handler at g_frameAnimationEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

/* SmpFrameAnim_UpdateFrameSequence_SmpFrameanim advances a frame sequence: it adds elapsed time into offset 0x54 and, once that
   exceeds the duration at 0x58, moves the frame index at 0x4C through the -1 terminated array at
   0x48. SmpFrameAnim_CreateFrameSequence resets the index through here after counting the frames. */

void SmpFrameAnim_SetSequenceFrame(struct FrameSequence *sequence, s32 frame) {
    sequence->frame = frame;
}

/* Sets how long each frame of a sequence is shown; SmpFrameAnim_UpdateFrameSequence_SmpFrameanim advances the frame once the
   time accumulated at 0x54 exceeds this. SmpFrameAnim_CreateFrameSequence clears it when it builds the sequence. */

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

/* Sets how many more times a counted-loop sequence repeats; SmpFrameAnim_UpdateFrameSequence_SmpFrameanim decrements it each
   time the sequence wraps and stops when it reaches zero. SmpFrameAnim_CreateFrameSequence clears it on creation. */

void SmpFrameAnim_SetLoopCount(struct FrameSequence *sequence, s32 loops) {
    sequence->loops = loops;
}

/* Returns how many more times a counted-loop sequence repeats, which SmpFrameAnim_SetLoopCount sets. */

s32 SmpFrameAnim_GetLoopCount(struct FrameSequence *sequence) {
    return sequence->loops;
}

/* Sets playback mode bits in a frame sequence; SmpFrameAnim_CreateFrameSequence sets bit 1 and SmpFrameAnim_UpdateFrameSequence_SmpFrameanim sets
   bit 2 when it reverses a ping-pong sequence. */

void SmpFrameAnim_AddSequenceFlags(struct FrameSequence *sequence, s32 bits) {
    sequence->flags |= bits;
}

/* Clears playback mode bits in a frame sequence; SmpFrameAnim_AddSequenceFlags sets them and SmpFrameAnim_UpdateFrameSequence_SmpFrameanim clears
   bit 1 or 2 when it reverses a ping-pong sequence. */

void SmpFrameAnim_ClearSequenceFlags(struct FrameSequence *sequence, s32 bits) {
    sequence->flags &= ~bits;
}

/* Tests whether any of the given playback mode bits are set; SmpFrameAnim_UpdateFrameSequence_SmpFrameanim asks it about bit 1
   (forward), 0x10 (ping-pong), 0x20 (counted loop) and 8 (loop) on every tick. */

s32 SmpFrameAnim_HasSequenceFlags(struct FrameSequence *sequence, s32 bits) {
    return (sequence->flags & bits) != 0;
}

s32 SmpFrameAnim_DispatchEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_frameAnimationEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_frameAnimationEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_smpEventHandlerTables)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_frameAnimationEventActorKinds)) + offset))->value;
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

void SmpFrameAnim_IgnoreEvent(s32 unused0, struct Triple unused1) {
}

s32 SmpFrameAnim_DestroyController(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}

/* SMP_CONTROLLER_EVENTS.CPP */
extern char addrLow_SmpFlicker_DestroyController[];
extern char addrLow_SmpFlicker_UpdateFlicker[];
extern char addrLow_SmpSlider_DestroyController[];
extern char addrLow_Smp_UpdateFadeProgress[];
extern char g_selection_HandleCharacterVariantCycleEntry[];
#if defined(VERSION_US_REV1)
/* 800E3300.CPP */
extern char addrLow_SmpFrameAnim_UpdateFrameSequence[];
extern char addrLow_SmpFrameAnim_DestroyController[];
RestsmpFrameControllerEventRecordsUsRev1Record877 g_smpFrameControllerEventRecordsUsRev1 = {
    3587,
    30000,
    (unsigned int)addrLow_SmpFrameAnim_DestroyController,
    3592,
    30000,
    (unsigned int)addrLow_SmpFrameAnim_UpdateFrameSequence,
    { 0x00000000, 0x00000000, 0x00000000 },
};
/* 800E3324.CPP */
extern char addrLow_SmpFlicker_UpdateFlicker[];
extern char addrLow_SmpFlicker_DestroyController[];
extern char addrLow_Smp_UpdateFadeProgress[];
extern char addrLow_SmpSlider_DestroyController[];
extern char g_selection_HandleCharacterVariantCycleEntry[];
RestsmpControllerEventRecordTailsUsRev1Layout878 g_smpControllerEventRecordTailsUsRev1 = {
    { 199, 179, 181, 3587, 30000 },
    (void *)&addrLow_SmpFlicker_DestroyController,
    { 3592, 30000 },
    { (void *)&addrLow_SmpFlicker_UpdateFlicker, 0, 0, 0 },
    { 154, 158, 159, 3587, 30000 },
    (void *)&addrLow_SmpSlider_DestroyController,
    { 3592, 30000 },
    { (void *)&addrLow_Smp_UpdateFadeProgress, 0, 0, 0, (void *)&g_selection_HandleCharacterVariantCycleEntry },
    { 3594, 7 },
};
#endif
