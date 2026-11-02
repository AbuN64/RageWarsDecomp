#include "MENU/GFX/IMAGE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "UI/QUAG/N64_ENG.H"
#include "RESMGR/resmgr_stream_callbacks.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SLOTRECATCV1.H"
#include "TYPES.H"
#include "FRONTEND/NODE_GETIMAGETEXTURE.H"
#include "FRONTEND/NODE_RELEASECHUNKIMAGES.H"
#include "RESMGR/resmgr_stream_io.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/FRONTEND_CONFIGUREIMAGECONVERSION.H"
extern struct FrontendTextureTimerEntry *g_frontendResourceTextureTimers;
extern ArchiveTextureEntry *g_frontendResourceTextures;
extern FileState g_frontendResourceState;
extern void XStdio_CloseStream(s32 file);
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Frontend_ConfigureOwnedImage(s32 id, s32 format, s16 width, s16 height, s32 stride, s32 rows, s32 a6, s32 size, void *pixels, s32 a9, s32 paletteBytes, void *palette, s32 colors);

/* Tears down the UI resource set: releases eligible entries, closes active
   subsystems, frees each nested chunk allocation and the shared tables, then
   clears the complete state record. */






extern s16 g_frontendResourceTextureCount, g_frontendResourceFontCount;

extern struct ArchiveChunkImageListsView *g_frontendResourceFonts;


extern void Node_ReleaseRetainedImageSlot(s32 i);

extern void Node_ReleaseActiveChunkImages(void);

extern void Node_ReleaseUnprotectedBuffers(s32), Node_UpdateImageReleaseTimers(s32), Node_ReleaseAllChunkImages(void);


/* Expires cached UI resources against the current tick from N64Eng_GetFrameCounter unless the cache is
   locked: releases through Node_ReleaseRetainedImageSlot the first flagged entry whose unretained resource has an
   id below the tick and stops; otherwise, for each live chunk, clears every flagged slot whose time
   has passed (freeing its data through Image_ReleaseImage) and stops as soon as a chunk still holds live
   slots after one expires, freeing through Node_ReleaseChunkImages and clearing each chunk left empty. */

















/* Returns a texture's resource id, first loading its pixel and 16-bit palette data, detecting a transparent palette entry and creating the texture resource when it is not yet loaded, and in both cases updates the texture's usage record for the requested mode (1 stamps the next expiry time, 2 pins it, 3 counts a reference); the opened file handle is stored through the header symbol as in the paletted texture loader, and the resource id is held in two locals (the second passed to Smp_CopyAndSwizzleImage), which reproduces the cartridge's three stack slots. */
















extern void Frontend_ClearOwnedImage(s32 id);

extern s32 Smp_CopyAndSwizzleImage(struct GameImage *dst, struct GameImage *src);

static inline void touch(s32 index, s32 mode) {
    switch (mode) {
        case 1:
            if (g_frontendResourceTextureTimers[index].id != -1) {
                g_frontendResourceTextureTimers[index].id = N64Eng_GetFrameCounter() + 10;
            }
            break;
        case 2:
            g_frontendResourceTextureTimers[index].id = -1;
            break;
        case 3:
            g_frontendResourceTextureTimers[index].retained++;
            break;
    }
}

/* Loads texture and palette data, detects transparency and creates the requested texture resource, storing the opened file handle through the header symbol (a codegen choice that keeps the handle address separate from the header base). */










void Node_CloseResourceArchive(void) {
    s32 i;
    s32 invalid;
    s32 i_chunks;
    s32 offset_chunks;
    s32 offset;
    struct FrontendTextureTimerEntry *resource;
    struct ArchiveChunkImageListsView *chunk;
    void **block;
    void **tables;
    void **first;
    void **second;
    FileState *state;
    i = 0;
    if (g_frontendResourceTextureCount > 0) {
        invalid = -1;
        offset = 0;
        do {
            if (((ArchiveTextureEntry *)(offset + (s32)g_frontendResourceTextures))->flags & 1) {
                resource = g_frontendResourceTextureTimers + i;
                if (resource->id != invalid && resource->retained == 0) {
                    Node_ReleaseRetainedImageSlot(i);
                }
            }
            offset += 28;
        } while (++i < g_frontendResourceTextureCount);
    }
    Node_ReleaseActiveChunkImages();
    state = &g_frontendResourceState;
    if (state->streamHandle) XStdio_CloseStream(state->streamHandle);
    Node_ReleaseUnprotectedBuffers(1);
    Node_UpdateImageReleaseTimers(1);
    if (state->entries) Cache_FreeMemory(state->entries);
    i_chunks = 0;
    Node_ReleaseAllChunkImages();
    offset_chunks = 0;
    if (state->chunkCount > 0) {
        do {
            block = ((struct ArchiveChunkImageListsView *)(offset_chunks + (s32)g_frontendResourceFonts))->optional;
            if (block) {
                Cache_FreeMemory(*block);
                Cache_FreeMemory(((struct ArchiveChunkImageListsView *)(offset_chunks + (s32)g_frontendResourceFonts))->optional);
            }
            i_chunks++;
            Cache_FreeMemory(*((struct ArchiveChunkImageListsView *)(offset_chunks + (s32)g_frontendResourceFonts))->primary);
            block = ((struct ArchiveChunkImageListsView *)(offset_chunks + (s32)g_frontendResourceFonts))->primary;
            offset_chunks += 1180;
            Cache_FreeMemory(block);
        } while (i_chunks < g_frontendResourceFontCount);
    }
    tables = g_frontendResourceImagePool;
    if (tables[0]) Cache_FreeMemory(tables[0]);
    first = tables + 3;
    if (tables[3]) Cache_FreeMemory(tables[3]);
    second = tables + 2;
    if (tables[2]) Cache_FreeMemory(tables[2]);
    if (tables[13]) Cache_FreeMemory(tables[13]);
    if (tables[-1]) Cache_FreeMemory(tables[-1]);
    if (tables[10]) Cache_FreeMemory(tables[10]);
    if (tables[11]) Cache_FreeMemory(tables[11]);
    if (tables[-2]) Cache_FreeMemory(tables[-2]);
    if (tables[12]) Cache_FreeMemory(tables[12]);
    if (tables[7]) Cache_FreeMemory(tables[7]);
    if (first[5]) Cache_FreeMemory(first[5]);
    if (second[3]) Cache_FreeMemory(second[3]);
    XPlus_FillBytes((char *)tables - ((char *)&((FileState *)0)->pad26C - (char *)0), 0, 680);
}

void Node_EvictExpiredImages(void) {
    s32 now;
    s32 i;
    s32 j;
    s32 k;
    struct ArchiveOwnedImageSlot *slot;
    struct ArchiveOwnedImageSlot *slots;
    struct FrontendTextureTimerEntry *resource;

    now = N64Eng_GetFrameCounter();
    if (g_frontendResourceState.locked != 0) {
        return;
    }
    for (i = 0; i < g_frontendResourceState.count; i++) {
        if (g_frontendResourceState.entries[i].flags & 1) {
            resource = &g_frontendResourceState.resources[i];
            if (resource->id != -1 && resource->retained == 0 && resource->id < now) {
                Node_ReleaseRetainedImageSlot(i);
                return;
            }
        }
    }
    for (i = 0; i < g_frontendResourceState.chunkCount; i++) {
        if (g_frontendResourceState.chunks[i].live != 0 && g_frontendResourceState.chunks[i].active != 0) {
            for (j = 0; j < g_frontendResourceState.chunks[i].header->glyphCount; j++) {
                slots = g_frontendResourceState.chunks[i].slots[j];
                for (k = 0; k < 96; k++) {
                    slot = &slots[k];
                    if ((slot->flags & 1) && slot->owner < now) {
                        Image_ReleaseImage((struct OwnedImage *)slot->data);
                        slot->owner = 0;
                        slot->flags &= ~1;
                        g_frontendResourceState.chunks[i].live--;
                        if (g_frontendResourceState.chunks[i].live != 0) {
                            return;
                        }
                    }
                }
            }
            if (g_frontendResourceState.chunks[i].live == 0) {
                Node_ReleaseChunkImages(i);
                g_frontendResourceState.chunks[i].active = 0;
            }
        }
    }
}

s32 Node_GetImageTexture(s32 index, s32 mode) {
    s32 id;
    s32 texture;
    u16 *palette;
    void *pixels;
    s32 paletteBytes;
    s32 stride;
    s32 transparent;
    s32 size;
    s32 i;
    s32 format;
    ArchiveTextureEntry *entry;

    if (g_frontendResourceTextures[index].flags & 1) {
        touch(index, mode);
        return g_frontendResourceTextures[index].imageHandle;
    }
    palette = 0;
    paletteBytes = 0;
    id = g_frontendResourceTextures[index].imageHandle;
    stride = 0;
    N64Eng_GetTimeSeconds();
    ((FileState *)((char *)&g_frontendResourceFilename - 4))->streamHandle = XStdio_OpenStream(&g_frontendResourceFilename, &s_frontendResourceOpenMode);
    entry = &g_frontendResourceFilename.textureEntries[index];
    transparent = 0;
    if (entry->bitsPerPixel == 8) {
        stride = (entry->width + 7) & -8;
    } else if (entry->bitsPerPixel == 4) {
        stride = (entry->width + 15) & -16;
    } else if (entry->bitsPerPixel == 16) {
        stride = (entry->width + 3) & -4;
    }
    Frontend_ClearOwnedImage(id);
    texture = id;
    size = stride * entry->height * entry->bitsPerPixel / 8;
    pixels = Cache_AllocateMemory(size);
    XStdio_SeekStream(g_frontendResourceState.streamHandle, g_frontendResourceState.textureDataOffset + entry->pixelOffset, 0);
    XStdio_ReadStream(pixels, size, 1, g_frontendResourceState.streamHandle);
    if (entry->paletteCount > 0) {
        paletteBytes = entry->paletteCount * 2;
        palette = Cache_AllocateMemory(paletteBytes);
        XStdio_SeekStream(g_frontendResourceState.streamHandle, g_frontendResourceState.textureDataOffset + entry->paletteOffset, 0);
        XStdio_ReadStream(palette, paletteBytes, 1, g_frontendResourceState.streamHandle);
        for (i = 0; i < entry->paletteCount; i++) {
            if (!(palette[i] & 1)) {
                transparent = 1;
                g_frontendResourceChromaKeys[index] = palette[i];
                break;
            }
        }
        if (i == entry->paletteCount) {
            transparent = 0;
            g_frontendResourceChromaKeys[index] = 0xFF000000;
        }
    }
    format = -1;
    if (entry->paletteCount > 0) {
        if (entry->bitsPerPixel == 8) {
            format = 32;
            if (transparent) {
                format = 30;
            }
        } else {
            format = 22;
            if (transparent) {
                format = 20;
            }
        }
    } else if (entry->bitsPerPixel == 16) {
        format = 5;
    } else if (entry->bitsPerPixel == 24) {
        format = 8;
    } else if (entry->bitsPerPixel == 32) {
        format = 12;
    }
    Frontend_ConfigureOwnedImage(id, format, entry->width, entry->height, stride, entry->height, 1, size, pixels, 1, paletteBytes,
                  palette, entry->paletteCount);
    Smp_CopyAndSwizzleImage(texture, id);
    g_frontendResourceTextures[index].flags |= 1;
    XStdio_CloseStream(g_frontendResourceState.streamHandle);
    g_frontendResourceState.streamHandle = 0;
    N64Eng_GetTimeSeconds();
    touch(index, mode);
    return g_frontendResourceTextures[index].imageHandle;
}

void Node_LoadTextureIntoOutput(s32 index, s32 output) {
    s32 *palette;
    s32 *pixels;
    s32 paletteBytes;
    s32 stride;
    s32 transparent;
    s32 size;
    s32 i;
    s32 format;
    ArchiveTextureEntry *entry;

    if (g_frontendResourceTextures[index].flags & 1) {
        Frontend_CopyOwnedImage(output, g_frontendResourceTextures[index].imageHandle);
        return;
    }
    palette = 0;
    paletteBytes = 0;
    stride = 0;
    ((FileState *)((char *)&g_frontendResourceFilename - 4))->streamHandle = XStdio_OpenStream(&g_frontendResourceFilename, &s_frontendResourceOpenMode);
    entry = &g_frontendResourceFilename.textureEntries[index];
    transparent = 0;
    if (entry->bitsPerPixel == 8) {
        stride = (entry->width + 7) & -8;
    } else if (entry->bitsPerPixel == 4) {
        stride = (entry->width + 15) & -16;
    } else if (entry->bitsPerPixel == 16) {
        stride = (entry->width + 3) & -4;
    }
    size = stride * entry->height * entry->bitsPerPixel / 8;
    pixels = Cache_AllocateMemory(size);
    XStdio_SeekStream(g_frontendResourceState.streamHandle, g_frontendResourceState.textureDataOffset + entry->pixelOffset, 0);
    XStdio_ReadStream(pixels, size, 1, g_frontendResourceState.streamHandle);
    if (entry->paletteCount > 0) {
        paletteBytes = entry->paletteCount * 2;
        palette = Cache_AllocateMemory(paletteBytes);
        XStdio_SeekStream(g_frontendResourceState.streamHandle, g_frontendResourceState.textureDataOffset + entry->paletteOffset, 0);
        XStdio_ReadStream(palette, paletteBytes, 1, g_frontendResourceState.streamHandle);
        for (i = 0; i < entry->paletteCount; i++) {
            if (!(palette[i] & 0xFF000000)) {
                transparent = 1;
                g_frontendResourceChromaKeys[index] = palette[i];
                break;
            }
        }
        if (i == entry->paletteCount) {
            transparent = 0;
            g_frontendResourceChromaKeys[index] = 0xFF000000;
        }
    }
    format = -1;
    if (entry->paletteCount > 0) {
        if (entry->bitsPerPixel == 8) {
            format = 32;
            if (transparent) {
                format = 30;
            }
        } else {
            format = 22;
            if (transparent) {
                format = 20;
            }
        }
    } else if (entry->bitsPerPixel == 16) {
        format = 28;
    } else if (entry->bitsPerPixel == 24) {
        format = 8;
    } else if (entry->bitsPerPixel == 32) {
        format = 12;
    }
    Frontend_ConfigureOwnedImage(output, format, entry->width, entry->height, stride, entry->height, 1, size, pixels, 1, paletteBytes,
                  palette, entry->paletteCount);
    XStdio_CloseStream(g_frontendResourceState.streamHandle);
    g_frontendResourceState.streamHandle = 0;
}
