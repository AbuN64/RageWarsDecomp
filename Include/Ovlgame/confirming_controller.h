#ifndef OVLGAME_CONFIRMING_CONTROLLER_H
#define OVLGAME_CONFIRMING_CONTROLLER_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Ovlgame/menu_controller_selection_view.h"
#include "Common/resident_event_handler.h"
#include "Ai/Player/player_placeplayerforround.h"

struct MenuControllerSelectionView;
struct Holder;

struct ConfirmingControllerStatusView;
typedef struct ConfirmingControllerStatusView ConfirmingControllerStatusView;

struct ConfirmingControllerSettingsView;
typedef struct ConfirmingControllerSettingsView ConfirmingControllerSettingsView;

extern void Confirming_SelectConfirmingController(struct MenuControllerSelectionView *menuOwner);

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


#endif
