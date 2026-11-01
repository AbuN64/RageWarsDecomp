#ifndef MENU_FRAME_SEQUENCE_H
#define MENU_FRAME_SEQUENCE_H
#include "TYPES.H"
struct FrontendArchiveHandleView;
typedef struct FrameSequence FrameSequence;
struct FrameSequence {
    char pad0[0x44];
    struct FrontendArchiveHandleView *target;
    s32 *frames;
    s32 frame;
    s32 count;
    s32 elapsed;
    s32 duration;
    s32 flags;
    s32 loops;
};
#endif
