#include "include_asm.h"
#include "COMMON/BOOT_TV_TYPE.H"
#include <ultra64.h>
#include "COMMON/OSVISCALE.H"
#include "TYPES.H"
#include "../../include/AUDIO/__OSVISWAPCONTEXT.H"
#include "DATA/REST_SOURCE_RECORDS.H"

/* viswapcontext.c */
/* __osViSwapContext, drafted from ultralib src/io/viswapcontext.c (2.0I: vStart straight from the
   field registers). The unsigned-to-float and float-to-unsigned conversions of the y scale use the
   cartridge's 2^32 and 2^31 constants, so both are written out. */
extern __OSViContext *__osViCurr;
extern __OSViContext *__osViNext;
 /* 2^32 */
 /* 2^31 */
void __osViSwapContext(void)
{
    register Modep *vm;
    register __OSViContext *vc;
    u32 origin;
    u32 hStart;
    u32 nomValue;
    u32 field;
    f64 nom;
    f32 scale;
    u32 yscale;
    u32 *yscalep;
    __OSViContext **curr;
    field = 0;
    vc = __osViNext;
    vm = vc->modep;
    field = (*(volatile u32 *)(0xA4400010)) & 1;
    origin = osVirtualToPhysical(vc->framep) + (vm->fldRegs[field].origin);
    if (vc->state & 2) {
        vc->x.scale |= (vm->comRegs.xScale & ~0xFFF);
    } else {
        vc->x.scale = vm->comRegs.xScale;
    }
    if (vc->state & 4) {
        nomValue = vm->fldRegs[field].yScale & 0xFFF;
        yscalep = &vc->y.scale;
        nom = (s32)nomValue;
        if ((s32)nomValue < 0) {
            nom += g_videoScaleUnsignedBias;
        }
        scale = vc->y.factor * (f32)nom;
        /* The unsigned conversion in GCC's own order: large values take the offset path. */
        if (scale >= g_videoScaleSignedConversionLimit) {
            goto large;
        }
        yscale = (s32)scale;
        goto converted;
    large:
        yscale = (s32)(scale - g_videoScaleSignedConversionLimit) | 0x80000000;
    converted:
        *yscalep = yscale;
        vc->y.scale |= vm->fldRegs[field].yScale & ~0xFFF;
    } else {
        vc->y.scale = vm->fldRegs[field].yScale;
    }
    hStart = vm->comRegs.hStart;
    if (vc->state & 0x20) {
        hStart = 0;
    }
    if (vc->state & 0x40) {
        vc->y.scale = 0;
        origin = osVirtualToPhysical(vc->framep);
    }
    if (vc->state & 0x80) {
        vc->y.scale = (vc->y.offset << 16) & (0x3FF << 16);
        origin = osVirtualToPhysical(vc->framep);
    }
    IO_WRITE(0xA4400004, origin);
    IO_WRITE(0xA4400008, vm->comRegs.width);
    IO_WRITE(0xA4400014, vm->comRegs.burst);
    IO_WRITE(0xA4400018, vm->comRegs.vSync);
    IO_WRITE(0xA440001C, vm->comRegs.hSync);
    IO_WRITE(0xA4400020, vm->comRegs.leap);
    IO_WRITE(0xA4400024, hStart);
    IO_WRITE(0xA4400028, vm->fldRegs[field].vStart);
    IO_WRITE(0xA440002C, vm->fldRegs[field].vBurst);
    IO_WRITE(0xA440000C, vm->fldRegs[field].vIntr);
    IO_WRITE(0xA4400030, vc->x.scale);
    IO_WRITE(0xA4400034, vc->y.scale);
    IO_WRITE(0xA4400000, vc->control);
    curr = &__osViCurr;
    __osViNext = *curr;
    *curr = vc;
    *__osViNext = **curr;
}

/* VIDEO_SCALE_UNSIGNED_BIAS_DATA.CPP */
/* ROM-grounded data: src/g_videoScaleUnsignedBias_StorageWords_VideoScaleUnsignedBiasData.c */
const RestvideoScaleUnsignedBias_StorageWordsLayout386 g_videoScaleUnsignedBias_StorageWords = {
    { 3e+01f, 0.0f, 2.1474836e+09f },
};
