#include "COMMON/TRIPLE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/STREAM.H"
#include "TYPES.H"
#include "ENGINE/ANIM/POLYTRAK2.H"

/* Converts an amount over a period into a whole rate: returns g_motionQuantizedRateZero for an amount
 * equal to it or a period not above g_motionQuantizedRatePeriodThreshold; otherwise the ratio scaled by g_motionQuantizedRatePeriodThreshold + 4 and rounded up
 * when that stays below the limit g_motionMinimumQuantizedRate, else the ratio scaled by g_motionQuantizedRateFallbackScale rounded up when that
 * stays below the limit, else the amount itself. Rounding up is a static helper. */






static inline f32 round_up(f32 x, f32 floor) {
    s32 i;

    if (x <= floor) {
        return (f32)(s32)x;
    }
    i = (s32)x;
    if ((f32)i == x) {
        return (f32)i;
    }
    return (f32)(i + 1);
}






f32 Polytrak2_ChooseQuantizedTrackRate(f32 amount, f32 period) {
    f32 rate;

    rate = 0.0f;
    if (amount == g_motionQuantizedRateZero) {
        return g_motionQuantizedRateZero;
    }
    if (period <= g_motionQuantizedRatePeriodThreshold) {
        return g_motionQuantizedRateZero;
    }
    rate = round_up(amount / period * g_motionQuantizedRateScale, rate);
    if (rate < g_motionMinimumQuantizedRate) {
        return rate;
    }
    rate = round_up(amount / period * g_motionQuantizedRateFallbackScale, 0.0f);
    if (rate < g_motionMinimumQuantizedRate) {
        return rate;
    }
    return amount;
}
