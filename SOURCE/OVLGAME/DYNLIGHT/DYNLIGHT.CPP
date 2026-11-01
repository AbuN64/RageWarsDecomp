#include "include_asm.h"
#include "COMMON/OBJB.H"
#include "OVLGAME/OVLGAME_INITIALIZEDYNAMICLIGHTPOOL.H"
#include "COMMON/S1.H"
#include "TYPES.H"
/* Initializes a list and its eight records with default state. */
void Ovlgame_InitializeDynamicLightPool(struct CGameDynamicLight_t *lightPool) {
    f32 initialFade;
    s32 lightByteOffset;
    s32 i;
    CDLight *light;
    void *base;

    List_InitializeIntrusive(&lightPool->m_ActiveList, 0, 4);
    List_InitializeIntrusive(&lightPool->m_FreeList, 0, 4);
    i = 0;
    lightByteOffset = 40;
    initialFade = 1.0f;
    do {
        base = lightPool;
        light = base + lightByteOffset;
        List_AppendIntrusive(&lightPool->m_FreeList, light);
        lightByteOffset += 24;
        i += 1;
        light->m_pROMLight = 0;
        light->m_ColorFade = initialFade;
        light->m_bEnabled = 0;
    } while (i < 8);
}
