#ifndef COMMON_SLOTRECATCV1_H
#define COMMON_SLOTRECATCV1_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
struct ArchiveChunkImageSlot;
struct ArchiveChunkImageSlot {
    char pad0[8];
    u16 flags;
    char padA[2];
    char data[32];
};

struct ArchiveChunkImageEntry;
struct ArchiveChunkImageSlot;
struct ArchiveChunkImageEntry {
    s32 active;
    char pad4[0x300];
    void *buffers[96];
    struct ArchiveChunkImageSlot **ns;
    char pad488[4];
    FontGlyphCountView *def;
    char pad490[0xC];
};
struct ArchiveChunkImageEntry;
struct PoolFrontendReleaseChunkImages;
struct PoolFrontendReleaseChunkImages {
    s16 count;
    char pad2[6];
    struct ArchiveChunkImageEntry *entries;
};


extern void Node_SkipResourceOperation(void);

struct ArchiveTextureEntry;
typedef struct ArchiveTextureEntry ArchiveTextureEntry;


struct ArchiveOwnedImageSlot;
struct ArchiveOwnedImageSlot {
    char pad0[4];
    s32 owner;
    u16 flags;
    char padA[2];
    char data[32];
};


struct ArchiveChunkImageListsView;
struct ArchiveChunkImageListsView {
    char pad[0x484];
    void **primary;
    void **optional;
    char rest[16];
};


struct ResourceFrontendUpdateImageReleaseTimers;
struct ResourceFrontendUpdateImageReleaseTimers {
    void *data;
    s32 flags;
    char pad8[0x14];
};
struct TimerFrontendUpdateImageReleaseTimers;
struct TimerFrontendUpdateImageReleaseTimers {
    s32 owner;
    s16 delay;
};
struct ArchiveImageReleasePool;
struct ResourceFrontendUpdateImageReleaseTimers;
struct TimerFrontendUpdateImageReleaseTimers;
struct ArchiveImageReleasePool {
    s16 count;
    struct ResourceFrontendUpdateImageReleaseTimers *resources;
    s32 timerCount;
    struct TimerFrontendUpdateImageReleaseTimers *timers;
};

struct Field_u16_14;


extern int g_frontendResourceFirstScreen;




struct WidgetRecordValueQuadView;
struct WidgetRecordValueQuadView {
    char pad[0x2C];
    s32 values[4];
};

extern s32 Node_GetFirstResourceScreen(void);

struct PoolFrontendReleaseChunkImages;
typedef struct PoolFrontendReleaseChunkImages PoolFrontendReleaseChunkImages;

struct ButtonWidget;
typedef struct ButtonWidget ButtonWidget;



struct ArchiveChunkImageSlot;
typedef struct ArchiveChunkImageSlot ArchiveChunkImageSlot;



extern s16 Node_GetTextureEntryHeight(s32 index);

struct ArchiveOwnedImageEntry;
struct ArchiveOwnedImageSlot;
struct ArchiveOwnedImageEntry {
    s32 active;
    char pad4[0x300];
    void *buffers[96];
    struct ArchiveOwnedImageSlot **pages;
    char pad488[4];
    FontGlyphCountView *def;
    unsigned char refCount;
    char pad491[0xB];
};
struct ArchiveOwnedImageEntry;
struct PoolFrontendReleaseActiveChunkImages;
struct PoolFrontendReleaseActiveChunkImages {
    s16 count;
    char pad2[6];
    struct ArchiveOwnedImageEntry *entries;
};

struct Style;
struct Style {
    f32 scaleX;
    f32 scaleY;
    s32 v[5];
};

struct UiWidget;
struct UiWidget {
    s32 name;
    struct UiWidget *next;
    struct UiWidget *children;
    char padC[2];
    u16 type;
    char pad10[2];
    u16 flags;
    char pad14[0x18];
    s32 words[4];
    char pad3C[8];
    s32 extra;
};

extern s16 Node_GetResourceScreenCount(void);

struct FileHeader;
typedef struct FileHeader FileHeader;

struct ArchiveTextureEntry;
struct ArchiveTextureEntry {
    s32 imageHandle;
    s32 flags;
    s16 bitsPerPixel;
    s16 width;
    s16 height;
    s16 paletteCount;
    s32 reservedWord;
    s32 pixelOffset;
    s32 paletteOffset;
};

struct ArchiveTextureEntry;
struct FileHeader;
struct FileHeader {
    char pad0[0x25C];
    struct ArchiveTextureEntry *textureEntries;
};

struct UiWidget;
typedef struct UiWidget UiWidget;

struct Pair2C;
struct Pair2C {
    char pad[0x2C];
    u8 first;
    u8 second;
};

struct Pair2C;

extern s16 Node_GetTextureEntryWidth(s32 index);



struct ArchiveOwnedImageSlot;
typedef struct ArchiveOwnedImageSlot ArchiveOwnedImageSlot;

struct Style;
typedef struct Style Style;



struct ArchiveImageReleasePool;
typedef struct ArchiveImageReleasePool ArchiveImageReleasePool;

struct Pair14;
struct ButtonWidget;
struct ButtonWidget {
    char pad0[0x2C];
    struct Pair14 *normal;
    struct Pair14 *highlighted;
    struct Pair14 *pressed;
};

struct FileState;
struct ArchiveTextureDataEntryView;
struct FrontendTextureTimerEntry;
struct ChunkFrontendEvictExpiredImages;
struct FileState {
    s32 streamHandle;
    char pad4[0x244];
    s32 textureDataOffset;
    char pad24C[0x10];
    s16 count;
    struct ArchiveTextureDataEntryView *entries;
    char pad264[4];
    struct FrontendTextureTimerEntry *resources;
    char pad26C[4];
    s16 chunkCount;
    char pad272[6];
    struct ChunkFrontendEvictExpiredImages *chunks;
    char pad27C[0x28];
    s32 locked;
};

struct PoolFrontendReleaseActiveChunkImages;
typedef struct PoolFrontendReleaseActiveChunkImages PoolFrontendReleaseActiveChunkImages;

struct FileState;
typedef struct FileState FileState;

struct WidgetRecordValueQuadView;

extern s32 Node_GetTextureChromaKey(s32 index);

struct ChunkFrontendEvictExpiredImages;
struct ArchiveOwnedImageSlot;
struct FontGlyphCountView;
struct ChunkFrontendEvictExpiredImages {
    void *active;
    char pad4[0x480];
    struct ArchiveOwnedImageSlot **slots;
    char pad488[4];
    struct FontGlyphCountView *header;
    u8 live;
    char pad491[0xB];
};
struct ChunkFrontendEvictExpiredImages;
struct ArchiveTextureDataEntryView;
struct FrontendTextureTimerEntry;
#endif
