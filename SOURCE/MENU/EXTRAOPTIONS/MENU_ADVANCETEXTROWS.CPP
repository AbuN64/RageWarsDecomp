#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/NUMBERPADSCREEN.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SCREEN.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"


#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define CREDITS_LINES g_creditsLocalizedLines[g_languageIndex]
#else
#define CREDITS_LINES g_creditsLocalizedLines[0]
#endif
#if defined(VERSION_DE)
#define ID_ROW0 946
#define ID_CLOSE 933
#elif defined(VERSION_EU_X)
#define ID_ROW0 956
#define ID_CLOSE 943
#else
#define ID_ROW0 952
#define ID_CLOSE 939
#endif
void Menu_AdvanceTextRows(void) {
    MenuWidget *item;
    char *text;
    s32 line;
    s32 index;

    line = g_extraOptionsScreen->length;
    index = g_extraOptionsScreen->value;
    do {
        text = CREDITS_LINES[index];

        if (text != 0) {
            index++;
        }
        item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0);
        switch (line) {
        case 0:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0);
            break;
        case 1:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 1);
            break;
        case 2:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 2);
            break;
        case 3:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 3);
            break;
        case 4:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 4);
            break;
        case 5:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 5);
            break;
        case 6:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 6);
            break;
        case 7:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 7);
            break;
        case 8:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 8);
            break;
        case 9:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 9);
            break;
        }
        item->text = text;
        line++;
    } while (line < 10);
        if (CREDITS_LINES[g_extraOptionsScreen->value] != 0)

    {
        if (g_extraOptionsScreen->length == 0) {
            g_extraOptionsScreen->value++;
        }
    } else {
        Widget_SetWidgetFlag08(g_extraOptionsScreen->pad, 0);
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_CLOSE), 1);
        g_extraOptionsScreen->cursor = 1;
    }
    if (g_extraOptionsScreen->length > 0) {
        g_extraOptionsScreen->length--;
    }
}
