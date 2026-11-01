#include "include_asm.h"
#include "COMMON/ALPARAM_S.H"

void alFilterNew(void *filterStorage, void *pullHandler, void *parameterHandler, int filterType) {
    struct ALFilter_s *filter = filterStorage;
    filter->source = 0;
    filter->handler = pullHandler;
    filter->setParam = (s32 (*)(void *, s32, void *))parameterHandler;
    filter->inp = 0;
    filter->outp = 0;
    filter->type = filterType;
}


