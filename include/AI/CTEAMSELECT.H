#ifndef AI_CTEAMSELECT_H
#define AI_CTEAMSELECT_H
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
#include "MENU/TEAMMENU.H"

struct WeaponMenuPlayer {
    char pad[0x5DC];
    WeaponMenuView *view;
};

typedef struct {
    u8 padding_0[4];
    f32 closeDelay;
    u8 padding_8[884];
    s32 selectedIndex;
} ResetTimerStorage;
typedef struct {
    u8 padding_0[1688];
    void * controller;
} ResetOwnerStorage;
typedef struct {
    u8 padding_0[176];
    s32 buttons;
} ResetFlagsStorage;

typedef struct Shared_MenuItemRecord Shared_MenuItemRecord;
struct Shared_MenuItemRecord {
    s32 index;
    s32 enabled;
    f32 angle;
    s32 image;
    f32 value;
};
typedef struct Shared_MenuItemList Shared_MenuItemList;
struct Shared_MenuItemList {
    u32 unknown00[7];
    Shared_MenuItemRecord records[4];
    s32 selection;
};
extern f32 g_teamWheelInitialSlotScale;

extern void TeamSelect_ResetTeamWheel(TeamMenu *menu);

struct CBarrel_t;
extern void TeamSelect_DrawWeaponWheel(struct CBarrel_t *menu, s32 unusedArgument, s32 viewPlayer);

extern void TeamSelect_ResetWeaponWheel(CBarrel *menu);
extern f32 CTeamSelect_ComputeDirectedAngleStep(f32 currentAngle, f32 targetAngle, s32 turnDirection, f32 approachRate);
#endif
