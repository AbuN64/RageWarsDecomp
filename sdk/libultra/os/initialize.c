#include "include_asm.h"
#include "Common/alfxparam.h"
#include "Common/measured.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include "Common/runtime_declarations.h"
#include "Common/argb_color.h"
#include <platform_sdk.h>
#include "Common/__osdispatchthread.h"
#include "Common/multiplayeroptions.h"
#include "Common/loadout.h"
#include "Common/virtual_pager.h"
#include "Common/group.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/manager.h"
#include "Common/cartridgereadworker.h"
#include "Common/audio_voice_slots.h"
#include "Common/soundvoicepool.h"
#include "Common/lightdata.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/mtx.h"
#include "Common/particle_attachment_and_owner_views.h"
#include "Common/colorentry.h"
#include "Common/worldsortentry.h"
#include "Common/results.h"
#include "Common/round_session.h"
#include "Common/menu_screen_elements.h"
#include "Common/hud_effects.h"
#include "Common/albank_s.h"
#include "Common/sequence_timing.h"
#include "Common/alparam_s.h"
#include "Common/audio_effect_chain.h"
#include "Common/ospihandle_s.h"
#include "types.h"
#include "Common/controller_motor_state.h"
#include "Common/osviscale.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/ctx.h"
#include <PR/os_internal_reg.h>
#include "Common/audio_loaddecodedsamples.h"
#include "Common/cheatcode.h"
#include "Common/note_state.h"
#include "Common/frontend_video_mode.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Common/label.h"
#include "Common/player_join_requests.h"
#include "Common/characterselectionroot.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/weapon_unlock_presets.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/match_settings.h"
#include "Common/menu_model_preview.h"
#include "Common/player_item_inventory.h"
#include "Common/objb.h"
#include "Common/boot_tv_type.h"
#include "../../include/libultra/io/pirawread.H"
#include "../../include/libultra/io/si.h"
#include <PR/os_internal_si.h>
#include "Engine/Virtual/virtual_region_and_pager_operations.h"
#include "Ui/X_files/x_plus.h"
#include "../../include/libultra/debug/assert.h"
#include "Sirawread/sirawread.h"

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
