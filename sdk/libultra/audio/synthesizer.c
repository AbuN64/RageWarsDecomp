#include "COMMON/ALFXPARAM.H"
#include <PR/abi.h>
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/STATERECAT34.H"
#include "COMMON/ALAUXBUS_S.H"
#include "../../include/libultra/audio/synthesizer.h"
#include "TYPES.H"
#include "../../include/libgultra_inferred/__NEXTSAMPLETIME.H"
#include "../../include/libgultra/alunlink.h"
#include "../../include/al_globals.h"
#include "../../include/libgultra.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "include_asm.h"
#include "COMMON/OSPIHANDLE_S.H"
#include "../../include/libultra/debug/assert.h"


       /* alHeapDBAlloc */
extern void alSaveNew(ALSave *);

                             /* alSaveNew */
extern void alAuxBusNew(ALAuxBus_s *, void *, s32);

              /* alAuxBusNew */
extern void alMainBusNew(ALMainBus_s *, void *, s32);

             /* alMainBusNew */


 /* alSynAllocFX */
extern s32 alMainBusParam(void *, s32, void *);

                   /* alMainBusParam */


                   /* alLink */
extern void alLoadNew(ALLoadFilter *, ALDMANew, ALHeap *);

   /* alLoadNew */

                   /* alLoadParam */
extern void alResampleNew(ALResampler *, ALHeap *);

              /* alResampleNew */
extern s32 alResampleParam(void *, s32, void *);

                   /* alResampleParam */
extern void alEnvmixerNew(ALEnvMixer4C *, ALHeap *);

               /* alEnvmixerNew */

                   /* alEnvmixerParam */
extern s32 alAuxBusParam(void *, s32, void *);

                   /* alAuxBusParam */
extern s32 alSaveParam(void *, s32, ALFilter_s14 *);

 /* alGlobals */

s32 _timeToSamplesNoRound(SynthOutputRateView *synth, s32 microseconds);

         /* _timeToSamplesNoRound */
void _collectPVoices(void *synth);


                   /* alSaveParam */

void alSynNew(ALSynth *drvr, ALSynConfig *c)
{
    s32 i;
    PVoice_s *pv;
    PVoice_s *pvoices;
    ALHeap *hp = c->heap;
    ALSave *save;
    ALFilter_s14 *sources;
    ALParam_s1C *params;
    ALParam_s1C *paramPtr;

    drvr->head = 0;
    drvr->numPVoices = c->maxPVoices;
    drvr->curSamples = 0;
    drvr->paramSamples = 0;
    drvr->outputRate = c->outputRate;
    drvr->maxOutSamples = 160;
    drvr->dma = (ALDMANew)c->dmaproc;

    save = alHeapDBAlloc(0, 0, hp, 1, sizeof(ALSave));
    alSaveNew(save);
    drvr->outputFilter = (ALFilter_s14 *)save;

    drvr->auxBus = alHeapDBAlloc(0, 0, hp, 1, sizeof(ALAuxBus_s));
    drvr->maxAuxBusses = 1;
    sources = alHeapDBAlloc(0, 0, hp, c->maxPVoices, sizeof(ALFilter_s14 *));
    alAuxBusNew(drvr->auxBus, sources, c->maxPVoices);

    drvr->mainBus = alHeapDBAlloc(0, 0, hp, 1, sizeof(ALMainBus_s));
    sources = alHeapDBAlloc(0, 0, hp, c->maxPVoices, sizeof(ALFilter_s14 *));
    alMainBusNew(drvr->mainBus, sources, c->maxPVoices);

    if (c->fxType != 0) {
        alSynAllocFX(drvr, 0, c, hp);
    } else
        alMainBusParam(drvr->mainBus, 2, &drvr->auxBus[0]); /* AL_FILTER_ADD_SOURCE */

    drvr->pFreeList.next = 0;
    drvr->pFreeList.prev = 0;
    drvr->pLameList.next = 0;
    drvr->pLameList.prev = 0;
    drvr->pAllocList.next = 0;
    drvr->pAllocList.prev = 0;

    pvoices = alHeapDBAlloc(0, 0, hp, c->maxPVoices, sizeof(PVoice_s));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink((ListLink *)pv, &drvr->pFreeList);
        pv->vvoice = 0;

        alLoadNew(&pv->decoder, drvr->dma, hp);
        alLoadParam(&pv->decoder, 1, 0); /* AL_FILTER_SET_SOURCE */

        alResampleNew(&pv->resampler, hp);
        alResampleParam(&pv->resampler, 1, &pv->decoder);

        alEnvmixerNew(&pv->envmixer, hp);
        alEnvmixerParam(&pv->envmixer, 1, &pv->resampler);

        alAuxBusParam(drvr->auxBus, 2, &pv->envmixer);

        pv->channelKnob = (ALFilter_s14 *)&pv->envmixer;
    }

    alSaveParam(save, 1, drvr->mainBus);

    params = alHeapDBAlloc(0, 0, hp, c->maxUpdates, sizeof(ALParam_s1C));
    drvr->paramList = 0;
    for (i = 0; i < c->maxUpdates; i++) {
        paramPtr = &params[i];
        paramPtr->next = drvr->paramList;
        drvr->paramList = paramPtr;
    }
    drvr->heap = hp;
}

             /* _collectPVoices */

Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen)
{
    ALPlayer_s14 *client;
    ALFilter_sC *output;
    ALSynth4C *drvr = &g_audioGlobals->drvr;
    s16 tmp = 0;
    Acmd *cmdlEnd = cmdList;
    Acmd *cmdPtr;
    s32 nOut;
    s16 *lOutBuf = outBuf;

    if (drvr->head == 0) {
        *cmdLen = 0;
        return cmdList;
    }

    for (drvr->paramSamples = __nextSampleTime(drvr, &client);
         drvr->paramSamples - drvr->curSamples < outLen;
         drvr->paramSamples = __nextSampleTime(drvr, &client)) {
        drvr->paramSamples &= ~0xf;
        client->samplesLeft += _timeToSamplesNoRound(drvr, (*client->handler)(client));
    }
    drvr->paramSamples &= ~0xf;

    while (outLen > 0) {
        nOut = ((drvr->maxOutSamples) < (outLen) ? (drvr->maxOutSamples) : (outLen));

        cmdPtr = cmdlEnd;
        aSegment(cmdPtr++, 0, 0);

        output = drvr->outputFilter;
        (*output->setParam)(output, 6, lOutBuf); /* AL_FILTER_SET_DRAM */
        cmdlEnd = (*output->handler)(output, &tmp, nOut, drvr->curSamples, cmdPtr);

        outLen -= nOut;
        lOutBuf += nOut << 1;
        drvr->curSamples += nOut;
    }

    *cmdLen = (s32)(cmdlEnd - cmdList);
    _collectPVoices(drvr);
    return cmdlEnd;
}

void *__allocParam(void) {
    void *head;
    void *param;

    head = g_audioGlobals->drvr.paramList;
    param = 0;
    if (head != 0) {
        param = head;
        g_audioGlobals->drvr.paramList = *(void **)param;
        *(void **)param = 0;
    }
    return param;
}

void __freeParam(void *parameterStorage) {
    struct ALParam_s1C *parameter = parameterStorage;
    ALGlobals *head = g_audioGlobals;
    parameter->next = head->drvr.paramList;
    head->drvr.paramList = parameterStorage;
}

void _freePVoice(s32 synth, s32 listLink) {
    alUnlink((ListLink *)listLink);
    alLink(listLink, synth + 0x14);
}

void _collectPVoices(void *synth) {
    void *node;

    node = ((ALSynth4C *)synth)->pLameList.next;
    if (node != 0) {
        do {
            alUnlink(node);
            alLink(node, (char *)synth + 4);
            node = ((ALSynth4C *)synth)->pLameList.next;
        } while (node != 0);
    }
}

s32 _timeToSamples(SynthOutputRateView *synth, s32 microseconds) {
    f32 v;
    int idx;

    v = (f32)microseconds * (f32)synth->outputRate;
    idx = 0;
    v = v * g_audioRoundedSampleTimeConstants[idx];
    v = v + g_audioRoundedSampleTimeConstants[1];
    return (s32)v & ~0xF;
}

extern char g_synthesizerNoClientAssertText;

extern char s_audioSynthesizerText;


s32 __nextSampleTime(ALSynth4C *drvr, ALPlayer_s14 **client) {
 s32 smallest = 0x7FFFFFFF;
 ALPlayer_s14 *scan;
 if (drvr->head == 0) __assert(&g_synthesizerNoClientAssertText, &s_audioSynthesizerText, 0x133);
 *client = 0;
 scan = drvr->head;
 if (scan != 0) {
  do {
   if (scan->samplesLeft - drvr->curSamples < smallest) {
    *client = scan;
    smallest = scan->samplesLeft - drvr->curSamples;
   }
   scan = scan->next;
  } while (scan != 0);
 }
 return (*client)->samplesLeft;
}

s32 _timeToSamplesNoRound(SynthOutputRateView *synth, s32 microseconds) {
    f32 v;
    int idx;

    v = (f32)microseconds * (f32)synth->outputRate;
    idx = 0;
    v = v * g_audioSampleTimeConstants[idx];
    v = v + g_audioSampleTimeConstants[1];
    return (s32)v;
}


