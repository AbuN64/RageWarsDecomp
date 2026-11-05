#ifndef OSCONTREQUESFORMATSHORT_H
#define OSCONTREQUESFORMATSHORT_H
#include "types.h"
#include "Common/note_state.h"


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
