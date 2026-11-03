#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"
#include "ENGINE/VISDATA2.H"
#include "GSKY/GSKY_CONTAINSVISIBLEPOINT.H"



s32 Gsky_ContainsVisiblePoint(s32 cameraAddress, Triple testPoint) {
    return Visdata_ContainsPoint((char *)&((GameplayCamera *)cameraAddress)->clipPlanes, &testPoint);
}
