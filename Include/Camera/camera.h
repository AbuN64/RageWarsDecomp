#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H
#include "Camera/fade_and_color_blend_views.h"
#include "Common/animation.h"
#include "Engine/Audio/channel.h"
#include "Common/viewflags.h"
#include "Common/runtime_declarations.h"
#include "Common/weapon_screen_message_operations.h"
#include "Menu/Items/Scene/scene_buildcachedgeometry.h"
#include "Common/gameplay_camera.h"
#include "Common/aiprofile.h"
struct ViewFlags;
struct Overlay;
struct View;
extern void Camera_DrawAndAdvanceMessages(struct ScreenMessageOwner*race, struct GameplayCamera*racer);
extern void Camera_DrawViewportBorder(struct GameplayCamera*racer);
extern void Camera_UpdateScreenMessages(struct ScreenMessageOwner*owner, struct GameplayCamera*pool);
extern struct ViewFlags g_cameraRenderFlagState;

extern void Camera_AccumulateDistanceScaledShake(CShake *shake, CVector3 position, CVector3 *out);
extern void Camera_AdvanceOverlayFade(struct Overlay *overlay);
extern void Camera_DrawViewportOverlays(struct View *entity);
extern void Camera_AnimateViewColorsAndLight(struct View *actor);
extern void Camera_BlendEnvironmentColors(struct View *self);
extern void Camera_BuildShakenViewTransform(void *cameraTransform);
extern void Camera_UpdateFrustumBounds(struct GameplayCamera *camera);
extern void Camera_SetupViewportAndFog(struct GameplayCamera *view);
extern void Camera_DrawWorldViewLayers(char *view, char *world);
extern const unsigned char k_CameraEncodedBytes[13];
extern void Camera_EaseViewportRectangle(struct GameplayCamera *camera, f32 a, f32 b, f32 c, f32 d);
extern void Camera_DrawActiveViews(struct ScreenMessageOwner *race, s32 world);
struct GameplayCamera;
void Camera_UpdateViewProjectionAndEffects(struct GameplayCamera *camera);
struct ScreenMessageOwner;
void Camera_UpdateViewportLayoutAndBounds(struct ScreenMessageOwner *state);
extern const char g_camerasText[];
extern CCameraText * Camera_PostScreenMessage(struct ScreenMessageOwner *owner, struct GameplayCamera *pool, u8 *text);

#endif
