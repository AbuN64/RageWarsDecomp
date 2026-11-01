#ifndef SYSTEM_VIDEO_CONTEXT_VIEWS_H
#define SYSTEM_VIDEO_CONTEXT_VIEWS_H
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
struct VideoContextEventView {
    char pad0[2];
    s16 f2;
    char pad4[0xC];
    s32 f10;
    s32 f14;
};
struct __OSViContext {
    u16 state;
    u16 retraceCount;
    void *framep;
    void *modep;
    u32 control;
    OSMesgQueue *msgq;
    void * msg;
};
#endif
