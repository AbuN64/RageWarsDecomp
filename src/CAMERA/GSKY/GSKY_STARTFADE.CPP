#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"

/* The native ABI receives full words. Narrowing happens at the byte stores,
 * so callers may pass values such as 0x80 and 0xFF without sign extension. */
void Gsky_StartFade(void *camera, s32 requestedFadeMode, s32 startValue, s32 endValue, s32 stepAmount, s32 redChannel, s32 greenChannel, s32 blueChannel)
{
 do { if (camera != 0) { ((GameplayCamera *)camera)->fadeStep = (s8) stepAmount; ((GameplayCamera *)camera)->fadeMode = requestedFadeMode; ((GameplayCamera *)camera)->fadeStart = startValue; ((GameplayCamera *)camera)->fadeEnd = endValue; ((GameplayCamera *)camera)->fadeState = 0; ((GameplayCamera *)camera)->fadeRed = (s8) redChannel; ((GameplayCamera *)camera)->fadeGreen = (s8) greenChannel; ((GameplayCamera *)camera)->fadeBlue = (s8) blueChannel; ((GameplayCamera *)camera)->fadeCounter = 0; ((GameplayCamera *)camera)->fadeEnabled = 1; } } while (0);
}
