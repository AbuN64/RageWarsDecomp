#include "COMMON/OBJRECAT3CV2.H"
#include "MATH/DOUBLEBITS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MATH/math_double.H"
#include "MATH/XMATH_EVALUATEEXPONENTIALDOUBLE.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"

/* Rounds a double up to the next integer by the 2^52 add-and-subtract trick, handling negative values through an inlined round-down that recurses back into this function. Adapted from XMath_FloorDouble with the rounding direction reversed, the negative case routed through an inline copy of the round-down and the constants changed. */





static inline f64 round_down(f64 value) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = k_xmathCeilIntegralLimit;
    if (limit <= value) {
        return value;
    }
    if (value < k_xmathCeilSignBoundary) {
        return -XMath_CeilDouble(-value);
    }
    temp = value;
    temp += limit;
    temp -= limit;
    if (value < temp) {
        integral = temp - k_xmathCeilIntegralBias;
    } else {
        integral = temp;
    }
    return integral;
}




extern f64 NaturalLogDouble(f64 value);

/* Returns e raised to a double: 1 for arguments of negligible magnitude, and otherwise splits the argument into k ln 2 plus a remainder r, evaluates the rational approximation 1/2 + p(r)/(q(r) - p(r)) and scales it by two to the power k + 1 through ScaleDoubleExponent_XmathEvaluateexponentialdouble. */














/* Returns the arcsine of a value clamped to [-1, 1] using the polynomial approximation pi/2 - sqrt(1 - x) * p(x) on its magnitude and restoring the sign afterwards. */








/* Returns the arccosine of a value clamped to [-1, 1] as pi/2 minus the arcsine, which is computed by the polynomial approximation pi/2 - sqrt(1 - x) * p(x) on the magnitude with the sign restored. Adapted from XMath_EvaluateArcSine with the constants moved to k_xmathArcCosineUpperClamp through k_xmathArcCosineHalfPi and the final subtraction from pi/2 added. */








/** Perform the pair of adjacent no-op hooks at VRAM 0x8029E8A0. */
void XMath_InitializeMath(void) {
}

void XMath_ShutdownMath(void) {
}

f32 XMath_SquareFloat(f32 value) {
    return value * value;
}

void XMath_EvaluatePositiveSquareRoot(f32 value) {
    if (!(value <= 0.0f)) {
        Gu_Sqrtf(value);
    }
}

f32 XMath_EvaluateReciprocalSquareRoot(f32 value) {
    f32 squareRoot;

    if (value <= 0.0f) {
        squareRoot = 0.0f;
    } else {
        squareRoot = Gu_Sqrtf(value);
    }
    return k_xmathReciprocalSquareRootUnit / squareRoot;
}

f32 XMath_OffsetFloatRemainder(f32 value, f32 divisor) {
    f32 result;
    result = (f32) FloatModulo((f64) value, (f64) divisor);
    if (result < divisor) {
        result += divisor;
    }
    return result;
}

f64 XMath_FloorDouble(f64 value) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = k_xmathFloorIntegralLimit;
    if (limit <= value) {
        return value;
    }
    if (value < k_xmathFloorSignBoundary) {
        return -XMath_CeilDouble(-value);
    }
    temp = value;
    temp += limit;
    temp -= limit;
    if (value < temp) {
        integral = temp - k_xmathFloorIntegralBias;
    } else {
        integral = temp;
    }
    return integral;
}

f64 XMath_CeilDouble(f64 value) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = k_xmathCeilIntegralLimit;
    if (limit <= value) {
        return value;
    }
    if (value < k_xmathCeilSignBoundary) {
        return -round_down(-value);
    }
    temp = value;
    temp += limit;
    temp -= limit;
    if (temp < value) {
        integral = temp + k_xmathCeilRoundUpUnit;
    } else {
        integral = temp;
    }
    return integral;
}

f64 XMath_SplitDoubleFraction(f64 value, f64 *whole) {
    f64 temp;
    f64 integral;
    f64 limit;

    limit = k_xmathFractionIntegralLimit;
    if (limit <= value) {
        integral = value;
    } else {
        if (value < k_xmathFractionSignBoundary) {
            integral = -XMath_CeilDouble(-value);
        } else {
            temp = value;
            temp += limit;
            temp -= limit;
            if (value < temp) {
                integral = temp - k_xmathFractionIntegralBias;
            } else {
                integral = temp;
            }
        }
    }
    *whole = integral;
    return value - integral;
}

f32 XMath_AbsoluteFloat(f32 value) {
    if (value >= 0.0f) {
        return value;
    }
    return -value;
}

s32 XMath_AbsoluteInteger(s32 value) {
    if (value < 0) {
        if (value) {
            return -value;
        } else {
            return -value;
        }
    }
    return value;
}

/* Returns the base-10 logarithm of a double: NaturalLogDouble(value) times 1/ln 10. */
f64 Log10Double(f64 value) {
    return NaturalLogDouble(value) * k_xmathNaturalLogToBaseTenScale;
}

f64 XMath_EvaluateExponentialDouble(f64 x) {
    f64 r;
    f64 t;
    f64 p;
    f64 q;
    s32 k;

    if (k_xmathExponentialUpperLimit < x) {
        f64 result = k_xmathExponentialInitialResult;
        if (x < k_xmathExponentialLowerLimit) return result;
    }
    t = x * k_xmathExponentialBaseTwoScale;
    k = t;
    if (k < 0) {
        k--;
    }
    if (k_xmathExponentialRoundingAndDenominatorConstant <= t - k) {
        k++;
    }
    r = x - k * k_xmathExponentialReductionLeadingTerm + k * k_xmathExponentialReductionTrailingTerm;
    t = r * r;
    p = ((t * k_xmathExponentialNumeratorCubicCoefficient + k_xmathExponentialNumeratorLinearCoefficient) * t + k_xmathExponentialNumeratorConstant) * r;
    q = (t * k_xmathExponentialDenominatorQuadraticCoefficient + k_xmathExponentialDenominatorLinearCoefficient) * t + k_xmathExponentialRoundingAndDenominatorConstant;
    return ScaleDoubleExponent(p / (q - p) + k_xmathExponentialRoundingAndDenominatorConstant, k + 1);
}

f64 XMath_SplitDoubleExponent(f64 value, s32 *exponent) {
    DoubleBits u;
    f64 special;

    special = k_xmathExponentSpecialValue;
    if (value != special) {
        if (k_xmathExponentSpecialValue || exponent) {
            goto normal;
        } else {
            goto normal;
        }
    }
    *exponent = 0;
    return special;
normal:
    u.d = value;

    *exponent = ((u.w.hi >> 20) & 0x7FF) - 1022;
    u.w.hi = (u.w.hi & 0x800FFFFF) | 0x3FE00000;
    return u.d;
}

void XMath_EvaluateCosine(f32 angle) {
    ((s32 (*)(f32))XMath_EvaluateSine)(angle + k_xmathCosinePhaseOffset);
}

f32 XMath_EvaluateTangent(f32 angle) {
    f32 r1 = XMath_EvaluateSine(angle);
    f32 r2 = XMath_EvaluateSine(angle + k_xmathTangentCosinePhaseOffset);
    return r1 / r2;
}

f32 XMath_EvaluateArcTangent(f32 value) {
    f32 reducedValueSquared;
    f32 reducedValue;
    f32 result;
    f32 magnitude;

    magnitude = value;
    if (value < 0.0f) {
        magnitude = -value;
    }
    reducedValue = (magnitude - k_xmathArcTangentReductionUnit) / (magnitude + k_xmathArcTangentReductionUnit);
    reducedValueSquared = reducedValue * reducedValue;
    result = (((((((((((((((reducedValueSquared * k_xmathArcTangentPolynomialLeadingCoefficient) + k_xmathArcTangentCoefficientPairOne) * reducedValueSquared) - *(&k_xmathArcTangentCoefficientPairOne + 1)) * reducedValueSquared) + k_xmathArcTangentCoefficientPairTwo) * reducedValueSquared) - *(&k_xmathArcTangentCoefficientPairTwo + 1)) * reducedValueSquared) + k_xmathArcTangentCoefficientPairThree) * reducedValueSquared) - *(&k_xmathArcTangentCoefficientPairThree + 1)) * reducedValueSquared) + k_xmathArcTangentCoefficientAndOffset) * reducedValue) + *(&k_xmathArcTangentCoefficientAndOffset + 1);
    if (value < 0.0f) {
        result = -result;
    }
    return result;
}

f32 XMath_EvaluateArcSine(f32 x) {
    s32 negative;
    f32 poly;
    f32 root;
    f32 result;

    if (k_xmathArcSineClampConstants < x) {
        x = k_xmathArcSineClampConstants;
    }
    do {
        if (x < *(&k_xmathArcSineClampConstants + 1)) {
            x = *(&k_xmathArcSineClampConstants + 1);
        }
        negative = 0;
        if (x < 0.0f) {
            negative = 1;
            x = -x;
        }
        poly = (((((x * k_xmathArcSineCoefficientPairOne + *(&k_xmathArcSineCoefficientPairOne + 1)) * x - k_xmathArcSineCoefficientPairTwo) * x + *(&k_xmathArcSineCoefficientPairTwo + 1)) * x
                 - k_xmathArcSineCoefficientPairThree) * x) + *(&k_xmathArcSineCoefficientPairThree + 1);
        x = k_xmathArcSineClampConstants - x;
        if (x <= 0.0f) {
            root = 0.0f;
        } else {
            root = Gu_Sqrtf(x);
        }
    } while (0);
    result = k_xmathArcSineResultConstants - root * poly;
    if (negative) {
        result = -result;
    }
    return result;
}

f32 XMath_EvaluateArcCosine(f32 x) {
    s32 negative;
    f32 poly;
    f32 root;
    f32 result;

    if (*(&k_xmathArcSineResultConstants + 1) < x) {
        x = *(&k_xmathArcSineResultConstants + 1);
    }
    do {
        if (x < k_xmathArcCosineLowerClamp) {
            x = k_xmathArcCosineLowerClamp;
        }
        negative = 0;
        if (x < 0.0f) {
            negative = 1;
            x = -x;
        }
        poly = (((((x * (-0.011680527590215206f) + k_xmathArcCosineCoefficientPairOne) * x - *(&k_xmathArcCosineCoefficientPairOne + 1)) * x + k_xmathArcCosineCoefficientPairTwo) * x
                 - *(&k_xmathArcCosineCoefficientPairTwo + 1)) * x) + k_xmathArcCosineCoefficientAndOffset;
        x = *(&k_xmathArcSineResultConstants + 1) - x;
        if (x <= 0.0f) {
            root = 0.0f;
        } else {
            root = Gu_Sqrtf(x);
        }
    } while (0);
    result = *(&k_xmathArcCosineCoefficientAndOffset + 1) - root * poly;
    if (negative) {
        result = -result;
    }
    return *(&k_xmathArcCosineCoefficientAndOffset + 1) - result;
}
