#include "TYPES.H"

#if defined(VERSION_EU_X)
extern char addrLow_Events_PlayClipEvent[];
extern char addrLow_Events_StopClipEvent[];
extern char addrLow_Events_SpawnActorEffect[];
extern char addrLow_Events_ApplyDirectDamage[];
extern char addrLow_Events_ApplyRadialDamage[];
extern char addrLow_Events_ApplyRadialDamageWithKnockback[];
extern char addrLow_Events_PreserveEventArgument[];
extern char addrLow_Events_RunFirstNodeOperation[];
extern char addrLow_Events_RunSecondNodeOperation_eu_x[];
extern char g_Events_RunSecondNodeOperationPackedAddress24_us_rev1[];
extern char addrLow_Events_ConsumeEventArgument[];
extern char addrLow_Events_RequestActorPosition[];
extern char addrLow_Events_StartEnabledCameraEmitter[];
extern char addrLow_Events_StartDisabledCameraEmitter[];
extern char addrLow_Events_PostGameplayMessage[];
extern char addrLow_Events_ApplyFlag100RadialDamage[];
extern char addrLow_Events_ApplyFlag100RadialKnockback[];
extern char addrLow_Events_ApplyFlag200RadialDamage[];
extern char addrLow_Events_ApplyFlag200RadialKnockback[];
extern char addrLow_Events_ApplyFlag400RadialDamage[];
extern char addrLow_Events_ApplyFlag400RadialKnockback[];
extern char addrLow_Events_StartActorEmitter[];
extern char addrLow_Events_IgnoreEvent[];
extern char addrLow_Events_PlayTeamClip_eu_x[];
extern char addrLow_Events_SpawnFilteredActorEffect[];
extern char addrLow_Events_FireWithinHeightRange[];
extern char addrLow_Events_SetActorEventBit_eu_x[];
extern char addrLow_Events_ClearActorEventBit[];
extern char addrLow_Events_SpawnAttachedEffect[];
extern char addrLow_Events_SpawnPositionedEffect[];
extern char addrLow_Events_PlayTeamEffect[];
extern char addrLow_Events_SetActorLoopingSound[];
extern char addrLow_Events_StopActorLoopingSound[];
extern char addrLow_Events_IncrementNearbyPlayerCounter[];
extern char addrLow_Events_SetActorEffectMode[];
extern char addrLow_Events_DeactivateActor[];
u32 g_actorEventCallbackTableWords_eu_x[428] = {
    0xFFFFFF00, 0xFFFFFF00, 0x00007F00, 0x00000000, 0xD9000000, 0x00000000,
    0xD9FFFFFF, 0x00000001, 0xDB020000, 0x00000018, 0xDC08060A, 0x800CD248,
    0xDC08090A, 0x800CD240, 0xDF000000, 0x00000000, 0xE3000A01, 0x00000000,
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
    0xDB040014, 0x0000FFFF, 0xDB04001C, 0x0000FFFF, 0x01004008, 0x8014C8E0,
    0x06000204, 0x00040600, 0xDB040004, 0x00000005, 0xDB04000C, 0x00000005,
    0xDB040014, 0x0000FFFB, 0xDB04001C, 0x0000FFFB, 0xDF000000, 0x00000000,
    0xE3001001, 0x00000000, 0xD7FF0002, 0x80008000, 0xD9F9FBFF, 0x00000000,
    0xD9FFFFFF, 0x00210004, 0xFCFF97FF, 0xFFFFFE38, 0xE200001C, 0xC8104E50,
    0xDB040004, 0x00000001, 0xDB04000C, 0x00000001, 0xDB040014, 0x0000FFFF,
    0xDB04001C, 0x0000FFFF, 0x01004008, 0x8014C8E0, 0x06000204, 0x00040600,
    0xDB040004, 0x00000005, 0xDB04000C, 0x00000005, 0xDB040014, 0x0000FFFB,
    0xDB04001C, 0x0000FFFB, 0xDF000000, 0x00000000, 0x3F169CFB, 0x3F162965,
    (unsigned int)addrLow_Events_PlayClipEvent, 0x00000000, (unsigned int)addrLow_Events_SpawnActorEffect, 0x00000000, (unsigned int)addrLow_Events_ApplyDirectDamage, 0x00000004,
    (unsigned int)addrLow_Events_ApplyRadialDamage, 0x00000006, (unsigned int)addrLow_Events_ApplyRadialDamageWithKnockback, 0x00000006, (unsigned int)addrLow_Events_PreserveEventArgument, 0x0000000A,
    (unsigned int)addrLow_Events_RunFirstNodeOperation, 0x00000010, (unsigned int)addrLow_Events_RunSecondNodeOperation_eu_x, 0x00000010, (unsigned int)addrLow_Events_SpawnActorEffect, 0x00000000,
    (unsigned int)g_Events_RunSecondNodeOperationPackedAddress24_us_rev1, 0x00000000, (unsigned int)addrLow_Events_ConsumeEventArgument, 0x00000000, (unsigned int)addrLow_Events_RequestActorPosition, 0x00000000,
    (unsigned int)addrLow_Events_StartEnabledCameraEmitter, 0x00000000, (unsigned int)addrLow_Events_StartDisabledCameraEmitter, 0x00000000, (unsigned int)addrLow_Events_PostGameplayMessage, 0x00000000,
    (unsigned int)addrLow_Events_ApplyFlag100RadialDamage, 0x00000006, (unsigned int)addrLow_Events_ApplyFlag100RadialKnockback, 0x00000006, (unsigned int)addrLow_Events_ApplyFlag200RadialDamage, 0x00000007,
    (unsigned int)addrLow_Events_ApplyFlag200RadialKnockback, 0x00000007, (unsigned int)addrLow_Events_ApplyFlag400RadialDamage, 0x00000006, (unsigned int)addrLow_Events_ApplyFlag400RadialKnockback, 0x00000006,
    (unsigned int)addrLow_Events_StartActorEmitter, 0x00000000, (unsigned int)addrLow_Events_IgnoreEvent, 0x00000000, (unsigned int)addrLow_Events_PlayTeamClip_eu_x, 0x00000000,
    (unsigned int)addrLow_Events_SpawnFilteredActorEffect, 0x00000000, (unsigned int)addrLow_Events_FireWithinHeightRange, 0x00000007, (unsigned int)addrLow_Events_SetActorEventBit_eu_x, 0x00000000,
    (unsigned int)addrLow_Events_ClearActorEventBit, 0x00000000, (unsigned int)addrLow_Events_SpawnAttachedEffect, 0x00000000, (unsigned int)addrLow_Events_PlayTeamEffect, 0x00000000,
    (unsigned int)addrLow_Events_StopClipEvent, 0x00000000, (unsigned int)addrLow_Events_SetActorLoopingSound, 0x00000000, (unsigned int)addrLow_Events_StopActorLoopingSound, 0x00000000,
    (unsigned int)addrLow_Events_IncrementNearbyPlayerCounter, 0x00000002, (unsigned int)addrLow_Events_SpawnPositionedEffect, 0x00000000, (unsigned int)addrLow_Events_SetActorEffectMode, 0x00000000,
    (unsigned int)addrLow_Events_DeactivateActor, 0x00000000, 0x3EDF9547, 0x3EDE6595, 0x00000000, 0x00000000,
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
