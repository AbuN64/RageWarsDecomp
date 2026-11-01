#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"

extern void *g_courseOptionsScreen;
extern struct TextEntry g_rewardItemTiers[][17];
extern u8 *XPlus_CopyString(u8 *, u8 *);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
struct JoinNameEntry { u8 **names; s32 pad; };
extern struct JoinNameEntry g_joinPlayerNamesLocalized[];
#endif
#if defined(VERSION_EU_X)
enum { DRAW_ICON=913, DRAW_NAME=915, DRAW_VARIANT=914, DRAW_FIRST=916, DRAW_SECOND=917 };
#elif defined(VERSION_DE)
enum { DRAW_ICON=903, DRAW_NAME=905, DRAW_VARIANT=904, DRAW_FIRST=906, DRAW_SECOND=907 };
#else
enum { DRAW_ICON=909, DRAW_NAME=911, DRAW_VARIANT=910, DRAW_FIRST=912, DRAW_SECOND=913 };
#endif
void Join_UpdateJoinRequestDisplay(s32 index) {
    void *window;
    RequestDrawScreen *screen;
    MenuWidget *widget;
    s32 model;
    char *name;
    Shared_Game *game;
    void *widgetObject;
    void *variantObject;
    char ***variantSlot;
    screen = g_courseOptionsScreen;
    window = screen->roots[index];
    if (screen->count < index || g_joinRequestEntries[index].id < 0) {
        Widget_SetWidgetFlag08(window, 0);
    } else {
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_ICON);
        widget = widgetObject;
        widget->alpha = 125;
        model = Key_FindKeyIndex(g_joinRequestEntries[index].id);
        widget->value = g_characterPortraitRecords[model].portrait;
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_NAME);
        widget = widgetObject;
        widget->alpha = 125;
        model = Join_FindJoinModelIndex(g_joinRequestEntries[index].variant, g_joinRequestEntries[index].id);
    name = g_joinRequestEntries[index].name;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        game = &g_gameSettings;
        XPlus_CopyString((u8 *)name, g_joinPlayerNamesLocalized[g_joinRequestEntries[index].variant * 17 + model].names[game->language]);
#else
        XPlus_CopyString((u8 *)name,
          (u8 *)*g_rewardItemTiers[g_joinRequestEntries[index].variant][model].text
        );
#endif
        widget->text = name;
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_VARIANT);
        widget = widgetObject;
        widget->alpha = 125;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        widget->text = g_resultsRankTexts[g_joinRequestEntries[index].variant][game->language];
#else
        variantObject = &g_resultsRankTexts[g_joinRequestEntries[index].variant];
        variantSlot = variantObject;
        widget->text = **variantSlot;
#endif
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_FIRST);
        widget = widgetObject;
        widget->alpha = 125;
        widget->value = g_joinRequestDrawPairs[g_joinRequestEntries[index].word8].first;
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_SECOND);
        widget = widgetObject;
        widget->alpha = 125;
        widget->value = g_joinRequestDrawPairs[g_joinRequestEntries[index].word8].second;
    }
}

/* Seats the three join requests in free player settings slots, searching down from slot 7. */
extern u8 *XPlus_CopyString(u8 *, u8 *);
void Join_SeatJoinRequests(void) {
    Shared_PlayerSettingsRecord *player;
    s32 slot = 7;
    s32 i = 0;
    Shared_Game *g = &g_gameSettings;
    Shared_PlayerSettingsRecord *settings = g->playerSettings;
    do {
        if (slot <= 0) return;
        if (g_joinRequestEntries[i].id >= 0) {
            while (slot > 0 && g->playerSettings[slot].enabled == 1) {
                slot--;
            }
            if (slot >= 0) {
                player = &settings[slot];
                player->locked = 1;
                player->enabled = 1;
                player->slot = slot;
                player->character = g_joinRequestEntries[i].id;
                player->team = g_joinRequestEntries[i].variant;
                player->rank = g_joinRequestEntries[i].word8;
                player->variant = g_joinRequestEntries[i].variantC;
                XPlus_CopyString(player->name, (u8 *)g_joinRequestEntries[i].name);
                slot--;
            }
        }
        i++;
    } while (i < 3);
}
