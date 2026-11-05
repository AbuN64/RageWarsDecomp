#ifndef COMMON_LOCALDECODERANGE_H
#define COMMON_LOCALDECODERANGE_H
#include "Engine/folded_constants.h"
#include "types.h"
struct Anim {
    s32 time;
    s16 current;
    s16 next;
    u16 frames;
    u8 blending;
    u8 active;
    s32 length;
    void *resource;
};
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/stream.h"







extern float g_motionTrackFrameScale;

struct LocalDecodeRange;

struct LocalDecodeRange;
typedef struct LocalDecodeRange LocalDecodeRange;







struct TrackBitarrayExpandCurveSamples;


struct DecodeArray;

struct BitFieldSource;
typedef struct BitFieldSource BitFieldSource;

struct BitFieldSource;


struct DecodeArray;
typedef struct DecodeArray DecodeArray;



extern void Bitarray_ExpandCurveSamples(char **stream, f32 *out, s32 frames);






struct PolytrakWordAndTripleRecord;
typedef struct PolytrakWordAndTripleRecord PolytrakWordAndTripleRecord;

struct Pack;
struct Pack {
    s32 count;
    s32 offsets[1];
};



struct Anim;





struct MotionPackHeader;

struct Anim;
typedef struct Anim Anim;

struct Pack;
typedef struct Pack Pack;


struct MotionPackHeader;
typedef struct MotionPackHeader MotionPackHeader;

extern float g_motionRotationDecodeLimit;

struct TrackBitarrayExpandCurveSamples;
typedef struct TrackBitarrayExpandCurveSamples TrackBitarrayExpandCurveSamples;





struct PolytrakWordAndTripleRecord;


typedef struct CGameAnimateState_t {
    f32 time;
    s16 current,next,frames;
    u8 active,blending;
    char padc[4]; void *resource;
} CGameAnimateState_t;
extern f32 Graphu64_InterpolateWrappedValue(f32,f32,f32);
extern s32 Gastate_GetAnimationEventCount(void *);
#endif
