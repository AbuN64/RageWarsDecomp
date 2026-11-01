#ifndef OSCONTREQUESFORMATSHORT_H
#define OSCONTREQUESFORMATSHORT_H
#include "TYPES.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/ITEMRECAT20V1.H"


struct __OSContRequesFormatShort;
typedef struct __OSContRequesFormatShort __OSContRequesFormatShort;

struct __OSContRequesFormatShort;
struct __OSContRequesFormatShort {
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u8 typeh;
    u8 typel;
    u8 status;
};
#endif
