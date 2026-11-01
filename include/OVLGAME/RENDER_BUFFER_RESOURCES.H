#ifndef OVLGAME_RENDER_BUFFER_RESOURCES_H
#define OVLGAME_RENDER_BUFFER_RESOURCES_H
#include "TYPES.H"
struct CacheResourceBlockView;
/* The render buffer record (g_renderResourceRecord): the resource handles behind the render globals. */
struct RenderBufferResources {
    s32 ready;
    struct CacheResourceBlockView *displayLists;
    struct CacheResourceBlockView *fifo;
    struct CacheResourceBlockView *frameBuffers[3];
    struct CacheResourceBlockView *zBuffer;
    struct CacheResourceBlockView *audioHeap;
};
#endif
