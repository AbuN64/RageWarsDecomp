#ifndef LIBULTRA_PFS_PFS_H
#define LIBULTRA_PFS_PFS_H
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "TYPES.H"
extern s32 __osCheckPackId(OSPfs*pfs, __OSPackId*temp);
extern s32 __osRepairPackId(OSPfs*pfs, __OSPackId*badid, __OSPackId*newid);
#endif
