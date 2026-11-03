#include "../../include/PERIPHERAL_PORT_BYTE_VIEWS.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/COMPRESSED_SEQUENCE_AND_EVENT_VIEWS.H"
#include "../../include/libgultra_inferred/cseq.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "../../include/BUF16B.H"
#include "../../include/libgultra/__INITCHANSTATE.H"
#include "../../include/libgultra/seqplayer.h"
#include "../../include/libgultra_inferred/__CSPHANDLEMIDIMSG.H"
#include "../../include/libultra/debug/assert.h"
#include "../../include/al_globals.h"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/SHAREDPLAYER.H"
#include "../../include/libgultra/alunlink.h"
#include "include_asm.h"

extern s16 __vsVol(ALVoiceState *, ALSeqPlayer *);

extern s32 __vsDelta(void *, s32);

extern void __seqpReleaseVoice(void *, void *, s32);

extern void __initFromBank(void *, void *);

extern void *__lookupSoundQuick(void *, s32, s32, s32);

extern void *__mapVoice(void *, u8, u8, u8);

extern ALVoiceState *__lookupVoice(ALSeqPlayer *, u8, u8);

extern s32 __vsPan(void *, void *);

extern void __setInstChanState(void *, void *, s32);

void __CSPHandleMIDIMsg(void *object, ALEvent *message);
void __CSPHandleMetaMsg(void *sequencePlayer, CompressedSequenceMetaEvent *metaEvent);
void __CSPHandleNextSeqEvent(void *rawPlayer);
void __CSPPostNextSeqEvent(void *sequencePlayer);
void __setUsptFromTempo(void *sequencePlayer, f32 microsecondsPerQuarter);
void __CSPRepostEvent(void *eventQueue, CompressedSequenceEventNode *repostedEvent);

/* csplayer.c */
void alCSPNew(ALCSPlayer *sequencePlayer, ALSeqpConfig *config) {
    ALSeqPlayer *obj = sequencePlayer;
    InitParams *params = config;
    s32 context = params->context;
    s32 global = (s32)g_audioGlobals;
    s32 allocation;
    s32 i;

    obj->chanMask = 0xFF;
    obj->uspt = 0x1E8;
    obj->vol = 0x7FFF;
    obj->bank = 0;
    obj->target = 0;
    obj->nextDelta = 0;
    obj->state = 0;
    obj->frameTime = 0x3E80;
    obj->curTime = 0;
    obj->drvr = global;
    obj->initOsc = params->value10;
    obj->updateOsc = params->value14;
    obj->stopOsc = params->value18;
    obj->nextEvent.type = 9;
    obj->maxChannels = params->kind;
    obj->chanState = alHeapDBAlloc(0, 0, (void *)context, params->kind, 0x10);
    __initChanState(obj);

    allocation = alHeapDBAlloc(0, 0, (void *)context, params->count38, 0x38);
    obj->vFreeList = 0;
    i = 0;
    if (params->count38 > 0) {
        {
            ALVoiceState *records = (ALVoiceState *)allocation;
            do {
                records->next = obj->vFreeList;
                obj->vFreeList = records;
                i++;
                records++;
            } while (i < params->count38);
        }
    }

    obj->vAllocHead = 0;
    obj->vAllocTail = 0;
    allocation = alHeapDBAlloc(0, 0, (void *)context, params->count1C, 0x1C);
    alEvtqNew(&obj->evtq, (void *)allocation, params->count1C);
    {
        ALPlayer *node = &obj->node;
        node->next = 0;
        node->handler = &__CSPVoiceHandler_Address;
        node->clientData = node;
        alSynAddPlayer(g_audioGlobals, node);
    }
}

#if defined(VERSION_US)
unsigned int k_CsplayerEncodedWordsBlock1[1] = {
    0x6174615F,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_CsplayerZeroWords[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_CsplayerEncodedWordsBlock3[1] = {
    0x4275C28F,
};
#endif

#if defined(VERSION_DE)
unsigned int k_CsplayerEncodedWordsBlock2[1] = {
    0xAFB60030,
};
#endif

/* K_RESOURCESENCODEDBYTES.CPP */
/* ROM-grounded data: rodata/shared/800CC5A0 */
#if defined(VERSION_DE)
const char k_ResourcesEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

#if defined(VERSION_EU)
const char k_ResourcesEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

#if defined(VERSION_EU_X)
const char k_ResourcesEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

#if defined(VERSION_US)
const char k_ResourcesEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

#if defined(VERSION_US_REV1)
const char k_ResourcesEncodedBytes[3] __attribute__((aligned(1))) = "EX\000";
#endif

/* CSPLAYER.CPP */
const char g_audioCsplayerText[17] = "audio/csplayer.c";

/* csplayer.c */
/* Drain due compact-sequence events and advance to the next event time.
 * Event-kind10 reads the shared short carrier; kind12 uses its two byte
 * carriers for channel and priority. Existing message/voice views are reused. */
ALMicroTime __CSPVoiceHandler(ALSeqPlayer *node)
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
            __CSPHandleNextSeqEvent(seqp);
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
            Seqplayer_ReleaseSequenceVoice((ALSeqPlayer *)seqp, voice);
            break;
        case 6: /* AL_SEQP_ENV_EVT */
            voice = seqp->nextEvent.msg.vol.voice;
            vs = (ALVoiceState *)voice->clientPrivate;
            if (vs->envPhase == 0)
                vs->envPhase = 1;
            delta = seqp->nextEvent.msg.vol.delta;
            vs->envEndTime = seqp->curTime + delta;
            vs->envGain = seqp->nextEvent.msg.vol.vol;
            alSynSetVol(seqp->drvr, voice, __vsVol((ALVoiceState *)vs, (ALSeqPlayer *)seqp), delta);
            break;
        case 22: /* AL_TREM_OSC_EVT */
            vs = seqp->nextEvent.msg.osc.vs;
            oscState = seqp->nextEvent.msg.osc.oscState;
            delta = (*seqp->updateOsc)(oscState, &oscValue);
            tremeloSlot = &vs->tremelo;
            tremelo = (u32)oscValue;
            *tremeloSlot = tremelo;
            alSynSetVol(seqp->drvr, &vs->voice, __vsVol((ALVoiceState *)vs, (ALSeqPlayer *)seqp),
                          __vsDelta(vs, seqp->curTime));
            evt.type = 22;
            evt.msg.osc.vs = vs;
            evt.msg.osc.oscState = oscState;
            alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, delta);
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
            alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, delta);
            break;
        case 2:  /* AL_SEQP_MIDI_EVT */
        case 21: /* AL_CSP_NOTEOFF_EVT */
            __CSPHandleMIDIMsg(seqp, (ALEvent *)&seqp->nextEvent);
            break;
        case 7: /* AL_SEQP_META_EVT */
            __CSPHandleMetaMsg(seqp, (CompressedSequenceMetaEvent *)&seqp->nextEvent);
            break;
        case 10: /* AL_SEQP_VOL_EVT */
            seqp->vol = seqp->nextEvent.msg.spvol.vol;
            for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                alSynSetVol(seqp->drvr, &vs->voice, __vsVol((ALVoiceState *)vs, (ALSeqPlayer *)seqp),
                              __vsDelta(vs, seqp->curTime));
            }
            break;
        case 15: /* AL_SEQP_PLAY_EVT */
            if (seqp->state != 1) {
                seqp->state = 1;
                __CSPPostNextSeqEvent(seqp);
            }
            break;
        case 16: /* AL_SEQP_STOP_EVT */
            if (seqp->state == 2) {
                for (vs = seqp->vAllocHead; vs != 0; vs = seqp->vAllocHead) {
                    alSynStopVoice(seqp->drvr, &vs->voice);
                    alSynFreeVoice(seqp->drvr, &vs->voice);
                    if (vs->flags)
                        __seqpStopOsc(seqp, vs);
                    Seqplayer_ReleaseSequenceVoice((ALSeqPlayer *)seqp, &vs->voice);
                }
                seqp->state = 0;
            }
            break;
        case 17: /* AL_SEQP_STOPPING_EVT */
            if (seqp->state == 1) {
                alEvtqFlushType(&seqp->evtq, 0);
                alEvtqFlushType(&seqp->evtq, 21);
                alEvtqFlushType(&seqp->evtq, 2);
                for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
                    if ((u8)__voiceNeedsNoteKill(seqp, (s32)&vs->voice, 50000))
                        __seqpReleaseVoice(seqp, &vs->voice, 50000);
                }
                seqp->state = 2;
                evt.type = 16;
                alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, 0x7fffffff);
            }
            break;
        case 12: /* AL_SEQP_PRIORITY_EVT */
            chan = seqp->nextEvent.msg.sppriority.chan;
            seqp->chanState[chan].priority = seqp->nextEvent.msg.sppriority.priority;
            break;
        case 13: /* AL_SEQP_SEQ_EVT */
            if (seqp->state == 1)
                __assert(g_compressedSequencePlayerAssertText, g_audioCsplayerText, 295);
            seqp->target = seqp->nextEvent.msg.spseq.seq;
            __setUsptFromTempo(seqp, 500000.0f);
            if (seqp->bank)
                __initFromBank(seqp, seqp->bank);
            break;
        case 14: /* AL_SEQP_BANK_EVT */
            if (seqp->state != 0)
                __assert(g_compressedSequencePlayerAssertText, g_audioCsplayerText, 304);
            seqp->bank = seqp->nextEvent.msg.spbank.bank;
            __initFromBank(seqp, seqp->bank);
            break;
        case 4: /* AL_SEQ_END_EVT */
        case 3: /* AL_TEMPO_EVT */
        case 1: /* AL_SEQ_MIDI_EVT */
            __assert(g_compressedSequencePlayerAssertText, g_audioCsplayerText, 314);
            break;
        }
        seqp->nextDelta = alEvtqNextEvent(&seqp->evtq, (s16 *)&seqp->nextEvent);
    } while (seqp->nextDelta == 0);
    seqp->curTime += seqp->nextDelta;
    return seqp->nextDelta;
}

/** Dispatch the current object message and forward any resulting value. */
void __CSPHandleNextSeqEvent(void *rawPlayer) {
    ALSeqPlayer *sequencePlayer = rawPlayer;
    ALEvent message;
    ALEvent output;
    s32 value1;
    s32 value2;
    s32 value3;
    ALCSeq *sequence;
    s32 value;
    sequence = sequencePlayer->target;
    if (sequence != 0) {
        alCSeqNextEvent(sequence, &message);
        {
        s32 sw_message_value = (s16)((u16)message.type - 1);
        if ((unsigned int)sw_message_value > 19) {
            goto sw_message_default;
        }
        switch (sw_message_value) {
        case 0: goto sw_message_0;
        case 1: goto sw_message_default;
        case 2: goto sw_message_2;
        case 3: goto sw_message_3;
        case 4: goto sw_message_default;
        case 5: goto sw_message_default;
        case 6: goto sw_message_default;
        case 7: goto sw_message_default;
        case 8: goto sw_message_default;
        case 9: goto sw_message_default;
        case 10: goto sw_message_default;
        case 11: goto sw_message_default;
        case 12: goto sw_message_default;
        case 13: goto sw_message_default;
        case 14: goto sw_message_default;
        case 15: goto sw_message_default;
        case 16: goto sw_message_default;
        case 17: goto sw_message_17;
        case 18: goto sw_message_17;
        case 19: goto sw_message_17;
        }
    }
    do {
        sw_message_0:
            __CSPHandleMIDIMsg(sequencePlayer, &message);
            if (sequencePlayer->state == 1) {
                sequence = sequencePlayer->target;
                if (sequence != 0 && (__alCSeqNextDelta(sequence, &value1) & 0xFF)) {
                    output.type = 0;
                    value = value1;
                    goto send_value;
                }
            }
            break;
        sw_message_2:
            __CSPHandleMetaMsg(sequencePlayer, &message);
            if (sequencePlayer->state == 1) {
                sequence = sequencePlayer->target;
                if (sequence != 0 && (__alCSeqNextDelta(sequence, &value2) & 0xFF)) {
                    output.type = 0;
                    value = value2;
                    goto send_value;
                }
            }
            break;
        sw_message_3:
            sequencePlayer->state = 2;
            message.type = 0x10;
            alEvtqPostEvent(&sequencePlayer->evtq, &message, 0x7FFFFFFF);
            break;
        sw_message_17:
        sw_message_18:
        sw_message_19:
            if (sequencePlayer->state == 1) {
                sequence = sequencePlayer->target;
                if (sequence != 0 && (__alCSeqNextDelta(sequence, &value3) & 0xFF)) {
                    output.type = 0;
                    value = value3;
send_value:
                    alEvtqPostEvent(&sequencePlayer->evtq, &output,
                                  value * sequencePlayer->uspt);
                }
            }
            break;
        sw_message_default:
            __assert(g_compressedSequencePlayerAssertText, g_audioCsplayerText, 0x190);
            break;

    } while (0);
    }
}

/* Apply one compact-sequence MIDI message. The existing event storage and
 * callee-specific voice/player views share their measured O32 prefixes. */
void __CSPHandleMIDIMsg(void *object, ALEvent *message)
{
    ALSeqPlayer *seqp = object;
    ALEvent *event = (ALEvent *)message;
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
            f32 pitch, oscValue, initialOscValue;
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
            alSynAllocVoice(seqp->drvr, (ALVoice *)voice, &config);
            vstate->sound = sound;
            vstate->envPhase = 0;
            if (seqp->chanState[chan].sustain > 63)
                vstate->phase = 2;
            else
                vstate->phase = 0;
            cents = (key - sound->keyMap->keyBase) * 100 + sound->keyMap->detune;
            vstate->pitch = alCents2Ratio(cents);
            initialOscValue = g_compressedSequenceInitialOscillatorValue;
            vstate->envGain = sound->envelope->attackVolume;
            vstate->envEndTime = seqp->curTime + sound->envelope->attackTime;
            vstate->flags = 0;
            inst = seqp->chanState[chan].instrument;
            oscValue = initialOscValue;
            if (inst->tremType) {
                if (seqp->initOsc) {
                    deltaTime = (*seqp->initOsc)(&oscState, &oscValue, inst->tremType,
                                                 inst->tremRate, inst->tremDepth, inst->tremDelay);
                    if (deltaTime) {
                        evt.type = 22; /* AL_TREM_OSC_EVT */
                        evt.msg.osc.vs = vstate;
                        evt.msg.osc.oscState = oscState;
                        alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime);
                        vstate->flags |= 0x01;
                    }
                }
            }
            tremeloSlot = &vstate->tremelo;
            if (!(oscValue >= g_compressedSequenceOscillatorMinimum)) {
                tremelo = (s32)oscValue;
            } else {
                tremelo = (s32)(oscValue - g_compressedSequenceOscillatorMinimum);
                tremelo |= 0x80000000;
            }
            initialOscValue = g_compressedSequenceFallbackOscillatorValue;
            *tremeloSlot = tremelo;
            oscValue = initialOscValue;
            if (inst->vibType) {
                if (seqp->initOsc) {
                    deltaTime = (*seqp->initOsc)(&oscState, &oscValue, inst->vibType,
                                                 inst->vibRate, inst->vibDepth, inst->vibDelay);
                    if (deltaTime) {
                        evt.type = 23; /* AL_VIB_OSC_EVT */
                        evt.msg.osc.vs = vstate;
                        evt.msg.osc.oscState = oscState;
                        evt.msg.osc.chan = chan;
                        alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime);
                        vstate->flags |= 0x02;
                    }
                }
            }
            vstate->vibrato = oscValue;
            pitch = vstate->pitch * seqp->chanState[chan].pitchBend * vstate->vibrato;
            fxmix = seqp->chanState[chan].fxmix;
            pan = __vsPan(vstate, seqp);
            vol = __vsVol((ALVoiceState *)vstate, (ALSeqPlayer *)seqp);
            deltaTime = sound->envelope->attackTime;
            alSynStartVoiceParams(seqp->drvr, (ALVoice *)voice, sound->wavetable, pitch, vol, pan, fxmix, deltaTime);
            evt.type = 6; /* AL_SEQP_ENV_EVT */
            evt.msg.vol.voice = voice;
            evt.msg.vol.vol = sound->envelope->decayVolume;
            evt.msg.vol.delta = sound->envelope->decayTime;
            alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime);
            if (midi->duration) {
                evt.type = 21; /* AL_CSP_NOTEOFF_EVT */
                evt.msg.midi.status = chan | 0x80;
                evt.msg.midi.byte1 = key;
                evt.msg.midi.byte2 = 0;
                deltaTime = seqp->uspt * midi->duration;
                alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime);
            }
            break;
        }
    case 0x80: /* AL_MIDI_NoteOff */
        vstate = (ALVoiceState *)__lookupVoice((ALSeqPlayer *)seqp, key, chan);
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
        vstate = (ALVoiceState *)__lookupVoice((ALSeqPlayer *)seqp, key, chan);
        if (!vstate)
            return;
        vstate->velocity = byte2;
        alSynSetVol(seqp->drvr, &vstate->voice, __vsVol((ALVoiceState *)vstate, (ALSeqPlayer *)seqp),
                      __vsDelta(vstate, seqp->curTime));
        break;
    case 0xD0: /* AL_MIDI_ChannelPressure */
        for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
            if (vs->channel == chan) {
                vs->velocity = byte1;
                alSynSetVol(seqp->drvr, &vs->voice, __vsVol((ALVoiceState *)vs, (ALSeqPlayer *)seqp),
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
                    vol = __vsVol((ALVoiceState *)vs, (ALSeqPlayer *)seqp);
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
        default:
            break;
        }
        break;
    case 0xC0: /* AL_MIDI_ProgramChange */
        if (seqp->bank == 0)
            __assert(g_compressedSequencePlayerAssertText, g_audioCsplayerText, 711);
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

void __CSPHandleMetaMsg(void *sequencePlayer, CompressedSequenceMetaEvent *metaEvent) {
    s32 padding[4];
    s32 total = 0;
    CompressedSequenceEventNode *head = 0;
    s32 scale;
    CompressedSequenceEventNode *node;
    CompressedSequenceEventNode *next;
    if (metaEvent->status == 0xFF) {
        if (metaEvent->metaType != 0x51) {
            return;
        }
        scale = ((CompressedSequenceTempoAndQueueView *)(sequencePlayer))->uspt;
        __setUsptFromTempo(sequencePlayer,
                      (f32)((metaEvent->tempoHigh << 16) | (metaEvent->tempoMid << 8) | metaEvent->tempoLow));
        node = ((struct CompressedSequenceAllocatedEventsView *) ((char *) sequencePlayer))->link;
        while (node != 0) {
            next = ((struct CompressedSequenceEventLink *) ((char *) node))->link;
            total += node->value;
            if (node->type == 0x15) {
                s32 node_total;
                alUnlink((ListLink *)node);
                if (head != 0) {
                    alLink(node, head);
                } else {
                    head = node;
                    node->prev = 0;
                    node->next = 0;
                }
                node_total = total;
                if (next != 0) {
                    total -= node->value;
                    next->value += node->value;
                }
                node->value = node_total;
            }
            node = next;
        }
        node = head;
        while (node != 0) {
            next = node->prev;
            node->value = (node->value / scale) * ((CompressedSequenceTempoAndQueueView *)(sequencePlayer))->uspt;
            __CSPRepostEvent(&((CompressedSequenceTempoAndQueueView *)(sequencePlayer))->evtq, node);
            node = next;
        }
    }
}

void __CSPPostNextSeqEvent(void *sequencePlayer) {
    ALSeqPlayer *player = sequencePlayer;
    ALEvent event;
    s32 result;
    ALCSeq *sequence;

    if (player->state == 1) {
        sequence = player->target;
        if (sequence != 0 && (__alCSeqNextDelta(sequence, &result) & 0xFF)) {
            event.type = 0;
            alEvtqPostEvent(&player->evtq, &event, result * player->uspt);
        }
    }
}

void __CSPRepostEvent(void *eventQueue, CompressedSequenceEventNode *repostedEvent) {
    CompressedSequenceEventQueueHead *object = eventQueue;
    s32 saved;
    CompressedSequenceEventNode **link;
    CompressedSequenceEventNode *node;
    s32 value;
    s32 node_value;

    saved = osSetIntMask(1);
    link = &object->allocatedEvents;
    if (link != 0) {
loop:
        node = *link;
        if (node == 0) {
            goto insert;
        }
        value = repostedEvent->value;
        node_value = node->value;
        if (value < node_value) {
            node->value = node_value - value;
insert:
            alLink(repostedEvent, link);
            goto done;
        }
        repostedEvent->value = value - node_value;
        link = (CompressedSequenceEventNode **)*link;
        if (link != 0) {
            goto loop;
        }
    }
done:
    osSetIntMask(saved);
}

void __setUsptFromTempo(void *sequencePlayer, f32 microsecondsPerQuarter) {
    ALSeqPlayer *player = sequencePlayer;
    ALCSeq *targetValue;

    targetValue = player->target;
    if (targetValue != 0) {
        player->uspt = (s32)(microsecondsPerQuarter * targetValue->qnpt);
        return;
    }
    player->uspt = 0x1E8;
}

#if !(defined(VERSION_US_REV1))
const unsigned int k_CsplayerEncodedWords[3] = {
    0x42FE0000, 0x4F000000, 0x3F800000,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g___CSPHandleMIDIMsgConstantWords_Csplayer.c */
const unsigned int g___CSPHandleMIDIMsgConstantWords[3] = {
    0x42FE0000, 0x4F000000, 0x3F800000,
};
#endif
