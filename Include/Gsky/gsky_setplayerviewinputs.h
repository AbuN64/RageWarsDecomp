#ifndef GSKY_GSKY_SETPLAYERVIEWINPUTS_H
#define GSKY_GSKY_SETPLAYERVIEWINPUTS_H
struct GameplayCamera;
struct Shared_Quad;
void Gsky_SetPlayerViewInputs(struct GameplayCamera *camera, s32 bobSuppression, f32 lensFlareInputOne, f32 lensFlareInputTwo, f32 lensFlareInputThree, f32 lensFlareInputFour, f32 floorSampleX, f32 floorSampleY, f32 floorSampleZ, f32 floorHeightOffset, struct Shared_Quad floorSampleData, s32 floorPolygon, f32 requestedZoomBlend, f32 requestedZoomFov);
#endif
