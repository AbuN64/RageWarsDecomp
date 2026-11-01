#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"
#include "CAMERA/GSKY_RESETHEADBOB.H"

extern f32 k_cameraInitialBobRateY;






void Gsky_ResetHeadBob(GameplayCamera *camera) {
    if (camera != 0) {
        f32 f0 = k_cameraInitialBobAmplitudeX;
        f32 f1 = k_cameraInitialBobAmplitudeY;
        f32 f2 = k_cameraInitialBobRateX;
        f32 f3 = k_cameraInitialBobRateY;

        camera->bobPhaseX = 0;
        camera->bobPhaseY = 0;
        camera->bobAmplitudeX = f0;
        camera->bobAmplitudeY = f1;
        camera->bobRateX = f2;
        camera->bobRateY = f3;
    }
}

void Gsky_HeadBobInitializeNoOp(void) {
}

void Gsky_HeadBobUpdateNoOp(void) {
}
