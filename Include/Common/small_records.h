#ifndef COMMON_SMALL_RECORDS_H
#define COMMON_SMALL_RECORDS_H
#include "types.h"
#include "Common/audio_callbacks.h"
#include "Common/vector.h"

typedef struct { s16 id, weight; } SpawnChoice;

struct ListLink {
    struct ListLink *next;
    struct ListLink *prev;
};
typedef struct ListLink ListLink;

struct ResourceManagerState {
    s32 active;
    s32 count;
};
typedef struct ResourceManagerState ResourceManagerState;

struct ScalarPair {
    f32 first;
    f32 second;
};
typedef struct ScalarPair ScalarPair;

struct Polytrak2QuantizationRange {
    u32 value;
    f32 start;
    f32 delta;
};
typedef struct Polytrak2QuantizationRange Polytrak2QuantizationRange;

struct Vec3Words {
    s32 w[3];
};
typedef struct Vec3Words Vec3Words;

/* Leaf records that larger records hold by value; they depend on nothing, so any header may include them. */
struct IntPair {
    int first;
    int second;
};

struct ImageTableEntry {
    s32 offset;
    u8 tag[4];
};
typedef struct ImageTableEntry ImageTableEntry;

struct UnitMtx {
    s32 m[16];
};
typedef struct UnitMtx UnitMtx;

struct Block24 {
    s32 words[6];
};
typedef struct Block24 Block24;

struct FixedPointMatrix {
    u32 upper[8];
    u32 lower[8];
};
typedef struct FixedPointMatrix FixedPointMatrix;
union ObjectLinks4_3 {
    void * v0;
    char * v1;
};
typedef union ObjectLinks4_3 ObjectLinks4_3;

union WordOrFloat {
    s32 word;
    f32 value;
};
typedef union WordOrFloat WordOrFloat;
struct ALFilter_s14 {
    struct ALFilter_s14 *source;
    ALCmdHandler handler;
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
};
typedef struct ALFilter_s14 ALFilter_s14;
struct Triple {
    s32 x;
    s32 y;
    s32 z;
};
typedef struct Triple Triple;
typedef struct { CVector3 pos; s32 room; } ApproachLocation;

struct ScalarFloatView {
    f32 value;
};

typedef struct ScalarFloatView ScalarFloatView;

#endif
