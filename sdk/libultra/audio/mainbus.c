#include "../../include/libgultra.h"
#include "types.h"
#include <PR/abi.h>
#include "Common/audio_callbacks.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/alauxbus_s.h"
#include "Common/alparam_s.h"
#include "include_asm.h"

/* MAINBUS.CPP */
/* 802B975C_2.CPP */
#if defined(VERSION_EU)
Acmd *alMainBusPull(ALMainBus_s *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALMainBus_s *m = filter;
    ALFilter_s14 **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, 0x440, outCount << 1);
    aClearBuffer(ptr++, 0x580, outCount << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = sources[i]->handler(sources[i], outp, outCount, sampleOffset, ptr);
        aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
        aMix(ptr++, 0, 0x7FFF, 0x6C0, 0x440);
        aMix(ptr++, 0, 0x7FFF, 0x800, 0x580);
    }
    return ptr;
}
#endif

/* 802B975C_6.CPP */
#if !(defined(VERSION_DE) || defined(VERSION_EU))
/* alMainBusPull (libultra audio main bus): clears the main left and right buffers, then pulls each source and mixes the aux outputs into the main buffers. */
Acmd *alMainBusPull(ALMainBus_s *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALMainBus_s *m = filter;
    ALFilter_s14 **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, 0x440, outCount << 1);
    aClearBuffer(ptr++, 0x580, outCount << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = sources[i]->handler(sources[i], outp, outCount, sampleOffset, ptr);
        aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
        aMix(ptr++, 0, 0x7FFF, 0x6C0, 0x440);
        aMix(ptr++, 0, 0x7FFF, 0x800, 0x580);
    }
    return ptr;
}
#endif

/* mainbus.c */
#if defined(VERSION_DE)
#include "Common/alauxbus_s.h"

Acmd *alMainBusPull(ALMainBus_s *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALMainBus_s *m = filter;
    ALFilter_s14 **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, 0x440, outCount << 1);
    aClearBuffer(ptr++, 0x580, outCount << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = sources[i]->handler(sources[i], outp, outCount, sampleOffset, ptr);
        aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
        aMix(ptr++, 0, 0x7FFF, 0x6C0, 0x440);
        aMix(ptr++, 0, 0x7FFF, 0x800, 0x580);
    }
    return ptr;
}
#endif
