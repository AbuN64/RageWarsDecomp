#ifndef LIBULTRA_IO_LEOINTERRUPT_RESUME_H
#define LIBULTRA_IO_LEOINTERRUPT_RESUME_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CTX.H"
/* Disk transfer state embedded at offset 0x14 in the PI device handle. */
typedef struct DiskTransferInfo {
    u16 command;
    u16 mode;
    u32 block;
    s32 sector;
    u32 deviceAddress;
    u32 bmControl;
} DiskTransferInfo;
extern void __osLeoAbnormalResume(void);
extern void __osLeoResume(void);
#endif
