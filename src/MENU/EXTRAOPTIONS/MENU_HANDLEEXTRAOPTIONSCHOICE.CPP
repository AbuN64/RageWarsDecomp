#include "COMMON/NUMBERPADSCREEN.H"
#include "TYPES.H"
#include "COMMON/SCREEN.H"

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
s32 Menu_HandleExtraOptionsChoice(void) {
    MarkMenuEventHandled();
    if (g_extraOptionsScreen->open == 0) {
        Menu_ShowExtraOptionsPanel();
    } else {
        switch (Menu_GetFocusedElementId()) {
        case 940:
            SmpSlider_SetTransitionMode(g_extraOptionsScreen->dialog, 2);
            Menu_ApplyExtraOptionFlags();
            break;
        case 950:
            Menu_OpenOptionsKeypad();
            break;
        }
    }
    return 0;
}
#endif
