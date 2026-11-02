#include "include_asm.h"
#include "COMMON/VECTOR3.H"

/* 800C19E8.CPP */
#if defined(VERSION_DE)
/* two stale words ahead of the up vector (0, 0.99999f): linker fill, read by nothing */
unsigned int g_cvector3Getdirectionrotation2DataPad[2] = {
    0x00000000, 0x3F7FFF58,
};
/* 800C19F0: world up, copied to the stack by CVector3_GetDirectionRotation2 (lw x3) */
CVector3 k_turretUpDirection = { 0.0f, 1.0f, 0.0f };
#endif

/* 800C6AEC.CPP */
const float k_cvector3Getdirectionrotation2DataFloatConstantWords[5] = {
    0.99999f, 1.0f, -0.99999f, 1.5707965f,
    0.5f,
};

/* 800C6B00.CPP */
/* ROM-grounded data: src/k_cvector3Getdirectionrotation2DataFloatConstantWordsBlock1_Cvector3Getdirectionrotation2Data.c */
const float k_cvector3Getdirectionrotation2DataFloatConstantWordsBlock1[3] = {
    0.5f, 0.5f, 0.5f,
};
