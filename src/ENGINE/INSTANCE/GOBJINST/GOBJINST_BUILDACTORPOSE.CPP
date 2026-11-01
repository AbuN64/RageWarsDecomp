#include "COMMON/GAMEPLAY_CAMERA.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "include_asm.h"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/WORLD.H"
#include "COMMON/UNSIGNED_QUOTIENT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ACTORRESOURCEHEADER.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"

/* Builds and packs the animated part matrices of an actor, then updates the
 * frame timing totals. */
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ENGINE/INSTANCE/GOBJINST.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Complete nonpadded pose records recovered from the pinned shared pose header. */
typedef struct Shared_PoseJointRef Shared_PoseJointRef;
struct Shared_PoseJointRef {
    s16 pos;
    s16 rot;
};

typedef struct Shared_PoseDefaultFrame Shared_PoseDefaultFrame;
struct Shared_PoseDefaultFrame {
    CVector3 pos;
    s16 rot[4];
};

typedef struct Shared_PoseTrack Shared_PoseTrack;
struct Shared_PoseTrack {
    Shared_PoseJointRef *joints;
    Shared_PoseDefaultFrame *frames;
    void *posTable;
    void *rotTable;
    s32 rotFrame0;
    s32 rotFrame1;
    s32 posFrame0;
    s32 posFrame1;
    f32 blend;
};

typedef struct Shared_PoseFlags Shared_PoseFlags;
struct Shared_PoseFlags {
    s32 frame;
    s32 blend;
    s32 mode;
};
typedef struct Shared_FrameProfile Shared_FrameProfile;
struct Shared_FrameProfile {
    u64 start;
    u32 unknown08[2];
    s32 frame;
    s32 prevCount;
    s32 count;
    u32 reservedWord;
    f32 prev;
    f32 cur;
    f32 avg;
};

typedef f32 PoseMatrix[4][4];
typedef void (*PoseCallback)(PoseMatrix, Shared_PoseContext *);

extern char g_actorRotationBlendAndResourceTuning;


extern s32 g_gameFrameCounter;
extern s32 g_lightingBufferIndex;
extern Shared_FrameProfile g_actorPoseTiming;





extern s32 g_gameSettings;

extern s32 Cinema_IsSequenceInWindow(void);
extern void Gobjinst_ApplyImpactBoneTwist(Shared_PoseActor *, Shared_PosePart *, PoseMatrix, CVector3, CVector3, s32);
extern void Gobjinst_ApplyTimedMatrixWobble(Shared_PoseActor *, s32, PoseMatrix);
extern f32 Gobjinst_GetActorHeight(Shared_PoseActor *);
extern void Gastate_SwitchRequestedAnimation(Shared_AnimState *, s32, s32, s32, s32, s32);
extern void Gastate_PrepareAnimationFrames();
extern void Gastate_ReleaseAnimationResource(Shared_AnimState *);
extern s32 Gastate_IsAnimationResourceRetained(Shared_AnimState *);
extern void Ghot_DispatchAttachmentEffects(u8 *, s32, PoseMatrix *, Shared_PoseActor *, void *);
extern void Graphu64_MultiplyAffineMatrices(PoseMatrix, PoseMatrix, PoseMatrix);
extern void Graphu64_ConvertMatrixToFloat(PoseMatrix, u8 *);
extern void Graphu64_InterpolateQuaternionArc(CQuatern *, f32, CQuatern *, CQuatern *);
extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);
extern void Graphu64_BuildAxisAngleMatrix(PoseMatrix, f32, f32, f32, f32);
extern void CopyMatrix(PoseMatrix, PoseMatrix);
extern void TranslateMatrix(PoseMatrix, f32, f32, f32);
extern void ScaleMatrixLocal(PoseMatrix, f32, f32, f32);
extern f32 Graphu64_GetTrianglePlaneHeight(StateFlags *, f32, f32);
extern s32 Map_ReserveEntries(void *, s32);
extern void Scene_SampleWorldLighting(void *, CVector3 *, u8 *);
extern void Fx_AddActorRibbonSamples(RibbonWorld *, Shared_PoseActor *, PoseMatrix *);
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"

static inline CVector3 randVec(void) {
    CVector3 v;

    v.x = Graphu64_NextRandom() % 100;
    v.y = Graphu64_NextRandom() % 100;
    v.z = Graphu64_NextRandom() % 100;
    return v;
}

static inline void twistPart(Shared_PosePart *part, PoseMatrix cur, s32 n, s32 i) {
    CVector3 turn;
    CVector3 axis;
    PoseMatrix rotm;
    PoseMatrix inv;
    f32 angle;

    if (i != 0) {
        turn.x = cur[3][0];
        turn.y = cur[3][1];
        turn.z = cur[3][2];
        axis = part->twistAxis;
        angle = g_boneTwistImpulseCurve[25 - part->twistStep] * 0.5f;
        angle *= 0.3f;
        angle *= (n == 5 ? -2.0f : (f32)n);
        CopyMatrix(inv, cur);
        Graphu64_ScaleVector(&turn, &turn, -1.0f);
        TranslateMatrix(inv, turn.x, turn.y, turn.z);
        Graphu64_BuildAxisAngleMatrix(rotm, angle, axis.x, axis.y, axis.z);
        Graphu64_MultiplyAffineMatrices(cur, inv, rotm);
        Graphu64_ScaleVector(&turn, &turn, -1.0f);
        TranslateMatrix(cur, turn.x, turn.y, turn.z);
        if (part->twistJoints[0] == i) {
            part->twistStep--;
        }
    }
}

static inline void trackPos(Shared_PoseTrack *t, s32 i, CVector3 *out) {
    if (t->joints[i].pos == -1) {
        *out = t->frames[i].pos;
    } else {
        f32 *data = SetN64_GetPackSection(t->posTable, t->joints[i].pos);
        f32 *a = &data[t->posFrame0];
        f32 *b = &data[t->posFrame1];

        out->x = a[0] + t->blend * (b[0] - a[0]);
        out->y = a[1] + t->blend * (b[1] - a[1]);
        out->z = a[2] + t->blend * (b[2] - a[2]);
    }
}

static inline void trackRot(Shared_PoseTrack *t, s32 i, CQuatern *out, s32 slerp) {
    Shared_PoseDefaultFrame *frame;
    f32 z;
    if (slerp) {
        if (t->joints[i].rot == -1) {
            frame = t->frames;
            frame += i;
            out->x = frame->rot[0] * (1.0f / 32767.0f);
            out->y = frame->rot[1] * (1.0f / 32767.0f);
            z = frame->rot[2] * (1.0f / 32767.0f);
            goto default_frame;
        } else {
            f32 *data = SetN64_GetPackSection(t->rotTable, t->joints[i].rot);

            Graphu64_InterpolateQuaternionArc(out, t->blend, (CQuatern *)&data[t->rotFrame0], (CQuatern *)&data[t->rotFrame1]);
        }
    } else if (t->joints[i].rot == -1) {
        frame = t->frames;
            frame += i;

        out->x = frame->rot[0] * (1.0f / 32767.0f);
        out->y = frame->rot[1] * (1.0f / 32767.0f);
        z = frame->rot[2] * (1.0f / 32767.0f);
    default_frame:
        out->z = z;
        out->w = frame->rot[3] * (1.0f / 32767.0f);
    } else {
        f32 *data = SetN64_GetPackSection(t->rotTable, t->joints[i].rot);
        f32 *a = &data[t->rotFrame0];
        f32 *b = &data[t->rotFrame1];

        out->x = a[0] + t->blend * (b[0] - a[0]);
        out->y = a[1] + t->blend * (b[1] - a[1]);
        out->z = a[2] + t->blend * (b[2] - a[2]);
        out->w = a[3] + t->blend * (b[3] - a[3]);
    }
}

static inline void quatToMtx(PoseMatrix m, CQuatern *q, CVector3 *t) {
    f32 xx = q->x * q->x;
    f32 yy = q->y * q->y;
    f32 zz = q->z * q->z;
    f32 ww = q->w * q->w;
    f32 xy = 2.0f * q->x * q->y;
    f32 wz = 2.0f * q->w * q->z;
    f32 xz = 2.0f * q->x * q->z;
    f32 wy = 2.0f * q->w * q->y;
    f32 yz = 2.0f * q->y * q->z;
    f32 wx = 2.0f * q->w * q->x;

    m[0][0] = ww + xx - yy - zz;
    m[0][1] = xy + wz;
    m[0][2] = xz - wy;
    m[0][3] = 0.0f;
    m[1][0] = xy - wz;
    m[1][1] = ww - xx + yy - zz;
    m[1][2] = yz + wx;
    m[1][3] = 0.0f;
    m[2][0] = xz + wy;
    m[2][1] = yz - wx;
    m[2][2] = ww - xx - yy + zz;
    m[2][3] = 0.0f;
    m[3][0] = t->x;
    m[3][1] = t->y;
    m[3][2] = t->z;
    m[3][3] = 1.0f;
}

static inline void packMtx(u32 *out, PoseMatrix m) {
    u32 *hi = out;
    u32 *lo = out + 8;
    u32 e1;
    u32 e2;

        e1 = (u32)m[0][0];
        e2 = (u32)m[0][1];
        *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
        *lo++ = (e1 << 16) | (e2 & 0xFFFF);
        e1 = (u32)m[0][2];
        e2 = 0;
        *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
        *lo++ = (e1 << 16) | (e2 & 0xFFFF);
        e1 = (u32)m[1][0];
        e2 = (u32)m[1][1];
        *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
        *lo++ = (e1 << 16) | (e2 & 0xFFFF);
        e1 = (u32)m[1][2];
        e2 = 0;
        *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
        *lo++ = (e1 << 16) | (e2 & 0xFFFF);
        e1 = (u32)m[2][0];
        e2 = (u32)m[2][1];
        *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
        *lo++ = (e1 << 16) | (e2 & 0xFFFF);
        e1 = (u32)m[2][2];
        e2 = 0;
        *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
        *lo++ = (e1 << 16) | (e2 & 0xFFFF);
        e1 = (u32)m[3][0];
        e2 = (u32)m[3][1];
        *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
        *lo++ = (e1 << 16) | (e2 & 0xFFFF);
        e1 = (u32)m[3][2];
        e2 = 65536;
        *hi++ = (e1 & 0xFFFF0000) | (e2 >> 16);
        *lo++ = (e1 << 16) | (e2 & 0xFFFF);

}

s32 Gobjinst_BuildActorPose(Shared_PoseActor *actor, void *modelPack, s32 model) {
    PoseMatrix mtx[129];
    CVector3 pos;
    Shared_PoseContext ctx;
    Shared_PoseTrack tracks[2];
    Shared_PoseFlags f;
    PoseMatrix m;
    CVector3 trans;
    CVector3 posA;
    CVector3 posB;
    CQuatern rot;
    CQuatern rotA;
    CQuatern rotB;
    CVector3 scale;
    Shared_PoseWorld *world;
    s32 *mem;
    Shared_AnimState *animA;
    Shared_AnimState *animB;
    s32 id0;
    s32 id1;
    s32 id2;
    s32 id3;
    s32 id4;
    s32 count;
    s32 kind;
    PoseMatrix *parent;
    u32 *out;
    s32 scaled;
    s32 ret;
    s32 skip;
    s32 isRoot;
    s32 isKind9;
    s32 i;
    PoseMatrix *cur;
    s32 flags;
    u32 dt;

    world = 0;
    ctx.parts = SetN64_GetPackSection(modelPack, 5);
    count = ctx.parts->count;
    actor->handle = Map_ReserveEntries(&g_actorMatrixPool, count);
    if (actor->handle == 0) {
        return 0;
    }
    ret = 0;
    isRoot = actor->flags & 1;
    isKind9 = actor->model->kind == 9;
    mem = Cache_RequestResource(0, actor->animationResourceId, actor->animationResourceId, ((actor->animationResourceUnits * 4) + 15) & ~7, 4, 0, 0, &g_actorRotationBlendAndResourceTuning + 4, 0);
    skip = ret;
    if (mem != 0) {
        animA = &actor->animA;
        animB = &actor->animB;
        Gastate_SwitchRequestedAnimation(animA, *mem, actor->animationResourceId, 0, 0, 0);
        if (Gastate_IsAnimationResourceRetained(animA)) {
            if (actor->flags & 0x400) {
                Gastate_SwitchRequestedAnimation(animB, *mem, actor->animationResourceId, 0, 0, 0);
                f.blend = Gastate_IsAnimationResourceRetained(animB);
            } else {
                f.blend = 0;
            }
            ctx.actor = actor;
            ctx.handle = actor->handle;
            ctx.mtx = &mtx[1];
            ctx.model = model;
            ctx.modelPack = modelPack;
            ctx.animA = animA;
            ctx.animB = animB;
            f.frame = (!isRoot || isKind9) && !skip;
            Gastate_PrepareAnimationFrames(&actor->animA, &tracks[0], f.frame);
            Gastate_PrepareAnimationFrames(&actor->animB, &tracks[1]);
            kind = actor->model->kind;
            scaled = 0;
            scale.x = 1.0f;
            scale.y = 1.0f;
            scale.z = 1.0f;
            flags = actor->flags;
            if (flags & 0x300000) {
                if (flags & 0x100000) {
                    world = actor->world;
                    if (world->scale != 1.0f) {
                        scaled = 1;
                        if (world->scale > 1.0f) {
                            scale.x = world->scale;
                            scale.y = world->scale * 1.5f;
                        } else {
                            scale.x = world->scale;
                            scale.y = world->scale;
                            scale.z = world->scale;
                        }
                    }
                    f.frame = 1;
                } else {
                    f.frame = 0;
                }
                if (Cinema_IsSequenceInWindow()) {
                    f.frame = 0;
                }
            }
            if (!Cinema_IsSequenceInWindow() && ((animA->activeFlag == 0 && animB->activeFlag == 0) || kind == 1)) {
                f.mode = 0;
            } else {
                f.mode = 1;
            }
            if (!(actor->flags & 0x200000) && (kind == 1 || kind == 11)) {
                if (g_gameSettings & 0x100) {
                    id0 = 195;
                    id1 = 199;
                    id2 = 194;
                    id3 = 198;
                } else {
                    id0 = -1;
                    id1 = -1;
                    id2 = -1;
                    id3 = -1;
                }
                id4 = -1;
                if (g_gameSettings & 0x20) {
                    id4 = 1;
                }
                if (g_gameSettings & 0x80) {
                    scaled = 1;
                    Graphu64_ScaleVector(&scale, &scale, 0.5f);
                }
            } else {
                id0 = -1;
                id1 = -1;
                id2 = -1;
                id3 = -1;
                id4 = -1;
            }
            mtx[0][0][0] = actor->mtx.right.x * 65536.0f;
            mtx[0][1][0] = actor->mtx.up.x * 65536.0f;
            mtx[0][2][0] = actor->mtx.forward.x * 65536.0f;
            mtx[0][3][0] = actor->mtx.m30 * 65536.0f;
            mtx[0][0][1] = actor->mtx.right.y * 65536.0f;
            mtx[0][1][1] = actor->mtx.up.y * 65536.0f;
            mtx[0][2][1] = actor->mtx.forward.y * 65536.0f;
            mtx[0][3][1] = actor->mtx.m31 * 65536.0f;
            mtx[0][0][2] = actor->mtx.right.z * 65536.0f;
            mtx[0][1][2] = actor->mtx.up.z * 65536.0f;
            mtx[0][2][2] = actor->mtx.forward.z * 65536.0f;
            mtx[0][3][2] = actor->mtx.m32 * 65536.0f;
            mtx[0][0][3] = mtx[0][1][3] = mtx[0][2][3] = 0.0f;
            mtx[0][3][3] = 65536.0f;
            out = (u32 *)actor->handle;
            i = 0;
            g_actorPoseTiming.start = osGetCount();
            cur = &mtx[1];
            for (; i < count; cur++, out += 16, i++) {
                Shared_PosePartEntry *entry;
                s32 partFlags;

                ctx.index = i;
                entry = (Shared_PosePartEntry *)&ctx.parts->data[i * ctx.parts->stride];
                ctx.part = entry;
                parent = &mtx[entry->u.b.parent + 1];
                partFlags = entry->u.b.flags;
                trackPos(&tracks[0], i, &posA);
                trackRot(&tracks[0], i, &rotA, f.mode);
                if (f.blend) {
                    trackPos(&tracks[1], i, &posB);
                    trackRot(&tracks[1], i, &rotB, f.mode);
                    {
                        f32 t = actor->blendFactor;

                        trans.x = posB.x + t * (posA.x - posB.x);
                        trans.y = posB.y + t * (posA.y - posB.y);
                        trans.z = posB.z + t * (posA.z - posB.z);
                    }
                    Graphu64_InterpolateQuaternionArc(&rot, actor->blendFactor, &rotB, &rotA);
                } else {
                    trans = posA;
                    rot = rotA;
                }
                if (f.frame) {
                    f.frame = 0;
                    trans.x = trans.y = 0.0f;
                }
                quatToMtx(m, &rot, &trans);
                if (actor->callback != 0) {
                    ((PoseCallback)actor->callback)(m, &ctx);
                }
                Graphu64_MultiplyAffineMatrices(*cur, m, *parent);
                if (actor->part.twistStep) {
                    s32 n = 0;
                    if (actor->part.twistJoints[0] == i) {
                        n = 4;
                    }
                    if (actor->part.twistJoints[1] == i) {
                        n = 3;
                    }
                    if (actor->part.twistJoints[2] == i) {
                        n = 2;
                    }
                    if (actor->part.twistJoints[3] == i) {
                        n = 1;
                    }
                    if (n != 0 && actor->callback != 0) {
                        twistPart(&actor->part, *cur, n, i);
                    }
                } else if (i != 0 && world != 0 && world->impactTwistPending != 0 && ctx.part != 0 &&
                           ctx.part->u.f.kind == 1 && ctx.part->u.f.sway == 0) {
                    if ((actor->flags & 0x1000000) && actor->boneMatrixData != 0) {
                        PoseMatrix bone;
                        CVector3 r = randVec();

                        Graphu64_ConvertMatrixToFloat(bone, actor->boneMatrixData + i * 64);
                        Gobjinst_ApplyImpactBoneTwist(actor, &actor->part, bone, actor->pos, r, i);
                    }
                    world->impactTwistPending = 0;
                }
                if (actor->flags & 0x800000) {
                    Gobjinst_ApplyTimedMatrixWobble(actor, partFlags, *cur);
                }
                if (partFlags == id0) {
                    id0 = -1;
                    ScaleMatrixLocal(*cur, 2.0f, 2.0f, 2.0f);
                } else if (partFlags == id1) {
                    id1 = -1;
                    ScaleMatrixLocal(*cur, 2.0f, 2.0f, 2.0f);
                } else if (partFlags == id2) {
                    id2 = -1;
                    ScaleMatrixLocal(*cur, 2.0f, 2.0f, 2.0f);
                } else if (partFlags == id3) {
                    id3 = -1;
                    ScaleMatrixLocal(*cur, 2.0f, 2.0f, 2.0f);
                } else if (partFlags == id4) {
                    id4 = -1;
                    ScaleMatrixLocal(*cur, 3.0f, 3.0f, 3.0f);
                }
                if (scaled) {
                    CopyMatrix(m, *cur);
                    ScaleMatrixLocal(m, scale.x, scale.y, scale.z);
                    packMtx(out, m);
                } else {
                    packMtx(out, *cur);
                }
            }
            dt = osGetCount() - g_actorPoseTiming.start;
            if (g_gameFrameCounter != g_actorPoseTiming.frame) {
                f32 last = g_actorPoseTiming.cur;
                s32 n = g_actorPoseTiming.count;

                g_actorPoseTiming.frame = g_gameFrameCounter;
                g_actorPoseTiming.cur = 0.0f;
                g_actorPoseTiming.count = 0;
                g_actorPoseTiming.prev = last;
                g_actorPoseTiming.prevCount = n;
                g_actorPoseTiming.avg = g_actorPoseTiming.avg * 0.97f + last * 0.03f;
            }
            g_actorPoseTiming.cur += (f32)(((u64)dt * 64) / 3000);
            g_actorPoseTiming.count++;
            if (f.blend) {
                Gastate_ReleaseAnimationResource(animB);
            }
            Gastate_ReleaseAnimationResource(animA);
            switch (kind) {
                case 4:
                    actor->verticalOffset = actor->model->verticalOffset;
                    break;
                case 1:
                case 11: {
                    f32 h = Gobjinst_GetActorHeight(actor);

                    actor->verticalOffset = mtx[1][3][1] * (1.0f / 65536.0f) - actor->pos.y - h * 0.5f;
                    if (actor->verticalOffset < 0.0f) {
                        actor->verticalOffset = 0.0f;
                    }
                    if ((actor->flags & 0x20000000) && actor->surface != 0 && (actor->surface->flags & 0x40)) {
                        f32 ground = Graphu64_GetTrianglePlaneHeight(actor->surface, actor->pos.x, actor->pos.z);
                        f32 d = actor->pos.y + actor->verticalOffset + h;

                        d -= ground;

                        if (d > 0.0f) {
                            mtx[1][3][1] -= d * 65536.0f;
                            actor->verticalOffset -= d;
                        }
                    }
                    break;
                }
                default:
                    actor->verticalOffset = 0.0f;
                    break;
            }
            if (actor->attachmentEffectsFlag != 0) {
                s32 bit = 1 << actor->partBitIndex;

                if (actor->part.effectPartMask & bit) {
                    Shared_PosePartTable *table = SetN64_GetPackSection(modelPack, 3);
                    s32 n = table->count;

                    if (n != 0) {
                        u8 *data = table->data;

                        Ghot_DispatchAttachmentEffects(data, n, &mtx[1], actor, SetN64_GetPackSection(modelPack, 5));
                    }
                }
            }
            if (actor->effectReferenceCount) {
                Fx_AddActorRibbonSamples(&g_actorParticleScene, actor, &mtx[1]);
            }
            if (!(actor->flags & 8)) {
                pos = actor->pos;
                pos.y += actor->verticalOffset;
                pos.y += Gobjinst_GetActorHeight(actor) * 0.5f;
                Scene_SampleWorldLighting(&g_world, &pos, actor->sampledLighting[g_lightingBufferIndex]);
            }
            ret = 1;
            actor->flags |= 0x200;
        }
        Cache_UnlockResource(0, mem);
    }
    if (!ret) {
        actor->handle = 0;
    }
    return ret;
}

#include "COMMON/VIEWFLAGS.H"
#include <PR/gbi.h>
extern char s_actorModelVariantResourceTag[];
extern Gfx *g_displayListCursor;
typedef struct SceneModelRef {
    u8 pad0[0x1C];
    u32 viewMask; /* 0x1C */
} SceneModelRef;
typedef struct SceneObject SceneObject;
typedef struct DrawContext {
    s32 visible;
    s32 hasSecond;
    struct RacerViewport *camera;
    void *first;
    void *second;
    f32 *offset;
    s32 pad;
} DrawContext;
struct SceneObject {
    u8 pad0;
    s8 firstKey; /* 1 */
    s8 secondKey; /* 2 */
    u8 pad3[0x11];
    SceneModelRef *model; /* 0x14 */
    u8 pad18[0x5C];
    f32 transform[16]; /* 0x74 */
    u8 padB4[0xC];
    Gfx *cached; /* 0xC0 */
    s32 resource; /* 0xC4 */
    u8 padC8[8];
    s32 resourceFlags; /* 0xD0 */
    u8 padD4[0x14];
    Box bounds; /* 0xE8 */
    u32 flags; /* 0x100 */
    u8 pad104[0x6C];
    s32 behaviorFlags; /* 0x170 */
    u8 pad174[0x108];
    void (*draw)(SceneObject *, void *, DrawContext *); /* 0x27C */
    u8 pad280[0xC];
    void (*update)(SceneObject *, void *); /* 0x28C */
};
extern void *Gobjinst_RequestAnimatedModelVariant(SceneObject *, s32);
extern s32 Visdata_TestBoxAgainstFrustum(void *, void *);
extern void TextLoad_ResetTextureCache(void);
/* Draws one scene object: loads its model, culls its bounding box against the camera's clip box and plane test,
 * then records the object's draw callback into a display list cached on the object (a branch placeholder is
 * patched at the end) or replays the cached list.
 * Byte-exact for us-rev1. */
void Gobjinst_DrawVisibleCachedActor(SceneObject *object, struct RacerViewport *camera) {
    void **mem;
    void *model;
    void *first;
    void *second;
    s32 visible;
    s32 second_needed;
    f32 offset[3];
    s32 spare[6];
    DrawContext context;

    if (!(object->flags & 0x40000) || object->draw == 0) {
        return;
    }
    if (!(object->flags & 0x2000)) {
        object->flags &= ~0x200;
        return;
    }
    mem = Cache_RequestResource(0, object->resource, object->resource, object->resourceFlags, 0, 0, 0, s_actorModelVariantResourceTag, 1);
    if (mem == 0) {
        return;
    }
    model = SetN64_GetPackSection(*mem, 0);
    if (g_gameSession.clockPaused != 0) {
        object->update(object, &object->behaviorFlags);
        Graphu64_TransformBoundingBox(object->transform, (s32)model, &object->bounds);
    }
    visible = 1;
    if (!(object->flags & 0x200000)) {
        second_needed = visible = 0;
        if (object->model == 0 || (camera->visibilityFlags & object->model->viewMask)) {
            if (camera->clipBounds[1].x > object->bounds.min.x && camera->clipBounds[0].x < object->bounds.max.x &&
                camera->clipBounds[1].z > object->bounds.min.z && camera->clipBounds[0].z < object->bounds.max.z &&
                camera->clipBounds[1].y > object->bounds.min.y && camera->clipBounds[0].y < object->bounds.max.y &&
                Visdata_TestBoxAgainstFrustum((char *)&((GameplayCamera *)camera)->clipPlanes, &object->bounds) != 0) {
                visible = 1;
                if (object->model != 0) {
                    goto sync;
                }
            }
        }
    } else {
    sync:
        second_needed = visible;
    }
    if (visible == 0 && second_needed == 0) {
        Cache_UnlockResource(0, mem);
        return;
    }
    Geometry_InvalidateMaterialKeys();
    TextLoad_ResetTextureCache();
    if (object->cached != 0) {
        gSPDisplayList(g_displayListCursor++, (unsigned int)object->cached);
        Cache_UnlockResource(0, mem);
        return;
    }
    first = Gobjinst_RequestAnimatedModelVariant(object, object->firstKey);
    if (first == 0) {
        Cache_UnlockResource(0, mem);
        return;
    }
    if ((object->flags & 0x200) == 0 && Gobjinst_BuildActorPose(object, *(void **)first, (s32)model) == 0) {
        Cache_UnlockResource(0, first);
        Cache_UnlockResource(0, mem);
        return;
    }
    offset[0] = offset[1] = offset[2] = 0.0f;
    if (second_needed != 0) {
        second = Gobjinst_RequestAnimatedModelVariant(object, object->secondKey);
        second_needed = second != 0;
    } else {
        second = 0;
    }
    context.hasSecond = second_needed;
    context.visible = visible;
    context.camera = camera;
    context.first = first;
    context.second = second;
    context.offset = offset;
    context.pad = 0;
    object->cached = g_displayListCursor;
    gSPBranchList(g_displayListCursor++, 0);
    object->draw(object, &object->behaviorFlags, &context);
    gSPEndDisplayList(g_displayListCursor++);
    gSPBranchList(object->cached++, (unsigned int)g_displayListCursor);
    gSPDisplayList(g_displayListCursor++, (unsigned int)object->cached);
    Cache_UnlockResource(0, first);
    if (second != 0) {
        Cache_UnlockResource(0, second);
    }
    Cache_UnlockResource(0, mem);
}
