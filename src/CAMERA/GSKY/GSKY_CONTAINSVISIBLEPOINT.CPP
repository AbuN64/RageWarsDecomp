#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"

extern s32 Visdata_ContainsPoint(s32 planes, Triple *point);

s32 Gsky_ContainsVisiblePoint(s32 cameraAddress, Triple testPoint) {
    return Visdata_ContainsPoint((char *)&((GameplayCamera *)cameraAddress)->clipPlanes, &testPoint);
}
