#ifndef FRONTEND_ARCHIVEDATA_H
#define FRONTEND_ARCHIVEDATA_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/LAYOUT.H"
/* Records of the menu resource archive as they sit in memory after the archive header is read. */
/* One entry of the resource map (g_frontendResourceScreens, 12 bytes): the entry's offset in the archive data
   and size, and the buffer it was loaded into (0 while not loaded). */
typedef struct ArchiveMapEntry {
    s32 offset;
    s32 size;
    void *data;
} ArchiveMapEntry;
/* One entry of the text index (the section table of the string archive, 8 bytes): where the
   section of NUL-separated strings starts, relative to the archive base, and how many strings it holds. */
typedef struct ArchiveTextIndexEntry {
    s32 start;
    s32 count;
} ArchiveTextIndexEntry;
/* One font record of the archive (32 bytes, read at ROM header word 2; three fonts): the glyph cell
   width, the count of bitmaps, and where the font's 0x60 glyph records and the bitmap sizes sit. The
   halfwords at 0xA, 0xC and 0x10 (spacing, line height) are read by Node_GetFontMetricAtA, Node_GetFontMetricAtC and
   Node_GetFontLetterSpacing; bytes 0..7, 0x12 and the word at 0x1C have no reader. */
typedef struct ArchiveFontRecord {
    u8 unused0[8];
    s16 glyphWidth;
    s16 verticalOffset;
    s16 lineHeight;
    s16 bitmapCount;
    s16 letterSpacing;
    s16 unused12;
    s32 glyphTableOffset;
    s32 bitmapSizesOffset;
    s32 unused1C;
} ArchiveFontRecord;
/* Records of the menu resource file (original names from the debug type catalog). */
/* One texture of the resource's texture table (28 bytes). */
typedef struct _sm_texture_element {
    struct OwnedImage *VramAddr;
    u32 SMFlags;
    s16 BitsPerPixel;
    s16 Width;
    s16 Height;
    s16 NClutColors;
    u16 Flags;
    s16 TPage;
    s32 ImageOffset;
    s32 ClutOffset;
} _sm_texture_element;

/* One glyph of a font (8 bytes). */

/* One cached glyph image (44 bytes). */
typedef struct t_char {
    s32 unusedGlyphWord;
    s32 CharTimer;
    u16 SMFlags;
    struct OwnedImage Vram;
} t_char;

/* One open font (0x49C bytes): its 96 glyphs, their cached images per clut and its font table entry. */
typedef struct _sm_font {
    s32 Active;
    sm_font_char CharInfo[96];
    u8 *CharBits[96];
    t_char **Char;
    u8 **Clut;
    ArchiveFontRecord *TableEntry;
    u8 NumInUse;
    struct FrontendTextureTimerEntry FontTimer;
} _sm_font;

/* The resource file header (0x54 bytes): where each table sits in the file and how long it is. */
typedef struct t_res_header {
    s32 TextureTable;
    s32 TextureTableLen;
    s32 FontTable;
    s32 FontTableLen;
    s32 FontClutTable;
    s32 FontClutTableLen;
    s32 FontData;
    s32 FontDataLen;
    s32 LanguageTable;
    s32 LanguageTableLen;
    s32 StringTable;
    s32 StringTableLen;
    s32 ScreenTable;
    s32 ScreenTableLen;
    s32 ScreenData;
    s32 ScreenDataLen;
    s32 TextureData;
    s32 TextureDataLen;
    s32 CharData;
    s32 CharDataLen;
    s32 FirstScreen;
} t_res_header;

/* The open menu resource (g_frontendResourceState, 0x2A8 bytes). */
typedef struct t_resource {
    s32 In;
    char Name[512];
    s32 Init;
    t_res_header Header;
    s16 NTextures;
    _sm_texture_element *Texture;
    u32 *ChromaKey;
    struct FrontendTextureTimerEntry *TexTimer;
    struct OwnedImage *VramPool;
    s16 NFonts;
    ArchiveFontRecord *FontTable;
    _sm_font *Font;
    s16 NLanguages;
    ArchiveTextIndexEntry *LangTable;
    s32 CurrentLanguage;
    char *StringBuffer;
    char **StringTable;
    s16 NScreens;
    ArchiveMapEntry *Screen;
    ArchiveMapEntry *ScreenOriginal;
    s16 *ScreenFlags;
    s16 *RefCount;
    s32 NeverFreeResources;
} t_resource;

extern t_resource g_frontendResourceState;
#endif
