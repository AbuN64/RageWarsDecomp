#include "include_asm.h"
#include "Common/alfxparam.h"
#include "Common/alauxbus_s.h"
#include "../../include/libultra/audio/synthesizer.h"
#include "Common/audio_effect_chain.h"
#include "types.h"
#include "../../include/libultra/audio/drvrnew.h"


extern s32 alMainBusParam(void *bus, s32 param, s32 source);




ALFxRef *alSynAllocFX(ALSynth *synth, s16 busNumber, ALSynConfig *config, ALHeap *heap) {
    s32 scaled = busNumber * 0x4C;
    s32 auxiliaryBus;

    alFxNew((s32)synth->auxBus + scaled + 0x20, config, heap);
    auxiliaryBus = (s32)synth->auxBus + scaled;
    alFxParam((int *)(auxiliaryBus + 0x20), 1, auxiliaryBus);
    alMainBusParam(synth->mainBus, 2, (s32)synth->auxBus + scaled + 0x20);
    return (s32)synth->auxBus + scaled + 0x20;
}

