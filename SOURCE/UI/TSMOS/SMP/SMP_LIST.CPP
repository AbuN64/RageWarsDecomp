#include "COMMON/ANIMATION.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/STATEPAIR.H"
#include "MENU/SCROLL.H"
#include "TYPES.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "MENU/SMPLIST_REGISTERLISTCLASS.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* SMP_LIST.CPP */
/* Sets the word at 0x54 of commandListMenu to 2, calls SoundElement_PlayFlatSound with 0xE74, and sets the byte at 0x10 of every child in the list at 0x8 whose halfword at 0xE is not 8 to 100, returning zero. Adapted from N64Eng_SetLinkedCommand100WithSound with the two stores to 0x5C and 0x48 replaced by a single store of 2 to 0x54. */

/* Marks a menu's state word at offset 0x54 as 2 when XMath_AbsoluteInteger's value for the fifth argument
   is below Smos_GetControlRepeatLimit's; then, when the fourth argument is one, stores the fourth argument as the state and scrolls down through SmpSlider_IncrementSliderItem. Returns zero. */

extern s32 Smos_GetControlRepeatLimit();

extern void SmpSlider_IncrementSliderItem(struct Scroll *scroll);

extern void SmpSlider_DecrementSliderItem(struct Scroll *scroll);

/* Scrolls a menu one step in the direction its state word at offset 0x54 records: up through
   SmpSlider_DecrementSliderItem for state 0, down through SmpSlider_IncrementSliderItem for state 1, and returns zero. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

s32 SmpList_ResetEntryCommands(struct CommandListMenu *commandListMenu) {
    struct LinkedCommandEntry *p;

    commandListMenu->state = 2;
    SoundElement_PlayFlatSound(3700);
    p = commandListMenu->entries;
    if (p != 0) {
        do {
            if (p->kind != 8) {
                p->command = 100;
            }
            p = p->next;
        } while (p != 0);
    }
    return 0;
}

s32 SmpList_HandleIncrementInput(struct SliderStepRecord *menu, void *second, void *third, s32 active, s32 fifth) {
    if (XMath_AbsoluteInteger(fifth) < Smos_GetControlRepeatLimit()) {
        menu->activeState = 2;
    }
    if (active == 1) {
        menu->activeState = active;
        SmpSlider_IncrementSliderItem(menu);
        return 0;
    }
    return 0;
}

s32 SmpList_HandleDecrementInput(struct SliderStepRecord *menu, void *second, void *third, s32 active, s32 fifth) {
    if (XMath_AbsoluteInteger(fifth) < Smos_GetControlRepeatLimit()) {
        menu->activeState = 2;
    }
    if (active == 1) {
        menu->activeState = 0;
        SmpSlider_DecrementSliderItem(menu);
        return 0;
    }
    return 0;
}

/* Sets the word at offset 0x54 of an object to 2 when the event's upper halfword is 3 and its
   value is 6 or 7, and returns zero. */

s32 SmpList_HandleStopEvent(struct SliderStepRecord *object, void *unused, u32 event, s32 value) {
    if ((event >> 16) == 3 && value < 8 && value >= 6) {
        object->activeState = 2;
    }
    return 0;
}

s32 SmpList_UpdateSliderMotion(struct SliderStepRecord *menu)
{
    struct SliderStepRecord *target = menu;

    switch (menu->activeState) {
    case 0:
        SmpSlider_DecrementSliderItem(menu);
        break;
    case 1:
        SmpSlider_IncrementSliderItem(target);
        break;
    case 2:
        break;
    }
    return 0;
}

s32 SmpList_DestroyController(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}

void SmpList_RegisterListClass(void) {
    SmSmngr_RegisterElementHandlers(2916, g_SmpButton_DispatchListEventAddress, g_SmpButton_DrawListWidgetAddress, 3);
}
