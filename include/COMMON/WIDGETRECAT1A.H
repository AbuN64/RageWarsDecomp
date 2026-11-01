#ifndef COMMON_WIDGETRECAT1A_H
#define COMMON_WIDGETRECAT1A_H
#include "TYPES.H"
#include "COMMON/LONE/G_TEXTVERTICALOFFSET.H"
#include "COMMON/LONE/G_TEXTLINEHEIGHT.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
struct WidgetPointHitView;
struct WidgetPointHitView {
    char pad0[4];
    struct WidgetPointHitView *next;
    struct WidgetPointHitView *child;
    s16 id;
    u16 selector;
    char pad10[4];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};


struct Widget;

struct WidgetTreePositionView;
typedef struct WidgetTreePositionView WidgetTreePositionView;

struct WidgetTreePositionView;
struct WidgetTreePositionView {
    struct WidgetTreePositionView *parent;
    struct WidgetTreePositionView *next;
    struct WidgetTreePositionView *child;
    char padC[2];
    u16 type;
    char pad10[0x1C];
};


struct t_dldc;
typedef struct t_dldc sm_dldc;

extern int g_widgetTextBatchMode;

struct NodeFrontendReplaceWidgetLinks;
struct NodeFrontendReplaceWidgetLinks {
    struct NodeFrontendReplaceWidgetLinks *parent;
    struct NodeFrontendReplaceWidgetLinks *nextSibling;
    struct NodeFrontendReplaceWidgetLinks *firstChild;
};


struct WidgetNode;
struct WidgetNode {
    struct WidgetNode *next;
    char pad4[0xC - 4];
    s16 resource; /* +0x0C: selected resource identifier */
    char padE[0x12 - 0xE];
    unsigned short flags;
    s16 x; /* +0x14: widget position */
    s16 y; /* +0x16 */
};

struct WidgetNode;

struct WidgetNode;


struct WidgetReferenceNodeView;
typedef struct WidgetReferenceNodeView WidgetReferenceNodeView;

struct WidgetFrontendDrawImageWidget;
struct WidgetFrontendDrawImageWidget {
    char pad0[0x12];
    u16 flags;
    char pad14[0x18];
    s32 image;
};

struct WidgetFrontendDrawImageWidget;
typedef struct WidgetFrontendDrawImageWidget WidgetFrontendDrawImageWidget;

struct Widget;

struct Widget;

struct Tree;

struct BatchRec;
typedef struct BatchRec BatchRec;

struct WidgetNode;

struct NodeFrontendReplaceWidgetLinks;
typedef struct NodeFrontendReplaceWidgetLinks NodeFrontendReplaceWidgetLinks;

struct WidgetLayout;
struct WidgetLayout {
    char pad0[0x10];
    u8 alpha;
    char pad11;
    u16 flags;
    s16 x, y;
    s16 width, height;
    s16 offsetX, offsetY;
    f32 scaleX, scaleY;
    s32 reservedWord;
    u32 colors[4];
};

struct MenuWidget;

struct Tree;
struct Tree {
    struct Tree *parent;
    struct Tree *next;
    struct Tree *child;
    short id;
    char pad0E[0x6];
    short reservedHalfwordFirst;
    short reservedHalfwordSecond;
};
typedef struct Tree Tree;

struct DrawArgsFrontendDrawVisibleWidgetClipped;
struct DrawArgsFrontendDrawVisibleWidgetClipped {
    s32 x;
    s32 y;
    s32 flags;
    f32 scaleX;
    f32 scaleY;
    s32 v[5];
};

struct WidgetAncestorOffsetView;
struct WidgetAncestorOffsetView {
    struct WidgetAncestorOffsetView *next;
    char pad4[0x14 - 4];
    s16 x;
    s16 y;
};

struct WidgetAncestorOffsetView;

struct t_dldc;
struct t_dldc {
    s32 x;
    s32 y;
    s32 flags;
    f32 XScale;
    f32 YScale;
    u8 alpha;
    u8 pad15[3];
    struct CacheResourceBlockView Rgn;
};

struct WidgetNode;

struct Pair14;

struct WidgetFrontendUpdateSliderGeometry;
struct WidgetFrontendUpdateSliderGeometry {
    char pad0[0x14];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};
struct Slider;
struct WidgetFrontendUpdateSliderGeometry;
struct Slider {
    char pad0[0xC];
    s16 parentId;
    char padE[0x36];
    s32 min;
    s32 max;
    s32 step;
    s32 value;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    struct WidgetFrontendUpdateSliderGeometry *thumb;
    struct WidgetFrontendUpdateSliderGeometry *fill;
    s32 flags;
};

struct Slider;
typedef struct Slider Slider;


struct WidgetLayout;
typedef struct WidgetLayout WidgetLayout;

struct WidgetReferenceNodeView;
struct WidgetReferenceNodeView {
    char pad0[4];
    struct WidgetReferenceNodeView *left;
    struct WidgetReferenceNodeView *right;
    char padC[2];
    u16 kind;
    char pad10[2];
    u16 flags;
    char pad14[0x18];
    void *ref2C;
    void *ref30;
    void *ref34;
    void *ref38;
    char pad3C[8];
    void *ref44;
};

struct DrawArgsFrontendDrawVisibleWidgetClipped;
typedef struct DrawArgsFrontendDrawVisibleWidgetClipped DrawArgsFrontendDrawVisibleWidgetClipped;

struct WidgetPointHitView;
typedef struct WidgetPointHitView WidgetPointHitView;


extern int g_textBatchFontId;






struct MenuWidget;

struct BatchRec;
struct CacheResourceBlockView;
struct TextSprite;
struct BatchRec {
    struct CacheResourceBlockView area;
    struct TextSprite *cursor;
    s32 count;
};

char *Node_GetStringByIndex(s32);
s32 Node_CompareRecordShortValuesRomEntry(char *, char *);
#endif
