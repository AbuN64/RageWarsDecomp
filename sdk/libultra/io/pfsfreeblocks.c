#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "../../include/OSCONTREQUESFORMATSHORT.H"
#include "TYPES.H"
#include <ultra64.h>
#include "../../include/PFS/PFS_READWRITEINODE.H"
#include "../../include/PFS/__OSCHECKID.H"

/* osPfsFreeBlocks, drafted from ultralib src/io/pfsfreeblocks.c (2.0I branch): count the unused pages
   in every bank's inode table and report them as bytes. */









s32 osPfsFreeBlocks(OSPfs *pfs, s32 *bytes_not_used)
{
    int j;
    int pages = 0;
    __OSInode inode;
    s32 ret = 0;
    u8 bank;
    int offset;

    if ((pfs->status & 1) == 0)
        return 5;
    if (__osCheckId(pfs) == 2)
        return 2;
    for (bank = 0; bank < pfs->banks; bank++) {
        ret = Pfs_ReadWriteInode(pfs, &inode, 0, bank);
        if (ret != 0)
            return ret;
        offset = ((bank > 0) ? 1 : pfs->inode_start_page);

        for (j = offset; j < 128; j++) {
            if (inode.inode_page[j].ipage == 3) {
                pages++;
            }
        }
    }

    *bytes_not_used = pages * 8 * 32;
    return 0;
}

