#include "include_asm.h"
#include "Common/alparam_s.h"
#include <PR/abi.h>
#include "Common/audio_callbacks.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include <platform_sdk.h>
#include "../../include/libultra/debug/assert.h"
#include "../../include/al_globals.h"
#include "../../include/VOICE_START_AND_PARAMETER_UPDATE_VIEWS.H"
#include "Common/alauxbus_s.h"
#include "../../include/libultra/audio/synthesizer.h"
#include "../../include/libultra/audio/env.h"
#include "Data/Ovl1_c/env.h"

/* libultra audio/env.c, built with -fforce-addr (config.toml): the eqpower base stays in a register. */
extern s16 g_audioEqualPowerPanTable[128]; /* eqpower */
extern char g_audioEnvelopeSourceAssertText[]; /* Resident "EX" assertion expression. */
 /* "audio/env.c" */
#define eqpower g_audioEqualPowerPanTable
#define EQPOWER_LENGTH 128
#define AL_RESAMPLER_OUT 0
#define AL_MAX_RSP_SAMPLES 160

/* The SDK's traditional-cpp assert: the expression string is the literal "EX". */
#define assert_at(EX, line) ((EX) ? ((void)0) : __assert(g_audioEnvelopeSourceAssertText, s_audioEnvText, line))

Acmd *_pullSubFrame(void *filter, s16 *inp, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p);

/* alEnvmixerPull: walk the envelope mixer's control list up to outCount samples, pulling the
   source for the span before each update, applying it (voice start/stop/free, volume, pan, fx
   mix, or passing it down the chain), freeing it, then pulling the remainder of the frame. */
Acmd *alEnvmixerPull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    ALEnvMixer *e = (ALEnvMixer *)filter;
    s16 inp;
    s32 lastOffset;
    s32 thisOffset = sampleOffset;
    s32 samples;
    s16 loutp = 0;
    s32 fVol;
    ALParam_s *thisParam;

    inp = AL_RESAMPLER_OUT;

    while (e->ctrlList != 0) {
        lastOffset = thisOffset;
        thisOffset = e->ctrlList->delta;
        samples = thisOffset - lastOffset;
        if (samples > outCount)
            break;

        assert_at(samples >= 0, 103);
        assert_at(samples <= AL_MAX_RSP_SAMPLES, 104);

        switch (e->ctrlList->type) {
        case AL_FILTER_START_VOICE_ALT: {
            ALStartParamAlt *param = (ALStartParamAlt *)e->ctrlList;
            ALFilter_s *f = (ALFilter_s *)e;
            s32 tmp;

            if (param->unity) {
                (*e->filter.setParam)(&e->filter, AL_FILTER_SET_UNITY_PITCH, 0);
            }
            (*e->filter.setParam)(&e->filter, AL_FILTER_SET_WAVETABLE, param->wave);
            (*e->filter.setParam)(&e->filter, AL_FILTER_START, 0);

            e->first = 1;
            e->delta = 0;
            e->segEnd = param->samples;

            tmp = ((s32)param->volume * (s32)param->volume) >> 15;
            e->volume = (s16)tmp;
            e->pan = param->pan;
            e->dryamt = eqpower[param->fxMix];
            e->wetamt = eqpower[EQPOWER_LENGTH - param->fxMix - 1];

            if (param->samples) {
                e->cvolL = 1;
                e->cvolR = 1;
            } else {
                /* No ramp: the current volume is the target volume. */
                e->cvolL = (e->volume * eqpower[e->pan]) >> 15;
                e->cvolR = (e->volume * eqpower[EQPOWER_LENGTH - e->pan - 1]) >> 15;
            }

            if (f->source) {
                union {
                    f32 f;
                    s32 i;
                } data;
                data.f = param->pitch;
                (*f->source->setParam)(f->source, AL_FILTER_SET_PITCH, (void *)data.i);
            }
        } break;

        case AL_FILTER_SET_FXAMT:
        case AL_FILTER_SET_PAN:
        case AL_FILTER_SET_VOLUME:
            ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);

            if (e->delta >= e->segEnd) {
                /* Target reached (or segEnd was 0): settle on it. */
                e->ltgt = (e->volume * eqpower[e->pan]) >> 15;
                e->rtgt = (e->volume * eqpower[EQPOWER_LENGTH - e->pan - 1]) >> 15;
                e->delta = e->segEnd; /* prevent overflow */
                e->cvolL = e->ltgt;
                e->cvolR = e->rtgt;
            } else {
                /* Estimate the current volume along the ramp. */
                e->cvolL = _getVol(e->cvolL, e->delta, e->lratm, e->lratl);
                e->cvolR = _getVol(e->cvolR, e->delta, e->rratm, e->rratl);
            }

            /* A zero volume would never ramp anywhere. */
            if (e->cvolL == 0) e->cvolL = 1;
            if (e->cvolR == 0) e->cvolR = 1;

            if (e->ctrlList->type == AL_FILTER_SET_PAN)
                e->pan = (s16)e->ctrlList->data.i;

            if (e->ctrlList->type == AL_FILTER_SET_VOLUME) {
                /* A new segment; volume maps non-linearly to loudness. */
                e->delta = 0;
                fVol = (e->ctrlList->data.i);
                fVol = (fVol * fVol) >> 15;
                e->volume = (s16)fVol;
                e->segEnd = e->ctrlList->moredata.i;
            }

            if (e->ctrlList->type == AL_FILTER_SET_FXAMT) {
                e->dryamt = eqpower[e->ctrlList->data.i];
                e->wetamt = eqpower[EQPOWER_LENGTH - e->ctrlList->data.i - 1];
            }

            e->first = 1; /* force a volume update */
            break;

        case AL_FILTER_START_VOICE: {
            ALStartParam *p = (ALStartParam *)e->ctrlList;

            if (p->unity) {
                (*e->filter.setParam)(&e->filter, AL_FILTER_SET_UNITY_PITCH, 0);
            }
            (*e->filter.setParam)(&e->filter, AL_FILTER_SET_WAVETABLE, p->wave);
            (*e->filter.setParam)(&e->filter, AL_FILTER_START, 0);
        } break;

        case AL_FILTER_STOP_VOICE: {
            ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);
            (*e->filter.setParam)(&e->filter, AL_FILTER_RESET, 0);
        } break;

        case AL_FILTER_FREE_VOICE: {
            ALSynth4C *drvr = &g_audioGlobals->drvr;
            ALFreeParam *param = (ALFreeParam *)e->ctrlList;
            param->pvoice->offset = 0;
            _freePVoice(drvr, param->pvoice);
        } break;

        default:
            /* Pull up to the update, then pass it down the chain. */
            ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);
            (*e->filter.setParam)(&e->filter, e->ctrlList->type, (void *)e->ctrlList->data.i);
            break;
        }
        loutp += (samples << 1);
        outCount -= samples;

        /* Return the update to the free list. */
        thisParam = e->ctrlList;
        e->ctrlList = e->ctrlList->next;
        if (e->ctrlList == 0)
            e->ctrlTail = 0;

        __freeParam(thisParam);
    }

    ptr = _pullSubFrame(e, &inp, &loutp, outCount, sampleOffset, ptr);

    /* Prevent overflow in e->delta. */
    if (e->delta > e->segEnd)
        e->delta = e->segEnd;

    return ptr;
}


/* _pullSubFrame, drafted from ultralib src/audio/env.c: when the envelope mixer is playing, pull
   its source and append the buffer, volume and envelope-mixer commands for one subframe,
extern char s_audioEnvText[]; /* "audio/env.c" */

 /* __assert */
  /* _getRate */

Acmd *_pullSubFrame(void *filter, s16 *inp, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    struct ALEnvMixer_s *e = (struct ALEnvMixer_s *)filter;
    ALFilter_s14_2 *source = e->filter.source;

    if (e->motion != 1 || !outCount)
        return ptr;

    ((source) ? ((void)0) : __assert(g_audioEnvelopeSourceAssertText, s_audioEnvText, 366));

    ptr = (*source->handler)(source, inp, outCount, sampleOffset, p);

    aSetBuffer(ptr++, 0x00, *inp, 1088 + *outp, outCount << 1);
    aSetBuffer(ptr++, 0x08, 1408 + *outp, 1728 + *outp, 2048 + *outp);

    if (e->first) {
        e->first = 0;

        e->ltgt = (e->volume * g_audioEqualPowerPanTable[e->pan]) >> 15;
        e->lratm = _getRate((f64)e->cvolL, (f64)e->ltgt, e->segEnd, &(e->lratl));
        e->rtgt = (e->volume * g_audioEqualPowerPanTable[128 - e->pan - 1]) >> 15;
        e->rratm = _getRate((f64)e->cvolR, (f64)e->rtgt, e->segEnd, &(e->rratl));

        aSetVolume(ptr++, 0x02 | 0x04, e->cvolL, 0, 0);
        aSetVolume(ptr++, 0x00 | 0x04, e->cvolR, 0, 0);
        aSetVolume(ptr++, 0x02 | 0x00, e->ltgt, e->lratm, e->lratl);
        aSetVolume(ptr++, 0x00 | 0x00, e->rtgt, e->rratm, e->rratl);
        aSetVolume(ptr++, 0x08, e->dryamt, 0, e->wetamt);
        aEnvMixer(ptr++, 0x01 | 0x08, osVirtualToPhysical(e->state));
    }
    else
        aEnvMixer(ptr++, 0x00 | 0x08, osVirtualToPhysical(e->state));

    *inp += (outCount << 1);
    e->delta += outCount;

    return ptr;
}

/* _getRate: approximate per-step volume scaling using the public ultralib log table and repeated squaring. */

s16 _getRate(f64 vol, f64 tgt, s32 count, u16 *ratel)
{
  s16 s;
  f64 invn = (1.0f) / ((f32) count);
  f64 eps;
  f64 a;
  f64 fs;
  f64 logMantissaSample;
  f64 mant;
  s32 i_invn;
  s32 ex;
  s32 indx;
  if (count == 0)
  {
    if (tgt >= vol)
    {
      *ratel = 0xffff;
      return 0x7fff;
    }
    else
    {
      *ratel = 0;
      return 0;
    }
  }
  if (tgt < (1.0))
  {
    tgt = (1.0);
  }
  if (vol <= (0.0))
  {
    vol = (1.0);
  }
  {
    LogTab logtab = { { -0.91253697872161865, -0.75207197666168213, -0.60768300294876099, -0.47643798589706421, -0.3561440110206604, -0.24511200189590454, -0.14201900362968445, -4.580400139093399e-2 } };
    f64 absvalue;
    s32 *eptr;
    i_invn = (s32) (invn * (1073741824.0));
    tgt = tgt / vol;
    eptr = &ex;
    *eptr = 0;
    if (tgt == (0.0))
    {
      vol = tgt;
    }
    else
    {
      absvalue = __builtin_fabs(tgt);
      if (absvalue >= (1.0))
      {
        do
        {
          absvalue *= (0.5);
          ++(*eptr);
        }
        while (absvalue >= (1.0));
      }
      if (absvalue < (0.5))
      {
        do
        {
          absvalue += absvalue;
          --(*eptr);
        }
        while (absvalue < (0.5));
      }
      vol = absvalue;
      if (!(tgt > (0.0)))
      {
        vol = -vol;
      }
    }
    indx = (s32) (vol * (16.0));
    absvalue = (0.69314718246459961);
    eps = ((logMantissaSample = logtab.v[indx - 8]) + ex) * absvalue;
    mant = (1073741824.0); eps /= mant; fs = eps + (1.0); a = (1.0);
    while (i_invn)
    {
      if (i_invn & 1)
      {
        a = a * fs;
      }
      fs *= fs;
      i_invn >>= 1;
    }

  }
  if (vol)
  {
    a *= (a *= (a *= a));
    s = (s16) a;
    *ratel = (s16) ((a - ((f32) s)) * (65535.0));
    return (s16) a;
  }
  else
  {
    a *= (a *= (a *= a));
    s = (s16) a;
    *ratel = (s16) ((a - ((f32) s)) * (65535.0));
    return (s16) a;
  }
}

/* alEnvmixerParam, drafted from ultralib src/audio/env.c: apply one parameter to the envelope
   mixer, appending an update to the control list, resetting or starting the filter, setting its
   source, and otherwise passing the parameter down to the source. The parameter identifiers are
   the cartridge's own 1, 3, 4 and 9. */
s32 alEnvmixerParam(void *filter, s32 paramID, void *param)
{
    ALFilter_s *f = (ALFilter_s *)filter;
    ALEnvMixer *e = (ALEnvMixer *)filter;

    switch (paramID) {

      case (3):
          if (e->ctrlTail) {
              e->ctrlTail->next = (ALParam_s *)param;
          } else {
              e->ctrlList = (ALParam_s *)param;
          }
          e->ctrlTail = (ALParam_s *)param;

          break;

      case (4):
          e->first = 1;
          e->motion = 0;
          e->volume = 1;
          if (f->source)
              (*f->source->setParam)(f->source, 4, param);
          break;

      case (9):
          e->motion = 1;
          if (f->source)
              (*f->source->setParam)(f->source, 9, param);
          break;

      case (1):
          f->source = (ALFilter_s *)param;
          break;

      default:
          if (f->source)
              (*f->source->setParam)(f->source, paramID, param);
    }
    return 0;
}

f32 _getVol(f32 initialVolume, s32 sampleCount, s32 rateInteger, s32 rateFraction)
{
    f32 base;
    f32 result;
    s32 n;
    s32 i;

    n = sampleCount >> 3;
    i = 0;
    if (n == 0) {
        return initialVolume;
    }

    base = (f32)(rateInteger << 16);
    base += (f32)(rateFraction & 0xFFFF);
    base *= g_audioEnvelopeRateScale;
    result = g_audioEnvelopeFallbackRate;
    do {
        if (n & 1) {
            result *= base;
        }
        n >>= 1;
        i++;
        if (n == 0) {
            break;
        }
        base *= base;
    } while (i < 0x20);

    return initialVolume * result;
}


f64 frexp(f64 inputValue, s32 *exponentOut) {
    f64 value;

    *exponentOut = 0;
    if (inputValue == g_audioFrexpZero) {
        return inputValue;
    }
    value = __builtin_fabs(inputValue);
    if (g_audioFrexpUpperLimit <= value) {
        do {
            value *= g_audioFrexpHalvingScale;
            *exponentOut += 1;
        } while (g_audioFrexpUpperLimit <= value);
    }
    if (value < g_audioFrexpLowerLimit) {
        do {
            value += value;
            *exponentOut -= 1;
        } while (value < g_audioFrexpLowerLimit);
    }
    if (!(g_audioFrexpRestoreSignThreshold < inputValue)) {
        value = -value;
    }
    return value;
}

f64 _ldexpf(f64 value, s32 shift) {
    if (shift != 0) {
        value = value * (f64)(1 << shift);
    }
    return value;
}

#if defined(VERSION_US)
/* Zero word ending env's object; no instruction reads it. */
unsigned int g_ldexpfZeroTail[1] = {
    0x00000000,
};
#endif

