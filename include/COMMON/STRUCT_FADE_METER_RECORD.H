#ifndef COMMON_STRUCT_FADE_METER_RECORD_H
#define COMMON_STRUCT_FADE_METER_RECORD_H
#include "TYPES.H"

/* Menu_InitializeFadeMeter has no identified callers. Its 0x0C input is
   stored verbatim; no allocation or reader proves it is a Meter.bar pointer. */
struct FadeMeterRecord {
    s32 resetState[3]; /* +0x00..0x08: cleared at initialization */
    s32 value;         /* +0x0C: caller-supplied word */
    s32 initialized;   /* +0x10: set to one at initialization */
};
#endif
