#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"
#include "COMMON/MEASUREDRECAT0V1.H"
#include "COMMON/MEASURED.H"
#include "COMMON/MEASUREDRECAT14V4.H"
#include "COMMON/MEASUREDRECAT14V2.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ARGB_COLOR.H"
#include <ultra64.h>
#include "COMMON/__OSDISPATCHTHREAD.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/GROUP.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/MTX.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "COMMON/COLORENTRY.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/RESULTS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/OBJRECAT18V1.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "TYPES.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "COMMON/OSVISCALE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/CTX.H"
#include <PR/os_internal_reg.h>
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/LABEL.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/STATERECAT91.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/OBJB.H"
#include "COMMON/BOOT_TV_TYPE.H"
#include "../../include/libultra/io/pirawread.H"
#include "../../include/libultra/io/si.h"
#include <PR/os_internal_si.h>
#include "ENGINE/VIRTUAL/VIRTUAL_REGION_AND_PAGER_OPERATIONS.H"
#include "UI/X_FILES/X_PLUS.H"
#include "../../include/libultra/debug/assert.h"

/* Drafted from ultralib src/os/initialize.c (before 2.0J, _FINALROM): the clock
   rate comes from the ROM header through osPiRawReadIo. */




extern void osWritebackDCache(void *addr, s32 size);
extern void osInvalICache(void *addr, s32 size);


void osInitialize(void)
{
    u32 pifdata;
    u32 clock = 0;
    u64 *rate;

    __osFinalrom = 1;
    __osSetSR(__osGetSR() | 0x20000000);
    __osSetFpcCsr(0x01000800);
    while (__osSiRawReadIo(0x1FC007FC, &pifdata)) {
        ;
    }
    while (__osSiRawWriteIo(0x1FC007FC, pifdata | 8)) {
        ;
    }
    *(QuadN64EngDrawNumericWidgetChildren *)0x80000000 = *g_osExceptionPreamble;
    *(QuadN64EngDrawNumericWidgetChildren *)0x80000080 = *g_osExceptionPreamble;
    *(QuadN64EngDrawNumericWidgetChildren *)0x80000100 = *g_osExceptionPreamble;
    *(QuadN64EngDrawNumericWidgetChildren *)0x80000180 = *g_osExceptionPreamble;
    osWritebackDCache((void *)0x80000000, 0x80000180 - 0x80000000 + sizeof(QuadN64EngDrawNumericWidgetChildren));
    osInvalICache((void *)0x80000000, 0x80000180 - 0x80000000 + sizeof(QuadN64EngDrawNumericWidgetChildren));
    Vhandler_MapBootstrapAddressRange();
    osPiRawReadIo(4, &clock);
    clock &= ~0xf;
    if (clock != 0) {
        g_systemClockFrequency = clock;
    } else {
        g_systemClockFrequency = 62500000;
    }
    rate = &g_systemClockFrequency;
    *rate = *rate * 3 / 4;
    if (osResetType == 0) {
        XPlus_FillMemory(osAppNMIBuffer, 0, 0x40);
    }
    if (g_consoleTvType == 0) {
        g_audioClockRate = 0x2F5B2D2;
    } else if (g_consoleTvType == 2) {
        g_audioClockRate = 0x2E6025C;
    } else {
        g_audioClockRate = 0x2E6D354;
    }
}


int __osSiRawReadIo(u32 deviceAddress, u32 *data) {
    if (deviceAddress & 3) {
        __assert(g_serialDmaAssertionCondition, &s_sirawreadText, 0x33);
    }
    if (data == 0) {
        __assert(g_serialDmaAssertionCondition, &s_sirawreadText, 0x34);
    }
    if (__osSiDeviceBusy() != 0) {
        return -1;
    }
    *data = *(u32 *)(deviceAddress | 0xA0000000);
    return 0;
}

int __osSiRawWriteIo(u32 deviceAddress, u32 data) {
    if (deviceAddress & 3) {
        __assert(&g_audioAssertionConditionText, &g_audioAssertionSourceText, 0x34);
    }
    if (__osSiDeviceBusy() != 0) {
        return -1;
    }
    *(u32 *)(deviceAddress | 0xA0000000) = data;
    return 0;
}


const char s_siRawWriteSourcePath[16] = "io/sirawwrite.c";
