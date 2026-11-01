#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record0;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record1;
    struct { u8 opcode; SnLe16 offset; } record2;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record3;
    u8 followingRecordFragment[6];
} k_PortalAfterInitPlayerMode __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 5 },
    { 52, SN_LE16(0), 0 },
    { 50, SN_LE16(20) },
    { 52, SN_LE16(20), 10 },
    { 0x0A, 0x5C, 0x30, 0x00, 0x2C, 0x04 }
};
typedef char k_PortalAfterInitPlayerModeSizeCheck[(sizeof(k_PortalAfterInitPlayerMode) == 21) ? 1 : -1];
#endif
