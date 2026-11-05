#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/navigation_graph.h"
#include "Common/particle_lighting.h"
#if !defined(M2CTX) && !defined(PERMUTER)
/* asn64 defines glabel and dlabel itself: the first macro.inc of an object replaces them with splat's */
#define INCLUDE_PRE ".ifndef _MACRO_INC_GUARD\n    .purgem glabel\n    .purgem dlabel\n    .endif\n"
#define INCLUDE_ASM(SEG, NAME) \
    __asm__(INCLUDE_PRE ".section .text\n    .set noat\n    .set noreorder\n" \
            "    .include \"nonmatchings/" SEG "/" #NAME ".s\"\n" \
            "    .set reorder\n    .set at\n")
#define INCLUDE_RODATA(SEG, NAME) \
    __asm__(INCLUDE_PRE ".section .rodata\n    .include \"data/" SEG "/" #NAME ".s\"\n.section .text")
#define INCLUDE_DATA(SEG, NAME) \
    __asm__(INCLUDE_PRE ".section .data\n    .include \"data/" SEG "/" #NAME ".s\"\n.section .text")
#define INCLUDE_BSS(SEG, NAME, SIZE) \
    __asm__(".section .bss\n    .space " #SIZE "\n.section .text")
#else
#define INCLUDE_ASM(SEG, NAME)
#define INCLUDE_RODATA(SEG, NAME)
#define INCLUDE_DATA(SEG, NAME)
#define INCLUDE_BSS(SEG, NAME, SIZE)
#endif
#endif
