#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RECORDRECAT1C.H"
#include "OVLGAME/RENDER_BUFFER_RESOURCES.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "OVLGAME/NOTE_RELEASERENDERBUFFERS.H"

/* Clears a record: the words at offsets 0, 4, 8, 0x18 and 0x1C, and the three-word array at 0xC
   from its last entry down. */
void Note_ClearRenderRecord(struct RenderBufferResources *record) {
    s32 i;
    record->ready = 0;
    record->displayLists = 0;
    record->fifo = 0;
    record->zBuffer = 0;
    record->audioHeap = 0;
    for (i = 2; i >= 0; i--) {
        record->frameBuffers[i] = 0;
    }
}
/* Releases every resource handle the render buffer record holds and clears the record. */
void Note_ReleaseRenderBuffers(struct RenderBufferResources *record) {
    s32 j;
    s32 k;

    if (record->displayLists != NULL) {
        Cache_ReleaseResource(NULL, record->displayLists);
    }
    if (record->fifo != NULL) {
        Cache_ReleaseResource(NULL, record->fifo);
    }
    if (record->zBuffer != NULL) {
        Cache_ReleaseResource(NULL, record->zBuffer);
    }
    if (record->audioHeap != NULL) {
        Cache_ReleaseResource(NULL, record->audioHeap);
    }
    for (j = 0; j < 3; j++) {
        if (record->frameBuffers[j] != NULL) {
            Cache_ReleaseResource(NULL, record->frameBuffers[j]);
        }
    }
    record->ready = 0;
    record->displayLists = NULL;
    record->fifo = NULL;
    record->zBuffer = NULL;
    record->audioHeap = NULL;
    for (k = 2; k >= 0; k--) {
        record->frameBuffers[k] = NULL;
    }
}
