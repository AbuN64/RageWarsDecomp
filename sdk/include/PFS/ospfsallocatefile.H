#ifndef PFS_OSPFSALLOCATEFILE_H
#define PFS_OSPFSALLOCATEFILE_H
#include "../OSCONTREQUESFORMATSHORT.H"
extern s32 __osPfsDeclearPage(OSPfs *pfs, __OSInode *inode, int file_size_in_pages, int *first_page, u8 bank,
                         int *decleared, int *last_page);
extern s32 __osClearPage(OSPfs *pfs, int page_no, u8 *data, u8 bank);
extern s32 __osPfsReleasePages(OSPfs *pfs, __OSInode *inode, u8 start_page, u16 *sum, u8 bank,
                         __OSInodeUnit *last_page, int flag);
extern s32 __osBlockSum(OSPfs *pfs, u8 page_no, u16 *sum, u8 bank);
#endif
