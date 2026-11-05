#ifndef MULTI_INITIAL_H
#define MULTI_INITIAL_H
#include "Menu/built_menu.h"
#include "Common/player_item_inventory.h"

struct Arg1Struct;
struct ControllerPakDialogContext;
struct ControllerPortOwnerView;
struct ControllerPortView;
struct HolderMultiIsPlayerItemAvailable {
    char pad[0x1C];
    struct PlayerItemInventoryView *player;
    char pad20[0x30 - 0x20];
    f32 fade;
    f32 alpha;
};
struct MultiplayerAvailabilityItem {
    s16 availability;
    u8 pad2[10];
    struct Flagged *widget;
};
struct MultiplayerItemAvailabilityView {
    char pad[0x14];
    s32 resource;
    struct ItemDef *def;
};
struct ControllerPakDialogContext {
    u8 pad0[0x1C];
    s32 player;
    struct ControllerPortView *controller;
};
struct TypedMenuVariableView {
    char pad[0x14];
    struct Variable *variable;
};
extern s32 Initial_RequestTransitionWithPakDisabled(void *owner, struct ControllerPortOwnerView *dialog);
extern s32 Initial_OpenDialogAfterTimerReset(void *owner, struct Arg1Struct *dialog);
extern void Initial_ProbeMenuControllerPak(struct Shared_PakMenu *menu);
extern s32 Initial_OpenDialogWithControllerPak(void *owner, struct ControllerPakDialogContext *dialog);
extern void Initial_EnableMenuControllerPak(void *menu);

extern s32 Initial_ReturnSuccess(void);
extern void Initial_SelectInitialController(void *owner, struct MenuBuildState *menu);
extern s32 Initial_RequestSessionTransition(void);
struct Part {
    char pad[0x78];
    u8 active;
};

#endif
