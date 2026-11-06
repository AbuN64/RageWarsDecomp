#include "Common/weapon_special_fire.h"
#include "types.h"
#include "Common/weapon_screen_message_operations.h"
#include "include_asm.h"

/* de holds these as g_cameraShakeDistanceComplement and g_cameraShake{X,Y,Z}AngleScale (camera.cpp). */
#if !defined(VERSION_DE)
const float k_weaponShakeUnitAndDegreesToRadians[4] = {
    1.0f, 0.017453294f, 0.017453294f, 0.017453294f,
};
#endif

#if defined(VERSION_DE)
float g_weaponShakeInitialAngle = 90.0f;
float g_weaponShakeAngleRate = 3.0f;
float g_weaponShakeActiveDecay = 6.0f;
float g_weaponShakeIdleDecay = 6.0f;
float g_cameraShakeDistanceComplement = 1.0f;
float g_cameraShakeXAngleScale = 0.0174532942f;
float g_cameraShakeYAngleScale = 0.0174532942f;
float g_cameraShakeZAngleScale = 0.0174532942f;
#endif
