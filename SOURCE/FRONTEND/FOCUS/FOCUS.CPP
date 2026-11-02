#include "include_asm.h"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/PLAYERPROFILES.H"



#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/LABEL.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
extern void Cache_SetResourceActivityState(unsigned int value);
extern int Cache_GetResourceActivityState(void);
extern PlayerRecord g_profileUnlockFlagBase[];
extern s32 Defs_TestBit(void *bits, s32 bit);

static __inline__ MenuFrontendRefreshUnlockedFocusLabel *screen32(void) {
    void *block = g_profileStatisticsScreen;
    return block;
}

static __inline__ void *record32(void) { return &g_profileStatisticsScreen->record; }


#if defined(VERSION_DE)
enum { PROFILE_RESOURCE_498 = 494, PROFILE_RESOURCE_499 = 495, PROFILE_RESOURCE_500 = 496, PROFILE_RESOURCE_502 = 498, PROFILE_RESOURCE_505 = 501, PROFILE_RESOURCE_506 = 502, PROFILE_RESOURCE_509 = 505 };
#elif defined(VERSION_EU_X)
enum { PROFILE_RESOURCE_498 = 502, PROFILE_RESOURCE_499 = 503, PROFILE_RESOURCE_500 = 504, PROFILE_RESOURCE_502 = 507, PROFILE_RESOURCE_505 = 509, PROFILE_RESOURCE_506 = 511, PROFILE_RESOURCE_509 = 513 };
#else
enum { PROFILE_RESOURCE_498 = 498, PROFILE_RESOURCE_499 = 499, PROFILE_RESOURCE_500 = 500, PROFILE_RESOURCE_502 = 502, PROFILE_RESOURCE_505 = 505, PROFILE_RESOURCE_506 = 506, PROFILE_RESOURCE_509 = 509 };
#endif

/* The hub spells g_profileStatisticsScreen as the menu block; this unit keeps its ProfileStatisticsScreen view
   because it reads the 0x32-byte text buffers from 0x110 up, which the hub only pads over. */

extern const char g_longAndIntFormats[];

extern char g_profileStatisticsNumberFormat[];

/* EC30 hands back the hub Item view; this unit reads/writes the Label view (text pointer at 0x38)
   through the store-side cast. */
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);

extern char *Match_UpdateRankText(s32);

extern s32 Achieve_CountEarnedAchievements(s32);

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/MENU_MATCH_GLOBALS.H"
#endif

/* The hub spells g_profileStatisticsScreen as the padded menu block; its focus slot at +0x0EC is a word there,
   while this unit's view types it as a node pointer, so each member use casts to the view. */
extern TextEntry g_focusUnlockEntries[];

extern char g_focusUnlockLabelText[];

extern signed char g_profileSlotIndices[];


void Focus_UpdateFocusCaption(void) {
    s32 index;
    s32 count;
    s32 text;
    if (screen32()->focus == 0) {
        Model_SetPreviewModel(record32(), 0);
        return;
    }
    for (index = 0; index < 50; index++) {
        if (g_focusUnlockEntries[index].id == screen32()->focus->input) {
            if (Defs_TestBit(&g_profileUnlockFlagBase[screen32()->player], index) == 1) {
                text = 0;
                count = 0;
                switch (index) {
                case 36: text = 3701; break;
                case 37: text = 3702; break;
                case 38: text = 3703; break;
                case 39: text = 3704; break;
                case 40: text = 3705; break;
                case 41: text = 3706; break;
                case 42: text = 3707; break;
                case 43: text = 3708; break;
                case 44: text = 3709; break;
                case 45: text = 3710; break;
                case 46: text = 3711; break;
                case 47: text = 3712; break;
                case 48: text = 3713; break;
                case 49: text = 3714; break;
                default: text = 3700; count = index; break;
                }
                Model_SetPreviewModel(record32(), text);
                Model_SetPreviewRenderFlags(record32(), count);
                if (Cache_GetResourceActivityState() == 0) Cache_SetResourceActivityState(1);
            } else {
                Model_SetPreviewModel(record32(), 0);
            }
            return;
        }
    }
}

/* Fills the player record screen for the selected record g_localPlayerProfiles[index]: shows the record's
   name in item 0x1F3 and its rank text from Match_UpdateRankText in item 0x1F2, and formats into the
   screen's text buffers the record's counters at 0x70, 0x6C and 0x74, the value Achieve_CountEarnedAchievements
   reports and the byte at 0x17 for items 0x1FD, 0x1F4, 0x1F6, 0x1F9 and 0x1FA, making each item
   visible through Widget_SetWidgetFlag08_EquipActivateequipmentpanel. */
void Focus_RefreshProfileStatistics(void) {
    SlotSelectionWidget *item;
    s32 score;

    item = Node_FindWidgetByResourceId(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->handle, PROFILE_RESOURCE_499);
    Widget_SetWidgetFlag08(item, 1);
    ((Label *) item)->text = g_localPlayerProfiles[((ProfileStatisticsScreen *) g_profileStatisticsScreen)->index].name;
    item = Node_FindWidgetByResourceId(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->handle, PROFILE_RESOURCE_498);
    Widget_SetWidgetFlag08(item, 1);
    ((Label *) item)->text = Match_UpdateRankText(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->index);
    item = Node_FindWidgetByResourceId(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->handle, PROFILE_RESOURCE_509);
    Widget_SetWidgetFlag08(item, 1);
    XStdio_FormatBuffer(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->kills, g_longAndIntFormats, g_localPlayerProfiles[((ProfileStatisticsScreen *) g_profileStatisticsScreen)->index].statistics.kills);
    ((Label *) item)->text = ((ProfileStatisticsScreen *) g_profileStatisticsScreen)->kills;
    item = Node_FindWidgetByResourceId(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->handle, PROFILE_RESOURCE_500);
    Widget_SetWidgetFlag08(item, 1);
    XStdio_FormatBuffer(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->wins, g_longAndIntFormats, g_localPlayerProfiles[((ProfileStatisticsScreen *) g_profileStatisticsScreen)->index].statistics.wins);
    ((Label *) item)->text = ((ProfileStatisticsScreen *) g_profileStatisticsScreen)->wins;
    item = Node_FindWidgetByResourceId(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->handle, PROFILE_RESOURCE_502);
    Widget_SetWidgetFlag08(item, 1);
    XStdio_FormatBuffer(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->deaths, g_longAndIntFormats, g_localPlayerProfiles[((ProfileStatisticsScreen *) g_profileStatisticsScreen)->index].statistics.deaths);
    ((Label *) item)->text = ((ProfileStatisticsScreen *) g_profileStatisticsScreen)->deaths;
    score = Achieve_CountEarnedAchievements(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->index);
    item = Node_FindWidgetByResourceId(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->handle, PROFILE_RESOURCE_505);
    Widget_SetWidgetFlag08(item, 1);
    XStdio_FormatBuffer(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->score, g_profileStatisticsNumberFormat, score);
    ((Label *) item)->text = ((ProfileStatisticsScreen *) g_profileStatisticsScreen)->score;
    item = Node_FindWidgetByResourceId(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->handle, PROFILE_RESOURCE_506);
    Widget_SetWidgetFlag08(item, 1);
    XStdio_FormatBuffer(((ProfileStatisticsScreen *) g_profileStatisticsScreen)->count, g_profileStatisticsNumberFormat, g_localPlayerProfiles[((ProfileStatisticsScreen *) g_profileStatisticsScreen)->index].count);
    ((Label *) item)->text = ((ProfileStatisticsScreen *) g_profileStatisticsScreen)->count;
}

/* Sets the label text for the focused node: the text of its entry in the 50-entry id table when the
   current player's unlock bit for that entry is set, otherwise the default text; the European
   cartridges hold each entry's text per language and pick the current language's. */
void Focus_RefreshUnlockedFocusLabel(void) {
    s32 i;
    if (((MenuFrontendRefreshUnlockedFocusLabel *) g_profileStatisticsScreen)->focus == 0) {
        ((MenuFrontendRefreshUnlockedFocusLabel *) g_profileStatisticsScreen)->label->text = g_focusUnlockLabelText + 4;
        return;
    }
    for (i = 0; i < 50; i++) {
        if (g_focusUnlockEntries[i].id == ((MenuFrontendRefreshUnlockedFocusLabel *) g_profileStatisticsScreen)->focus->input) {
            if (Defs_TestBit(&g_profileUnlockFlagBase[((MenuFrontendRefreshUnlockedFocusLabel *) g_profileStatisticsScreen)->player], i) == 1) {
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
                ((MenuFrontendRefreshUnlockedFocusLabel *) g_profileStatisticsScreen)->label->text = g_focusUnlockEntries[i].text[0];
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
                ((MenuFrontendRefreshUnlockedFocusLabel *) g_profileStatisticsScreen)->label->text = g_focusUnlockEntries[i].text[g_frontendScreenStatus.settings.language];
#endif
            } else {
                ((MenuFrontendRefreshUnlockedFocusLabel *) g_profileStatisticsScreen)->label->text = g_focusUnlockLabelText + 4;
            }
            return;
        }
    }
}

void Focus_ShowUnlockedEntries(s32 style) {
    MenuWidget *node;
    s32 i;
    for (i = 0; i < 50; i++) {
        node = Node_FindWidgetByResourceId(g_profileStatisticsScreen->root, (u16)g_focusUnlockEntries[i].id);
        if (Defs_TestBit(&g_profileUnlockFlagBase[g_profileStatisticsScreen->activeSlot], i) == 1) {
            Widget_SetWidgetFlag08(node, 1);
            node->alpha = style;
        } else {
            Widget_SetWidgetFlag08(node, 0);
        }
    }
}

/* Advances a cursor over four 400-byte entries, wrapping to 0, until it reaches one whose flag byte in
   g_profileSlotIndices is not negative; after six steps without one it sets the cursor to -1. */
void Focus_AdvanceActiveSlot(int *cursor) {
    int steps;

    steps = 0;
    do {
        (*cursor)++;
        if (*cursor >= 4) {
            *cursor = 0;
        }
        steps++;
        if (steps >= 6) {
            *cursor = -1;
            return;
        }
    } while (g_profileSlotIndices[*cursor * 400] < 0);
}


/* Releases the object g_profileStatisticsScreen holds through Cache_FreeMemory, clears g_profileStatisticsScreen and returns zero.
 * The hub names g_profileStatisticsScreen as the menu block it points at; the release helper takes a plain pointer
 * and the clear stores a null word. */
s32 Focus_FreeMenuBlock(void) {
    Cache_FreeMemory(g_profileStatisticsScreen);
    g_profileStatisticsScreen = 0;
    return 0;
}
