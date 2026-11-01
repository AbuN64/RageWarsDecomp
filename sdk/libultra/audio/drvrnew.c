#include "../../include/libgultra.h"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ALAUXBUS_S.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "COMMON/TRIPLE.H"
#include "../../include/libgultra_inferred/ALFILTERNEW.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "include_asm.h"

/* alFxNew, drafted from ultralib src/audio/drvrnew.c: initialise the effect filter, pick the
   parameter table for the configured effect type, allocate the delay line and its sections, and
   give each section its optional resampler and low-pass filter. init_lpfilter's body is written
   out where the library's -O3 inlined it, against this function's own cartridge constants (a
   static inline helper kept 16384.0 in the inner loop instead of hoisting it into f20); the
   parameter tables are the cartridge's g_audioSmallRoomParameters..g_audioNoEffectParameters and the unsigned length
   conversion is written out in GCC's order. */



        /* alFilterNew */


 /* alHeapDBAlloc */

extern char alFxParam_Address;

 /* alFxParam */
extern char alFxPull_Address;

 /* alFxPull */
extern char alFxParamHdl_Address;

 /* alFxParamHdl */

extern s32 g_audioSmallRoomParameters[];

 /* SMALLROOM_PARAMS */
extern s32 g_audioBigRoomParameters[];

 /* BIGROOM_PARAMS */
extern s32 g_audioEchoParameters[];

 /* ECHO_PARAMS */
extern s32 g_audioChorusParameters[];

 /* CHORUS_PARAMS */
extern s32 g_audioFlangeParameters[];

 /* FLANGE_PARAMS */
extern s32 g_audioNoEffectParameters[];

 /* NULL_PARAMS */

 /* 16384.0 */
extern const f32 g_effectResampleIncrementScale;

 /* 1 / 1000 */

 /* 2^32 */
extern const f32 g_effectResampleDepthScale;

typedef s32 (*FuncPtr)(void *);




 /* 1 / 173123.404906676 */

 /* 1.0f */

 /* 1.0 / 16384 */

void alFxNew(ALFx *r, ALSynConfig *c, ALHeap *hp)
{
    u16 i, j, k;
    s32 *param = 0;
    ALFilter_s14 *f = &r->filter;
    ALDelay28 *d;

    alFilterNew(f, 0, (s32)&alFxParam_Address, 5);
    f->handler = &alFxPull_Address;
    r->paramHdl = &alFxParamHdl_Address;

    switch (c->fxType) {
      case 1: param = g_audioSmallRoomParameters; break;
      case 2: param = g_audioBigRoomParameters; break;
      case 5: param = g_audioEchoParameters; break;
      case 3: param = g_audioChorusParameters; break;
      case 4: param = g_audioFlangeParameters; break;
      case 6: param = c->params; break;
      default: param = g_audioNoEffectParameters; break;
    }

    j = 0;

    r->section_count = param[j++];
    r->length = param[j++];

    r->delay = (void *)alHeapDBAlloc(0, 0, hp, r->section_count, sizeof(ALDelay28));
    r->base = (void *)alHeapDBAlloc(0, 0, hp, r->length, sizeof(s16));
    r->input = r->base;

    for (k = 0; k < r->length; k++)
        r->base[k] = 0;

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        d->input = param[j++];
        d->output = param[j++];
        d->fbcoef = param[j++];
        d->ffcoef = param[j++];
        d->gain = param[j++];

        if (param[j]) {
            s32 length;
            f64 flength;
            f32 rsinc;
            f32 depth;

            rsinc = (f32)param[j++] * g_effectResampleIncrementScale;
            d->rsinc = (rsinc + rsinc) / c->outputRate;

            depth = (f32)param[j++];
            length = d->output - d->input;
            flength = length;
            if (length < 0)
                flength += g_effectDelayLengthUnsignedBias;
            d->rsgain = depth * ((f32)flength * g_effectResampleDepthScale);
            d->rsval = g_effectResamplerInitialValue;
            d->rsdelta = 0;
            d->rs = (void *)alHeapDBAlloc(0, 0, hp, 1, sizeof(struct ALResampler_s));
            ((struct ALResampler_s *)d->rs)->state = (void *)alHeapDBAlloc(0, 0, hp, 1, 32);
            ((struct ALResampler_s *)d->rs)->delta = 0;
            ((struct ALResampler_s *)d->rs)->first = 1;
        } else {
            d->rs = 0;
            j++;
            j++;
        }

        if (param[j]) {
            d->lp = (void *)alHeapDBAlloc(0, 0, hp, 1, sizeof(struct AudioLowPassFilter));
            ((struct AudioLowPassFilter *)d->lp)->state = (void *)alHeapDBAlloc(0, 0, hp, 1, sizeof(AudioPoleFilterState));
            ((struct AudioLowPassFilter *)d->lp)->cutoff = param[j++];
            {
                struct AudioLowPassFilter *lp = d->lp;
                s32 n, temp;
                s16 fc;
                f64 ffc, fcoef;

                temp = lp->cutoff * 16384;
                fc = temp >> 15;
                lp->gain = 16384 - fc;

                lp->first = 1;
                for (n = 0; n < 8; n++)
                    lp->coefficients.taps[n] = 0;

                lp->coefficients.taps[n++] = fc;
                fcoef = ffc = (f64)fc * g_effectLowPassCoefficientScale;

                for (; n < 16; n++) {
                    fcoef *= ffc;
                    lp->coefficients.taps[n] = (s16)(fcoef * 16384.0);
                }
            }
        } else {
            d->lp = 0;
            j++;
        }
    }
}

void alLoadNew(void *loadFilter, FuncPtr createDma, s32 heap) {
    alFilterNew(loadFilter, &alAdpcmPull_Address, &alLoadParam_Address, 0);
    ((ALLoadFilter48_2 *)loadFilter)->state = alHeapDBAlloc(0, 0, heap, 1, 0x20);
    ((ALLoadFilter48_2 *)loadFilter)->lstate = alHeapDBAlloc(0, 0, heap, 1, 0x20);
    ((ALLoadFilter48_2 *)loadFilter)->dma = createDma(&((ALLoadFilter48_2 *)loadFilter)->dmaState);
    ((ALLoadFilter48_2 *)loadFilter)->lastsam = 0;
    ((ALLoadFilter48_2 *)loadFilter)->first = 1;
    ((ALLoadFilter48_2 *)loadFilter)->memin = 0;
}

void alMainBusNew(void *busFilter, s32 maxSources, s32 sources) {
    alFilterNew(busFilter, (s32) &alMainBusPull_Address, (s32) &alMainBusParam_Address, 7);
    (((struct TextLayerRect *) ((s8 *) busFilter))->x) = 0;
    (((struct TextLayerRect *) ((s8 *) busFilter))->right) = sources;
    (((struct TextLayerRect *) ((s8 *) busFilter))->y) = maxSources;
}

void alAuxBusNew(void *busFilter, s32 maxSources, s32 sources) {
    alFilterNew(busFilter, (s32) &alAuxBusPull_Address, (s32) &alAuxBusParam_Address, 6);
    (((struct TextLayerRect *) ((s8 *) busFilter))->x) = 0;
    (((struct TextLayerRect *) ((s8 *) busFilter))->right) = sources;
    (((struct TextLayerRect *) ((s8 *) busFilter))->y) = maxSources;
}


void alResampleNew(ALResampler_s *resampler, s32 heap) {
    s32 result;
    f32 k;

    alFilterNew(resampler, &alResamplePull_Address, &alResampleParam_Address, 1);
    result = alHeapDBAlloc(0, 0, heap, 1, 0x20);
    k = g_resamplerInitialRatio;
    resampler->state = (void *)result;
    resampler->delta = 0;
    resampler->first = 1;
    resampler->motion = 0;
    resampler->upitch = 0;
    resampler->ctrlList = 0;
    resampler->ctrlTail = 0;
    resampler->ratio = k;
}

void alSaveNew(ALSave *saveFilter) {
    alFilterNew(saveFilter, (s32) &alSavePull_Address, (s32) &alSaveParam_Address, 3);
    saveFilter->dramout = 0;
    saveFilter->first = 1;
}

extern char alEnvmixerPull_Address, alEnvmixerParam_Address;

void alEnvmixerNew(ALEnvMixer *envelopeMixer, ALHeap *heap) {
    s32 result;
    ALEnvMixer *mixer = envelopeMixer;

    alFilterNew(envelopeMixer, &alEnvmixerPull_Address, &alEnvmixerParam_Address, 4);
    result = alHeapDBAlloc(0, 0, heap, 1, 0x50);
    mixer->state = (void *)result;
    mixer->first = 1;
    mixer->motion = 0;
    mixer->volume = 1;
    mixer->ltgt = 1;
    mixer->rtgt = 1;
    mixer->cvolL = 1;
    mixer->cvolR = 1;
    mixer->dryamt = 0;
    mixer->wetamt = 0;
    mixer->lratm = 1;
    mixer->lratl = 0;
    mixer->lratm = 1;
    mixer->lratl = 0;
    mixer->delta = 0;
    mixer->segEnd = 0;
    mixer->pan = 0;
    mixer->ctrlList = 0;
    mixer->ctrlTail = 0;
    mixer->sources = 0;
}

/* _init_lpfilter, drafted from ultralib src/audio/drvrnew.c: derive the low-pass filter's gain and
   its sixteen coefficients from the configured cutoff. This object carries its own copies of the
   1/16384 and 16384.0 double constants, at g_lowPassCoefficientScale and g_lowPassFixedPointScale, distinct from the copies the
   inlined body in alFxNew uses. */


void init_lpfilter(AudioLowPassFilter *lp)
{
    s32 i, temp;
    s16 fc;
    f64 ffc, fcoef;

    temp = lp->cutoff * 16384;
    fc = temp >> 15;
    lp->gain = 16384 - fc;

    lp->first = 1;
    for (i = 0; i < 8; i++)
        lp->coefficients.taps[i] = 0;

    lp->coefficients.taps[i++] = fc;
    fcoef = ffc = (f64)fc * g_lowPassCoefficientScale;

    for (; i < 16; i++) {
        fcoef *= ffc;
        lp->coefficients.taps[i] = (s16)(fcoef * g_lowPassFixedPointScale);
    }
}


