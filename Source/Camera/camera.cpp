#include "Common/particle_lighting.h"
#include "Common/graphics_matrix_and_vector_math.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/viewflags.h"
#include "Common/lightdata.h"
#include "types.h"
#include "Camera/fade_and_color_blend_views.h"
#include "Common/game_session.h"
#include "Common/particle_lighting.h"
#include "Common/approachlocation.h"
#include "Fx/normalize_vector.h"
#include "Common/world.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/ballisticparams.h"
#include "Render/setn64_getpacksection.h"
#include "Common/weapon_special_fire.h"
#include "Common/resident_event_handler.h"
#include "Common/shared_menureply.h"
#include "Common/obj.h"
#include "Common/triple.h"
#include "Camera/gsky_getfloorsurfaceshake.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/gameplay_camera.h"
#include "Common/shared_gameslot.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Game/builddirectionmatrix.h"
#include "Common/player_sequence_state.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "System/textload_resettexturecache.h"
#include "Common/menu_screen_elements.h"
#include "Common/frontend_clock_state.h"
#include "Common/scene_frame_and_effect_updates.h"
#include <platform_sdk.h>
#include "Common/video_dimensions.h"
#include <PR/gbi.h>
#include "Common/display.h"
#include "Common/results.h"
#include "Render/setn64_onworldviewdraw.h"
#include "Camera/camera.h"
#include "Common/effectrender.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/trigger_and_float_value_operations.h"
#include "Common/sessionhandlerrow.h"
#include "Common/objb.h"
#include "Engine/Cache/list.h"
#include "Engine/Audio/channel.h"
#include "Common/shared_worldfunc.h"
#include <PR/abi.h>
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/heap_arena_entry.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Common/sky_layers.h"
#include "Engine/Cinema/cinema.h"
#include "Engine/session.h"
#include "onscrn.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Engine/defs.h"
#include "Engine/gregion.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Engine/visdata_decoderegiongrid.h"
#include "Fx/fx_drawcoloredribbon.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Gsky/sky.h"
#include "Gsky/sky_drawlensflare.h"
#include "Menu/Items/Scene/scene_buildcachedgeometry.h"
#include "Menu/Items/Scene/scene_drawtransparentobjects.h"
#include "Setn64/setn64_drawcolorrectangle.h"
#include "Weapons/player_updatefragtagselection.h"
#include "Weaponshake/weaponshake.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Textload/textload_resettexturecache.h"
#include "Setn64/setn64_cleardepthrect.h"
#include "Pak/menu_createmenufromtemplate.h"
#include "Onscrn/onscreen_drawscaledmaskedimage.h"
#include "Cinema/cinema.h"
#include "Setn64/setn64_updatefadetransition.h"
#include "Fx/fx_drawboundedparticlequads.h"
#include "Gsky/gsky_getfloorsurfaceshake.h"
#include "Camera/camera_address_symbols.h"
#include "Common/screenmessagesubstitution.h"

/* Samples one shake axis: a random value within the amplitude for mode 0, a sine of the scaled angle for mode 1, and zero otherwise. */
static inline f32 Camera_SampleShakeAxis(CShakeAxis *wave, f32 *angleScale) {
    switch (wave->mode) {
    case 1:
        return Gu_Sinf(wave->m_Angle * *angleScale) * wave->m_Amp;
    case 0:
        return Graphu64_RandomBetween(-wave->m_Amp, wave->m_Amp);
    }
    return 0.0f;
}

void Camera_AccumulateDistanceScaledShake(CShake *shake, CVector3 position, CVector3 *out) {
    f32 distance;

    Graphu64_SubtractVectors(&position, &position, &shake->m_vPos);
    distance = Gu_Sqrtf((position.x * position.x) +
                             (position.y * position.y) +
                             (position.z * position.z));
    if (distance < shake->m_Radius) {
        distance = Defs_CosineEase(g_cameraShakeDistanceComplement - (distance / shake->m_Radius));

        out->x += Camera_SampleShakeAxis(&shake->x, &g_cameraShakeXAngleScale) * distance;

        out->y += Camera_SampleShakeAxis(&shake->y, &g_cameraShakeYAngleScale) * distance;

        out->z += Camera_SampleShakeAxis(&shake->z, &g_cameraShakeZAngleScale) * distance;
    }
}

/* Advances an overlay's fade: state 1 fades the alpha in over fadeIn frames up to alphaMax, state 2 holds
 * alphaMax for hold frames, state 3 fades out over fadeOut frames and returns to state 0; each state change
 * restarts the timer, which otherwise advances by the frame time g_frameElapsedTime. */
void Camera_AdvanceOverlayFade(Overlay *overlay) {
    switch (overlay->state) {
    case 0:
        break;
    case 1:
        if (overlay->fadeIn <= overlay->timer) {
            overlay->state = 2;
            overlay->timer = 0.0f;
        } else {
            overlay->alpha = (u32)(overlay->timer / (overlay->fadeIn + 1) * overlay->alphaMax);
            break;
        }
        /* Fade-in finished: continue straight into the hold handling. */
    case 2:
        if (!(overlay->hold <= overlay->timer)) {
            overlay->alpha = overlay->alphaMax;
            break;
        }
        overlay->state = 3;
        overlay->timer = 0.0f;
        /* fallthrough */
    case 3:
        if (overlay->fadeOut <= overlay->timer) {
            overlay->state = 0;
            overlay->timer = 0.0f;
            break;
        }
        overlay->alpha = (u32)(overlay->alphaMax - overlay->timer / (overlay->fadeOut + 1) * overlay->alphaMax);
        break;
    }
    overlay->timer += g_frameElapsedTime;
}

/* Finishes an entity for the frame: when a player in the g_transientPlayerList list owns it, draws its rectangle
 * through SetN64_DrawColorRectangle if that player shows outlines (flag 0x1000), using the entity's colour (or the
 * override colour g_playerSequenceSavedViewBytes when g_playerSequenceCompletionPending is set, darkened when option 0x4000 is set); it then
 * notifies the player list through Playerai_UpdateViewPlayerProjection when Cinema_IsSequenceInWindow is clear and SetN64_IsModeThirteen is set,
 * and finishes the entity through Cinema_DrawSequenceOverlay. */
static inline SharedPlayer *Camera_FindPlayerOwningView(View *entity) {
    SharedPlayer *player;

    for (player = g_transientPlayerList.actorList; player != 0; player = player->views16E0.view16E0_1.next) {
        if (player->views5DC.view5DC_4.entity == entity) {
            return player;
        }
    }
    return 0;
}

void Camera_DrawViewportOverlays(View *entity) {
    SharedPlayer *owner;
    u8 color[4];
    s32 i;

    owner = Camera_FindPlayerOwningView(entity);
    if (owner == 0) {
        return;
    }
    if (owner->views1C.view38_3.flags & 0x1000) {
        color[0] = entity->color[0];
        color[1] = entity->color[1];
        color[2] = entity->color[2];
        color[3] = entity->color[3];
        if (g_playerSequenceCompletionPending != 0) {
            for (i = 0; i < 4; i++) {
                color[i] = g_playerSequenceSavedViewBytes[i];
            }
        }
        if (g_gameSettings.flags & 0x4000) {
            color[0] >>= 3;
            color[1] >>= 3;
            color[2] >>= 3;
        }
        SetN64_DrawColorRectangle(&g_gameSession, color, entity->viewport[2], entity->viewport[3], entity->viewport[2] + entity->viewport[0],
                      entity->viewport[3] + entity->viewport[1]);
    }
    if (Cinema_IsSequenceInWindow() == 0 && SetN64_IsModeThirteen() != 0) {
        Playerai_UpdateViewPlayerProjection(&g_playerViewRenderContext, entity);
    }
    Cinema_DrawSequenceOverlay(entity);
}

#if defined(VERSION_US)
const unsigned int k_cameraZeroPad[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_EU_X)
const unsigned int k_cameraZeroPad[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_EU)
const unsigned int k_cameraZeroPad[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_DE)
const unsigned int k_cameraZeroPad[1] = {
    0x00000000,
};
#endif

/* Animate the shared light colors and direction, and both actor tint colors. */
#if defined(VERSION_US_REV1)

#endif
#if defined(VERSION_US_REV1)
const unsigned int k_CameraZeroWords[1] = {
    0x00000000,
};
#endif
void Camera_AnimateViewColorsAndLight(View *actor) {
    CVector3 direction;
    f32 phaseScale;
    f32 ambientScale;
    f32 ambient;
    f32 diffuse;
    f32 red;
    f32 green;
    f32 blue;
    s32 channel;
    s8 redByte;
    s8 greenByte;
    s8 blueByte;

    phaseScale = 1.0f;
    channel = 0;
    ambientScale = phaseScale;
    do {
        ambient = (ambientScale * (Gu_Sinf(
            phaseScale * (f32) (u32) g_gameLoopFrameCount * ((f32) (channel + 2) * 4.0f) *
            0.01745329424738884f) * 16.0f)) + 16.0f + 48.0f;
        g_playerModelLighting[0].ambientCopy[channel] = g_playerModelLighting[0].ambient[channel] = (u32)ambient;
        diffuse = (((Gu_Sinf(
            phaseScale * (f32) (u32) g_gameLoopFrameCount * ((f32) (channel + 2) * 4.0f) *
            0.01745329424738884f) * 64.0f) + 255.0f) - 64.0f) - 1.0f;
        g_playerModelLighting[0].diffuseCopy[channel] = g_playerModelLighting[0].diffuse[channel] = (u32)diffuse;
        channel += 1;
    } while (channel < 3);
    direction.x = Gu_Sinf((f32) ((u32) g_gameLoopFrameCount * 6) * 0.01745329424738884f);
    direction.y = Gu_Sinf((f32) ((u32) g_gameLoopFrameCount * 8) * 0.01745329424738884f);
    direction.z = Math_Cosf((f32) ((u32) g_gameLoopFrameCount * 10) * 0.01745329424738884f);
    Graphu64_NormalizeVec3(&direction);
    direction.x *= 120.0f;
    direction.y *= 120.0f;
    direction.z *= 120.0f;
    g_playerModelLighting[0].direction[0] = (u32)direction.x;
    g_playerModelLighting[0].direction[1] = (u32)direction.y;
    g_playerModelLighting[0].direction[2] = (u32)direction.z;
    red = (Gu_Sinf(2.0f * (phaseScale * (f32) (u32) g_gameLoopFrameCount) * 0.06981317698955536f) * 64.0f) + 128.0f;
    redByte = (u32)red & 0xF8;
    actor->color[0] = redByte;
    actor->secondaryColor[0] = redByte;
    green = (Gu_Sinf(phaseScale * (f32) (u32) g_gameLoopFrameCount * 0.20943953096866608f) * 64.0f) + 128.0f;
    greenByte = (u32)green & 0xF8;
    actor->color[1] = greenByte;
    actor->secondaryColor[1] = greenByte;
    blue = (Gu_Sinf(phaseScale * (f32) (u32) g_gameLoopFrameCount * 0.27925270795822144f) * 64.0f) + 128.0f;
    blueByte = (u32)blue & 0xF8;
    actor->color[2] = blueByte;
    actor->secondaryColor[2] = blueByte;
}

void Camera_BlendEnvironmentColors(View *self) {
    u8 target[4];
    ColorBlendRecord *rec;
    SharedPlayer *node;
    SharedPlayer *ownerNode;
    u32 hold;
    u32 freeze;
    u32 fadeA;
    u32 fadeB;
    u32 endN;
    f32 endA;
    f32 endB;
    f32 t;
    f32 k;
    s32 i;
    u16 *key = self->key;

    if (key == 0) {
        if (&g_world == 0 || g_world.mode == 0) {
            return;
        }
        rec = (void *)(SetN64_GetPackSection(g_world.modelSections, 0) + 8);
    } else {
        rec = Scene_GetModelRecordByIndexPointer(&g_world, key);
        if (rec == 0) {
            return;
        }
    }

    hold = 0;
    fadeA = hold;
    fadeB = hold;
    freeze = hold;
    for (node = g_transientPlayerList.actorList; node != 0; node = node->views16E0.view16E0_1.next) {
        if (node->views5DC.view5DC_0.messageCamera == self) {
            ownerNode = node;
            goto found;
        }
    }
    node = 0;
    ownerNode = 0;
found:
    if (node != 0) {
        hold = 0;
        if ((ownerNode->views5E8.view664_27.timer & 0x40) ||
            (ownerNode->views1C.view38_3.flags & 0x1000)) {
            hold = 1;
        }
        freeze = node->views1C.view38_3.flags & 0x20000;
        fadeA = 0;
        if (node->views1C.view38_3.flags & 0x8000) {
            fadeA = fadeA < hold;
        }
        fadeB = 0;
        if (node->views1C.view38_3.flags & 0x10000) {
            fadeB = fadeB < hold;
        }
    }

    if (key != 0 && (*key != self->lastKey || hold != 0 || freeze != 0)) {
        if (self->lastKey == -1 || hold != 0 || freeze != 0) {
            self->blendTime = 1.0f;
        } else {
            self->blendTime = 0.0f;
        }
        self->lastKey = *key;
        for (i = 0; i < 4; i++) {
            self->secondaryColor[i] = self->color[i];
        }
        self->previousA = self->blendA;
        self->previousN = self->blendN;
        self->previousB = self->blendB;
    }

    if (hold != 0 || freeze != 0 || fadeA != 0 || fadeB != 0) {
        for (i = 0; i < 4; i++) {
            target[i] = rec->heldColor[i];
        }
        endN = rec->heldN;
        endA = rec->heldA;
        endB = rec->heldB;
    } else {
        for (i = 0; i < 3; i++) {
            target[i] = rec->color[i];
        }
        target[3] = 0;
        endN = rec->n;
        endA = rec->a;
        endB = rec->b;
    }

    if (g_gameLoopFrameCount == 0 || rec->period == 0.0f) {
        self->blendTime = 1.0f;
    } else {
        f32 progress;
        progress = self->blendTime + g_frameElapsedTime / (rec->period * 15.0f);
        if (1.0f < progress) {
            progress = 1.0f;
        }
        self->blendTime = progress;
    }

    t = self->blendTime;
    k = t * (t * -2.0f) * t + t * (t * 3.0f);

    /* Clamp the interpolated channels to [0, 255] and the scalar to [0, 995]. */
    for (i = 0; i < 4; i++) {
        self->color[i] = (u32)(
            (255.0f < ((f32)self->secondaryColor[i] +
                       k * ((f32)target[i] - (f32)self->secondaryColor[i]))
                 ? 255.0f
                 : ((f32)self->secondaryColor[i] +
                    k * ((f32)target[i] - (f32)self->secondaryColor[i]))) < 0.0f
                ? 0.0f
                : (255.0f < ((f32)self->secondaryColor[i] +
                             k * ((f32)target[i] - (f32)self->secondaryColor[i]))
                       ? 255.0f
                       : ((f32)self->secondaryColor[i] +
                          k * ((f32)target[i] - (f32)self->secondaryColor[i]))));
    }
    self->blendN = (u32)(
        (995.0f < ((f32)self->previousN + k * ((f32)endN - (f32)self->previousN))
             ? 995.0f
             : ((f32)self->previousN + k * ((f32)endN - (f32)self->previousN))) < 0.0f
            ? 0.0f
            : (995.0f < ((f32)self->previousN + k * ((f32)endN - (f32)self->previousN))
                   ? 995.0f
                   : ((f32)self->previousN + k * ((f32)endN - (f32)self->previousN))));

    if (self->blendOffset > 0.0f) {
        endA += self->blendOffset * 1024.0f;
    }
    self->blendA = self->previousA + k * (endA - self->previousA);
    self->blendB = self->previousB + k * (endB - self->previousB);
}

/* The camera position is passed as a three-word CVector3 value. */

/* Actor transform and camera-effect subobjects. */
typedef struct TransformWorld {
    s32 identifier;
    char pad4[0x11AC-4];
    CShake *effects;
} TransformWorld;

void Camera_BuildShakenViewTransform(void *cameraTransform) {
    GameplayCamera *actor=cameraTransform;
    Rotation q18,q28,q38,q48,q58;
    f32 m68[16],mA8[16],mE8[16],m128[16],m168[16],m1A8[16];
    CVector3 viewMotionOffsets,result,transformed;
    f32 zero,cosineInput;
    CShake *effect;
    f32 *baseQuaternion;
    f32 *matrix;
    f32 rollHalfAngle;
    f32 pitchHalfAngle;
    f32 sequenceAngleScale;
    f32 gameplayAngleScale;
    f32 rollHalfSine;
    f32 pitchHalfSine;
    f32 yawHalfSine;
    f32 sequenceRollHalfSine;
    f32 sequencePitchHalfSine;
    f32 sequenceYawHalfSine;
    f32 adjustedPitch;
    f32 adjustedRoll;
    void *combinedQuaternion;

    if (actor->dirty != 0) {
        adjustedPitch = actor->lensFlareInputTwo;
        adjustedRoll = actor->lensFlareInputFour;
        if (Cinema_IsSequenceInWindow() == 0) {
            Gsky_GetFloorSurfaceShake(cameraTransform, &viewMotionOffsets);
            adjustedRoll += viewMotionOffsets.z;
            gameplayAngleScale = g_cameraGameplayAngleScale;
            rollHalfAngle = adjustedRoll * gameplayAngleScale;
            adjustedPitch += viewMotionOffsets.x;
            rollHalfSine = Gu_Sinf(rollHalfAngle);
            pitchHalfAngle = adjustedPitch * gameplayAngleScale;
            g_turretAimSine = rollHalfSine;
            q38.word[0] = 0;
            q38.word[1] = 0;
            q38.f[2] = rollHalfSine;
            q38.f[3] = Math_Cosf(rollHalfAngle);
            pitchHalfSine = Gu_Sinf(pitchHalfAngle);
            g_turretAimSine = pitchHalfSine;
            q18.f[0] = pitchHalfSine;
            q18.word[1] = 0;
            q18.word[2] = 0;
            q18.f[3] = Math_Cosf(pitchHalfAngle);
            combinedQuaternion = ((f32 *)&actor->billboardQuaternion);
            yawHalfSine = Gu_Sinf((actor->lensFlareInputOne + actor->lensFlareInputThree) * gameplayAngleScale);
            q28.word[0] = 0;
            q28.f[1] = yawHalfSine;
            q28.word[2] = 0;
            cosineInput = ((actor->lensFlareInputOne + actor->lensFlareInputThree) * gameplayAngleScale);
            g_turretAimSine = yawHalfSine;
            baseQuaternion = actor->floorSampleData.f;
            q28.f[3] = Math_Cosf(cosineInput);
            MultiplyQuaternions(q48.f, q18.f, q28.f);
            MultiplyQuaternions(combinedQuaternion, q48.f, baseQuaternion);
            MultiplyQuaternions(((f32 *)&actor->orientation), q38.f, combinedQuaternion);
            MultiplyQuaternions(q58.f, q38.f, q48.f);
            MatrixFromQuaternion(q58.f, m68);
            zero=0.0f;
            Graphu64_BuildTranslationMatrix(mA8, zero, actor->floorHeightOffset, zero);
            MatrixFromQuaternion(baseQuaternion, mE8);
            result.x = zero;
            result.y = zero;
            result.z = zero;
            Camera_AccumulateDistanceScaledShake(&actor->shake, actor->shake.m_vPos, &result);
            Weapon_UpdateShakeAxis(&actor->shake.x);
            Weapon_UpdateShakeAxis(&actor->shake.y);
            Weapon_UpdateShakeAxis(&actor->shake.z);
            if (cameraTransform != &g_fallbackScreenMessageEmitter) {
                effect = ((TransformWorld*)(void*)&g_fallbackScreenMessageEmitter)->effects;
                if (effect != 0) {
                    do {
                        Camera_AccumulateDistanceScaledShake(effect, (*(CVector3 *)&actor->floorSampleX), &result);
                        effect = effect->next;
                    } while (effect != 0);
                }
            }
            Graphu64_MultiplyAffineMatrices(m168, m68, mE8);
            Graphu64_TransformPoint(m168, &result, &transformed);
            Graphu64_MultiplyAffineMatrices(m168, m68, mA8);
            matrix = m1A8;
            Graphu64_MultiplyAffineMatrices(matrix, m168, mE8);
            Graphu64_BuildTranslationMatrix(m128,
                actor->floorSampleX + transformed.x,
                actor->floorSampleY + viewMotionOffsets.y + transformed.y,
                actor->floorSampleZ + transformed.z);
            Graphu64_MultiplyAffineMatrices(actor->viewOrient, matrix, m128);
        } else {
            cosineInput = actor->lensFlareInputFour;
            sequenceAngleScale = g_cameraSequenceAngleScale;
            sequenceRollHalfSine = Gu_Sinf(cosineInput * sequenceAngleScale);
            q38.word[0] = 0;
            q38.word[1] = 0;
            q38.f[2] = sequenceRollHalfSine;
            cosineInput = (actor->lensFlareInputFour * sequenceAngleScale);
            g_turretAimSine = sequenceRollHalfSine;
            q38.f[3] = Math_Cosf(cosineInput);
            sequencePitchHalfSine = Gu_Sinf(actor->lensFlareInputTwo * sequenceAngleScale);
            q18.f[0] = sequencePitchHalfSine;
            q18.word[1] = 0;
            q18.word[2] = 0;
            cosineInput = (actor->lensFlareInputTwo * sequenceAngleScale);
            g_turretAimSine = sequencePitchHalfSine;
            q18.f[3] = Math_Cosf(cosineInput);
            sequenceYawHalfSine = Gu_Sinf((actor->lensFlareInputOne + actor->lensFlareInputThree) * sequenceAngleScale);
            q28.word[0] = 0;
            q28.f[1] = sequenceYawHalfSine;
            q28.word[2] = 0;
            cosineInput = ((actor->lensFlareInputOne + actor->lensFlareInputThree) * sequenceAngleScale);
            g_turretAimSine = sequenceYawHalfSine;
            q28.f[3] = Math_Cosf(cosineInput);
            MultiplyQuaternions(q48.f, q18.f, q28.f);
            *(Rotation *)&actor->billboardQuaternion=q48;
            MultiplyQuaternions(((f32 *)&actor->orientation), q38.f, ((f32 *)&actor->billboardQuaternion));
            MatrixFromQuaternion(q48.f, m68);
            Graphu64_BuildTranslationMatrix(m128,actor->floorSampleX,actor->floorSampleY,actor->floorSampleZ);
            Graphu64_MultiplyAffineMatrices(actor->viewOrient, m68, m128);
        }

        actor->cachedPitch = adjustedPitch;
        actor->cachedRoll = adjustedRoll;
        actor->cachedYaw = (f32) actor->lensFlareInputOne;
    }
}

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

/* Rebuilds a camera's view volume when it is active: the eye and the four far corners at depth farPlane come
 * either from verticalFieldOfView and aspect (a perspective camera, radius the slant distance to the far
 * plane) or, while the global orthographic flag is set, from farHalfWidth and farHalfHeight (radius the
 * corner distance); the corners are transformed by viewOrient into corners, clipPlanes and clipBounds are
 * rebuilt from them, and a box around the eye of that radius (half again as tall) is stored in
 * volumeBounds. */
void Camera_UpdateFrustumBounds(GameplayCamera *camera) {
    CVector3 pts[5];
    CVector3 *out;
    f32 radius;
    f32 height;

    if (camera->dirty == 0) {
        return;
    }
    if (g_gameSettings.local == 0) {
        radius = camera->farPlane /
                 Math_Cosf(camera->verticalFieldOfView * camera->aspect * g_cameraFrustumAngleConstants[0]);
        pts[0].x = 0.0f;
        pts[0].y = 0.0f;
        pts[0].z = 0.0f;
        pts[1].x = radius * Gu_Sinf(camera->verticalFieldOfView * camera->aspect * g_cameraFrustumAngleConstants[0]);
        pts[1].y = pts[1].x / camera->aspect;
        pts[1].z = -camera->farPlane;
        pts[2].x = -pts[1].x;
        pts[2].y = pts[1].y;
        pts[2].z = pts[1].z;
        pts[3].x = pts[1].x;
        pts[3].y = -pts[1].y;
        pts[3].z = pts[1].z;
        pts[4].x = -pts[1].x;
        pts[4].y = -pts[1].y;
        pts[4].z = pts[1].z;
    } else {
        pts[0].x = 0.0f;
        pts[0].y = 0.0f;
        pts[0].z = 0.0f;
        pts[1].x = camera->farHalfWidth * g_cameraFrustumAngleConstants[1];
        pts[1].y = camera->farHalfHeight * g_cameraFrustumAngleConstants[1];
        pts[1].z = -camera->farPlane;
        pts[2].x = -pts[1].x;
        pts[2].y = pts[1].y;
        pts[2].z = pts[1].z;
        pts[3].x = pts[1].x;
        pts[3].y = -pts[1].y;
        pts[3].z = pts[1].z;
        pts[4].x = -pts[1].x;
        pts[4].y = -pts[1].y;
        pts[4].z = pts[1].z;
        radius = Gu_Sqrtf(pts[1].x * pts[1].x + pts[1].y * pts[1].y + pts[1].z * pts[1].z);
    }
    out = &camera->corners[0];
    Graphu64_TransformPoints(camera->viewOrient, pts, out, 5);
    Visdata_BuildFrustumPlanes(camera->clipPlanes, out, out + 1, out + 2, out + 3, out + 4);
    Region_ComputePointBounds(camera->clipBounds, 5, out);
    height = radius * g_cameraFrustumHeightScale;
    camera->volumeBounds[0].x = camera->corners[0].x - radius;
    camera->volumeBounds[1].x = camera->corners[0].x + radius;
    camera->volumeBounds[0].y = camera->corners[0].y - height;
    camera->volumeBounds[1].y = camera->corners[0].y + height;
    camera->volumeBounds[0].z = camera->corners[0].z - radius;
    camera->volumeBounds[1].z = camera->corners[0].z + radius;
}

#if !(defined(VERSION_US_REV1))
const float k_cinemaSequenceWindowConstants[3] = {
    0.008726647f, 0.5f, 1.5f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_cinemaSequenceWindowConstants[3] = {
    0.008726647f, 0.5f, 1.5f,
};
#endif

struct CShakeAxis_t;

int Cinema_IsSequenceInWindow(void);
f32 Cinema_GetSequenceResponse();

void Graphu64_MultiplyMatrices(f32 *, f32 *, f32 *);






void MatrixFromQuaternion(f32 *, f32 *);

int Tsmos_IsFrontendActive(void);
int Tsmos_GetMenuModelFlag(void);

f32 Gu_Sqrtf(f32);
void Menu_UpdateDialogList(struct MessageList *list);
void Sky_UpdateSceneEffects(void *scene, void *host);

typedef struct SharedCameraOwnerView CameraOwnerView;
typedef struct CameraRuntimeMode CameraRuntimeModeView;
typedef struct Lights CameraFrameLights;
typedef struct CameraFloorSurfaceView CameraFloorPolygonView;

/* Updates the actor view and projection matrices and applies camera effects. */
void Camera_UpdateViewProjectionAndEffects(GameplayCamera *camera) {
    f32 ground_x;
    CameraFloorPolygonView *floorPolygon;
    f32 referenceViewMatrix[16];
    f32 composedViewMatrix[16];
    f32 halfTurnMatrix[16];
    f32 inverseRotatedView[16];
    f32 worldToViewMatrix[16];
    f32 right[16];
    f32 horizontalFlipMatrix[16];
    f32 matrix[16];
    f32 hudProjectionMatrix[16];
    s32 (*modeCallback)(s8 *);
    f32 farPlaneDistance;
    f32 projectionOrFloorScale;
    f32 baseHorizontalSlope;
    f32 div_stage;
    f32 horizontalSlope;
    f32 floorSampleZ;
    f32 fovSine;
    f32 verticalSlope;
    f32 fovy;
    f32 floorHeightOffset;
    f32 aspect;
    f32 initial_zoom;
    f32 floorSampleY;
    f32 zoomBlend;
    f32 kickStepDelta;
    f32 bobBlendLimit;
    f32 lightZeroDirectionX;
    f32 lightZeroDirectionY;
    f32 lightZeroDirectionZ;
    f32 lightOneDirectionX;
    f32 lightOneDirectionY;
    f32 lightOneDirectionZ;
    f32 horizontalStretch;
    f32 bobRateBlend;
    f32 verticalStretch;
    s32 sequenceFarPlane;
    s32 fovOverrideState;
    s32 captured_state;
    s32 kickStepOperand;
    s8 *viewProjectionMatrix;
    s8 *viewOrientationMatrix;
    u16 previousKickStep;
    u16 advancedKickStep;
    u16 clampedKickStep;

    CameraFrameLights *frameLights;
    CameraOwnerView *cameraOwner;
    CameraOwnerView *actorCursor;
    CameraRuntimeModeView *state;

    for (actorCursor = g_transientPlayerList.actorList; actorCursor != 0; actorCursor = actorCursor->nextActor) {
        if (actorCursor->camera == camera) {
            cameraOwner = actorCursor;
            goto owner_found;
        }
    }
    cameraOwner = 0;
owner_found:
    camera->elapsed = (f32) (camera->elapsed + g_frameElapsedTime);
    Camera_BlendEnvironmentColors((View *) camera);
    camera->dirty = 1;
    if (Cinema_IsSequenceInWindow() == 0) {
        modeCallback = g_cameraModeCallbacks[camera->mode].fn;
        if (modeCallback != 0) {
            modeCallback(camera);
        }
    }
    frameLights = &camera->lights[g_lightingBufferIndex];
    guLookAtF(referenceViewMatrix, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    if ((Cinema_IsSequenceInWindow() != 0) && (camera != &g_fallbackScreenMessageEmitter)) {
        Cinema_UpdateSequenceTrack(camera);
    }
    zoomBlend = camera->zoomBlend;
    initial_zoom = camera->zoomFov;
    Camera_BuildShakenViewTransform(camera);
    if (Cinema_IsSequenceInWindow() == 0) {
        Weapon_UpdateShakeAxis(&camera->shake.x);
        Weapon_UpdateShakeAxis(&camera->shake.y);
        Weapon_UpdateShakeAxis(&camera->shake.z);
    }
    viewOrientationMatrix = (s8 *)camera->viewOrient;
    Graphu64_GetMatrixTranslation(viewOrientationMatrix, &camera->position.x);
    Graphu64_InvertAffineMatrix(camera->inverseViewOrient, (f32 *) viewOrientationMatrix);
    BuildYawMatrix(halfTurnMatrix, 3.1415927f);
    Graphu64_MultiplyAffineMatrices(composedViewMatrix, halfTurnMatrix, (f32 *) viewOrientationMatrix);
    Graphu64_InvertAffineMatrix(inverseRotatedView, composedViewMatrix);
    Graphu64_MultiplyAffineMatrices(worldToViewMatrix, inverseRotatedView, referenceViewMatrix);
    CopyMatrix(camera->worldToView, worldToViewMatrix);
    if ((cameraOwner != 0) && (cameraOwner->movementFlags & 0x40) && (camera->bobSuppressed == 0) && (Cinema_IsSequenceInWindow() == 0)) {
        f32 inverseBobRateBlend;
        horizontalStretch = (((camera->bobAmplitudeX * 0.5f * (Gu_Sinf(camera->bobPhaseX) + 1.0f)) + 0.8f) > 1.0f) ? 1.0f : ((camera->bobAmplitudeX * 0.5f * (Gu_Sinf(camera->bobPhaseX) + 1.0f)) + 0.8f);
        camera->stretchX = horizontalStretch;
        verticalStretch = (((camera->bobAmplitudeY * 0.5f * (Gu_Sinf(camera->bobPhaseY) + 1.0f)) + 0.9f) > 1.0f) ? 1.0f : ((camera->bobAmplitudeY * 0.5f * (Gu_Sinf(camera->bobPhaseY) + 1.0f)) + 0.9f);
        camera->stretchY = verticalStretch;
        camera->bobPhaseX = (f32) (camera->bobPhaseX + (g_frameElapsedTime * camera->bobRateX));
        camera->bobPhaseY = (f32) (camera->bobPhaseY + (g_frameElapsedTime * camera->bobRateY));
        bobRateBlend = cameraOwner->bobSpeed * 2.5f;
        bobBlendLimit = 0.0f;
        if ((bobRateBlend < 0.0f) || (bobBlendLimit = 1.0f, (bobRateBlend > 1.0f))) {
            bobRateBlend = bobBlendLimit;
        }
        Graphu64_EaseValueToward(&camera->bobAmplitudeX, 0.1f, 0.5f);
        Graphu64_EaseValueToward(&camera->bobAmplitudeY, 0.05f, 0.5f);
        inverseBobRateBlend = 1.0f - bobRateBlend;
        Graphu64_EaseValueToward(&camera->bobRateX, (bobRateBlend * 0.104719765f) + (inverseBobRateBlend * 0.06981318f), 0.16666667f);
        Graphu64_EaseValueToward(&camera->bobRateY, (bobRateBlend * 0.087266475f) + (inverseBobRateBlend * 0.03490659f), 0.16666667f);
    } else {
        camera->stretchY = 1.0f;
        camera->stretchX = 1.0f;
    }
    previousKickStep = camera->kickStep;
    kickStepOperand = 50;
    if (previousKickStep != kickStepOperand) {
        camera->stretchY = (f32) (((f32) (kickStepOperand - previousKickStep) * 0.08f) + 1.0f);
        kickStepDelta = g_frameElapsedTime * 10.0f;
        if (!(kickStepDelta >= 2.1474836e9f)) {
            kickStepOperand = (s32) kickStepDelta;
        } else {
            kickStepOperand = (s32) (kickStepDelta - 2.1474836e9f) | 0x80000000;
        }
        advancedKickStep = camera->kickStep + kickStepOperand;
        clampedKickStep = advancedKickStep;
        camera->kickStep = advancedKickStep;
        if ((u32) (clampedKickStep & 0xFFFF) >= 51U) {
            clampedKickStep = 50;
        }
        camera->kickStep = clampedKickStep;
    }
    if (Cinema_IsSequenceInWindow() != 0) {
        fovy = Cinema_GetSequenceResponse(camera);
    } else {
        fovOverrideState = Tsmos_IsFrontendActive();
        if ((fovOverrideState == 1) && (Tsmos_GetMenuModelFlag() == fovOverrideState)) {
            fovy = 45.0f;
        } else if (zoomBlend != 0.0f) {
            fovy = (zoomBlend * (initial_zoom - 75.0f)) + 75.0f;
        } else {
            fovy = 75.0f;
        }
    }
    if ((Cinema_IsSequenceInWindow() != 0) && (camera != &g_fallbackScreenMessageEmitter)) {
        aspect = camera->viewWidth / camera->viewHeight;
    } else if (((SharedCameraRenderView *)&g_playerWeaponClassMode)->renderMode == 2) {
        aspect = 0.6666667f;
        if (((SharedCameraRenderView *)&g_playerWeaponClassMode)->sequenceViewReady == 0) {
            aspect = 2.666666f;
        }
    } else {
        aspect = 1.333333f;
    }
    fovy = fovy * 0.017453294f;
    fovSine = Gu_Sinf(fovy);
    verticalSlope = fovSine / Math_Cosf(fovy);
    baseHorizontalSlope = verticalSlope * 1.2792794f;
    verticalSlope = baseHorizontalSlope / aspect;
    verticalSlope = verticalSlope / camera->stretchY;
    horizontalSlope = baseHorizontalSlope / camera->stretchX;
    projectionOrFloorScale = 1.0f;
    fovy = Graphu64_ArcCos(Gu_Sqrtf(projectionOrFloorScale / ((verticalSlope * verticalSlope) + 1.0f)));
    fovy = fovy * 57.295776f;
    farPlaneDistance = camera->farPlane;
    aspect = horizontalSlope / verticalSlope;
    camera->aspect = aspect;
    camera->fovY = fovy;
    camera->farHalfWidth = (f32) (farPlaneDistance * horizontalSlope);
    camera->farHalfHeight = (f32) (farPlaneDistance * verticalSlope);
    if (Cinema_IsSequenceInWindow() != 0) {
        sequenceFarPlane = (s32) Cinema_GetScaledSequenceValue();
        if (sequenceFarPlane > 0) {
            camera->farPlane = (f32) sequenceFarPlane;
        }
    }
    guPerspectiveF(right, &camera->perspNorm, fovy, aspect, 16.0f, camera->farPlane, 1.0f - (zoomBlend * 0.95f));
    Graphu64_BuildScaleMatrix(horizontalFlipMatrix, -1.0f, 1.0f, 1.0f);
    Graphu64_MultiplyMatrices(composedViewMatrix, worldToViewMatrix, (f32 *) right);
    viewProjectionMatrix = (s8 *)camera->viewProjection;
    Graphu64_MultiplyMatrices((f32 *) viewProjectionMatrix, composedViewMatrix, horizontalFlipMatrix);
    Graphu64_ClampMatrixToFixedRange((f32 *) viewProjectionMatrix);
    GraphU64_PackFixedMatrix((f32 *) viewProjectionMatrix, camera->projection[g_lightingBufferIndex]);
    CopyMatrix(matrix, worldToViewMatrix);
    state = &((SharedCameraRenderView *)&g_playerWeaponClassMode)->state;
    if (state->mode == 4) {
        PitchMatrix(matrix, camera->elapsed * 0.010908309f);
        YawMatrix(matrix, camera->elapsed * 0.008726647f);
    }
    Graphu64_ClampMatrixToFixedRange(matrix);
    lightZeroDirectionX = matrix[0] * 128.0f;
    if (!(lightZeroDirectionX <= 127.0f)) {
        lightZeroDirectionX = 127.0f;
    }
    frameLights->light0DirX = (s8) (s32) lightZeroDirectionX;
    lightZeroDirectionY = matrix[4] * 128.0f;
    if (!(lightZeroDirectionY <= 127.0f)) {
        lightZeroDirectionY = 127.0f;
    }
    frameLights->light0DirY = (s8) (s32) lightZeroDirectionY;
    lightZeroDirectionZ = matrix[8] * 128.0f;
    if (!(lightZeroDirectionZ <= 127.0f)) {
        lightZeroDirectionZ = 127.0f;
    }
    frameLights->light0DirZ = (s8) (s32) lightZeroDirectionZ;
    lightOneDirectionX = matrix[1] * 128.0f;
    if (!(lightOneDirectionX <= 127.0f)) {
        lightOneDirectionX = 127.0f;
    }
    frameLights->light1DirX = (s8) (s32) lightOneDirectionX;
    lightOneDirectionY = matrix[5] * 128.0f;
    if (!(lightOneDirectionY <= 127.0f)) {
        lightOneDirectionY = 127.0f;
    }
    frameLights->light1DirY = (s8) (s32) lightOneDirectionY;
    lightOneDirectionZ = matrix[9] * 128.0f;
    if (!(lightOneDirectionZ <= 127.0f)) {
        lightOneDirectionZ = 127.0f;
    }
    frameLights->light1DirZ = (s8) (s32) lightOneDirectionZ;
    frameLights->light0R = 0;
    frameLights->light0G = 0;
    frameLights->light0B = 0;
    frameLights->light0PadA = 0;
    frameLights->light0CopyR = 0;
    frameLights->light0CopyG = 0;
    frameLights->light0CopyB = 0;
    frameLights->light0PadB = 0;
    frameLights->light1R = 0;
    frameLights->light1G = 128;
    frameLights->light1B = 0;
    frameLights->light1PadA = 0;
    frameLights->light1CopyR = 0;
    frameLights->light1CopyG = 128;
    frameLights->light1CopyB = 0;
    frameLights->light1PadB = 0;
    Camera_UpdateFrustumBounds(camera);
    MatrixFromQuaternion(&camera->billboardQuaternion, camera->faceScreen);
    BuildYawMatrix(camera->faceScreenUpright, camera->cachedYaw);
    if (((SharedCameraRenderView *)&g_playerWeaponClassMode)->alternateViewEnabled != 0) {
        guPerspectiveF(right, &camera->hudPerspNorm, 47.5f, (f32) ((s32) g_hudReferenceViewportWidth / g_hudReferenceViewportHeight), 16.0f, 7168.0f, 1.0f);
        Graphu64_IdentityMatrix(worldToViewMatrix);
        Graphu64_MultiplyMatrices(composedViewMatrix, worldToViewMatrix, (f32 *) right);
        Graphu64_BuildScaleMatrix(horizontalFlipMatrix, -1.0f, 1.0f, 1.0f);
        Graphu64_MultiplyMatrices(hudProjectionMatrix, composedViewMatrix, horizontalFlipMatrix);
        Graphu64_ClampMatrixToFixedRange(hudProjectionMatrix);
        GraphU64_PackFixedMatrix(hudProjectionMatrix, camera->hudProjection[g_lightingBufferIndex]);
    }
    Sky_UpdateSceneEffects(&camera->sceneEffects, camera);
    Menu_UpdateDialogList(&camera->messageList);
    if (Cinema_IsSequenceInWindow() != 0) {
        camera->floorPoly = ((void *(*)())Scene_FindFloorPolygon)(&g_world, &camera->floorSampleX);
    }
    captured_state = g_defaultCameraSurfaceType;
    camera->floorSurface = captured_state;
    floorPolygon = camera->floorPoly;
    ground_x = camera->floorSampleX;
    floorSampleY = camera->floorSampleY;
    floorSampleZ = camera->floorSampleZ;
    floorHeightOffset = camera->floorHeightOffset;
    if ((floorPolygon != 0) && (Cinema_IsSequenceInWindow() == 0)) {
        projectionOrFloorScale = ((floorSampleY + floorHeightOffset) - Region_GetPolygonHeight(floorPolygon, ground_x, floorSampleZ)) * 0.09765625f;
        if ((projectionOrFloorScale < 11.0f) && (projectionOrFloorScale > 5.0f)) {
            camera->floorSurface = (s32) floorPolygon->surfaceType;
        }
    }
    if (Cinema_IsSequenceInWindow() != 0) {
        camera->floorSurface = (s32) g_defaultCameraSurfaceType;
    }
    if (camera->zoomBlend > 0.0f) {
        camera->floorSurface = (s32) g_defaultCameraSurfaceType;
    }
}


/* Splits a 0x00BBGGRR fade color into its three fog/fill channels. */
static inline void Camera_UnpackColor(u32 color, u8 *red, u8 *green, u8 *blue) {
    *blue = color >> 16;
    *green = color >> 8;
    *red = color;
}

/* Set projection, viewport and look-at, then draw the view's clear rectangle and fog. */
void Camera_SetupViewportAndFog(GameplayCamera *view) {
    u8 red, green, blue;
    s16 uly, ulx, lrx, lry;
    s32 flag;
    u32 color;
    s16 vx, vy;
    s16 maxx, maxy;
    f32 width, height, x, y;
    Frame *buffer;
    s32 frame;
    Gfx **gfx = &g_displayListCursor;

    gDPPipeSync((*gfx)++);
    gSPDisplayList((*gfx)++, ((g_cameraViewDisplayListPrimary)));
    gSPDisplayList((*gfx)++, ((g_cameraViewDisplayListSecondary)));
    view->pixelXScale = 1.0f;
    view->pixelYScale = 1.0f;
    view->pixelXScale = view->fadeScalarOne;
    view->pixelYScale = view->fadeScalarTwo;
    x = view->viewLeft;
    y = view->viewTop;
    width = view->viewWidth;
    maxx = SCREEN_WD - 1;
    height = view->viewHeight;
    ulx = x;
    maxy = SCREEN_HT - 1;
    vx = (width + width) * view->pixelXScale;
    vy = (height + height) * view->pixelYScale;
    uly = y;
    lrx = x + width;
    lry = y + height;
    if (lrx > SCREEN_WD - 1) {
        lrx = maxx;
    }
    if (ulx < 0) {
        ulx = 0;
    }
    if (uly < 0) {
        uly = 0;
    }
    if (lry > SCREEN_HT - 1) {
        lry = maxy;
    }
    buffer = g_gameSession.ring.current;
    frame = g_lightingBufferIndex;
    gSPMatrix((*gfx)++, view->projection[frame], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPPerspNormalize((*gfx)++, view->perspNorm);
    view->viewports[frame].vscale[0] = vx;
    view->viewports[frame].vscale[1] = vy;
    view->viewports[frame].vtrans[0] = (vx * 0.25f + view->viewLeft) * 4.0f;
    view->viewports[frame].vtrans[1] = (vy * 0.25f + view->viewTop) * 4.0f;
    gSPViewport((*gfx)++, &view->viewports[frame]);
    gDPSetScissor((*gfx)++, G_SC_NON_INTERLACE, ulx, uly, lrx, lry);
    gSPLookAtX((*gfx)++, &view->lights[frame].light0R);
    gSPLookAtY((*gfx)++, &view->lights[frame].light1R);
    Geometry_SetViewEffect(view->monochrome);
    if (view != &((SharedCameraRenderView *)&g_playerWeaponClassMode)->view) {
        Textload_SetTextureEffect(view->monochrome);
    }
    Geometry_SelectEffectModes();
    TextLoad_ResetTextureCache();
    gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
    flag = 0;
    if (Tsmos_IsFrontendActive() != 0) {
        flag = GetMenuScreenOwner() != 2;
    }
    if (view != &((SharedCameraRenderView *)&g_playerWeaponClassMode)->view || ((SharedCameraRenderView *)&g_playerWeaponClassMode)->renderMode == 0 || flag != 0) {
        Geometry_SetModePreset(20);
        gDPPipeSync(g_displayListCursor++);
        SetN64_ClearDepthRect(&g_gameSession, ulx, lrx, uly, lry, view->monochrome);
        gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
        if (g_gameSettings.flags & 0x4000) {
            red = 0;
            green = 0;
            blue = 0;
        } else {
            red = view->clearRed & 0xF8;
            green = view->clearGreen & 0xF8;
            blue = view->clearBlue & 0xF8;
        }
        if (Cinema_IsSequenceInWindow() != 0) {
            color = Cinema_GetSequenceProperty();
            if (color != 0xFF00) {
                Camera_UnpackColor(color, &red, &green, &blue);
            }
        }
        gSPGeometryMode(g_displayListCursor++, 0, G_FOG);
        if (view->monochrome != 0) {
            gDPSetFogColor(g_displayListCursor++, 0, 0, 0, 255);
            gSPFogPosition(g_displayListCursor++, 995, 1000);
        } else {
            gDPSetFogColor(g_displayListCursor++, red, green, blue, 255);
            gSPFogPosition(g_displayListCursor++, (u16)view->fogNear, 1000);
        }
        gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, buffer->colorImage);
        if (view->monochrome != 0) {
            gDPSetFillColor(g_displayListCursor++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));
        } else {
            gDPSetFillColor(g_displayListCursor++, (GPACK_RGBA5551(red, green, blue, 1) << 16) |
                                              GPACK_RGBA5551(red, green, blue, 1));
        }
        if (view != &((SharedCameraRenderView *)&g_playerWeaponClassMode)->view || ((SharedCameraRenderView *)&g_playerWeaponClassMode)->state.mode == 3) {
            gDPFillRectangle(g_displayListCursor++, ulx, uly, lrx, lry);
        }
    }
    gDPPipeSync(g_displayListCursor++);
    Geometry_SetColorDither(0);
    gDPSetAlphaDither(g_displayListCursor++, G_AD_NOTPATTERN);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    if (view != &((SharedCameraRenderView *)&g_playerWeaponClassMode)->view) {
        Defs_SetupPointLights(view);
    }
    gDPPipeSync(g_displayListCursor++);
}

/* Draws one view of the game world: after the per-frame setup (SetN64_OnWorldViewDraw) it runs the world, player,
 * effect, particle, object and translucent passes for the view in order, skipping the player and effect
 * passes in the alternate HUD mode (Cinema_IsSequenceInWindow) and running the extra passes only when SetN64_IsModeThirteen
 * allows; when the depth-clear debug flag is set it then clears the view's rectangle (viewWidth, viewHeight, viewLeft, viewTop) to the far
 * depth with a fill-rectangle command. */
void Camera_DrawWorldViewLayers(char *view, char *world) {
    f32 right;

    SetN64_OnWorldViewDraw();
    Scene_DrawVisibleInstances(world, view);
    if (Cinema_IsSequenceInWindow() == 0) {
        Playerai_UpdateViewModelBounds(&g_playerViewRenderContext, view);
    }
    if (SetN64_IsModeThirteen() != 0) {
        Playerai_DrawPlayersForView(&g_playerViewRenderContext, view);
    }
    Scene_DrawOpaqueActors(world, view);
    Fx_DrawBoundedParticleQuads(&g_gameSession.hud.actors, view);
    if (Cinema_IsSequenceInWindow() == 0) {
        SetN64_DrawVisibleEffects(&((Shared_World *)world)->effectSlots, view);
    }
    Scene_DrawTransparentObjects(world, view);
    Playerai_DrawPlayerModelsForView(&g_playerViewRenderContext, view);
    Sky_DrawDepthSortedSceneEffects((char *)&((GameplayCamera *)view)->sceneEffects, view);
    Scene_DrawWorldParticles(world, view);
    Fx_DrawLinkedGeometry(&g_gameSession.hud.actors, view);
    Gsky_DrawObjectFlares(view);
    if (Cinema_IsSequenceInWindow() == 0 && SetN64_IsModeThirteen() != 0) {
        Playerai_DrawViewPlayer(&g_playerViewRenderContext, view);
    }
    if (g_gameSettings.flags & 0x200) {
        gDPPipeSync(g_displayListCursor++);
        gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
        gDPSetBlendColor(g_displayListCursor++, 255, 255, 255, 255);
        gDPSetPrimDepth(g_displayListCursor++, 65535, 65535);
        gDPSetDepthSource(g_displayListCursor++, G_ZS_PRIM);
        Geometry_SetModePreset(22);
        {
            Gfx *_g;

            right = ((GameplayCamera *)(view))->viewLeft + ((GameplayCamera *)(view))->viewWidth;
            gDPFillRectangle((Gfx *)(g_displayListCursor++), ((GameplayCamera *)(view))->viewLeft, ((GameplayCamera *)(view))->viewTop, right, ((GameplayCamera *)(view))->viewTop + ((GameplayCamera *)(view))->viewHeight);
        }
    }
}





#if !(defined(VERSION_US_REV1))
const float k_cameraApproachValueUnit[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_cameraApproachValueUnit[1] = {
    1.0f,
};
#endif

/* Eases a camera's four framing values (viewWidth, viewHeight, viewLeft, viewTop) toward their targets by 16 each
 * frame, snapping to the targets when Control_IsSnapshotActive_Camera reports a cut and recording the easing rate 30 in
 * g_cameraFramingTransitionTimer whenever a value moves.
 */
static inline f32 Camera_ApproachValue(f32 value, f32 target, f32 step) {
    if (Control_IsSnapshotActive() != 0) {
        value = target;
    }
    if (value < target) {
        value += step;
        g_cameraFramingTransitionTimer = 30.0f;
        if (target < value) {
            value = target;
        }
    } else if (target < value) {
        value -= step;
        g_cameraFramingTransitionTimer = 30.0f;
        if (value < target) {
            value = target;
        }
    }
    return value;
}

void Camera_EaseViewportRectangle(GameplayCamera *camera, f32 a, f32 b, f32 c, f32 d) {
    GameplayCamera *record = camera;
    record->viewWidth = Camera_ApproachValue(record->viewWidth, a, 16.0f);
    record->viewHeight = Camera_ApproachValue(record->viewHeight, b, 16.0f);
    record->viewLeft = Camera_ApproachValue(record->viewLeft, c, 16.0f);
    record->viewTop = Camera_ApproachValue(record->viewTop, d, 16.0f);
}

/* Update split-screen rectangles, advance transient effects, and merge visible bounds. */
void Camera_UpdateViewportLayoutAndBounds(ScreenMessageOwner *state) {
    f32 halfWidth;
    f32 halfHeight;
    f32 width;
    f32 height;
    f32 top;
    f32 left;
    f32 splitY;
    f32 volumeMinZ;
    f32 volumeMaxX;
    f32 volumeMaxY;
    f32 volumeMaxZ;
    f32 clipMinX;
    f32 clipMinY;
    f32 clipMinZ;
    f32 clipMaxX;
    f32 clipMaxY;
    f32 clipMaxZ;
    f32 volumeMinX;
    f32 volumeMinY;
    f32 right;
    f32 splitX;
    f32 bottom;
    CShake *nextEffect;
    s32 timer;
    CShake *effect;
    s32 finished;
    u32 xDone;
    u32 yDone;
    u32 zDone;
    u32 mode;
    ViewFlags *flags;
    Shared_Game *settings;
    CGameStatus *layout;
    GameplayCamera *view;
    Box *clip, *bounds;
    ViewFlags initialFlags;

    right = (f32) g_hudReferenceViewportWidth;
    top = 0.0f;
    bottom = (f32) g_hudReferenceViewportHeight;
    left = 0.0f;
    if ((u32) state->header.views.count >= 2U) {
        top = g_cameraViewportTopInset;
        bottom -= g_cameraViewportBottomInset;
        left = g_cameraViewportLeftInset;
        right -= g_cameraViewportRightInset;
    }
    width = right - left;
    halfWidth = width * g_cameraViewportHalfScale;
    height = bottom - top;
    halfHeight = height * g_cameraViewportHalfScale;
    effect = g_cameraShakeEffectList;
    view = &state->self;
    if (effect != 0) {
        do {
            nextEffect = effect->next;
            xDone = Weapon_UpdateShakeAxis(&effect->x);
            yDone = Weapon_UpdateShakeAxis(&effect->y);
            zDone = Weapon_UpdateShakeAxis(&effect->z);
            finished = 0;
            if ((xDone != 0) && (yDone != 0)) {
                finished = zDone > 0U;
            }
            if (finished != 0) {
                List_RemoveIntrusive(&state->activeEffects, effect);
                List_PrependIntrusive(&state->freeEffects, effect);
            }
            effect = nextEffect;
            view = &state->self;
        } while (effect != 0);
    }
    view->viewWidth = (f32) g_hudReferenceViewportWidth;
    view->viewHeight = (f32) g_hudReferenceViewportHeight;
    view->viewLeft = 0;
    view->viewTop = 0;
    if ((Cinema_IsSequenceInWindow() == 0) && (Cinema_IsSequenceActive() == 0)) {
        mode = (u32) state->header.views.count;
        view = state->header.views.head;
        switch (mode) {
        case 1:
            view->viewWidth = width;
            view->viewHeight = height;
            view->viewLeft = 0;
            view->viewTop = 0;
            break;
        case 2:
            if (g_gameSettings.twoPlayerScreenPreference == 0) {
                view->viewWidth = width;
                view->viewHeight = halfHeight;
                view->viewLeft = left;
                view->viewTop = top;
                view = view->next;
                view->viewWidth = width;
                view->viewHeight = halfHeight;
                view->viewLeft = left;
                view->viewTop = top + halfHeight;
                break;
            } else {
                view->viewWidth = halfWidth;
                view->viewHeight = height;
                view->viewLeft = left;
                view->viewTop = top;
                view = view->next;
                view->viewWidth = halfWidth;
                view->viewHeight = height;
                    view->viewTop = top;
                view->viewLeft = (f32) (left + halfWidth);
            }
            break;
        case 3:
            layout = &g_gameSettings.counters;
            if (layout->transitionActive == 0) {
            settings = &g_gameSettings;
            if (settings->slots[0].enabled == 1) {
                view->viewWidth = halfWidth;
                view->viewHeight = halfHeight;
                view->viewLeft = left;
                view->viewTop = top;
                view = view->next;
            }
            if (settings->slots[1].enabled == 1) {
                view->viewWidth = halfWidth;
                view->viewHeight = halfHeight;
                    view->viewTop = top;
                view->viewLeft = (f32) (left + halfWidth);
                view = view->next;
            }
            if (settings->slots[2].enabled == 1) {
                view->viewWidth = halfWidth;
                view->viewHeight = halfHeight;
                view->viewLeft = left;
                view->viewTop = (f32) (top + halfHeight);
                view = view->next;
            }
            if (settings->slots[3].enabled == 1) {
                splitX = left + halfWidth;
                splitY = top + halfHeight;
                view->viewWidth = halfWidth;
                view->viewHeight = halfHeight;
                view->viewLeft = splitX;
                view->viewTop = splitY;
                break;
            }

            } else {
                view->viewWidth = halfWidth;
                view->viewHeight = halfHeight;
                view->viewLeft = left;
                view->viewTop = top;
                view = view->next;
                view->viewWidth = halfWidth;
                view->viewHeight = halfHeight;
                    view->viewTop = top;
                view->viewLeft = (f32) (left + halfWidth);
                view = view->next;
                splitY = top + halfHeight;
                view->viewWidth = halfWidth;
                view->viewHeight = halfHeight;
                view->viewLeft = left;
                view->viewTop = splitY;
                break;
            }
            break;
        case 4:
            view->viewWidth = halfWidth;
            view->viewHeight = halfHeight;
            view->viewLeft = left;
                view->viewTop = top;
            view = view->next;
            splitX = left + halfWidth;
            view->viewWidth = halfWidth;
            view->viewHeight = halfHeight;
                view->viewTop = top;
            view->viewLeft = splitX;
            view = view->next;
            splitY = top + halfHeight;
            view->viewWidth = halfWidth;
            view->viewHeight = halfHeight;
            view->viewLeft = left;
            view->viewTop = splitY;
            view = view->next;
            view->viewWidth = halfWidth;
            view->viewHeight = halfHeight;
            view->viewLeft = splitX;
            view->viewTop = splitY;
            break;

        }
    }
    memcpy(&g_cameraClipBounds, state->self.clipBounds, sizeof(g_cameraClipBounds));
    memcpy(&g_cameraVolumeBounds, state->self.volumeBounds, sizeof(g_cameraVolumeBounds));
    g_cameraRenderFlagState.flags = g_defaultCameraSurfaceType;
    Camera_UpdateViewProjectionAndEffects(&state->self);
    view = state->header.views.head;
    if (view != 0) {
        if ((g_frontendScreenStatus.status[7] != 0) || (Cinema_GetPlaybackPauseState() != 0)) {
            Camera_UpdateViewProjectionAndEffects(view);
        }
        if ((Cinema_IsSequenceInWindow() != 0) || (Cinema_IsSequenceActive() != 0)) {
            Camera_UpdateViewProjectionAndEffects(view);
        }
        memcpy(&g_cameraClipBounds, view->clipBounds, sizeof(g_cameraClipBounds));
        memcpy(&g_cameraVolumeBounds, view->volumeBounds, sizeof(g_cameraVolumeBounds));
        initialFlags.flags = view->floorSurface;
        g_cameraRenderFlagState = initialFlags;
        view = view->next;
        if (view != 0) {
            clip = &g_cameraClipBounds;
            bounds = &g_cameraVolumeBounds;
            flags = &g_cameraRenderFlagState;
            do {
                if ((g_frontendScreenStatus.status[7] != 0) || (Cinema_GetPlaybackPauseState() != 0)) {
                    Camera_UpdateViewProjectionAndEffects(view);
                }
                clipMinX = view->clipBounds[0].x;
                if (!(clipMinX <= clip->min.x)) {
                    clipMinX = clip->min.x;
                }
                clip->min.x = clipMinX;
                clipMinY = view->clipBounds[0].y;
                if (!(clipMinY <= clip->min.y)) {
                    clipMinY = clip->min.y;
                }
                clip->min.y = clipMinY;
                clipMinZ = view->clipBounds[0].z;
                if (!(clipMinZ <= clip->min.z)) {
                    clipMinZ = clip->min.z;
                }
                clip->min.z = clipMinZ;
                clipMaxX = view->clipBounds[1].x;
                if (!(clip->max.x <= clipMaxX)) {
                    clipMaxX = clip->max.x;
                }
                clip->max.x = clipMaxX;
                clipMaxY = view->clipBounds[1].y;
                if (!(clip->max.y <= clipMaxY)) {
                    clipMaxY = clip->max.y;
                }
                clip->max.y = clipMaxY;
                clipMaxZ = view->clipBounds[1].z;
                if (!(clip->max.z <= clipMaxZ)) {
                    clipMaxZ = clip->max.z;
                }
                clip->max.z = clipMaxZ;
                volumeMinX = view->volumeBounds[0].x;
                if (!(volumeMinX <= bounds->min.x)) {
                    volumeMinX = bounds->min.x;
                }
                bounds->min.x = volumeMinX;
                volumeMinY = view->volumeBounds[0].y;
                if (!(volumeMinY <= bounds->min.y)) {
                    volumeMinY = bounds->min.y;
                }
                bounds->min.y = volumeMinY;
                volumeMinZ = view->volumeBounds[0].z;
                if (!(volumeMinZ <= bounds->min.z)) {
                    volumeMinZ = bounds->min.z;
                }
                bounds->min.z = volumeMinZ;
                volumeMaxX = view->volumeBounds[1].x;
                if (!(bounds->max.x <= volumeMaxX)) {
                    volumeMaxX = bounds->max.x;
                }
                bounds->max.x = volumeMaxX;
                volumeMaxY = view->volumeBounds[1].y;
                if (!(bounds->max.y <= volumeMaxY)) {
                    volumeMaxY = bounds->max.y;
                }
                bounds->max.y = volumeMaxY;
                volumeMaxZ = view->volumeBounds[1].z;
                if (!(bounds->max.z <= volumeMaxZ)) {
                    volumeMaxZ = bounds->max.z;
                }
                bounds->max.z = volumeMaxZ;
                flags->flags |= view->floorSurface;
                view = view->next;
            } while (view != 0);
        }
    }

    if (state->header.lastMode != state->header.views.count) {
        state->header.layoutTimer = 2;
        state->header.lastMode = state->header.views.count;
        return;
    }
    timer = state->header.layoutTimer;
    if (timer != 0) {
        state->header.layoutTimer = (s32) (timer - 1);
    }
}

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

/* Per-frame race update: clears three per-frame flags of the race's own racer, passes the race's first word to Cache_MarkResourceInUse, runs the 30-frame flash timer (restarted while g_simpleObjectPauseState is set or in mode 3) and while it runs clears the screen with a full-screen viewport, scissor and fill before Geometry_InvalidateMaterialKeys, then updates every racer in the list until it ends or Cinema_IsSequenceActive or Cinema_IsSequenceInWindow reports, updates the race's own racer, hands the list to Playerai_DrawViewMatchCountdown when the replay flag of g_playerViewRenderContext is set, and passes the own racer's menu block to Menu_DispatchMenuListCallback. */
void Camera_DrawActiveViews(ScreenMessageOwner *race, s32 world)
{
    GameplayCamera *racer;
    race->self.clearRed = 0;
    race->self.clearGreen = 0;
    race->self.clearBlue = 0;
    if (race->header.allocation != 0) {
        Cache_MarkResourceInUse(0, race->header.allocation);
    }
    if (g_gameSession.clockPaused != 0 || race->header.views.count == 3) {
        g_cameraFramingTransitionTimer = 30.0f;
    }
    if (g_cameraFramingTransitionTimer != 0.0f) {
        g_cameraFramingTransitionTimer -= g_frameElapsedTime;
    }
    if (g_cameraFramingTransitionTimer < 0.0f) {
        g_cameraFramingTransitionTimer = 0.0f;
    }
    if (g_cameraFramingTransitionTimer != 0.0f) {
        racer = race->header.views.head;
        if (racer != 0) {
            gDPPipeSync(g_displayListCursor++);
            gSPDisplayList(g_displayListCursor++, ((g_cameraViewDisplayListPrimary)));
            gSPDisplayList(g_displayListCursor++, ((g_cameraViewDisplayListSecondary)));
            racer->viewports[g_lightingBufferIndex].vscale[0] = SCREEN_WD;
            racer->viewports[g_lightingBufferIndex].vscale[1] = SCREEN_HT;
            racer->viewports[g_lightingBufferIndex].vtrans[0] = SCREEN_WD;
            racer->viewports[g_lightingBufferIndex].vtrans[1] = SCREEN_HT;
            gDma2p(g_displayListCursor++, G_MOVEMEM, ((&racer->viewports[g_lightingBufferIndex])), 16, G_MV_VIEWPORT, 0);
            gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
            gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, (u32)((g_currentRenderFrame->colorImage)));
            gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
            gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);
            gDPSetRenderMode(g_displayListCursor++, ((0)), 0);
            gDPSetFillColor(g_displayListCursor++, ((0x10001)));
            gDPFillRectangle(g_displayListCursor++, 0, 0, (SCREEN_WD), (SCREEN_HT));
            Geometry_InvalidateMaterialKeys();
        }
    }
    for (racer = race->header.views.head; racer != 0;) {
        Camera_SetupViewportAndFog(racer);
        Camera_DrawWorldViewLayers((char *) racer, (char *) world);
        if (racer->monochrome != 0) {
            Gsky_DrawViewportEffectNoOp(racer, racer->effectArgument);
        }
        Camera_DrawViewportOverlays((View *) racer);
        Camera_DrawAndAdvanceMessages(race, racer);
        Menu_DispatchMenuListCallback(&racer->messageList);
        Camera_DrawViewportBorder(racer);
        if (Cinema_IsSequenceActive() != 0 || Cinema_IsSequenceInWindow() != 0) {
            racer = 0;
        } else {
            racer = racer->next;
        }
    }
    Camera_SetupViewportAndFog(&race->self);
    if (race->header.views.count == 0) {
        Camera_DrawViewportOverlays((View *) &race->self);
    }
    Camera_DrawAndAdvanceMessages(race, &race->self);
    if (g_playerViewRenderContext.game.local != 0) {
        racer = race->header.views.head;
        if (racer != 0) {
            Playerai_DrawViewMatchCountdown(&g_playerViewRenderContext, racer);
        }
    }
    Menu_DispatchMenuListCallback(&race->self.messageList);
}

void Camera_DrawViewportBorder(GameplayCamera *racer) {
    View *entity = (View *)racer;
    f32 x;
    f32 y;
    f32 width;
    f32 height;

    Geometry_InvalidateMaterialKeys();
    x = entity->viewport[2];
    y = entity->viewport[3];
    width = entity->viewport[0];
    height = entity->viewport[1];
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE,
                     0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE);
    gDPSetRenderMode(g_displayListCursor++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0, 0, 0, 0);
    gDPFillRectangle(g_displayListCursor++, x, y, (x + width) - 1.0f, y + 2.0f);
    gDPFillRectangle(g_displayListCursor++, x, (y + height) - 2.0f,
                    (x + width) - 1.0f, (y + height) - 1.0f);
    gDPFillRectangle(g_displayListCursor++, x, y, x + 2.0f, (y + height) - 1.0f);
    gDPFillRectangle(g_displayListCursor++, (x + width) - 2.0f, y,
                    (x + width) - 1.0f, (y + height) - 1.0f);
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE,
                     0, 0, 0, SHADE, 0, 0, 0, SHADE);
    gDPSetRenderMode(g_displayListCursor++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetFillColor(g_displayListCursor++, (1 << 16) | 1);
    gDPFillRectangle(g_displayListCursor++, x, y, (x + width) - 1.0f, y);
    gDPFillRectangle(g_displayListCursor++, x, (y + height) - 1.0f,
                    (x + width) - 1.0f, (y + height) - 1.0f);
    gDPFillRectangle(g_displayListCursor++, x, y, x, (y + height) - 1.0f);
    gDPFillRectangle(g_displayListCursor++, (x + width) - 1.0f, y,
                    x + width, (y + height) - 1.0f);
}

/* Posts a text as on-screen messages, one per line: when Cinema_IsSequenceActive reports it, the messages already in
 * the pool's object list are flagged kind 4 and the new ones get kind 1, otherwise kind 2; the text (or
 * g_screenMessageSubstitutionReplacement when given g_screenMessageSubstitutionSource) is split at newlines and for each non-empty line the oldest message node
 * of the owner's active message list is recycled and set up centred horizontally 80 pixels above the bottom of the
 * screen at unit size. Returns the last message node. */



static inline CCameraText *Camera_RecycleOldestMessage(struct ScreenMessageOwner *owner, struct GameplayCamera *pool) {
    CCameraText *oldest;

    oldest = owner->activeMessages.head;
    if (oldest != 0) {
        Gsky_ClearScreenMessage(oldest);
        List_RemoveIntrusive(&owner->activeMessages, oldest);
        List_AppendIntrusive(&pool->objects, oldest);
    }
    return oldest;
}

static inline CCameraText *Camera_PostMessageLines(struct ScreenMessageOwner *owner, struct GameplayCamera *pool, u8 *text, s32 kind, f32 size, s32 target) {
    CCameraText *message;
    s32 height;
    u8 *line;
    u8 *p;

    message = 0;
    if (pool == 0) {
        return message;
    }
    if (text == *(u8 **)g_screenMessageSubstitutionSource) {
        text = (u8 *)*g_screenMessageSubstitutionReplacement;
    }
    p = text;
    line = p;
    while (*p != 0) {
        p++;
        if (*p == '\n' || *p == 0) {
            if (line != p) {
                message = Camera_RecycleOldestMessage(owner, pool);
                if (message != 0) {
                    message->kind = kind;
                    message->text = line;
                    message->m_nAlpha = 0;
                    message->alpha = 1.0f;
                    message->m_DisplayTime = size * 15.0f;
                    message->target = target;
                    message->forceScaledText = 0;
                    message->m_ModeTime = 0;
                    message->postResetWord = 0;
                    message->m_XScale = 1.0f;
                    message->m_YScale = 1.0f;
                    height = g_hudReferenceViewportHeight;
                    message->x = g_hudReferenceViewportWidth / 2;
                    message->y = height - 80;
                }
                line = p + 1;
            }
        }
    }
    return message;
}

CCameraText *Camera_PostScreenMessage(struct ScreenMessageOwner *owner, struct GameplayCamera *pool, u8 *text) {
    CCameraText *pending;
    s32 kind;

    kind = 2;
    if (pool == 0) {
        return 0;
    }
    if (Cinema_IsSequenceActive() != 0) {
        pending = pool->objects.head;
        if (pending != 0) {
            kind = 1;
            do {
                pending->kind = 4;
                pending = pending->next;
            } while (pending != 0);
        }
    }
    return Camera_PostMessageLines(owner, pool, text, kind, 1.0f, -1);
}

void Camera_UpdateScreenMessages(struct ScreenMessageOwner *owner, struct GameplayCamera *pool) {
    f32 spacing;
    f32 fade;
    CCameraText *node;
    CCameraText *msg;
    CCameraText *waiting;

    spacing = 9.0f;
    if (pool != 0) {
        OnScreen_SetupTextRendering();
        OnScreen_LoadTextTileModeTwo();
        node = pool->objects.head;
        if (node != 0) {
            node->y = (f32)g_hudReferenceViewportHeight * 0.81f;
            for (msg = node->next; msg != 0; msg = msg->next) {
                msg->y = node->y + spacing;
                node = msg;
            }
        }
        for (msg = pool->objects.tail; msg != 0; msg = msg->prev) {
            Onscrn_DrawText(msg->text, (s32)msg->x, (s32)msg->y, msg->m_nAlpha, 1, 1, 1.0f, 1.0f);
        }
        for (msg = pool->objects.tail; msg != 0; msg = msg->prev) {
            fade = g_frameElapsedTime * 0.06666667f;
            node = msg;
            switch (msg->kind) {
            case 2:
                msg->m_nAlpha = (s32)(Gu_Sinf(msg->m_ModeTime * 1.5707964f) * 255.0f);
                msg->m_ModeTime += fade;
                if (msg->m_ModeTime > 1.0f) {
                    msg->kind = 3;
                    msg->m_ModeTime = 0.0f;
                }
                break;
            case 1:
                msg->m_nAlpha = 0;
                break;
            case 3:
                msg->m_nAlpha = 255;
                break;
            case 4:
                msg->m_nAlpha = (s32)(Math_Cosf(msg->m_ModeTime * 1.5707964f) * 255.0f);
                msg->m_ModeTime += fade;
                if (msg->m_ModeTime > 1.0f) {
                    for (waiting = pool->objects.head; waiting != 0; waiting = waiting->next) {
                        if (waiting->kind == 1) {
                            waiting->kind = 2;
                            waiting->m_ModeTime = 0.0f;
                        }
                    }
                    node->kind = 0;
                    node->m_ModeTime = 0.0f;
                }
                break;
            default:
                node->m_nAlpha = 0;
                node->kind = 0;
                break;
            }
        }
        for (msg = pool->objects.tail; msg != 0; msg = node) {
            node = msg->prev;
            if (msg->kind == 0) {
                List_RemoveIntrusive(&pool->objects, msg);
                List_PrependIntrusive(&owner->activeMessages, msg);
            }
        }
    }
}

/* Draws and advances the screen messages of one view, retiring finished ones. */
void Camera_DrawAndAdvanceMessages(ScreenMessageOwner *race, GameplayCamera *racer) {
    f32 scale;
    f32 width, height, x, y;
    f32 scaleY;
    f32 scaleX;
    f32 offsetY;
    s32 small;
    CCameraText *message;
    CCameraText *prev;
    f32 drop;
    f32 offsetXf;
    f32 left;
    s32 centered;

    if (Cinema_IsSequenceInWindow() != 0) {
        Camera_UpdateScreenMessages((struct ScreenMessageOwner *)race, (struct GameplayCamera *)racer);
        return;
    }
    scale = g_cameraMessageResolutionScale;
    height = racer->viewHeight;
    width = racer->viewWidth;
    x = racer->viewLeft;
    y = racer->viewTop;
    scaleY = height / (f32)g_hudReferenceViewportHeight;
    scaleX = width / (f32)g_hudReferenceViewportWidth;
    small = 1;
    if (!(scaleX < scale) && !(scaleY < scale)) {
        small = 0;
    }
    offsetXf = width * g_cameraMessageHorizontalOffsetScale + x;
    drop = scaleY * g_cameraMessageDropScale;
    left = height * g_cameraMessageVerticalOffsetScale + y;
    offsetY = left - drop;
    message = racer->objects.tail;
    for (; message != 0; message = prev) {
        prev = message->prev;
        if (message->kind != 0) {
            OnScreen_SetupTextRendering();
            if (small || message->forceScaledText != 0) {
                scale = g_cameraMessageLargeTextScale;
                if (g_frontendCurrentVideoModeIndex == 0) {
                    scale = g_cameraMessageSmallTextScale;
                }
                scaleY = g_cameraMessageVerticalScale;
                centered = 1;
            } else {
                scale = g_cameraMessageDefaultScale;
                centered = 1;
            }
            Onscrn_DrawText(message->text, (s32)offsetXf, (s32)offsetY, message->m_nAlpha, centered, centered,
                             message->alpha * scaleX * scale, message->alpha * scaleY * scale);
            switch (message->kind) {
            case 2:
                message->m_nAlpha += 31;
                if (message->m_nAlpha >= 255) {
                    message->m_nAlpha = 255;
                    message->kind = 3;
                    message->m_Time = message->m_DisplayTime;
                }
                message->alpha = Gu_Sinf((f32)message->m_nAlpha * g_cameraMessageFadeInAngleScale);
                break;
            case 3:
                message->m_Time -= g_frameElapsedTime;
                left = message->m_Time;
                message->m_nAlpha = 255;
                message->alpha = g_cameraMessageFullAlpha;
                if (left < 0.0f) {
                    message->kind = 4;
                    message->m_nAlpha = 128;
                }
                break;
            case 4:
                message->alpha -= Gu_Sinf(g_cameraMessageFadeOutPhase - (f32)message->m_nAlpha * g_cameraMessageFadeOutAngleScale) * g_cameraMessageFadeOutAmplitude;
                if (message->alpha < 0.0f) {
                    message->alpha = 0.0f;
                }
                message->m_nAlpha -= 12;
                if (message->m_nAlpha < 0) {
                    message->m_nAlpha = 0;
                    message->kind = 0;
                }
                break;
            }
        }
        if (message->kind == 0) {
            List_RemoveIntrusive(&racer->objects, message);
            List_PrependIntrusive(&race->activeMessages, message);
        }
        offsetY -= scaleY * g_cameraMessageLineOffsetScale / scale;
    }
}

#if !(defined(VERSION_US_REV1))
const float k_cameraViewTuning[14] = {
    1.0f, 0.5f, 18.0f, 0.8f,
    0.6f, 0.5f, 0.8f, 0.4f,
    0.006159986f, 1.0f, 0.012319972f, 255.0f,
    0.33333334f, 9.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_cameraViewTuning[14] = {
    1.0f, 0.5f, 18.0f, 0.8f,
    0.6f, 0.5f, 0.8f, 0.4f,
    0.006159986f, 1.0f, 0.012319972f, 255.0f,
    0.33333334f, 9.0f,
};
#endif

/* Retained data for this translation unit. */
#if !(defined(VERSION_US_REV1))
const float k_CameraEncodedWords[2] = {
    0.5f, 0.5f,
};
#endif
#if defined(VERSION_US_REV1)
const float k_cameraFrustumBoundsHalves[2] = {
    0.5f, 0.5f,
};
#endif

const char g_camerasText[8] = "Cameras";

const unsigned char k_CameraEncodedBytes[13] = "Camera Texts";
#if !(defined(VERSION_US_REV1))
const float k_cameraDrawActiveViewsHalf[1] = {
    0.5f,
};
#endif
#if defined(VERSION_US_REV1)
const float k_CameraHalfWords[1] = {
    0.5f,
};
#endif
