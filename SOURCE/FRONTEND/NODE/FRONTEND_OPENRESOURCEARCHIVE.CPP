#include "COMMON/FRUSTUM.H"
#include "MENU/GFX/IMAGE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/LONE/FRONTEND_VIEWPORT_WIDTH.H"
#include "RESMGR/resmgr_stream_callbacks.H"
#include "include_asm.h"
#include "COMMON/NODERECAT2A8.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "COMMON/SLOTRECATCV1.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"
#include "FRONTEND/NODE_RELEASECHUNKIMAGES.H"
#include "RESMGR/resmgr_stream_io.H"
#include "UI/QUAG/N64_ENG.H"
#include "SCENE/CACHE_FREEMEMORY.H"
extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *, struct CacheResourceBlockView *, WidgetLayout *, sm_dldc *);
#include "RESMGR/resmgr_string_memory.H"
#include "AUDIO/VOICE.H"

/* Puts a new node in a tree node's place, taking over its parent and next links and becoming the parent's first child or the successor of the predecessor Node_FindWidgetPredecessor's search finds, then makes the old node the new node's only child with its next link and the halfwords at 0x14 and 0x16 cleared.
   Adapted from Node_InsertWidgetBefore with the new node taking the old node's next link and child position and the old node's links reset afterwards changed. */



extern struct Tree *Node_FindWidgetPredecessor(struct Tree *node, s32 id);

static inline struct Tree *findPredecessor(struct Tree *node, s32 id) {
    s32 childId;
    struct Tree *found = 0;

    childId = id;
    while (node != 0 && found == 0) {
        if (node->next != 0 && node->next->id == (u16)id) {
            found = node;
        }
        if (found == 0 && node->child != 0) {
            found = Node_FindWidgetPredecessor(node->child, (u16)childId);
        }
        node = node->next;
    }
    return found;
}

/* Measures the pixel width of a string of the given length in the given font by summing each character's signed width byte from the font record Node_GetGlyphBuffer returns, then adding the spacing Node_GetFontLetterSpacing reports once between each pair of characters.
   Adapted from SoundVoicePool_Initialize with the two clears and per-record call replaced by the font lookup, the width sum and the spacing term changed. */





extern GlyphBuffer *Node_GetGlyphBuffer(s32 index);

extern short Node_GetFontLetterSpacing(s32 index);

/* Draws a widget's variant image: when Widget_ComputeWidgetBounds accepts the widget at the position, picks the
   pressed (flag 0x100), highlighted (flag 0x40) or normal image of the widget, and when present
   moves the position back by the image's offset scaled by the style's scale factors and draws it
   through Widget_DrawWidget with the same flags and style. */













extern void Widget_DrawWidget(struct Pair14 *image, Triple at, Style style);

/* Draws the child at 0x8 of a window with the arguments passed by value after clearing g_frontendRenderStateInitialized once Widget_ComputeWidgetBounds resolves the window's rectangle, and when flag 0x200 of the halfword at 0x12 is set it saves the four values N64Eng_GetClipBounds reports, narrows them by the resolved basis through Node_ClampRectToClip_FrontendOpenresourcearchive, giving up when it fails, and installs them through N64Eng_SetClipBounds around the draw, restoring the saved values after it. Adapted from SmpOverlay_DrawOverlayWidget_FrontendOpenresourcearchive with g_frontendRenderStateInitialized cleared before the rectangle is resolved, the resolved basis declared first, and a failed Node_ClampRectToClip_FrontendOpenresourcearchive ending the function. */












extern void Widget_DrawVisibleSiblings(void *, Args);


/* Records the last column and row of a width by height area: stores width - 1 and height - 1 in
   g_frontendViewportWidth and g_frontendViewportHeight, and fills the rectangle g_frontendClipBounds with zero to width - 1 and zero
   to height - 1. */




extern struct CacheResourceBlockView g_frontendClipBounds;

/* Releases every loaded slot of the active, referenced entries of the pool at g_frontendResourceFontCount: each
   loaded slot (flag 1) has its data released through Image_ReleaseImage, its flags and owner cleared and
   the entry's reference count decremented, and an entry left without references is unloaded
   through Node_ReleaseChunkImages and marked inactive. Pool layout and indexed slot access follow Node_ReleaseChunkImages. */









extern PoolFrontendReleaseActiveChunkImages g_frontendResourceFontCount;


/* Relocates a loaded widget list and its children from the stored base to base: for widgets
   flagged 0x10 rebases the four resource words, then by widget type clears an out-of-range image
   index (type 3), rebases the extra pointer and marks the widget 0x800 (type 2), clears the fourth
   word (type 4) or turns the three packed resource references (index and offset) into pointers,
   acquiring resources through Node_AcquireArchiveEntry and marking them in g_frontendResourceScreenFlags as needed (type 8);
   it then rebases the name (clearing it for an empty type 2 widget), the child list, which it
   relocates recursively, and the next pointer. */



extern s16 g_frontendResourceTextureCount;



extern void Node_AcquireArchiveEntry(s32 index);

static inline void Node_ResolveWidgetResourceReference(UiWidget *widget) {
    UiWidget *w;
    u32 index;
    s32 offset;
    s32 data;

    w = widget;
    index = (u32)(w->words[0] & 0xFFFF0000) >> 16;
    offset = w->words[0] & 0xFFFF;
    if (index != 0 || offset != 0) {
        data = Node_GetScreenData(index);
        if (data == 0) {
            Node_AcquireArchiveEntry(index);
            data = Node_GetScreenData(index);
            g_frontendResourceScreenFlags[index] |= 1;
        }
        w->words[0] = data + offset;
    }
    index = (u32)(w->words[1] & 0xFFFF0000) >> 16;
    offset = w->words[1] & 0xFFFF;
    if (index != 0 || offset != 0) {
        data = Node_GetScreenData(index);
        if (data == 0) {
            Node_AcquireArchiveEntry(index);
            data = Node_GetScreenData(index);
            g_frontendResourceScreenFlags[index] |= 1;
        }
        w->words[1] = data + offset;
    }
    index = (u32)(w->words[2] & 0xFFFF0000) >> 16;
    offset = w->words[2] & 0xFFFF;
    if (index != 0 || offset != 0) {
        data = Node_GetScreenData(index);
        if (data == 0) {
            Node_AcquireArchiveEntry(index);
            data = Node_GetScreenData(index);
            g_frontendResourceScreenFlags[index] |= 1;
        }
        w->words[2] = data + offset;
    }
}

void Node_WrapNodeInParent(struct Tree *node, struct Tree *added) {
    struct Tree *parent;

    added->child = node;
    added->parent = node->parent;
    added->next = node->next;
    parent = node->parent;
    if (parent->child == node) {
        parent->child = added;
    } else {
        findPredecessor(parent, (u16)node->id)->next = added;
    }
    node->next = 0;
    node->parent = added;
    node->reservedHalfwordFirst = 0;
    node->reservedHalfwordSecond = 0;
}

/* Walks a node tree recursively, replacing every reference to one pointer with another in each node's link fields. */



void Node_ReplaceNodeRefs(WidgetReferenceNodeView *node, void *from, void *to) {
    if (node != 0) {
        if (node->left != 0) {
            Node_ReplaceNodeRefs(node->left, from, to);
        }
        if (node->right != 0) {
            Node_ReplaceNodeRefs(node->right, from, to);
        }
        if (node->flags & 0x10) {
            if (node->ref30 == from) {
                node->ref30 = to;
            }
            if (node->ref34 == from) {
                node->ref34 = to;
            }
            if (node->ref38 == from) {
                node->ref38 = to;
            }
            if (node->ref2C == from) {
                node->ref2C = to;
            }
        }
        if (node->kind == 2) {
            if (node->ref44 == from) {
                node->ref44 = to;
            }
        }
    }
}

/* Swaps two widgets within the widget tree: after walking up from the first widget to the root
   (type 2), it finds each widget's predecessor in its parent's child list, links the other widget
   in its place (as the predecessor's next or the parent's first child), and swaps the two widgets'
   parent and next links. */



void Node_SwapWidgetTreePositions(WidgetTreePositionView *a, WidgetTreePositionView *b) {
    WidgetTreePositionView *w;
    WidgetTreePositionView *cursorA;
    WidgetTreePositionView *cursorB;
    WidgetTreePositionView saved;

    cursorA = a;
root:
    if (cursorA->type != 2) {
        cursorA = cursorA->parent;
        goto root;
    }
    cursorA = a->parent;
    w = cursorA->child;
    cursorA = 0;
    goto testA;
nextA:
    w = cursorA->next;
testA:
    if (w != a) {
        cursorA = w;
        if (cursorA != 0) {
            goto nextA;
        }
    }
    cursorB = b->parent;
    w = cursorB->child;
    cursorB = 0;
    goto testB;
nextB:
    w = cursorB->next;
testB:
    if (w != b) {
        cursorB = w;
        if (cursorB != 0) {
            goto nextB;
        }
    }
    if (cursorA != 0) {
        cursorA->next = b;
    } else {
        a->parent->child = b;
    }
    if (cursorB != 0) {
        cursorB->next = a;
    } else {
        b->parent->child = a;
    }
    saved = *a;
    a->next = b->next;
    a->parent = b->parent;
    b->next = saved.next;
    b->parent = saved.parent;
}

s32 Node_MeasureTextPrefix(s32 font, u8 *text, s32 length) {
    GlyphBuffer *record;
    s32 i;
    s32 total;

    record = Node_GetGlyphBuffer(font);
    total = 0;
    for (i = 0; i < length; i++) {
        total += record->glyphs[*text++ - 32].width;
    }
    total += Node_GetFontLetterSpacing(font) * (length - 1);
    return total;
}

/* Stores two bytes at offsets 0x2C and 0x2D of a record, a pair set together. */


void Node_SetRecordBytePair(struct Pair2C *record, u8 first, u8 second) {
    record->first = first;
    record->second = second;
}

/** Store a word at offset 0x2c. */
void Node_SetObjectWordAt2C(void *object, int value) {
    FrontendArchiveHandleView *record = object;
    record->archiveHandle = value;
}

/** Store a word at offset 0x2c. */
void Node_AssignObjectWordAt2C(void *object, int value) {
    FrontendArchiveHandleView *record = object;
    record->archiveHandle = value;
}

/* Stores four values into the consecutive words at offsets 0x2C to 0x38 of a record. */


void Node_SetRecordValueQuad(struct WidgetRecordValueQuadView *record, s32 first, s32 second, s32 third, s32 fourth) {
    record->values[0] = first;
    record->values[1] = second;
    record->values[2] = third;
    record->values[3] = fourth;
}

void Node_DrawButtonImage(ButtonWidget *widget, Triple at, Style style) {
    Shared_Quad box0;
    Shared_Quad box1;
    struct Pair14 *image;

    if (Widget_ComputeWidgetBounds((struct CacheResourceBlockView *)&box0, (struct CacheResourceBlockView *)&box1, (WidgetLayout *)widget, (sm_dldc *)&at) != 0) {
        if (at.z & 0x100) {
            image = widget->pressed;
        } else if (at.z & 0x40) {
            image = widget->highlighted;
        } else {
            image = widget->normal;
        }
        if (image != 0) {
            at.x -= (s32)(image->first * style.scaleX);
            at.y -= (s32)(image->second * style.scaleY);
            Widget_DrawWidget(image, at, style);
        }
    }
}

void Node_DrawClippedChildren(WidgetLayout *widget, Args args) {
    QuadN64EngDrawNumericWidgetChildren basis;
    QuadN64EngDrawNumericWidgetChildren value;
    QuadN64EngDrawNumericWidgetChildren transformed;
    QuadN64EngDrawNumericWidgetChildren first;
    s32 changed;
    UiWidget *window = widget;

    changed = 0;
    g_frontendRenderStateInitialized = 0;
    if (Widget_ComputeWidgetBounds((struct CacheResourceBlockView *)&first, (struct CacheResourceBlockView *)&basis, widget, (sm_dldc *)&args) != 0) {
        if ((window->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.x, &value.z, &value.y, &value.w);
            transformed = value;
            if (Node_ClampRectToClip(&transformed, &basis) == 0) {
                return;
            }
            N64Eng_SetClipBounds(transformed.x, transformed.z,
                          transformed.y, transformed.w);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(window->children, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.x, value.z, value.y, value.w);
        }
    }
}

/* Intersects a rectangle with another in place, widening it to at least one unit and returning whether it was non-empty. */



s32 Node_ClampRectToClip(struct CacheResourceBlockView *rect, struct CacheResourceBlockView *clip) {
    s32 ok;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 v;

    x0 = rect->first;
    ok = 1;
    if (x0 < clip->first) {
        x0 = clip->first;
    }
    x1 = rect->second;
    rect->first = x0;
    if (clip->second < x1) {
        x1 = clip->second;
    }
    y0 = rect->third;
    rect->second = x1;
    if (y0 < clip->third) {
        y0 = clip->third;
    }
    y1 = rect->fourth;
    rect->third = y0;
    if (clip->fourth < y1) {
        y1 = clip->fourth;
    }
    rect->fourth = y1;
    v = rect->first + 1;
    if (rect->second < v) {
        rect->second = v;
        ok = 0;
    }
    v = rect->third + 1;
    if (rect->fourth < v) {
        rect->fourth = v;
        ok = 0;
    }
    return ok;
}

void Node_SetDisplayClipBounds(s32 width, s32 height) {
    struct CacheResourceBlockView *rect = &g_frontendClipBounds;

    width--;
    height--;
    g_frontendViewportWidth = width;
    g_frontendViewportHeight = height;
    rect->third = 0;
    rect->first = 0;
    rect->second = width;
    rect->fourth = height;
}

/** Perform no work. */
void Node_NoOperation(void) {
}

/* Orders two records by the unsigned halfword at offset 0x14, returning the difference in the
   shape a sort comparator uses. */


int Node_CompareRecordShortValues(struct Field_u16_14 *a, struct Field_u16_14 *b) {
    return a->value - b->value;
}

void Node_ReleaseActiveChunkImages(void) {
    s32 e;
    s32 n;
    s32 i;
    ArchiveOwnedImageSlot *slot;

    for (e = 0; e < g_frontendResourceFontCount.count; e++) {
        if (g_frontendResourceFontCount.entries[e].refCount != 0 && g_frontendResourceFontCount.entries[e].active != 0) {
            for (n = 0; n < g_frontendResourceFontCount.entries[e].def->glyphCount; n++) {
                slot = g_frontendResourceFontCount.entries[e].pages[n];
                for (i = 0; i < 96; i++) {
                    if (slot[i].flags & 1) {
                        Image_ReleaseImage((struct OwnedImage *)slot[i].data);
                        slot[i].flags = 0;
                        slot[i].owner = 0;
                        g_frontendResourceFontCount.entries[e].refCount--;
                    }
                }
            }
            if (g_frontendResourceFontCount.entries[e].refCount == 0) {
                Node_ReleaseChunkImages(e);
                g_frontendResourceFontCount.entries[e].active = 0;
            }
        }
    }
}

void Node_RelocateWidgetTree(UiWidget *widget, s32 base, s32 old) {
    for (; widget != 0; widget = widget->next) {
        if (widget->flags & 0x10) {
            if (widget->words[0] != 0) {
                widget->words[0] = widget->words[0] + base - old;
            }
            if (widget->words[1] != 0) {
                widget->words[1] = widget->words[1] + base - old;
            }
            if (widget->words[2] != 0) {
                widget->words[2] = widget->words[2] + base - old;
            }
            if (widget->words[3] != 0) {
                widget->words[3] = widget->words[3] + base - old;
            }
        }
        switch (widget->type) {
            case 3:
                if (widget->words[0] < 0 || g_frontendResourceTextureCount - 1 < widget->words[0]) {
                    widget->words[0] = 0;
                }
                break;
            case 2:
                if (widget->extra != 0) {
                    widget->extra = widget->extra + base - old;
                }
                widget->flags |= 0x800;
                break;
            case 4:
                widget->words[3] = 0;
                break;
            case 8:
                Node_ResolveWidgetResourceReference(widget);
                break;
        }
        if ((widget->name != 0 && (widget->next != 0 || widget->children != 0)) || widget->type != 2) {
            widget->name = widget->name + base - old;
        } else {
            widget->name = 0;
        }
        if (widget->children != 0) {
            widget->children = (UiWidget *)((s32)widget->children + base - old);
            Node_RelocateWidgetTree(widget->children, base, old);
        }
        if (widget->next != 0) {
            widget->next = (UiWidget *)((s32)widget->next + base - old);
        }
    }
}

#include "FRONTEND/ARCHIVEDATA.H"
#include "FRONTEND/LAYOUT.H"
struct Record *Cache_AllocateMemory(s32 size);
u8 *XPlus_CopyString(u8 *dst, u8 *src);
void XStdio_CloseStream(s32 handle);
void Node_LoadLanguageStrings(s32 index);
void Cache_FreeMemory(void *allocation);

/* Loads the string table of resource archive section index: frees the previous string buffer and
 * pointer table, reads the section's bytes from the archive file into a fresh buffer (its size is the
 * distance to the next section's start, or to the archive end for the last one), then builds the table of
 * string starts: entry 0 is the buffer, and every byte after a terminating zero starts the next string. */
void Node_LoadLanguageStrings(s32 languageIndex) {
    s32 stringCount;
    s32 bufferSize;
    s32 stringIndex;
    s32 closeArchive;
    u8 *character;

    closeArchive = 0;
    stringCount = g_frontendResourceState.LangTable[languageIndex].count;
    if (g_frontendResourceState.StringBuffer != 0) {
        Cache_FreeMemory(g_frontendResourceState.StringBuffer);
    }
    g_frontendResourceState.StringBuffer = 0;
    if (g_frontendResourceState.StringTable != 0) {
        Cache_FreeMemory(g_frontendResourceState.StringTable);
    }
    g_frontendResourceState.StringTable = 0;
    if (languageIndex < g_frontendResourceState.NLanguages - 1) {
        bufferSize = g_frontendResourceState.LangTable[languageIndex + 1].start - g_frontendResourceState.LangTable[languageIndex].start;
    } else {
        bufferSize = g_frontendResourceState.Header.StringTableLen - g_frontendResourceState.LangTable[languageIndex].start;
    }
    g_frontendResourceState.StringBuffer = Cache_AllocateMemory(bufferSize);
    XStdio_SeekStream(g_frontendResourceState.In, g_frontendResourceState.LangTable[languageIndex].start + g_frontendResourceState.Header.StringTable, 0);
    XStdio_ReadStream(g_frontendResourceState.StringBuffer, bufferSize, 1, g_frontendResourceState.In);
    if (closeArchive) {
        XStdio_CloseStream(g_frontendResourceState.In);
        g_frontendResourceState.In = 0;
    }
    g_frontendResourceState.StringTable = Cache_AllocateMemory(stringCount << 2);
    g_frontendResourceState.StringTable[0] = g_frontendResourceState.StringBuffer;
    stringIndex = 1;
    for (character = (u8 *)g_frontendResourceState.StringBuffer + 1; character < (u8 *)g_frontendResourceState.StringBuffer + bufferSize && stringIndex < stringCount; character++) {
        if (*character == 0) {
            g_frontendResourceState.StringTable[stringIndex] = (char *)character + 1;
            stringIndex++;
        }
    }
}

/* Opens the menu archive NAME: reads its table of contents, then its image table (with a fresh image
   and load state per entry), its text index (loading section 0), its resource map (with copies when
   g_frontendArchiveResident is set) and its fonts with their bitmap pages and glyph rows; records the name and closes
   the file. */
void Node_OpenResourceArchive(u8 *name) {
    t_resource *res;
    s32 handle;
    _sm_texture_element *texture;
    ArchiveFontRecord *entry;
    _sm_font *font;
    s32 *clutOffsets;
    s32 stride;
    s32 clut;
    s32 i;
    s32 n;
    s32 j;

    res = &g_frontendResourceState;
    handle = XStdio_OpenStream(name, &s_frontendResourceOpenMode);
    res->In = handle;
    XStdio_ReadStream(&g_frontendResourceState.Header, sizeof(t_res_header), 1, handle);
    g_frontendResourceState.NTextures = g_frontendResourceState.Header.TextureTableLen / sizeof(_sm_texture_element);
    if (g_frontendResourceState.NTextures > 0) {
        g_frontendResourceState.VramPool = Cache_AllocateMemory(g_frontendResourceState.NTextures * sizeof(struct OwnedImage));
        g_frontendResourceState.TexTimer = Cache_AllocateMemory(g_frontendResourceState.NTextures * sizeof(struct FrontendTextureTimerEntry));
        g_frontendResourceState.ChromaKey = Cache_AllocateMemory(g_frontendResourceState.NTextures * sizeof(void *));
        texture = g_frontendResourceState.Texture = Cache_AllocateMemory(g_frontendResourceState.Header.TextureTableLen);
        XStdio_SeekStream(res->In, g_frontendResourceState.Header.TextureTable, 0);
        XStdio_ReadStream(texture, sizeof(_sm_texture_element), g_frontendResourceState.NTextures, res->In);
        for (i = 0; i < g_frontendResourceState.NTextures; i++, texture++) {
            texture->SMFlags = 0;
            texture->TPage = 0;
            g_frontendResourceState.TexTimer[i].retained = 0;
            g_frontendResourceState.TexTimer[i].id = 0;
            g_frontendResourceState.Texture[i].VramAddr = &g_frontendResourceState.VramPool[i];
            Image_ResetImage(&g_frontendResourceState.VramPool[i]);
        }
    }
    g_frontendResourceState.NLanguages = g_frontendResourceState.Header.LanguageTableLen / sizeof(ArchiveTextIndexEntry);
    if (g_frontendResourceState.NLanguages > 0) {
        g_frontendResourceState.LangTable = Cache_AllocateMemory(g_frontendResourceState.Header.LanguageTableLen);
        XStdio_SeekStream(res->In, g_frontendResourceState.Header.LanguageTable, 0);
        XStdio_ReadStream(g_frontendResourceState.LangTable, g_frontendResourceState.Header.LanguageTableLen, 1, res->In);
        Node_LoadLanguageStrings(0);
    }
    g_frontendResourceState.NScreens = g_frontendResourceState.Header.ScreenTableLen / sizeof(ArchiveMapEntry);
    if (g_frontendResourceState.NScreens > 0) {
        g_frontendResourceState.Screen = Cache_AllocateMemory(g_frontendResourceState.Header.ScreenTableLen);
        if (g_frontendArchiveResident != 0) {
            g_frontendResourceState.ScreenOriginal = Cache_AllocateMemory(g_frontendResourceState.Header.ScreenTableLen);
            XPlus_FillBytes(g_frontendResourceState.ScreenOriginal, 0, g_frontendResourceState.Header.ScreenTableLen);
        }
        XStdio_SeekStream(res->In, g_frontendResourceState.Header.ScreenTable, 0);
        XStdio_ReadStream(g_frontendResourceState.Screen, g_frontendResourceState.Header.ScreenTableLen, 1, res->In);
        for (i = 0; i < g_frontendResourceState.NScreens; i++) {
            g_frontendResourceState.Screen[i].data = 0;
        }
        g_frontendResourceState.RefCount = Cache_AllocateMemory(g_frontendResourceState.NScreens * sizeof(s16));
        XPlus_FillBytes(g_frontendResourceState.RefCount, 0, g_frontendResourceState.NScreens * sizeof(s16));
        g_frontendResourceState.ScreenFlags = Cache_AllocateMemory(g_frontendResourceState.NScreens * sizeof(s16));
        XPlus_FillBytes(g_frontendResourceState.ScreenFlags, 0, g_frontendResourceState.NScreens * sizeof(s16));
    }
    if (g_frontendResourceState.Header.FontTableLen > 0) {
        clutOffsets = Cache_AllocateMemory(g_frontendResourceState.Header.FontClutTableLen);
        XStdio_SeekStream(res->In, g_frontendResourceState.Header.FontClutTable, 0);
        XStdio_ReadStream(clutOffsets, g_frontendResourceState.Header.FontClutTableLen, 1, res->In);
        g_frontendResourceState.FontTable = Cache_AllocateMemory(g_frontendResourceState.Header.FontTableLen);
        XStdio_SeekStream(res->In, g_frontendResourceState.Header.FontTable, 0);
        XStdio_ReadStream(g_frontendResourceState.FontTable, g_frontendResourceState.Header.FontTableLen, 1, res->In);
        g_frontendResourceState.NFonts = g_frontendResourceState.Header.FontTableLen / sizeof(ArchiveFontRecord);
        g_frontendResourceState.Font = Cache_AllocateMemory(g_frontendResourceState.NFonts * sizeof(_sm_font));
        XPlus_FillBytes(g_frontendResourceState.Font, 0, g_frontendResourceState.NFonts * sizeof(_sm_font));
        for (i = 0; i < g_frontendResourceState.NFonts; i++) {
            g_frontendResourceState.Font[i].TableEntry = &g_frontendResourceState.FontTable[i];
        }
        clut = 0;
        for (n = 0; n < g_frontendResourceState.NFonts; n++) {
            entry = g_frontendResourceState.Font[n].TableEntry;
            font = &g_frontendResourceState.Font[n];
            XStdio_SeekStream(res->In, g_frontendResourceState.Header.FontData + entry->glyphTableOffset, 0);
            XStdio_ReadStream(font->CharInfo, 8, 96, res->In);
            font->Char = Cache_AllocateMemory(entry->bitmapCount * sizeof(t_char *));
            font->Char[0] = Cache_AllocateMemory(entry->bitmapCount * 96 * sizeof(t_char));
            XPlus_FillBytes(font->Char[0], 0, entry->bitmapCount * 96 * sizeof(t_char));
            for (j = 0; j < entry->bitmapCount; j++) {
                font->Char[j] = font->Char[0] + j * 96;
            }
            if (entry->bitmapCount > 0) {
                stride = (entry->glyphWidth * 2 + 7) & ~7;
                font->Clut = Cache_AllocateMemory(entry->bitmapCount * sizeof(t_char *));
                font->Clut[0] = Cache_AllocateMemory(entry->bitmapCount * stride);
                XStdio_SeekStream(res->In, g_frontendResourceState.Header.CharData + clutOffsets[clut], 0);
                XStdio_ReadStream(font->Clut[0], entry->bitmapCount * stride, 1, res->In);
                for (j = 0; j < entry->bitmapCount; j++) {
                    font->Clut[j] = font->Clut[0] + j * stride;
                }
                if (n < 0) {
                    stride = 0;
                }
                clut += entry->bitmapCount;
            }
        }
        Cache_FreeMemory(clutOffsets);
    } else {
        g_frontendResourceState.NFonts = 0;
    }
    g_frontendResourceState.Init = 1;
    XPlus_CopyString(g_frontendResourceState.Name, name);
    g_frontendResourceState.NeverFreeResources = 0;
    XStdio_CloseStream(g_frontendResourceState.In);
    g_frontendResourceState.In = 0;
}
