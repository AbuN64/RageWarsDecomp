#include "COMMON/ALAUXBUS_S.H"
#include <PR/abi.h>
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
/* alAuxBusPull: clears the aux left and right output buffers, then pulls every source filter of the bus into the command list. */
Acmd *alAuxBusPull(ALAuxBus_s *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALAuxBus_s *m = filter;
    ALFilter_s14 **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, 0x6C0, outCount << 1);
    aClearBuffer(ptr++, 0x800, outCount << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = sources[i]->handler(sources[i], outp, outCount, sampleOffset, ptr);
    }
    return ptr;
}
#endif

#if defined(VERSION_DE)
/* alAuxBusPull: clears the aux left and right output buffers, then pulls every source filter of the bus into the command list. */
Acmd *alAuxBusPull(ALAuxBus_s *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALAuxBus_s *m = filter;
    ALFilter_s14 **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, 0x6C0, outCount << 1);
    aClearBuffer(ptr++, 0x800, outCount << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = sources[i]->handler(sources[i], outp, outCount, sampleOffset, ptr);
    }
    return ptr;
}
#endif

#if defined(VERSION_US)

Acmd *alAuxBusPull(ALAuxBus_s *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALAuxBus_s *m = filter;
    ALFilter_s14 **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, 0x6C0, outCount << 1);
    aClearBuffer(ptr++, 0x800, outCount << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = sources[i]->handler(sources[i], outp, outCount, sampleOffset, ptr);
    }
    return ptr;
}
#endif

#if defined(VERSION_EU)
Acmd *alAuxBusPull(ALAuxBus_s *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALAuxBus_s *m = filter;
    ALFilter_s14 **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, 0x6C0, outCount << 1);
    aClearBuffer(ptr++, 0x800, outCount << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = sources[i]->handler(sources[i], outp, outCount, sampleOffset, ptr);
    }
    return ptr;
}
#endif

s32 alAuxBusParam(ObjalAuxBusParam *bus, s32 operation, s32 source) {
    int sourceCount;
    s32 *base;
    s32 count;

    base = bus->base;
    if (operation == 2) {
        sourceCount = bus->count;
        count = sourceCount;
        base[count] = source;
        sourceCount = count + 1;
        bus->count = sourceCount;
    }
    return 0;
}
