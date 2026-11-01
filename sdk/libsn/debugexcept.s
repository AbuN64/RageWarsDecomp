.set gp=64
.set fp=64

#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(Libgultra_ReturnFromDebugException)
    lw      AT, 0x33C(k0)
    nop
    bnez    AT, 6f
    nop
    li      AT, 0x64
1:
    bnez    AT, 1b
    addi    AT, AT, -0x1
    lui     AT, 0xA460
    ori     AT, AT, 0x10
2:
    lw      v0, 0(AT)
    nop
    andi    v0, v0, 0x3
    bnez    v0, 2b
    nop
    lui     AT, %hi(g_debugCartridgeExceptionCheckRegister)
    lw      AT, %lo(g_debugCartridgeExceptionCheckRegister)(AT)
    nop
    beqz    AT, 6f
    nop
    bgez    zero, Libgultra_TrwExceptionHandler+0x1B8
    nop
    li      AT, -0x1
    j       Libgultra_TrwExceptionHandler+0x1B0
    nop
    li      AT, -0x1
    j       Libgultra_TrwExceptionHandler+0x1B0
    nop
    j       Libgultra_TrwExceptionHandler+0x1AC
    nop
    sd      v1, 0x18(k0)
    sd      a0, 0x20(k0)
    sd      ra, 0xF8(k0)
    bal     3f
    nop
    ld      ra, 0xF8(k0)
    ld      a0, 0x20(k0)
    bgez    zero, 6f
    ld      v1, 0x18(k0)
3:
    lui     v1, 0x8000
    ori     v1, v1, 0x180
    lui     v0, %hi(Libgultra_SavedExceptionVectorAddress)
    addiu   v0, v0, %lo(Libgultra_SavedExceptionVectorAddress)
    addi    a0, v0, 0x14
4:
    lw      AT, 0(v0)
    addi    v0, v0, 0x4
    sw      AT, 0(v1)
    addi    v1, v1, 0x4
    bne     v0, a0, 4b
    nop
    lui     v1, %hi(g_tlbMissExceptionVector)
    lui     v0, %hi(Libgultra_SavedTlbVectorAddress)
    addiu   v0, v0, %lo(Libgultra_SavedTlbVectorAddress)
    addi    a0, v0, 0x14
5:
    lw      AT, 0(v0)
    addi    v0, v0, 0x4
    sw      AT, %lo(g_tlbMissExceptionVector)(v1)
    addi    v1, v1, 0x4
    bne     v0, a0, 5b
    nop
    jal     Libgultra_TrwCacheFlush0
    nop
    jal     Libgultra_TrwCacheFlush1
    nop
    jr      ra
    nop
    sw      a0, 0x338(k0)
    j       6f
    nop
    mfc0    AT, C0_EPC
    nop
    addiu   AT, AT, 0x4
    mtc0    AT, C0_EPC
    li      AT, 0x0
    j       Libgultra_TrwExceptionHandler+0x1B0
    nop
    lui     v0, %hi(Libsn_InitializeHostMemoryAccess_Address)
    addiu   v0, v0, %lo(Libsn_InitializeHostMemoryAccess_Address)
    j       7f
    nop
6:
    ld      v0, 0x330(k0)
7:
    mfc0    AT, C0_EPC
    nop
    addiu   AT, AT, 0x4
    mtc0    AT, C0_EPC
    ld      AT, 0x328(k0)
    mfc0    k0, C0_ERROR_EPC
    eret
END(Libgultra_ReturnFromDebugException)

LEAF(Libgultra_TrwExceptionTail1)
    sd      zero, 0(k0)
    sd      AT, 0x8(k0)
    sd      v0, 0x10(k0)
    sd      v1, 0x18(k0)
    sd      a0, 0x20(k0)
    sd      a1, 0x28(k0)
    sd      a2, 0x30(k0)
    sd      a3, 0x38(k0)
    sd      t0, 0x40(k0)
    sd      t1, 0x48(k0)
    sd      t2, 0x50(k0)
    sd      t3, 0x58(k0)
    sd      t4, 0x60(k0)
    sd      t5, 0x68(k0)
    sd      t6, 0x70(k0)
    sd      t7, 0x78(k0)
    sd      s0, 0x80(k0)
    sd      s1, 0x88(k0)
    sd      s2, 0x90(k0)
    sd      s3, 0x98(k0)
    sd      s4, 0xA0(k0)
    sd      s5, 0xA8(k0)
    sd      s6, 0xB0(k0)
    sd      s7, 0xB8(k0)
    sd      t8, 0xC0(k0)
    sd      t9, 0xC8(k0)
    sd      k1, 0xD8(k0)
    sd      gp, 0xE0(k0)
    sd      sp, 0xE8(k0)
    sd      fp, 0xF0(k0)
    mfc0    t0, C0_ERROR_EPC
    sd      t0, 0xD0(k0)
    mflo    t0
    sd      t0, 0x100(k0)
    mfhi    t0
    sd      t0, 0x108(k0)
    mfc0    t0, C0_INX
    nop
    sd      t0, 0x118(k0)
    mfc0    t0, C0_RAND
    nop
    sd      t0, 0x120(k0)
    mfc0    t0, C0_ENTRYLO0
    nop
    sd      t0, 0x128(k0)
    mfc0    t0, C0_ENTRYLO1
    nop
    sd      t0, 0x130(k0)
    mfc0    t0, C0_CONTEXT
    nop
    sd      t0, 0x138(k0)
    mfc0    t0, C0_PAGEMASK
    nop
    sd      t0, 0x140(k0)
    mfc0    t0, C0_WIRED
    nop
    sd      t0, 0x148(k0)
    mfc0    t0, $7
    nop
    sd      t0, 0x150(k0)
    mfc0    t0, C0_BADVADDR
    nop
    sd      t0, 0x158(k0)
    mfc0    t0, C0_COUNT
    nop
    sd      t0, 0x160(k0)
    mfc0    t0, C0_ENTRYHI
    nop
    sd      t0, 0x168(k0)
    mfc0    t0, C0_COMPARE
    nop
    sd      t0, 0x170(k0)
    mfc0    t0, C0_SR
    nop
    sd      t0, 0x178(k0)
    mfc0    t0, C0_CAUSE
    nop
    sd      t0, 0x180(k0)
    mfc0    t0, C0_EPC
    nop
    sd      t0, 0x188(k0)
    mfc0    t0, C0_PRID
    nop
    sd      t0, 0x190(k0)
    mfc0    t0, C0_CONFIG
    nop
    sd      t0, 0x198(k0)
    mfc0    t0, C0_LLADDR
    nop
    sd      t0, 0x1A0(k0)
    mfc0    t0, C0_WATCHLO
    nop
    sd      t0, 0x1A8(k0)
    mfc0    t0, C0_WATCHHI
    nop
    sd      t0, 0x1B0(k0)
    mfc0    t0, $20
    nop
    sd      t0, 0x1B8(k0)
    mfc0    t0, $21
    nop
    sd      t0, 0x1C0(k0)
    mfc0    t0, $22
    nop
    sd      t0, 0x1C8(k0)
    mfc0    t0, $23
    nop
    sd      t0, 0x1D0(k0)
    mfc0    t0, $24
    nop
    sd      t0, 0x1D8(k0)
    mfc0    t0, $25
    nop
    sd      t0, 0x1E0(k0)
    mfc0    t0, C0_ECC
    nop
    sd      t0, 0x1E8(k0)
    mfc0    t0, C0_CACHE_ERR
    nop
    sd      t0, 0x1F0(k0)
    mfc0    t0, C0_TAGLO
    nop
    sd      t0, 0x1F8(k0)
    mfc0    t0, C0_TAGHI
    nop
    sd      t0, 0x200(k0)
    mfc0    t0, C0_ERROR_EPC
    nop
    sd      t0, 0x208(k0)
    mfc0    t0, $31
    nop
    sd      t0, 0x210(k0)
    ld      t0, 0x178(k0)
    lui     t1, 0x2000
    and     t1, t1, t0
    beqz    t1, 1f
    nop
    cfc1    t0, $0
    nop
    sw      t0, 0x318(k0)
    cfc1    t0, $31
    nop
    sw      t0, 0x31C(k0)
    sdc1    $f0, 0x218(k0)
    sdc1    $f2, 0x228(k0)
    sdc1    $f4, 0x238(k0)
    sdc1    $f6, 0x248(k0)
    sdc1    $f8, 0x258(k0)
    sdc1    $f10, 0x268(k0)
    sdc1    $f12, 0x278(k0)
    sdc1    $f14, 0x288(k0)
    sdc1    $f16, 0x298(k0)
    sdc1    $f18, 0x2A8(k0)
    sdc1    $f20, 0x2B8(k0)
    sdc1    $f22, 0x2C8(k0)
    sdc1    $f24, 0x2D8(k0)
    sdc1    $f26, 0x2E8(k0)
    sdc1    $f28, 0x2F8(k0)
    sdc1    $f30, 0x308(k0)
    ld      t0, 0x178(k0)
    lui     t1, 0x400
    and     t1, t1, t0
    beqz    t1, 1f
    nop
    sdc1    $f1, 0x220(k0)
    sdc1    $f3, 0x230(k0)
    sdc1    $f5, 0x240(k0)
    sdc1    $f7, 0x250(k0)
    sdc1    $f9, 0x260(k0)
    sdc1    $f11, 0x270(k0)
    sdc1    $f13, 0x280(k0)
    sdc1    $f15, 0x290(k0)
    sdc1    $f17, 0x2A0(k0)
    sdc1    $f19, 0x2B0(k0)
    sdc1    $f21, 0x2C0(k0)
    sdc1    $f23, 0x2D0(k0)
    sdc1    $f25, 0x2E0(k0)
    sdc1    $f27, 0x2F0(k0)
    sdc1    $f29, 0x300(k0)
    sdc1    $f31, 0x310(k0)
1:
    ld      t0, 0x178(k0)
    nop
    andi    t0, t0, 0x4
    bnez    t0, 2f
    nop
    ld      t0, 0x188(k0)
    j       3f
    nop
2:
    ld      t0, 0x208(k0)
    nop
3:
    sd      t0, 0x110(k0)
    jr      ra
    nop
END(Libgultra_TrwExceptionTail1)
