#ifndef OVLGAME_SHAREDRECAT224_H
#define OVLGAME_SHAREDRECAT224_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "OVLGAME/MENU_CONTROLLER_SELECTION_VIEW.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"

struct Holder;

struct ConfirmingControllerStatusView;
typedef struct ConfirmingControllerStatusView ConfirmingControllerStatusView;

struct ConfirmingControllerSettingsView;
typedef struct ConfirmingControllerSettingsView ConfirmingControllerSettingsView;

extern void Confirming_SelectConfirmingController(MenuControllerSelectionView *menuOwner);

struct ConfirmingControllerStatusView;
struct ConfirmingControllerStatusView {
    char pad0[0x148];
    s8 confirmed;
};

struct ConfirmingControllerSettingsView;
struct ConfirmingControllerSettingsView {
    char pad0[0x78];
    s8 controllerSelected;
    char pad79[0x6];
    s8 controllerIndex;
};

extern s32 Player_PlacePlayerForRound(s32 player);
#endif
