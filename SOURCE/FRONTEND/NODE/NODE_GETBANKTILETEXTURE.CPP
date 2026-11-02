#include "MENU/GFX/IMAGE.H"
#include "UI/QUAG/N64_ENG.H"
#include "RESMGR/resmgr_stream_callbacks.H"
#include "include_asm.h"
#include "COMMON/SLOTRECATCV1.H"
#include "TYPES.H"
#include "RESMGR/resmgr_stream_io.H"

/* Advances the deferred-release timers: for each of the g_frontendResourceTextureCount slots (all reset first when mode
   is 1) whose owner is not -1, counts the delay down, and once it has run out releases the slot's
   loaded resource data through Image_ReleaseImage, clearing its loaded flag, and clears the owner. */







extern ArchiveImageReleasePool g_frontendResourceTextureCount;


void Node_UpdateImageReleaseTimers(s32 mode) {
    s32 i;

    for (i = 0; i < g_frontendResourceTextureCount.count; i++) {
        if (mode == 1) {
            g_frontendResourceTextureCount.timers[i].delay = 0;
            g_frontendResourceTextureCount.timers[i].owner = 0;
        }
        if (g_frontendResourceTextureCount.timers[i].owner != -1) {
            if (g_frontendResourceTextureCount.timers[i].delay > 0) {
                g_frontendResourceTextureCount.timers[i].delay--;
            } else {
                if (g_frontendResourceTextureCount.resources[i].flags & 1) {
                    Image_ReleaseImage((struct OwnedImage *)g_frontendResourceTextureCount.resources[i].data);
                    g_frontendResourceTextureCount.resources[i].flags &= ~1;
                }
                g_frontendResourceTextureCount.timers[i].owner = 0;
            }
        }
    }
}

typedef struct {
    char pad0[0x20];
} Texture;
typedef struct {
    char pad0[4];
    s32 stamp;
    u16 flags;
    char pad0A[2];
    Texture texture;
} TextureSlot;
typedef struct {
    s32 offset;
    s8 fmt;
    s8 siz;
    s8 wid;
    char pad7[1];
} Tile;
typedef struct {
    s32 f0;
    s32 f4;
    s16 depth;
    s16 f0A;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 base;
    s32 size;
} BankImage;
typedef struct {
    s32 loaded;
    Tile tiles[96];
    u8 *offsets[96];
    TextureSlot **slotsByPass;
    s32 **listsByPass;
    BankImage *image;
    u8 loads;
    char pad491[3];
    s32 stamp;
    s16 held;
    char pad49A[2];
} Bank;
typedef struct {
    char pad0[0x30];
    s32 base;
    char pad34[0x24];
    Bank *banks;
} Tables;
typedef struct {
    s32 handle;
    s32 name;
    char pad8[0x218];
    Tables tables;
} File;
extern File g_frontendResourceState;
extern char s_frontendResourceOpenMode;
extern struct Record *Cache_AllocateMemory(s32 size);
extern void XStdio_CloseStream(s32 handle);
extern void Frontend_ClearOwnedImage(Texture *texture);
extern void Frontend_ReleaseOwnedImageBuffers(Texture *texture);
extern void Frontend_ConfigureOwnedImage(Texture *texture, s32 kind, s8 fmt, s8 siz, s32 wid, s32 siz2, s32 zero,
                          s32 bytes, void *offset, s32 zero2, s32 pitch, s32 *list, s32 depth);
extern void Image_SwizzleImage(struct SwizzledImageView *image);
extern s32 Smp_CopyAndSwizzleImage(struct GameImage *dst, struct GameImage *src);
extern void Smp_SetImageStateWord(s32 flag);

void *Node_GetBankTileTexture(u8 which, s32 group, s32 pass) {
    s32 sizes[96];
    Texture scratch;
    Texture *texture;
    Texture *into;
    BankImage *image;
    s32 kind;
    Tile *tile;
    TextureSlot *slot;
    s32 threshold;
    Bank *bank;
    TextureSlot *slots;
    s32 index;
    s32 code;
    s32 stamp;
    s32 size;
    s32 bytes;
    s32 i;

    slots = g_frontendResourceState.tables.banks[group].slotsByPass[pass];
    index = which;
    {
    if (slots[index].flags & 1) {
        Bank *cachedBank;
        stamp = N64Eng_GetFrameCounter() + 10;
        slots[index].stamp = stamp;
        cachedBank = &g_frontendResourceState.tables.banks[group];
        if (cachedBank->held == 0 && cachedBank->stamp != -1) {
            cachedBank->stamp = stamp;
        }
        return &slots[which].texture;
    }
    }
    kind = 0;
    N64Eng_GetTimeSeconds();
    image = g_frontendResourceState.tables.banks[group].image;
    tile = &g_frontendResourceState.tables.banks[group].tiles[index];
    slot = &slots[index];
    code = 0;
    if (tile->fmt == 0 || tile->siz == 0) {
        return 0;
    }
    texture = &slot->texture;
    Frontend_ClearOwnedImage(texture);
    into = texture;
    if (image->depth == 0) {
        code = 32;
    } else if (image->depth < 17) {
        code = 4;
    } else if (image->depth < 257) {
        code = 8;
    }
    if (image->depth > 0) {
        kind = 20;
        if (code == 8) {
            kind = 30;
        }
    } else if (code == 16) {
        kind = 28;
    } else if (code == 24) {
        kind = 8;
    } else if (code == 32) {
        kind = 12;
    }
    if (g_frontendResourceState.tables.banks[group].loaded == 0) {
        Tables *tables = &g_frontendResourceState.tables;

        bank = &tables->banks[group];
        g_frontendResourceState.handle = XStdio_OpenStream(&g_frontendResourceState.name, &s_frontendResourceOpenMode);
        size = bank->image->size;
        i = 0;
        bank->offsets[0] = Cache_AllocateMemory(size);
        XStdio_SeekStream(g_frontendResourceState.handle, g_frontendResourceState.tables.base + bank->image->base, 0);
        XStdio_ReadStream(g_frontendResourceState.tables.banks[group].offsets[0], size, 1, g_frontendResourceState.handle);
        do {
            sizes[i] = bank->tiles[i].wid * bank->tiles[i].siz;
            sizes[i] = sizes[i] * code / 8;
            bank->offsets[i] = bank->offsets[0] + (bank->tiles[i].offset - bank->image->base);
            i += 1;
        } while (i < 96);
        threshold = 0x1000;
        if (image->depth > 0) {
            threshold = 0x800;
        }
        i = 0;
        do {
            if (threshold < sizes[i]) {
                Tile *big = &g_frontendResourceState.tables.banks[group].tiles[i];

                Frontend_ClearOwnedImage(&scratch);
                Frontend_ConfigureOwnedImage(&scratch, kind, big->fmt, big->siz, big->wid, big->siz, 0, sizes[i],
                              g_frontendResourceState.tables.banks[group].offsets[i], 0, image->depth * 2,
                              g_frontendResourceState.tables.banks[group].listsByPass[pass], image->depth);
                Image_SwizzleImage(&scratch);
                Frontend_ReleaseOwnedImageBuffers(&scratch);
            }
            i += 1;
        } while (i < 96);
        XStdio_CloseStream(g_frontendResourceState.handle);
        g_frontendResourceState.handle = 0;
        bank->loaded = 1;
    }
    bytes = tile->wid * tile->siz * code >> 3;
    Frontend_ConfigureOwnedImage(texture, kind, tile->fmt, tile->siz, tile->wid, tile->siz, 0,
                  bytes, g_frontendResourceState.tables.banks[group].offsets[which], 0,
                  image->depth * 2, g_frontendResourceState.tables.banks[group].listsByPass[pass], image->depth);
    Smp_SetImageStateWord(0);
    Smp_CopyAndSwizzleImage(into, texture);
    Smp_SetImageStateWord(1);
    N64Eng_GetTimeSeconds();
    slot->stamp = N64Eng_GetFrameCounter() + 10;
    g_frontendResourceState.tables.banks[group].loads += 1;
    slot->flags |= 1;
    return &slot->texture;
}
