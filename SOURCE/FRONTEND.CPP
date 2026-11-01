

/* G_COLLISIONSETUPTABLE.CPP */
#if defined(VERSION_US)
#include "COMMON/CCOLLISIONSETUP_T.H"
/* 8043962C_12.CPP */
/* g_collisionSetupTable_Frontend11.CPP */
/* The collision setup table CCollision_Initialize hands to CCollision_ApplySetupTable (through its KUSEG alias
 * g_collisionSetupTableResource): one row per collision info, ended by an empty row. */
CCollisionSetup_t g_collisionSetupTable[36] = {
    { (CCollisionInfo2_t *)0x800FE458, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE358, 0x3C552B, 5, 2, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE190, 0x3C5529, 2, 2, 2, -2100.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE2F8, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE3B8, 0x3C5729, 5, 2, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FDFB0, 0x3C5D29, 5, 2, 2, -69.119995f, 0.0f, 0.0f, 0.0f, 0.08f },
    { (CCollisionInfo2_t *)0x800FE1B0, 0x3C5529, 5, 2, 2, 0.0f, 0.0f, 0.9f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE418, 0x2C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE010, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE130, 0x3C5309, 5, 6, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE398, 0x3C5729, 0, 0, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE318, 0x3C5308, 5, 3, 2, -2303.9998f, 0.3f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE110, 0x3C5308, 5, 3, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE478, 0x3C5108, 5, 2, 2, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE378, 0x3C5109, 5, 2, 2, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE150, 0x3C5309, 5, 6, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE498, 0x3C5108, 5, 2, 2, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE4D8, 0x344108, 0, 3, 3, -1235.4816f, 0.5f, 0.25f, 0.0f, 0.25f },
    { (CCollisionInfo2_t *)0x800FE090, 0x110108, 1, 3, 3, -4941.9263f, 0.7083334f, 0.1f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE438, 0x345309, 0, 3, 3, -1535.9999f, 0.6f, 1.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE3F8, 0x305109, 0, 3, 3, 0.0f, 0.6f, 1.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE4F8, 0x10, 0, 0, 0, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE0D0, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE070, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE050, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FDFF0, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FDFD0, 0x1C000, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE0F0, 0x204408, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE030, 0x1C000, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE1D0, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE170, 0x0, 0, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE0B0, 0x341508, 2, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE3D8, 0x141508, 2, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE4B8, 0x101508, 1, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x800FE338, 0x105529, 5, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0 },
};
#endif
