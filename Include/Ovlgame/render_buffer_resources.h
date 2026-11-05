#ifndef OVLGAME_RENDER_BUFFER_RESOURCES_H
#define OVLGAME_RENDER_BUFFER_RESOURCES_H
#include "types.h"
struct CacheResourceNode;
/* The render buffer record (g_renderResourceRecord): the resource handles behind the render globals. */
struct RenderBufferResources {
    s32 ready;
    struct CacheResourceNode *displayLists;
    struct CacheResourceNode *fifo;
    struct CacheResourceNode *frameBuffers[3];
    struct CacheResourceNode *zBuffer;
    struct CacheResourceNode *audioHeap;
};
#endif
