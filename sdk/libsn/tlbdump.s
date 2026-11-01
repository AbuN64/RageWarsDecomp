#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(Libgultra_CaptureTlbMappingTable)
    add     v0, zero, zero
    addi    a1, zero, 0x1E
    lui     a0, %hi(g_capturedTlbMappings)
    addiu   a0, a0, %lo(g_capturedTlbMappings)
#if VERSION_EU
    addi    a2, zero, 0x15E
#elif VERSION_EU_X
    addi    a2, zero, 0x158
#elif VERSION_US
    addi    a2, zero, 0x14C
#elif VERSION_US_REV1
    addi    a2, zero, 0x156
#else
    addi    a2, zero, 0x14E
#endif
1:
    mtc0    v0, C0_INX
    tlbr
    nop
    nop
    nop
    nop
    mfc0    v1, C0_PAGEMASK
    nop
    srl     v1, v1, 13
    sh      v1, 0(a0)
    mfc0    v1, C0_ENTRYHI
    nop
    srl     v1, v1, 12
    sh      v1, 0x2(a0)
    mfc0    v1, C0_ENTRYLO0
    nop
    srl     v1, v1, 6
    sub     v1, v1, a2
    sh      v1, 0x4(a0)
    mfc0    v1, C0_ENTRYLO1
    nop
    srl     v1, v1, 6
    sub     v1, v1, a2
    sh      v1, 0x6(a0)
    addi    a0, a0, 0x8
    bne     a1, v0, 1b
    addi    v0, v0, 0x1
    jr      ra
    nop
END(Libgultra_CaptureTlbMappingTable)
