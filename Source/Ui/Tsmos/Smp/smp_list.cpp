#include "Common/animation.h"
#include "Common/vector4f.h"
#include "Common/menu_screen_elements.h"
#include "Common/rotation_extraction.h"
#include "Common/statepair.h"
#include "Menu/scroll.h"
#include "types.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Menu/smplist_registerlistclass.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/cache_freememory.h"
#include "Ui/smos.h"
#include "Ui/smp_slider.h"

/* Marks the command list menu as dimmed, plays the menu click sound, dims every child of the list except the kind-8 ones, and returns zero. */

/* Marks a menu's state as 2 when XMath_AbsoluteInteger's value for the fifth argument
   is below Smos_GetControlRepeatLimit's; then, when the fourth argument is one, stores the fourth argument as the state and scrolls down through SmpSlider_IncrementSliderItem. Returns zero. */

/* Scrolls a menu one step in the direction its state records: up through
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

/* Sets the active state of an object to 2 when the event's upper halfword is 3 and its
   value is 6 or 7, and returns zero. */

s32 SmpList_HandleStopEvent(struct SliderStepRecord *object, void *eventKind, u32 event, s32 value) {
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
