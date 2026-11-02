#include "include_asm.h"
#include "COMMON/VECTOR3.H"

/* k_TurretMixedLinkFragmentsEncodedBytes_TurretMixedLinkFragments.CPP */
#if defined(VERSION_US)
/* two stale words ahead of the up vector ('RGBR', 0): linker fill, read by nothing */
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
#endif

#if defined(VERSION_EU)
/* two stale opcode words (lw v0,12(s0); lui a2,0x500) ahead of the up vector: linker fill, read by nothing */
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
#endif

/* 800C6DB0.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
/* 8 bytes of stale fill (0x00209EF4 twice) padding the rodata between g_difficultyAimNegativeJitter and the Portal_DispatchActorBehavior literals to 16; read by nothing */
unsigned int g_difficultyAimJitterPad[2] = {
    0x00209EF4, 0x00209EF4,
};
#endif
#if defined(VERSION_EU_X)
/* two stale words (8.0f, 23.0f as bit patterns) ahead of the up vector: linker fill, read by nothing */
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
#endif
#endif
