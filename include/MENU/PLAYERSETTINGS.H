#ifndef MENU_PLAYERSETTINGS_H
#define MENU_PLAYERSETTINGS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct PlayerSettings;
struct PlayerSettings {
    char pad0[0x78];
    s8 active;
    char pad79[6];
    s8 selected;
    char pad80[150 - 0x80];
};

struct StatusView;
struct StatusView {
    char pad[336];
    s8 active;
};

struct Body;
struct Character;
struct Controller;
struct Controls;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Record;
struct Rider;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;
struct View;
struct PlayerCharacterKindView;

struct MenuCMenuProfileUpdatePlayerAnimationChoice;
struct MenuCMenuProfileUpdatePlayerAnimationChoice {
    char pad[0x1C];
    SharedPlayer *player;
    s32 input;
};



struct PlayerProfileMenuContext;
typedef struct PlayerProfileMenuContext PlayerProfileMenuContext;


struct PlayerProfileMenuContext;
struct PlayerStateDirtyOwnerView;
struct PlayerProfileMenuContext {
    char pad0[0x1C];
    struct PlayerStateDirtyOwnerView *owner;
    PakMenuSlot *widget;
};


struct GameSpeedMenuValue;
struct GameSpeedMenuValue {
    unsigned char padding_0[32];
    int controllerIndex;
};

struct Obj1C;
struct Obj1C {
    char pad0[0x5D4];
    s32 dialogParameter;
    PlayerCharacterKindView *characterKindView;
    s32 dialogParentBase;
    char pad5E0[0x698 - 0x5E0];
    s32 dialogController;
    char pad69C[0x858 - 0x69C];
    s32 alternateDialogFlag;
};

struct PlayerDialogMenuContext;
struct Obj1C;
struct PlayerDialogMenuContext {
    char pad0[0x1C];
    struct Obj1C *selectionPlayer;
};



extern float g_profileGameSpeedWrapLimit;

struct ProfileModeMenuContext;
typedef struct ProfileModeMenuContext ProfileModeMenuContext;

struct PlayerDialogMenuContext;
typedef struct PlayerDialogMenuContext PlayerDialogMenuContext;


struct Shared_PakMenu;

struct PlayerSettings;
typedef struct PlayerSettings PlayerSettings;

struct StatusView;
typedef struct StatusView StatusView;


struct ProfileOptions;
struct ProfileOptions {
    u8 pad0[0x7B];
    s8 profileMode;
};

struct ProfileModeSelectionPlayer;
struct ProfileOptions;
struct ProfileModeSelectionPlayer {
    u8 pad0[0x5D8];
    struct ProfileOptions *characterKindView;
};
struct ProfileModeSelectionPlayer;
struct ProfileModeMenuContext;
struct ProfileModeMenuContext {
    u8 pad0[0x1C];
    struct ProfileModeSelectionPlayer *selectionPlayer;
};

struct StatusStep;
typedef struct StatusStep StatusStep;

struct StatusStep;
struct StatusStep {
    char pad[150];
};

struct Obj1C;
typedef struct Obj1C Obj1C;

struct FlaggedRosterView;
struct FlaggedRosterView {
    char pad0[0x148];
    u8 flag;
};




struct FlaggedRosterView;
typedef struct FlaggedRosterView FlaggedRosterView;

struct MenuCMenuProfileUpdatePlayerAnimationChoice;
typedef struct MenuCMenuProfileUpdatePlayerAnimationChoice MenuCMenuProfileUpdatePlayerAnimationChoice;





struct ProfileOptions;
typedef struct ProfileOptions ProfileOptions;

#endif
