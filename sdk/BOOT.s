#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

/* entry.s */
.text
.set noreorder
.set noat

LEAF(Boot_EntryPoint)
    lui     sp, 0x803F
    ori     sp, sp, 0xFFC0
    li      a0, 0x1E
1:
    mfc0    t0, C0_ENTRYHI
    mtc0    a0, C0_INX
    lui     t1, 0x8000
    mtc0    t1, C0_ENTRYHI
    mtc0    zero, C0_ENTRYLO0
    mtc0    zero, C0_ENTRYLO1
    nop
    tlbwi
    nop
    nop
    nop
    nop
    mtc0    t0, C0_ENTRYHI
    nop
    bnez    a0, 1b
    addi    a0, a0, -0x1
    li      a0, 0x1F
    lui     a1, 0x1F
    ori     a1, a1, 0xE000
    lui     a2, 0x20
    li      a3, 0x0
    lui     t1, 0x10
    sw      t1, 0x10(sp)
    li      t0, 0x7
    jal     rw_boot_entry+0x88
    sw      t0, 0x14(sp)
#if VERSION_EU
    lui     a0, %hi(Sched_RestoreBootMemoryAddressEu)
    addiu   a0, a0, %lo(Sched_RestoreBootMemoryAddressEu)
#elif VERSION_EU_X
    lui     a0, %hi(Sched_RestoreBootMemoryAddressEuX)
    addiu   a0, a0, %lo(Sched_RestoreBootMemoryAddressEuX)
#elif VERSION_US
    lui     a0, %hi(ItemMenu_RestoreBootMemory_Address)
    addiu   a0, a0, %lo(ItemMenu_RestoreBootMemory_Address)
#elif VERSION_US_REV1
    lui     a0, %hi(Sched_RestoreBootMemoryAddressUsRev1)
    addiu   a0, a0, %lo(Sched_RestoreBootMemoryAddressUsRev1)
#else
    lui     a0, %hi(Sched_RestoreBootMemoryAddressDe)
    addiu   a0, a0, %lo(Sched_RestoreBootMemoryAddressDe)
#endif
    jalr    a0
    nop
    break   1, 2
    lw      t8, 0x10(sp)
    addi    t0, zero, 0x7
    lw      t9, 0x14(sp)
    addi    t7, zero, -0x1
    and     t9, t9, t0
    ori     t9, t9, 0x18
    mfc0    t0, C0_ENTRYHI
    mtc0    a0, C0_INX
    mtc0    a1, C0_PAGEMASK
    mtc0    a2, C0_ENTRYHI
    beq     a3, t7, 2f
    addi    t6, zero, 0x1
    srl     t5, a3, 6
    or      t5, t5, t9
    b       3f
    mtc0    t5, C0_ENTRYLO0
2:
    mtc0    t6, C0_ENTRYLO0
3:
    beq     t8, t7, 4f
    mtc0    t6, C0_ENTRYLO1
    srl     t5, t8, 6
    or      t5, t5, t9
    mtc0    t5, C0_ENTRYLO1
4:
    tlbwi
    nop
    nop
    nop
    nop
    mtc0    t0, C0_ENTRYHI
    jr      ra
    nop
END(Boot_EntryPoint)
