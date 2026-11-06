#ifndef AI_CTEAMSELECT_H
#define AI_CTEAMSELECT_H
#include "types.h"
#include "Common/small_records.h"

struct ControllerButtonFlagsView;
struct ControllerButtonFlagsView {
    char pad0[0xB0];
    s32 buttons;
};
typedef struct ControllerButtonFlagsView ControllerButtonFlagsView;

struct ControllerAxesView;
struct ControllerAxesView {
    char pad0[0xC6];
    s8 x;
    s8 y;
};
typedef struct ControllerAxesView ControllerAxesView;

struct Object6C;
struct Object6C {
    char pad[0x6C];
    s32 value;
};

#include "Common/gameplay_camera.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/triple.h"
#include "Menu/teammenu.h"
#include "Cteamselect/player_resetplayerforround_data.h"

struct GameplayCamera;
struct WeaponMenuPlayer {
    char pad[0x5DC];
    struct GameplayCamera *view;
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



struct CBarrel_t;
extern void TeamSelect_DrawWeaponWheel(struct CBarrel_t *menu, s32 unusedArgument, s32 viewPlayer);


extern f32 CTeamSelect_ComputeDirectedAngleStep(f32 currentAngle, f32 targetAngle, s32 turnDirection, f32 approachRate);
void TeamSelect_DrawWeaponWheelSprites(s32 menu, s32 unusedView, s32 player);
struct CBarrel_t;
void TeamSelect_ResetWeaponWheel(struct CBarrel_t *menu);
struct Player;
void TeamSelect_UpdateDraftPanel(CBarrel *wheel, struct Player *player, s32 selectionContext);
s32 TeamSelect_TryCloseWeaponWheel(CBarrel *wheel, struct Player *player);
extern void TeamSelect_EmptyWeaponWheelHook(void *weaponWheelState);

#endif
