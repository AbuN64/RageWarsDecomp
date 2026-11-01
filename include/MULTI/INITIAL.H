#ifndef MULTI_INITIAL_H
#define MULTI_INITIAL_H
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/ITEMRECAT20V1.H"

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
    ControllerPortView *controller;
};
struct TypedMenuVariableView {
    char pad[0x14];
    struct Variable *variable;
};
extern s32 Initial_RequestTransitionWithPakDisabled(void *unused0, ControllerPortOwnerView *dialog);
extern s32 Initial_OpenDialogAfterTimerReset(void *unused0, Arg1Struct *dialog);
extern void Initial_ProbeMenuControllerPak(struct Shared_PakMenu *menu);
extern s32 Initial_OpenDialogWithControllerPak(void *unused0, ControllerPakDialogContext *dialog);
extern void Initial_EnableMenuControllerPak(void *menu);

extern s32 Initial_ReturnSuccess(void);
extern void Initial_SelectInitialController(void *unused0, struct GamePlayerListView *menu);
extern s32 Initial_RequestSessionTransition(void);
#endif
