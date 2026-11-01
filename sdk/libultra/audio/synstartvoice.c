#include "COMMON/ALPARAM_S.H"
#include "include_asm.h"
#include "../../include/libgultra.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "../../include/VOICE_START_AND_PARAMETER_UPDATE_VIEWS.H"
#include "TYPES.H"
#include "../../include/libgultra/ALSYNSTARTVOICE.H"
#include "../../include/libultra/audio/synthesizer.h"

/* alSynStartVoice_Alsynstartvoice.c */
void alSynStartVoice(ALSynth *synth, ALVoice *voice, ALWaveTable *waveTable) {
    s32 updateSampleTime;
    void *controlUpdate;
    void *voiceFilter;
    SharedRecV3 fn;

    if ((((AudioVoiceStartView *)(voice))->pvoice.v0) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct AudioSynthParamSamplesView *)(synth))->paramSamples) + (((struct AudioPhysicalVoiceOffsetView *) ((AudioVoiceStartView *) voice)->pvoice.v1)->offset);
            ((AudioStartVoiceUpdate *)(controlUpdate))->type = AL_FILTER_START_VOICE;
            ((AudioStartVoiceUpdate *)(controlUpdate))->wave = waveTable;
            ((AudioStartVoiceUpdate *)(controlUpdate))->next = 0;
            ((AudioStartVoiceUpdate *)(controlUpdate))->delta = updateSampleTime;
            ((AudioStartVoiceUpdate *)(controlUpdate))->unity = ((AudioVoiceStartView *)(voice))->unityPitch;
            voiceFilter = ((struct Draw *) ((AudioVoiceStartView *) voice)->pvoice.v1)->model;
            fn = ((CallbackStateC_4 *)(voiceFilter))->callback;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}

/* 8025DE50_11.CPP */

/* 8025DE50_19.CPP */
/* 8025DE50_19.CPP */

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
unsigned char g_AlsynstartvoiceTrailingBytesBlock2[8] = { 0x03, 0xE0, 0x00, 0x08, 0x27, 0xBD, 0x00, 0x18 };
#endif

/* 8025DE50_9.CPP */
