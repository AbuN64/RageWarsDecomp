#ifndef MATH_DOUBLEBITS_H
#define MATH_DOUBLEBITS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
extern float k_xmathArcTangentPolynomialLeadingCoefficient;




extern double k_xmathExponentialNumeratorConstant;



extern double k_xmathVectorAnglePeriodDouble;

extern float k_xmathArcCosineCoefficientPairOne;

extern float k_xmathArcSineCoefficientPairOne;

extern double k_xmathExponentSpecialValue;

extern float k_xmathPlaneDenominatorLowerTolerance;



extern double k_xmathExponentialInitialResult;

extern float k_xmathArcTangentCoefficientPairOne;

union DoubleBits;
typedef union DoubleBits DoubleBits;

extern double k_xmathExponentialUpperLimit;

extern float k_xmathTangentCosinePhaseOffset;

extern double k_xmathExponentialDenominatorLinearCoefficient;

extern double k_xmathExponentialBaseTwoScale;


extern double k_xmathExponentialNumeratorCubicCoefficient;


extern float k_xmathArcCosineLowerClamp;

extern double k_xmathExponentialRoundingAndDenominatorConstant;

extern f32 XMath_EvaluateArcTangent(f32 value);

extern float k_xmathCosinePhaseOffset;


extern float k_xmathArcTangentCoefficientAndOffset;


extern f32 XMath_EvaluateArcCosine(f32 x);

extern float k_xmathArcCosineCoefficientAndOffset;


extern float k_xmathArcTangentCoefficientPairThree;

extern f64 XMath_EvaluateExponentialDouble(f64 x);

extern double k_xmathExponentialReductionTrailingTerm;

extern double k_xmathExponentialDenominatorQuadraticCoefficient;


extern f64 Log10Double(f64 value);

extern float k_xmathArcSineCoefficientPairTwo;




extern float k_xmathArcSineClampConstants;

extern f32 XMath_EvaluateTangent(f32 angle);


extern double k_xmathNaturalLogToBaseTenScale;

extern double k_xmathExponentialLowerLimit;


extern float k_xmathPlaneDenominatorUpperTolerance;

extern f64 XMath_SplitDoubleExponent(f64 value, s32 *exponentOut);

extern float k_xmathArcTangentReductionUnit;

extern float k_xmathVectorAngleUpperThreshold;

extern float k_xmathPlaneParallelFraction;

union DoubleBits;
union DoubleBits {
    f64 d;
    struct {
        u32 hi;
        u32 lo;
    } w;
};


extern double k_xmathExponentialNumeratorLinearCoefficient;

extern double k_xmathExponentialReductionLeadingTerm;

extern float k_xmathArcSineCoefficientPairThree;

extern float k_xmathArcCosineCoefficientPairTwo;

extern float k_xmathArcSineResultConstants;


extern double k_xmathPositiveAnglePeriodDouble;

extern float k_xmathPositiveAngleModuloThreshold;

extern float k_xmathArcTangentCoefficientPairTwo;
#endif
