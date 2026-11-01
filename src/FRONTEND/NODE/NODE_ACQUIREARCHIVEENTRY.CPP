#include "MENU/GFX/IMAGE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "UI/QUAG/N64_ENG.H"
#include "RESMGR/resmgr_stream_callbacks.H"
#include "include_asm.h"
#include "COMMON/SLOTRECATCV1.H"
#include "TYPES.H"
#include "FRONTEND/NODE_RELEASECHUNKIMAGES.H"
#include "FRONTEND/ARCHIVEDATA.H"
#include "RESMGR/resmgr_stream_io.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* Unloads entry index of the pool at g_frontendResourceFontCount: releases the data of every loaded slot (flag 1) in
   each of the entry's slot ns (the n count comes from the entry's definition) through
   Image_ReleaseImage and clears the flag, frees the entry's buffer through Cache_FreeMemory and clears the
   buffer table when one is held, and marks the entry inactive. */









extern PoolFrontendReleaseChunkImages g_frontendResourceFontCount;


void Node_ReleaseChunkImages(s32 index) {
    s32 n;
    s32 i;
    ArchiveChunkImageSlot *slot;

    for (n = 0; n < g_frontendResourceFontCount.entries[index].def->glyphCount; n++) {
        slot = g_frontendResourceFontCount.entries[index].ns[n];
        for (i = 0; i < 96; i++) {
            if (slot[i].flags & 1) {
                Image_ReleaseImage((struct OwnedImage *)slot[i].data);
                slot[i].flags &= ~1;
            }
        }
    }
    if (g_frontendResourceFontCount.entries[index].buffers[0] != 0) {
        Cache_FreeMemory(g_frontendResourceFontCount.entries[index].buffers[0]);
        g_frontendResourceFontCount.entries[index].buffers[0] = 0;
        for (n = 0; n < 96; n++) {
            g_frontendResourceFontCount.entries[index].buffers[n] = 0;
        }
    }
    g_frontendResourceFontCount.entries[index].active = 0;
}

extern struct Record *Cache_AllocateMemory(s32 size);

extern void Node_RelocateWidgetTree(void *, void *, s32);
extern void XStdio_CloseStream(s32);

/* Loads entry index of the menu archive into memory and counts the use: in cache mode 1 an entry
   already loaded is restored from its saved copy and rebased; otherwise an entry not yet loaded is
   read from the archive file into a new buffer (and copied into a second buffer when copies are
   kept) and rebased. */
void Node_AcquireArchiveEntry(s32 index) {
    void *data;
    g_frontendResourceState.RefCount[index]++;
    if (g_frontendResourceState.NeverFreeResources == 1) {
        if (g_frontendResourceState.Screen[index].data == 0) goto load;
        XPlus_CopyBytes(g_frontendResourceState.Screen[index].data, g_frontendResourceState.ScreenOriginal[index].data, g_frontendResourceState.Screen[index].size);
        data = g_frontendResourceState.Screen[index].data;
        Node_RelocateWidgetTree(data, data, g_frontendResourceState.Screen[index].offset - g_frontendResourceState.Screen[0].offset);
    }
    if (g_frontendResourceState.Screen[index].data != 0) return;
load:
    N64Eng_GetTimeSeconds();
    g_frontendResourceState.Screen[index].data = Cache_AllocateMemory(g_frontendResourceState.Screen[index].size);
    g_frontendResourceState.In = XStdio_OpenStream(g_frontendResourceState.Name, &s_frontendResourceOpenMode);
    XStdio_SeekStream(g_frontendResourceState.In, g_frontendResourceState.Header.ScreenData + g_frontendResourceState.Screen[index].offset, 0);
    XStdio_ReadStream(g_frontendResourceState.Screen[index].data, g_frontendResourceState.Screen[index].size, 1, g_frontendResourceState.In);
    if (g_frontendArchiveResident != 0) {
        g_frontendResourceState.ScreenOriginal[index].data = Cache_AllocateMemory(g_frontendResourceState.Screen[index].size);
        XPlus_CopyBytes(g_frontendResourceState.ScreenOriginal[index].data, g_frontendResourceState.Screen[index].data, g_frontendResourceState.Screen[index].size);
    }
    XStdio_CloseStream(g_frontendResourceState.In);
    g_frontendResourceState.In = 0;
    data = g_frontendResourceState.Screen[index].data;
    Node_RelocateWidgetTree(data, data, g_frontendResourceState.Screen[index].offset - g_frontendResourceState.Screen[0].offset);
    N64Eng_GetTimeSeconds();
}
