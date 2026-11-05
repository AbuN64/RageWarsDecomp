#include "include_asm.h"
#include "Scene/cache_freememory.h"
#include "Common/playerprofiles.h"
#include "Common/label.h"
#include "Common/selectionscreenstate.h"
#include "Common/globals.h"
#include "Common/runtime_declarations.h"
#include "Ui/X_files/x_stdio.h"

/* unit FOCUS.CPP */
static __inline__ MenuFrontendRefreshUnlockedFocusLabel *Focus_GetStatisticsScreen(void) {
    void *block = g_profileStatisticsScreen;
    return block;
}

static __inline__ void *Focus_GetStatisticsRecord(void) { return &g_profileStatisticsScreen->record; }

#if defined(VERSION_DE)
enum { PROFILE_RESOURCE_498 = 494, PROFILE_RESOURCE_499 = 495, PROFILE_RESOURCE_500 = 496, PROFILE_RESOURCE_502 = 498, PROFILE_RESOURCE_505 = 501, PROFILE_RESOURCE_506 = 502, PROFILE_RESOURCE_509 = 505 };
#elif defined(VERSION_EU_X)
enum { PROFILE_RESOURCE_498 = 502, PROFILE_RESOURCE_499 = 503, PROFILE_RESOURCE_500 = 504, PROFILE_RESOURCE_502 = 507, PROFILE_RESOURCE_505 = 509, PROFILE_RESOURCE_506 = 511, PROFILE_RESOURCE_509 = 513 };
#else
enum { PROFILE_RESOURCE_498 = 498, PROFILE_RESOURCE_499 = 499, PROFILE_RESOURCE_500 = 500, PROFILE_RESOURCE_502 = 502, PROFILE_RESOURCE_505 = 505, PROFILE_RESOURCE_506 = 506, PROFILE_RESOURCE_509 = 509 };
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Common/menu_match_globals.h"
#include "Cache/cache_allocresourceblock.h"
#include "Defs/defs.h"
#include "Match/match_updateranktext.h"
#include "Achieve/achieve.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"
#endif

void Focus_UpdateFocusCaption(void) {
    s32 index;
    s32 count;
    s32 text;
    if (Focus_GetStatisticsScreen()->focus == 0) {
        Model_SetPreviewModel(Focus_GetStatisticsRecord(), 0);
        return;
    }
    for (index = 0; index < 50; index++) {
        if (g_focusUnlockEntries[index].id == Focus_GetStatisticsScreen()->focus->value) {
            if (Defs_TestBit(&g_profileUnlockFlagBase[Focus_GetStatisticsScreen()->player], index) == 1) {
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
                Model_SetPreviewModel(Focus_GetStatisticsRecord(), text);
                Model_SetPreviewRenderFlags(Focus_GetStatisticsRecord(), count);
                if (Cache_GetResourceActivityState() == 0) Cache_SetResourceActivityState(1);
            } else {
                Model_SetPreviewModel(Focus_GetStatisticsRecord(), 0);
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
        if (g_focusUnlockEntries[i].id == ((MenuFrontendRefreshUnlockedFocusLabel *) g_profileStatisticsScreen)->focus->value) {
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
    } while (g_profileSlotIndices[*cursor][0] < 0);
}

/* Releases the object g_profileStatisticsScreen holds through Cache_FreeMemory, clears g_profileStatisticsScreen and returns zero. */
s32 Focus_FreeMenuBlock(void) {
    Cache_FreeMemory(g_profileStatisticsScreen);
    g_profileStatisticsScreen = 0;
    return 0;
}

/* unit INTEGER_FORMAT_STRINGS.CPP */
const char g_longAndIntFormats[7] =
    "%ld\000%d\000";
