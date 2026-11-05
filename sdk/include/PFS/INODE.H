#ifndef PFS_INODE_H
#define PFS_INODE_H
#include "types.h"

union __OSInodeUnit {
    struct {
        u8 bank;
        u8 page;
    } inode_t;
    u16 ipage;
};

typedef union __OSInodeUnit __OSInodeUnit;

struct __OSInode {
    __OSInodeUnit inode_page[128];
};

typedef struct __OSInode __OSInode;

#endif
