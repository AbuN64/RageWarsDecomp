#include "Common/small_records.h"
#include "Common/alauxbus_s.h"
#include "Common/alparam_s.h"
#include "include_asm.h"
#include "../../include/libgultra.h"
#include "Common/runtime_declarations.h"
#include "Pools/pools.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "../../include/VOICE_START_AND_PARAMETER_UPDATE_VIEWS.H"
#include "types.h"
#include "../../include/libgultra/ALSYNSTARTVOICE.H"
#include "../../include/libultra/audio/synthesizer.h"

/* alSynStartVoice_Alsynstartvoice.c */
void alSynStartVoice(ALSynth *synth, ALVoice *voice, ALWaveTable *waveTable) {
    s32 updateSampleTime;
    void *controlUpdate;
    void *voiceFilter;
    ALSetParam fn;

    if ((((ALVoice *)(voice))->pvoice) != 0) {
        controlUpdate = __allocParam();
        if (controlUpdate != 0) {
            updateSampleTime = (((struct ALSynth4C *)(synth))->paramSamples) + (((struct PVoice_s *) ((ALVoice *) voice)->pvoice)->offset);
            ((AudioStartVoiceUpdate *)(controlUpdate))->type = AL_FILTER_START_VOICE;
            ((AudioStartVoiceUpdate *)(controlUpdate))->wave = waveTable;
            ((AudioStartVoiceUpdate *)(controlUpdate))->next = 0;
            ((AudioStartVoiceUpdate *)(controlUpdate))->delta = updateSampleTime;
            ((AudioStartVoiceUpdate *)(controlUpdate))->unity = ((ALVoice *)(voice))->unityPitch;
            voiceFilter = ((ALVoice *) voice)->pvoice->channelKnob;
            fn = ((ALFilter_s14 *)(voiceFilter))->setParam;
            fn(voiceFilter, AL_FILTER_ADD_UPDATE, controlUpdate);
        }
    }
}

/* 8025DE50_11.CPP */

/* 8025DE50_19.CPP */
/* 8025DE50_19.CPP */

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
/* Stale code jr ra; addiu sp,24; no instruction reads it. */
unsigned char g_alSynStartVoiceStaleCode[8] = { 0x03, 0xE0, 0x00, 0x08, 0x27, 0xBD, 0x00, 0x18 };
#endif

/* 8025DE50_9.CPP */
