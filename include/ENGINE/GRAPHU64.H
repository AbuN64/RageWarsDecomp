#ifndef ENGINE_GRAPHU64_H
#define ENGINE_GRAPHU64_H
#include "TYPES.H"
#include "COMMON/OBJRECAT4V7.H"
#include "COMMON/GRAPHICS_MATRIX_AND_VECTOR_MATH.H"

extern f32 g_arcCosEndpoint;

extern float g_fullFixedMatrixElement0ConversionConstants;

extern CVector3 *Graphu64_ProjectOntoCrossNormal(CVector3 *out, CVector3 *value, CVector3 *a, CVector3 *b);
#endif
