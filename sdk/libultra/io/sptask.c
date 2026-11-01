#include "../../include/LIBC.H"
#include "COMMON/ALFXPARAM.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include "COMMON/OSPIHANDLE_S.H"
#include <PR/os_internal_rsp.h>
#include "../../include/libgultra/sp.h"

/* _VirtualToPhysicalTask, drafted from ultralib src/io/sptask.c; this library's bcopy is the
   destination-first copy Libc_CopyBytes. */




/* The yielded task records its ucode pointer in the last word of its 0xC00-byte yield buffer. */



OSTask *_VirtualToPhysicalTask(OSTask *intp);






OSTask *_VirtualToPhysicalTask(OSTask *intp)
{
    OSTask *tp;
    OSTask *task = &g_signalProcessorTaskCopy;
    tp = task;
    Libc_CopyBytes(task, intp, sizeof(OSTask));
    if (task->t.ucode != 0) { task->t.ucode = (void *)osVirtualToPhysical(task->t.ucode); } (void)0;
    if (task->t.ucode_data != 0) { task->t.ucode_data = (void *)osVirtualToPhysical(task->t.ucode_data); } (void)0;
    if (task->t.dram_stack != 0) { task->t.dram_stack = (void *)osVirtualToPhysical(task->t.dram_stack); } (void)0;
    if (task->t.output_buff != 0) { task->t.output_buff = (void *)osVirtualToPhysical(task->t.output_buff); } (void)0;
    if (task->t.output_buff_size != 0) { task->t.output_buff_size = (void *)osVirtualToPhysical(task->t.output_buff_size); } (void)0;
    if (task->t.data_ptr != 0) { task->t.data_ptr = (void *)osVirtualToPhysical(task->t.data_ptr); } (void)0;
    if (task->t.yield_data_ptr != 0) { task->t.yield_data_ptr = (void *)osVirtualToPhysical(task->t.yield_data_ptr); } (void)0;
    return tp;
}

void osSpTaskLoad(OSTask *intp) {
    OSTask *block;
    s32 result;

    block = _VirtualToPhysicalTask(intp);
    if (block->t.flags & 1) {
        block->t.ucode_data = block->t.yield_data_ptr;
        block->t.ucode_data_size = block->t.yield_data_size;
        intp->t.flags &= ~1;
        if (block->t.flags & 4) {
            block->t.ucode = (u64 *)IO_READ(((u32)intp->t.yield_data_ptr + 0xBFCU) | 0xA0000000U);
        }
    }
    osWritebackDCache(block, 0x40);
    __osSpSetStatus(0x2B00);
    do {
        result = __osSpSetPc(0x04001000);
    } while (result == -1);
    do {
        result = __osSpRawStartDma(1, 0x04000FC0, (s32)block, 0x40);
    } while (result == -1);
    while (__osSpDeviceBusy() != 0) {
    }
    do {
        result = __osSpRawStartDma(1, 0x04001000, (s32)block->t.ucode_boot, block->t.ucode_boot_size);
    } while (result == -1);
}


void osSpTaskStartGo(OSTask *tp) {
    do {
    } while (__osSpDeviceBusy() != 0);
    __osSpSetStatus(0x125U);
}
