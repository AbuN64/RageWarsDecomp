.set gp=64
.set fp=64

#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(__osExceptionPreamble)
#if VERSION_EU
    addiu   sp, sp, 0x40
    addu    a2, zero, zero
    lui     k0, %hi(__osExceptionKuseg)
    addiu   k0, k0, %lo(__osExceptionKuseg)
#elif VERSION_EU_X || VERSION_US_REV1
    sw      v0, 0(s0)
    jal     __osLeoAbnormalResume
    lui     k0, %hi(__osExceptionKuseg)
    addiu   k0, k0, %lo(__osExceptionKuseg)
#elif VERSION_US
    lui     k0, %hi(__osExceptionKuseg)
    addiu   k0, k0, %lo(__osExceptionKuseg)
#endif
    jr      k0
    nop
#if VERSION_DE
    lui     k0, %hi(__osExceptionKuseg)
    addiu   k0, k0, %lo(__osExceptionKuseg)
    jr      k0
    nop
    lui     k0, %hi(__osThreadSave)
    addiu   k0, k0, %lo(__osThreadSave)
#elif VERSION_US
    lui     k0, 0x8015
    addiu   k0, k0, -0x7430
#else
    lui     k0, %hi(__osThreadSave)
    addiu   k0, k0, %lo(__osThreadSave)
#endif
    sd      AT, 0x20(k0)
    mfc0    k1, C0_SR
    nop
    sw      k1, 0x118(k0)
    li      AT, -0x4
    and     k1, k1, AT
    mtc0    k1, C0_SR
    sd      t0, 0x58(k0)
    sd      t1, 0x60(k0)
    sd      t2, 0x68(k0)
    sw      zero, 0x18(k0)
    mfc0    t0, C0_CAUSE
    addu    t0, k0, zero
    lui     k0, %hi(__osRunningThread)
    lw      k0, %lo(__osRunningThread)(k0)
    ld      t1, 0x20(t0)
    ld      t2, 0x118(t0)
    sd      t1, 0x20(k0)
    sd      t2, 0x118(k0)
    ld      t1, 0x58(t0)
    ld      t2, 0x60(t0)
    sd      t1, 0x58(k0)
    sd      t2, 0x60(k0)
    ld      t1, 0x68(t0)
    sd      v0, 0x28(k0)
    sd      t1, 0x68(k0)
    sd      v1, 0x30(k0)
    sd      a0, 0x38(k0)
    sd      a1, 0x40(k0)
    sd      a2, 0x48(k0)
    sd      a3, 0x50(k0)
    sd      t3, 0x70(k0)
    sd      t4, 0x78(k0)
    sd      t5, 0x80(k0)
    sd      t6, 0x88(k0)
    sd      t7, 0x90(k0)
    sd      s0, 0x98(k0)
    sd      s1, 0xA0(k0)
    sd      s2, 0xA8(k0)
    sd      s3, 0xB0(k0)
    sd      s4, 0xB8(k0)
    sd      s5, 0xC0(k0)
    sd      s6, 0xC8(k0)
    sd      s7, 0xD0(k0)
    sd      t8, 0xD8(k0)
    sd      t9, 0xE0(k0)
    sd      gp, 0xE8(k0)
    sd      sp, 0xF0(k0)
    sd      fp, 0xF8(k0)
    sd      ra, 0x100(k0)
    mflo    t0
    sd      t0, 0x108(k0)
    mfhi    t0
    sd      t0, 0x110(k0)
    lw      k1, 0x118(k0)
    nop
    andi    t1, k1, 0xFF00
    beqz    t1, 1f
    nop
    lui     t0, %hi(__OSGlobalIntMask)
    addiu   t0, t0, %lo(__OSGlobalIntMask)
    lw      t0, 0(t0)
    nop
    li      AT, -0x1
    xor     t2, t0, AT
    andi    t2, t2, 0xFF00
    or      t4, t1, t2
    lui     AT, 0xFFFF
    ori     AT, AT, 0xFF
    and     t3, k1, AT
    or      t3, t3, t4
    sw      t3, 0x118(k0)
    andi    t0, t0, 0xFF00
    and     t1, t1, t0
    lui     AT, 0xFFFF
    ori     AT, AT, 0xFF
    and     k1, k1, AT
    or      k1, k1, t1
1:
    lui     t1, %hi(MI_INTERRUPT_MASK_REGISTER)
    lw      t1, %lo(MI_INTERRUPT_MASK_REGISTER)(t1)
    nop
    beqz    t1, 2f
    nop
    lui     t0, %hi(__OSGlobalIntMask)
    addiu   t0, t0, %lo(__OSGlobalIntMask)
    lw      t0, 0(t0)
    nop
    srl     t0, t0, 16
    li      AT, -0x1
    xor     t0, t0, AT
    lw      t4, 0x128(k0)
    andi    t0, t0, 0x3F
    and     t0, t0, t4
    or      t1, t1, t0
2:
    mfc0    t0, C0_EPC
    sw      t1, 0x128(k0)
    sw      t0, 0x11C(k0)
    lw      t0, 0x18(k0)
    nop
    beqz    t0, 3f
    nop
    cfc1    t0, $31
    nop
    sw      t0, 0x12C(k0)
    sdc1    $f0, 0x130(k0)
    sdc1    $f2, 0x138(k0)
    sdc1    $f4, 0x140(k0)
    sdc1    $f6, 0x148(k0)
    sdc1    $f8, 0x150(k0)
    sdc1    $f10, 0x158(k0)
    sdc1    $f12, 0x160(k0)
    sdc1    $f14, 0x168(k0)
    sdc1    $f16, 0x170(k0)
    sdc1    $f18, 0x178(k0)
    sdc1    $f20, 0x180(k0)
    sdc1    $f22, 0x188(k0)
    sdc1    $f24, 0x190(k0)
    sdc1    $f26, 0x198(k0)
    sdc1    $f28, 0x1A0(k0)
    lw      t1, 0x118(k0)
    sdc1    $f30, 0x1A8(k0)
    lui     AT, 0x400
    and     t1, t1, AT
    beqz    t1, 3f
    nop
    sdc1    $f1, 0x1B0(k0)
    sdc1    $f3, 0x1B8(k0)
    sdc1    $f5, 0x1C0(k0)
    sdc1    $f7, 0x1C8(k0)
    sdc1    $f9, 0x1D0(k0)
    sdc1    $f11, 0x1D8(k0)
    sdc1    $f13, 0x1E0(k0)
    sdc1    $f15, 0x1E8(k0)
    sdc1    $f17, 0x1F0(k0)
    sdc1    $f19, 0x1F8(k0)
    sdc1    $f21, 0x200(k0)
    sdc1    $f23, 0x208(k0)
    sdc1    $f25, 0x210(k0)
    sdc1    $f27, 0x218(k0)
    sdc1    $f29, 0x220(k0)
    sdc1    $f31, 0x228(k0)
3:
    mfc0    t0, C0_CAUSE
    li      t1, 0x2
    sw      t0, 0x120(k0)
    sh      t1, 0x10(k0)
    andi    t1, t0, 0x7C
    li      t2, 0x24
    beq     t1, t2, 15f
    li      t2, 0x2C
    beq     t1, t2, handle_CpU
    li      t2, 0x0
    bne     t1, t2, panic
    and     s0, k1, t0
4:
    andi    t1, s0, 0xFF00
    srl     t2, t1, 12
    bnez    t2, 5f
    nop
    srl     t2, t1, 8
    addi    t2, t2, 0x10
5:
#if VERSION_EU
    lui     AT, %hi(g_interruptDispatchOffsetsEu)
#elif VERSION_EU_X
    lui     AT, %hi(g_interruptDispatchOffsetsEuX)
#elif VERSION_US_REV1
    lui     AT, 0x800D
#else
    lui     AT, 0x800C
#endif
    addu    AT, AT, t2
#if VERSION_EU
    lbu     t2, %lo(g_interruptDispatchOffsetsEu)(AT)
    lui     AT, %hi(g_interruptDispatchHandlersEu)
#elif VERSION_EU_X
    lbu     t2, %lo(g_interruptDispatchOffsetsEuX)(AT)
    lui     AT, 0x800D
#elif VERSION_US
    lbu     t2, 0x7940(AT)
    lui     AT, 0x800C
#elif VERSION_US_REV1
    lbu     t2, -0x3390(AT)
    lui     AT, 0x800D
#else
    lbu     t2, 0x7A20(AT)
    lui     AT, 0x800C
#endif
    addu    AT, AT, t2
#if VERSION_EU
    lw      t2, %lo(g_interruptDispatchHandlersEu)(AT)
#elif VERSION_EU_X
    lw      t2, -0x7000(AT)
#elif VERSION_US
    lw      t2, 0x7960(AT)
#elif VERSION_US_REV1
    lw      t2, -0x3370(AT)
#else
    lw      t2, 0x7A40(AT)
#endif
    nop
    jr      t2
    nop
    li      AT, -0x2001
    and     s0, s0, AT
    bgez    zero, 4b
    nop
    li      AT, -0x4001
    and     s0, s0, AT
    bgez    zero, 4b
    nop
    mfc0    t1, C0_COMPARE
    lui     AT, 0xFFFF
    ori     AT, AT, 0x7FFF
    and     s0, s0, AT
    mtc0    t1, C0_COMPARE
    jal     send_mesg
    li      a0, 0x18
    bgez    zero, 4b
    nop
    li      a0, 0x10
    li      AT, -0x801
    and     s0, s0, AT
#if VERSION_EU
    lui     sp, %hi(g_exceptionStackTopEu)
    addiu   sp, sp, %lo(g_exceptionStackTopEu)
#elif VERSION_EU_X
    lui     sp, %hi(g_exceptionStackTopEuX)
    addiu   sp, sp, %lo(g_exceptionStackTopEuX)
#elif VERSION_US
    lui     sp, 0x8014
    addiu   sp, sp, 0x7BD0
#elif VERSION_US_REV1
    lui     sp, %hi(g_exceptionStackTopUsRev1)
    addiu   sp, sp, %lo(g_exceptionStackTopUsRev1)
#else
    lui     sp, %hi(g_exceptionStackTopDe)
    addiu   sp, sp, %lo(g_exceptionStackTopDe)
#endif
    addiu   sp, sp, 0xFF0
    li      t2, 0x4
#if VERSION_DE || VERSION_US
    lui     AT, 0x800D
#else
    lui     AT, 0x800E
#endif
    addu    AT, AT, t2
#if VERSION_EU
    lw      t2, 0x5910(AT)
#elif VERSION_EU_X
    lw      t2, 0xAD0(AT)
#elif VERSION_US
    lw      t2, 0x3F40(AT)
#elif VERSION_US_REV1
    lw      t2, -0x6D40(AT)
#else
    lw      t2, 0x5290(AT)
#endif
    nop
    beqz    t2, 6f
    nop
    jalr    t2
    li      a0, 0x10
    beqz    v0, 6f
    nop
    bgez    zero, 16f
    nop
6:
    jal     send_mesg
    nop
    bgez    zero, 4b
    nop
    lui     s1, 0xA430
    lw      s1, 0x8(s1)
    lui     t0, %hi(__OSGlobalIntMask)
    addiu   t0, t0, %lo(__OSGlobalIntMask)
    lw      t0, 0(t0)
    nop
    srl     t0, t0, 16
    and     s1, s1, t0
    andi    t1, s1, 0x1
    beqz    t1, 8f
    nop
    andi    s1, s1, 0x3E
    lui     t4, 0xA404
    lw      t4, 0x10(t4)
    ori     t1, zero, 0x8008
    lui     AT, 0xA404
    sw      t1, 0x10(AT)
    andi    t4, t4, 0x300
    beqz    t4, 7f
    nop
    jal     send_mesg
    li      a0, 0x20
    beqz    s1, 13f
    nop
    bgez    zero, 8f
    nop
7:
    jal     send_mesg
    li      a0, 0x58
    beqz    s1, 13f
    nop
8:
    andi    t1, s1, 0x8
    nop
    beqz    t1, 9f
    andi    s1, s1, 0x37
    lui     AT, 0xA440
    sw      zero, 0x10(AT)
    jal     send_mesg
    li      a0, 0x38
    beqz    s1, 13f
    nop
9:
    andi    t1, s1, 0x4
    beqz    t1, 10f
    nop
    andi    s1, s1, 0x3B
    li      t1, 0x1
    lui     AT, 0xA450
    sw      t1, 0xC(AT)
    jal     send_mesg
    li      a0, 0x30
    beqz    s1, 13f
    nop
10:
    andi    t1, s1, 0x2
    beqz    t1, 11f
    nop
    andi    s1, s1, 0x3D
    lui     AT, 0xA480
    sw      zero, 0x18(AT)
    jal     send_mesg
    li      a0, 0x28
    beqz    s1, 13f
    nop
11:
    andi    t1, s1, 0x10
    beqz    t1, 12f
    nop
    andi    s1, s1, 0x2F
    li      t1, 0x2
    lui     AT, 0xA460
    sw      t1, 0x10(AT)
    jal     send_mesg
    li      a0, 0x40
    beqz    s1, 13f
    nop
12:
    andi    t1, s1, 0x20
    beqz    t1, 13f
    nop
    andi    s1, s1, 0x1F
    li      t1, 0x800
    lui     AT, 0xA430
    sw      t1, 0(AT)
    jal     send_mesg
    li      a0, 0x48
13:
    li      AT, -0x401
    and     s0, s0, AT
    bgez    zero, 4b
    nop
    lw      k1, 0x118(k0)
#if VERSION_EU
    lui     t1, %hi(g_preNmiShutdownFlagEu)
    addiu   t1, t1, %lo(g_preNmiShutdownFlagEu)
#elif VERSION_EU_X
    lui     t1, %hi(g_preNmiShutdownFlagEuX)
    addiu   t1, t1, %lo(g_preNmiShutdownFlagEuX)
#elif VERSION_US
    lui     t1, 0x800D
    addiu   t1, t1, 0x3F04
#elif VERSION_US_REV1
    lui     t1, %hi(g_preNmiShutdownFlagUsRev1)
    addiu   t1, t1, %lo(g_preNmiShutdownFlagUsRev1)
#else
    lui     t1, %hi(g_preNmiShutdownFlagDe)
    addiu   t1, t1, %lo(g_preNmiShutdownFlagDe)
#endif
    li      AT, -0x1001
    and     k1, k1, AT
    lw      t2, 0(t1)
    li      AT, -0x1001
    and     s0, s0, AT
    beqz    t2, 14f
    sw      k1, 0x118(k0)
    bgez    zero, 16f
    nop
14:
    li      t2, 0x1
    sw      t2, 0(t1)
    jal     send_mesg
    li      a0, 0x70
    lui     t2, %hi(__osRunQueue)
    lw      t2, %lo(__osRunQueue)(t2)
    li      AT, -0x1001
    and     s0, s0, AT
    lw      k1, 0x118(t2)
    nop
    li      AT, -0x1001
    and     k1, k1, AT
    bgez    zero, 16f
    sw      k1, 0x118(t2)
    li      AT, -0x201
    and     t0, t0, AT
    mtc0    t0, C0_CAUSE
    li      AT, -0x201
    and     s0, s0, AT
    jal     send_mesg
    li      a0, 0x8
    bgez    zero, 4b
    nop
    li      AT, -0x101
    and     t0, t0, AT
    mtc0    t0, C0_CAUSE
    li      AT, -0x101
    and     s0, s0, AT
    jal     send_mesg
    li      a0, 0x0
    bgez    zero, 4b
    nop
15:
    li      t1, 0x1
    sh      t1, 0x12(k0)
    jal     send_mesg
    li      a0, 0x50
    bgez    zero, 16f
    nop
16:
    lui     t2, %hi(__osRunQueue)
    lw      t2, %lo(__osRunQueue)(t2)
    lw      t1, 0x4(k0)
    lw      t3, 0x4(t2)
    nop
    slt     AT, t1, t3
    beqz    AT, redispatch
    nop
    lui     a0, %hi(__osRunQueue)
    addiu   a0, a0, %lo(__osRunQueue)
    jal     __osEnqueueThread
    addu    a1, k0, zero
    j       __osDispatchThread
    nop
redispatch:
    lui     t1, %hi(__osRunQueue)
    addiu   t1, t1, %lo(__osRunQueue)
    lw      t2, 0(t1)
    nop
    sw      t2, 0(k0)
    j       __osDispatchThread
    sw      k0, 0(t1)
panic:
    lui     AT, %hi(__osFaultedThread)
    sw      k0, %lo(__osFaultedThread)(AT)
    li      t1, 0x1
    sh      t1, 0x10(k0)
    li      t1, 0x2
    mfc0    t2, C0_BADVADDR
    sh      t1, 0x12(k0)
    sw      t2, 0x124(k0)
    jal     send_mesg
    li      a0, 0x60
    j       __osDispatchThread
    nop
END(__osExceptionPreamble)

/* libultra exceptasm.s send_mesg: queue the message for the event in $a0 and wake a blocked receiver.
Handwritten: the caller is parked in $s2 and the routine returns with jr $s2. */
LEAF(send_mesg)
    addu    s2, ra, zero
    lui     t2, %hi(g_osEventMessageBindings)
    addiu   t2, t2, %lo(g_osEventMessageBindings)
    addu    t2, t2, a0
    lw      t1, 0(t2)
    nop
    beqz    t1, 3f
    nop
    lw      t3, 0x8(t1)
    lw      t4, 0x10(t1)
    nop
    slt     AT, t3, t4
    beqz    AT, 3f
    nop
    lw      t5, 0xC(t1)
    nop
    addu    t5, t5, t3
    div     zero, t5, t4
    bnez    t4, 1f
    nop
    break   7
1:
    li      AT, -0x1
    bne     t4, AT, 2f
    lui     AT, 0x8000
    bne     t5, AT, 2f
    nop
    break   6
2:
    mfhi    t5
    lw      t4, 0x14(t1)
    sll     t5, t5, 2
    addu    t4, t4, t5
    lw      t5, 0x4(t2)
    nop
    sw      t5, 0(t4)
    addiu   t2, t3, 0x1
    sw      t2, 0x8(t1)
    lw      t2, 0(t1)
    nop
    lw      t3, 0(t2)
    nop
    beqz    t3, 3f
    nop
    jal     __osPopThread
    addu    a0, t1, zero
    addu    t2, v0, zero
    lui     a0, %hi(__osRunQueue)
    addiu   a0, a0, %lo(__osRunQueue)
    jal     __osEnqueueThread
    addu    a1, t2, zero
3:
    jr      s2
    nop
END(send_mesg)

LEAF(handle_CpU)
    lui     AT, 0x3000
    and     t1, t0, AT
    srl     t1, t1, 28
    li      t2, 0x1
    bne     t1, t2, panic
    li      t1, 0x1
    sw      t1, 0x18(k0)
    lw      k1, 0x118(k0)
    nop
    lui     AT, 0x2000
    or      k1, k1, AT
    sw      k1, 0x118(k0)
    bgez    zero, redispatch
    nop
END(handle_CpU)

LEAF(__osEnqueueAndYield)
    lui     a1, %hi(__osRunningThread)
    lw      a1, %lo(__osRunningThread)(a1)
    mfc0    t0, C0_SR
    nop
    ori     t0, t0, 0x2
    sw      t0, 0x118(a1)
    sd      s0, 0x98(a1)
    sd      s1, 0xA0(a1)
    sd      s2, 0xA8(a1)
    sd      s3, 0xB0(a1)
    sd      s4, 0xB8(a1)
    sd      s5, 0xC0(a1)
    sd      s6, 0xC8(a1)
    sd      s7, 0xD0(a1)
    sd      gp, 0xE8(a1)
    sd      sp, 0xF0(a1)
    sd      fp, 0xF8(a1)
    sd      ra, 0x100(a1)
    sw      ra, 0x11C(a1)
    lw      k1, 0x18(a1)
    nop
    beqz    k1, 1f
    nop
    cfc1    k1, $31
    nop
    sw      k1, 0x12C(a1)
    sdc1    $f0, 0x130(a1)
    sdc1    $f2, 0x138(a1)
    sdc1    $f4, 0x140(a1)
    sdc1    $f8, 0x150(a1)
    sdc1    $f10, 0x158(a1)
    sdc1    $f12, 0x160(a1)
    sdc1    $f14, 0x168(a1)
    sdc1    $f16, 0x170(a1)
    sdc1    $f18, 0x178(a1)
    sdc1    $f20, 0x180(a1)
    sdc1    $f22, 0x188(a1)
    sdc1    $f24, 0x190(a1)
    sdc1    $f26, 0x198(a1)
    sdc1    $f28, 0x1A0(a1)
    sdc1    $f30, 0x1A8(a1)
    lw      k1, 0x118(a1)
    nop
    lui     AT, 0x400
    and     k1, k1, AT
    beqz    k1, 1f
    nop
    sdc1    $f1, 0x1B0(a1)
    sdc1    $f3, 0x1B8(a1)
    sdc1    $f5, 0x1C0(a1)
    sdc1    $f7, 0x1C8(a1)
    sdc1    $f9, 0x1D0(a1)
    sdc1    $f11, 0x1D8(a1)
    sdc1    $f13, 0x1E0(a1)
    sdc1    $f15, 0x1E8(a1)
    sdc1    $f17, 0x1F0(a1)
    sdc1    $f19, 0x1F8(a1)
    sdc1    $f21, 0x200(a1)
    sdc1    $f23, 0x208(a1)
    sdc1    $f25, 0x210(a1)
    sdc1    $f27, 0x218(a1)
    sdc1    $f29, 0x220(a1)
    sdc1    $f31, 0x228(a1)
1:
    lw      k1, 0x118(a1)
    nop
    andi    t1, k1, 0xFF00
    beqz    t1, 2f
    nop
    lui     t0, %hi(__OSGlobalIntMask)
    addiu   t0, t0, %lo(__OSGlobalIntMask)
    nop
    lw      t0, 0(t0)
    nop
    li      AT, -0x1
    xor     t0, t0, AT
    andi    t0, t0, 0xFF00
    or      t1, t1, t0
    lui     AT, 0xFFFF
    ori     AT, AT, 0xFF
    and     k1, k1, AT
    or      k1, k1, t1
    sw      k1, 0x118(a1)
2:
    lui     k1, %hi(MI_INTERRUPT_MASK_REGISTER)
    lw      k1, %lo(MI_INTERRUPT_MASK_REGISTER)(k1)
    nop
    beqz    k1, 3f
    nop
    lui     k0, %hi(__OSGlobalIntMask)
    addiu   k0, k0, %lo(__OSGlobalIntMask)
    lw      k0, 0(k0)
    nop
    srl     k0, k0, 16
    li      AT, -0x1
    xor     k0, k0, AT
    lw      t0, 0x128(a1)
    andi    k0, k0, 0x3F
    and     k0, k0, t0
    or      k1, k1, k0
3:
    beqz    a0, 4f
    sw      k1, 0x128(a1)
    jal     __osEnqueueThread
    nop
4:
    j       __osDispatchThread
END(__osEnqueueAndYield)

LEAF(__osEnqueueThread)
    addu    t9, a0, zero
    lw      t8, 0(a0)
    lw      t7, 0x4(a1)
    lw      t6, 0x4(t8)
    nop
    slt     AT, t6, t7
    bnez    AT, 2f
    nop
1:
    addu    t9, t8, zero
    lw      t8, 0(t8)
    nop
    lw      t6, 0x4(t8)
    nop
    slt     AT, t6, t7
    beqz    AT, 1b
2:
    lw      t8, 0(t9)
    sw      a1, 0(t9)
    sw      t8, 0(a1)
    jr      ra
    sw      a0, 0x8(a1)
END(__osEnqueueThread)

LEAF(__osPopThread)
    lw      v0, 0(a0)
    nop
    lw      t9, 0(v0)
    sw      zero, 0(v0)
    jr      ra
    sw      t9, 0(a0)
END(__osPopThread)

LEAF(__osDispatchThread)
    lui     a0, %hi(__osRunQueue)
    addiu   a0, a0, %lo(__osRunQueue)
    jal     __osPopThread
    nop
    lui     AT, %hi(__osRunningThread)
    sw      v0, %lo(__osRunningThread)(AT)
    li      t0, 0x4
    sh      t0, 0x10(v0)
    addu    k0, v0, zero
    lw      k1, 0x118(k0)
    lui     t0, %hi(__OSGlobalIntMask)
    addiu   t0, t0, %lo(__OSGlobalIntMask)
    lw      t0, 0(t0)
    nop
    andi    t0, t0, 0xFF00
    andi    t1, k1, 0xFF00
    and     t1, t1, t0
    lui     AT, 0xFFFF
    ori     AT, AT, 0xFF
    and     k1, k1, AT
    or      k1, k1, t1
    nop
    mtc0    k1, C0_SR
    nop
    ld      AT, 0x20(k0)
    ld      v0, 0x28(k0)
    ld      v1, 0x30(k0)
    ld      a0, 0x38(k0)
    ld      a1, 0x40(k0)
    ld      a2, 0x48(k0)
    ld      a3, 0x50(k0)
    ld      t0, 0x58(k0)
    ld      t1, 0x60(k0)
    ld      t2, 0x68(k0)
    ld      t3, 0x70(k0)
    ld      t4, 0x78(k0)
    ld      t5, 0x80(k0)
    ld      t6, 0x88(k0)
    ld      t7, 0x90(k0)
    ld      s0, 0x98(k0)
    ld      s1, 0xA0(k0)
    ld      s2, 0xA8(k0)
    ld      s3, 0xB0(k0)
    ld      s4, 0xB8(k0)
    ld      s5, 0xC0(k0)
    ld      s6, 0xC8(k0)
    ld      s7, 0xD0(k0)
    ld      t8, 0xD8(k0)
    ld      t9, 0xE0(k0)
    ld      gp, 0xE8(k0)
    ld      sp, 0xF0(k0)
    ld      fp, 0xF8(k0)
    ld      ra, 0x100(k0)
    ld      k1, 0x108(k0)
    nop
    mtlo    k1
    ld      k1, 0x110(k0)
    nop
    mthi    k1
    lw      k1, 0x11C(k0)
    nop
    mtc0    k1, C0_EPC
    lw      k1, 0x18(k0)
    nop
    beqz    k1, 1f
    nop
    lw      k1, 0x12C(k0)
    nop
    ctc1    k1, $31
    ldc1    $f0, 0x130(k0)
    ldc1    $f2, 0x138(k0)
    ldc1    $f4, 0x140(k0)
    ldc1    $f6, 0x148(k0)
    ldc1    $f8, 0x150(k0)
    ldc1    $f10, 0x158(k0)
    ldc1    $f12, 0x160(k0)
    ldc1    $f14, 0x168(k0)
    ldc1    $f16, 0x170(k0)
    ldc1    $f18, 0x178(k0)
    ldc1    $f20, 0x180(k0)
    ldc1    $f22, 0x188(k0)
    ldc1    $f24, 0x190(k0)
    ldc1    $f26, 0x198(k0)
    ldc1    $f28, 0x1A0(k0)
    ldc1    $f30, 0x1A8(k0)
    lw      k1, 0x118(k0)
    nop
    srl     k1, k1, 16
    andi    k1, k1, 0x400
    beqz    k1, 1f
    nop
    ldc1    $f1, 0x1B0(k0)
    ldc1    $f3, 0x1B8(k0)
    ldc1    $f5, 0x1C0(k0)
    ldc1    $f7, 0x1C8(k0)
    ldc1    $f9, 0x1D0(k0)
    ldc1    $f11, 0x1D8(k0)
    ldc1    $f13, 0x1E0(k0)
    ldc1    $f15, 0x1E8(k0)
    ldc1    $f17, 0x1F0(k0)
    ldc1    $f19, 0x1F8(k0)
    ldc1    $f21, 0x200(k0)
    ldc1    $f23, 0x208(k0)
    ldc1    $f25, 0x210(k0)
    ldc1    $f27, 0x218(k0)
    ldc1    $f29, 0x220(k0)
    ldc1    $f31, 0x228(k0)
1:
    lw      k1, 0x128(k0)
    lui     k0, %hi(__OSGlobalIntMask)
    addiu   k0, k0, %lo(__OSGlobalIntMask)
    lw      k0, 0(k0)
    nop
    srl     k0, k0, 16
    and     k1, k1, k0
    sll     k1, k1, 1
    lui     k0, %hi(g_interruptMaskCommandTable)
    addiu   k0, k0, %lo(g_interruptMaskCommandTable)
    addu    k1, k1, k0
    lhu     k1, 0(k1)
    lui     k0, %hi(MI_INTERRUPT_MASK_REGISTER)
    ori     k0, k0, %lo(MI_INTERRUPT_MASK_REGISTER)
    sw      k1, 0(k0)
    nop
    nop
    nop
    nop
    eret
END(__osDispatchThread)

LEAF(__osCleanupThread)
    jal     osDestroyThread
    addu    a0, zero, zero
/* alignment fill before leointerrupt.o: stale bytes of the original build, one value per version; they decode as
   instructions, but 0x00134348 is a jr with nonzero rt/rd/shamt fields, which no assembler mnemonic can encode */
#if VERSION_DE
    lui     a1, 0xA460
    lui     v1, 0x8015
    lw      v1, -0x784C(v1)
#elif VERSION_EU
    addiu   s2, zero, 0xFF
    beq     v0, s2, . + 4 + 0x74
    nop
#elif VERSION_US
    nop
    .word   0x00134348
    daddiu  AT, t3, 0x6C74
#else
    beqz    v0, . + 4 + 8
    addiu   s0, zero, 0x20
    addu    s0, s1, zero
#endif
END(__osCleanupThread)


.data
.balign 4
#if VERSION_DE
.globl g_preNmiShutdownFlagDe
g_preNmiShutdownFlagDe:
.word 0
#endif
#if VERSION_EU
.globl g_preNmiShutdownFlagEu
g_preNmiShutdownFlagEu:
.word 0
#endif
#if VERSION_EU_X
.globl g_preNmiShutdownFlagEuX
g_preNmiShutdownFlagEuX:
.word 0
#endif
#if VERSION_US_REV1
.globl g_preNmiShutdownFlagUsRev1
g_preNmiShutdownFlagUsRev1:
.word 0
#endif
