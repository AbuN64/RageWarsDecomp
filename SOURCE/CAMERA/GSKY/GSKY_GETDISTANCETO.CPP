#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "ENGINE/AUDIO/CHANNEL.H"

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
extern f32 Gu_Sqrtf(float value);




f32 Gsky_GetDistanceTo(void *gameplayCamera, CVector3 *targetPosition) {
    CVector3 delta;
    GameplayCamera *camera = gameplayCamera;
    Graphu64_SubtractVectors(&delta, &camera->position, targetPosition);
    return Gu_Sqrtf((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
}
