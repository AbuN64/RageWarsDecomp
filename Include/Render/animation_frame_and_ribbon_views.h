#ifndef RENDER_ANIMATION_FRAME_AND_RIBBON_VIEWS_H
#define RENDER_ANIMATION_FRAME_AND_RIBBON_VIEWS_H
#include "types.h"
#include "Common/effectcontribution.h"
#include "Common/sharedplayer.h"

struct Morph {
    s32 count;
    struct Blend *blends;
    struct Key *first;
    struct Key *second;
    union { f32 firstFrame; f32 scaleS; };
    union { f32 secondFrame; f32 scaleT; };
    f32 textureScaleS;
    f32 textureScaleT;
    f32 step;
};
/* Double-buffered vertex storage shared by the ribbon allocator and reset. */
struct Animator {
    s32 reservedWord;
    s32 mode;
    f32 time;
    f32 *loop;
    f32 *script;
    f32 value;
    f32 valueFrom;
    f32 valueTo;
    f32 valueDuration;
    f32 alpha;
    f32 alphaFrom;
    f32 alphaTo;
    f32 colourDuration;
    f32 rgb[3];
    char pad40[4];
    f32 rgbFrom[3];
    char pad50[4];
    f32 rgbTo[3];
};
#endif
