#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MATH/math_double.H"
#include "UI/X_FILES/X_MATH.H"

/* Converts an array of three angles into another angle triple via sine/cosine products, clamping and atan2-style calls, and writes it back. Adapted from XMath_ConvertYxzToZyxAngles, with the clamped product, branch products, fallback call, and result order changed. */









void XMath_ConvertZyxToYxzAngles(f32 *angles) {
    f32 sinFirstAngle;
    f32 cosFirstAngle;
    f32 sinSecondAngle;
    f32 cosSecondAngle;
    f32 sinThirdAngle;
    f32 cosThirdAngle;
    f32 angle;
    f32 test;
    f32 out1;
    f32 out2;

    XMath_EvaluateSineCosine(angles[0], &sinFirstAngle, &cosFirstAngle);
    XMath_EvaluateSineCosine(angles[1], &sinSecondAngle, &cosSecondAngle);
    XMath_EvaluateSineCosine(angles[2], &sinThirdAngle, &cosThirdAngle);
    test = (cosFirstAngle * sinThirdAngle * sinSecondAngle) - (sinFirstAngle * cosThirdAngle);
    if ((1.0f) < test) {
        test = (1.0f);
    }
    if (test < (-1.0f)) {
        test = (-1.0f);
    }
    angle = XMath_EvaluateArcSine(-test);
    test = ((f32 (*)(f32))XMath_EvaluateCosine)(angle);
    if (((9.9999997473787516e-05f) < test) || (test < (-9.9999997473787516e-05f))) {
        f32 product = cosFirstAngle * cosThirdAngle;
        f32 cross = sinFirstAngle * sinThirdAngle;
        f32 first0 = (product * sinSecondAngle) + cross;
        f32 first1 = cosFirstAngle * cosSecondAngle;
        f32 second0 = cosSecondAngle * sinThirdAngle;
        f32 second1 = (cross * sinSecondAngle) + product;
        out1 = XMath_EvaluateArcTangentTwo(first0, first1);
        out2 = XMath_EvaluateArcTangentTwo(second0, second1);
    } else {
        out1 = 0.0f;
        out2 = XMath_EvaluateArcTangentTwo(-sinSecondAngle, cosSecondAngle * cosThirdAngle);
    }
    angles[0] = angle;
    angles[1] = out1;
    angles[2] = out2;
}

/* Converts a vector of three angles into another angle triple via sine/cosine products, clamping and atan2-style calls, and writes it back. Adapted from XMath_ConvertYzxToZyxAngles, with the clamped product, the branch products, and the stored order of the second and third results changed. */











void XMath_ConvertZyxToYzxAngles(CVector3 *angles) {
    f32 sinFirstAngle;
    f32 cosFirstAngle;
    f32 sinSecondAngle;
    f32 cosSecondAngle;
    f32 sinThirdAngle;
    f32 cosThirdAngle;
    f32 outX;
    f32 outZ;
    f32 clamped;
    f32 angle;
    f32 test;

    XMath_EvaluateSineCosine(angles->x, &sinFirstAngle, &cosFirstAngle);
    XMath_EvaluateSineCosine(angles->y, &sinSecondAngle, &cosSecondAngle);
    XMath_EvaluateSineCosine(angles->z, &sinThirdAngle, &cosThirdAngle);

    clamped = cosSecondAngle * sinThirdAngle;
    if ((1.0f) < clamped) {
        clamped = (1.0f);
    }
    if (clamped < (-1.0f)) {
        clamped = (-1.0f);
    }

    angle = XMath_EvaluateArcSine(clamped);
    test = ((f32 (*)(f32))XMath_EvaluateCosine)(angle);
    if (((9.9999997473787516e-05f) < test) || (test < (-9.9999997473787516e-05f))) {
        f32 saved18 = sinSecondAngle;
        f32 product = saved18 * sinThirdAngle;
        f32 saved10 = sinFirstAngle;
        f32 saved24 = cosThirdAngle;
        f32 secondArg = cosSecondAngle * saved24;
        f32 t = cosFirstAngle * product;

        outX = XMath_EvaluateArcTangentTwo((saved10 * saved24) - t,
                             (saved10 * product) + (cosFirstAngle * saved24));
        outZ = XMath_EvaluateArcTangentTwo(saved18, secondArg);
    } else {
        { f32 t = sinFirstAngle * sinSecondAngle * cosThirdAngle; outX = XMath_EvaluateArcTangentTwo(sinFirstAngle * cosSecondAngle, (cosFirstAngle * sinThirdAngle) - t); }
        outZ = 0.0f;
    }

    angles->x = outX;
    angles->y = outZ;
    angles->z = angle;
}






void XMath_ConvertYzxToZyxAngles(CVector3 *angles) {
    f32 sinFirstAngle;
    f32 cosFirstAngle;
    f32 sinSecondAngle;
    f32 cosSecondAngle;
    f32 sinThirdAngle;
    f32 cosThirdAngle;
    f32 outX;
    f32 outZ;
    f32 clamped;
    f32 angle;
    f32 test;

    XMath_EvaluateSineCosine(angles->x, &sinFirstAngle, &cosFirstAngle);
    XMath_EvaluateSineCosine(angles->y, &sinSecondAngle, &cosSecondAngle);
    XMath_EvaluateSineCosine(angles->z, &sinThirdAngle, &cosThirdAngle);

    clamped = -sinSecondAngle * cosThirdAngle;
    if ((1.0f) < clamped) {
        clamped = (1.0f);
    }
    if (clamped < (-1.0f)) {
        clamped = (-1.0f);
    }

    angle = XMath_EvaluateArcSine(-clamped);
    test = ((f32 (*)(f32))XMath_EvaluateCosine)(angle);
    if (((9.9999997473787516e-05f) < test) || (test < (-9.9999997473787516e-05f))) {
        f32 product = sinSecondAngle * sinThirdAngle;
        f32 saved10 = sinFirstAngle;
        f32 saved20 = cosSecondAngle;
        f32 saved21 = sinThirdAngle;
        f32 secondArg = saved20 * cosThirdAngle;

        outX = XMath_EvaluateArcTangentTwo((cosFirstAngle * product) + (saved10 * saved20),
                             (-saved10 * product) + (saved20 * cosFirstAngle));
        outZ = XMath_EvaluateArcTangentTwo(saved21, secondArg);
    } else {
        outX = XMath_EvaluateArcTangentTwo(-cosThirdAngle * sinFirstAngle, cosThirdAngle * cosFirstAngle);
        outZ = 0.0f;
    }

    angles->x = outX;
    angles->y = angle;
    angles->z = outZ;
}






void XMath_ConvertYxzToZyxAngles(f32 *angles) {
    f32 sinFirstAngle;
    f32 cosFirstAngle;
    f32 sinSecondAngle;
    f32 cosSecondAngle;
    f32 sinThirdAngle;
    f32 cosThirdAngle;
    f32 angle;
    f32 test;
    f32 out0;
    f32 out2;

    XMath_EvaluateSineCosine(angles[0], &sinFirstAngle, &cosFirstAngle);
    XMath_EvaluateSineCosine(angles[1], &sinSecondAngle, &cosSecondAngle);
    XMath_EvaluateSineCosine(angles[2], &sinThirdAngle, &cosThirdAngle);
    test = (cosSecondAngle * sinFirstAngle * sinThirdAngle) - (sinSecondAngle * cosThirdAngle);
    if ((1.0f) < test) {
        test = (1.0f);
    }
    if (test < (-1.0f)) {
        test = (-1.0f);
    }
    angle = XMath_EvaluateArcSine(-test);
    test = ((f32 (*)(f32))XMath_EvaluateCosine)(angle);
    if (((9.9999997473787516e-05f) < test) || (test < (-9.9999997473787516e-05f))) {
        f32 product = cosSecondAngle * cosThirdAngle;
        f32 cross = sinSecondAngle * sinThirdAngle;
        f32 first0 = cross + (sinFirstAngle * product);
        f32 first1 = cosFirstAngle * cosSecondAngle;
        f32 second0 = cosFirstAngle * sinThirdAngle;
        f32 second1 = product + (cross * sinFirstAngle);
        out0 = XMath_EvaluateArcTangentTwo(first0, first1);
        out2 = XMath_EvaluateArcTangentTwo(second0, second1);
    } else {
        out0 = XMath_EvaluateArcTangentTwo(sinFirstAngle, cosFirstAngle * cosThirdAngle);
        out2 = 0.0f;
    }
    angles[0] = out0;
    angles[1] = angle;
    angles[2] = out2;
}

f32 XMath_EvaluateSine(f32 angle) {
    f32 angleSquared;
    f32 result;
    f32 reducedAngle;
    f32 workingAngle;
    s32 resultSign;

    workingAngle = angle;
    resultSign = 1;
    reducedAngle = workingAngle;
    if (((25.132743835449219f) < workingAngle) || (workingAngle < (-25.13274383544922f))) {
        FloatModulo((f64)workingAngle, (6.2831859588623047));
    } else {
        if ((6.2831859588623047f) < workingAngle) {
            do {
                reducedAngle -= (6.2831859588623047f);
            } while ((6.2831859588623047f) < reducedAngle);
        }
        result = 0.0f;
        if (reducedAngle < result) {
            do {
                reducedAngle += (6.283185958862305f);
            } while (reducedAngle < result);
        }
    }
    if (workingAngle < (-1.5707963705062866f)) {
        do {
            workingAngle += (6.2831854820251465f);
        } while (workingAngle < (-1.5707963705062866f));
    }
    if ((4.7123889923095703f) < workingAngle) {
        do {
            workingAngle -= (6.2831854820251465f);
        } while ((4.7123889923095703f) < workingAngle);
    }
    if ((1.5707963705062866f) < workingAngle) {
        resultSign = -1;
        workingAngle -= (3.1415927410125732f);
    }
    angleSquared = workingAngle * workingAngle;
    result = (((((((angleSquared * (2.7557318844628753e-06f)) - (0.00019841270113829523f)) * angleSquared) + (0.0083333337679505348f)) * angleSquared) - (0.1666666716337204f)) * angleSquared * workingAngle) + workingAngle;
    if (resultSign < 0) {
        result = -result;
    }
    return result;
}

/* Computes the sine and cosine of an angle by reducing it into one turn, folding it into a quadrant, and evaluating one odd polynomial for each output.
   Adapted from XMath_EvaluateSine with the fmod result kept and copied back into the angle, a shared zero local for the wrap loops, the quadrant fold producing a sine and a cosine argument, and both polynomials computed before the two pointer stores changed. */













void XMath_EvaluateSineCosine(f32 angle, f32 *sinOut, f32 *cosOut) {
    f32 r;
    f32 zero;
    f32 s;
    f32 c;
    f32 s2;
    f32 c2;
    f32 ps;
    f32 pc;

    r = angle;
    if (((25.132743835449219f) < angle) || (angle < (-25.13274383544922f))) {
        r = FloatModulo((f64)angle, (6.2831859588623047));
    } else {
        if ((6.2831859588623047f) < angle) {
            do {
                r -= (6.2831859588623047f);
            } while ((6.2831859588623047f) < r);
        }
        zero = 0.0f;
        if (r < zero) {
            do {
                r += (6.283185958862305f);
            } while (r < zero);
        }
    }
    angle = r;
    zero = 0.0f;
    while (angle < zero) {
        angle += (6.2831854820251465f);
    }
    if ((6.2831854820251465f) <= angle) {
        do {
            angle -= (6.2831854820251465f);
        } while ((6.2831854820251465f) <= angle);
    }
    if ((3.1415929794311523f) <= angle) {
        if ((4.7123894691467285f) <= angle) {
            angle -= (4.7123894691467285f);
            s = angle - (1.5707964897155762f);
            c = angle;
        } else {
            angle -= (3.1415929794311523f);
            s = -angle;
            c = angle - (1.5707964897155762f);
        }
    } else if ((1.5707964897155762f) <= angle) {
        angle -= (1.5707964897155762f);
        s = (1.5707964897155762f) - angle;
        c = -angle;
    } else {
        s = angle;
        c = (1.5707964897155762f) - angle;
    }
    s2 = s * s;
    c2 = c * c;
    ps = ((((((((s2 * (2.7557318844628753e-06f)) - (0.00019841270113829523f)) * s2) + (0.008333333767950535f)) * s2) - (0.1666666716337204f)) * s2) + (1.0f)) * s;
    pc = ((((((((c2 * (2.7557318844628753e-06f)) - (0.00019841270113829523f)) * c2) + (0.008333333767950535f)) * c2) - (0.1666666716337204f)) * c2) + (1.0f)) * c;
    *sinOut = ps;
    *cosOut = pc;
}

/* Returns the hyperbolic tangent of a double: 1 beyond 25.3, 1 - 2/(exp(2|x|) + 1) above atanh(0.5) with exp computed inline by a rational approximation scaled by ScaleDoubleExponent_XmathEvaluateexponentialdouble (ldexp), and the odd rational series x + x^3 P(x^2)/Q(x^2) for small arguments, with the sign of x restored. */



static inline f64 exp_inline_tanh(f64 x) {
    f64 t;
    f64 r;
    f64 p;
    s32 k;

    if (-2.710504946537621e-20 < x && x < 2.710504946537621e-20) {
        return 1.0;
    }
    t = x * 1.4426950216293335;
    k = t;
    if (k < 0) {
        k--;
    }
    if (0.5 <= t - k) {
        k++;
    }
    r = x - k * 0.693359375 + k * 2.1219444170128557e-4;
    t = r * r;
    p = ((t * 1.652032915444579e-5 + 6.943599786609411e-3) * t + 0.25) * r;
    return ScaleDoubleExponent(p / ((t * 4.9586285604164e-4 + 5.55538684129715e-2) * t + 0.5 - p) + 0.5, k + 1);
}

f64 XMath_EvaluateHyperbolicTangent(f64 x) {
    f64 z;
    f64 s;
    f64 result;

    z = x;
    if (x < 0.0) {
        z = -x;
    }
    if (z > 25.299999237060547) {
        result = 1.0;
    } else if (z > 0.5493061542510986) {
        result = exp_inline_tanh(z + z);
        result = 0.5 - 1.0 / (result + 1.0);
        result = result + result;
    } else if (z < 2.3000000515249751e-10) {
        result = z;
    } else {
        s = z * z;
        result = z + z * (((s * -0.9643748998641968 - 99.2259292602539) * s - 1613.411865234375) * s)
                / (((s + 112.74474334716795) * s + 2233.77197265625) * s + 4840.23583984375);
    }
    if (x < 0.0) {
        result = -result;
    }
    return result;
}

/* Returns the angle of the vector (x, y) in radians, atan2(y, x): both components within 1e-6 of zero are snapped to zero, the axes return exact multiples of pi/2, and otherwise the arctangent of |y/x| comes from the (t - 1)/(t + 1) series around pi/4, negated for a negative ratio and offset by the quadrant's term from k_xmathAtanQuadrantOffsets. */


f32 XMath_EvaluateArcTangentTwo(f32 y, f32 x) {
    s32 quadrant;
    f32 ratio;
    f32 magnitude;
    f32 t;
    f32 t2;
    f32 angle;

    if (-1e-6f < x && x < 1e-6f) {
        x = 0.0f;
    }
    if (-1e-6f < y && y < 1e-6f) {
        y = 0.0f;
    }
    if (x == 0.0f && y == 0.0f) {
        return 0.0f;
    }
    if (x == 0.0f) {
        if (y >= 0.0f) {
            return 1.5707964f;
        }
        return -1.5707964f;
    }
    if (y == 0.0f) {
        if (x >= 0.0f) {
            return 0.0f;
        }
        return 3.1415927f;
    }
    quadrant = 0;
    if (x < 0.0f) {
        quadrant = 1;
    }
    if (y < 0.0f) {
        quadrant |= 2;
    }
    ratio = y / x;
    magnitude = ratio;
    if (quadrant != 0 && quadrant != 3) {
        magnitude = -ratio;
    }
    if (magnitude < 1e-6f) {
        return k_xmathAtanQuadrantOffsets[quadrant];
    }
    magnitude = ratio;
    if (ratio < 0.0f) {
        magnitude = -ratio;
    }
    t = (magnitude - 1.0f) / (magnitude + 1.0f);
    t2 = t * t;
    angle = (((((((-0.004054058f * t2 + 0.021861229f) * t2 - 0.055909887f) * t2 + 0.09642004f) * t2
                 - 0.13908534f) * t2 + 0.19946536f) * t2 - 0.33329856f) * t2 + 0.99999934f) * t
            + 0.7853982f;
    if (ratio < 0.0f) {
        angle = -angle;
    }
    return angle + k_xmathAtanQuadrantOffsets[quadrant];
}

extern f32 Gu_Sqrtf(f32);
/** Square root that returns 0 for zero or negative input. */
static inline f32 safeSqrt(f32 value) {
    if (value <= 0.0f) {
        return 0.0f;
    }
    return Gu_Sqrtf(value);
}
/** Length of a 3-vector. */
static inline f32 vectorLength(f32 *v) {
    return safeSqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
/** Arc sine by polynomial: clamps to [-1, 1], pi/2 - sqrt(1 - |x|) * poly(|x|), sign restored. */
static inline f32 arcSin(f32 x) {
    s32 negative;
    f32 polynomial;
    f32 result;
    if (x > 1.0f) {
        x = 1.0f;
    }
    if (x < -1.0f) {
        x = -1.0f;
    }
    negative = 0;
    if (x < 0.0f) {
        negative = 1;
        x = -x;
    }
    polynomial = (((((x * -0.0116805276f + 0.0308918804f) * x - 0.0501743034f) * x + 0.0889789909f) * x - 0.214598805f) * x + 1.57079625f);
    result = 1.5707964f - safeSqrt(1.0f - x) * polynomial;
    if (negative) {
        result = -result;
    }
    return result;
}
/** Arc cosine as pi/2 - arcSin. */
static inline f32 arcCos(f32 x) {
    return 1.5707964f - arcSin(x);
}
/** Angle between two 3-vectors, 0 when either has zero length. */
f32 VectorAngle(f32 *a, f32 *b) {
    f32 lengthA = vectorLength(a);
    f32 lengthB = vectorLength(b);
    f32 product = lengthA * lengthB;
    f32 value;
    if (product == 0.0f) {
        return 0.0f;
    }
    value = (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]) / product;
    if (value > 1.0f) {
        value = 1.0f;
    } else if (value < -1.0f) {
        value = -1.0f;
    }
    return arcCos(value);
}
