#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "BUF16B.H"
#include "libgultra/__INITCHANSTATE.H"
#include "al_globals.h"
#include "COMMON/TRIPLE.H"
#include "COMMON/LONE/G_AUDIOSEQPLAYERTEXT.H"
#include "COMMON/LONE/SEQUENCE_PLAYER_ASSERT_TEXT.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/OBJRECAT18V1.H"
#include "libgultra/seqplayer.h"
#include "libgultra/__POSTNEXTSEQEVENT.H"
#include "libultra/debug/assert.h"
#include "COMMON/ALSEQUENCEPLAYER.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/OBJRECAT4V6.H"
#include "libgultra.h"
#include "COMMON/ALDELAY28.H"
#include "libgultra/alunlink.h"
#include "COMMON/ALFXPARAM.H"
#include "DATA/REST_SOURCE_RECORDS.H"

/* seqplayer_2.c */
 /* 2147483648.0f */

                        /* __handleNextSeqEvent */
                   /* __setUsptFromTempo */
extern ALMicroTime alEvtqNextEvent(ALEventQueue *, ALEvent *);

    /* alEvtqNextEvent */
extern void alEvtqFlushType(ALEventQueue *, s16);

extern char addrLow_Device_EnableTriggerActor[];

extern char addrLow_Link_ClearActorStateBit[];

void __initChanState(void *playerObject);
void Seqplayer_AdvanceSequenceEvent(ALSeqPlayer *seqp);
void Seqplayer_HandleSequenceMidiEvent(ALSeqPlayer *seqp, ALEvent *event);
void Seqplayer_ReleaseSequenceVoice(ALSeqPlayer *voicePool, void *voice);
void Seqplayer_SetTempoMicrosecondsPerTick(ALSeqPlayer *player, f32 tempo);
void __handleMetaMsg(ALSeqPlayer *player, ALEvent *metaEvent);
void __initFromBank(void *seqPlayer, void *instrumentBank);
void __postNextSeqEvent(void *seqPlayer);
void __seqpReleaseVoice(void *seqPlayer, void *releasedVoice, s32 releaseDuration);
void __seqpStopOsc(void *seqPlayer, void *voiceState);
s32 __voiceNeedsNoteKill(void *sequencePlayer, s32 targetVoice, s32 releaseDeadline);
int __vsDelta(void *voiceObject, int currentTime);
s16 __vsVol(ALVoiceState *vs, ALSeqPlayer *seqp);
void *__lookupSoundQuick(void *seqPlayer, s32 noteKey, s32 noteVelocity, s32 channelNumber);
ALVoiceState *__lookupVoice(ALSeqPlayer *seqp, u8 key, u8 channel);
ALVoiceState *__mapVoice(ALSeqPlayer *sequencePlayer, u8 noteKey, u8 noteVelocity, u8 midiChannel);
void __setInstChanState(void *seqPlayer, void *selectedInstrument, s32 channelNumber);
s32 __vsPan(void *voiceObject, void *playerObject);
void __resetPerfChanState(void *playerObject, s32 index);

/* seqplayer.c */
/* seqplayer.c */
/* 802B3B80_2.CPP */
#if defined(VERSION_EU)
#include "TYPES.H"
#include "COMMON/ALSEQUENCEPLAYER.H"
#include "COMMON/COMPRESSED_SEQUENCE_AND_EVENT_VIEWS.H"
#include "al_globals.h"
extern void __initChanState(void *);

void Seqplayer_CreateSequencePlayer(ALSeqPlayer *seqp, InitParams *c) {
    void *heap = c->context;
    void *drvr = g_audioGlobals;
    ALVoiceState *vs;
    ALVoiceState *voices;
    ALEventListItem *items;
    s32 i;
    seqp->chanMask = 0xFF;
    seqp->uspt = 0x1E8;
    seqp->bank = 0;
    seqp->target = 0;
    seqp->nextDelta = 0;
    seqp->state = 0;
    seqp->vol = 0x7FFF;
    seqp->drvr = drvr;
    seqp->debugFlags = c->debugFlags;
    seqp->frameTime = 0x3E80;
    seqp->curTime = 0;
    seqp->initOsc = c->value10;
    seqp->updateOsc = c->value14;
    seqp->stopOsc = c->value18;
    seqp->loopStart = 0;
    seqp->loopEnd = 0;
    seqp->loopCount = 0;
    seqp->nextEvent.type = 9;
    seqp->maxChannels = c->kind;
    seqp->chanState = alHeapDBAlloc(0, 0, heap, c->kind, sizeof(ALChanState));
    __initChanState(seqp);
    voices = alHeapDBAlloc(0, 0, heap, c->count38, sizeof(ALVoiceState));
    seqp->vFreeList = 0;
    for (i = 0; i < c->count38; i++) {
        vs = &voices[i];
        vs->next = seqp->vFreeList;
        seqp->vFreeList = vs;
    }
    seqp->vAllocHead = 0;
    seqp->vAllocTail = 0;
    items = alHeapDBAlloc(0, 0, heap, c->count1C, sizeof(ALEventListItem));
    alEvtqNew(&seqp->evtq, items, c->count1C);
    seqp->node.next = 0;
    seqp->node.handler = &Seqplayer_ProcessSequenceEvents_Address;
    seqp->node.clientData = seqp;
    alSynAddPlayer(g_audioGlobals, seqp);
}
#endif

/* 802B54A0.CPP */
#if !(defined(VERSION_EU))

void alSeqpNew(ALSeqPlayer *p, ALSeqpConfig *c) {
    void *heap = c->heap;
    void *driver = g_audioGlobals;
    ALVoiceState *voice;
    void *events;
    s32 i;
    p->chanMask = 255;
    p->uspt = 488;
    p->bank = 0;
    p->target = 0;
    p->nextDelta = 0;
    p->state = 0;
    p->vol = 32767;
    p->drvr = driver;
    p->debugFlags = c->debugFlags;
    p->frameTime = 16000;
    p->curTime = 0;
    p->initOsc = c->initOsc;
    p->updateOsc = c->updateOsc;
    p->stopOsc = c->stopOsc;
    p->loopStart = 0;
    p->loopEnd = 0;
    p->loopCount = 0;
    p->nextEvent.type = 9;
    p->maxChannels = c->maxChannels;
    p->chanState = alHeapDBAlloc(0, 0, heap, c->maxChannels, 16);
    __initChanState(p);
    {
        ALVoiceState *base = alHeapDBAlloc(0, 0, heap, c->maxVoices, 56);
        p->vFreeList = 0;
        i = 0;
        if (c->maxVoices > 0) {
            voice = base;
            do {
                voice->next = p->vFreeList;
                p->vFreeList = voice;
                i++;
                voice++;
            } while (i < c->maxVoices);
        }
    }
    p->vAllocHead = 0;
    p->vAllocTail = 0;
    events = alHeapDBAlloc(0, 0, heap, c->maxEvents, 28);
    alEvtqNew(&p->evtq, events, c->maxEvents);
    p->node.next = 0;
    p->node.handler = (ALVoiceHandler)&Seqplayer_ProcessSequenceEvents_Address;
    p->node.clientData = p;
    alSynAddPlayer(g_audioGlobals, p);
}
#endif

/* SEQPLAYER.CPP */
#if defined(VERSION_US_REV1)
extern char addrLow_Device_EnableTriggerActor[];
extern char addrLow_Link_ClearActorStateBit[];
void * g_SeqplayerEncodedWordsBlock1[3] = {
    (void *)&addrLow_Device_EnableTriggerActor, (void *)&addrLow_Link_ClearActorStateBit, 0,
};
#endif

/* seqplayer_data.c */
#if defined(VERSION_US)
unsigned int k_SeqplayerEncodedWordsBlock1[3] = {
    0x74656D54, 0x00008855, 0x02000800,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_SeqplayerEncodedWordsBlock2[3] = {
    0x002056F0, 0x0027924C, 0x00000000,
};
#endif

/* K_WEAPONAIENCODEDWORDS.CPP */
#if defined(VERSION_EU)
float k_WeaponaiEncodedWords[3] = {
    1.0f, 1024.0f, 0.0009765625f,
};
#endif

/* SEQPLAYER_PROCESSSEQUENCEEVENTS_DATA.CPP */
/* ROM-grounded data: rodata/shared/800CC690 */
#if defined(VERSION_DE)
const char k_SeqplayerProcesssequenceeventsEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

#if defined(VERSION_EU)
const char k_SeqplayerProcesssequenceeventsEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

#if defined(VERSION_EU_X)
const char k_SeqplayerProcesssequenceeventsEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

#if defined(VERSION_US)
const char k_SeqplayerProcesssequenceeventsEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

#if defined(VERSION_US_REV1)
const char k_SeqplayerProcesssequenceeventsEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

/* SEQPLAYER.CPP */
const char g_audioSeqplayerText[18] = "audio/seqplayer.c";

/* seqplayer.c */
                 /* alEvtqFlushType */

        /* __vsVol */
                 /* __assert */

ALMicroTime Seqplayer_ProcessSequenceEvents(void *node)
{
    ALSeqPlayer *seqp = node;
    ALEvent evt;
    ALVoice *voice;
    ALMicroTime delta;
    ALVoiceState *vs;
    void *oscState;
    f32 oscValue;
    u8 chan;
    u32 tremelo;
    u8 *tremeloSlot;

    do {
        switch (seqp->nextEvent.type) {
        case 0: /* AL_SEQ_REF_EVT */
            Seqplayer_AdvanceSequenceEvent(seqp);
            break;
        case 9: /* AL_SEQP_API_EVT */
            evt.type = 9;
            alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, seqp->frameTime);
            break;
        case 5: /* AL_NOTE_END_EVT */
            voice = seqp->nextEvent.msg.note.voice;
            alSynStopVoice(seqp->drvr, voice);
            alSynFreeVoice(seqp->drvr, voice);
            vs = (ALVoiceState *)voice->clientPrivate;
            if (vs->flags)
                __seqpStopOsc(seqp, vs);
            Seqplayer_ReleaseSequenceVoice(seqp, voice);
            break;
        case 6: /* AL_SEQP_ENV_EVT */
            voice = seqp->nextEvent.msg.vol.voice;
            vs = (ALVoiceState *)voice->clientPrivate;
            if (vs->envPhase == 0)
                vs->envPhase = 1;
            delta = seqp->nextEvent.msg.vol.delta;
            vs->envGain = seqp->nextEvent.msg.vol.vol;
            vs->envEndTime = seqp->curTime + delta;
            alSynSetVol(seqp->drvr, voice, __vsVol(vs, seqp), delta);
            break;
        case 22: /* AL_TREM_OSC_EVT */
            vs = seqp->nextEvent.msg.osc.vs;
            oscState = seqp->nextEvent.msg.osc.oscState;
            delta = (*seqp->updateOsc)(oscState, &oscValue);
            tremeloSlot = &vs->tremelo;
            tremelo = (u32)oscValue;
            *tremeloSlot = tremelo;
            alSynSetVol(seqp->drvr, &vs->voice, __vsVol(vs, seqp),
                          __vsDelta(vs, seqp->curTime));
            evt.type = 22;
            evt.msg.osc.vs = vs;
            evt.msg.osc.oscState = oscState;
            alEvtqPostEvent(&seqp->evtq, &evt, delta);
            break;
        case 23: /* AL_VIB_OSC_EVT */
            vs = seqp->nextEvent.msg.osc.vs;
            oscState = seqp->nextEvent.msg.osc.oscState;
            chan = seqp->nextEvent.msg.osc.chan;
            delta = (*seqp->updateOsc)(oscState, &oscValue);
            vs->vibrato = oscValue;
            alSynSetPitch(seqp->drvr, &vs->voice,
                          vs->pitch * vs->vibrato * seqp->chanState[chan].pitchBend);
            evt.type = 23;
            evt.msg.osc.vs = vs;
            evt.msg.osc.oscState = oscState;
            evt.msg.osc.chan = chan;
            alEvtqPostEvent(&seqp->evtq, &evt, delta);
            break;
        case 2: /* AL_SEQP_MIDI_EVT */
            Seqplayer_HandleSequenceMidiEvent(seqp, &seqp->nextEvent);
            break;
        case 7: /* AL_SEQP_META_EVT */
            __handleMetaMsg(seqp, &seqp->nextEvent);
            break;
        case 15: /* AL_SEQP_PLAY_EVT */
            if (seqp->state != 1) {
                seqp->state = 1;
                __postNextSeqEvent(seqp);
            }
            break;
        case 16: /* AL_SEQP_STOP_EVT */
            if (seqp->state == 2) {
                for (vs = seqp->vAllocHead; vs != 0; vs = seqp->vAllocHead) {
                    alSynStopVoice(seqp->drvr, &vs->voice);
                    alSynFreeVoice(seqp->drvr, &vs->voice);
                    if (vs->flags)
                        __seqpStopOsc(seqp, vs);
                    Seqplayer_ReleaseSequenceVoice(seqp, &vs->voice);
                }
                seqp->curTime = 0;
                seqp->state = 0;
            }
            break;
        case 17: /* AL_SEQP_STOPPING_EVT */
            if (seqp->state == 1) {
                alEvtqFlushType(&seqp->evtq, 0);
                alEvtqFlushType(&seqp->evtq, 2);
                for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                    if ((u8)__voiceNeedsNoteKill(seqp, &vs->voice, 50000))
                        __seqpReleaseVoice(seqp, &vs->voice, 50000);
                }
                seqp->state = 2;
                evt.type = 16;
                alEvtqPostEvent(&seqp->evtq, &evt, 0x7fffffff);
            }
            break;
        case 10: /* AL_SEQP_VOL_EVT */
            seqp->vol = seqp->nextEvent.msg.spvol.vol;
            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                alSynSetVol(seqp->drvr, &vs->voice, __vsVol(vs, seqp),
                              __vsDelta(vs, seqp->curTime));
            }
            break;
        case 11: /* AL_SEQP_LOOP_EVT */
            seqp->loopStart = seqp->nextEvent.msg.loop.start;
            seqp->loopEnd = seqp->nextEvent.msg.loop.end;
            seqp->loopCount = seqp->nextEvent.msg.loop.count;
            break;
        case 12: /* AL_SEQP_PRIORITY_EVT */
            chan = seqp->nextEvent.msg.sppriority.chan;
            seqp->chanState[chan].priority = seqp->nextEvent.msg.sppriority.priority;
            break;
        case 13: /* AL_SEQP_SEQ_EVT */
            if (seqp->state == 1)
                __assert(g_sequencePlayerAssertText, g_audioSeqplayerText, 296);
            seqp->target = seqp->nextEvent.msg.spseq.seq;
            Seqplayer_SetTempoMicrosecondsPerTick(seqp, 500000.0f);
            if (seqp->bank)
                __initFromBank(seqp, seqp->bank);
            break;
        case 14: /* AL_SEQP_BANK_EVT */
            if (seqp->state != 0)
                __assert(g_sequencePlayerAssertText, g_audioSeqplayerText, 305);
            seqp->bank = seqp->nextEvent.msg.spbank.bank;
            __initFromBank(seqp, seqp->bank);
            break;
        case 4: /* AL_SEQ_END_EVT */
        case 3: /* AL_TEMPO_EVT */
        case 1: /* AL_SEQ_MIDI_EVT */
            __assert(g_sequencePlayerAssertText, g_audioSeqplayerText, 315);
            break;
        }
        seqp->nextDelta = alEvtqNextEvent(&seqp->evtq, &seqp->nextEvent);
    } while (seqp->nextDelta == 0);
    seqp->curTime += seqp->nextDelta;
    return seqp->nextDelta;
}

/* seqplayer_3.c */
/* __handleMIDIMsg, drafted from ultralib src/audio/seqplayer.c: applies one MIDI channel message
   to the sequence player (note on with voice allocation, envelope and oscillator setup, note off,
   pressure, controllers, program change and pitch bend). Adapted from the matched csplayer twin:
   the status and data bytes are read through the event rather than the midi pointer, and the
   float to u8 tremolo conversion is written out against the cartridge's 2^31 constant with its
   store address taken first. */

 /* 127.0f, followed by 2^31 */

 /* 1.0f */

 /* "EX" */

 /* "audio/seqplayer.c" */

 /* __lookupSoundQuick */

 /* __mapVoice */

 /* __lookupVoice */

 /* alSynAllocVoice */
                                   /* alCents2Ratio */

 /* __vsPan */

 /* __vsVol */

 /* __vsDelta */

 /* alSynStartVoiceParams */

 /* alEvtqPostEvent */

 /* __seqpReleaseVoice */

 /* alSynSetVol */

 /* alSynSetPan */

 /* alSynSetFXMix */

 /* alSynSetPitch */

 /* __setInstChanState */

void Seqplayer_AdvanceSequenceEvent(ALSeqPlayer *seqp)
{
    ALEvent evt;

    if (seqp->target == 0)
        return;

    alSeqNextEvent(seqp->target, &evt);

    switch (evt.type) {
    case 1:     /* AL_SEQ_MIDI_EVT */
        Seqplayer_HandleSequenceMidiEvent(seqp, &evt);
        postNextSeqEvent(seqp);
        break;

    case 3:     /* AL_TEMPO_EVT */
        __handleMetaMsg(seqp, &evt);
        postNextSeqEvent(seqp);
        break;

    case 4:     /* AL_SEQ_END_EVT */
        seqp->state = 2;
        evt.type = 16;  /* AL_SEQP_STOP_EVT */
        alEvtqPostEvent(&seqp->evtq, &evt, 0x7fffffff);
        break;

    default:
        __assert(g_sequencePlayerAssertText, g_audioSeqplayerText, 412);
    }
}

 /* __assert */
void Seqplayer_HandleSequenceMidiEvent(ALSeqPlayer *seqp, ALEvent *event)
{
    ALVoice *voice;
    ALVoiceState *vs;
    s32 status;
    u8 chan;
    u8 key;
    u8 vel;
    u8 byte1;
    u8 byte2;
    ALMIDIEvent *midi = &event->msg.midi;
    s16 vol;
    ALEvent evt;
    ALMicroTime deltaTime;
    ALVoiceState *vstate;
    u8 pan;
    if (!(event->type == 1 || event->type == 2)) /* AL_SEQ_MIDI_EVT, AL_SEQP_MIDI_EVT */
        __assert(g_sequencePlayerAssertText, g_audioSeqplayerText, 436);
    status = event->msg.midi.status & 0xF0;
    chan = event->msg.midi.status & 0x0F;
    byte1 = key = event->msg.midi.byte1;
    byte2 = vel = event->msg.midi.byte2;
    switch (status) {
    case 0x90: /* AL_MIDI_NoteOn */
        if (vel != 0) {
            ALVoiceConfig config;
            ALSound *sound;
            s16 cents;
            f32 pitch, oscValue;
            u8 fxmix;
            void *oscState;
            ALInstrument *inst;
            s32 tremelo;
            u8 *tremeloSlot;
            if (seqp->state != 1)
                break;
            sound = __lookupSoundQuick(seqp, key, vel, chan);
            if (!sound)
                return;
            config.priority = seqp->chanState[chan].priority;
            config.fxBus = 0;
            config.unityPitch = 0;
            vstate = __mapVoice(seqp, key, vel, chan);
            if (!vstate)
                return;
            voice = &vstate->voice;
            alSynAllocVoice(seqp->drvr, voice, &config);
            vstate->sound = sound;
            vstate->envPhase = 0;
            if (seqp->chanState[chan].sustain > 63)
                vstate->phase = 2;
            else
                vstate->phase = 0;
            cents = (key - sound->keyMap->keyBase) * 100 + sound->keyMap->detune;
            vstate->pitch = alCents2Ratio(cents);
            vstate->envGain = sound->envelope->attackVolume;
            vstate->envEndTime = seqp->curTime + sound->envelope->attackTime;
            vstate->flags = 0;
            inst = seqp->chanState[chan].instrument;
            oscValue = g_sequenceInitialOscillatorValue;
            if (inst->tremType) {
                if (seqp->initOsc) {
                    deltaTime = (*seqp->initOsc)(&oscState, &oscValue, inst->tremType,
                                                 inst->tremRate, inst->tremDepth, inst->tremDelay);
                    if (deltaTime) {
                        evt.type = 22; /* AL_TREM_OSC_EVT */
                        evt.msg.osc.vs = vstate;
                        evt.msg.osc.oscState = oscState;
                        alEvtqPostEvent(&seqp->evtq, &evt, deltaTime);
                        vstate->flags |= 0x01;
                    }
                }
            }
            tremeloSlot = &vstate->tremelo;
            if (!(oscValue >= (*(&g_sequenceInitialOscillatorValue + 1)))) {
                tremelo = (s32)oscValue;
            } else {
                tremelo = (s32)(oscValue - (*(&g_sequenceInitialOscillatorValue + 1)));
                tremelo |= 0x80000000;
            }
            *tremeloSlot = tremelo;
            oscValue = g_sequenceFallbackOscillatorValue;
            if (inst->vibType) {
                if (seqp->initOsc) {
                    deltaTime = (*seqp->initOsc)(&oscState, &oscValue, inst->vibType,
                                                 inst->vibRate, inst->vibDepth, inst->vibDelay);
                    if (deltaTime) {
                        evt.type = 23; /* AL_VIB_OSC_EVT */
                        evt.msg.osc.vs = vstate;
                        evt.msg.osc.oscState = oscState;
                        evt.msg.osc.chan = chan;
                        alEvtqPostEvent(&seqp->evtq, &evt, deltaTime);
                        vstate->flags |= 0x02;
                    }
                }
            }
            vstate->vibrato = oscValue;
            pitch = vstate->pitch * seqp->chanState[chan].pitchBend * vstate->vibrato;
            fxmix = seqp->chanState[chan].fxmix;
            pan = __vsPan(vstate, seqp);
            vol = __vsVol(vstate, seqp);
            deltaTime = sound->envelope->attackTime;
            alSynStartVoiceParams(seqp->drvr, voice, sound->wavetable, pitch, vol, pan, fxmix, deltaTime);
            evt.type = 6; /* AL_SEQP_ENV_EVT */
            evt.msg.vol.voice = voice;
            evt.msg.vol.vol = sound->envelope->decayVolume;
            evt.msg.vol.delta = sound->envelope->decayTime;
            deltaTime = sound->envelope->attackTime;
            alEvtqPostEvent(&seqp->evtq, &evt, deltaTime);
            break;
        }
    case 0x80: /* AL_MIDI_NoteOff */
        vstate = __lookupVoice(seqp, key, chan);
        if (!vstate)
            return;
        if (vstate->phase == 2)
            vstate->phase = 4;
        else {
            vstate->phase = 3;
            __seqpReleaseVoice(seqp, &vstate->voice, vstate->sound->envelope->releaseTime);
        }
        break;
    case 0xA0: /* AL_MIDI_PolyKeyPressure */
        vstate = __lookupVoice(seqp, key, chan);
        if (!vstate)
            return;
        vstate->velocity = byte2;
        alSynSetVol(seqp->drvr, &vstate->voice, __vsVol(vstate, seqp),
                      __vsDelta(vstate, seqp->curTime));
        break;
    case 0xD0: /* AL_MIDI_ChannelPressure */
        for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
            if (vs->channel == chan) {
                vs->velocity = byte1;
                alSynSetVol(seqp->drvr, &vs->voice, __vsVol(vs, seqp),
                              __vsDelta(vs, seqp->curTime));
            }
        }
        break;
    case 0xB0: /* AL_MIDI_ControlChange */
        switch (byte1) {
        case 0x0A: /* AL_MIDI_PAN_CTRL */
            seqp->chanState[chan].pan = byte2;
            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                if (vs->channel == chan) {
                    pan = __vsPan(vs, seqp);
                    alSynSetPan(seqp->drvr, &vs->voice, pan);
                }
            }
            break;
        case 0x07: /* AL_MIDI_VOLUME_CTRL */
            seqp->chanState[chan].vol = byte2;
            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                if ((vs->channel == chan) && (vs->envPhase != 3)) {
                    vol = __vsVol(vs, seqp);
                    alSynSetVol(seqp->drvr, &vs->voice, vol, __vsDelta(vs, seqp->curTime));
                }
            }
            break;
        case 0x10: /* AL_MIDI_PRIORITY_CTRL */
            seqp->chanState[chan].priority = byte2;
            break;
        case 0x40: /* AL_MIDI_SUSTAIN_CTRL */
            seqp->chanState[chan].sustain = byte2;
            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                if ((vs->channel == chan) && (vs->phase != 3)) {
                    if (byte2 > 63) {
                        if (vs->phase == 0)
                            vs->phase = 2;
                    } else {
                        if (vs->phase == 2)
                            vs->phase = 0;
                        else if (vs->phase == 4) {
                            vs->phase = 3;
                            __seqpReleaseVoice(seqp, &vs->voice, vs->sound->envelope->releaseTime);
                        }
                    }
                }
            }
            break;
        case 0x5B: /* AL_MIDI_FX1_CTRL */
            seqp->chanState[chan].fxmix = byte2;
            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                if (vs->channel == chan)
                    alSynSetFXMix(seqp->drvr, &vs->voice, byte2);
            }
            break;
        case 0x14: /* AL_MIDI_FX_CTRL_0 */
        case 0x15: /* AL_MIDI_FX_CTRL_1 */
        case 0x16: /* AL_MIDI_FX_CTRL_2 */
        case 0x17: /* AL_MIDI_FX_CTRL_3 */
        case 0x18: /* AL_MIDI_FX_CTRL_4 */
        case 0x19: /* AL_MIDI_FX_CTRL_5 */
        case 0x1A: /* AL_MIDI_FX_CTRL_6 */
        case 0x1B: /* AL_MIDI_FX_CTRL_7 */
        case 0x5D: /* AL_MIDI_FX3_CTRL */
        default:
            break;
        }
        break;
    case 0xC0: /* AL_MIDI_ProgramChange */
        if (seqp->bank == 0)
            __assert(g_sequencePlayerAssertText, g_audioSeqplayerText, 714);
        if (key < seqp->bank->instCount) {
            ALInstrument *inst = seqp->bank->instArray[key];
            __setInstChanState(seqp, inst, chan);
        }
        break;
    case 0xE0: /* AL_MIDI_PitchBendChange */
        {
            s32 bendVal;
            f32 bendRatio;
            s32 cents;
            bendVal = ((byte2 << 7) + byte1) - 8192;
            cents = (seqp->chanState[chan].bendRange * bendVal) / 8192;
            bendRatio = alCents2Ratio(cents);
            seqp->chanState[chan].pitchBend = bendRatio;
            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next)
                if (vs->channel == chan)
                    alSynSetPitch(seqp->drvr, &vs->voice, vs->pitch * bendRatio * vs->vibrato);
        }
        break;
    default:
        break;
    }
}

/* seqplayer.c */
ALVoiceState *__mapVoice(ALSeqPlayer *sequencePlayer, u8 noteKey, u8 noteVelocity, u8 midiChannel) {
    ALVoiceState *node;
    ALSeqPlayer88 *player = (ALSeqPlayer88 *)sequencePlayer;
    ALVoiceState *next;
    ALVoiceState *tail;

    node = player->vFreeList;
    if (node != 0) {
        next = node->next;
        player->vFreeList = next;
        node->next = 0;
        if (player->vAllocHead == 0) {
            player->vAllocHead = node;
        } else {
            tail = player->vAllocTail;
            tail->next = node;
        }
        player->vAllocTail = node;
        node->channel = midiChannel;
        node->key = noteKey;
        node->velocity = noteVelocity;
        node->voice.clientPrivate = node;
    }
    return node;
}

void Seqplayer_ReleaseSequenceVoice(ALSeqPlayer *voicePool, void *voice) {
    ALVoiceState *node;
    ALVoiceState *prev;

    prev = 0;
    node = voicePool->vAllocHead;
    while (node != 0) {
        if ((void *)&node->voice == voice) {
            if (prev != 0) {
                prev->next = node->next;
            } else {
                voicePool->vAllocHead = node->next;
            }
            if (node == voicePool->vAllocTail) {
                voicePool->vAllocTail = prev;
            }
            node->next = voicePool->vFreeList;
            voicePool->vFreeList = node;
            return;
        }
        prev = node;
        node = node->next;
    }
}

/* voiceneedsnotekill.c */
s32 __voiceNeedsNoteKill(void *sequencePlayer, s32 targetVoice, s32 releaseDeadline) {
    s32 amount;
    s32 total;
    s32 result;
    char *next;
    char *cur;

    total = 0;
    cur = ((ALSeqPlayer *)sequencePlayer)->evtq.allocList.next;
    result = 1;
    if (cur != 0) {
        do {
            amount = ((ALEventListItem *)cur)->delta;
            next = ((ALEventListItem *)cur)->node.next;
            total += amount;
            if (((ALEventListItem *)cur)->evt.type == 5 && (s32)((ALEvent *)&((ALEventListItem *)cur)->evt)->msg.note.voice == targetVoice) {
                if (releaseDeadline < total) {
                    if (next != 0) {
                        ((ALEventListItem *)next)->delta = ((ALEventListItem *)next)->delta + amount;
                    }
                    alUnlink(cur);
                    alLink(cur, &((ALSeqPlayer *)sequencePlayer)->evtq.freeList.next);
                    goto done;
                }
                result = 0;
                goto done;
            }
            cur = next;
        } while (cur != 0);
    }
done:
    return result;
}

/* __lookupVoice, drafted from ultralib src/audio/seqplayer.c: walk the sequence player's allocated
   voice list for the voice playing a key on a channel that is not being released. */

ALVoiceState *__lookupVoice(ALSeqPlayer *seqp, u8 key, u8 channel)
{
    ALVoiceState *vs;

    for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
        if ((vs->key == key) && (vs->channel == channel) &&
            (vs->phase != 3) && (vs->phase != 4))
            return vs;
    }
    return 0;
}

/* seqplayer.c */
/* seqplayer_4.c */

void *__lookupSoundQuick(void *seqPlayer, s32 noteKey, s32 noteVelocity, s32 channelNumber) {
    s32 high;
    s32 low;
    s32 middle;
    u8 x;
    u8 y;
    ALInstrument *table;
    ALSound *entry;
    u8 *bounds;

    table = ((ALSeqPlayer *)seqPlayer)->chanState[channelNumber & 0xFF].instrument;
    high = table->soundCount;
    low = 1;
    if (table == 0) {
        __assert(g_sequencePlayerAssertText, g_audioSeqplayerText, 0x376);
    }

    if (high > 0) {
        x = noteKey;
        y = noteVelocity;
        do {
            middle = (low + high) / 2;
            entry = table->soundArray[middle - 1];
            bounds = (u8 *)entry->keyMap;
            if (x >= bounds[2] && x <= bounds[3] &&
                y >= bounds[0] && y <= bounds[1]) {
                return entry;
            }
            if (x < bounds[2] ||
                (y < bounds[0] && x <= bounds[3])) {
                high = middle - 1;
            } else {
                low = middle + 1;
            }
        } while (low <= high);
    }
    return 0;
}

/* seqplayer_voice_channels.c */

/* __vsVol, drafted from ultralib src/audio/seqplayer.c: combine a voice's tremolo, velocity and
   envelope gain with its sound's sample volume, the player volume and the channel volume. */

s16 __vsVol(ALVoiceState *vs, ALSeqPlayer *seqp)
{
    u32 t1, t2;

    t1 = (vs->tremelo * vs->velocity * vs->envGain) >> 6;
    t2 = (vs->sound->sampleVolume * seqp->vol *
          seqp->chanState[vs->channel].vol) >> 14;

    t1 *= t2;
    t1 >>= 15;

    return (s16)t1;
}

/** Clamp (record - currentTime) at a lower bound of 0x3E8 for negative results. */
int __vsDelta(void *voiceObject, int currentTime) {
    ALVoiceState *voice = voiceObject;
    int v = voice->envEndTime - currentTime;
    if (v >= 0) {
        return v;
    }
    return 0x3E8;
}

s32 __vsPan(void *voiceObject, void *playerObject) {
    ALVoiceState *voice = voiceObject;
    ALSeqPlayer *player = playerObject;
    s32 pan;
    char center = 0x40;
    pan = player->chanState[voice->channel].pan + (voice->sound->samplePan - center);
    if (pan < 0) pan = 0;
    if (pan >= 0x80) pan = 0x7F;
    return pan & 0xFF;
}

void __initFromBank(void *seqPlayer, void *instrumentBank) {
    s32 i;
    ALBank *p;
    void *found;

    p = instrumentBank;
    i = 0;
    do {
        found = p->instArray[i];
        i++;
    } while (found == 0);
    i = 0;
    if (((ALSeqPlayer *)seqPlayer)->maxChannels != 0) {
        do {
            __resetPerfChanState(seqPlayer, i);
            __setInstChanState(seqPlayer, found, i);
            i += 1;
        } while (i < ((ALSeqPlayer *)seqPlayer)->maxChannels);
    }
    if (((ALBank *)instrumentBank)->percussion != 0) {
        __resetPerfChanState(seqPlayer, i);
        __setInstChanState(seqPlayer, ((ALBank *)instrumentBank)->percussion, 9);
    }
}

void __initChanState(void *playerObject) {
    ALSeqPlayer *player = playerObject;
    s32 i;
    s32 off;
    s32 c40, c7f, c5, cc8;
    f32 val;

    i = 0;
    if (player->maxChannels != 0) {
        c40 = 0x40;
        c7f = 0x7F;
        c5 = 5;
        cc8 = 0xC8;
        val = g_sequenceChannelInitialOscillatorValue;
        do {
            off = i << 4;
            player->chanState[i].instrument = 0;
            player->chanState[i].fxId = 0;
            player->chanState[i].fxmix = 0;
            player->chanState[i].pan = (u8) c40;
            player->chanState[i].vol = (u8) c7f;
            player->chanState[i].priority = (u8) c5;
            player->chanState[i].sustain = 0;
            player->chanState[i].bendRange = (u16) cc8;
            player->chanState[i].pitchBend = val;
            i += 1;
        } while (i < (s32) player->maxChannels);
    }
}

/* Initialize one channel of the sequence player's channel table. */
void __resetPerfChanState(void *playerObject, s32 index) {
    ALSeqPlayer *player = playerObject;

    player->chanState[index].fxId = 0;
    player->chanState[index].fxmix = 0;
    player->chanState[index].pan = 0x40;
    player->chanState[index].vol = 0x7F;
    player->chanState[index].priority = 5;
    player->chanState[index].sustain = 0;
    player->chanState[index].bendRange = 0xC8;
    player->chanState[index].pitchBend = g_sequenceInitialPitchBend;
}

/* seqplayer.c */

/* Voice events serialize the voice pointer in the first four payload bytes. */
static inline ALVoice *event_voice(ALEvent *event) {
    return (ALVoice *)event->msg.note.voice;
}

/** Store a new history slot (pointer + selected byte/word fields) into the ring buffer at seqPlayer+0x60. */
void __setInstChanState(void *seqPlayer, void *selectedInstrument, s32 channelNumber) {
    s32 stride = channelNumber * 0x10;

    ((ALChanState *)(stride + (s32)((ALSeqPlayer *)seqPlayer)->chanState))->instrument = selectedInstrument;
    ((ALChanState *)((stride + (s32)((ALSeqPlayer *)seqPlayer)->chanState)))->pan = ((ALInstrument *)selectedInstrument)->pan;
    ((ALChanState *)((stride + (s32)((ALSeqPlayer *)seqPlayer)->chanState)))->vol = ((ALInstrument *)selectedInstrument)->volume;
    ((ALChanState *)((stride + (s32)((ALSeqPlayer *)seqPlayer)->chanState)))->priority = ((ALInstrument *)selectedInstrument)->priority;
    ((ALChanState *)((stride + (s32)((ALSeqPlayer *)seqPlayer)->chanState)))->bendRange = (u16)((ALInstrument *)selectedInstrument)->bendRange;
}

void __seqpReleaseVoice(void *seqPlayer, void *releasedVoice, s32 releaseDuration) {
    ALEventListItem *cur;
    ALEventListItem *next;
    ALVoiceState *object;
    s32 type6;
    SeqplayerVoiceEvent entry;

    object = ((ALVoice *)releasedVoice)->clientPrivate;
    if (object->envPhase == 0) {
        cur = (ALEventListItem *)((ALSeqPlayer *)seqPlayer)->evtq.allocList.next;
        if (cur != 0) {
            type6 = 6;
            do {
                next = (ALEventListItem *)cur->node.next;
                if (cur->evt.type == type6 &&
                    event_voice(&cur->evt) == releasedVoice) {
                    if (next != 0) {
                        next->delta = next->delta +
                                            cur->delta;
                    }
                    alUnlink(cur);
                    alLink(cur, &((ALSeqPlayer *)seqPlayer)->evtq);
                }
                cur = next;
            } while (cur != 0);
        }
    }
    object->velocity = 0;
    object->envPhase = 3;
    object->envGain = 0;
    object->envEndTime = ((ALSeqPlayer *)seqPlayer)->curTime + releaseDuration;
    alSynSetPriority(((ALSeqPlayer *)seqPlayer)->drvr, releasedVoice, 0);
    alSynSetVol(((ALSeqPlayer *)seqPlayer)->drvr, releasedVoice, 0, releaseDuration);
    entry.type = 5;
    entry.object = releasedVoice;
    alEvtqPostEvent(&((ALSeqPlayer *)seqPlayer)->evtq, &entry, releaseDuration);
}

void __seqpStopOsc(void *seqPlayer, void *voiceState) {
    ALEventListItem *cur;
    ALEventListItem *next;
    u16 type;
    s32 type16;

    cur = (void *)((ALSeqPlayer *)seqPlayer)->evtq.allocList.next;
    if (cur != 0) {
        type16 = 0x16;
        do {
            type = cur->evt.type;
            next = (void *)cur->node.next;
            if ((type == 0x16 || type == 0x17) &&
                ((ALEvent *)&cur->evt)->msg.osc.vs == voiceState) {
                ((ALSeqPlayer *)seqPlayer)->stopOsc(
                    ((ALEvent *)&cur->evt)->msg.osc.oscState);
                alUnlink(cur);
                if (next != 0) {
                    next->delta = next->delta +
                                        cur->delta;
                }
                alLink(cur, &((ALSeqPlayer *)seqPlayer)->evtq.freeList.next);
                if ((short)type == type16) {
                    ((ALVoiceState *)voiceState)->flags &= 0xFE;
                } else {
                    ((ALVoiceState *)voiceState)->flags &= 0xFD;
                }
                if (((ALVoiceState *)voiceState)->flags == 0) {
                    break;
                }
            }
            cur = next;
        } while (cur != 0);
    }
}

void __postNextSeqEvent(void *seqPlayer) {
    ALEvent referenceEvent;
    s32 deltaTicks;
    s32 remainingLoops;
    void *sequence;

    sequence = ((SequencePlayerEventView *)(seqPlayer))->sequence;
    if ((((SequencePlayerEventView *)(seqPlayer))->state == 1) && (sequence != 0) &&
        (__alSeqNextDelta(sequence, &deltaTicks) & 0xFF)) {
        if ((((SequencePlayerEventView *)(seqPlayer))->loopCount != 0) &&
            ((alSeqGetTicks(sequence) + deltaTicks) >=
             ((struct MenuTextOwnerView *) ((SequencePlayerEventView *) seqPlayer)->loopEnd)->flags)) {
            alSeqSetLoc(sequence, ((SequencePlayerEventView *)(seqPlayer))->loopStart);
            remainingLoops = ((SequencePlayerEventView *)(seqPlayer))->loopCount;
            if (remainingLoops != -1) {
                ((SequencePlayerEventView *)(seqPlayer))->loopCount = remainingLoops - 1;
            }
        }
        referenceEvent.type = 0;
        alEvtqPostEvent(&((SequencePlayerEventView *)(seqPlayer))->eventQueue, &referenceEvent,
                      deltaTicks * ((SequencePlayerEventView *)(seqPlayer))->microsecondsPerTick);
    }
}

void __handleMetaMsg(ALSeqPlayer *player, ALEvent *metaEvent) {
    u8 *p = (u8 *)metaEvent;
    int pad[4];

    (void)pad;
    if (p[8] == 0xFF && p[9] == 0x51) {
        Seqplayer_SetTempoMicrosecondsPerTick(player, (f32)((p[0xB] << 0x10) | (p[0xC] << 8) | p[0xD]));
    }
}

/* seqplayer.c */
void Seqplayer_SetTempoMicrosecondsPerTick(ALSeqPlayer *player, f32 tempo) {
    ALSeq *sequence;

    sequence = player->target;
    if (sequence != 0) {
        player->uspt = (s32)(tempo * sequence->qnpt);
        return;
    }
    player->uspt = 0x1E8;
}

/* seqplayer_data.c */
#if !(defined(VERSION_US_REV1))
const unsigned int g_seqplayer_HandleSequenceMidiEventConstantWords[5] = {
    0x42FE0000, 0x4F000000, 0x3F800000, 0x3F800000, 0x3F800000,
};
#endif

#if defined(VERSION_US_REV1)
const unsigned int k_SeqplayerEncodedWords[3] = {
    0x42FE0000, 0x4F000000, 0x3F800000,
};

/* ROM-grounded data: src/g___initChanStateConstantWords_Seqplayer.c */
const unsigned int g___initChanStateConstantWords[1] = {
    0x3F800000,
};

/* ROM-grounded data: src/g___resetPerfChanStateConstantWords_Seqplayer.c */
const unsigned int g___resetPerfChanStateConstantWords[1] = {
    0x3F800000,
};
#endif
