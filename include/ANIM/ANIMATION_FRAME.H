#ifndef ANIM_ANIMATION_FRAME_H
#define ANIM_ANIMATION_FRAME_H
#include "TYPES.H"

/* Published animation descriptor prefix; callers receive a frame pointer. */
struct Shared_AnimFrame {
    u8 kind;
    u8 frameDuration;
    u8 shiftS;
    u8 shiftT;
    u8 primitiveMinimumLod;
    u8 materialCombineKind;
};
typedef struct Shared_AnimInfo {
    s32 count;
    s32 variationCount;
    struct Shared_AnimFrame *frame;
} Shared_AnimInfo;
#endif
