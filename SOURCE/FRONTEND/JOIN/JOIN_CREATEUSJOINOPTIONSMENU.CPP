#include "COMMON/SCREEN.H"
#include "include_asm.h"

#if defined(VERSION_US)
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/REQUESTRECAT10.H"
#include "TYPES.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/REQUESTRECAT10.H"
#include "TYPES.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
extern struct CourseOptionsScreen *g_courseOptionsScreen;

s32 Join_CreateUsJoinOptionsMenu(void *root) {
    MenuWidget *item;
    s32 row;

    { void *memory = Cache_AllocateMemory(32); g_courseOptionsScreen = memory; }
    g_courseOptionsScreen->handle = root;
    g_courseOptionsScreen->mode = SmpOverlay_CreateOverlayNode((s32) root, 4);
    SmpOverlay_ShowSlotById((s32) root, 0, 905);
    SmpOverlay_ShowSlotById((s32) root, 1, 905);
    SmpOverlay_ShowSlotById((s32) root, 2, 905);
    SmpOverlay_ShowSlotById((s32) root, 3, 905);

    item = Node_FindWidgetByResourceId(root, 907);
    item->alpha = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(item, 0);
    }

    g_courseOptionsScreen->timer = 0;
    g_courseOptionsScreen->selection = 0;
    item = Node_FindWidgetByResourceId(root, 908);
    g_courseOptionsScreen->rows[0] = item;
    item = Node_FindWidgetByResourceId(root, 917);
    g_courseOptionsScreen->rows[1] = item;
    item = Node_FindWidgetByResourceId(root, 918);
    g_courseOptionsScreen->rows[2] = item;
    g_courseOptionsScreen->step = Join_CountUsedSlots();

    for (row = 0; row < 3; row++) {
        Join_UpdateJoinRequestDisplay(row);
        item = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[row], 914);
        Widget_SetWidgetFlag08(item, 0);
    }

    Tsmos_ActivateControllerState();

    item = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 914);
    Widget_SetWidgetFlag08(item, 1);
    return 0;
}
#endif

#if defined(VERSION_US)
#include "COMMON/ITEMRECAT20V1.H"
extern struct TextEntry g_rewardItemTiers[][17];
extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

s32 Join_SelectPreviousUsJoinModel(void *sender, void *context, void *argument, s32 event) {
    s32 variant;
    s32 model;
    s32 id;

    if (event != 1) return 0;
    MarkMenuEventHandled();
    if (Menu_GetPreviousScreenOwner(0) == 22) return 0;
    variant = g_joinRequestEntries[g_courseOptionsScreen->selection].variant;
    model = Join_FindJoinModelIndex(variant, g_joinRequestEntries[g_courseOptionsScreen->selection].id);
    do {
        variant--;
        if (variant < 0) {
            variant = 2;
            model--;
            if (model < 0) model = 16;
        }
        id = g_rewardItemTiers[variant][model].id;
    } while (id == -1);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variant = variant;
    g_joinRequestEntries[g_courseOptionsScreen->selection].id = id;
    XPlus_CopyString(g_joinRequestEntries[g_courseOptionsScreen->selection].name,
                    *g_rewardItemTiers[variant][id].text);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variantC = variant;
    Join_UpdateJoinRequestDisplay(g_courseOptionsScreen->selection);
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif

#if defined(VERSION_US)
extern struct TextEntry g_rewardItemTiers[][17];
extern void MarkMenuEventHandled();
extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

s32 CJoinCharacter_CycleModelSelection(void *unused0, void *unused1, void *unused2, s32 event) {
    s32 variant;
    s32 model;
    s32 id;

    if (event != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        return 0;
    }
    variant = g_joinRequestEntries[g_courseOptionsScreen->selection].variant;
    model = Join_FindJoinModelIndex(variant, g_joinRequestEntries[g_courseOptionsScreen->selection].id);
    do {
        variant++;
        if (variant >= 3) {
            variant = 0;
            model++;
            if (model >= 17) {
                model = 0;
            }
        }
        id = g_rewardItemTiers[variant][model].id;
    } while (id == -1);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variant = variant;
    g_joinRequestEntries[g_courseOptionsScreen->selection].id = id;
    XPlus_CopyString(g_joinRequestEntries[g_courseOptionsScreen->selection].name, *g_rewardItemTiers[variant][id].text);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variantC = variant;
    id = g_courseOptionsScreen->selection;
    Join_UpdateJoinRequestDisplay(id);
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif
