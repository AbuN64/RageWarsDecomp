#ifndef MATH_XMATH_EVALUATEEXPONENTIALDOUBLE_H
#define MATH_XMATH_EVALUATEEXPONENTIALDOUBLE_H
#include "Common/rotation_extraction.h"
extern f32 XMath_SquareFloat(f32 value);
extern f64 XMath_FloorDouble(f64 value);
extern f32 XMath_OffsetFloatRemainder(f32 value, f32 period);
extern f64 XMath_SplitDoubleFraction(f64 value, f64 *whole);
extern void XMath_InitializeMath(void);
extern void XMath_ShutdownMath(void);
extern f32 XMath_AbsoluteFloat(f32 value);
extern f64 XMath_CeilDouble(f64 value);
#endif
