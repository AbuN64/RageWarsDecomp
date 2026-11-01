#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(Decompress_ExpandBackReferences)
    li      t5, 0x0
    lui     t3, %hi(g_backReferenceOutputByteCount)
    addiu   t3, t3, %lo(g_backReferenceOutputByteCount)
    addiu   t6, t6, 0x4
    lbu     t5, 0(t6)
    lbu     t4, 0x1(t6)
    lbu     s2, 0x2(t6)
    lbu     t7, 0x3(t6)
    sll     t5, t5, 24
    sll     t4, t4, 16
    sll     s2, s2, 8
    or      t5, t5, t4
    or      t5, t5, s2
    or      t5, t5, t7
    addiu   t6, t6, 0x4
    sw      t5, 0(t3)
    addu    v1, t6, zero
    addi    v1, v1, 0xA
    addu    a1, s1, zero
    addu    a2, a1, zero
    addu    a2, a2, t5
    lbu     t5, 0(t6)
    lbu     t4, 0x1(t6)
    lbu     s2, 0x2(t6)
    lbu     t7, 0x3(t6)
    sll     t5, t5, 24
    sll     t4, t4, 16
    sll     s2, s2, 8
    or      t5, t5, t4
    or      t5, t5, s2
    or      t5, t5, t7
    addiu   t6, t6, 0x4
    addu    a0, v1, zero
    add     a0, a0, t5
    addi    t3, t3, -0x2
    sh      zero, 0(t3)
    lui     t2, 0xFFFF
    ori     t2, t2, 0xFF00
    li      t7, 0x1
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    addu    t2, t2, t2
    srl     t7, t2, 8
    j       30f
    andi    t7, t7, 0x1
    li      v0, -0x1
    jr      ra
    nop
    li      v0, -0x2
    jr      ra
    nop
1:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       11f
    andi    t7, t7, 0x1
2:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       14f
    andi    t7, t7, 0x1
3:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       15f
    andi    t7, t7, 0x1
4:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       16f
    andi    t7, t7, 0x1
5:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       18f
    andi    t7, t7, 0x1
6:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       19f
    andi    t7, t7, 0x1
7:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       20f
    andi    t7, t7, 0x1
8:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       22f
    andi    t7, t7, 0x1
9:
    li      t0, 0x3
10:
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 1b
    nop
11:
    addu    t1, t1, t1
    addu    t1, t1, t7
    srl     t7, t1, 16
    andi    t7, t7, 0x1
    addi    t0, t0, -0x1
    bgez    t0, 10b
    nop
    addi    t1, t1, 0x2
12:
    lbu     t4, 0(v1)
    lbu     s2, 0x1(v1)
    sb      t4, 0(a1)
    sb      s2, 0x1(a1)
    lbu     t4, 0x2(v1)
    lbu     s2, 0x3(v1)
    sb      t4, 0x2(a1)
    sb      s2, 0x3(a1)
    addiu   v1, v1, 0x4
    addi    t1, t1, -0x1
    bgez    t1, 12b
    addi    a1, a1, 0x4
    j       30f
    nop
13:
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 2b
    nop
14:
    addu    t0, t0, t0
    addu    t0, t0, t7
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 3b
    nop
15:
    beq     zero, t7, 17f
    nop
    addi    t0, t0, -0x1
    add     t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 4b
    nop
16:
    addu    t0, t0, t0
    addu    t0, t0, t7
    srl     t7, t0, 16
    andi    t7, t7, 0x1
    addi    t4, t0, -0x9
    beq     zero, t4, 9b
    nop
17:
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 5b
    nop
18:
    beq     zero, t7, 24f
    nop
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 6b
    nop
19:
    addu    t1, t1, t1
    addu    t1, t1, t7
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 7b
    nop
20:
    bne     zero, t7, 36f
    nop
    bne     zero, t1, 23f
    nop
    addi    t1, t1, 0x1
21:
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 8b
    nop
22:
    addu    t1, t1, t1
    addu    t1, t1, t7
    srl     t7, t1, 16
    andi    t7, t7, 0x1
23:
    sll     t4, t1, 8
    andi    t4, t4, 0xFF00
    srl     t1, t1, 8
    or      t1, t1, t4
24:
    andi    s3, t1, 0xFF00
    lbu     t1, 0(v1)
    addiu   v1, v1, 0x1
    or      t1, t1, s3
    addu    t6, a1, zero
    sub     t6, t6, t1
    addi    t6, t6, -0x1
    andi    t7, t0, 0x1
    srl     t0, t0, 1
    beq     zero, t7, 25f
    nop
    lbu     t4, 0(t6)
    addi    t6, t6, 0x1
    sb      t4, 0(a1)
    addi    a1, a1, 0x1
25:
    addi    t0, t0, -0x1
    bne     zero, t1, 27f
    nop
    andi    s3, t1, 0xFF00
    lbu     t1, 0(t6)
    nop
    or      t1, t1, s3
26:
    sb      t1, 0(a1)
    addi    t0, t0, -0x1
    sb      t1, 0x1(a1)
    bgez    t0, 26b
    addi    a1, a1, 0x2
    j       30f
    nop
27:
    lbu     s2, 0x1(t6)
    lbu     t4, 0(t6)
    sb      s2, 0x1(a1)
    sb      t4, 0(a1)
    addi    t6, t6, 0x2
    addi    t0, t0, -0x1
    bgez    t0, 27b
    addi    a1, a1, 0x2
    j       30f
    nop
28:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    bne     zero, t7, 32f
    nop
29:
    lbu     t4, 0(v1)
    addi    v1, v1, 0x1
    sb      t4, 0(a1)
    addi    a1, a1, 0x1
30:
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    bne     zero, t7, 31f
    nop
    lbu     t4, 0(v1)
    addi    v1, v1, 0x1
    sb      t4, 0(a1)
    addi    a1, a1, 0x1
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    beq     zero, t7, 29b
    nop
31:
    andi    t2, t2, 0xFF
    beq     zero, t2, 28b
    nop
32:
    li      t0, 0x2
    li      t1, 0x0
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 39f
    nop
33:
    beq     zero, t7, 13b
    nop
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 40f
    nop
34:
    beq     zero, t7, 24b
    nop
    addi    t0, t0, 0x1
    add     t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 41f
    nop
35:
    beq     zero, t7, 17b
    nop
    lbu     t0, 0(v1)
    addi    v1, v1, 0x1
    nop
    beq     zero, t0, 44f
    addi    t0, t0, 0x8
    j       17b
    nop
36:
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 42f
    nop
37:
    addu    t1, t1, t1
    addu    t1, t1, t7
    srl     t7, t1, 16
    andi    t7, t7, 0x1
    ori     t1, t1, 0x4
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    beq     zero, t2, 43f
    nop
38:
    bne     zero, t7, 23b
    nop
    j       21b
    nop
39:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       33b
    andi    t7, t7, 0x1
40:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       34b
    andi    t7, t7, 0x1
41:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       35b
    andi    t7, t7, 0x1
42:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       37b
    andi    t7, t7, 0x1
43:
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    j       38b
    andi    t7, t7, 0x1
44:
    addu    t2, t2, t2
    srl     t7, t2, 8
    andi    t7, t7, 0x1
    andi    t2, t2, 0xFF
    bne     zero, t2, 45f
    nop
    lbu     t2, 0(v1)
    addi    v1, v1, 0x1
    addu    t2, t2, t2
    addu    t2, t2, t7
    srl     t7, t2, 8
    andi    t7, t7, 0x1
45:
    bne     zero, t7, 30b
    nop
    lhu     t5, 0(t3)
    addi    t3, t3, 0x2
    beq     zero, t5, 47f
    nop
46:
    lh      s0, 0(t3)
    addi    t3, t3, 0x2
    sb      s0, 0(a1)
    addi    a1, a1, 0x1
    addi    t5, t5, -0x1
    bne     zero, t5, 46b
    nop
47:
    j       48f
    nop
    sw      s0, 0(t3)
48:
    li      v0, 0x0
    jr      ra
    nop
END(Decompress_ExpandBackReferences)
