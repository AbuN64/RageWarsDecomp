#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VIEWFLAGS.H"
#include "CAMERA/FADE_AND_COLOR_BLEND_VIEWS.H"
#include "TYPES.H"

/* Configures an emitter: stores a position vector, a shared value in three channels, a scale, and three rates converted by the constant in k_cameraInitialBobRateY. */



extern f32 k_cameraInitialBobRateY[];




static inline void set_emitter(ShakeEmitterChannelView *obj, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos)
{
    obj->position = pos;
    obj->scale = scale;
    obj->firstValue = value;
    obj->firstRate = a;
    obj->secondValue = value;
    obj->secondRate = b;
    obj->thirdValue = value;
    obj->thirdRate = c;
}

void Gsky_StartScaledShake(ShakeEmitterChannelView *obj, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos)
{
    if (obj != 0) {
        f32 k = k_cameraInitialBobRateY[1];
        set_emitter(obj, a * k, b * k, c * k, scale, value, pos);
    }
}
