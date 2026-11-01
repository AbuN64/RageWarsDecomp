#ifndef COMMON_MTX_H
#define COMMON_MTX_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"

struct CMatrix4;
struct CMatrix4 {
    CVector3 right;
    f32 m03;
    CVector3 up;
    f32 m13;
    CVector3 forward;
    f32 m23;
    f32 m30;
    f32 m31;
    f32 m32;
    f32 m33;
};
typedef struct CMatrix4 CMatrix4;



extern float g_planeProjectionAndDirectionConstants;

extern float g_boundedApproachStepConstants;

extern float g_axisAngleMatrixHomogeneousScale;




extern float g_directionFallbackAxisScale;



extern float g_wrappedInterpolationPeriod;





extern float g_directionMatrixHomogeneousScale;





extern float g_wrappedDifferenceUpperPeriod;
#endif
