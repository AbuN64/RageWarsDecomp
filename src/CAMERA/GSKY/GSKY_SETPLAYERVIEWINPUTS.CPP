#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/WORLD.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"

/* Stores its parameters into the object at camera offsets 0x24 through 0x60, then refreshes the object's ground reference and picks its surface value at 0x64 from the ground under it. Adapted from Gsky_UpdateFloorSurface with the parameter block stores added and the k_cameraInputSurfaceDistanceScale thresholds changed. */



extern s32 Cinema_IsSequenceInWindow(void);

extern f32 Region_GetPolygonHeight(s32 node, f32 positionX, f32 positionZ);










void Gsky_SetPlayerViewInputs(GameplayCamera *camera, s32 bobSuppression, f32 lensFlareInputOne, f32 lensFlareInputTwo, f32 lensFlareInputThree, f32 lensFlareInputFour, f32 floorSampleX,
                   f32 floorSampleY, f32 floorSampleZ, f32 floorHeightOffset, Shared_Quad floorSampleData, s32 floorPolygon, f32 requestedZoomBlend,
                   f32 requestedZoomFov) {
    s32 object;
    f32 value;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    camera->bobSuppressed = bobSuppression;
    camera->lensFlareInputOne = lensFlareInputOne;
    camera->lensFlareInputTwo = lensFlareInputTwo;
    camera->lensFlareInputThree = lensFlareInputThree;
    camera->lensFlareInputFour = lensFlareInputFour;
    camera->floorSampleX = floorSampleX;
    camera->floorSampleY = floorSampleY;
    camera->floorSampleZ = floorSampleZ;
    camera->floorHeightOffset = floorHeightOffset;
    camera->floorSampleData = floorSampleData;
    camera->floorPoly = (void *)floorPolygon;
    camera->zoomBlend = requestedZoomBlend;
    camera->zoomFov = requestedZoomFov;
    if (Cinema_IsSequenceInWindow() != 0) {
        camera->floorPoly = (void *)Scene_FindFloorPolygon(&g_world, &camera->floorSampleX);
    }
    object = (s32)camera->floorPoly;
    x = camera->floorSampleX;
    y = camera->floorSampleY;
    z = camera->floorSampleZ;
    w = camera->floorHeightOffset;
    camera->floorSurface = g_defaultCameraSurfaceType;
    if (object != 0 && Cinema_IsSequenceInWindow() == 0) {
        value = ((y + w) - Region_GetPolygonHeight(object, x, z)) * k_cameraInputSurfaceDistanceScale;
        if (value < k_cameraInputSurfaceUpperDistance && k_cameraInputSurfaceLowerDistance < value) {
            camera->floorSurface = ((MenuRules *)(object))->locked;
        }
    }
    if (Cinema_IsSequenceInWindow() != 0) {
        camera->floorSurface = g_defaultCameraSurfaceType;
    }
    if (camera->zoomBlend > 0.0f) {
        camera->floorSurface = g_defaultCameraSurfaceType;
    }
}
