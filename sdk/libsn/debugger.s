.set gp=64
.set fp=64

#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

#if !VERSION_DE
LEAF(Libgultra_DispatchExceptionVectors)
#if VERSION_EU
    xori    v0, v1, 0x2561
    swr     a1, 0x7728(t1)
#elif VERSION_US
    bltz    t0, 1f
    sll     zero, a0, 0
#else
    ldc1    $f21, 0xA0(sp)
    ldc1    $f20, 0x98(sp)
#endif
    mtc0    k0, C0_ERROR_EPC
    lui     k0, %hi(Libgultra_TrwExceptionHandler_Address)
    addiu   k0, k0, %lo(Libgultra_TrwExceptionHandler_Address)
    jr      k0
    nop
    nop
    nop
#if VERSION_US
1:
#endif
    nop
    nop
    nop
    lui     k0, 0x8000
    ori     k0, k0, 0x194
    jr      k0
    nop
    mtc0    k0, C0_ERROR_EPC
    lui     k0, %hi(Libgultra_TrwExceptionHandler_Address)
    addiu   k0, k0, %lo(Libgultra_TrwExceptionHandler_Address)
    jr      k0
    nop
    nop
    nop
    nop
    nop
    nop
    lui     k0, 0x8000
    ori     k0, k0, 0x14
    jr      k0
    nop
END(Libgultra_DispatchExceptionVectors)
#endif

LEAF(Libsn_InstallDebuggerExceptionHooks)
    addi    sp, sp, -0x8
    sw      ra, 0(sp)
    lui     t0, %hi(Libgultra_DebugExceptionVectorTemplateAddress)
    addiu   t0, t0, %lo(Libgultra_DebugExceptionVectorTemplateAddress)
    lui     t1, %hi(Libgultra_SavedExceptionVectorAddress)
    addiu   t1, t1, %lo(Libgultra_SavedExceptionVectorAddress)
    lui     t2, 0x8000
    ori     t2, t2, 0x180
    lui     t3, %hi(Libgultra_SavedExceptionVectorAddress)
    addiu   t3, t3, %lo(Libgultra_SavedExceptionVectorAddress)
1:
    lw      t4, 0(t2)
    lw      t5, 0(t0)
    addiu   t0, t0, 0x4
    sw      t4, 0(t1)
    addiu   t1, t1, 0x4
    sw      t5, 0(t2)
    bne     t0, t3, 1b
    addiu   t2, t2, 0x4
    lui     t0, %hi(Libgultra_DebugTlbVectorTemplateAddress)
    addiu   t0, t0, %lo(Libgultra_DebugTlbVectorTemplateAddress)
    lui     t1, %hi(Libgultra_SavedTlbVectorAddress)
    addiu   t1, t1, %lo(Libgultra_SavedTlbVectorAddress)
    lui     t2, %hi(g_tlbMissExceptionVector)
    lui     t3, %hi(Libgultra_SavedTlbVectorAddress)
    addiu   t3, t3, %lo(Libgultra_SavedTlbVectorAddress)
2:
    lw      t4, %lo(g_tlbMissExceptionVector)(t2)
    lw      t5, 0(t0)
    addiu   t0, t0, 0x4
    sw      t4, 0(t1)
    addiu   t1, t1, 0x4
    sw      t5, 0(t2)
    bne     t0, t3, 2b
    addiu   t2, t2, 0x4
    jal     Libgultra_TrwCacheFlush0
    nop
    jal     Libgultra_TrwCacheFlush1
    nop
    li      t0, -0x802
    lui     AT, %hi(g_debugExceptionStatusMask)
    sw      t0, %lo(g_debugExceptionStatusMask)(AT)
    lw      ra, 0(sp)
    jr      ra
    addi    sp, sp, 0x8
END(Libsn_InstallDebuggerExceptionHooks)

LEAF(Libgultra_TrwCacheFlush0)
    lui     t0, %hi(g_debugDataCacheLastIndex)
    addiu   t1, t0, %lo(g_debugDataCacheLastIndex)
1:
    cache   (C_IINV | CACH_PD), 0(t0)
    bne     t0, t1, 1b
    addiu   t0, t0, 0x10
    jr      ra
    nop
END(Libgultra_TrwCacheFlush0)

LEAF(Libgultra_TrwCacheFlush1)
    lui     t0, %hi(g_debugInstructionCacheLastIndex)
    addiu   t1, t0, %lo(g_debugInstructionCacheLastIndex)
1:
    cache   (C_IINV | CACH_PI), 0(t0)
    bne     t0, t1, 1b
    addiu   t0, t0, 0x20
    jr      ra
    nop
END(Libgultra_TrwCacheFlush1)

LEAF(Libgultra_TrwGetSr)
    mfc0    v0, C0_SR
    jr      ra
    nop
END(Libgultra_TrwGetSr)

LEAF(Libgultra_TrwSetSr)
    mtc0    a0, C0_SR
    jr      ra
    nop
END(Libgultra_TrwSetSr)

LEAF(Libgultra_TrwReadTlbEntry)
    addi    sp, sp, -0x10
    sw      a0, 0(sp)
    sw      a1, 0x4(sp)
    sw      a2, 0x8(sp)
    sw      a3, 0xC(sp)
    mfc0    v0, C0_ENTRYHI
    addi    a0, zero, 0x1F
    lui     a1, %hi(g_debugTlbEntryTableEnd)
    addiu   a1, a1, %lo(g_debugTlbEntryTableEnd)
1:
    mtc0    a0, C0_INX
    addi    a0, a0, -0x1
    tlbr
    nop
    nop
    nop
    nop
    mfc0    a2, C0_PAGEMASK
    mfc0    a3, C0_ENTRYHI
    sw      a2, 0(a1)
    sw      a3, 0x4(a1)
    mfc0    a2, C0_ENTRYLO0
    mfc0    a3, C0_ENTRYLO1
    sw      a2, 0x8(a1)
    sw      a3, 0xC(a1)
    bgez    a0, 1b
    addi    a1, a1, -0x10
    mtc0    v0, C0_ENTRYHI
    sw      a0, 0(sp)
    sw      a1, 0x4(sp)
    sw      a2, 0x8(sp)
    sw      a3, 0xC(sp)
    jr      ra
    addi    sp, sp, 0x10
END(Libgultra_TrwReadTlbEntry)

LEAF(Libgultra_TrwExceptionHandler)
    lui     k0, %hi(g_debugExceptionContext)
    addiu   k0, k0, %lo(g_debugExceptionContext)
    sd      AT, 0x328(k0)
    sd      v0, 0x330(k0)
    mfc0    AT, C0_CAUSE
    lw      v0, 0x338(k0)
    srl     AT, AT, 2
    andi    AT, AT, 0x1F
    beqz    AT, 2f
    srlv    v0, v0, AT
    andi    v0, v0, 0x1
    bnez    v0, 9f
    nop
1:
    ld      AT, 0x328(k0)
    ld      v0, 0x330(k0)
#if VERSION_DE
    bgez    zero, Libsn_SendHostTripleRequest+0xEC
#else
    bgez    zero, Libgultra_DispatchExceptionVectors+0x1C
#endif
    nop
2:
    mfc0    AT, C0_CAUSE
    nop
    andi    AT, AT, 0x800
    beqz    AT, 1b
    nop
3:
    lui     AT, 0xA460
    ori     AT, AT, 0x10
    lw      AT, 0(AT)
    nop
    andi    AT, AT, 0x3
    bnez    AT, 3b
    nop
    lui     AT, %hi(g_debugCartridgeHandshakeRegister)
    lw      AT, %lo(g_debugCartridgeHandshakeRegister)(AT)
    nop
    andi    AT, AT, 0xFFFF
    addi    AT, AT, -0x202
    bnez    AT, 8f
    nop
4:
    lui     AT, 0xA460
    ori     AT, AT, 0x10
    lw      AT, 0(AT)
    nop
    andi    AT, AT, 0x3
    bnez    AT, 4b
    nop
    lui     AT, 0x303
    ori     AT, AT, 0x303
    lui     v0, %hi(g_debugCartridgeHandshakeRegister)
    sw      AT, %lo(g_debugCartridgeHandshakeRegister)(v0)
5:
    lui     AT, 0xA460
    ori     AT, AT, 0x10
    lw      AT, 0(AT)
    nop
    andi    AT, AT, 0x3
    bnez    AT, 5b
    nop
    lui     v0, %hi(g_debugCartridgeHandshakeRegister)
    lw      AT, %lo(g_debugCartridgeHandshakeRegister)(v0)
    lui     v0, 0x303
    ori     v0, v0, 0x303
    sub     AT, AT, v0
    bnez    AT, 7f
    nop
    lui     AT, 0x1
    ori     AT, AT, 0x1
6:
    bnez    AT, 6b
    addi    AT, AT, -0x1
    beqz    AT, 5b
    nop
7:
    lui     AT, 0xA460
    ori     AT, AT, 0x10
    lw      AT, 0(AT)
    nop
    andi    AT, AT, 0x3
    bnez    AT, 7b
    nop
    lui     v0, %hi(g_debugCartridgeHandshakeRegister)
    sw      zero, %lo(g_debugCartridgeHandshakeRegister)(v0)
    mfc0    AT, C0_CAUSE
    nop
    ori     AT, AT, 0x100
    j       1b
    mtc0    AT, C0_CAUSE
8:
    lui     AT, 0xA460
    ori     AT, AT, 0x10
    lw      AT, 0(AT)
    nop
    andi    AT, AT, 0x3
    bnez    AT, 8b
    nop
    lui     AT, %hi(g_debugCartridgeExceptionCheckRegister)
    lw      AT, %lo(g_debugCartridgeExceptionCheckRegister)(AT)
    nop
    andi    AT, AT, 0xFFFF
    beqz    AT, 1b
    nop
    bgez    zero, 12f
    nop
9:
    li      v0, 0x9
    bne     AT, v0, 11f
    nop
    mfc0    v0, C0_EPC
    nop
    lw      v0, 0(v0)
    nop
    srl     v0, v0, 6
    addiu   AT, v0, -0x400
    bgez    AT, 14f
    nop
10:
    li      AT, 0x9
11:
    sb      AT, 0x320(k0)
    sb      zero, 0x322(k0)
12:
    li      AT, 0x1
    sw      AT, 0x33C(k0)
    ld      AT, 0x328(k0)
    ld      v0, 0x330(k0)
    sd      ra, 0xF8(k0)
    jal     Libgultra_TrwExceptionTail1
    nop
    lui     sp, %hi(g_debugExceptionStackTop)
    addiu   sp, sp, %lo(g_debugExceptionStackTop)
    jal     Libsn_ServiceHostCommands
    nop
    jal     Libgultra_TrwCacheFlush0
    nop
    jal     Libgultra_TrwCacheFlush1
    nop
    lui     k0, %hi(g_debugExceptionContext)
    addiu   k0, k0, %lo(g_debugExceptionContext)
    li      AT, 0x1
    sb      AT, 0x320(k0)
    ld      t0, 0x108(k0)
    nop
    mthi    t0
    ld      t0, 0x100(k0)
    nop
    mtlo    t0
    ld      t0, 0x178(k0)
    nop
    mtc0    t0, C0_SR
    ld      t0, 0x110(k0)
    nop
    mtc0    t0, C0_EPC
    ld      t0, 0xD0(k0)
    nop
    mtc0    t0, C0_ERROR_EPC
    ld      t0, 0x178(k0)
    lui     t1, 0x2000
    and     t1, t1, t0
    beqz    t1, 13f
    nop
    lw      t0, 0x318(k0)
    nop
    ctc1    t0, $0
    lw      t0, 0x31C(k0)
    nop
    ctc1    t0, $31
    ldc1    $f0, 0x218(k0)
    ldc1    $f2, 0x228(k0)
    ldc1    $f4, 0x238(k0)
    ldc1    $f6, 0x248(k0)
    ldc1    $f8, 0x258(k0)
    ldc1    $f10, 0x268(k0)
    ldc1    $f12, 0x278(k0)
    ldc1    $f14, 0x288(k0)
    ldc1    $f16, 0x298(k0)
    ldc1    $f18, 0x2A8(k0)
    ldc1    $f20, 0x2B8(k0)
    ldc1    $f22, 0x2C8(k0)
    ldc1    $f24, 0x2D8(k0)
    ldc1    $f26, 0x2E8(k0)
    ldc1    $f28, 0x2F8(k0)
    ldc1    $f30, 0x308(k0)
    ld      t0, 0x178(k0)
    lui     t1, 0x400
    and     t1, t1, t0
    beqz    t1, 13f
    nop
    ldc1    $f1, 0x220(k0)
    ldc1    $f3, 0x230(k0)
    ldc1    $f5, 0x240(k0)
    ldc1    $f7, 0x250(k0)
    ldc1    $f9, 0x260(k0)
    ldc1    $f11, 0x270(k0)
    ldc1    $f13, 0x280(k0)
    ldc1    $f15, 0x290(k0)
    ldc1    $f17, 0x2A0(k0)
    ldc1    $f19, 0x2B0(k0)
    ldc1    $f21, 0x2C0(k0)
    ldc1    $f23, 0x2D0(k0)
    ldc1    $f25, 0x2E0(k0)
    ldc1    $f27, 0x2F0(k0)
    ldc1    $f29, 0x300(k0)
    ldc1    $f31, 0x310(k0)
13:
    ld      AT, 0x8(k0)
    ld      v0, 0x10(k0)
    ld      v1, 0x18(k0)
    ld      a0, 0x20(k0)
    ld      a1, 0x28(k0)
    ld      a2, 0x30(k0)
    ld      a3, 0x38(k0)
    ld      t0, 0x40(k0)
    ld      t1, 0x48(k0)
    ld      t2, 0x50(k0)
    ld      t3, 0x58(k0)
    ld      t4, 0x60(k0)
    ld      t5, 0x68(k0)
    ld      t6, 0x70(k0)
    ld      t7, 0x78(k0)
    ld      s0, 0x80(k0)
    ld      s1, 0x88(k0)
    ld      s2, 0x90(k0)
    ld      s3, 0x98(k0)
    ld      s4, 0xA0(k0)
    ld      s5, 0xA8(k0)
    ld      s6, 0xB0(k0)
    ld      s7, 0xB8(k0)
    ld      t8, 0xC0(k0)
    ld      t9, 0xC8(k0)
    ld      k1, 0xD8(k0)
    ld      gp, 0xE0(k0)
    ld      sp, 0xE8(k0)
    ld      fp, 0xF0(k0)
    ld      ra, 0xF8(k0)
    sw      zero, 0x33C(k0)
    mfc0    k0, C0_ERROR_EPC
    eret
14:
    addiu   AT, v0, -0x409
    bgez    AT, 10b
    nop
    lui     AT, %hi(jtbl_TrwExceptionBreakCodes)
    addiu   AT, AT, %lo(jtbl_TrwExceptionBreakCodes)
    addiu   v0, v0, -0x400
    sll     v0, v0, 2
    addu    v0, v0, AT
    lw      v0, 0(v0)
    nop
    jr      v0
    nop
END(Libgultra_TrwExceptionHandler)

