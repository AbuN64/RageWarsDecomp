#include "COMMON/ITEMRECAT20V1.H"
#include "../../include/OSCONTREQUESFORMATSHORT.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "TYPES.H"
#include "../../include/PFS/ospfsallocatefile.H"
#include <ultra64.h>
#include "../../include/PFS/PFS_READWRITEINODE.H"
#include "../../include/PFS/__OSCHECKID.H"
#include "../../include/PFS/PFS_SELECTACTIVEBANK.H"

/* ospfsallocatefile.CPP */
/* osPfsAllocateFile, drafted from ultralib src/io/pfsallocatefile.c (2.0I branch): create a
   controller pak file by finding a free directory entry, chaining enough free pages across the
   banks' inode tables and writing the new directory entry. */

extern s32 __osContRamWrite(void *queue, int channel, u16 address, u8 *buffer, int force);

s32 osPfsAllocateFile(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name,
                  int file_size_in_bytes, s32 *file_no)
{
    int start_page;
    int decleared;
    int last_page;
    int old_last_page = 0;
    int j;
    s32 ret = 0;
    int file_size_in_pages;
    __OSInode inode;
    __OSInode backup_inode;
    __OSDir dir;
    u8 bank;
    u8 old_bank = 0;
    int firsttime = 0;
    s32 bytes;
    __OSInodeUnit fpage;

    if (company_code == 0 || game_code == 0) {
        return 5;
    }

    file_size_in_pages = (file_size_in_bytes + 32 * 8 - 1) / (32 * 8);

    if ((pfs->status & 1) == 0) {
        return 5;
    }

    if (__osCheckId(pfs) == 2)
        return 2;

    if (((ret = osPfsFindFile(pfs, company_code, game_code, game_name, ext_name, file_no)) != 0) &&
        ret != 5) {
        return ret;
    }

    if (*file_no != -1) {
        return 9;
    }

    ret = osPfsFreeBlocks(pfs, &bytes);

    if (file_size_in_bytes > bytes) {
        return 7;
    }

    if (file_size_in_pages != 0) {

        if (((ret = osPfsFindFile(pfs, 0, 0, 0, 0, file_no)) != 0) && ret != 5) {
            return ret;
        }

        if (*file_no == -1) {
            return 8;
        }

        for (bank = 0; bank < pfs->banks; bank++) {
            ret = Pfs_ReadWriteInode(pfs, &inode, 0, bank);
            if (ret != 0)
                return ret;
            ret = __osPfsDeclearPage(pfs, &inode, file_size_in_pages, &start_page, bank, &decleared, &last_page);
            if (ret != 0)
                return ret;

            if (start_page != -1) {
                if (firsttime == 0) {
                    fpage.inode_t.page = start_page;
                    fpage.inode_t.bank = bank;
                } else {
                    backup_inode.inode_page[old_last_page].inode_t.bank = bank;
                    backup_inode.inode_page[old_last_page].inode_t.page = start_page;
                    ret = Pfs_ReadWriteInode(pfs, &backup_inode, 1, old_bank);
                    if (ret != 0)
                        return ret;
                }

                for (j = 0; j < 128; j++) {
                    backup_inode.inode_page[j].ipage = inode.inode_page[j].ipage;
                }
                old_last_page = last_page;
                old_bank = bank;
                firsttime++;
                if (file_size_in_pages > decleared) {
                    file_size_in_pages = file_size_in_pages - decleared;
                } else {
                    file_size_in_pages = 0;
                    break;
                }
            }
        }

        if (file_size_in_pages > 0 || start_page == -1) {
            return 3;
        }

        backup_inode.inode_page[old_last_page].inode_t.bank = bank;
        backup_inode.inode_page[old_last_page].inode_t.page = start_page;
        ret = Pfs_ReadWriteInode(pfs, &backup_inode, 1, old_bank);
        if (ret != 0)
            return ret;

        dir.start_page = fpage;
        dir.company_code = company_code;
        dir.game_code = game_code;
        dir.data_sum = 0;

        for (j = 0; j < 16; j++)
            dir.game_name[j] = *game_name++;
        for (j = 0; j < 4; j++)
            dir.ext_name[j] = *ext_name++;

        ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->dir_table + *file_no, (u8 *)&dir, 0);
        if (ret != 0)
            return ret;
        return ret;
    } else {
        return 5;
    }
}

/* __osPfsDeclearPage, drafted from ultralib src/io/pfsallocatefile.c (2.0I branch): claim up to the
   requested number of free pages in one bank's inode table, linking them in order and clearing each
   claimed page on the pak. */

s32 __osPfsDeclearPage(OSPfs *pfs, __OSInode *inode, int file_size_in_pages, int *first_page, u8 bank,
                  int *decleared, int *last_page)
{
    int j;
    int spage;
    int old_page;
    u8 tmp_data[32];
    int i;
    s32 ret = 0;
    int offset = bank > 0 ? 1 : pfs->inode_start_page;

    for (j = offset; j < 128; j++) {
        if (inode->inode_page[j].ipage == 3) {
            break;
        }
    }

    if (j == 128) {
        *first_page = -1;
        return ret;
    }

    for (i = 0; i < 32; i++) {
        tmp_data[i] = 0;
    }

    spage = j;
    *decleared = 1;
    old_page = j;
    j++;

    while (file_size_in_pages > *decleared && j < 128) {
        if (inode->inode_page[j].ipage == 3) {
            inode->inode_page[old_page].inode_t.bank = bank;
            inode->inode_page[old_page].inode_t.page = j;
            ret = __osClearPage(pfs, old_page, tmp_data, bank);
            if (ret != 0)
                return ret;
            old_page = j;
            (*decleared)++;
        }
        j++;
    }

    *first_page = spage;

    if (j == 128 && file_size_in_pages > *decleared) {
        *last_page = old_page;
        return ret;
    } else {
        inode->inode_page[old_page].ipage = 1;
        ret = __osClearPage(pfs, old_page, tmp_data, bank);
        *last_page = 0;
        return ret;
    }
}

/* __osClearPage, drafted from ultralib src/io/pfsallocatefile.c (2.0I branch): select the given
   controller pak bank, write the caller's block to each of the page's eight blocks, then select
   bank zero again. */

s32 __osClearPage(OSPfs *pfs, int page_no, u8 *data, u8 bank)
{
    int i;
    s32 ret;

    ret = 0;
    pfs->activebank = bank;
    ret = Pfs_SelectActiveBank(pfs);
    if (ret != 0)
        return ret;
    for (i = 0; i < 8; i++) {
        ret = __osContRamWrite(pfs->queue, pfs->channel, page_no * 8 + i, data, 0);
        if (ret != 0) {
            break;
        }
    }
    pfs->activebank = 0;
    ret = Pfs_SelectActiveBank(pfs);
    return ret;
}

/* osPfsDeleteFile, drafted from ultralib src/io/pfsdeletefile.c (2.0I branch): find a controller pak
   file, free every page of its chain bank by bank, and write an empty directory entry in its place. */

extern s32 __osContRamRead(void *queue, int channel, u16 address, u8 *buffer);

s32 osPfsDeleteFile(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name)
{
    s32 file_no;
    int k;
    s32 ret;
    __OSInode inode;
    __OSDir dir;
    u16 sum = 0;
    __OSInodeUnit last_page;
    u8 startpage;
    u8 bank;

    if (company_code == 0 || game_code == 0) {
        return 5;
    }

    if ((pfs->status & 1) == 0)
        return 5;
    if (__osCheckId(pfs) == 2)
        return 2;
    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = Pfs_SelectActiveBank(pfs);
        if (ret != 0)
            return ret;
    }
    ret = osPfsFindFile(pfs, company_code, game_code, game_name, ext_name, &file_no);
    if (ret != 0)
        return ret;

    if (file_no == -1) {
        return 5;
    }
    ret = __osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8 *)&dir);
    if (ret != 0)
        return ret;

    startpage = dir.start_page.inode_t.page;

    for (bank = dir.start_page.inode_t.bank; bank < pfs->banks;) {
        ret = Pfs_ReadWriteInode(pfs, &inode, 0, bank);
        if (ret != 0)
            return ret;
        ret = __osPfsReleasePages(pfs, &inode, startpage, &sum, bank, &last_page, 1);
        if (ret != 0)
            return ret;
        ret = Pfs_ReadWriteInode(pfs, &inode, 1, bank);
        if (ret != 0)
            return ret;

        if (last_page.ipage == 1) {
            break;
        }

        bank = last_page.inode_t.bank;
        startpage = last_page.inode_t.page;
    }

    if (bank >= pfs->banks) {
        return 3;
    }

    dir.game_code = 0;
    dir.company_code = 0;
    dir.start_page.ipage = 0;
    dir.data_sum = 0;
    for (k = 0; k < 16; k++) {
        dir.game_name[k] = 0;
    }
    for (k = 0; k < 4; k++) {
        dir.ext_name[k] = 0;
    }
    dir.status = 0;

    ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8 *)&dir, 0);

    return ret;
}

/* __osPfsReleasePages, drafted from ultralib src/io/pfsdeletefile.c (2.0I branch): walk a file's page
   chain within one bank, marking each page free and summing its blocks, and report the link that
   leaves the bank. */

s32 __osPfsReleasePages(OSPfs *pfs, __OSInode *inode, u8 start_page, u16 *sum, u8 bank,
                  __OSInodeUnit *last_page, int flag)
{
    __OSInodeUnit next_page;
    __OSInodeUnit old_page;
    s32 ret;
    int offset;

    ret = 0;
    next_page = inode->inode_page[start_page];

    if (next_page.ipage != 1) {
        offset = (next_page.inode_t.bank > 0) ? 1 : pfs->inode_start_page;
    } else {
        offset = (bank > 0) ? 1 : pfs->inode_start_page;
    }

    if (next_page.inode_t.page < offset && next_page.ipage != 1) {
        return 3;
    }

    *last_page = next_page;

    if (flag == 1) {
        inode->inode_page[start_page].ipage = 3;
    }

    ret = __osBlockSum(pfs, start_page, sum, bank);
    if (ret != 0)
        return ret;

    if (next_page.ipage == 1) {
        return 0;
    }

    while (next_page.ipage >= pfs->inode_start_page) {
        old_page = next_page;
        next_page = inode->inode_page[next_page.inode_t.page];
        inode->inode_page[old_page.inode_t.page].ipage = 3;

        ret = __osBlockSum(pfs, old_page.inode_t.page, sum, bank);
        if (ret != 0)
            return ret;

        if (next_page.inode_t.bank != bank) {
            break;
        }
    }

    if (next_page.ipage >= pfs->inode_start_page && next_page.inode_t.bank == bank) {
        inode->inode_page[next_page.inode_t.page].ipage = 3;
    }

    *last_page = next_page;
    return 0;
}

/* __osBlockSum, drafted from ultralib src/io/pfsdeletefile.c (2.0I branch): select a bank, add the
   byte sum of each of one page's eight blocks to a running total, and select bank zero again. */

s32 __osBlockSum(OSPfs *pfs, u8 page_no, u16 *sum, u8 bank)
{
    int i;
    s32 ret;
    u8 data[32];

    ret = 0;
    pfs->activebank = bank;
    ret = Pfs_SelectActiveBank(pfs);
    if (ret != 0)
        return ret;
    for (i = 0; i < 8; i++) {
        ret = __osContRamRead(pfs->queue, pfs->channel, page_no * 8 + i, data);
        if (ret != 0) {
            pfs->activebank = 0;
            Pfs_SelectActiveBank(pfs);
            return ret;
        }
        *sum = *sum + Pfs_SumBytes(data, sizeof(data));
    }
    pfs->activebank = 0;
    ret = Pfs_SelectActiveBank(pfs);
    return ret;
}
