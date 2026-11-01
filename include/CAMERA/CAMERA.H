#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H
#include "CAMERA/FADE_AND_COLOR_BLEND_VIEWS.H"
#include "COMMON/ANIMATION.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
extern void Camera_DrawAndAdvanceMessages(Race*race, RacerViewport*racer);
extern void Camera_DrawViewportBorder(RacerViewport*racer);
extern void Camera_UpdateScreenMessages(struct ScreenMessageOwner*owner, struct ScreenMessagePool*pool);
extern ViewFlags g_cameraRenderFlagState;
extern void Scene_DrawVisibleInstances(char*, char*);
extern void Camera_AccumulateDistanceScaledShake(CShake *shake, CVector3 position, CVector3 *out);
extern void Camera_AdvanceOverlayFade(Overlay *overlay);
extern void Camera_DrawViewportOverlays(View *entity);
extern void Camera_AnimateViewColorsAndLight(View *actor);
extern void Camera_BlendEnvironmentColors(View *self);
extern void Camera_BuildShakenViewTransform(void *cameraTransform);
extern void Camera_UpdateFrustumBounds(GameplayCamera *camera);
extern void Camera_SetupViewportAndFog(RacerViewport *view);
extern void Camera_DrawWorldViewLayers(char *view, char *world);
extern const unsigned char k_CameraEncodedBytes[13];
extern void Camera_EaseViewportRectangle(GameplayCamera *camera, f32 a, f32 b, f32 c, f32 d);
extern void Camera_DrawActiveViews(Race *race, s32 world);
#endif
