#include "TYPES.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/NAME.H"

/* Relabels the four slot rows of the block g_pakProfileScreenState points to: for each row item (0x28B, 0x28D,
   0x28F, then 0x291) of the block's window it calls Widget_SetWidgetFlag100_MenuRefreshextraoptionlocks(0) and points the text at 0x38
   of the item's label at 0x8 at player p's chosen slot (the index at 0xAEC of p's 2920-byte record
   at 0x58, slots of 400 bytes from 0x18) when p is not -1 and SmpOverlay_GetSlotValue_PakinterfaceRelabelslotrows reports
   this row as p's focus in the list at 0x4, otherwise at the row's 400-byte record in g_localPlayerProfiles
   when its owner byte 0xD is not negative, or at nothing. */
/* The first row item's id: eu-x numbers its items 9 higher and de 1 higher, as each cartridge's
   own bytes show; us, us-rev1 and eu share 0x28B. */
extern char g_localPlayerProfiles[];
extern s8 g_profileSlotIndices[];
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
extern void Widget_SetWidgetFlag100(MenuWidget *record, int enable);
extern void *SmpOverlay_GetSlotValue(s32, s32);
void PAKInterface_RelabelSlotRows(s32 player) {
    struct ItemFrontendRelabelSlotRows *item;
    struct WidgetLabelTextView *label;
    s32 id;
    s32 i;
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
#if defined(VERSION_DE)
            id = 652;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 651;
#elif defined(VERSION_EU_X)
            id = 660;
#endif
            break;
        case 1:
#if defined(VERSION_DE)
            id = 652 + 2;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 651 + 2;
#elif defined(VERSION_EU_X)
            id = 660 + 2;
#endif
            break;
        case 2:
#if defined(VERSION_DE)
            id = 652 + 4;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 651 + 4;
#elif defined(VERSION_EU_X)
            id = 660 + 4;
#endif
            break;
        default:
#if defined(VERSION_DE)
            id = 652 + 6;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 651 + 6;
#elif defined(VERSION_EU_X)
            id = 660 + 6;
#endif
            break;
        }
        item = Node_FindWidgetByResourceId(g_pakProfileScreenState->window, id);
        Widget_SetWidgetFlag100(item, 0);
        label = item->label;
        if (player != -1 && item == SmpOverlay_GetSlotValue(g_pakProfileScreenState->list, player)) {
            label->text = g_pakProfileScreenState->players[player].slots[g_pakProfileScreenState->players[player].chosen];
        } else if (g_profileSlotIndices[i * 400] >= 0) {
            label->text = &g_localPlayerProfiles[i * 400];
        } else {
            label->text = 0;
        }
    }
}
