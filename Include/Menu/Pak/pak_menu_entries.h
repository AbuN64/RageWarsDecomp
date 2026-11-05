#ifndef MENU_PAK_PAK_MENU_ENTRIES_H
#define MENU_PAK_PAK_MENU_ENTRIES_H
#include "Common/pak_enter_player_options.h"
struct MenuStyle;
struct StyledMenuTextPanel;
struct TextBoundsText;
extern void Menu_DrawMenuEntries(struct MenuStyle *menu, s8 *member);
extern void Menu_DrawMenuPanel(struct StyledMenuTextPanel *menu, struct TextBoundsText *text, s32 relative);
/* The draw style menu item callbacks receive last: alpha and fade scale the item's intensity. */
typedef struct MenuStyle {
    /* The same record Menu_DrawStyledMenuText draws through as its fourth argument (StyledMenuTextPanel), and
       Setup_DrawNameCursor reads its id at +0x1C. */
    s16 state;
    s16 x; /* 0x02 */
    s16 y; /* 0x04 */
    char pad6[6];
    struct TextBoundsText *entries; /* 0x0C */
    s32 count; /* 0x10 */
    char pad14[0x1C - 0x14];
    s32 id; /* 0x1C */
    char pad20[0x30 - 0x20];
    f32 alpha; /* 0x30 */
    f32 fade; /* 0x34 */
    s32 shadowEnabled;
    s32 panelDisablesShadow;
} MenuStyle;

#endif
