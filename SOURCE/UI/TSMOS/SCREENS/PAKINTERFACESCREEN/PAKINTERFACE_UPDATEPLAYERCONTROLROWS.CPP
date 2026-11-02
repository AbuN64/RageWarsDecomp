#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"

/* Updates the four player control rows, their visibility, and the selected player label. */
extern s32 Control_IsControllerConnected(s32);
extern void Widget_SetWidgetFlag100(MenuWidget *record, int enable);
extern void *SmpOverlay_GetSlotValue(s32, s32);
void PAKInterface_UpdatePlayerControlRows(s32 player) {
    struct Shared_Item *item;
    struct WidgetLabelTextView *label;
    u16 id;
    s32 i;
    i = 0;
    do {
        if (i == 1) goto row_one;
        if (i < 2) {
            if (i == 0) goto row_zero;
#if defined(VERSION_DE)
            id = 662 + 6;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 665 + 6;
#elif defined(VERSION_EU_X)
            id = 671 + 6;
#endif
            goto row_done;
        }
        if (i == 2) goto row_two;
#if defined(VERSION_DE)
        id = 662 + 6;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 665 + 6;
#elif defined(VERSION_EU_X)
        id = 671 + 6;
#endif
        goto row_done;
    row_zero:
#if defined(VERSION_DE)
        id = 662;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 665;
#elif defined(VERSION_EU_X)
        id = 671;
#endif
        goto row_done;
    row_one:
#if defined(VERSION_DE)
        id = 662 + 2;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 665 + 2;
#elif defined(VERSION_EU_X)
        id = 671 + 2;
#endif
        goto row_done;
    row_two:
#if defined(VERSION_DE)
        id = 662 + 4;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 665 + 4;
#elif defined(VERSION_EU_X)
        id = 671 + 4;
#endif
    row_done:
        item = Node_FindWidgetByResourceId(g_pakProfileScreenState->window, id);
        if (Control_IsControllerConnected(i) == 1) {
            Widget_SetWidgetFlag100(item, 0);
        } else {
            Widget_SetWidgetFlag100(item, 1);
        }
        label = item->label;
        if (player != -1 && item == SmpOverlay_GetSlotValue(g_pakProfileScreenState->list, player)) {
            label->text = g_pakProfileScreenState->players[player].slots[g_pakProfileScreenState->players[player].chosen];
        } else {
            label->text = 0;
        }
        i += 1;
    } while (i < 4);
}
