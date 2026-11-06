#include "include_asm.h"
#include "Data/Gfxdata/event_handler_code_targets.h"
#include "Data/Ui/type_text_event_table.h"
#include "Common/frontend_video_mode.h"
#include "Common/selectionscreenstate.h"
#include "Common/widget_tree.h"
#include "types.h"
#include "Frontend/archivedata.h"
#include "Common/frustum.h"
#include "Menu/Gfx/image.h"
#include "Common/runtime_declarations.h"
#include "Common/Lone/frontend_viewport_width.h"
#include "Resmgr/resmgr_stream_callbacks.h"
#include "Menu/widget_records.h"
#include "Common/sharedplayer.h"
#include "Common/archive_chunk_images.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Frontend/node_releasechunkimages.h"
#include "Resmgr/resmgr_stream_io.h"
#include "Ui/Quag/N64_Eng.h"
#include "Scene/cache_freememory.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Audio/voice.h"
#include "Frontend/node_getimagetexture.h"
#include "Frontend/frontend_configureimageconversion.h"
#include "Node/node_getbanktiletexture.h"
#include "Image/image.h"
#include "Ui/smp.h"
#include "Cache/cache_allocatememory.h"
#include "X_stdio/x_stdio.h"
#include "Frontend/frontend_address_symbols.h"
#include "Common/resident_event_handler.h"
#include "Common/aiprofile.h"
#include "Common/widget_texture_retention.h"
#include "Frontend/layout.h"
#include "Node/node_configurescrolledtablecell.h"
#include "Node/frontend_openresourcearchive.h"
#include "Node/node_acquirearchiveentry.h"
#include "Frontend/node_creategridlistfromwidget.h"
#include "Frontend/widget_drawtextwidget.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/screen.h"

struct DraftWidget;
void Widget_DrawWidget(struct DraftWidget *widget, sm_dldc args);
extern struct PoolFrontendReleaseActiveChunkImages g_frontendResourceFontCount;

/* unit FRONTEND_OPENRESOURCEARCHIVE_DATA.CPP */
const unsigned char s_frontendResourceBinaryReadModeStorage[] = {
    0x72, 0x62, 0x00,
#if defined(VERSION_EU_X)
    /* Retained suffix at 800E88F3, in this same object's next section. */
    0xF4, 0x00, 0x43, 0xD5, 0x14, 0x00, 0x43, 0xD5, 0x04, 0x00, 0x43, 0xD5, 0x34,
#endif
#if defined(VERSION_EU)
    0x4B,
#endif
#if defined(VERSION_US_REV1)
    0xC4,
#endif
};

#if defined(VERSION_US)
extern char s_FrontendOpenresourcearchiveELINTRO4equText[13];
#endif

#if defined(VERSION_DE)
char k_FrontendOpenresourcearchiveEncodedBytes[13] =
    "s : %d ]\012\000\000\000\000";
#endif

/* unit S_TYPETEXT.CPP */
#if defined(VERSION_US)
TypeTextEventTable s_typeText = {
    {
        { 5, 30000, g_selectPreviousGridRowHandlerAddress },
        { 6, 30000, g_selectNextGridRowHandlerAddress },
        { 7, 30000, g_selectPreviousGridColumnHandlerAddress },
        { 8, 30000, g_selectNextGridColumnHandlerAddress },
        { 0xE03, 30000, g_eventHandlerCodeTargetIdE03 },
        { 0, 0, 0 },
    },
    "T_TYPE_F",
};
#endif

/* unit NODE_REPLACEWIDGETLINKS.CPP */
#include <platform_sdk.h>
#include "types.h"

MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier) {
    MenuWidget *node = root;
    u16 id = identifier;
    MenuWidget *found = 0;

    while (node != 0 && found == 0) {
        if (node->resource == id) {
            found = node;
        }
        if (found == 0 && node->child != 0) {
            found = Node_FindWidgetByResourceId(node->child, id);
        }
        node = node->sibling;
    }
    return found;
}

/* Searches the sibling list starting at node, descending depth first into each node's child list, for the first node whose next sibling carries the given id, and returns that predecessor or null. */
struct Tree *Node_FindWidgetPredecessor(struct Tree *node, s32 id) {
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

/* Recursively replaces a node reference throughout a linked hierarchy and copies the old node links into its replacement. */
void Node_ReplaceWidgetLinks(NodeFrontendReplaceWidgetLinks *node, NodeFrontendReplaceWidgetLinks *parent, NodeFrontendReplaceWidgetLinks *oldWidget, NodeFrontendReplaceWidgetLinks *newWidget) {
    NodeFrontendReplaceWidgetLinks *nextSibling;
    NodeFrontendReplaceWidgetLinks *firstChild;
    if (node != NULL) {
        nextSibling = node->nextSibling;
        if (nextSibling != NULL) {
            Node_ReplaceWidgetLinks(nextSibling,parent,oldWidget,newWidget);
        }
        firstChild = node->firstChild;
        if (firstChild != NULL) {
            Node_ReplaceWidgetLinks(firstChild, node, oldWidget, newWidget);
        }
        if (node->parent == oldWidget) {
            node->parent = newWidget;
        }
        if (node->nextSibling == oldWidget) {
            node->nextSibling = newWidget;
        }
        if (node->firstChild == oldWidget) {
            node->firstChild = newWidget;
        }
        if (node == oldWidget) {
            newWidget->parent = (NodeFrontendReplaceWidgetLinks *) node->parent;
            newWidget->nextSibling = (NodeFrontendReplaceWidgetLinks *) node->nextSibling;
            newWidget->firstChild = (NodeFrontendReplaceWidgetLinks *) node->firstChild;
        }
    }
}

/* unit NODE_INSERTWIDGETBEFORE.CPP */
/* Links a new node into a tree just before a given node, making it the parent's first child when the given node was, and otherwise attaching it after the predecessor that Node_FindWidgetPredecessor's search finds from the parent by the given node's id. */
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

void Node_InsertWidgetBefore(struct Tree *node, struct Tree *added) {
    struct Tree *parent;

    added->next = node;
    added->parent = node->parent;
    added->child = 0;
    parent = node->parent;
    if (parent->child == node) {
        parent->child = added;
    } else {
        findPredecessor(parent, (u16)node->id)->next = added;
    }
}

/* unit FRONTEND_OPENRESOURCEARCHIVE.CPP */
/* Relocates a loaded widget list and its children from the stored base to base: for widgets
   flagged 0x10 rebases the four resource words, then by widget type clears an out-of-range image
   index (type 3), rebases the extra pointer and marks the widget 0x800 (type 2), clears the fourth
   word (type 4) or turns the three packed resource references (index and offset) into pointers,
   acquiring resources through Node_AcquireArchiveEntry and marking them in g_frontendResourceScreenFlags as needed (type 8);
   it then rebases the name (clearing it for an empty type 2 widget), the child list, which it
   relocates recursively, and the next pointer. */


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

/* Measures the pixel width of a string of the given length in the given font by summing each character's signed width byte from the font record Node_GetGlyphBuffer returns, then adding the spacing Node_GetFontLetterSpacing reports once between each pair of characters. */
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

/* Stores the two bytes of a record's pair together. */
void Node_SetRecordBytePair(struct Pair2C *record, u8 first, u8 second) {
    record->first = first;
    record->second = second;
}

/** Stores the archive handle of the object. */
void Node_SetArchiveHandle(void *object, int value) {
    FrontendArchiveHandleView *record = object;
    record->archiveHandle = value;
}

/** Stores the archive handle of the object; identical to Node_SetArchiveHandle. */
void Node_AssignArchiveHandle(void *object, int value) {
    FrontendArchiveHandleView *record = object;
    record->archiveHandle = value;
}

/* Stores four values into a record's consecutive value words. */
void Node_SetRecordValueQuad(struct WidgetRecordValueQuadView *record, s32 first, s32 second, s32 third, s32 fourth) {
    record->values[0] = first;
    record->values[1] = second;
    record->values[2] = third;
    record->values[3] = fourth;
}

/* Draws a widget's variant image: when Widget_ComputeWidgetBounds accepts the widget at the position, picks the
   pressed (flag 0x100), highlighted (flag 0x40) or normal image of the widget, and when present
   moves the position back by the image's offset scaled by the style's scale factors and draws it
   through Widget_DrawWidget with the same flags and style. */
void Node_DrawButtonImage(ButtonWidget *widget, sm_dldc args) {
    Shared_Quad box0;
    Shared_Quad box1;
    struct Pair14 *image;

    if (Widget_ComputeWidgetBounds((struct WidgetRect *)&box0, (struct WidgetRect *)&box1, (WidgetLayout *)widget, &args) != 0) {
        if (args.flags & 0x100) {
            image = widget->pressed;
        } else if (args.flags & 0x40) {
            image = widget->highlighted;
        } else {
            image = widget->normal;
        }
        if (image != 0) {
            args.x -= (s32)(image->first * args.XScale);
            args.y -= (s32)(image->second * args.YScale);
            Widget_DrawWidget((struct DraftWidget *)image, args);
        }
    }
}

/* Draws the first child of a window with the arguments passed by value after clearing g_frontendRenderStateInitialized once Widget_ComputeWidgetBounds resolves the window's rectangle, and when flag 0x200 of the halfword at 0x12 is set it saves the four values N64Eng_GetClipBounds reports, narrows them by the resolved basis through Node_ClampRectToClip_FrontendOpenresourcearchive, giving up when it fails, and installs them through N64Eng_SetClipBounds around the draw, restoring the saved values after it. */
void Node_DrawClippedChildren(WidgetLayout *widget, sm_dldc args) {
    struct WidgetRect basis;
    struct WidgetRect value;
    struct WidgetRect transformed;
    struct WidgetRect first;
    s32 changed;
    UiWidget *window = widget;

    changed = 0;
    g_frontendRenderStateInitialized = 0;
    if (Widget_ComputeWidgetBounds((struct WidgetRect *)&first, (struct WidgetRect *)&basis, widget, &args) != 0) {
        if ((window->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.left, &value.top, &value.right, &value.bottom);
            transformed = value;
            if (Node_ClampRectToClip(&transformed, &basis) == 0) {
                return;
            }
            N64Eng_SetClipBounds(transformed.left, transformed.top,
                          transformed.right, transformed.bottom);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(window->children, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.left, value.top, value.right, value.bottom);
        }
    }
}

/* Intersects a rectangle with another in place, widening it to at least one unit and returning whether it was non-empty. */
s32 Node_ClampRectToClip(struct WidgetRect *rect, struct WidgetRect *clip) {
    s32 ok;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 v;

    x0 = rect->left;
    ok = 1;
    if (x0 < clip->left) {
        x0 = clip->left;
    }
    x1 = rect->right;
    rect->left = x0;
    if (clip->right < x1) {
        x1 = clip->right;
    }
    y0 = rect->top;
    rect->right = x1;
    if (y0 < clip->top) {
        y0 = clip->top;
    }
    y1 = rect->bottom;
    rect->top = y0;
    if (clip->bottom < y1) {
        y1 = clip->bottom;
    }
    rect->bottom = y1;
    v = rect->left + 1;
    if (rect->right < v) {
        rect->right = v;
        ok = 0;
    }
    v = rect->top + 1;
    if (rect->bottom < v) {
        rect->bottom = v;
        ok = 0;
    }
    return ok;
}

/* Records the last column and row of a width by height area: stores width - 1 and height - 1 in
   g_frontendViewportWidth and g_frontendViewportHeight, and fills the rectangle g_frontendClipBounds with zero to width - 1 and zero
   to height - 1. */
void Node_SetDisplayClipBounds(s32 width, s32 height) {
    struct WidgetRect *rect = &g_frontendClipBounds;

    width--;
    height--;
    g_frontendViewportWidth = width;
    g_frontendViewportHeight = height;
    rect->top = 0;
    rect->left = 0;
    rect->right = width;
    rect->bottom = height;
}

/** Perform no work. */
void Node_NoOperation(void) {
}

/* Orders two records by their unsigned halfword value, returning the difference in the
   shape a sort comparator uses. */
int Node_CompareRecordShortValues(struct TextSpriteGlyphKey *a, struct TextSpriteGlyphKey *b) {
    return a->value - b->value;
}

/* Releases every loaded slot of the active, referenced entries of the pool at g_frontendResourceFontCount: each
   loaded slot (flag 1) has its data released through Image_ReleaseImage, its flags and owner cleared and
   the entry's reference count decremented, and an entry left without references is unloaded
   through Node_ReleaseChunkImages and marked inactive. Pool layout and indexed slot access follow Node_ReleaseChunkImages. */
void Node_ReleaseActiveChunkImages(void) {
    s32 e;
    s32 n;
    s32 i;
    ArchiveOwnedImageSlot *slot;

    for (e = 0; e < g_frontendResourceFontCount.count; e++) {
        if (g_frontendResourceFontCount.entries[e].refCount != 0 && g_frontendResourceFontCount.entries[e].active != 0) {
            for (n = 0; n < g_frontendResourceFontCount.entries[e].def->bitmapCount; n++) {
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
                if (widget->words[0] < 0 || g_frontendResourceTextureCount.count - 1 < widget->words[0]) {
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

#include "Frontend/layout.h"
#include "Node/node_configurescrolledtablecell.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Node/node_acquirearchiveentry.h"
#include "Frontend/frontend_address_symbols.h"
struct Record *Cache_AllocateMemory(s32 size);
u8 *XPlus_CopyString(u8 *dst, u8 *src);
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

/* unit NODE_GETIMAGETEXTURE.CPP */
extern struct FrontendTextureTimerEntry *g_frontendResourceTextureTimers;
extern ArchiveTextureEntry *g_frontendResourceTextures;
extern struct Record *Cache_AllocateMemory(s32 size);

/* Tears down the UI resource set: releases eligible entries, closes active
   subsystems, frees each nested chunk allocation and the shared tables, then
   clears the complete state record. */










extern void Node_ReleaseRetainedImageSlot(s32 i);

extern void Node_ReleaseActiveChunkImages(void);

extern void Node_ReleaseUnprotectedBuffers(s32), Node_UpdateImageReleaseTimers(s32), Node_ReleaseAllChunkImages(void);


/* Expires cached UI resources against the current tick from N64Eng_GetFrameCounter unless the cache is
   locked: releases through Node_ReleaseRetainedImageSlot the first flagged entry whose unretained resource has an
   id below the tick and stops; otherwise, for each live chunk, clears every flagged slot whose time
   has passed (freeing its data through Image_ReleaseImage) and stops as soon as a chunk still holds live
   slots after one expires, freeing through Node_ReleaseChunkImages and clearing each chunk left empty. */

/* Returns a texture's resource id, first loading its pixel and 16-bit palette data, detecting a transparent palette entry and creating the texture resource when it is not yet loaded, and in both cases updates the texture's usage record for the requested mode (1 stamps the next expiry time, 2 pins it, 3 counts a reference); the opened file handle is stored through the header symbol as in the paletted texture loader, and the resource id is held in two locals (the second passed to Smp_CopyAndSwizzleImage), which reproduces the cartridge's three stack slots. */
static inline void Frontend_TouchTextureEntry(s32 index, s32 mode) {
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
    struct _sm_font *chunk;
    void **block;
    void **tables;
    void **first;
    void **second;
    t_resource *state;
    i = 0;
    if (g_frontendResourceTextureCount.count > 0) {
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
        } while (++i < g_frontendResourceTextureCount.count);
    }
    Node_ReleaseActiveChunkImages();
    state = &g_frontendResourceState;
    if (state->In) XStdio_CloseStream(state->In);
    Node_ReleaseUnprotectedBuffers(1);
    Node_UpdateImageReleaseTimers(1);
    if (state->Texture) Cache_FreeMemory(state->Texture);
    i_chunks = 0;
    Node_ReleaseAllChunkImages();
    offset_chunks = 0;
    if (state->NFonts > 0) {
        do {
            block = (void **)((struct _sm_font *)(offset_chunks + (s32)g_frontendResourceState.Font))->Clut;
            if (block) {
                Cache_FreeMemory(*block);
                Cache_FreeMemory(((struct _sm_font *)(offset_chunks + (s32)g_frontendResourceState.Font))->Clut);
            }
            i_chunks++;
            Cache_FreeMemory(*((struct _sm_font *)(offset_chunks + (s32)g_frontendResourceState.Font))->Char);
            block = (void **)((struct _sm_font *)(offset_chunks + (s32)g_frontendResourceState.Font))->Char;
            offset_chunks += 1180;
            Cache_FreeMemory(block);
        } while (i_chunks < g_frontendResourceState.NFonts);
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
    XPlus_FillBytes((char *)tables - ((char *)&((t_resource *)0)->VramPool - (char *)0), 0, 680);
}

void Node_EvictExpiredImages(void) {
    s32 now;
    s32 i;
    s32 j;
    s32 k;
    t_char *slot;
    t_char *slots;
    struct FrontendTextureTimerEntry *resource;

    now = N64Eng_GetFrameCounter();
    if (g_frontendResourceState.NeverFreeResources != 0) {
        return;
    }
    for (i = 0; i < g_frontendResourceState.NTextures; i++) {
        if (g_frontendResourceState.Texture[i].SMFlags & 1) {
            resource = &g_frontendResourceState.TexTimer[i];
            if (resource->id != -1 && resource->retained == 0 && resource->id < now) {
                Node_ReleaseRetainedImageSlot(i);
                return;
            }
        }
    }
    for (i = 0; i < g_frontendResourceState.NFonts; i++) {
        if (g_frontendResourceState.Font[i].NumInUse != 0 && g_frontendResourceState.Font[i].Active != 0) {
            for (j = 0; j < g_frontendResourceState.Font[i].TableEntry->bitmapCount; j++) {
                slots = g_frontendResourceState.Font[i].Char[j];
                for (k = 0; k < 96; k++) {
                    slot = &slots[k];
                    if ((slot->SMFlags & 1) && slot->CharTimer < now) {
                        Image_ReleaseImage(&slot->Vram);
                        slot->CharTimer = 0;
                        slot->SMFlags &= ~1;
                        g_frontendResourceState.Font[i].NumInUse--;
                        if (g_frontendResourceState.Font[i].NumInUse != 0) {
                            return;
                        }
                    }
                }
            }
            if (g_frontendResourceState.Font[i].NumInUse == 0) {
                Node_ReleaseChunkImages(i);
                g_frontendResourceState.Font[i].Active = 0;
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
        Frontend_TouchTextureEntry(index, mode);
        return g_frontendResourceTextures[index].imageHandle;
    }
    palette = 0;
    paletteBytes = 0;
    id = g_frontendResourceTextures[index].imageHandle;
    stride = 0;
    N64Eng_GetTimeSeconds();
    ((t_resource *)((char *)&g_frontendResourceFilename - 4))->In = XStdio_OpenStream(&g_frontendResourceFilename, &s_frontendResourceOpenMode);
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
    XStdio_SeekStream(g_frontendResourceState.In, g_frontendResourceState.Header.TextureData + entry->pixelOffset, 0);
    XStdio_ReadStream(pixels, size, 1, g_frontendResourceState.In);
    if (entry->paletteCount > 0) {
        paletteBytes = entry->paletteCount * 2;
        palette = Cache_AllocateMemory(paletteBytes);
        XStdio_SeekStream(g_frontendResourceState.In, g_frontendResourceState.Header.TextureData + entry->paletteOffset, 0);
        XStdio_ReadStream(palette, paletteBytes, 1, g_frontendResourceState.In);
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
    Frontend_ConfigureOwnedImage((struct Config *)id, format, entry->width, entry->height, stride, entry->height, 1, size, (int)pixels, 1, paletteBytes,
                  (int)palette, entry->paletteCount);
    Smp_CopyAndSwizzleImage((struct GameImage *)texture, (struct GameImage *)id);
    g_frontendResourceTextures[index].flags |= 1;
    XStdio_CloseStream(g_frontendResourceState.In);
    g_frontendResourceState.In = 0;
    N64Eng_GetTimeSeconds();
    Frontend_TouchTextureEntry(index, mode);
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
    ((t_resource *)((char *)&g_frontendResourceFilename - 4))->In = XStdio_OpenStream(&g_frontendResourceFilename, &s_frontendResourceOpenMode);
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
    XStdio_SeekStream(g_frontendResourceState.In, g_frontendResourceState.Header.TextureData + entry->pixelOffset, 0);
    XStdio_ReadStream(pixels, size, 1, g_frontendResourceState.In);
    if (entry->paletteCount > 0) {
        paletteBytes = entry->paletteCount * 2;
        palette = Cache_AllocateMemory(paletteBytes);
        XStdio_SeekStream(g_frontendResourceState.In, g_frontendResourceState.Header.TextureData + entry->paletteOffset, 0);
        XStdio_ReadStream(palette, paletteBytes, 1, g_frontendResourceState.In);
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
    XStdio_CloseStream(g_frontendResourceState.In);
    g_frontendResourceState.In = 0;
}

/* unit NODE_GETBANKTILETEXTURE.CPP */
/* Advances the deferred-release timers: for each of the g_frontendResourceTextureCount slots (all reset first when mode
   is 1) whose owner is not -1, counts the delay down, and once it has run out releases the slot's
   loaded resource data through Image_ReleaseImage, clearing its loaded flag, and clears the owner. */


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

    slots = ((Bank *)g_frontendResourceState.Font)[group].slotsByPass[pass];
    index = which;
    {
    if (slots[index].flags & 1) {
        Bank *cachedBank;
        stamp = N64Eng_GetFrameCounter() + 10;
        slots[index].stamp = stamp;
        cachedBank = &((Bank *)g_frontendResourceState.Font)[group];
        if (cachedBank->held == 0 && cachedBank->stamp != -1) {
            cachedBank->stamp = stamp;
        }
        return &slots[which].texture;
    }
    }
    kind = 0;
    N64Eng_GetTimeSeconds();
    image = ((Bank *)g_frontendResourceState.Font)[group].image;
    tile = &((Bank *)g_frontendResourceState.Font)[group].tiles[index];
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
    if (((Bank *)g_frontendResourceState.Font)[group].loaded == 0) {
        s32 *tables = &g_frontendResourceState.Header.FontData;

        bank = &((Bank *)*(struct _sm_font **)((char *)tables +
            ((char *)&g_frontendResourceState.Font -
             (char *)&g_frontendResourceState.Header.FontData)))[group];
        g_frontendResourceState.In = XStdio_OpenStream(&g_frontendResourceState.Name, &s_frontendResourceOpenMode);
        size = bank->image->size;
        i = 0;
        bank->offsets[0] = Cache_AllocateMemory(size);
        XStdio_SeekStream(g_frontendResourceState.In, g_frontendResourceState.Header.CharData + bank->image->base, 0);
        XStdio_ReadStream(((Bank *)g_frontendResourceState.Font)[group].offsets[0], size, 1, g_frontendResourceState.In);
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
                Tile *big = &((Bank *)g_frontendResourceState.Font)[group].tiles[i];

                Frontend_ClearOwnedImage(&scratch);
                Frontend_ConfigureOwnedImage((struct Config *)&scratch, kind, big->fmt, big->siz, big->wid, big->siz, 0, sizes[i],
                              (int)((Bank *)g_frontendResourceState.Font)[group].offsets[i], 0, image->depth * 2,
                              (int)((Bank *)g_frontendResourceState.Font)[group].listsByPass[pass], image->depth);
                Image_SwizzleImage(&scratch);
                Frontend_ReleaseOwnedImageBuffers(&scratch);
            }
            i += 1;
        } while (i < 96);
        XStdio_CloseStream(g_frontendResourceState.In);
        g_frontendResourceState.In = 0;
        bank->loaded = 1;
    }
    bytes = tile->wid * tile->siz * code >> 3;
    Frontend_ConfigureOwnedImage((struct Config *)texture, kind, tile->fmt, tile->siz, tile->wid, tile->siz, 0,
                  bytes, (int)((Bank *)g_frontendResourceState.Font)[group].offsets[which], 0,
                  image->depth * 2, (int)((Bank *)g_frontendResourceState.Font)[group].listsByPass[pass], image->depth);
    Smp_SetImageStateWord(0);
    Smp_CopyAndSwizzleImage(into, texture);
    Smp_SetImageStateWord(1);
    N64Eng_GetTimeSeconds();
    slot->stamp = N64Eng_GetFrameCounter() + 10;
    ((Bank *)g_frontendResourceState.Font)[group].loads += 1;
    slot->flags |= 1;
    return &slot->texture;
}

/* unit NODE_ACQUIREARCHIVEENTRY.CPP */
/* Unloads entry index of the pool at g_frontendResourceFontCount: releases the data of every loaded slot (flag 1) in
   each of the entry's slot ns (the n count comes from the entry's definition) through
   Image_ReleaseImage and clears the flag, frees the entry's buffer through Cache_FreeMemory and clears the
   buffer table when one is held, and marks the entry inactive. */


void Node_ReleaseChunkImages(s32 index) {
    s32 n;
    s32 i;
    ArchiveOwnedImageSlot *slot;

    for (n = 0; n < g_frontendResourceFontCount.entries[index].def->bitmapCount; n++) {
        slot = g_frontendResourceFontCount.entries[index].pages[n];
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

/* Loads entry index of the menu archive into memory and counts the use: in cache mode 1 an entry
   already loaded is restored from its saved copy and rebased; otherwise an entry not yet loaded is
   read from the archive file into a new buffer (and copied into a second buffer when copies are
   kept) and rebased. */
void Node_AcquireArchiveEntry(s32 index) {
    void *data;
    g_frontendResourceState.RefCount[index]++;
    if (g_frontendResourceState.NeverFreeResources == 1 && g_frontendResourceState.Screen[index].data != 0) {
        XPlus_CopyBytes(g_frontendResourceState.Screen[index].data, g_frontendResourceState.ScreenOriginal[index].data, g_frontendResourceState.Screen[index].size);
        data = g_frontendResourceState.Screen[index].data;
        Node_RelocateWidgetTree(data, data, g_frontendResourceState.Screen[index].offset - g_frontendResourceState.Screen[0].offset);
    }
    if (g_frontendResourceState.Screen[index].data != 0) return;
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

/* unit NODE_CONFIGURESCROLLEDTABLECELL.CPP */
/* The records are 1180 bytes apart; the global points into the heap. */

typedef struct List List;

extern ArchiveTextureEntry *g_frontendResourceTextures;
/* Releases the buffers of the pool at g_frontendResourceScreenCount: every entry holding a buffer that is not locked
   (flag 1) unless force is set has its reference count forced to one and dropped, and when it
   reaches zero the buffer is freed through Cache_FreeMemory, along with the entry's secondary buffer
   when secondary buffers are in use (g_frontendArchiveResident), and the entry is cleared. Pool fields read as one struct at g_frontendResourceScreenCount, as in Node_UpdateImageReleaseTimers. */
void Node_ReleaseUnprotectedBuffers(s32 force) {
    s32 i;

    for (i = 0; i < g_frontendResourceState.NScreens; i++) {
        if (g_frontendResourceState.Screen[i].data != 0 && (!(g_frontendResourceState.ScreenFlags[i] & 1) || force != 0)) {
            g_frontendResourceState.RefCount[i] = 1;
            g_frontendResourceState.RefCount[i]--;
            if (g_frontendResourceState.Screen[i].data != 0 && g_frontendResourceState.RefCount[i] == 0) {
                Cache_FreeMemory(g_frontendResourceState.Screen[i].data);
                if (g_frontendArchiveResident != 0 && g_frontendResourceState.ScreenOriginal != 0 &&
                    g_frontendResourceState.ScreenOriginal[i].data != 0) {
                    Cache_FreeMemory(g_frontendResourceState.ScreenOriginal[i].data);
                }
                g_frontendResourceState.Screen[i].data = 0;
            }
        }
    }
}

/** Perform no work. */
void Node_SkipResourceOperation(void) {
}

/* Returns the screen count g_frontendResourceState.NScreens. */
s16 Node_GetResourceScreenCount(void) {
    return g_frontendResourceState.NScreens;
}

/* Returns the texture count g_frontendResourceState.NTextures. */
s16 Node_GetResourceTextureCount(void) {
    return g_frontendResourceState.NTextures;
}

/* Returns the font count g_frontendResourceState.NFonts. */
s16 Node_GetResourceFontCount(void) {
    return g_frontendResourceState.NFonts;
}

/* Returns the word held in g_frontendResourceState.Header.FirstScreen. */
s32 Node_GetFirstResourceScreen(void) {
    return g_frontendResourceState.Header.FirstScreen;
}

/* Returns the width of entry i in the record table g_frontendResourceTextures points
   to; the width and height are read by Node_GetTextureEntryWidth and Node_GetTextureEntryHeight. */
s16 Node_GetTextureEntryWidth(s32 index) {
    return g_frontendResourceState.Texture[index].Width;
}

/* Returns the height of entry i in the record table g_frontendResourceTextures points
   to; the width and height are read by Node_GetTextureEntryWidth and Node_GetTextureEntryHeight. */
s16 Node_GetTextureEntryHeight(s32 index) {
    return g_frontendResourceState.Texture[index].Height;
}

/* Returns entry i of the chroma key table g_frontendResourceState.ChromaKey. */
s32 Node_GetTextureChromaKey(s32 index) {
    return g_frontendResourceState.ChromaKey[index];
}

/** Report success. */
int Node_ReturnOne(void) {
    return 1;
}

/* Releases UI resource slot i once its retain count reaches zero, closing its open entry and clearing the slot id. */
void Node_ReleaseRetainedImageSlot(s32 i) {
    struct FrontendTextureTimerEntry *resource;

    resource = (struct FrontendTextureTimerEntry *)(i * 8 + (s32)g_frontendResourceTextureTimers);
    if (resource->id != -1) {
        if (resource->retained > 0) {
            resource->retained--;
        } else {
            if (g_frontendResourceTextures[i].flags & 1) {
                Image_ReleaseImage((struct OwnedImage *)g_frontendResourceTextures[i].imageHandle);
                g_frontendResourceTextures[i].flags &= ~1;
            }
            g_frontendResourceTextureTimers[i].id = 0;
        }
    }
}

/* Returns the signed byte at offset 0x9 of entry j in the 8-byte entries that begin record i of
   the font table g_frontendResourceState.Font (1180-byte records). */
signed char Node_GetFontCharacterHeight(int entry, int index) {
    return g_frontendResourceState.Font[index].CharInfo[(unsigned char)entry].height;
}

/* Returns the signed byte at offset 0xA of entry j in the 8-byte entries that begin record i of
   the font table g_frontendResourceState.Font (1180-byte records). */
signed char Node_GetFontCharacterPhysicalWidth(int entry, int index) {
    return g_frontendResourceState.Font[index].CharInfo[(unsigned char)entry].PhysicalWidth;
}

/* Returns the halfword at offset 0xE of the object held at offset 0x48C of record i in the
   font table g_frontendResourceState.Font (1180-byte records); Node_GetFontLetterSpacing reads offset 0x10 of the same
   object. */
short Node_GetFontBitmapCount(int index) {
    return g_frontendResourceState.Font[index].TableEntry->bitmapCount;
}

short Node_GetFontLetterSpacing(int index) {
    return g_frontendResourceState.Font[index].TableEntry->letterSpacing;
}

short Node_GetFontVerticalOffset(int index) {
    return g_frontendResourceState.Font[index].TableEntry->verticalOffset;
}

short Node_GetFontLineHeight(int index) {
    return g_frontendResourceState.Font[index].TableEntry->lineHeight;
}

/** Report success. */
int Node_ReturnConstantOne(void) {
    return 1;
}

/** Report success. */
int Node_ReturnUnitValue(void) {
    return 1;
}

/* Runs Node_ReleaseChunkImages for each of the manager g_frontendResourceFontCount's entries unless its mode is 1. */
void Node_ReleaseAllChunkImages(void) {
    int i;

    if (g_frontendResourceState.NeverFreeResources != 1) {
        for (i = 0; i < g_frontendResourceState.NFonts; i++) {
            Node_ReleaseChunkImages(i);
        }
    }
}

/* This global holds a heap address rather than a static one, so it is a pointer variable and not an array base.
   The words it returns are not word aligned, so the element type is a pointer to bytes. */
char *Node_GetStringByIndex(s32 index) {
    return g_frontendResourceState.StringTable[index];
}

/* Returns the halfword held in g_frontendResourceLanguageCount. */
s16 Node_GetResourceLanguageCount(void) {
    return g_frontendResourceState.NLanguages;
}

/* Calls Node_LoadLanguageStrings when the language count g_frontendResourceState.NLanguages is non-zero. */
void Node_LoadLanguageStringsIfAny(s32 languageIndex) {
    if (g_frontendResourceState.NLanguages != 0) {
        Node_LoadLanguageStrings(languageIndex);
    }
}

/* Returns the third word of the 12-byte screen record selected by the index: a pointer that may be absent.
   The index stays inside the bound that Node_IsValidScreenIndex_NodeConfigurescrolledtablecell checks
   against g_frontendResourceScreenCount, so this is an accessor over the same table. */
void *Node_GetScreenData(s32 index) {
    return g_frontendResourceState.Screen[index].data;
}

/* Returns whether an index lies inside the table bound g_frontendResourceScreenCount, from zero up to but not
   including it. */
s32 Node_IsValidScreenIndex(s32 index) {
    if (index >= 0 && index < g_frontendResourceState.NScreens) {
        return 1;
    }
    return 0;
}

/* Drops one reference to buffer pool entry i and, when none remain, frees its primary and secondary buffers and clears the entry. */
void Node_ReleaseReferencedBuffer(s32 i) {
    g_frontendResourceState.RefCount[i]--;
    if (g_frontendResourceState.Screen[i].data != 0 && g_frontendResourceState.RefCount[i] == 0) {
        Cache_FreeMemory(g_frontendResourceState.Screen[i].data);
        if (g_frontendArchiveResident != 0 && g_frontendResourceState.ScreenOriginal != 0 &&
            g_frontendResourceState.ScreenOriginal[i].data != 0) {
            Cache_FreeMemory(g_frontendResourceState.ScreenOriginal[i].data);
        }
        g_frontendResourceState.Screen[i].data = 0;
    }
}

/* Clears the block g_frontendResourceState through XPlus_FillBytes, sets g_frontendWidgetStateChanged and clears
   g_frontendArchiveResident. */
void Node_InitializeResourceState(void) {
    XPlus_FillBytes(&g_frontendResourceState, 0, sizeof(g_frontendResourceState));
    g_frontendWidgetStateChanged = 1;
    g_frontendArchiveResident = 0;
}

void Node_ClearResourceInitializationFlag(void) {
    g_frontendWidgetStateChanged = 0;
}

void Node_SetSecondaryBufferMode(s32 value) {
    g_frontendArchiveResident = value;
}

/* Sets the buffer pool flag, then runs Node_AcquireArchiveEntry on every buffer pool entry, Node_GetImageTexture_NodeConfigurescrolledtablecell in mode 2 on every resource slot and Node_GetBankTileTexture on every chunk. */
void Node_AcquireAllResourceTextures(void) {
    s32 i;

    g_frontendResourceState.NeverFreeResources = 1;
    for (i = 0; i < g_frontendResourceState.NScreens; i++) {
        Node_AcquireArchiveEntry(i);
    }
    for (i = 0; i < g_frontendResourceTextureCount.count; i++) {
        Node_GetImageTexture(i, 2);
    }
    for (i = 0; i < g_frontendResourceState.NFonts; i++) {
        Node_GetBankTileTexture(0, i, 0);
    }
}

GlyphBuffer *Node_GetGlyphBuffer(s32 index) {
    return (GlyphBuffer *)&g_frontendResourceState.Font[index];
}

void Node_ReleaseUnretainedTextureEntries(void) {
    s32 i;
    s32 invalid;
    s32 offset;
    struct FrontendTextureTimerEntry *resource;

    i = 0;
    if (g_frontendResourceTextureCount.count > 0) {
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
        } while (++i < g_frontendResourceTextureCount.count);
    }
}

/* Loads or unloads the images of a widget subtree: visits the later siblings when asked and the
   children, then for an image widget (type 3) loads its image through Node_GetImageTexture_NodeConfigurescrolledtablecell or unloads it
   through Node_ReleaseRetainedImageSlot, and for a button (type 8) visits its normal, pressed and highlighted
   variants without their siblings; type 4 widgets and other types have nothing to do. */
void Node_UpdateWidgetTextureRetention(WidgetTextureRetentionView *widget, s32 load, s32 siblings) {
    if (widget == 0) {
        return;
    }
    if (widget->next != 0 && siblings != 0) {
        Node_UpdateWidgetTextureRetention(widget->next, load, siblings);
    }
    if (widget->child != 0) {
        Node_UpdateWidgetTextureRetention(widget->child, load, siblings);
    }
    switch (widget->type) {
        case 4:
            break;
        case 3:
            if (load != 0) {
                Node_GetImageTexture(widget->normal, 3);
            } else {
                Node_ReleaseRetainedImageSlot(widget->normal);
            }
            break;
        case 8:
            if (widget->normal != 0) {
                Node_UpdateWidgetTextureRetention(widget->normal, load, 0);
            }
            if (widget->pressed != 0) {
                Node_UpdateWidgetTextureRetention(widget->pressed, load, 0);
            }
            if (widget->highlighted != 0) {
                Node_UpdateWidgetTextureRetention(widget->highlighted, load, 0);
            }
            break;
    }
}

/* Clamps a list's two cursor coordinates into their [min, max] ranges and scrolls each view offset so the cursor stays inside the visible window. */
void Node_ClampListCursorAndScroll(List *list) {
    if (list->maxY < list->cursorY) {
        list->cursorY = list->maxY;
    }
    if (list->maxX < list->cursorX) {
        list->cursorX = list->maxX;
    }
    if (list->cursorY < list->minY) {
        list->cursorY = list->minY;
    }
    if (list->cursorX < list->minX) {
        list->cursorX = list->minX;
    }
    if (list->cursorY - list->scrollY >= list->visibleY - list->minY) {
        list->scrollY = list->cursorY - (list->visibleY - list->minY) + 1;
    }
    if (list->cursorX - list->scrollX >= list->visibleX - list->minX) {
        list->scrollX = list->cursorX - (list->visibleX - list->minX) + 1;
    }
    if (list->cursorY < list->scrollY) {
        list->scrollY = list->cursorY;
    }
    if (list->cursorX < list->scrollX) {
        list->scrollX = list->cursorX;
    }
}

/* Lays out cell (row, col) of a scrolling table: copies the table's cell template, picks the header
   colours for header rows and columns and the body colours otherwise (mapping body positions past
   the headers onto the scrolled contents), offsets the cell by the widths and heights of the
   columns and rows before it (repeating the last header size beyond the headers), sets its size
   from its own column and row, points it at the content entry and gives the selected entry its
   highlight colours. */
void Node_ConfigureScrolledTableCell(sm_dllistbox *table, sm_dltext *cell, u32 row, u32 col) {
    s32 lastCol;
    s32 lastRow;
    u32 entryCol;
    u32 entryRow;
    s32 x;
    s32 y;
    s32 n;
    s32 i;

    cell->Hdr = table->layout;
    cell->Font = table->fg;
    cell->FontClut = table->bg;
    if (col < table->headerCols) {
        entryCol = col;
        cell->Font = table->headerFg;
        cell->FontClut = table->headerBg;
        lastCol = -1;
        if (col != 0) {
            lastCol = col - 1;
        }
    } else {
        lastCol = -1;
        entryCol = col - table->headerCols + table->colScroll;
        if (table->headerCols != 0) {
            lastCol = col;
        }
    }
    if (row < table->headerRows) {
        entryRow = row;
        cell->Font = table->headerFg;
        cell->FontClut = table->headerBg;
        lastRow = -1;
        if (row != 0) {
            lastRow = row - 1;
        }
    } else {
        lastRow = -1;
        entryRow = row - table->headerRows + table->rowScroll;
        if (table->headerRows != 0) {
            lastRow = row;
        }
    }
    x = 0;
    y = 0;
    n = lastCol;
    if (table->headerCols < lastCol) {
        n = table->headerCols;
    }
    if (lastCol != -1) {
        for (i = 0; i < n; i++) {
            x += table->widths[i];
        }
    }
    n = lastRow;
    if (table->headerRows < lastRow) {
        n = table->headerRows;
    }
    if (lastRow != -1) {
        for (i = 0; i < n; i++) {
            y += table->heights[i];
        }
    }
    if (table->headerCols < lastCol) {
        x += (lastCol - table->headerCols) * table->widths[table->headerCols - 1];
    }
    if (table->headerRows < lastRow) {
        y += (lastRow - table->headerRows) * table->heights[table->headerRows - 1];
    }
    if (col < table->headerCols) {
        cell->Hdr.width = table->widths[col];
    } else {
        cell->Hdr.width = table->widths[table->headerCols - 1];
    }
    if (row < table->headerRows) {
        cell->Hdr.height = table->heights[row];
    } else {
        cell->Hdr.height = table->heights[table->headerRows - 1];
    }
    cell->pString = table->contents[(entryRow * table->columns + entryCol) * 2];
    if (entryRow == table->selectedRow && entryCol == table->selectedCol) {
        cell->FontHighlighted = table->selectedFg;
        cell->FontHighlightedClut = table->selectedBg;
    } else {
        cell->FontHighlighted = cell->Font;
        cell->FontHighlightedClut = cell->FontClut;
    }
    cell->Hdr.x += x;
    cell->Hdr.y += y;
}

/* Calls the handler registered for eventId (tables s_typeText, g_typedWidgetEventActorKinds, g_typedWidgetEventHandlers). A row matches when its event equals eventId and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 Node_DispatchTypedWidgetEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_typedWidgetEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_typedWidgetEventHandlers;
        offset = 0;
        do {
            if ((*(s32 *) (((char *) (&s_typeText)) + offset)) == eventId) {
                actor_kind = ((struct MenuWidget *) ((char *) widget))->resource;
                table_kind = (*(s32 *) (((char *) (&g_typedWidgetEventActorKinds)) + offset));
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}

/* unit NODE_CREATEGRIDLISTFROMWIDGET.CPP */
/* Looks up the entry with the given identifier among the list Node_GetScreenData returns for what GetMenuScreenOwner returns, through Node_FindWidgetByResourceId, and stores two words into the eight-byte cell at the given row and column of its cell table, whose row width is the grid's column count. */
/* Visits every cell of a list's column-by-row grid, computing each cell's rectangle through Node_ConfigureScrolledTableCell and drawing it through Widget_DrawTextWidget_NodeCreategridlistfromwidget with the given style. */
void Node_DrawGridListCells(GridList *gridList, sm_dldc style) {
    GridList *list = gridList;
    UnitMtx cell;
    u32 column;
    u32 row;

    for (column = 0; column < list->columns; column++) {
        for (row = 0; row < list->rows; row++) {
            Node_ConfigureScrolledTableCell(list, &cell, column, row);
            Widget_DrawTextWidget((TextWidget *)&cell, style);
        }
    }
}

/* Allocates and zeroes a 0x60-byte record, copies the header of the record Node_FindWidgetByResourceId finds for the low half of the first argument, tags it 0xB, stores four byte arguments and three alternating pairs of the last two, allocates and zeroes a width-by-height table of eight-byte cells at 0x44, and registers the record through Node_ReplaceWidgetLinks. */
s32 Node_CreateGridListFromWidget(s32 widgetResourceId, u8 cellWidth, u8 cellHeight, u8 columnCount, u8 rowCount, u8 initialColumn, u8 initialRow) {
    MenuWidget *source;
    s32 context;
    MenuWidget *result;
    s32 size;
    void *cells;

    source = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), widgetResourceId & 0xFFFF);
    context = Node_GetScreenData(GetMenuScreenOwner());
    result = Cache_AllocateMemory(96);
    XPlus_FillBytes(result, 0, 96);
    *(Header44 *)result = *(Header44 *)source;
    result->kind = 11;
    result->rowCount = rowCount;
    result->columnCount = columnCount;
    result->cellHeight = cellHeight;
    result->cellWidth = cellWidth;
    result->minimumRow = initialRow;
    result->minimumColumn = initialColumn;
    result->initialRow = initialRow;
    result->initialColumn = initialColumn;
    result->selectedRow = initialRow;
    result->selectedColumn = initialColumn;
    size = columnCount * rowCount * 8;
    cells = Cache_AllocateMemory(size);
    result->cells = cells;
    XPlus_FillBytes(cells, 0, size);
    Node_ReplaceWidgetLinks((NodeFrontendReplaceWidgetLinks *)context, 0,
                            (NodeFrontendReplaceWidgetLinks *)source,
                            (NodeFrontendReplaceWidgetLinks *)result);
    return 1;
}

void Node_SetGridCellValues(s32 identifier, s32 row, s32 column, s32 first, s32 second) {
    EntryFrontendSetGridCellValues *entry = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), (u16)identifier);

    entry->cells[row * entry->width + column].first = first;
    entry->cells[row * entry->width + column].second = second;
}

void Node_GetGridCellValues(s32 identifier, s32 row, s32 column, s32 *first, s32 *second) {
    EntryFrontendSetGridCellValues *entry = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), (u16)identifier);

    *first = entry->cells[row * entry->width + column].first;
    *second = entry->cells[row * entry->width + column].second;
}

void Node_SetGridForegroundColors(s32 identifier, s32 first, s32 second, s32 third) {
    u8 *entry = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), (u16)identifier);

    entry[84] = second;
    entry[86] = third;
    entry[82] = first;
}

void Node_SetGridBackgroundColors(s32 identifier, s32 first, s32 second, s32 third) {
    u8 *entry = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), (u16)identifier);

    entry[85] = second;
    entry[87] = third;
    entry[83] = first;
}

void Node_SetGridDimensionArrays(s32 identifier, s32 first, s32 second) {
    struct EntryFrontendSetGridDimensionArrays *entry = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), (u16)identifier);

    entry->second = second;
    entry->first = first;
}

void Node_GetGridSelection(s32 identifier, s32 *first, s32 *second) {
    struct MenuWidget *entry = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), (u16)identifier);

    *first = entry->selectedColumn;
    *second = entry->selectedRow;
}

/* While active and the cursor row is above the minimum row, moves the cursor up one row; then clamps the cursor and scroll position and marks the menu event handled. Returns zero. */
s32 Node_SelectPreviousGridRow(List *list, void *second, void *third, s32 active) {
    s32 row = list->cursorX;

    if (active && list->minX < row) {
        list->cursorX = row - 1;
    }
    Node_ClampListCursorAndScroll(list);
    MarkMenuEventHandled();
    return 0;
}

/* While active and the cursor row is below the last row, moves the cursor down one row; then clamps the cursor and scroll position and marks the menu event handled. Returns zero. */
s32 Node_SelectNextGridRow(List *list, void *second, void *third, s32 active) {
    u8 row = list->cursorX;

    if (active && row < list->maxX - 1) {
        list->cursorX = row + 1;
    }
    Node_ClampListCursorAndScroll(list);
    MarkMenuEventHandled();
    return 0;
}

/* While active and the cursor column is above the minimum column, moves the cursor left one column; then clamps the cursor and scroll position and marks the menu event handled. Returns zero. */
s32 Node_SelectPreviousGridColumn(List *list, void *second, void *third, s32 active) {
    s32 column = list->cursorY;

    if (active && list->minY < column) {
        list->cursorY = column - 1;
    }
    Node_ClampListCursorAndScroll(list);
    MarkMenuEventHandled();
    return 0;
}

/* While active and the cursor column is before the last column, moves the cursor right one column; then clamps the cursor and scroll position and marks the menu event handled. Returns zero. */
s32 Node_SelectNextGridColumn(List *list, void *second, void *third, s32 active) {
    u8 column = list->cursorY;

    if (active && column < list->maxY - 1) {
        list->cursorY = column + 1;
    }
    Node_ClampListCursorAndScroll(list);
    MarkMenuEventHandled();
    return 0;
}

s32 Node_DestroyGridList(struct ObjectFrontendDestroyGridList *object) {
    struct ObjectFrontendDestroyGridList *self = object;

    if (object->child != 0) {
        Cache_FreeMemory(object->child);
    }
    Cache_FreeMemory(self);
    return 0;
}

/* unit NODE_RESOURCE_AND_COLLISION_LINK_DATA.CPP */
#if defined(VERSION_EU_X)
#include "Common/ccollisionsetup_t.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"
#include "Frontend/widget_findwidgetatpoint.h"
/* The collision setup table CCollision_Initialize hands to CCollision_ApplySetupTable (through its KUSEG alias
 * g_collisionSetupTableResource): one row per collision info, ended by an empty row. */
/* ROM row targets use byte offsets: secondary slots 1/2/3/5/0/6/4 and
 * supporting-platform slots 1/4/3/2/0 are spaced 0x20 bytes apart. */
CCollisionSetup_t g_collisionSetupTable[36] = {
    { (CCollisionInfo2_t *)((char *)&g_secondaryCollisionContext + 0x20), 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_supportingPlatformCollisionQuery + 0x20), 0x3C552B, 5, 2, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_collisionSurfaceExcludedFromTrace + 0x20), 0x3C5529, 2, 2, 2, -2100.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_particleOwnerEffectFlags + 0x8), 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_supportingPlatformCollisionQuery + 0x80), 0x3C5729, 5, 2, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_pagerPageCounters + 0x10), 0x3C5D29, 5, 2, 2, -69.119995f, 0.0f, 0.0f, 0.0f, 0.08f },
    { (CCollisionInfo2_t *)((char *)&g_collisionSurfaceExcludedFromTrace + 0x40), 0x3C5529, 5, 2, 2, 0.0f, 0.0f, 0.9f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_globalGameplayFlags, 0x2C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_portalDefaultCollisionQuery + 0x20), 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_playerCollisionProbe + 0x40), 0x3C5309, 5, 6, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_supportingPlatformCollisionQuery + 0x60), 0x3C5729, 0, 0, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_particleOwnerEffectFlags + 0x28), 0x3C5308, 5, 3, 2, -2303.9998f, 0.3f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_playerCollisionProbe + 0x20), 0x3C5308, 5, 3, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_secondaryCollisionContext + 0x40), 0x3C5108, 5, 2, 2, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_supportingPlatformCollisionQuery + 0x40), 0x3C5109, 5, 2, 2, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_playerCollisionProbe + 0x60), 0x3C5309, 5, 6, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_secondaryCollisionContext + 0x60), 0x3C5108, 5, 2, 2, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_secondaryCollisionContext + 0xA0), 0x344108, 0, 3, 3, -1235.4816f, 0.5f, 0.25f, 0.0f, 0.25f },
    { (CCollisionInfo2_t *)&g_effectRenderDefaults, 0x110108, 1, 3, 3, -4941.9263f, 0.7083334f, 0.1f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_secondaryCollisionContext, 0x345309, 0, 3, 3, -1535.9999f, 0.6f, 1.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_primaryCollisionContext, 0x305109, 0, 3, 3, 0.0f, 0.6f, 1.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_secondaryCollisionContext + 0xC0), 0x10, 0, 0, 0, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_portalAlternateCollisionQuery, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_portalNoModelFlagCollisionQuery, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_portalModeCollisionQuery, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_portalDefaultCollisionQuery, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_particleCollisionProbeResult, 0x1C000, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_playerCollisionProbe, 0x204408, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_defaultProbeMotionSettings, 0x1C000, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_collisionNoDetachSettingsAlternate, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_collisionSurfaceExcludedFromTrace, 0x0, 0, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_effectRenderDefaults + 0x20), 0x341508, 2, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_defaultActorCollisionInfo, 0x141508, 2, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)((char *)&g_secondaryCollisionContext + 0x80), 0x101508, 1, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)&g_supportingPlatformCollisionQuery, 0x105529, 5, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0 },
};
#endif
