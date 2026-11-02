#include "TYPES.H"
#include "include_asm.h"

/* 800CBCB0.CPP */
#if defined(VERSION_DE)
extern char g_Events_PlayClipEventEncodedCallbackEntryVariant2[];
extern char g_Events_StopClipEventEncodedCallbackEntryVariant2[];
extern char g_Events_SpawnActorEffectEncodedCallback[];
extern char g_Events_ApplyDirectDamageEncodedCallbackEntryVariant2[];
extern char g_Events_ApplyRadialDamageEncodedCallbackEntryVariant2[];
extern char g_Events_ApplyRadialDamageWithKnockbackEncodedCallbackEntryVariant2[];
extern char g_Events_PreserveEventArgumentEncodedCallbackEntryVariant2[];
extern char g_Events_RunFirstNodeOperationEncodedCallbackEntryVariant2[];
extern char addrLow_Events_RunSecondNodeOperationEntryVariant2[];
extern char addrLow_Events_StartCameraFadeAtPointEntryVariant2[];
extern char g_Events_ConsumeEventArgumentEncodedCallbackEntryVariant2[];
extern char g_Events_RequestActorPositionEncodedCallbackEntryVariant2[];
extern char g_Events_StartEnabledCameraEmitterEncodedCallbackEntryVariant2[];
extern char g_Events_StartDisabledCameraEmitterEncodedCallbackEntryVariant2[];
extern char g_Events_PostGameplayMessageEncodedCallbackEntryVariant2[];
extern char g_Events_ApplyFlag100RadialDamageEncodedCallbackEntryVariant2[];
extern char g_Events_ApplyFlag100RadialKnockbackEncodedCallbackEntryVariant2[];
extern char g_Events_ApplyFlag200RadialDamageEncodedCallbackEntryVariant2[];
extern char g_Events_ApplyFlag200RadialKnockbackEncodedCallbackEntryVariant2[];
extern char g_Events_ApplyFlag400RadialDamageEncodedCallbackEntryVariant2[];
extern char g_Events_ApplyFlag400RadialKnockbackEncodedCallbackEntryVariant2[];
extern char g_Events_StartActorEmitterEncodedCallbackEntryVariant2[];
extern char addrLow_Events_PlayTeamClip_eu_x[];
extern char addrLow_Events_PlayTeamClipEntryVariant2[];
extern char g_Events_SpawnFilteredActorEffectEncodedCallbackEntryVariant2[];
extern char g_Events_FireWithinHeightRangeEncodedCallbackEntryVariant2[];
extern char addrLow_Events_SetActorEventBitEntryVariant2[];
extern char g_Events_ClearActorEventBitEncodedCallbackEntryVariant2[];
extern char g_Events_SpawnAttachedEffectEncodedCallbackEntryVariant2[];
extern char g_Events_SpawnPositionedEffectPackedAddress24[];
extern char g_Events_PlayTeamEffectPackedAddress24[];
extern char g_Events_SetActorLoopingSoundPackedAddress24_us_rev1[];
extern char g_Events_StopActorLoopingSoundPackedAddress24[];
extern char g_Events_IncrementNearbyPlayerCounterPackedAddress24[];
extern char g_Events_SetActorEffectModePackedAddress24[];
extern char g_Events_DeactivateActorPackedAddress24[];
u32 g_resourceModelDisplayListAndEventCallbackWords_de[428] = {
    0xFFFFFF00, 0xFFFFFF00, 0x00007F00, 0x00000000, 0xD9000000, 0x00000000,
    0xD9FFFFFF, 0x00000001, 0xDB020000, 0x00000018, 0xDC08060A, 0x800CBC98,
    0xDC08090A, 0x800CBC90, 0xDF000000, 0x00000000, 0xE3000A01, 0x00000000,
    0xE3000800, 0x00000000, 0xE3000F00, 0x00000000, 0xE3001001, 0x00000000,
    0xE3000D01, 0x00000000, 0xE3000C00, 0x00080000, 0xE3001201, 0x00002000,
    0xE3001402, 0x00000C00, 0xE3001700, 0x00000000, 0xE2001E01, 0x00000000,
    0xE7000000, 0x00000000, 0xDF000000, 0x00000000, 0xF5100000, 0x07000000,
    0xF3000000, 0x0755C000, 0xF5101000, 0x00014050, 0xF2000000, 0x0007C07C,
    0xF5100900, 0x01010441, 0xF2000000, 0x0103C03C, 0xF5100540, 0x0200C832,
    0xF2000000, 0x0201C01C, 0xF5100350, 0x03008C23, 0xF2000000, 0x0300C00C,
    0xF5100354, 0x04005014, 0xF2000000, 0x04004004, 0xF5100356, 0x05001405,
    0xF2000000, 0x05000000, 0xE3001001, 0x00000000, 0xDF000000, 0x00000000,
    0xF5100000, 0x07000000, 0xF3000000, 0x0755C000, 0xF5101000, 0x00054150,
    0xF2000000, 0x0007C07C, 0xF5100900, 0x01050541, 0xF2000000, 0x0103C03C,
    0xF5100540, 0x0204C932, 0xF2000000, 0x0201C01C, 0xF5100350, 0x03048D23,
    0xF2000000, 0x0300C00C, 0xF5100354, 0x04045114, 0xF2000000, 0x04004004,
    0xF5100356, 0x05041505, 0xF2000000, 0x05000000, 0xE3001001, 0x00000000,
    0xDF000000, 0x00000000, 0xF5100000, 0x07000000, 0xF3000000, 0x0755C000,
    0xF5101000, 0x00017C5F, 0xF2000000, 0x0007C07C, 0xF5101000, 0x01014050,
    0xF2000000, 0x0107C07C, 0xF5100900, 0x02010441, 0xF2000000, 0x0203C03C,
    0xF5100540, 0x0300C832, 0xF2000000, 0x0301C01C, 0xF5100350, 0x04008C23,
    0xF2000000, 0x0400C00C, 0xF5100354, 0x05005014, 0xF2000000, 0x05004004,
    0xF5100356, 0x06001405, 0xF2000000, 0x06000000, 0xE3000D01, 0x00040000,
    0xE3001001, 0x00000000, 0xDF000000, 0x00000000, 0xF5100000, 0x07000000,
    0xF3000000, 0x0755C000, 0xF5101000, 0x0001785E, 0xF2000000, 0x0007C07C,
    0xF5101000, 0x01014050, 0xF2000000, 0x0107C07C, 0xF5100900, 0x02010441,
    0xF2000000, 0x0203C03C, 0xF5100540, 0x0300C832, 0xF2000000, 0x0301C01C,
    0xF5100350, 0x04008C23, 0xF2000000, 0x0400C00C, 0xF5100354, 0x05005014,
    0xF2000000, 0x05004004, 0xF5100356, 0x06001405, 0xF2000000, 0x06000000,
    0xE3000D01, 0x00040000, 0xE3001001, 0x00000000, 0xDF000000, 0x00000000,
    0xF5900000, 0x07000000, 0xF3000000, 0x07580000, 0xF5800800, 0x00018060,
    0xF2000000, 0x000FC0FC, 0xF5800500, 0x01014451, 0xF2000000, 0x0107C07C,
    0xF5800340, 0x02010842, 0xF2000000, 0x0203C03C, 0xF5800350, 0x0300CC33,
    0xF2000000, 0x0301C01C, 0xF5800358, 0x04009024, 0xF2000000, 0x0400C00C,
    0xF580035C, 0x05005415, 0xF2000000, 0x05004004, 0xF580035E, 0x06001806,
    0xF2000000, 0x06000000, 0xE3000D01, 0x00000000, 0xE3001001, 0x00000000,
    0xDF000000, 0x00000000, 0xE3001001, 0x00000000, 0xD7000002, 0x80008000,
    0xD9F9FBFF, 0x00000000, 0xD9FFFFFF, 0x00210004, 0xFCFF97FF, 0xFFFFFE38,
    0xE200001C, 0xC8104B50, 0xDB040004, 0x00000001, 0xDB04000C, 0x00000001,
    0xDB040014, 0x0000FFFF, 0xDB04001C, 0x0000FFFF, 0x01004008, 0x801428E0,
    0x06000204, 0x00040600, 0xDB040004, 0x00000005, 0xDB04000C, 0x00000005,
    0xDB040014, 0x0000FFFB, 0xDB04001C, 0x0000FFFB, 0xDF000000, 0x00000000,
    0xE3001001, 0x00000000, 0xD7FF0002, 0x80008000, 0xD9F9FBFF, 0x00000000,
    0xD9FFFFFF, 0x00210004, 0xFCFF97FF, 0xFFFFFE38, 0xE200001C, 0xC8104E50,
    0xDB040004, 0x00000001, 0xDB04000C, 0x00000001, 0xDB040014, 0x0000FFFF,
    0xDB04001C, 0x0000FFFF, 0x01004008, 0x801428E0, 0x06000204, 0x00040600,
    0xDB040004, 0x00000005, 0xDB04000C, 0x00000005, 0xDB040014, 0x0000FFFB,
    0xDB04001C, 0x0000FFFB, 0xDF000000, 0x00000000, (unsigned int)g_Events_SpawnActorEffectEncodedCallback, 0x00000000,
    (unsigned int)g_Events_PlayClipEventEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)g_Events_SpawnActorEffectEncodedCallback, 0x00000000, (unsigned int)g_Events_ApplyDirectDamageEncodedCallbackEntryVariant2, 0x00000004,
    (unsigned int)g_Events_ApplyRadialDamageEncodedCallbackEntryVariant2, 0x00000006, (unsigned int)g_Events_ApplyRadialDamageWithKnockbackEncodedCallbackEntryVariant2, 0x00000006, (unsigned int)g_Events_PreserveEventArgumentEncodedCallbackEntryVariant2, 0x0000000A,
    (unsigned int)g_Events_RunFirstNodeOperationEncodedCallbackEntryVariant2, 0x00000010, (unsigned int)addrLow_Events_RunSecondNodeOperationEntryVariant2, 0x00000010, (unsigned int)g_Events_SpawnActorEffectEncodedCallback, 0x00000000,
    (unsigned int)addrLow_Events_StartCameraFadeAtPointEntryVariant2, 0x00000000, (unsigned int)g_Events_ConsumeEventArgumentEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)g_Events_RequestActorPositionEncodedCallbackEntryVariant2, 0x00000000,
    (unsigned int)g_Events_StartEnabledCameraEmitterEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)g_Events_StartDisabledCameraEmitterEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)g_Events_PostGameplayMessageEncodedCallbackEntryVariant2, 0x00000000,
    (unsigned int)g_Events_ApplyFlag100RadialDamageEncodedCallbackEntryVariant2, 0x00000006, (unsigned int)g_Events_ApplyFlag100RadialKnockbackEncodedCallbackEntryVariant2, 0x00000006, (unsigned int)g_Events_ApplyFlag200RadialDamageEncodedCallbackEntryVariant2, 0x00000007,
    (unsigned int)g_Events_ApplyFlag200RadialKnockbackEncodedCallbackEntryVariant2, 0x00000007, (unsigned int)g_Events_ApplyFlag400RadialDamageEncodedCallbackEntryVariant2, 0x00000006, (unsigned int)g_Events_ApplyFlag400RadialKnockbackEncodedCallbackEntryVariant2, 0x00000006,
    (unsigned int)g_Events_StartActorEmitterEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)addrLow_Events_PlayTeamClip_eu_x, 0x00000000, (unsigned int)addrLow_Events_PlayTeamClipEntryVariant2, 0x00000000,
    (unsigned int)g_Events_SpawnFilteredActorEffectEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)g_Events_FireWithinHeightRangeEncodedCallbackEntryVariant2, 0x00000007, (unsigned int)addrLow_Events_SetActorEventBitEntryVariant2, 0x00000000,
    (unsigned int)g_Events_ClearActorEventBitEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)g_Events_SpawnAttachedEffectEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)g_Events_PlayTeamEffectPackedAddress24, 0x00000000,
    (unsigned int)g_Events_StopClipEventEncodedCallbackEntryVariant2, 0x00000000, (unsigned int)g_Events_SetActorLoopingSoundPackedAddress24_us_rev1, 0x00000000, (unsigned int)g_Events_StopActorLoopingSoundPackedAddress24, 0x00000000,
    (unsigned int)g_Events_IncrementNearbyPlayerCounterPackedAddress24, 0x00000002, (unsigned int)g_Events_SpawnPositionedEffectPackedAddress24, 0x00000000, (unsigned int)g_Events_SetActorEffectModePackedAddress24, 0x00000000,
    (unsigned int)g_Events_DeactivateActorPackedAddress24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00071115, 0x15110700, 0x00000000,
    0x00000003, 0x1529363E, 0x3E362815, 0x03000000, 0x0000031C, 0x3550626E,
    0x6E625038, 0x1C010000, 0x00001738, 0x5879919F, 0x9E927959, 0x36170000,
    0x00082850, 0x799FBDCE, 0xCEBE9F79, 0x4E290800, 0x00113662, 0x91BEDFF2,
    0xF2E0BD92, 0x62361000, 0x00173E6E, 0x9FCEF2FF, 0xFFF3CE9F, 0x6D3E1500,
    0x00173D6E, 0xA1CDF2FF, 0xFFF3CE9F, 0x6D401700, 0x00103662, 0x92BEDFF3,
    0xF2E0BE92, 0x62361100, 0x00072850, 0x799FBDCF, 0xCEBE9F78, 0x4E290700,
    0x00001736, 0x597A92A1, 0x9F927958, 0x36150000, 0x0000031C, 0x3650646E,
    0x6E644E36, 0x1C010000, 0x00000003, 0x1528363E, 0x3D362815, 0x03000000,
    0x00000000, 0x00071015, 0x15110700, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
};
#endif

/* 80268160_14.CPP */
#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    u32 renderModesAndFlags[12];
    s32 fillEnabled;
    f32 fillRed;
    f32 fillGreen;
    f32 fillBlue;
    f32 fillAlpha;
    f32 fillTargetAlpha;
    u8 primitiveOverride[6];
    u8 alignmentFill[2];
} g_geometryDrawResourceModelWritableWords_de __attribute__((aligned(4))) = {
    { 0xffffffff, 0xffffffff, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x10000, 0xc4000000, 0xc8000000 },
    0,
    255.0f,
    255.0f,
    255.0f,
    255.0f,
    255.0f,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x0 }
};
typedef char g_geometryDrawResourceModelWritableWords_deSizeCheck[(sizeof(g_geometryDrawResourceModelWritableWords_de) == 80) ? 1 : -1];
#endif
#endif

#if defined(VERSION_DE)
#if defined(VERSION_DE)
unsigned short k_GeometryDrawresourcemodelEncodedHalfwords[8] = {
    0xA000, 0x0000, 0xA000, 0x0000, 0x00FF, 0x0000, 0x00FF, 0x0000,
};
#endif
#endif
