#include "COMMON/FRUSTUM.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/LAYOUT.H"
#include "TYPES.H"
#include "FRONTEND/NODE_CREATEGRIDLISTFROMWIDGET.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/WIDGET_DRAWTEXTWIDGET.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"

/* Visits every cell of a list's column-by-row grid, computing each cell's rectangle through Node_ConfigureScrolledTableCell and drawing it through Widget_DrawTextWidget_NodeCreategridlistfromwidget with the given style. */







extern void Node_ConfigureScrolledTableCell(GridList *list, UnitMtx *cell, u32 column, u32 row);


/* Allocates and zeroes a 0x60-byte record, copies the header of the record Node_FindWidgetByResourceId finds for the low half of the first argument, tags it 0xB, stores four byte arguments and three alternating pairs of the last two, allocates and zeroes a width-by-height table of eight-byte cells at 0x44, and registers the record through Node_ReplaceWidgetLinks.
   Adapted from SmpSlider_CreateSliderWidget with the record size, tag 0xB, the byte fields, the cell table and the Node_ReplaceWidgetLinks registration changed. */









extern struct Record *Cache_AllocateMemory(s32 size);


extern void Node_ReplaceWidgetLinks(s32 node, s32 parent, MenuWidget *oldWidget, MenuWidget *newWidget);

/* Looks up the entry with the given identifier among the list Node_GetScreenData returns for what GetMenuScreenOwner returns, through Node_FindWidgetByResourceId, and stores two words into the eight-byte cell at the given row and column of its cell table at 0x44, whose row width is the byte at 0x4B.
   Adapted from Node_SetGridBackgroundColors with the three byte stores replaced by the two cell-word stores changed. */






/* When the fourth argument is set, lowers the byte at offset 0x4C of an entry by one while it is
   above the minimum at 0x50; then calls Node_ClampListCursorAndScroll and MarkMenuEventHandled. Returns zero. */
extern void Node_ClampListCursorAndScroll(void *);

extern void MarkMenuEventHandled();

/* Releases an object through Cache_FreeMemory, first releasing the object it holds at offset 0x44
   when there is one, and returns zero. */



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
    Node_ReplaceWidgetLinks(context, 0, source, result);
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

s32 Node_SelectPreviousGridRow(u8 *entry, void *second, void *third, s32 active) {
    s32 value = entry[76];

    if (active && entry[80] < value) {
        entry[76] = value - 1;
    }
    Node_ClampListCursorAndScroll(entry);
    MarkMenuEventHandled();
    return 0;
}

s32 Node_SelectNextGridRow(u8 *entry, void *second, void *third, s32 active) {
    u8 value = entry[76];

    if (active && value < entry[74] - 1) {
        entry[76] = value + 1;
    }
    Node_ClampListCursorAndScroll(entry);
    MarkMenuEventHandled();
    return 0;
}

s32 Node_SelectPreviousGridColumn(u8 *entry, void *second, void *third, s32 active) {
    s32 value = entry[77];

    if (active && entry[81] < value) {
        entry[77] = value - 1;
    }
    Node_ClampListCursorAndScroll(entry);
    MarkMenuEventHandled();
    return 0;
}

s32 Node_SelectNextGridColumn(u8 *entry, void *second, void *third, s32 active) {
    u8 value = entry[77];

    if (active && value < entry[75] - 1) {
        entry[77] = value + 1;
    }
    Node_ClampListCursorAndScroll(entry);
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
