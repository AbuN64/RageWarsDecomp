#ifndef ENGINE_VISDATA_H
#define ENGINE_VISDATA_H
#include "types.h"
#include "Common/vector.h"

struct PlaneEquation {
    CVector3 normal;
    f32 distance;
};
typedef struct PlaneEquation PlaneEquation;

struct Frustum {
    f32 planes[6][4];
};
#if defined(VERSION_US)
extern void Visdata_EmptyInitializeHookSecondUs(void);
#endif
#if defined(VERSION_US)
extern void Visdata_EmptyReleaseHookSecondUs(void);
#endif
#endif
