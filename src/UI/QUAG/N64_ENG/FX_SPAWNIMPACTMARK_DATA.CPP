#include "include_asm.h"
#include "UI/QUAG/N64_ENG.H"

/* ribbonBlendResourceTable.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char g_ribbonBlendResourceFirstBase_de[];
unsigned int k_FxSpawnimpactmarkEncodedWords[6] = {
    (unsigned int)g_ribbonBlendResourceFirstBase_de + 0xC, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x34, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x5C, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0xD4, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x14C, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x174,
};
#endif
#if defined(VERSION_EU)
extern char g_ribbonBlendResourceFirstBase_de[];
unsigned int k_FxSpawnimpactmarkEncodedWords[6] = {
    (unsigned int)g_ribbonBlendResourceFirstBase_de + 0xC, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x34, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x5C, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0xD4, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x14C, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x174,
};
#endif
#if defined(VERSION_EU_X)
extern char g_ribbonBlendResourceFirstBase_de[];
unsigned int k_FxSpawnimpactmarkEncodedWords[6] = {
    (unsigned int)g_ribbonBlendResourceFirstBase_de + 0xC, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x34, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x5C, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0xD4, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x14C, (unsigned int)g_ribbonBlendResourceFirstBase_de + 0x174,
};
#endif
#if defined(VERSION_US)
extern char g_ribbonBlendResourceFirstBase_de[];
unsigned int k_FxSpawnimpactmarkEncodedWords[6] = {
    (unsigned int)g_ribbonBlendResourceFirstBase_de + 0xC, (unsigned int)g_ribbonBlendResourceSecond_us, (unsigned int)g_ribbonBlendResourceThird_us, (unsigned int)g_ribbonBlendResourceFourthBase_us + 0x60, (unsigned int)g_ribbonBlendResourceFifthBase_us + 0x64, (unsigned int)g_ribbonBlendResourceFifthBase_us + 0x8C,
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
unsigned int g_ribbonBlendResourceTable_StorageWords[6] = {
    0x800D2CB0, 0x800D2CD8, 0x800D2D00, 0x800D2D78, 0x800D2DF0, 0x800D2E18,
};
#endif

/* particleQuadDisplayListState.CPP */
/* ROM-grounded data: rodata/writable/800D2E58 */
unsigned int g_FxSpawnimpactmarkEncodedWords[2] = {
    0x00000000, 0x00000000,
};
