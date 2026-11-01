#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(__osSetCompare)
    mtc0    a0, C0_COMPARE
    jr      ra
    nop
END(__osSetCompare)
