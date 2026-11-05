#ifndef COMMON_MATH_HELPERS_H
#define COMMON_MATH_HELPERS_H
#define RW_CLAMP(value, low, high) ((value) < (low) ? (low) : (value) > (high) ? (high) : (value))
#define RW_MIN(a, b) ((a) > (b) ? (b) : (a))

#define RW_MIN_LT(a, b) ((a) < (b) ? (a) : (b))
#define RW_MAX_GT(a, b) ((a) > (b) ? (a) : (b))
#define RW_ABS(value) ((value) < 0.0f ? -(value) : (value))
/* pi to six decimals: the spelling some modules folded their angle literals from (3.141593f, not 3.1415927f) */
#define RW_PI_F6 3.141593f
#endif
