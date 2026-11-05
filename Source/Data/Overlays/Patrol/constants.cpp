#include "types.h"
#include "include_asm.h"

/* NAV_UPDATEPATROLROUTE_DATA.CPP */
#if !(defined(VERSION_US))
#if defined(VERSION_DE)
const f32 g_patrolGoalArrivalDistance = 102.399994f;
#endif
#if defined(VERSION_EU)
const f32 g_patrolGoalArrivalDistance = 102.399994f;
#endif
#if defined(VERSION_EU_X)
const f32 g_patrolGoalArrivalDistance = 102.399994f;
#endif
#if defined(VERSION_US_REV1)
const f32 g_patrolGoalArrivalDistance = 102.399994f;
#endif
#endif

#if defined(VERSION_EU_X)
struct {
    u8 retainedRecordWords[12];
} k_navUpdatepatrolrouteFragment __attribute__((aligned(4))) = {
    { 0x3C, 0x8E, 0xFA, 0x36, 0x41, 0x80, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00 }
};
#endif

#if defined(VERSION_DE)
struct {
    u8 retainedRecordWords[12];
} k_NavUpdatepatrolrouteEncodedWords __attribute__((aligned(4))) = {
    { 0x42, 0x4C, 0xCC, 0xCC, 0xAF, 0xB1, 0x00, 0x14, 0x00, 0xC0, 0x88, 0x21 }
};
#endif

/* BARREL_SPAWNEFFECTSFROMMASK_DATA.CPP */
const float k_barrelSpawneffectsfrommaskDataFloatConstantWords[2] = {
    4.5e+02f, 6.0e+02f,
};

#if defined(VERSION_US)
#if defined(VERSION_US)
extern char s_BarrelSpawneffectsfrommaskCBHoleTTText[12];
#else
char s_BarrelSpawneffectsfrommaskCBHoleTTText[12] =
    "CBHole_tT\000\000\000";
#endif
#endif

#if defined(VERSION_EU_X)
struct {
    u8 retainedRecordWords[12];
} k_barrelSpawneffectsfrommaskFragment __attribute__((aligned(4))) = {
    { 0x00, 0x00, 0x00, 0x00, 0x41, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};
#endif

#if defined(VERSION_EU)
struct {
    u8 retainedInstructionWords[12];
} k_barrelSpawneffectsfrommaskFragment __attribute__((aligned(4))) = {
    { 0x3C, 0x01, 0xFF, 0xFF, 0x34, 0x21, 0x00, 0xFF, 0x01, 0x81, 0x60, 0x24 }
};
#endif

#if defined(VERSION_DE)
struct {
    u8 retainedRecordWords[12];
} k_BarrelSpawneffectsfrommaskEncodedWords __attribute__((aligned(4))) = {
    { 0x3F, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x3B, 0x4C, 0xCC, 0xCD }
};
#endif

/* K_OVERLAYSLINKGAPCONSTANTSZEROWORDS.CPP */
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_US)
#if defined(VERSION_US)
extern unsigned int k_OverlaysLinkGapConstantsZeroWords[1];
#else
unsigned int k_OverlaysLinkGapConstantsZeroWords[1] = {
    0x00000000,
};
#endif
#endif
#endif

/* G_OVERLAYSONECONSTANTSCONSTANTWORDS.CPP */
#if defined(VERSION_US_REV1)
struct {
    u8 retainedRecordWords[8];
} g_patrolConstantsConstantWords __attribute__((aligned(4))) = {
    { 0x00, 0x23, 0x27, 0xB4, 0x00, 0x23, 0x27, 0xB4 }
};
#endif

/* G_OVERLAYONEUNSIGNEDCONVERTBIASFLOAT.CPP */
#if defined(VERSION_US_REV1)
float g_patrolUnsignedConvertBiasFloat[1] __attribute__((aligned(4))) = { 2147483648.0f };
#endif
