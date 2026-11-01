#ifndef OVLGAME_MENU_CONTROLLER_SELECTION_VIEW_H
#define OVLGAME_MENU_CONTROLLER_SELECTION_VIEW_H
#include "TYPES.H"
struct MenuControllerSelectionView {
    char pad0[0x20];
    s32 * controllerProfile;
};
#endif
