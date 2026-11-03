#include "include_asm.h"
#include "COMMON/SCREEN.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/LABEL.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "TYPES.H"

/* SLOT.CPP */
/* 8041BEA8_7.CPP */
#if defined(VERSION_US_REV1) || defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
/* Builds the player-selection menu block at 0x800E3590 for one menu tree: it allocates the block
 * with a 528-byte window request, remembers the tree and the pool SmpOverlay_CreateOverlayNode_Slot returns for it,
 * arms the tree's four option groups with id 513, hands the pool back to SmpOverlay_SetObjectValue, and
 * keeps the windows 492, 491, 486, 563, 510, 512, 511 and their lookup results in the block. The
 * window geometry is nudged by whole groups of four pixels so each window snaps to a 4-pixel grid;
 * the menu item window 488 and the two label windows 496/497 get fixed alpha bytes 110/120, window
 * 493 gets 110, and window 511 is cleared before the block is handed to Focus_AdvanceActiveSlot_Menu. */
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/LABEL.H"
#include "COMMON/ANIMATION.H"
#include "TYPES.H"
#include "FRONTEND/SMP_OVERLAY.H"

/* g_profileStatisticsScreen and its 528-byte block layout are spelled once in the closed hub as
 * SlotSelectionMenuBlock, shared with the neighbouring menu units that keep their own views over
 * the same block. */

/* The hub spells Focus_AdvanceActiveSlot_Menu; these two stay here, matching how the landed units that own
 * them define them: SmpOverlay_SetObjectValue writes the word at +0x6C of the object it is handed, and
 * Focus_ShowUnlockedEntries takes the style word this block keeps at +0x0FC. */

/* The pool and style helpers take a word, while this unit and the window lookups carry the menu
 * tree as a pointer; the cast carries that pointer through unchanged. */
/* Resource ids of this screen are numbered per version: de -4, eu-x 4 relative to us. */
static inline s32 slotRes(s32 id) {
#if defined(VERSION_DE)
    return id - 4;
#elif defined(VERSION_EU_X)
    return id + 4;
#else
    return id;
#endif
}

s32 Frontend_CreateSlotSelectionMenu(void *menuTree) {
    SlotSelectionWidget *item;
    s32 shift;
    s32 adjust;

    g_profileStatisticsScreen = (SlotSelectionMenuBlock *) Cache_AllocateMemory(528);
    g_profileStatisticsScreen->root = menuTree;
    g_profileStatisticsScreen->list = SmpOverlay_CreateOverlayNode((s32) menuTree, 4);
    SmpOverlay_ShowSlotById((s32) menuTree, 0, slotRes(513));
    SmpOverlay_ShowSlotById((s32) menuTree, 1, slotRes(513));
    SmpOverlay_ShowSlotById((s32) menuTree, 2, slotRes(513));
    SmpOverlay_ShowSlotById((s32) menuTree, 3, slotRes(513));
    /* SmpOverlay_CreateOverlayNode_Slot is published to this unit as handing back a word while SmpOverlay_SetObjectValue is
     * published as taking the pool object that word names; the cast puts that object view back on
     * the pool stored at +0x004 and carries it through unchanged. */
    SmpOverlay_SetObjectValue((struct Object6C *) g_profileStatisticsScreen->list, 1);

    g_profileStatisticsScreen->menuPhase = 1;
    g_profileStatisticsScreen->reservedWord = 4;
    g_profileStatisticsScreen->item492 = Node_FindWidgetByResourceId(menuTree, slotRes(492));
    g_profileStatisticsScreen->item492->x = g_profileStatisticsScreen->item492->x - g_profileStatisticsScreen->item492->w;
    shift = g_profileStatisticsScreen->item492->w;
    if (shift < 0) {
        shift += 3;
    }
    g_profileStatisticsScreen->round492 = shift >> 2;
    adjust = g_profileStatisticsScreen->item492->w - ((shift >> 2) << 2);
    g_profileStatisticsScreen->item492->x = g_profileStatisticsScreen->item492->x + adjust;

    g_profileStatisticsScreen->item491 = Node_FindWidgetByResourceId(menuTree, slotRes(491));
    g_profileStatisticsScreen->item491->x = g_profileStatisticsScreen->item491->x + g_profileStatisticsScreen->item491->w;
    shift = g_profileStatisticsScreen->item491->w;
    if (shift < 0) {
        shift += 3;
    }
    g_profileStatisticsScreen->round491 = shift >> 2;
    adjust = g_profileStatisticsScreen->item491->w - ((shift >> 2) << 2);
    g_profileStatisticsScreen->item491->x = g_profileStatisticsScreen->item491->x - adjust;

    Node_FindWidgetByResourceId(menuTree, slotRes(488))->alpha = 110;
    g_profileStatisticsScreen->lookup486 = SmpFlicker_CreateFlickerWidget((s32)slotRes(486), 255);

    item = Node_FindWidgetByResourceId(menuTree, slotRes(486));
    g_profileStatisticsScreen->item486 = item;
    Widget_SetWidgetFlag08(item, 0);

    item = Node_FindWidgetByResourceId(menuTree, slotRes(563));
    g_profileStatisticsScreen->item563 = item;
    Widget_SetWidgetFlag08(item, 0);

    Node_FindWidgetByResourceId(menuTree, slotRes(496))->alpha = 110;
    Node_FindWidgetByResourceId(menuTree, slotRes(497))->alpha = 120;

    item = Node_FindWidgetByResourceId(menuTree, slotRes(512));
    g_profileStatisticsScreen->item512 = item;
    Widget_SetWidgetFlag08(item, 0);

    g_profileStatisticsScreen->style = 0;
    g_profileStatisticsScreen->reservedWord1 = 27;
    item = Node_FindWidgetByResourceId(menuTree, slotRes(511));
    g_profileStatisticsScreen->item511 = item;
    Widget_SetWidgetFlag08(item, 0);

    g_profileStatisticsScreen->item511->alpha = 0;
    g_profileStatisticsScreen->reservedWord2 = 25;
    item = Node_FindWidgetByResourceId(menuTree, slotRes(510));
    g_profileStatisticsScreen->item510 = item;

    g_profileStatisticsScreen->player = 0;
    g_profileStatisticsScreen->activeSlot = -1;
    Focus_AdvanceActiveSlot(&g_profileStatisticsScreen->activeSlot);
    Focus_RefreshProfileStatistics();
    Focus_ShowUnlockedEntries(g_profileStatisticsScreen->style);
    Node_FindWidgetByResourceId(menuTree, slotRes(493))->alpha = 110;
    g_profileStatisticsScreen->focus = 0;
    return 0;
}
#endif

/* 8041BEA8.CPP */
/* Steps the record screen's transition state machine: slides the two panels in or out, swaps the
   visible item groups as each phase's timer runs out, and while idle (state 3) pulses the cursor's
   style from the elapsed time and moves the cursor to the node now under focus. */

/* The hub spells g_profileStatisticsScreen as the padded menu block; this unit's view of it is the published
   FrontendPanelTransitionView struct, so each member use casts g_profileStatisticsScreen to that view. */

extern void Menu_ReturnToPreviousScreen(void);

extern void SmpFlicker_StartFlicker(struct FlickerStartView *object, s32 count);
extern void *SmpOverlay_GetSlotValue(s32, s32);

/* Focus_ShowUnlockedEntries is declared by span LABEL_Slot.h; no local extern needed. */

s32 Frontend_AnimateSlotSelectionMenu(s32 unused0, s32 unused1, s32 animationStep) {
    NodeFrontendAnimateSlotSelectionMenu *node;

    switch (((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state) {
    case 1:
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->left->x += ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->leftStep;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->right->x -= ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->rightStep;
        if (--((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer <= 0) {
            SoundElement_PlayFlatSound(3705);
            /* NodeFrontendAnimateSlotSelectionMenu is the hub Item view's twin (style at 0x10, x/y at 0x14/0x16);
               E8D8 speaks Item, so the node slots cast to it here. */
            Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupA, 1);
            SmpFlicker_StartFlicker(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->fade, 4);
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 4;
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer = 4;
        }
        break;
    case 2:
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->left->x -= ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->leftStep;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->right->x += ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->rightStep;
        if (--((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer <= 0) {
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 3;
            MarkMenuEventHandled();
            Menu_ReturnToPreviousScreen();
            return 0;
        }
        break;
    case 4:
        if (SmpFlicker_IsFlickerIdle(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->fade) != 0) {
            SmpFlicker_RestoreFlickerValue(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->fade);
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 6;
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer = 4;
            Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupB, 1);
            Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupC, 1);
        }
        break;
    case 5:
        SoundElement_PlayFlatSound(3704);
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 2;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer = 4;
        Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupB, 0);
        Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupC, 0);
        Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupA, 0);
        break;
    case 6:
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->styleValue += ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->styleStep;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupC->style += ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->alphaStep;
        Focus_ShowUnlockedEntries(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->styleValue);
        if (--((FrontendPanelTransitionView *) g_profileStatisticsScreen)->timer <= 0) {
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->groupC->style = 100;
            Focus_ShowUnlockedEntries(110);
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state = 3;
            Widget_SetWidgetFlag08((SlotSelectionWidget *) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->cursor, 1);
        }
        break;
    case 7:
        break;
    }

    if (((FrontendPanelTransitionView *) g_profileStatisticsScreen)->state == 3) {
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->clock += animationStep;
        ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->cursor->style = Math_Cosf((f32) ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->clock * 0.0033333334f) * 30.0f + 220.0f;
        node = SmpOverlay_GetSlotValue(((FrontendPanelTransitionView *) g_profileStatisticsScreen)->handle, 0);
        if (node != ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->focus) {
            SoundElement_PlayFlatSound(3710);
            if (((FrontendPanelTransitionView *) g_profileStatisticsScreen)->focus != 0) {
                ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->focus->style = 110;
            }
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->focus = node;
            node->style = 225;
            Focus_RefreshUnlockedFocusLabel();
            Focus_UpdateFocusCaption();
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->cursor->x = node->x - 2;
            ((FrontendPanelTransitionView *) g_profileStatisticsScreen)->cursor->y = node->y;
        }
    }
    return 0;
}

#if !(defined(VERSION_EU) || defined(VERSION_US))
unsigned int k_SlotZeroWords[1] = {
    0x00000000,
};
#endif
#if defined(VERSION_EU) || defined(VERSION_US)
const unsigned int k_SlotZeroWords[1] = {
    0x00000000,
};
#endif

/* 80406A88_2.CPP */

/* 80408AC4_19.CPP */
