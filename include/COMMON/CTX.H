#ifndef COMMON_CTX_H
#define COMMON_CTX_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
struct OsThreadQueueNode;
struct OsThreadQueueNode {
    s32 runQueueNextWord;
    s32 priority;
    void *queue;
    struct OsThreadQueueNode *next;
    u16 state;
};





struct Ctx;
typedef struct Ctx Ctx;

struct Ctx;
struct Ctx {
    OSMesgQueue *cur;
    s32 f4;
};



struct OsThreadQueueNode;
typedef struct OsThreadQueueNode OsThreadQueueNode;


#endif
