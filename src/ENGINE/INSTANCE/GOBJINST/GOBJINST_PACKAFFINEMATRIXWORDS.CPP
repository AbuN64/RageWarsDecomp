#include "COMMON/ACTORRESOURCEHEADER.H"
#include "ENGINE/INSTANCE/GOBJINST.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PROPGEOMETRY.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern char g_actorParticleEffectSystem;

extern f32 Gobjinst_GetActorHeight(FadedActorRenderView *actor);

#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"

extern SpawnedEffectMotionView *Particle_GetLastSpawnedEffect(void *system);

extern f32 Gobjinst_GetActorRadius(FadedActorRenderView *actor);

extern void Ghot_DispatchAttachmentEffects(void *effectAttachments, s32 attachmentsRemaining, s32 attachmentMatrices, void *actor, void *attachmentNodes);


extern void *g_actorTypeOperations[];


/* Applies a blast from a source to a body when an owner is given: the strength comes from the falloff table
 * g_boneTwistImpulseCurve indexed by the source's remaining charges, times 0.5 and 0.3 and the kind (-2 for kind 5);
 * the body's reversed velocity is placed in its offset transform, an impulse at the source position is
 * built by Graphu64_BuildAxisAngleMatrix and applied through Graphu64_MultiplyAffineMatrices, the velocity is restored onto the body, and
 * the source spends a charge when its owner matches. */








extern void CopyMatrix(f32 *, BodyGobjinstApplyBoneTwistImpulse *);

extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);

extern void TranslateMatrix(void *, f32, f32, f32);

extern void Graphu64_BuildAxisAngleMatrix(f32 *, f32, f32, f32, f32);

extern void Graphu64_MultiplyAffineMatrices(BodyGobjinstApplyBoneTwistImpulse *, f32 *, f32 *);

extern void Graphu64_InterpolateQuaternionArc(void *out, s32 amount, void *firstQuaternion, void *secondQuaternion);

void Gobjinst_SpawnAnimatedModelViewEffect(FadedActorRenderView *actor, ResourceLookupPointerView *lookup) {
    CVector3 position;
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (Geometry_GetViewEffect() != 0) {
        node = SetN64_GetPackSection(*lookup->value, 2);
        if ((*node != 0) &&
            (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
            position = actor->position0;
            position.y += Gobjinst_GetActorHeight(actor) * g_maskedModelViewEffectTuning;
            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 148,
                          actor->position1, actor->rotation, position, 0, -1, 0);
            effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem);
            if (effect != 0) {
                scale = *(&g_maskedModelViewEffectTuning + 1);
                effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                effect->height = Gobjinst_GetActorHeight(actor) * scale;
            }
        }
    }
}

void Gobjinst_DispatchAttachmentEffects(void *actor, void *modelPack, s32 attachmentMaskIndex, s32 boneMatrices)
{
    ActorMatrixPackFlagsView *object = actor;
  AttachmentEventTableView *attachmentTable;
  s32 attachmentCount;
  s32 mask = 1 << attachmentMaskIndex;
  char *attachmentEntries;
  if ((object->matrixPackFlags) & mask)
  {
    attachmentTable = SetN64_GetPackSection(modelPack, 3);
    attachmentCount = attachmentTable->entryCount;
    if (attachmentCount != 0)
    {
      attachmentEntries = &attachmentTable->entries;
      Ghot_DispatchAttachmentEffects(attachmentEntries, attachmentCount, boneMatrices, actor, SetN64_GetPackSection(modelPack, 5));
    }
  }
}

void *Gobjinst_GetActorTypeEntry(char *actorStorage)
{
    s32 type;
    s32 i;
    s32 count;
    s32 limit;
    char *object;
    ObjectList *list;

    ActorKindDefinitionPointerView *actor = (void *)actorStorage;

    type = *actor->definition;
    if ((unsigned int)type >= 15) {
        return 0;
    }
    if (type == 11) {
        list = (ObjectList *)&g_playerViewRenderContext;
        count = list->count;
        i = 0;
        if (count > 0) {
            limit = count;
            object = list->objects;
            do {
                if (object == actorStorage) {
                    return 0;
                }
                if ((char *)&((SharedPlayer *)object)->views1C.view2E8_27.weapon == actorStorage) {
                    return g_actorDefinitionTable;
                }
                i++;
                object += sizeof(SharedPlayer);
            } while (i < limit);
        }
    }
    return g_actorTypeOperations[type];
}

void Gobjinst_ApplyBoneTwistImpulse(s32 unused, BoneTwistSourceView *source, BodyGobjinstApplyBoneTwistImpulse *body, s32 owner, s32 kind) {
    CVector3 velocity;
    CVector3 position;
    f32 impulse[16];
    f32 transform[16];
    f32 strength;
    f32 reverse;
    f32 multiplier;

    if (owner == 0) {
        return;
    }
    velocity.x = body->velocity.x;
    velocity.y = body->velocity.y;
    velocity.z = body->velocity.z;
    position = source->position;
    strength = g_boneTwistImpulseCurve[25 - source->charges] * 0.5f;
    strength *= 0.3f;
    if (kind == 5) {
        strength *= -2.0f;
    } else {
        strength *= kind;
    }
    CopyMatrix(transform, body);
    reverse = -1.0f;
    Graphu64_ScaleVector(&velocity, &velocity, reverse);
    TranslateMatrix(transform, velocity.x, velocity.y, velocity.z);
    Graphu64_BuildAxisAngleMatrix(impulse, strength, position.x, position.y, position.z);
    Graphu64_MultiplyAffineMatrices(body, transform, impulse);
    Graphu64_ScaleVector(&velocity, &velocity, reverse);
    TranslateMatrix(body, velocity.x, velocity.y, velocity.z);
    if (source->owner == owner) {
        source->charges--;
    }
}

/** Lerp a 3-component vector: out = a + t * (b - a). */
void Gobjinst_InterpolatePoseTranslation(void *outVector, f32 t, void *a, void *b) {
    CVector3 *out = outVector;
    CVector3 *start = a;
    CVector3 *end = b;
    out->x = start->x + (t * (end->x - start->x));
    out->y = start->y + (t * (end->y - start->y));
    out->z = start->z + (t * (end->z - start->z));
}

/** Lerp a 4-component vector: out = a + t * (b - a). */
void Gobjinst_InterpolatePoseRotation(void *cQuatern, f32 t, void *a, void *b) {
    CQuatern *out = cQuatern;
    CQuatern *left = a;
    CQuatern *right = b;

    out->x = left->x + (t * (right->x - left->x));
    out->y = left->y + (t * (right->y - left->y));
    out->z = left->z + (t * (right->z - left->z));
    out->w = left->w + (t * (right->w - left->w));
}

void Gobjinst_SampleBoneTranslation(void *poseTrack, s32 boneIndex, void *outTranslation) {
    AnimInfo *o = poseTrack;
    CVector3 *out = outTranslation;
    BoneRotationIndexPair *indices = (void *)o->boneIndexPairs;
    s16 idx;
    CROMInitialOrientation_t *recs;
    f32 *base;
    f32 *a;
    f32 scale;

    idx = indices[boneIndex].translation;
    if (idx == -1) {
        recs = (void *)o->initialOrientations;
        *out = recs[boneIndex].position;
        return;
    }
    base = SetN64_GetPackSection(o->translationFrames, (s32) idx);
    a = base + o->translationFirst;
    base = base + o->translationNext;

    scale = o->frameBlend;

    out->x = a[0] + scale * (base[0] - a[0]);
    out->y = a[1] + scale * (base[1] - a[1]);
    out->z = a[2] + scale * (base[2] - a[2]);
}

void Gobjinst_SampleBoneRotation(void *poseTrack, s32 boneIndex, CQuatern *outRotation) {
    char *o = (char *)poseTrack;
    s16 idx;
    char *rec;
    void *base;
    char *a;

    idx = ((struct BoneRotationIndexPair *) (((AnimInfo *) o)->boneIndexPairs + (boneIndex * 4)))->rotationIndex;
    if (idx == -1) {
        f32 scale;
        rec = ((AnimInfo *)(o))->initialOrientations + boneIndex * sizeof(CROMInitialOrientation_t);
        scale = (3.0518509447574615e-05f);
        outRotation->x = (f32)(((CROMInitialOrientation_t *)(rec))->m_RotX) * scale;
        outRotation->y = (f32)(((CROMInitialOrientation_t *)(rec))->m_RotY) * scale;
        outRotation->z = (f32)(((CROMInitialOrientation_t *)(rec))->m_RotZ) * scale;
        outRotation->w = (f32)(((CROMInitialOrientation_t *)(rec))->m_RotW) * scale;
        return;
    }
    base = SetN64_GetPackSection(((AnimInfo *)(o))->rotationFrames, (s32)idx);
    a = (char *)base + (((AnimInfo *)(o))->rotationFirst) * 4;
    base = (char *)base + (((AnimInfo *)(o))->rotationNext) * 4;
    {
        f32 scale;
        scale = ((AnimInfo *)(o))->frameBlend;
        outRotation->x = ((CQuatern *)(a))->x + scale * (((CQuatern *)(base))->x - ((CQuatern *)(a))->x);
        outRotation->y = ((CQuatern *)(a))->y + scale * (((CQuatern *)(base))->y - ((CQuatern *)(a))->y);
        outRotation->z = ((CQuatern *)(a))->z + scale * (((CQuatern *)(base))->z - ((CQuatern *)(a))->z);
        outRotation->w = ((CQuatern *)(a))->w + scale * (((CQuatern *)(base))->w - ((CQuatern *)(a))->w);
    }
}

void Gobjinst_SampleInterpolatedBoneRotation(BoneRotationTrackView *animation, s32 boneIndex, CQuatern *rotationOut) {
    BoneRotationTrackView *o = animation;
    BoneRotationIndexPair *indices;
    s16 idx;
    CROMInitialOrientation_t *rec;
    void *base;
    f32 scale;

    indices = (void *)o->boneIndexPairs;
    idx = indices[boneIndex].rotationIndex;
    if (idx == -1) {
        rec = (void *)(o->initialOrientations + boneIndex * sizeof(CROMInitialOrientation_t));
        scale = g_maskedModelViewEffectScale;
        rotationOut->x = (f32)rec->m_RotX * scale;
        rotationOut->y = (f32)rec->m_RotY * scale;
        rotationOut->z = (f32)rec->m_RotZ * scale;
        rotationOut->w = (f32)rec->m_RotW * scale;
        return;
    }
    base = SetN64_GetPackSection(o->rotationFrames, (s32)idx);
    Graphu64_InterpolateQuaternionArc(rotationOut, o->frameBlend,
                    (char *)base + o->rotationFirst * 4,
                    (char *)base + o->rotationNext * 4);
}

/* Converts the twelve used entries of a 4x4 float matrix to unsigned integers, splitting each pair into the high and low halfword arrays of a packed matrix and setting the final high word's low bit. Adapted from Graphu64_ConvertMatrixToFixed with the per-entry scale multiplies removed, the converted value scoped to each conversion block, and the g_affinePackUnsignedThresholdsRowZero thresholds changed. */
void Gobjinst_PackAffineMatrixWords(f32 *src, PackedMatrixWords *dst) {
    u32 *upper = dst->upper;
    u32 *lower = dst->lower;
    s32 a;
    s32 b;
    { f32 value = (src[0]); if (!((g_affinePackUnsignedThresholdsRowZero) <= value)) { (a) = (s32)value; } else { (a) = (s32)(value - (g_affinePackUnsignedThresholdsRowZero)); (a) |= 0x80000000; } };
    { f32 value = (src[1]); if (!((*(&g_affinePackUnsignedThresholdsRowZero + 1)) <= value)) { (b) = (s32)value; } else { (b) = (s32)(value - (*(&g_affinePackUnsignedThresholdsRowZero + 1))); (b) |= 0x80000000; } };
    *upper = (a & 0xFFFF0000) | ((u32)b >> 16);
    *lower = (a << 16) | (b & 0xFFFF);
    upper++;
    lower++;
    { f32 value = (src[2]); if (!((g_affinePackUnsignedThresholdsRowOne) <= value)) { (a) = (s32)value; } else { (a) = (s32)(value - (g_affinePackUnsignedThresholdsRowOne)); (a) |= 0x80000000; } };
    *upper = a & 0xFFFF0000;
    *lower = a << 16;
    upper++;
    lower++;
    { f32 value = (src[4]); if (!((*(&g_affinePackUnsignedThresholdsRowOne + 1)) <= value)) { (a) = (s32)value; } else { (a) = (s32)(value - (*(&g_affinePackUnsignedThresholdsRowOne + 1))); (a) |= 0x80000000; } };
    { f32 value = (src[5]); if (!((g_affinePackUnsignedThresholdsRowTwo) <= value)) { (b) = (s32)value; } else { (b) = (s32)(value - (g_affinePackUnsignedThresholdsRowTwo)); (b) |= 0x80000000; } };
    *upper = (a & 0xFFFF0000) | ((u32)b >> 16);
    *lower = (a << 16) | (b & 0xFFFF);
    upper++;
    lower++;
    { f32 value = (src[6]); if (!((*(&g_affinePackUnsignedThresholdsRowTwo + 1)) <= value)) { (a) = (s32)value; } else { (a) = (s32)(value - (*(&g_affinePackUnsignedThresholdsRowTwo + 1))); (a) |= 0x80000000; } };
    *upper = a & 0xFFFF0000;
    *lower = a << 16;
    upper++;
    lower++;
    { f32 value = (src[8]); if (!((g_affinePackUnsignedThresholdsRowThree) <= value)) { (a) = (s32)value; } else { (a) = (s32)(value - (g_affinePackUnsignedThresholdsRowThree)); (a) |= 0x80000000; } };
    { f32 value = (src[9]); if (!((*(&g_affinePackUnsignedThresholdsRowThree + 1)) <= value)) { (b) = (s32)value; } else { (b) = (s32)(value - (*(&g_affinePackUnsignedThresholdsRowThree + 1))); (b) |= 0x80000000; } };
    *upper = (a & 0xFFFF0000) | ((u32)b >> 16);
    *lower = (a << 16) | (b & 0xFFFF);
    upper++;
    lower++;
    { f32 value = (src[10]); if (!((g_affinePackUnsignedThresholdsTranslationXY) <= value)) { (a) = (s32)value; } else { (a) = (s32)(value - (g_affinePackUnsignedThresholdsTranslationXY)); (a) |= 0x80000000; } };
    *upper = a & 0xFFFF0000;
    *lower = a << 16;
    upper++;
    lower++;
    { f32 value = (src[12]); if (!((*(&g_affinePackUnsignedThresholdsTranslationXY + 1)) <= value)) { (a) = (s32)value; } else { (a) = (s32)(value - (*(&g_affinePackUnsignedThresholdsTranslationXY + 1))); (a) |= 0x80000000; } };
    { f32 value = (src[13]); if (!((g_affinePackUnsignedThresholdsTranslationZ) <= value)) { (b) = (s32)value; } else { (b) = (s32)(value - (g_affinePackUnsignedThresholdsTranslationZ)); (b) |= 0x80000000; } };
    *upper = (a & 0xFFFF0000) | ((u32)b >> 16);
    *lower = (a << 16) | (b & 0xFFFF);
    upper++;
    lower++;
    { f32 value = (src[14]); if (!((*(&g_affinePackUnsignedThresholdsTranslationZ + 1)) <= value)) { (a) = (s32)value; } else { (a) = (s32)(value - (*(&g_affinePackUnsignedThresholdsTranslationZ + 1))); (a) |= 0x80000000; } };
    *upper = (a & 0xFFFF0000) | 1;
    *lower = a << 16;
}
