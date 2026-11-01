#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/LIGHTDATA.H"
#include "TYPES.H"
#include "CAMERA/FADE_AND_COLOR_BLEND_VIEWS.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/APPROACHLOCATION.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "COMMON/WORLD.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/STATERECAT10.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/OBJ.H"
#include "COMMON/TRIPLE.H"
#include "CAMERA/GSKY_GETFLOORSURFACESHAKE.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include <ultra64.h>
#include "COMMON/VIDEO_DIMENSIONS.H"
#include <PR/gbi.h>
#include "COMMON/DISPLAY.H"
#include "COMMON/RESULTS.H"
#include "RENDER/SETN64_ONWORLDVIEWDRAW.H"
#include "CAMERA/CAMERA.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/TRIGGER_AND_FLOAT_VALUE_OPERATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/OBJB.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include <PR/abi.h>
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/S1.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "COMMON/DESCRIPTORRECAT29.H"
#include "ENGINE/CINEMA/CINEMA.H"
#include "ENGINE/SETN64.H"
#include "ONSCRN.H"

/* 80233920.CPP */
extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
extern f32 Gu_Sqrtf(f32);




void Camera_AccumulateDistanceScaledShake(CShake *shake, CVector3 position, CVector3 *out) {
    f32 distance;
    f32 value;
    AxisWave *wave;

    Graphu64_SubtractVectors(&position, &position, &shake->m_vPos);
    distance = Gu_Sqrtf((position.x * position.x) +
                             (position.y * position.y) +
                             (position.z * position.z));
    if (distance < shake->m_Radius) {
        distance = Defs_CosineEase(g_cameraShakeDistanceComplement - (distance / shake->m_Radius));

        wave = &shake->x;
        if (wave->mode == 0) goto x_sine;
        if (wave->mode != 1) goto x_zero;
        value = Gu_Sinf(wave->m_Angle * g_cameraShakeXAngleScale) * wave->m_Amp;
        goto x_done;
x_sine:
        value = Graphu64_RandomBetween(-wave->m_Amp, wave->m_Amp);
        goto x_done;
x_zero:
        value = 0.0f;
x_done:
        out->x += value * distance;

        wave = &shake->y;
        if (wave->mode == 0) goto y_sine;
        if (wave->mode != 1) goto y_zero;
        value = Gu_Sinf(wave->m_Angle * g_cameraShakeYAngleScale) * wave->m_Amp;
        goto y_done;
y_sine:
        value = Graphu64_RandomBetween(-wave->m_Amp, wave->m_Amp);
        goto y_done;
y_zero:
        value = 0.0f;
y_done:
        out->y += value * distance;

        wave = &shake->z;
        if (wave->mode == 0) goto z_sine;
        if (wave->mode != 1) goto z_zero;
        value = Gu_Sinf(wave->m_Angle * g_cameraShakeZAngleScale) * wave->m_Amp;
        goto z_done;
z_sine:
        value = Graphu64_RandomBetween(-wave->m_Amp, wave->m_Amp);
        goto z_done;
z_zero:
        value = 0.0f;
z_done:
        out->z += value * distance;
    }
}

/* Advances an overlay's fade: state 1 fades the alpha at 0x551 in over the 0x54B-frame duration up to the
 * maximum at 0x54A, state 2 holds the maximum for 0x54C frames, state 3 fades out over 0x54D frames and
 * returns to state 0; each state change restarts the timer at 0x538, which then advances by the frame
 * time g_frameElapsedTime. */



extern f32 g_frameElapsedTime;

void Camera_AdvanceOverlayFade(Overlay *overlay) {
    switch (overlay->state) {
    case 1:
        if (overlay->fadeIn <= overlay->timer) {
            overlay->state = 2;
            overlay->timer = 0.0f;
            goto hold;
        }
        overlay->alpha = (u32)(overlay->timer / (overlay->fadeIn + 1) * overlay->alphaMax);
        break;
    case 0:
        break;
    case 2:
    hold:
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





extern u8 g_playerSequenceSavedViewBytes[4];
extern void SetN64_DrawColorRectangle(void *, u8 *, s32, s32, s32, s32);
extern s32 Cinema_IsSequenceInWindow(void);
extern s32 SetN64_IsModeThirteen(void);
extern void Playerai_UpdateViewPlayerProjection(void *, View *);
extern void Cinema_DrawSequenceOverlay(View *);

static inline SharedPlayer *find_owner(View *entity) {
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

    owner = find_owner(entity);
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
const unsigned int k_CameraZeroWordsVariant1[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_EU_X)
const unsigned int k_CameraZeroWordsVariant4[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_EU)
const unsigned int k_CameraZeroWordsVariant3[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_DE)
const unsigned int k_CameraZeroWordsVariant2[1] = {
    0x00000000,
};
#endif

/* 80233920_2.CPP */
extern u32 g_gameLoopFrameCount;

/* Animate the shared light colors and direction, and both actor tint colors. */
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
            phaseScale * (f32) g_gameLoopFrameCount * ((f32) (channel + 2) * 4.0f) *
            0.01745329424738884f) * 16.0f)) + 16.0f + 48.0f;
        g_playerModelLighting[0].ambientCopy[channel] = g_playerModelLighting[0].ambient[channel] = (u32)ambient;
        diffuse = (((Gu_Sinf(
            phaseScale * (f32) g_gameLoopFrameCount * ((f32) (channel + 2) * 4.0f) *
            0.01745329424738884f) * 64.0f) + 255.0f) - 64.0f) - 1.0f;
        g_playerModelLighting[0].diffuseCopy[channel] = g_playerModelLighting[0].diffuse[channel] = (u32)diffuse;
        channel += 1;
    } while (channel < 3);
    direction.x = Gu_Sinf((f32) (g_gameLoopFrameCount * 6) * 0.01745329424738884f);
    direction.y = Gu_Sinf((f32) (g_gameLoopFrameCount * 8) * 0.01745329424738884f);
    direction.z = Math_Cosf((f32) (g_gameLoopFrameCount * 10) * 0.01745329424738884f);
    Graphu64_NormalizeVec3(&direction);
    direction.x *= 120.0f;
    direction.y *= 120.0f;
    direction.z *= 120.0f;
    g_playerModelLighting[0].direction[0] = (u32)direction.x;
    g_playerModelLighting[0].direction[1] = (u32)direction.y;
    g_playerModelLighting[0].direction[2] = (u32)direction.z;
    red = (Gu_Sinf(2.0f * (phaseScale * (f32) g_gameLoopFrameCount) * 0.06981317698955536f) * 64.0f) + 128.0f;
    redByte = (u32)red & 0xF8;
    actor->color[0] = redByte;
    actor->secondaryColor[0] = redByte;
    green = (Gu_Sinf(phaseScale * (f32) g_gameLoopFrameCount * 0.20943953096866608f) * 64.0f) + 128.0f;
    greenByte = (u32)green & 0xF8;
    actor->color[1] = greenByte;
    actor->secondaryColor[1] = greenByte;
    blue = (Gu_Sinf(phaseScale * (f32) g_gameLoopFrameCount * 0.27925270795822144f) * 64.0f) + 128.0f;
    blueByte = (u32)blue & 0xF8;
    actor->color[2] = blueByte;
    actor->secondaryColor[2] = blueByte;
}

/* 80233920_3.CPP */
extern void *Scene_GetModelRecordByIndexPointer(Shared_World *, u16 *);

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

/* 800C81A4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C81A4 */
#endif

/* 80233920_4.CPP */
extern struct MenuModelScreen g_fallbackScreenMessageEmitter[];
extern void MultiplyQuaternions(void*,void*,void*);
extern u32 Weapon_UpdateShakeAxis(CShakeAxis*);
extern void Graphu64_MultiplyAffineMatrices(f32*,f32*,f32*);
/* The camera position is passed as a three-word CVector3 value. */

/* Actor transform and camera-effect subobjects. */
typedef struct TransformActor {
    char pad0[0x28];
    f32 yaw,pitch,extraYaw,roll;
    TransformVector position;
    f32 height;
    Rotation base;
    char pad58[0x7C-0x58];
    s32 enabled;
    char pad80[0xA0-0x80];
    CShake effect;
    char padF4[0x134-0xF4];
    CVector3 cached;
    Rotation rotation,combined;
    f32 matrix[16];
} TransformActor;
typedef struct TransformWorld {
    s32 identifier;
    char pad4[0x11AC-4];
    CShake *effects;
} TransformWorld;

void Camera_BuildShakenViewTransform(void *cameraTransform) {
    TransformActor *actor=cameraTransform;
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

    if (actor->enabled != 0) {
        adjustedPitch = actor->pitch;
        adjustedRoll = actor->roll;
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
            combinedQuaternion = actor->combined.f;
            yawHalfSine = Gu_Sinf((actor->yaw + actor->extraYaw) * gameplayAngleScale);
            q28.word[0] = 0;
            q28.f[1] = yawHalfSine;
            q28.word[2] = 0;
            cosineInput = ((actor->yaw + actor->extraYaw) * gameplayAngleScale);
            g_turretAimSine = yawHalfSine;
            baseQuaternion = actor->base.f;
            q28.f[3] = Math_Cosf(cosineInput);
            MultiplyQuaternions(q48.f, q18.f, q28.f);
            MultiplyQuaternions(combinedQuaternion, q48.f, baseQuaternion);
            MultiplyQuaternions(actor->rotation.f, q38.f, combinedQuaternion);
            MultiplyQuaternions(q58.f, q38.f, q48.f);
            MatrixFromQuaternion(q58.f, m68);
            zero=0.0f;
            Graphu64_BuildTranslationMatrix(mA8, zero, actor->height, zero);
            MatrixFromQuaternion(baseQuaternion, mE8);
            result.x = zero;
            result.y = zero;
            result.z = zero;
            Camera_AccumulateDistanceScaledShake(&actor->effect, actor->effect.m_vPos, &result);
            Weapon_UpdateShakeAxis(&actor->effect.x);
            Weapon_UpdateShakeAxis(&actor->effect.y);
            Weapon_UpdateShakeAxis(&actor->effect.z);
            if (cameraTransform != &g_fallbackScreenMessageEmitter) {
                effect = ((TransformWorld*)(void*)&g_fallbackScreenMessageEmitter)->effects;
                if (effect != 0) {
                    do {
                        Camera_AccumulateDistanceScaledShake(effect, actor->position.value, &result);
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
                actor->position.value.x + transformed.x,
                actor->position.value.y + viewMotionOffsets.y + transformed.y,
                actor->position.value.z + transformed.z);
            Graphu64_MultiplyAffineMatrices(actor->matrix, matrix, m128);
        } else {
            cosineInput = actor->roll;
            sequenceAngleScale = g_cameraSequenceAngleScale;
            sequenceRollHalfSine = Gu_Sinf(cosineInput * sequenceAngleScale);
            q38.word[0] = 0;
            q38.word[1] = 0;
            q38.f[2] = sequenceRollHalfSine;
            cosineInput = (actor->roll * sequenceAngleScale);
            g_turretAimSine = sequenceRollHalfSine;
            q38.f[3] = Math_Cosf(cosineInput);
            sequencePitchHalfSine = Gu_Sinf(actor->pitch * sequenceAngleScale);
            q18.f[0] = sequencePitchHalfSine;
            q18.word[1] = 0;
            q18.word[2] = 0;
            cosineInput = (actor->pitch * sequenceAngleScale);
            g_turretAimSine = sequencePitchHalfSine;
            q18.f[3] = Math_Cosf(cosineInput);
            sequenceYawHalfSine = Gu_Sinf((actor->yaw + actor->extraYaw) * sequenceAngleScale);
            q28.word[0] = 0;
            q28.f[1] = sequenceYawHalfSine;
            q28.word[2] = 0;
            cosineInput = ((actor->yaw + actor->extraYaw) * sequenceAngleScale);
            g_turretAimSine = sequenceYawHalfSine;
            q28.f[3] = Math_Cosf(cosineInput);
            MultiplyQuaternions(q48.f, q18.f, q28.f);
            actor->combined=q48;
            MultiplyQuaternions(actor->rotation.f, q38.f, actor->combined.f);
            MatrixFromQuaternion(q48.f, m68);
            Graphu64_BuildTranslationMatrix(m128,actor->position.value.x,actor->position.value.y,actor->position.value.z);
            Graphu64_MultiplyAffineMatrices(actor->matrix, m68, m128);
        }

        actor->cached.x = adjustedPitch;
        actor->cached.z = adjustedRoll;
        actor->cached.y = (f32) actor->yaw;
    }
}

/* 800C82E8.CPP */
#if !(defined(VERSION_US_REV1))
const float k_CameraEncodedWords[2] = {
    0.5f, 0.5f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_CameraEncodedWordsBlock7_Camera.c */
const float k_CameraEncodedWordsBlock7[2] = {
    0.5f, 0.5f,
};
#endif

/* 80233920_5.CPP */
/* Rebuilds a camera's view volume when it is active: the eye and the four far corners at depth 0x528 come
 * either from the field of view 0x530 and aspect 0x70 (a perspective camera, radius the slant distance to
 * the far plane) or, while the global orthographic flag is set, from half the view extents 0x74 and 0x78
 * (radius the corner distance); the corners are transformed by the view matrix at 0x160 into 0x260, the
 * clip planes at 0x2F0 and the bounds at 0x350 are rebuilt from them, and a box around the eye of that
 * radius (half again as tall) is stored at 0x368. */





extern f32 Gu_Sqrtf(f32);
extern void Graphu64_TransformPoints(void *, CVector3 *, CVector3 *, s32);
extern void Visdata_BuildFrustumPlanes(void *, CVector3 *, CVector3 *, CVector3 *, CVector3 *, CVector3 *);
extern void Region_ComputePointBounds(void *, s32, CVector3 *);







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

/* 800C82F0.CPP */
#if !(defined(VERSION_US_REV1))
const float k_CameraEncodedWordsBlock1[3] = {
    0.008726647f, 0.5f, 1.5f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_CameraEncodedWordsBlock8_Camera.c */
const float k_CameraEncodedWordsBlock8[3] = {
    0.008726647f, 0.5f, 1.5f,
};
#endif

/* 80233920_6.CPP */
struct CShakeAxis_t;
extern u32 Weapon_UpdateShakeAxis(struct CShakeAxis_t *state);

int Cinema_IsSequenceInWindow(void);
f32 Cinema_GetSequenceResponse();
void Graphu64_InvertAffineMatrix(f32 *, f32 *);
void Graphu64_MultiplyAffineMatrices(f32 *, f32 *, f32 *);
void Graphu64_MultiplyMatrices(f32 *, f32 *, f32 *);
void GraphU64_PackFixedMatrix(f32 *, void *);
void Graphu64_IdentityMatrix(void *);
void Graphu64_ClampMatrixToFixedRange(f32 *);
void Graphu64_BuildScaleMatrix(void *, f32, f32, f32);
void CopyMatrix(float *, float *);
void Graphu64_GetMatrixTranslation(char *, float *);
void BuildYawMatrix(void *, f32);
void PitchMatrix(void *, f32);
void YawMatrix(void *, f32);
void MatrixFromQuaternion(f32 *, f32 *);

extern void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate);
f32 Region_GetPolygonHeight(void *, f32, f32);
int Tsmos_IsFrontendActive(void);
int Tsmos_GetModeOneFlag(void);



f32 Gu_Sqrtf(f32);
void Menu_UpdateDialogList(struct MessageList *list);
void Sky_UpdateSceneEffects(void *scene, void *host);                  /* extern */
               /* extern */
 /* extern */

extern struct MenuModelScreen g_fallbackScreenMessageEmitter[];
extern s32 g_lightingBufferIndex;
extern f32 g_frameElapsedTime;
extern s32 g_hudReferenceViewportWidth;
typedef struct SharedCameraOwnerView CameraOwnerView;
typedef struct SharedCameraRenderView CameraGlobalRenderView;
typedef struct CameraRuntimeMode CameraRuntimeModeView;
typedef struct Lights CameraFrameLights;
typedef struct CameraFloorSurfaceView CameraFloorPolygonView;







typedef struct Shared_CameraModeCallback CameraModeCallbackEntry;
extern CameraModeCallbackEntry g_cameraModeCallbacks[];
extern CameraGlobalRenderView g_playerWeaponClassMode;


/* unable to generate initializer: unknown type; const */

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x268, 0x26c, 0x270, 0x274, 0x278, 0x27c, 0x280, 0x284, 0x288, 0x298, 0x29c, 0x2a8, 0x2ac, 0x2b0, 0x2b4], gap at: 0x28c. */
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

    actorCursor = g_transientPlayerList.actorList;
    while (actorCursor != 0) {
        if (actorCursor->camera == camera) {
            cameraOwner = actorCursor;
            goto actor_found;
        }
        actorCursor = actorCursor->nextActor;
    }
    cameraOwner = 0;
actor_found:
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
        Weapon_UpdateShakeAxis(camera->shakeAxisX);
        Weapon_UpdateShakeAxis(camera->shakeAxisY);
        Weapon_UpdateShakeAxis(camera->shakeAxisZ);
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
        if ((fovOverrideState == 1) && (Tsmos_GetModeOneFlag() == fovOverrideState)) {
            fovy = 45.0f;
        } else if (zoomBlend != 0.0f) {
            fovy = (zoomBlend * (initial_zoom - 75.0f)) + 75.0f;
        } else {
            fovy = 75.0f;
        }
    }
    if ((Cinema_IsSequenceInWindow() != 0) && (camera != &g_fallbackScreenMessageEmitter)) {
        aspect = camera->viewWidth / camera->viewHeight;
    } else if (g_playerWeaponClassMode.renderMode == 2) {
        aspect = 0.6666667f;
        if (g_playerWeaponClassMode.sequenceViewReady == 0) {
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
    state = &g_playerWeaponClassMode.state;
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
    BuildYawMatrix(camera->faceScreenUpright, camera->roll);
    if (g_playerWeaponClassMode.alternateViewEnabled != 0) {
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

extern s32 g_lightingBufferIndex;
extern s32 g_hudReferenceViewportWidth;
extern Gfx *g_displayListCursor;
extern SharedCameraRenderView g_playerWeaponClassMode;
extern void Geometry_SetViewEffect(s32);
extern void Textload_SetTextureEffect(unsigned int);
extern void Geometry_SelectEffectModes(void);
extern void TextLoad_ResetTextureCache(void);
extern s32 Tsmos_IsFrontendActive(void);
extern s32 GetMenuScreenOwner(void);
extern void SetN64_ClearDepthRect(void *, s32, s32, s32, s32, s32);
extern s32 Cinema_IsSequenceInWindow(void);
extern u32 Cinema_GetSequenceProperty(void);
extern void Geometry_SetColorDither(s32);
extern void Defs_SetupPointLights(void *);
/* Splits a 0x00BBGGRR fade color into its three fog/fill channels. */
static inline void Camera_UnpackColor(u32 color, u8 *red, u8 *green, u8 *blue) {
    *blue = color >> 16;
    *green = color >> 8;
    *red = color;
}

/* Set projection, viewport and look-at, then draw the view's clear rectangle and fog. */
void Camera_SetupViewportAndFog(RacerViewport *view) {
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
    gSPDisplayList((*gfx)++, ((&g_cameraViewDisplayListFirst)));
    gSPDisplayList((*gfx)++, ((&g_cameraViewDisplayListSecond_de)));
    view->screenScaleX = 1.0f;
    view->screenScaleY = 1.0f;
    view->screenScaleX = view->viewportScaleX;
    view->screenScaleY = view->viewportScaleY;
    x = view->viewportX;
    y = view->viewportY;
    width = view->viewportWidth;
    maxx = SCREEN_WD - 1;
    height = view->viewportHeight;
    ulx = x;
    maxy = SCREEN_HT - 1;
    vx = (width + width) * view->screenScaleX;
    vy = (height + height) * view->screenScaleY;
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
    gSPMatrix((*gfx)++, view->projectionMatrices[frame], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPPerspNormalize((*gfx)++, view->perspectiveNorm);
    view->viewports[frame].vscale[0] = vx;
    view->viewports[frame].vscale[1] = vy;
    view->viewports[frame].vtrans[0] = (vx * 0.25f + view->viewportX) * 4.0f;
    view->viewports[frame].vtrans[1] = (vy * 0.25f + view->viewportY) * 4.0f;
    gSPViewport((*gfx)++, &view->viewports[frame]);
    gDPSetScissor((*gfx)++, G_SC_NON_INTERLACE, ulx, uly, lrx, lry);
    gSPLookAtX((*gfx)++, &view->lights[frame][0]);
    gSPLookAtY((*gfx)++, &view->lights[frame][4]);
    Geometry_SetViewEffect(view->effect);
    if (view != &g_playerWeaponClassMode.view) {
        Textload_SetTextureEffect(view->effect);
    }
    Geometry_SelectEffectModes();
    TextLoad_ResetTextureCache();
    gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
    flag = 0;
    if (Tsmos_IsFrontendActive() != 0) {
        flag = GetMenuScreenOwner() != 2;
    }
    if (view != &g_playerWeaponClassMode.view || g_playerWeaponClassMode.renderMode == 0 || flag != 0) {
        Geometry_SetModePreset(20);
        gDPPipeSync(g_displayListCursor++);
        SetN64_ClearDepthRect(&g_gameSession, ulx, lrx, uly, lry, view->effect);
        gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
        if (g_gameSettings.flags & 0x4000) {
            red = 0;
            green = 0;
            blue = 0;
        } else {
            red = view->hit & 0xF8;
            green = view->boost & 0xF8;
            blue = view->spin & 0xF8;
        }
        if (Cinema_IsSequenceInWindow() != 0) {
            color = Cinema_GetSequenceProperty();
            if (color != 0xFF00) {
                Camera_UnpackColor(color, &red, &green, &blue);
            }
        }
        gSPGeometryMode(g_displayListCursor++, 0, G_FOG);
        if (view->effect != 0) {
            gDPSetFogColor(g_displayListCursor++, 0, 0, 0, 255);
            gSPFogPosition(g_displayListCursor++, 995, 1000);
        } else {
            gDPSetFogColor(g_displayListCursor++, red, green, blue, 255);
            gSPFogPosition(g_displayListCursor++, (u16)view->fogNear, 1000);
        }
        gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, buffer->colorImage);
        if (view->effect != 0) {
            gDPSetFillColor(g_displayListCursor++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));
        } else {
            gDPSetFillColor(g_displayListCursor++, (GPACK_RGBA5551(red, green, blue, 1) << 16) |
                                              GPACK_RGBA5551(red, green, blue, 1));
        }
        if (view != &g_playerWeaponClassMode.view || g_playerWeaponClassMode.state.mode == 3) {
            gDPFillRectangle(g_displayListCursor++, ulx, uly, lrx, lry);
        }
    }
    gDPPipeSync(g_displayListCursor++);
    Geometry_SetColorDither(0);
    gDPSetAlphaDither(g_displayListCursor++, G_AD_NOTPATTERN);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    if (view != &g_playerWeaponClassMode.view) {
        Defs_SetupPointLights(view);
    }
    gDPPipeSync(g_displayListCursor++);
}

/* 80233920_7.CPP */
/* Draws one view of the game world: after the per-frame setup (SetN64_OnWorldViewDraw) it runs the world, player,
 * effect, particle, object and translucent passes for the view in order, skipping the player and effect
 * passes in the alternate HUD mode (Cinema_IsSequenceInWindow) and running the extra passes only when SetN64_IsModeThirteen
 * allows; when debug flag 0x200 is set it then clears the view's rectangle at 0x29C..0x2A8 to the far
 * depth with a fill-rectangle command. */


extern Gfx *g_displayListCursor;

extern s32 Cinema_IsSequenceInWindow(void);
extern void Playerai_UpdateViewModelBounds(void *, char *);
extern s32 SetN64_IsModeThirteen(void);
extern void Playerai_DrawPlayersForView(void *, char *);
extern void Scene_DrawOpaqueActors(char *, char *);
extern void Fx_DrawBoundedParticleQuads(void *, char *);
extern void Scene_DrawTransparentObjects(char *, char *);
extern void Playerai_DrawPlayerModelsForView(GamePlayerListView *, char *);
extern void Sky_DrawDepthSortedSceneEffects(char *, char *);
extern void Scene_DrawWorldParticles(char *, char *);
extern void Fx_DrawLinkedGeometry(void *, char *);
extern void Gsky_DrawObjectFlares(char *);
extern void Playerai_DrawViewPlayer(void *, char *);







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
    Fx_DrawBoundedParticleQuads(&g_actorParticleScene, view);
    if (Cinema_IsSequenceInWindow() == 0) {
        SetN64_DrawVisibleEffects(&((Shared_World *)world)->system11778, view);
    }
    Scene_DrawTransparentObjects(world, view);
    Playerai_DrawPlayerModelsForView(&g_playerViewRenderContext, view);
    Sky_DrawDepthSortedSceneEffects((char *)&((GameplayCamera *)view)->sceneEffects, view);
    Scene_DrawWorldParticles(world, view);
    Fx_DrawLinkedGeometry(&g_actorParticleScene, view);
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

/* 800C83C4.CPP */
/* ROM-grounded data: rodata/shared/800C83C4 */
const char g_camerasText[8] = "Cameras";

/* 800C83CC.CPP */
const unsigned char k_CameraEncodedBytes[13] = "Camera Texts";






/* 800C83DC.CPP */
#if !(defined(VERSION_US_REV1))
const float k_CameraEncodedWordsBlock4[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_CameraOneWords_Camera.c */
const float k_CameraOneWords[1] = {
    1.0f,
};
#endif

/* 8023660C.CPP */
/* Eases a camera's four framing values at 0x29C, 0x2A0, 0x2A4 and 0x2A8 toward their targets by 16 each
 * frame, snapping to the targets when Control_IsSnapshotActive_Camera reports a cut and recording the easing rate 30 in
 * g_cameraFramingTransitionTimer whenever a value moves. Adapted from Gsky_StepValueTowardTarget as a static helper.
 */

extern s32 Control_IsSnapshotActive(void);


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

/* 80233920_8.CPP */
extern u32 Weapon_UpdateShakeAxis(CShakeAxis *);
extern void Camera_UpdateViewProjectionAndEffects(GameplayCamera *camera);
/* Update split-screen rectangles, advance transient effects, and merge visible bounds. */
void Camera_UpdateViewportLayoutAndBounds(RaceViewportState *state) {
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

/* 800C8410.CPP */
#if !(defined(VERSION_US_REV1))
const float k_CameraEncodedWordsBlock2[1] = {
    0.5f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_CameraHalfWords_Camera.c */
const float k_CameraHalfWords[1] = {
    0.5f,
};
#endif

/* 80233920_9.CPP */
extern Gfx *g_displayListCursor;
extern s32 g_hudReferenceViewportWidth;
extern s32 g_lightingBufferIndex;
extern f32 g_frameElapsedTime;
extern char g_cameraViewDisplayListFirst;
extern char g_cameraViewDisplayListSecond_de;
extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern void Gsky_DrawViewportEffectNoOp(RacerViewport *, s32);
extern void Menu_DispatchMenuListCallback(struct MenuCallbackListOwner *owner);
extern s32 Cinema_IsSequenceInWindow(void);
extern void Playerai_DrawViewMatchCountdown(WorldCameraDrawActiveViews *, RacerViewport *);
/* Per-frame race update: clears three per-frame flags of the race's own racer, passes the race's first word to Cache_MarkResourceInUse, runs the 30-frame flash timer (restarted while g_simpleObjectPauseState is set or in mode 3) and while it runs clears the screen with a full-screen viewport, scissor and fill before Geometry_InvalidateMaterialKeys, then updates every racer in the list until it ends or Cinema_IsSequenceActive or Cinema_IsSequenceInWindow reports, updates the race's own racer, hands the list to Playerai_DrawViewMatchCountdown when the replay flag of g_playerViewRenderContext is set, and passes the own racer's block at 0x554 to Menu_DispatchMenuListCallback. */
void Camera_DrawActiveViews(Race *race, s32 world)
{
    RacerViewport *racer;
    race->self.hit = 0;
    race->self.boost = 0;
    race->self.spin = 0;
    if (race->header.music != 0) {
        Cache_MarkResourceInUse(0, race->header.music);
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
            gSPDisplayList(g_displayListCursor++, ((&g_cameraViewDisplayListFirst)));
            gSPDisplayList(g_displayListCursor++, ((&g_cameraViewDisplayListSecond_de)));
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
        if (racer->effect != 0) {
            Gsky_DrawViewportEffectNoOp(racer, racer->effectArg);
        }
        Camera_DrawViewportOverlays((View *) racer);
        Camera_DrawAndAdvanceMessages(race, racer);
        Menu_DispatchMenuListCallback(racer->sound);
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
    Menu_DispatchMenuListCallback(race->self.sound);
}


void Camera_DrawViewportBorder(RacerViewport *racer) {
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
 * the pool's list at 0xE40 are flagged kind 4 and the new ones get kind 1, otherwise kind 2; the text (or
 * g_screenMessageSubstitutionReplacement when given g_screenMessageSubstitutionSource) is split at newlines and for each non-empty line the oldest message node
 * of the owner's list at 0xF24 is recycled and set up centred horizontally 80 pixels above the bottom of the
 * screen at unit size. Returns the last message node. */




extern ScreenMessageTextView g_screenMessageSubstitutionReplacement;

extern ScreenMessageTextView g_screenMessageSubstitutionSource;













static inline CCameraText *recycle(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool) {
    CCameraText *oldest;

    oldest = owner->activeMessages.head;
    if (oldest != 0) {
        Gsky_ClearScreenMessage(oldest);
        List_RemoveIntrusive(&owner->activeMessages, oldest);
        List_AppendIntrusive(&pool->freeMessages, oldest);
    }
    return oldest;
}

static inline CCameraText *post_lines(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool, u8 *text, s32 kind, f32 size, s32 target) {
    CCameraText *message;
    s32 height;
    u8 *line;
    u8 *p;

    message = 0;
    if (pool == 0) {
        return message;
    }
    if (text == g_screenMessageSubstitutionSource.text) {
        text = g_screenMessageSubstitutionReplacement.text;
    }
    p = text;
    line = p;
    while (*p != 0) {
        p++;
        if (*p == '\n' || *p == 0) {
            if (line != p) {
                message = recycle(owner, pool);
                if (message != 0) {
                    message->kind = kind;
                    message->text = line;
                    message->m_nAlpha = 0;
                    message->alpha = 1.0f;
                    message->m_DisplayTime = size * 15.0f;
                    message->target = target;
                    message->pad20 = 0;
                    message->m_ModeTime = 0;
                    message->pad2C = 0;
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

CCameraText *Camera_PostScreenMessage(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool, u8 *text) {
    CCameraText *pending;
    s32 kind;

    kind = 2;
    if (pool == 0) {
        return 0;
    }
    if (Cinema_IsSequenceActive() != 0) {
        pending = pool->freeMessages.head;
        if (pending != 0) {
            kind = 1;
            do {
                pending->kind = 4;
                pending = pending->next;
            } while (pending != 0);
        }
    }
    return post_lines(owner, pool, text, kind, 1.0f, -1);
}

extern void Onscrn_DrawText(void *text, s32 x, s32 y, s32 alpha, s32 centred, s32 shadow, f32 scaleX, f32 scaleY);
void Camera_UpdateScreenMessages(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool) {
    f32 spacing;
    f32 fade;
    CCameraText *node;
    CCameraText *msg;
    CCameraText *waiting;

    spacing = 9.0f;
    if (pool != 0) {
        OnScreen_SetupTextRendering();
        OnScreen_LoadTextTileModeTwo();
        node = pool->freeMessages.head;
        if (node != 0) {
            node->y = (f32)g_hudReferenceViewportHeight * 0.81f;
            for (msg = node->next; msg != 0; msg = msg->next) {
                msg->y = node->y + spacing;
                node = msg;
            }
        }
        for (msg = pool->freeMessages.tail; msg != 0; msg = msg->prev) {
            Onscrn_DrawText(msg->text, (s32)msg->x, (s32)msg->y, msg->m_nAlpha, 1, 1, 1.0f, 1.0f);
        }
        for (msg = pool->freeMessages.tail; msg != 0; msg = msg->prev) {
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
                    for (waiting = pool->freeMessages.head; waiting != 0; waiting = waiting->next) {
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
        for (msg = pool->freeMessages.tail; msg != 0; msg = node) {
            node = msg->prev;
            if (msg->kind == 0) {
                List_RemoveIntrusive(&pool->freeMessages, msg);
                List_PrependIntrusive(&owner->activeMessages, msg);
            }
        }
    }
}

extern float g_cameraMessageResolutionScale;
extern float g_cameraMessageHorizontalOffsetScale;
extern float g_cameraMessageDropScale;
extern float g_cameraMessageVerticalOffsetScale;
extern float g_cameraMessageLargeTextScale;
extern float g_cameraMessageSmallTextScale;
extern float g_cameraMessageVerticalScale;
extern float g_cameraMessageDefaultScale;
extern float g_cameraMessageFadeInAngleScale;
extern float g_cameraMessageFullAlpha;
extern float g_cameraMessageFadeOutAngleScale;
extern float g_cameraMessageFadeOutPhase;
extern float g_cameraMessageFadeOutAmplitude;
extern float g_cameraMessageLineOffsetScale;
extern s32 g_frontendCurrentVideoModeIndex;
extern void Onscrn_DrawText(void *, s32, s32, s32, s32, s32, f32, f32);

/* Draws and advances the screen messages of one view, retiring finished ones. */
void Camera_DrawAndAdvanceMessages(Race *race, RacerViewport *racer) {
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
        Camera_UpdateScreenMessages((struct ScreenMessageOwner *)race, (struct ScreenMessagePool *)racer);
        return;
    }
    scale = g_cameraMessageResolutionScale;
    height = racer->viewportHeight;
    width = racer->viewportWidth;
    x = racer->viewportX;
    y = racer->viewportY;
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
    message = racer->activeMessages.tail;
    for (; message != 0; message = prev) {
        prev = message->prev;
        if (message->kind != 0) {
            OnScreen_SetupTextRendering();
            if (small || message->pad20 != 0) {
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
            List_RemoveIntrusive(&racer->activeMessages, message);
            List_PrependIntrusive(&race->freeMessages, message);
        }
        offsetY -= scaleY * g_cameraMessageLineOffsetScale / scale;
    }
}

/* 800C8504.CPP */
#if !(defined(VERSION_US_REV1))
const float k_CameraEncodedWordsBlock3[14] = {
    1.0f, 0.5f, 18.0f, 0.8f,
    0.6f, 0.5f, 0.8f, 0.4f,
    0.006159986f, 1.0f, 0.012319972f, 255.0f,
    0.33333334f, 9.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_CameraEncodedWordsBlock6[14] = {
    1.0f, 0.5f, 18.0f, 0.8f,
    0.6f, 0.5f, 0.8f, 0.4f,
    0.006159986f, 1.0f, 0.012319972f, 255.0f,
    0.33333334f, 9.0f,
};
#endif
