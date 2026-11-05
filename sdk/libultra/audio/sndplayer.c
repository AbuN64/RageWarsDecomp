#include "../../include/libgultra.h"
#include "Common/audio_callbacks.h"
#include "Common/runtime_declarations.h"
#include "Common/albank_s.h"
#include "Common/sound_player_parameter_events.h"
#include "Common/contreadformat.h"
#include "types.h"
#include "../../include/libgultra/_DIVS32BYF32.H"
#include "include_asm.h"
#include "../../include/EXTERNS.H"
#include "Common/triple.h"
#include "../../include/libgultra/alunlink.h"
#include "../../include/libultra/debug/assert.h"
#include "Data/rest_source_records.h"
#include "Common/alfxparam.h"

/* sndplayer.c */
extern int _sndpVoiceHandler_Address(void *soundPlayer);
#if defined(VERSION_US_REV1)
#define SNDP_MIN_PITCH g_soundPlayerMinPitch
#define SNDP_ASSERT_TEXT g_soundPlayerAssertText
#define SNDP_SOURCE_TEXT g_audioSndplayerSourceText
#else
#define SNDP_MIN_PITCH g_soundPlayerMinPitch
#define SNDP_ASSERT_TEXT g_soundPlayerAssertText
#define SNDP_SOURCE_TEXT s_audioSndplayerText
#endif

/* alSndpNew, drafted from ultralib src/audio/sndplayer.c: sets up a sound player from its config,
   allocating the sound states and event items from the heap, registers its voice handler with the
   global synthesizer and posts the first frame API event. */

extern ALGlobalsalSndpNew *g_audioGlobals;

 /* alGlobals */

          /* alHeapDBAlloc */

  /* alEvtqNew */

                   /* alSynAddPlayer */

          /* alEvtqPostEvent */
extern s32 alEvtqNextEvent(ALEventQueue *, ALEvent *);

                /* alEvtqNextEvent */
/* _sndpVoiceHandler (_sndpVoiceHandler); the cartridge stores the handler by its 0x002B7C8C address. */

 /* alSynAllocVoice */

         /* alSynStartVoice */

             /* alSynSetPan */

       /* alSynSetVol */

            /* alSynSetPitch */

             /* alSynSetFXMix */

                 /* alSynStopVoice */

       /* alEvtqPostEvent */

void alSndpNew(ALSndPlayer *sndp, ALSndpConfig *c)
{
    u8 *ptr;
    ALEvent evt;
    ALSoundState *sState;
    u32 i;

    sndp->maxSounds = c->maxSounds;
    sndp->target = -1;
    sndp->frameTime = 16000;
    sState = (ALSoundState *)alHeapDBAlloc(0, 0, c->heap, 1, c->maxSounds * sizeof(ALSoundState));
    sndp->sndState = sState;

    for (i = 0; i < c->maxSounds; i++)
        sState[i].sound = 0;

    ptr = alHeapDBAlloc(0, 0, c->heap, 1, c->maxEvents * sizeof(ALEventListItem));
    alEvtqNew(&sndp->evtq, (ALEventListItem *)ptr, c->maxEvents);

    sndp->drvr = &g_audioGlobals->drvr;

    sndp->node.next = 0;
    sndp->node.handler = _sndpVoiceHandler_Address;
    sndp->node.clientData = sndp;
    alSynAddPlayer(sndp->drvr, &sndp->node);

    evt.type = 5; /* AL_SNDP_API_EVT */
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
    sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);
}

       /* _removeEvents */

void _handleEvent(ALSndPlayer *sndp, ALSndpEvent *event)
{
    ALVoiceConfig vc;
    ALSound *snd;
    ALVoice *voice;
    u8 pan;
    f32 pitch;
    ALSndpEvent evt;
    s32 delta;
    s16 vol;
    s16 tmp;
    s32 vtmp;
    ALSoundState *state;
    const ALSndpEventhandleEvent *event_view =
        (const ALSndpEventhandleEvent *)event;

    state = event->common.state;
    snd = state->sound;

    switch (event->msg.type) {
        case 0: /* AL_SNDP_PLAY_EVT */
            if (state->state != 0 || !snd)
                return;
            vc.fxBus = 0;
            vc.priority = state->priority;
            vc.unityPitch = 0;
            voice = &state->voice;
            alSynAllocVoice(sndp->drvr, voice, &vc);
            vol = (s16)((s32)snd->envelope->attackVolume * state->vol / 127);
            tmp = state->pan - 64 + ((const ALSound *)snd)->samplePan;
            tmp = ((tmp) > (0) ? (tmp) : (0));
            pan = (u8)((tmp) < (127) ? (tmp) : (127));
            pitch = state->pitch;
            delta = snd->envelope->attackTime;
            alSynStartVoice(sndp->drvr, voice, snd->wavetable);
            state->state = 1;
            alSynSetPan(sndp->drvr, voice, pan);
            alSynSetVol(sndp->drvr, voice, vol, delta);
            alSynSetPitch(sndp->drvr, voice, pitch);
            alSynSetFXMix(sndp->drvr, voice, state->fxMix);
            evt.common.type = 6; /* AL_SNDP_DECAY_EVT */
            evt.common.state = state;
            delta = (s32)_DivS32ByF32(snd->envelope->attackTime, state->pitch);
            alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
            break;

        case 1: /* AL_SNDP_STOP_EVT */
            if (state->state != 1 || !snd)
                return;
            delta = (s32)_DivS32ByF32(snd->envelope->releaseTime, state->pitch);
            alSynSetVol(sndp->drvr, &state->voice, 0, delta);
            if (delta) {
                evt.common.type = 7; /* AL_SNDP_END_EVT */
                evt.common.state = state;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
                state->state = 2;
            } else {
                alSynStopVoice(sndp->drvr, &state->voice);
                alSynFreeVoice(sndp->drvr, &state->voice);
                _removeEvents(&sndp->evtq, state);
                state->state = 0;
            }
            break;

        case 2: /* AL_SNDP_PAN_EVT */
            state->pan = event_view->pan.pan;
            if (state->state == 1 && snd) {
                tmp = state->pan - 64 + ((const ALSound *)snd)->samplePan;
                tmp = ((tmp) > (0) ? (tmp) : (0));
                pan = (u8)((tmp) < (127) ? (tmp) : (127));
                alSynSetPan(sndp->drvr, &state->voice, pan);
            }
            break;

        case 4: /* AL_SNDP_PITCH_EVT */
            {
                f32 min = SNDP_MIN_PITCH;
                if ((state->pitch = event_view->pitch.pitch) < min)
                    state->pitch = min;
            }
            if (state->state == 1) {
                alSynSetPitch(sndp->drvr, &state->voice, state->pitch);
            }
            break;

        case 8: /* AL_SNDP_FX_EVT */
            state->fxMix = event_view->fx.mix;
            if (state->state == 1)
                alSynSetFXMix(sndp->drvr, &state->voice, state->fxMix);
            break;

        case 3: /* AL_SNDP_VOL_EVT */
            state->vol = event_view->vol.vol;
            if (state->state == 1 && snd) {
                vtmp = snd->envelope->decayVolume * state->vol / 127;
                alSynSetVol(sndp->drvr, &state->voice, (s16)vtmp, 1000);
            }
            break;

        case 6: /* AL_SNDP_DECAY_EVT */
            if (snd->envelope->decayTime != -1) {
                vtmp = snd->envelope->decayVolume * state->vol / 127;
                delta = (s32)_DivS32ByF32(snd->envelope->decayTime, state->pitch);
                alSynSetVol(sndp->drvr, &state->voice, (s16)vtmp, delta);
                evt.common.type = 1; /* AL_SNDP_STOP_EVT */
                evt.common.state = state;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
            }
            break;

        case 7: /* AL_SNDP_END_EVT */
            alSynStopVoice(sndp->drvr, &state->voice);
            alSynFreeVoice(sndp->drvr, &state->voice);
            _removeEvents(&sndp->evtq, state);
            state->state = 0;
            break;

        default:
            break;
    }
}

/* _sndpVoiceHandler, drafted from ultralib src/audio/sndplayer.c: the sound player's synthesizer
   callback; reposts the frame API event or handles the pending event until the next one is in
   the future, then advances the player's time by that delta. The pointer to the pending event
   is held in a local, standing in for the address register -fforce-addr kept for it. */

   /* _handleEvent */
       /* alEvtqNextEvent */

s32 _sndpVoiceHandler(void *node)
{
    ALSndPlayer *sndp = (ALSndPlayer *)node;
    ALSndpEvent evt;
    ALSndpEvent *next = (ALSndpEvent *)&sndp->nextEvent;

    do {
        switch (sndp->nextEvent.type) {
            case 5: /* AL_SNDP_API_EVT */
                evt.common.type = 5;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
                break;
            default:
                _handleEvent(sndp, next);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);
    } while (sndp->nextDelta == 0);

    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}

void _removeEvents(ALEventQueue *eventQueue, void *soundState) {
    s32 saved;
    ALEventListItem *cur;
    ALEventListItem *next;

    saved = osSetIntMask(1);
    cur = (ALEventListItem *)eventQueue->allocList.next;
    if (cur != 0) {
        do {
            next = (ALEventListItem *)cur->node.next;
            if (((ALSndpEvent *)&cur->evt)->common.state == soundState) {
                if (next != 0) {
                    next->delta = next->delta + cur->delta;
                }
                alUnlink(cur);
                alLink(cur, eventQueue);
            }
            cur = next;
        } while (cur != 0);
    }
    osSetIntMask(saved);
}

s32 _DivS32ByF32(s32 val, f32 div) {
    f32 fval;
    f64 dresult;
    s32 result;

    if (div == 0.0f) {
        __assert(SNDP_ASSERT_TEXT, SNDP_SOURCE_TEXT, 0x11D);
    }

    result = 0x7FFFFFFF;
    fval = (f32)val / div;
    dresult = (f64)fval;
    if (!(g_soundPlayerDelayConversionLimit < dresult)) {
        result = (s32)dresult;
    }
    return result;
}

/* The rodata literals the voice handler and _DivS32ByF32 read, after the _handleEvent jump table:
   the 0.0001f pitch floor, the assert expression text and the source path of the assert. */
#if defined(VERSION_US_REV1)
const f32 g_soundPlayerMinPitch = 0.0001f;
const char g_soundPlayerAssertText[] = "EX";
const char g_audioSndplayerSourceText[] = "audio/sndplayer.c";
#else
const f32 g_soundPlayerMinPitch = 0.0001f;
const char g_soundPlayerAssertText[] = "EX";
const char s_audioSndplayerText[] = "audio/sndplayer.c";
#endif

#if defined(VERSION_EU_X)
/* Zero word ending the sndplayer object; no instruction reads it. */
unsigned int g_divS32ByF32ZeroTail[1] = {
    0x00000000,
};
#endif

/* SP.CPP */
/* 802BE040_32.CPP */

/* 802BE040_44.CPP */
/* 802BE040_44.CPP */

/* SpZeroWordsUnit.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: zero word after _DivS32ByF32 */
unsigned int k_SpZeroWords[1] = {
    0x00000000,
};
#endif

/* SpStoreWordUnit.CPP */

/* SNDPLAYER_DATA.CPP */
/* ROM-grounded data: src/k_sndplayerIntegerLimit_SndplayerData.c */
const RestAudioFourByteDoubleConstant k_sndplayerIntegerLimit = { 2147483647.0 };

#if defined(VERSION_US)
char s_SndplayerTOptiText[8] =
    "t\011m_Opti";
#endif

#if defined(VERSION_EU)
extern char Weapon_FireStateEnterCallbackEntry[];
void *k_sndplayerFireStateCaseAddresses[2] = {
    (void *)(Weapon_FireStateEnterCallbackEntry + 1120), (void *)(Weapon_FireStateEnterCallbackEntry + 1120),
};
#endif

#if defined(VERSION_DE)
char s_SndplayerOSyntheText[8] =
    "o/synthe";
#endif
