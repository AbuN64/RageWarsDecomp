#ifndef FRONTEND_LAYOUT_H
#define FRONTEND_LAYOUT_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/FORMAT.H"
struct MenuWidget;

extern s32 Node_DispatchTypedWidgetEvent(void *element, s32 event, s32 source, s32 parameter, s32 value);




struct Layout;
typedef struct Layout Layout;



struct GridList;
struct GridList {
    char pad0[0x48];
    u8 columns;
    u8 rows;
};

struct EntryFrontendSetGridCellValues;
struct IntPair;
struct EntryFrontendSetGridCellValues {
    char pad_00[0x44];
    struct IntPair *cells;
    u8 pad_48[3];
    u8 width;
};

struct OwnedImage;



struct ObjectFrontendDestroyGridList;
struct ObjectFrontendDestroyGridList {
    char pad[0x44];
    void *child;
};

struct Layout;
struct Layout {
    s32 pad0[5];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s32 pad1C[4];
};


struct MenuWidget;

struct OwnedImage;
struct OwnedImage {
    u8 stream;
    u8 flags;
    s16 width;
    s16 height;
    s16 stride;
    s16 rowCount;
    s16 paletteEntries;
    char padC[4];
    s32 paletteCount;
    void *palette;
    void *pixels;
    s32 resourceId;
};

struct OwnedImage;

struct t_dltext;
typedef struct t_dltext sm_dltext;

struct t_dltext;
struct t_dltext {
    Layout Hdr;
    u8 Font;
    u8 FontClut;
    u8 FontHighlighted;
    u8 FontHighlightedClut;
    s32 pad30[2];
    s32 pString;
};


struct GridList;
typedef struct GridList GridList;

struct EntryFrontendSetGridDimensionArrays;
struct EntryFrontendSetGridDimensionArrays {
    char pad[0x58];
    s32 first;
    s32 second;
};


struct EntryFrontendSetGridCellValues;
typedef struct EntryFrontendSetGridCellValues EntryFrontendSetGridCellValues;



struct sm_dllistbox;
struct sm_dllistbox {
    Layout layout;
    s32 pad2C[6];
    s32 *contents;
    char pad48[3];
    u8 columns;
    u8 selectedRow;
    u8 selectedCol;
    u8 rowScroll;
    u8 colScroll;
    u8 headerRows;
    u8 headerCols;
    u8 headerFg;
    u8 headerBg;
    u8 fg;
    u8 bg;
    u8 selectedFg;
    u8 selectedBg;
    s32 *widths;
    s32 *heights;
};


struct OwnedImage;
typedef struct OwnedImage OwnedImage;



struct sm_dllistbox;
typedef struct sm_dllistbox sm_dllistbox;


typedef struct ImageDescriptor { u8 format; char pad1[7]; s16 width; char padA[0xA]; void *pixels, *palette; } ImageDescriptor;
extern Format g_destinationPixelFormat;
extern Format g_sourcePixelFormat;
extern void (*g_writeDestinationColor)(void);
extern void (*g_readSourceColor)(void);
extern void (*g_writeDestinationIndex)(void);
extern void (*g_readSourceIndex)(void);
extern void g_Frontend_WriteDestinationHalfwordPixelAddress(void);
extern void g_Frontend_WriteDestinationThreeBytePixelAddress(void);
extern void g_Frontend_WriteDestinationWordPixelAddress(void);
extern void g_Frontend_WriteDestinationNibbleIndexAddress(void);
extern void g_Frontend_WriteDestinationByteIndexAddress(void);
extern void g_Frontend_ReadSourceHalfwordPixelAddress(void);
extern void g_Frontend_ReadSourceThreeBytePixelAddress(void);
extern void g_Frontend_ReadSourceWordPixelAddress(void);
extern void g_Frontend_ReadSourceNibbleIndexAddress(void);
extern void g_Frontend_ReadSourceByteIndexAddress(void);
extern void g_Frontend_UseHalfwordPixelOffsetAddress(void);
extern void g_Frontend_UseThreeBytePixelOffsetAddress(void);
extern void g_Frontend_UseWordPixelOffsetAddress(void);
#endif
