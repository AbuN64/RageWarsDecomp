#include "COMMON/PACKEDMESHMATERIAL.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "include_asm.h"
#include "RENDER/RUMBLE_EXPANDMESHMATERIAL.H"

/* MATTABLE.CPP */
extern void Textload_LocateTextureResource(s32 *resourceId, s32 sectionIndex);

void Rumble_ExpandMeshMaterial(MeshMaterial *dstData, CROMSection *section) {
    s16 value;
    s32 reference;

    dstData->flags = section->flags;
    dstData->primaryColor[0] = section->primaryColor[0];
    dstData->primaryColor[1] = section->primaryColor[1];
    dstData->primaryColor[2] = section->primaryColor[2];
    dstData->primaryColor[3] = section->primaryColor[3];
    dstData->secondaryColor[0] = section->secondaryColor[0];
    dstData->secondaryColor[1] = section->secondaryColor[1];
    dstData->secondaryColor[2] = section->secondaryColor[2];
    dstData->secondaryColor[3] = section->secondaryColor[3];
    dstData->width = section->width;
    dstData->height = section->height;
    dstData->mode = section->mode;
    if (section->flags & 0x40) {
        value = (section->renderMode * 2) | 1;
    } else {
        value = section->renderMode * 2;
    }
    dstData->renderMode = value;
    reference = section->textureId;
    if (reference == -1) {
        dstData->texture = 0;
        return;
    }
    Textload_LocateTextureResource(&dstData->texture, reference);
}

f32 Rumble_SamplePackedFloatRange(s32 packedRange) {
    s32 baseFloatBits;
    s32 rangeFloatBits;
    u32 seed;
    s32 idx;
    f64 randomFraction;

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    /* The halves are read by address below; a little-endian host holds them swapped. */
    packedRange = (s32) (((u32) packedRange << 16) | ((u32) packedRange >> 16));
#endif
    baseFloatBits = (s32) (*(u16 *) &packedRange) << 16;
    if (((struct PackedMaterialHalfwordView *) ((u16 *) (&packedRange)))->spreadHighWord == 0) {
        return *(f32 *) &baseFloatBits;
    }
    rangeFloatBits = (s32) (((struct PackedMaterialHalfwordView *) ((u16 *) (&packedRange)))->spreadHighWord) << 16;
    seed = (g_primaryRandomSeed * (s32) 0xA84A5B53) + (s32) 0x58348C2D;
    idx = (s32) ((seed >> 16) & 0x7FFF);
    randomFraction = (f64) idx;
    g_primaryRandomSeed = seed;
    if (idx < 0) {
        randomFraction += g_packedFloatRandomBias;
    }
    return *(f32 *) &baseFloatBits + (((f32) randomFraction * *(f32 *) &rangeFloatBits) * g_packedFloatRandomScale);
}

/* WEAPON_SWITCH_STATE_TABLE_US.CPP */
#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
/* 800C9FAC.CPP */
/* ROM-grounded data: rodata/unresolved/800C9FAC */
struct {
    u8 retainedRecordWords[4];
} g_WeaponSwitchStateTableUsEncodedWords __attribute__((aligned(4))) = {
    { 0x00, 0x2A, 0x51, 0xC8 }
};
#endif
#endif

/* RUMBLE_SAMPLEPACKEDFLOATRANGE_DATA.CPP */
/* ROM-grounded data: src/g_Rumble_SamplePackedFloatRangeConstantsUsRev1_RumbleSamplepackedfloatrangeData.c */
const float g_Rumble_SamplePackedFloatRangeConstantsUsRev1[3] = {
    3.0e+01f, 0.0f, 3.051851e-05f,
};
