#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJRECAT4V6.H"
#include "AUDIO/VOICE_AND_SPATIAL_SOURCE_VIEWS.H"
#include "COMMON/ALBANK_S.H"
#include "TYPES.H"
#include "AUDIO/EXTERNS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* Updates a playing view each frame: records the result of Gsky_FindNearestCamera_ChannelStartnotevoice for its position in the context, selects its channel and checks whether it still plays; a view past its end, finished once, or whose track changed is marked done, and a done view that still plays is stopped once per frame and loses its handle; a stopped view first waits out its hold count, then is released with its slot and state cleared unless it is fading, while a playing view copies its tracked position and runs its three per-frame updates. The first channel selection matches as an inline helper returning the channel. */









#include "COMMON/MENU_MATCH_GLOBALS.H"
ALSndPlayer;
#include "TEXTURE/SOUND_UPDATEAUDIOCONTEXT.H"
#include "COMMON/LISTNODE.H"


extern s32 Gsky_FindNearestCamera(MenuMatchGlobals *, Triple *);


extern void Channel_UpdateVoiceVolume(ViewChannelUpdateVoicePlayback *);
extern void Channel_UpdateVoicePan(ViewChannelUpdateVoicePlayback *);
extern void Channel_UpdateVoicePitch(ViewChannelUpdateVoicePlayback *);




static inline char *selectChannel(AudioVoiceContextView *context, s32 slot) {
    alSndpSetSound(((AudioOwnerView *)context)->sound, context->slots.ids[slot]);
    return ((AudioOwnerView *)context)->sound;
}

void Channel_UpdateVoicePlayback(ViewChannelUpdateVoicePlayback *view) {
    char *channel;
    AudioVoiceContextView *context;
    Slots *slots;
    s32 playing;

    view->context->result = Gsky_FindNearestCamera(&g_frontendScreenStatus, &view->position);
    playing = alSndpGetState(selectChannel(view->context, view->slot));
    if (view->time <= g_voicePlaybackTimeThreshold || ((view->flags & 4) && view->finished == 0)) {
        view->done = 1;
    }
    if (view->followTrack != 0 && view->context->track != view->trackId) {
        view->done = 1;
    }
    if (playing != 0) {
        if (view->done != 0) {
            view->done = 1;
            view->tracked = 0;
            context = view->context;
            if (view->frame != context->frame) {
                channel = ((AudioOwnerView *)context)->sound;
                alSndpSetSound(channel, context->slots.ids[view->slot]);
                if (alSndpGetState(channel) != 0) {
                    alSndpStop(channel);
                }
                view->handle = -1;
            }
            return;
        }
    } else if (view->hold > 0) {
        view->hold--;
        view->flags |= 0x10;
        return;
    }
    if ((view->flags & 0x18) == 0x10) {
        alSndpPlay(((AudioOwnerView *)view->context)->sound);
        return;
    }
    if (playing == 0) {
        context = view->context;
        slots = &context->slots;
        alSndpDeallocate(((AudioOwnerView *)context)->sound, slots->ids[view->slot]);
        slots->ids[view->slot] = -1;
        view->reserved38 = 0;
        view->reservedC = -1;
        view->reserved8 = -1;
        view->trackId = -1;
        view->reserved3A = -1;
        view->reservedB4 = -1;
        return;
    }
    if (view->tracked != 0) {
        view->position = *view->tracked;
    }
    Channel_UpdateVoiceVolume(view);
    Channel_UpdateVoicePan(view);
    Channel_UpdateVoicePitch(view);
}

/* Picks the voice slot for a new sound of the given priority: the first of the sixteen slots with no sound, else the
 * lowest-priority voice below the new priority (priority 100 voices are never taken). A taken voice is released and the
 * call returns 16 (the spare voice) when that one is free, else -1. -1 also when no voice is low enough. */
s16 Channel_SelectVoiceSlot(RecordD90 *record, s32 variant, s32 count, s16 priority, s32 unused) {
    AudioVoiceContextView *context;
    Slots *slots;
    SlotCC *voice;
    VoiceQueueNode *waiting;
    s32 voicePriority;
    s32 best;
    s32 selected;
    s32 i;

    context = (AudioVoiceContextView *)record->header;
    slots = &context->slots;
    best = priority;
    selected = -1;
    voice = record->slots;
    for (i = 0; i < 16; i++) {
        if (slots->ids[i] == -1) {
            return i;
        }
        voicePriority = voice->priority;
        if (voicePriority < priority && best >= voicePriority && voicePriority != 100) {
            best = voicePriority;
            selected = i;
        }
        voice++;
    }
    if (selected == -1) {
        return -1;
    }
    if (slots->ids[selected] == -1) {
        waiting = context->queue.next;
        if (waiting != &context->queue && waiting->priority > priority) {
            return -1;
        }
        return selected;
    }
    release(&record->slots[(s16)selected]);
    if (record->slots[16].serial != -1) {
        return -1;
    }
    return 16;
}


typedef struct SoundBankState {
    ALBank *bank;
    char pad4[4];
    char pool[88];
    s16 slots[16];
    u16 allocated;
    char pad82[4];
    s16 current;
} SoundBankState;
typedef struct SoundEngine {
    char pad0[0x7C];
    SoundBankState state;
    s32 effect;
    s32 serial;
    char pad10C[0x2B8C - 0x10C];
    s16 priorityTable;
    char pad2B8E[2];
    s32 f2B90;
    char pad2B94[0x2BAC - 0x2B94];
    s32 f2BAC;
    char pad2BB0[0x2BBC - 0x2BB0];
    f32 f2BBC;
} SoundEngine;
typedef struct SoundVoiceParameters {
    s32 effect;
    char pad4[4];
    s32 reach;
    s32 reachCopy;
    s16 pitchOffset;
    char pad12[2];
    s32 zero24;
    s16 pan;
    char pad1A[0xA];
    f32 gain;
    s16 priority;
    s16 note;
    s16 variant;
    char pad2E[0x12];
    s32 zero50;
    u8 mode;
} SoundVoiceParameters;
typedef struct SoundVoice {
    char pad0[4];
    s32 userData;
    s32 slot;
    s32 serial;
    SoundVoiceParameters parameters;
    char pad58[0x48];
    s32 noteLength;
    s32 noteWord;
    s32 f_A8;
    s32 zeroAC;
    char padB0[4];
    s32 f_B4;
    f32 f_B8;
    s32 flagBC;
    s32 f_C0;
    s32 flagC4;
    char padC8[4];
} SoundVoice;
typedef struct SoundPlayer {
    SoundEngine *engine;
    SoundVoice voices[1];
} SoundPlayer;
extern s32 g_noteVoicePrimaryKeyTable[];
extern s32 g_noteVoiceSecondaryKeyTable[];
extern s32 SoundInfo_GetPriority(void *);
extern s32 SoundInfo_GetMode(void *);
extern s32 SoundInfo_GetPan(void *);
extern s32 SoundInfo_GetFlags(void *);

/* Starts a note on a free voice: picks the voice with Channel_SelectVoiceSlot, asks the sound set for its sample, and
 * fills in the voice record (volume, pan, pitch, which categories its effect belongs to). Returns the voice, or
 * 0 when the note's set is too small, the chance roll fails, or no voice or sample is available. */
SoundVoice *Channel_StartNoteVoice(SoundPlayer *player, SoundDescriptor *note, s32 variant, s32 userData) {
    SoundEngine *engine;
    SoundVoice *voice;
    s16 *slots;
    s16 index;
    s16 slot;
    s16 priority;
    s32 count;
    s32 roll;
    s32 i;
    f32 pitch;
    u32 pitchByte;
    s8 notePitch;
    SoundBankState *state;
    SoundVoiceParameters *parameters;
    char *pool;

    count = SoundInfo_GetGroup(note);
    priority = (s8)SoundInfo_GetPriority(note);
    engine = player->engine;
    slots = engine->state.slots;
    if (player->engine->state.bank->instArray[0]->soundCount < count) {
        return 0;
    }
    Sound_AcquireContextLock((s32 *)engine);
    if ((s8)SoundInfo_GetMode(note) != 100) {
        roll = Graphu64_NextRandomValue();
        roll %= 100;
        roll = roll < (s8)SoundInfo_GetMode(note);
        if (!roll) {
            goto fail;
        }
    }
    index = Channel_SelectVoiceSlot((RecordD90 *)player, (s16)variant, count, priority, (s16)SoundInfo_GetFlags(note));
    if (index == -1) {
        goto fail;
    }
    voice = &player->voices[index];
    if (index == 16) {
        voice->userData = userData;
        voice->serial = player->engine->serial++;
        voice->slot = 99;
    } else {
        player->engine->state.current = index;
        state = &player->engine->state;
        pool = state->pool;
        slot = alSndpAllocate(pool, (s32)state->bank->instArray[0]->soundArray[count]);
        slots[index] = slot;
        if (slot == -1) {
            voice->serial = -1;
            voice->slot = -1;
            voice->parameters.priority = 0;
            player->engine->state.current = -1;
fail:
            Sound_ReleaseContextLock((s32 *)player->engine);
            return 0;
        }
        pitch = (f32)priority * 1.27f;
        state->allocated++;
        voice->userData = userData;
        voice->serial = player->engine->serial++;
        voice->slot = slots[index];
        voice->noteLength = note->sample;
        pitchByte = (u32)pitch;
        alSndpSetPriority(pool, slots[index], pitchByte & 0xFF);
    }
    voice->f_A8 = player->engine->priorityTable;
    voice->f_C0 = player->engine->f2BAC;
    voice->flagBC = 0;
    for (i = 0; i < 4; i++) {
        if (voice->f_A8 == g_noteVoicePrimaryKeyTable[i]) {
            voice->flagBC = 1;
            break;
        }
    }
    voice->flagC4 = 1;
    for (i = 0; i < 6; i++) {
        if (voice->f_A8 == g_noteVoiceSecondaryKeyTable[i]) {
            voice->flagC4 = 0;
            break;
        }
    }
    voice->f_B4 = player->engine->f2B90;
    voice->zeroAC = 0;
    voice->f_B8 = player->engine->f2BBC;
    parameters = &voice->parameters;
    parameters->priority = priority;
    parameters->reachCopy = 32000;
    parameters->reach = 32000;
    parameters->zero24 = 0;
    notePitch = note->pitch;
    parameters->pan = 64;
    parameters->note = count;
    parameters->variant = variant;
    parameters->pitchOffset = notePitch;
    voice->parameters.effect = player->engine->effect;
    parameters->gain = 1.0f;
    parameters->mode = SoundInfo_GetPan(note);
    voice->noteWord = (s16)SoundInfo_GetFlags(note);
    parameters->zero50 = 0;
    Sound_ReleaseContextLock((s32 *)player->engine);
    return voice;
}
