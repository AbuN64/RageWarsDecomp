#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "MENU/GFX/IMAGE.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/WIDGETRECAT34.H"
#include "FRONTEND/LAYOUT.H"
#include "TYPES.H"
#include "FRONTEND/ARCHIVEDATA.H"
#include "FRONTEND/NODE_RELEASECHUNKIMAGES.H"
#include "FRONTEND/NODE_GETIMAGETEXTURE.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RESMGR/resmgr_string_memory.H"

extern BufferPool g_frontendResourceScreenCount;
extern ManagerFrontendReleaseAllChunkImages g_frontendResourceFontCount;
extern ArchiveTextureEntry *g_frontendResourceTextures;
/* Releases the buffers of the pool at g_frontendResourceScreenCount: every entry holding a buffer that is not locked
   (flag 1) unless force is set has its reference count forced to one and dropped, and when it
   reaches zero the buffer is freed through Cache_FreeMemory, along with the entry's secondary buffer
   when secondary buffers are in use (g_frontendArchiveResident), and the entry is cleared. Pool fields read as one struct at g_frontendResourceScreenCount, as in Node_UpdateImageReleaseTimers. */







extern s32 g_frontendArchiveResident;


/* Returns the screen count g_frontendResourceState.NScreens. */


/* Returns the texture count g_frontendResourceState.NTextures. */
extern s16 g_frontendResourceTextureCount;

/* Returns the font count g_frontendResourceState.NFonts. */


/* Returns the halfword at offset 0xA of entry i in the 28-byte record table g_frontendResourceTextures points
   to; Node_GetTextureEntryWidth and Node_GetTextureEntryHeight read offsets 0xA and 0xC. */




/* Returns the halfword at offset 0xC of entry i in the 28-byte record table g_frontendResourceTextures points
   to; Node_GetTextureEntryWidth and Node_GetTextureEntryHeight read offsets 0xA and 0xC. */




/* Returns entry i of the chroma key table g_frontendResourceState.ChromaKey. */

/* Releases UI resource slot i once its retain count reaches zero, closing its open entry and clearing the slot id. */






extern struct FrontendTextureTimerEntry *g_frontendResourceTextureTimers;


/* Returns the signed byte at offset 0x9 of entry j in the 8-byte entries that begin record i of
   the font table g_frontendResourceState.Font (1180-byte records). */


/* Returns the signed byte at offset 0xA of entry j in the 8-byte entries that begin record i of
   the font table g_frontendResourceState.Font (1180-byte records). */


/* Returns the halfword at offset 0xE of the object held at offset 0x48C of record i in the
   font table g_frontendResourceState.Font (1180-byte records); Node_GetFontLetterSpacing reads offset 0x10 of the same
   object. */


/* Runs Node_ReleaseChunkImages for each of the manager g_frontendResourceFontCount's entries unless its mode word at 0x34 is 1. */




/* The debugger showed this global holding 0x80698160, a heap address rather than a static one,
   so it is a pointer variable and not an array base. The returned words were 0x8069A52F and
   0x8069A673, which are guest addresses that are not word aligned, so the element type is a
   pointer to bytes. */

/* Calls Node_LoadLanguageStrings when the language count g_frontendResourceState.NLanguages is non-zero. */

extern void Node_LoadLanguageStrings(s32);

/* Twelve bytes of stride and a load at offset 8. The debugger showed the global holding
   0x80697F80 and the results being 0, 0x8067E570, 0x8067F870 and 0x80697E00, so the third word is
   a pointer that may be absent. The largest index seen was 0x1D, which is inside the bound of 36
   that Node_IsValidScreenIndex_NodeConfigurescrolledtablecell checks against g_frontendResourceScreenCount, so this is an accessor over the same table. */

/* Returns whether an index lies inside the table bound g_frontendResourceScreenCount, from zero up to but not
   including it. */


/* Drops one reference to buffer pool entry i and, when none remain, frees its primary and secondary buffers and clears the entry. */







/* Clears the 0x2A8-byte block g_frontendResourceState through XPlus_FillBytes, sets g_frontendWidgetStateChanged and clears
   g_frontendArchiveResident. */

extern s32 g_frontendWidgetStateChanged;


/* Sets the buffer pool flag, then runs Node_AcquireArchiveEntry on every buffer pool entry, Node_GetImageTexture_NodeConfigurescrolledtablecell in mode 2 on every resource slot and Node_GetBankTileTexture on every chunk. */





extern void Node_AcquireArchiveEntry(s32 index);

extern void Node_GetBankTileTexture(s32 which, s32 index, s32 pass);

/* A stride of 1180 bytes. The debugger showed the global holding 0x80696F50 and the two observed
   indices, 0 and 1, returning 0x80696F50 and 0x806973EC, which differ by exactly 1180. */




extern void Node_ReleaseRetainedImageSlot(s32 i);

/* Loads or unloads the images of a widget subtree: visits the later siblings when asked and the
   children, then for an image widget (type 3) loads its image through Node_GetImageTexture_NodeConfigurescrolledtablecell or unloads it
   through Node_ReleaseRetainedImageSlot, and for a button (type 8) visits its normal, pressed and highlighted
   variants without their siblings; type 4 widgets and other types have nothing to do. */





typedef struct List List;

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at s_typeText, an actor kind at g_typedWidgetEventActorKinds and a handler at g_typedWidgetEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */



extern unsigned int s_typeText[];

extern s32 g_typedWidgetEventActorKinds;

extern WidgetEventHandler g_typedWidgetEventHandlers;

void Node_ReleaseUnprotectedBuffers(s32 force) {
    s32 i;

    for (i = 0; i < g_frontendResourceScreenCount.count; i++) {
        if (g_frontendResourceScreenCount.primary[i].reservedPointer != 0 && (!(g_frontendResourceScreenCount.flags[i] & 1) || force != 0)) {
            g_frontendResourceScreenCount.refs[i] = 1;
            g_frontendResourceScreenCount.refs[i]--;
            if (g_frontendResourceScreenCount.primary[i].reservedPointer != 0 && g_frontendResourceScreenCount.refs[i] == 0) {
                Cache_FreeMemory(g_frontendResourceScreenCount.primary[i].reservedPointer);
                if (g_frontendArchiveResident != 0 && g_frontendResourceScreenCount.secondary != 0 &&
                    g_frontendResourceScreenCount.secondary[i].reservedPointer != 0) {
                    Cache_FreeMemory(g_frontendResourceScreenCount.secondary[i].reservedPointer);
                }
                g_frontendResourceScreenCount.primary[i].reservedPointer = 0;
            }
        }
    }
}

/** Perform no work. */
void Node_SkipResourceOperation(void) {
}

s16 Node_GetResourceScreenCount(void) {
    return g_frontendResourceState.NScreens;
}

s16 Node_GetResourceTextureCount(void) {
    return g_frontendResourceState.NTextures;
}

s16 Node_GetResourceFontCount(void) {
    return g_frontendResourceState.NFonts;
}

/* Returns the word held in g_frontendResourceFirstScreen. */


s32 Node_GetFirstResourceScreen(void) {
    return g_frontendResourceState.Header.FirstScreen;
}

s16 Node_GetTextureEntryWidth(s32 index) {
    return g_frontendResourceState.Texture[index].Width;
}

s16 Node_GetTextureEntryHeight(s32 index) {
    return g_frontendResourceState.Texture[index].Height;
}

s32 Node_GetTextureChromaKey(s32 index) {
    return g_frontendResourceState.ChromaKey[index];
}

/** Report success. */
int Node_ReturnOne(void) {
    return 1;
}

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

signed char Node_GetFontCharacterHeight(int entry, int index) {
    return g_frontendResourceState.Font[index].CharInfo[(unsigned char)entry].height;
}

signed char Node_GetFontCharacterPhysicalWidth(int entry, int index) {
    return g_frontendResourceState.Font[index].CharInfo[(unsigned char)entry].PhysicalWidth;
}

short Node_GetFontBitmapCount(int index) {
    return g_frontendResourceState.Font[index].TableEntry->bitmapCount;
}

short Node_GetFontLetterSpacing(int index) {
    return g_frontendResourceState.Font[index].TableEntry->letterSpacing;
}

short Node_GetFontMetricAtA(int index) {
    return g_frontendResourceState.Font[index].TableEntry->verticalOffset;
}

short Node_GetFontMetricAtC(int index) {
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

void Node_ReleaseAllChunkImages(void) {
    int i;

    if (g_frontendResourceFontCount.mode != 1) {
        for (i = 0; i < g_frontendResourceFontCount.count; i++) {
            Node_ReleaseChunkImages(i);
        }
    }
}

char *Node_GetStringByIndex(s32 index) {
    return g_frontendResourceState.StringTable[index];
}

/* Returns the halfword held in g_frontendResourceLanguageCount. */


s16 Node_GetResourceLanguageCount(void) {
    return g_frontendResourceState.NLanguages;
}

void Node_LoadLanguageStringsIfAny(s32 languageIndex) {
    if (g_frontendResourceState.NLanguages != 0) {
        Node_LoadLanguageStrings(languageIndex);
    }
}

void *Node_GetScreenData(s32 index) {
    return g_frontendResourceState.Screen[index].data;
}

s32 Node_IsValidScreenIndex(s32 index) {
    if (index >= 0 && index < g_frontendResourceState.NScreens) {
        return 1;
    }
    return 0;
}

void Node_ReleaseReferencedBuffer(s32 i) {
    g_frontendResourceScreenCount.refs[i]--;
    if (g_frontendResourceScreenCount.primary[i].reservedPointer != 0 && g_frontendResourceScreenCount.refs[i] == 0) {
        Cache_FreeMemory(g_frontendResourceScreenCount.primary[i].reservedPointer);
        if (g_frontendArchiveResident != 0 && g_frontendResourceScreenCount.secondary != 0 &&
            g_frontendResourceScreenCount.secondary[i].reservedPointer != 0) {
            Cache_FreeMemory(g_frontendResourceScreenCount.secondary[i].reservedPointer);
        }
        g_frontendResourceScreenCount.primary[i].reservedPointer = 0;
    }
}

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

void Node_AcquireAllResourceTextures(void) {
    s32 i;

    g_frontendResourceScreenCount.dirty = 1;
    for (i = 0; i < g_frontendResourceScreenCount.count; i++) {
        Node_AcquireArchiveEntry(i);
    }
    for (i = 0; i < g_frontendResourceTextureCount; i++) {
        Node_GetImageTexture(i, 2);
    }
    for (i = 0; i < g_frontendResourceFontCount.count; i++) {
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
}

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
            if (((struct AnimationEventMaskView *) (((char *) (&s_typeText)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_typedWidgetEventActorKinds)) + offset))->value;
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
