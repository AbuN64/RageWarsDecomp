#ifndef LIBULTRA_PFS_PFS_H
#define LIBULTRA_PFS_PFS_H
#include "Common/player_pool_and_inode_cache_views.h"
#include "types.h"
typedef struct __OSDir {
    u32 game_code;
    u16 company_code;
    __OSInodeUnit start_page;
    u8 status;
    s8 reserved;
    u16 data_sum;
    u8 ext_name[4];
    u8 game_name[16];
} __OSDir;

extern s32 __osCheckPackId(OSPfs*pfs, __OSPackId*temp);
extern s32 __osRepairPackId(OSPfs*pfs, __OSPackId*badid, __OSPackId*newid);
#endif
