#include "ANIM/ANIMATION_FRAME.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "ENGINE/PARTICLE.H"




struct Shared_AnimInfo;

/* Draws one particle for a view: fades particles hidden behind geometry in or out, blends its colours towards the
 * descriptor's targets (greyscale for views that ask for it), picks the animation frame, builds its matrix (once per
 * frame for a shared camera, per view otherwise), selects the texture and render mode, works out its alpha from life,
 * fade-in, fade-out and distance from the view, and emits the colour and draw commands. */

extern Gfx *g_displayListCursor;
#include "COMMON/DISPLAY.H"
extern f32 g_frameElapsedTime;
extern s32 g_lightingBufferIndex;
extern char g_defaultProbeMotionSettings;
extern s32 g_playerWeaponClassMode;
extern GlobalsMenuSetOptionsSceneSelection g_gameplayCameraList;

extern s32 g_gameSettings;

extern char g_particleSpriteVertices;

void *Textload_RequestTextureVariation(s32 *, s32);
void Textload_ReadTextureAnimationInfo(void *, struct Shared_AnimInfo *);
#if defined(VERSION_US_REV1)
void Textload_LoadTextureFrameTiles(s32 *, void *, s32, s32, s32, s32, s32, s32, s32);
#else
void Textload_LoadTextureFrame(s32 *, void *, s32, s32, s32, s32, s32, s32, s32);
#endif
Shared_ParticleInstance *Gsky_FindScreenMessage(GameplayCamera *);
s32 Unicol_MoveActorWithCollision(Shared_ParticleInstance *, CVector3, void *);
void *Map_ReserveEntries(void *, s32);
void Geometry_SetCombineMode(u32);
s32 Geometry_SetModePreset(s32);
void Cache_UnlockResource(s32, void *);
s32 Graphu64_NextRandom(void);

static inline s32 Particle_IsSpriteOccluded(Shared_Particle *particle, GameplayCamera *view) {
    Shared_ParticleInstance *inst;
    s32 hit;

    inst = Gsky_FindScreenMessage(view);
    if (inst != 0 && view->bobSuppressed == 0) {
        Shared_ParticleInstance saved;
        saved = *inst;
        inst->pos = view->position;
        hit = Unicol_MoveActorWithCollision(inst, particle->inst.pos, &g_defaultProbeMotionSettings);
        *inst = saved;
    } else {
        Shared_ParticleInstance probe;
        probe = particle->inst;
        probe.pos = view->position;
        hit = Unicol_MoveActorWithCollision(&probe, particle->inst.pos, &g_defaultProbeMotionSettings);
    }
    return hit;
}

static inline s32 Particle_GetSpriteViewMode(Shared_Particle *particle) {
    s32 mode = 0;

    if (particle->desc->flags & 0x2000000) {
        if (particle->flags & 2) {
            mode = 2;
        } else if (g_particleSpriteViewMode == 2) {
            mode = 1;
        }
    }
    return mode;
}

static inline s32 Particle_GetNonnegativeScaledSpriteSize(f32 value, f32 div) {
    return (value < 0.0f) ? 0 : (s32)((s32)value / div);
}

static inline f32 lesser(f32 a, f32 b) { return a > b ? b : a; }
static inline f32 greater(f32 a, f32 b) { return a < b ? b : a; }

void Particle_DrawSprite(Shared_Particle *particle, GameplayCamera *view) {
    struct Shared_AnimInfo info;
    u8 env[3];
    u8 prim[3];
    CVector3 viewPos;
    void *model;
    struct Shared_ParticleDesc *desc;
    void *mtx;
    f32 fade;
    f32 ratio;
    f32 dist;
    s32 hit;
    s32 alpha;
    s8 duration;
    s32 mode;
    s32 frame;
    s32 time;
    s32 textured;
    s32 shiftS;
    s32 shiftT;
    s32 sum;
    s16 gray;
    u8 *envTo;
    u8 *primTo;
    u8 *envFrom;
    u8 *primFrom;

    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (particle->time < 0.0f) {
        return;
    }
    model = Textload_RequestTextureVariation(&particle->model, -1);
    if (model == 0) {
        return;
    }
    desc = particle->desc;
    if ((desc->flags & 0x80000) && desc->playback == 1) {
        if (particle->inst.type != 96) {
            particle->time = 0.0f;
        }
        hit = Particle_IsSpriteOccluded(particle, view);
        if (!hit) {
            fade = particle->opacity + g_frameElapsedTime * 128.0f;
            alpha = (fade > 255.0f) ? 255 : (s32)fade;
        } else {
            fade = particle->opacity - g_frameElapsedTime * 128.0f;
            alpha = (fade < 0.0f) ? 0 : (s32)fade;
        }
        particle->opacity = alpha;
        if (alpha == 0.0f) {
            Cache_UnlockResource(0, model);
            return;
        }
    }

    particle->flags |= 8 << view->index;
    particle->alpha = 255.0f;
    ratio = particle->time / particle->life > 1.0f ? 1.0f : particle->time / particle->life;
    primFrom = particle->prim;
    envFrom = particle->env;
    primTo = desc->colors->prim;
    envTo = desc->colors->env;
    env[0] = (u32)((((envTo[0] - envFrom[0]) * ratio + envFrom[0]) > 255.0f ? 255.0f : ((envTo[0] - envFrom[0]) * ratio + envFrom[0])) < 0.0f ? 0.0f : (((envTo[0] - envFrom[0]) * ratio + envFrom[0]) > 255.0f ? 255.0f : ((envTo[0] - envFrom[0]) * ratio + envFrom[0])));
    env[1] = (u32)((((envTo[1] - envFrom[1]) * ratio + envFrom[1]) > 255.0f ? 255.0f : ((envTo[1] - envFrom[1]) * ratio + envFrom[1])) < 0.0f ? 0.0f : (((envTo[1] - envFrom[1]) * ratio + envFrom[1]) > 255.0f ? 255.0f : ((envTo[1] - envFrom[1]) * ratio + envFrom[1])));
    env[2] = (u32)((((envTo[2] - envFrom[2]) * ratio + envFrom[2]) > 255.0f ? 255.0f : ((envTo[2] - envFrom[2]) * ratio + envFrom[2])) < 0.0f ? 0.0f : (((envTo[2] - envFrom[2]) * ratio + envFrom[2]) > 255.0f ? 255.0f : ((envTo[2] - envFrom[2]) * ratio + envFrom[2])));
    prim[0] = (u32)((((primTo[0] - primFrom[0]) * ratio + primFrom[0]) > 255.0f ? 255.0f : ((primTo[0] - primFrom[0]) * ratio + primFrom[0])) < 0.0f ? 0.0f : (((primTo[0] - primFrom[0]) * ratio + primFrom[0]) > 255.0f ? 255.0f : ((primTo[0] - primFrom[0]) * ratio + primFrom[0])));
    prim[1] = (u32)((((primTo[1] - primFrom[1]) * ratio + primFrom[1]) > 255.0f ? 255.0f : ((primTo[1] - primFrom[1]) * ratio + primFrom[1])) < 0.0f ? 0.0f : (((primTo[1] - primFrom[1]) * ratio + primFrom[1]) > 255.0f ? 255.0f : ((primTo[1] - primFrom[1]) * ratio + primFrom[1])));
    prim[2] = (u32)((((primTo[2] - primFrom[2]) * ratio + primFrom[2]) > 255.0f ? 255.0f : ((primTo[2] - primFrom[2]) * ratio + primFrom[2])) < 0.0f ? 0.0f : (((primTo[2] - primFrom[2]) * ratio + primFrom[2]) > 255.0f ? 255.0f : ((primTo[2] - primFrom[2]) * ratio + primFrom[2])));

    if (view->monochrome != 0) {
        gray = env[0] + env[1] + env[2];
        gray /= 12;
        env[0] = gray * 2;
        env[1] = 0;
        env[2] = 0;
        gray = prim[0] + prim[1] + prim[2];
        gray /= 12;
        prim[0] = gray * 2;
        prim[1] = gray * 3;
        prim[2] = 0;
    }

    mode = Particle_GetSpriteViewMode(particle);
    Textload_ReadTextureAnimationInfo(model, &info);
    frame = particle->frame;
    time = particle->time;
    switch (desc->playback) {
        case 0:
            if (frame >= info.count - 1) {
                time = particle->life;
                frame = info.count - 1;
                particle->time = time;
            }
            break;
        case 1:
            if (frame >= info.count) {
                frame = info.count - 1;
            }
            break;
        case 2:
            frame %= info.count;
            break;
        case 3:
            if (info.count * 2 - 2 > 0) {
                frame %= info.count * 2 - 2;
            } else {
                frame = 0;
            }
            if (frame >= info.count) {
                frame = (info.count * 2 - 2) - frame;
            }
            break;
        case 4:
            frame = Graphu64_NextRandom() % info.count;
            break;
        case 5:
            if (particle->fixedSpriteFrame == -1) {
                particle->fixedSpriteFrame = Graphu64_NextRandom() % info.count;
            }
            frame = particle->fixedSpriteFrame;
            break;
    }

    if (!(particle->flags & 0x100000)) {
        if (g_playerWeaponClassMode == 1) {
            GameplayCamera *camera = g_gameplayCameraList.camera;
            CVector3 local;
            f32 depth;
            Graphu64_TransformPoint(camera->worldToView, &particle->inst.pos, &local);
            depth = local.z;
            if (depth < 0.0f) {
                depth = -depth;
            }
            Particle_BuildMatrix(particle, &particle->mtx[g_lightingBufferIndex], camera, depth);
        } else {
            Particle_BuildMatrix(particle, &particle->mtx[g_lightingBufferIndex], 0, 0.0f);
        }
        particle->spriteFrame = frame;
        particle->flags |= 0x100000;
    }
    Graphu64_TransformPoint(view->worldToView, &particle->inst.pos, &viewPos);
    dist = viewPos.z;
    if (dist < 0.0f) {
        dist = -dist;
    }
    if (g_playerWeaponClassMode == 1) {
        gSPMatrix(g_displayListCursor++, &particle->mtx[g_lightingBufferIndex], G_MTX_LOAD);
    } else {
        mtx = Map_ReserveEntries(&g_actorMatrixPool, 1);
        if (mtx == 0) {
            Cache_UnlockResource(0, model);
            return;
        }
        Particle_BuildMatrix(particle, mtx, view, dist);
        gSPMatrix(g_displayListCursor++, (u32)mtx, G_MTX_LOAD);
    }

    textured = particle->flags & 0x800000;
    shiftS = 1 << (((desc->flags & 0x100) ? 7 : 6) + info.frame->shiftS);
    shiftT = 1 << (((desc->flags & 0x200) ? 7 : 6) + info.frame->shiftT);
#if defined(VERSION_US_REV1)
    Textload_LoadTextureFrameTiles(&particle->model, model, frame, 0, shiftS, shiftT, 1, 1, 0);
#else
    Textload_LoadTextureFrame(&particle->model, model, frame, 0, shiftS, shiftT, 1, 1, 0);
#endif
    switch (info.frame->kind) {
        case 0:
        case 1:
            Geometry_SetCombineMode(24);
            break;
        case 3:
            Geometry_SetCombineMode(29);
            break;
    }
    if (textured) {
        Geometry_SetModePreset(15);
        {
            gSPTextureL(g_displayListCursor++, shiftS, shiftT, 0, 0xFF, 0, G_ON);
        }
    } else if ((desc->flags & 0x400) && desc->fade->modeSelector != 4) {
        Geometry_SetModePreset(15);
    } else if (desc->flags & 0x4000) {
        Geometry_SetModePreset(!(g_gameSettings & 0x200) ? 13 : 17);
    } else {
        Geometry_SetModePreset((g_gameSettings & 0x200) ? 18 : 19);
    }

    alpha = 0xFF;
    if ((desc->flags & 1) && particle->life > 0) {
        alpha = (particle->life - time) * 255.0f / particle->life;
    }
    duration = desc->fade->fadeIn;
    if (duration != -1 && time < duration) {
        alpha = alpha * (time + 1.0f) / (duration + 1.0f);
    }
    duration = desc->fade->fadeOut;
    if (duration != -1) {
        f32 left = particle->life - time;
        if ((left < 0.0f ? 0.0f : left) < duration) {
            alpha = Particle_GetNonnegativeScaledSpriteSize(alpha * (particle->life - time), duration + 1.0f);
        }
    }
    if (view->farPlane < -0.0001f || view->farPlane > 0.0001f) {
        f32 range = view->farPlane;
        f32 half;
        f32 delta;
        switch (desc->fade->rangeMode) {
            case 2:
                alpha = alpha * (((range - dist) * 10.0f / range) > 1.0f ? 1.0f : ((range - dist) * 10.0f / range));
                break;
            case 0:
                alpha = alpha * (((range - dist) * 5.0f / range) > 1.0f ? 1.0f : ((range - dist) * 5.0f / range));
                break;
            case 1:
                half = range * 0.5f;
                delta = half - dist;
                alpha = alpha * (delta < 0.0f ? half + delta : half - delta) / half;
                break;
        }
    }

    if (info.frame->kind == 3) {
        switch (mode) {
            case 0:
            default:
                gDPSetEnvColor(g_displayListCursor++, env[0], env[1], env[2], 255);
                break;
            case 2:
                gDPSetEnvColor(g_displayListCursor++, env[0], env[0], env[2], 255);
                break;
            case 1:
                gDPSetEnvColor(g_displayListCursor++, env[1], env[0], env[2], 255);
                break;
        }
    }
    alpha = (alpha > 255 ? 255 : alpha) < 0 ? 0 : (alpha > 255 ? 255 : alpha);
    gSPVertex(g_displayListCursor++, &g_particleSpriteVertices, 4, 0);
    if (textured) {
        gSPTextureL(g_displayListCursor++, shiftS, shiftT, 0, 0xFF, 0, G_ON);
        }
    particle->alpha = (alpha * particle->opacity) >> 8;
    switch (mode) {
        case 0:
        default:
            gDPSetPrimColor(g_displayListCursor++, 0, 0, prim[0], prim[1], prim[2], (u32)particle->alpha);
            break;
        case 2:
            gDPSetPrimColor(g_displayListCursor++, 0, 0, prim[0], prim[0], prim[2], (u32)particle->alpha);
            break;
        case 1:
            gDPSetPrimColor(g_displayListCursor++, 0, 0, prim[1], prim[0], prim[2], (u32)particle->alpha);
            break;
    }
    gSP2Triangles(g_displayListCursor++, 0, 1, 2, 0, 2, 3, 0, 0);
    Cache_UnlockResource(0, model);
}
