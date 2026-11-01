#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/OBJ.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "AI/ENEMIES/TURRETAI.H"
#include "include_asm.h"

/* TURRETAI.CPP */
/* SN debug stream left in us-rev1 (src/ragewars_debug_stream_us_rev1.c, ROM 0xE7092..0xF6880): function records at the retail vram */

extern void Graphu64_CrossVectors(CVector3 *, CVector3 *, CVector3 *);

void MultiplyQuaternions(void *, void *, void *);

void ScaleMatrixLocal(void *, f32, f32, f32);

s32 Graphu64_LimitVectorLength(f32 *, f32);

void TranslateMatrix(char *, f32, f32, f32);

void Graphu64_MultiplyAffineMatrices(f32 *, f32 *, f32 *);

void SwapMatrixUpForward(struct CMatrix4 *);

static inline void alignment_from_rider(f32 *matrix, TurretRiderTargetView *rider) {
    CQuatern q;
    CVector3 aim;
    aim.x = rider->aim.x;
    aim.y = rider->aim.y;
    aim.z = rider->aim.z;
    q = CVector3_GetDirectionRotation2(&aim);
    MatrixFromQuaternion(&q, matrix);
}

CQuatern CVector3_GetDirectionRotation2(CVector3 *dir) {
    CQuatern q;
    CVector3 up;
    CVector3 axis;
    f32 angle;
    f32 turn;

    up = k_turretUpDirection;
    Graphu64_NormalizeVec3(dir);
    if (dir->y > k_turretVerticalAimUpperLimit) {
        q.x = q.y = q.z = 0.0f;
        q.w = k_turretIdentityQuaternionW;
    } else if (dir->y < k_turretVerticalAimLowerLimit) {
        angle = k_turretInvertedAimAngle;
        q.x = g_turretAimSine = Gu_Sinf(angle);
        q.y = 0.0f;
        q.z = 0.0f;
        q.w = Math_Cosf(angle);
    } else {
        turn = Graphu64_ArcCos(dir->x * up.x + dir->y * up.y + dir->z * up.z);
        Graphu64_CrossVectors(&axis, &up, dir);
        Graphu64_NormalizeVec3(&axis);
        angle = turn * k_turretTurnAngleScale;
        g_turretAimSine = Gu_Sinf(angle);
        q.x = axis.x * g_turretAimSine;
        q.y = axis.y * g_turretAimSine;
        q.z = axis.z * g_turretAimSine;
        q.w = Math_Cosf(angle);
    }
    return q;
}

void Turret_CalcOrientMtx(struct Owner *owner, TurretRiderTargetView *rider) {
    CQuatern rotation;
    CQuatern combined;
    f32 model[16];
    f32 alignment[16];
    CTurretIntelligence *segment;
    f32 angleScale;
    f32 angle;
    f32 sine;

    segment = &owner->navigationTrack->segment;
    alignment_from_rider(alignment, rider);
    if (segment->m_RotNode == -1) {
        angle = owner->heading;
        angleScale = k_turretQuaternionAngleScale;
        sine = Gu_Sinf(angle * angleScale);
        rotation.x = 0.0f;
        rotation.y = sine;
        g_turretAimSine = sine;
        rotation.z = 0.0f;
        rotation.w = Math_Cosf(owner->heading * angleScale);
    } else {
        g_turretAimSine = Gu_Sinf(rider->heading * k_turretHeadingSineScale);
    }
    rotation.x = 0.0f;
    rotation.z = 0.0f;
    rotation.y = g_turretAimSine;
    rotation.w = Math_Cosf(rider->heading * k_turretHeadingCosineScale);
    MultiplyQuaternions(&combined, &rotation, &owner->orientation);
    MatrixFromQuaternion(&combined, model);
    ScaleMatrixLocal(model, owner->scale.x, owner->scale.y, owner->scale.z);
    Graphu64_LimitVectorLength(&owner->position.x, 20000.0f);
    TranslateMatrix((char *)model, owner->position.x, owner->position.y, owner->position.z);
    Graphu64_MultiplyAffineMatrices(&owner->transform.right.x, alignment, model);
    SwapMatrixUpForward(&owner->transform);
}

/* 800C6B18.CPP */
const float k_turretaiFloatConstantWords[5] = {
    0.5f, 6.283186f, 0.5f, 0.01f,
    0.01f,
};

/* 800C6B2C.CPP */
/* ROM-grounded data: src/turretai_float_constant_words_block1_us_rev1.c */
const float k_turretaiFloatConstantWordsBlock1[2] = {
    1.0f, -1.5707965f,
};
