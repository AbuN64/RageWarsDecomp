#ifndef COMMON_CAMERA_SHAKE_H
#define COMMON_CAMERA_SHAKE_H
#include "TYPES.H"
#include "COMMON/VECTOR3.H"

/* One 0x14-byte waveform, embedded three times in each 0x54-byte shake. */
typedef struct CShakeAxis_t CShakeAxis;
struct CShakeAxis_t {
    s32 mode;
    f32 value;
    f32 m_LastShake;
    f32 m_Amp;
    f32 m_Angle;
};

struct CShake_t;
typedef struct CShake_t CShake;

struct CShake_t {
    s32 m_pLast;
    CShake *next;
    CVector3 m_vPos;
    f32 m_Radius;
    CShakeAxis x;
    CShakeAxis y;
    CShakeAxis z;
};
#endif
