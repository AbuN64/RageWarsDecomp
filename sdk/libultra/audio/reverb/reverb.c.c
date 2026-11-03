#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"
#include <PR/abi.h>
#include "COMMON/AUDIO_CALLBACKS.H"
#include "AUDIO/ACMD.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ALDELAY28.H"
#include "../../../include/libultra/audio/reverb.H"
#include "TYPES.H"
#include "COMMON/ALAUXBUS_S.H"
#include "COMMON/ALSEQUENCEPLAYER.H"
#include <ultra64.h>
#include "../../../include/libultra/debug/assert.h"
#include "reverb/reverb.c.h"

/* reverb_Reverb.CPP */

/* reverb.c */
/* alResamplePull, drafted from ultralib src/audio/resample.c: at unity pitch pull the source and
   move its output; otherwise clip and quantise the pitch ratio, pull the input sample count it
   needs and append a resample command. The ratio limit, unity pitch and its reciprocal are the
   cartridge floats g_audioResamplerMaximumRatio, the one after it, and g_audioResamplerInverseFixedPointUnit. */

/* alFxPull, drafted from ultralib src/audio/reverb.c: pull the effect's source, mix the aux left
   and right outputs into the delay line input, run each delay section (load, feed-forward and
   feedback mixes, low-pass, save, gain into the output), advance the delay line input modulo its
   length and move the result into the aux left output. */

#if defined(VERSION_DE)
extern const float g_audioResamplerAssertText;
#elif defined(VERSION_EU)
extern const float g_audioResamplerAssertTextUsRev1;
#elif defined(VERSION_EU_X)
extern char g_audioResamplerAssertTextEuX[];
#elif defined(VERSION_US)
extern const float g_playerSecondLightRadius;
#else
extern char g_audioResamplerAssertTextEu[];
#endif

 /* "audio/reverb.c" */

 /* __assert */
extern Acmd *_loadOutputBuffer(struct ALFx *, ALDelay28 *, s32, s32, Acmd *);

 /* _loadOutputBuffer */

 /* _loadBuffer */
extern Acmd *_saveBuffer(struct ALFx *, s16 *, s32, s32, Acmd *);

/* reverb.CPP: linked before the reverb.c rodata, so defined before the first function whose switch emits a jump table */
/* ROM-grounded data: src/AudioResamplerMaximumRatioStorageSource.c */
const float g_audioResamplerMaximumRatio_StorageWords[3] = {
    1.99996f, 32768.0f, 3.0517578e-05f,
};

/* reverb.c */
s32 alMainBusParam(ALAuxBus_s *bus, s32 param, ALFilter_s14 *source) {
    ALFilter_s14 **sources = bus->sources;
    if (param == 2) {
        sources[bus->sourceCount++] = source;
    }
    return 0;
}

 /* osVirtualToPhysical */

 /* MAX_RATIO, followed by UNITY_PITCH */

    /* 1 / UNITY_PITCH */

Acmd *alResamplePull(ALResampler_s *filter, s16 *outp, s32 outCnt, s32 sampleOffset, Acmd *p)
{
    ALResampler_s *f = filter;
    Acmd *ptr = p;
    s16 inp;
    s32 inCount;
    ALFilter_s14_2 *source = f->filter.source;
    s32 incr;
    f32 finCount;
    f32 ratio;
    f32 unity;

    inp = 320; /* AL_DECODER_OUT */

    if (!outCnt)
        return ptr;

    if (f->upitch) {

        ptr = (*source->handler)(source, &inp, outCnt, sampleOffset, p);
        aDMEMMove(ptr++, inp, *outp, outCnt << 1);

    } else {

        if (f->ratio > g_audioResamplerMaximumRatio) f->ratio = g_audioResamplerMaximumRatio;

        ratio = f->ratio;
        unity = g_audioResamplerFixedPointUnit;
        f->ratio = (f32)(s32)(ratio * unity) * g_audioResamplerInverseFixedPointUnit;

        finCount = f->delta + (f->ratio * (f32)outCnt);
        inCount = (s32)finCount;
        f->delta = finCount - (f32)inCount;

        ptr = (*source->handler)(source, &inp, inCount, sampleOffset, p);

        incr = (s32)(f->ratio * unity);
        aSetBuffer(ptr++, 0, inp, *outp, outCnt << 1);
        aResample(ptr++, f->first, incr, osVirtualToPhysical(f->state));
        f->first = 0;
    }

    return ptr;
}

/** Apply a control message to this node and forward handled messages. */
s32 alResampleParam(void *resampler, s32 parameterId, s32 parameterValue) {
    void *node = resampler;
    void *target;
    void (*callback)(void *, s32, s32);

    {
        s32 sw_message_value = parameterId;
        sw_message_value -= (1);
        if ((unsigned int)sw_message_value > 8) {
            goto sw_message_default;
        }
        switch (sw_message_value) {
        case 0: goto sw_message_1;
        case 1: goto sw_message_default;
        case 2: goto sw_message_default;
        case 3: goto sw_message_4;
        case 4: goto sw_message_default;
        case 5: goto sw_message_default;
        case 6: goto sw_message_7;
        case 7: goto sw_message_8;
        case 8: goto sw_message_9;
        }
    }
    do {
    sw_message_1:
        *(s32 *)resampler = parameterValue;
        break;
    sw_message_4:
        ((AudioReverbParameterStateView *)(node))->delta = 0;
        ((AudioReverbParameterStateView *)(node))->first = 1;
        ((AudioReverbParameterStateView *)(node))->motion = 0;
        ((AudioReverbParameterStateView *)(node))->upitch = 0;
        target = *(void **)resampler;
        if (target != 0) {
            callback = ((struct CallbackStateC *) ((char *) target))->callback;
            callback(target, 4, 0);
        }
        break;
    sw_message_9:
        ((AudioReverbParameterStateView *)(node))->motion = 1;
        target = *(void **)resampler;
        if (target != 0) {
            callback = ((struct CallbackStateC *) ((char *) target))->callback;
            callback(target, 9, 0);
        }
        break;
    sw_message_7:
        ((AudioReverbParameterStateView *)(node))->ratio = parameterValue;
        break;
    sw_message_8:
        ((AudioReverbParameterStateView *)(node))->upitch = 1;
        break;
    sw_message_default:
        target = *(void **)resampler;
        if (target != 0) {
            callback = ((struct CallbackStateC *) ((char *) target))->callback;
            callback(target, parameterId, parameterValue);
        }
        break;

    } while (0);

    return 0;
}

 /* _saveBuffer */
Acmd *alFxPull(struct ALFx *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    struct ALFx *r = filter;
    ALFilter_s14_2 *source = (ALFilter_s14_2 *)r->filter.source;
    s16 i, buff1, buff2, input, output;
    s16 *in_ptr, *out_ptr, gain, *prev_out_ptr = 0;
    ALDelay28 *d, *pd;

    if (!source)
#if defined(VERSION_DE)
        __assert(&g_audioResamplerAssertText, g_audioResamplerSourceText, 75);
#elif defined(VERSION_EU)
        __assert(&g_audioResamplerAssertTextUsRev1, g_audioResamplerSourceText, 75);
#elif defined(VERSION_EU_X)
        __assert(g_audioResamplerAssertTextEuX, g_audioResamplerSourceText, 75);
#elif defined(VERSION_US)
        __assert(&g_playerSecondLightRadius, g_audioResamplerSourceText, 75);
#else
        __assert(g_audioResamplerAssertTextEu, g_audioResamplerSourceText, 75);
#endif

    ptr = (*source->handler)(source, outp, outCount, sampleOffset, p);

    input = 1728;
    output = 2048;
    buff1 = 0;
    buff2 = 320;

    aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
    aMix(ptr++, 0, 0xda83, 1728, input);
    aMix(ptr++, 0, 0x5a82, 2048, input);
    ptr = _saveBuffer(r, r->input, input, outCount, ptr);

    aClearBuffer(ptr++, output, outCount << 1);

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        in_ptr = &r->input[-d->input];
        out_ptr = &r->input[-d->output];

        if (in_ptr == prev_out_ptr) {
            { s16 t = buff2; buff2 = buff1; buff1 = t; };
        } else {
            ptr = _loadBuffer(r, in_ptr, buff1, outCount, ptr);
        }
        ptr = _loadOutputBuffer(r, d, buff2, outCount, ptr);

        if (d->ffcoef) {
            aMix(ptr++, 0, (u16)d->ffcoef, buff1, buff2);
            if (!d->rs && !d->lp) {
                ptr = _saveBuffer(r, out_ptr, buff2, outCount, ptr);
            }
        }

        if (d->fbcoef) {
            aMix(ptr++, 0, (u16)d->fbcoef, buff2, buff1);
            ptr = _saveBuffer(r, in_ptr, buff1, outCount, ptr);
        }

        if (d->lp)
            ptr = _filterBuffer(d->lp, buff2, outCount, ptr);

        if (!d->rs)
            ptr = _saveBuffer(r, out_ptr, buff2, outCount, ptr);

        if (d->gain)
            aMix(ptr++, 0, (u16)d->gain, buff2, output);

        prev_out_ptr = &r->input[d->output];
    }

    r->input += outCount;
    if (r->input > &r->base[r->length])
        r->input -= r->length;

    aDMEMMove(ptr++, output, 1728, outCount << 1);

    return ptr;
}

#if defined(VERSION_US)
unsigned int k_ReverbEncodedWords[3] = {
    0x540000A0, 0x6E020066, 0x000000A0,
};
#endif

#if defined(VERSION_EU)
unsigned int k_ReverbEncodedWordsBlock1[3] = {
    0x00000000, 0x41F00000, 0x00000000,
};
#endif
