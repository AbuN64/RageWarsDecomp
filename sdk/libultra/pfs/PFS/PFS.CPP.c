#include "PFS/INODE.H"
#include "Common/player_pool_and_inode_cache_views.h"
#include "types.h"
#include "Common/os_timer_interrupt_internals.h"
#include "../../../include/OSCONTREQUESFORMATSHORT.H"
#include "../../../include/PFS/PFS_SELECTACTIVEBANK.H"
#include "../../../include/PFS/PFS_READWRITEINODE.H"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "../../../include/PFS/__OSCHECKID.H"
#include "../../../include/libultra/pfs/PFS.H"
#include "../../../include/libultra/io/contramread.h"
#include "../../../include/libultra/io/contramwrite.h"

/* PFS.CPP */
/* 80447BB0_17.CPP */
/* __osRepairPackId, drafted from ultralib src/io/contpfs.c (2.0I branch): probe how many banks the
   controller pak really has, build a fresh id from the damaged one, write it to all four id areas and
   verify the first, with __osIdCheckSum as an inline helper the cartridge inlines. */




static inline s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum)
{
    u16 data = 0;
    u32 j;

    *csum = *icsum = 0;

    for (j = 0; j < 28; j += 2) {
        data = *(u16 *)((u32)ptr + j);
        *csum += data;
        *icsum += ~data;
    }

    return 0;
}

s32 __osRepairPackId(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid)
{
    s32 ret = 0;
    u8 temp[32];
    u8 comp[32];
    u8 mask = 0;
    int i;
    int j;
    u16 index[4];

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = Pfs_SelectActiveBank(pfs);
        if (ret != 0)
            return ret;
    }

    newid->repaired = -1;
    newid->random = osGetCount();
    newid->serial_mid = badid->serial_mid;
    newid->serial_low = badid->serial_low;

    j = 0;
    do {
        pfs->activebank = j;
        ret = Pfs_SelectActiveBank(pfs);
        if (ret != 0)
            return ret;
        ret = __osContRamRead(pfs->queue, pfs->channel, 0, temp);
        if (ret != 0)
            return ret;

        temp[0] = j | 0x80;

        for (i = 1; i < 32; i++) {
            temp[i] = ~temp[i];
        }

        ret = __osContRamWrite(pfs->queue, pfs->channel, 0, temp, 0);
        if (ret != 0)
            return ret;
        ret = __osContRamRead(pfs->queue, pfs->channel, 0, comp);
        if (ret != 0)
            return ret;

        for (i = 0; i < 32; i++) {
            if (comp[i] != temp[i]) {
                break;
            }
        }

        if (i != 32) {
            break;
        }

        if (j > 0) {
            pfs->activebank = 0;
            ret = Pfs_SelectActiveBank(pfs);
            if (ret != 0)
                return ret;
            ret = __osContRamRead(pfs->queue, pfs->channel, 0, (u8 *)temp);
            if (ret != 0)
                return ret;

            if (temp[0] != 0x80) {
                break;
            }
        }

        j++;
    } while (j < 62);

    pfs->activebank = 0;
    ret = Pfs_SelectActiveBank(pfs);
    if (ret != 0)
        return ret;

    mask = (j > 0) ? 1 : 0;

    newid->deviceid = (badid->deviceid & (u16)~1) | mask;
    newid->banks = j;
    newid->version = badid->version;
    __osIdCheckSum((u16 *)newid, &newid->checksum, &newid->inverted_checksum);
    index[0] = 1;
    index[1] = 3;
    index[2] = 4;
    index[3] = 6;

    for (i = 0; i < 4; i++) {
        ret = __osContRamWrite(pfs->queue, pfs->channel, index[i], (u8 *)newid, 1);
        if (ret != 0)
            return ret;
    }

    ret = __osContRamRead(pfs->queue, pfs->channel, 1, (u8 *)temp);
    if (ret != 0)
        return ret;

    for (i = 0; i < 32; i++) {
        if (temp[i] != ((u8 *)newid)[i]) {
            return 10;
        }
    }
    return 0;
}

/* __osCheckPackId, drafted from ultralib src/io/contpfs.c (2.0I branch): find a backup copy of the
   controller pak id whose checksums hold and write it over the other copies, with __osIdCheckSum as
   an inline helper the cartridge inlines. */

s32 __osCheckPackId(OSPfs *pfs, __OSPackId *temp)
{
    u16 index[4];
    s32 ret = 0;
    u16 sum;
    u16 isum;
    int i;
    int j;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = Pfs_SelectActiveBank(pfs);
        if (ret != 0)
            return ret;
    }
    index[0] = 1;
    index[1] = 3;
    index[2] = 4;
    index[3] = 6;
    for (i = 1; i < 4; i++) {
        ret = __osContRamRead(pfs->queue, pfs->channel, index[i], (u8 *)temp);
        if (ret != 0)
            return ret;
        __osIdCheckSum((u16 *)temp, &sum, &isum);
        if (temp->checksum == sum && temp->inverted_checksum == isum) {
            break;
        }
    }

    if (i == 4) {
        return 10;
    }

    for (j = 0; j < 4; j++) {
        if (j != i) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, index[j], (u8 *)temp, 1);
            if (ret != 0)
                return ret;
        }
    }

    return 0;
}

/* __osGetId, drafted from ultralib src/io/contpfs.c (2.0I branch): reread a controller pak's id block
   from bank zero, restore or rebuild it when damaged, and refresh the file system layout and label
   from it, with __osIdCheckSum as an inline helper the cartridge inlines; the id checksums are read
   through the block itself and the repaired device id through the new id, not the id pointer. */

static inline u16 __osSumcalc(u8 *ptr, int length)
{
    int i;
    u32 sum = 0;
    u8 *tmp = ptr;

    for (i = 0; i < length; i++) {
        sum += *tmp++;
        sum = sum & 0xFFFF;
    }
    return sum;
}

s32 __osGetId(OSPfs *pfs)
{
    int k;
    u16 sum;
    u16 isum;
    u8 temp[32];
    __OSPackId newid;
    s32 ret;
    __OSPackId *id;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = Pfs_SelectActiveBank(pfs);
        if (ret != 0)
            return ret;
    }
    ret = __osContRamRead(pfs->queue, pfs->channel, 1, (u8 *)&temp);
    if (ret != 0)
        return ret;
    __osIdCheckSum((u16 *)&temp, &sum, &isum);
    id = (__OSPackId *)&temp;

    if (((__OSPackId *)temp)->checksum != sum || ((__OSPackId *)temp)->inverted_checksum != isum) {
        ret = __osCheckPackId(pfs, id);

        if (ret == 10) {
            ret = __osRepairPackId(pfs, id, &newid);
            if (ret != 0)
                return ret;
            id = &newid;
        } else if (ret != 0) {
            return ret;
        }
    }

    if ((id->deviceid & 1) == 0) {
        ret = __osRepairPackId(pfs, id, &newid);
        if (ret != 0)
            return ret;
        id = &newid;

        if ((newid.deviceid & 1) == 0) {
            return 11;
        }
    }

    for (k = 0; k < 32; k++) {
        pfs->id[k] = ((u8 *)id)[k];
    }

    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = pfs->banks * 2 + 3;
    pfs->dir_size = 16;
    pfs->inode_table = 8;
    pfs->minode_table = (pfs->banks + 1) * 8;
    pfs->dir_table = pfs->minode_table + pfs->banks * 8;
    ret = __osContRamRead(pfs->queue, pfs->channel, 7, pfs->label);
    if (ret != 0)
        return ret;
    return 0;
}

s32 Pfs_ReadWriteInode(OSPfs *pfs, __OSInode *inode, u8 flag, u8 bank)
{
    u8 sum;
    int j;
    s32 ret;
    int offset;
    u8 *addr;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = Pfs_SelectActiveBank(pfs);
        if (ret != 0)
            return ret;
    }

    offset = (bank > 0) ? 1 : pfs->inode_start_page;

    if (flag == 1) {
        inode->inode_page[0].inode_t.page = __osSumcalc((u8 *)&inode->inode_page[offset], (128 - offset) * 2);
    }

    for (j = 0; j < 8; j++) {
        addr = ((u8 *)inode->inode_page + j * 32);

        if (flag == 1) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr, 0);
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr, 0);
        } else {
            ret = __osContRamRead(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr);
        }

        if (ret != 0) {
            return ret;
        }
    }

    if (flag == 0) {
        sum = __osSumcalc((u8 *)&inode->inode_page[offset], (128 - offset) * 2);
        if (sum != inode->inode_page[0].inode_t.page) {
            for (j = 0; j < 8; j++) {
                addr = ((u8 *)inode->inode_page + j * 32);
                ret = __osContRamRead(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr);
            }

            if (sum != inode->inode_page[0].inode_t.page) {
                return 3;
            }

            for (j = 0; j < 8; j++) {
                addr = ((u8 *)inode->inode_page + j * 32);
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr, 0);
            }
        } else {
            for (j = 0; j < 8; j++) {
                addr = ((u8 *)inode->inode_page + j * 32);
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr, 0);
            }
        }
    }

    return 0;
}

/* Returns the 16-bit sum of the first count bytes of a block. */

u16 Pfs_SumBytes(u8 *bytes, s32 count)
{
    s32 i;
    s32 sum;

    i = 0;
    sum = i;
    for (; i < count; i++) {
        sum += *bytes++;
        sum &= 0xFFFF;
    }
    return sum;
}

/* Sums the fourteen halfwords of a 0x1C-byte block into two checksums: the plain sum and the sum
   of their complements. Returns zero. */
s32 Pfs_ComputeIdChecksums(u16 *block, u16 *sum, u16 *inverse) {
    u32 offset;

    *inverse = 0;
    *sum = 0;
    for (offset = 0; offset < 0x1C; offset += 2) {
        u16 value = *(u16 *) ((char *) block + offset);

        *sum += value;
        *inverse += (u16) ~value;
    }
    return 0;
}

s32 __osCheckId(OSPfs *pfs)
{
    int k;
    u8 temp[32];
    s32 ret;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = Pfs_SelectActiveBank(pfs);
        if (ret != 0)
            return ret;
    }

    ret = __osContRamRead(pfs->queue, pfs->channel, 1, temp);

    if (ret != 0) {
        if (ret != 2) {
            return ret;
        }
        ret = __osContRamRead(pfs->queue, pfs->channel, 1, temp);
        if (ret != 0)
            return ret;
    }

    for (k = 0; k < 32; k++) {
        if (pfs->id[k] != temp[k])
            return 2;
    }

    return 0;
}

/* Select the PFS active bank. Existing PFS consumers supply the canonical
 * queue/channel/activebank fields at offsets 4, 8 and 0x65. The cartridge
 * returns the controller write result directly (v0 survives the epilogue). */

s32 Pfs_SelectActiveBank(OSPfs *pfs)
{
    u8 name[32];
    s32 i;

    for (i = 0; i < 32; i++) {
        name[i] = pfs->activebank;
    }
    return __osContRamWrite(pfs->queue, pfs->channel, 0x400, name, 0);
}

#if defined(VERSION_US)
unsigned char g_PfsLetterRString[4] = { 0x52, 0x00, 0x00, 0x00 };
#endif

/* 80447BB0_8.CPP */
