#ifndef MENU_TEAMMENU_H
#define MENU_TEAMMENU_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct TeamMenu;
typedef struct TeamMenu TeamMenu;

extern float g_weaponWheelPositiveAnglePeriod;

extern float g_teamMenuFloatConstantDe;

struct Shared_ActorView;

/* The weapon barrel (wheel) menu: CBarrel_t and CBarrelWeapon_t of the debug catalog. */
typedef struct CBarrelWeapon_t {
    s32 m_Weapon;
    void *m_pInfo;
    s32 m_bEnabled;
    f32 m_Rot;
    f32 m_Spin;
    f32 m_Scale;
} CBarrelWeapon;
typedef struct CBarrel_t {
    s32 m_Mode;
    f32 m_Time;
    f32 m_Alpha;
    f32 m_Rot;
    s32 m_Dir;
    f32 m_Glow;
    s32 CurrentWeaponListSize;
    CBarrelWeapon m_WeaponList[36];
    s32 m_Selected;
    s32 m_QuickSelect;
    s32 m_ButtonAWheel;
    s32 m_DisplaySlot;
    s32 m_UnderwaterWhenSetup;
    s32 m_WheelIndexLastFrame;
} CBarrel;

extern float g_weaponWheelNegativeAnglePeriod;

struct Item;
typedef struct Item Item;

struct TeamMenuSlotView;
typedef struct TeamMenuSlotView TeamMenuSlotView;


struct Entry;
typedef struct Entry Entry;

struct TeamMenuPlayerControllerView;
typedef struct TeamMenuPlayerControllerView TeamMenuPlayerControllerView;

struct MenuCteamselectDrawTeamWheel;
typedef struct MenuCteamselectDrawTeamWheel MenuCteamselectDrawTeamWheel;

struct ControllerAxesView;
struct TeamMenuPlayerControllerView;
struct TeamMenuPlayerControllerView {
    char pad0[0x698];
    struct ControllerAxesView *controller;
};

struct TeamWeaponRuntimePlayerView;
struct TeamWeaponRuntimePlayerView {
    char pad0[0x5D8];
    char * options;
    char pad5D8[0x670 - 0x5D8 - sizeof(char*)];
    f32 shieldDuration;
    char pad670[0x698 - 0x670 - sizeof(f32)];
    char * controller;
    char pad698[0x11B4 - 0x698 - sizeof(char*)];
    s32 locked;
    char pad11B4[0x11B8 - 0x11B4 - sizeof(s32)];
    s32 lockState;
};

struct TeamMenuIconView;
typedef struct TeamMenuIconView TeamMenuIconView;


struct Item;
struct Item {
    s32 slot;
    s32 weapon;
    CVector3 position;
    s32 icon;
    f32 width;
    f32 height;
};

struct TeamMenuSlotView;
struct TeamMenuSlotView {
    s32 team;
    s32 unused;
    f32 angle;
    s32 unused2;
    f32 scale;
};

struct TeamMenu {
    s32 state;
    s32 unused;
    f32 open;
    s32 reset;
    u8 reserved10[4];
    f32 spin;
    s32 count;
    TeamMenuSlotView slots[4];
    s32 cursor;
    s32 hover;
};

struct TeamWeaponRuntimePlayerView;
typedef struct TeamWeaponRuntimePlayerView TeamWeaponRuntimePlayerView;

struct TeamMenuSelectionPairView;
struct TeamMenuSelectionPairView {
    char pad0[0x6C];
    s32 cursor;
    char pad6C[0x70 - 0x6C - sizeof(s32)];
    s32 hover;
};

struct Entry34;
struct Entry34 {
    char pad0[0x1C];
    s32 weapon;
    void *info;
    s32 owned;
    f32 x;
    s32 y;
    f32 z;
};


struct TeamMenuSelectionPairView;
typedef struct TeamMenuSelectionPairView TeamMenuSelectionPairView;


struct TeamMenuPlayerLinksView;
typedef struct TeamMenuPlayerLinksView TeamMenuPlayerLinksView;

struct Entry;
struct Entry {
    char pad0[0x1E];
    u16 team;
    s32 enabled;
};

struct Entry34;
typedef struct Entry34 Entry34;


struct TeamMenuIconView;
struct TeamMenuIconView {
    s32 slot;
    CVector3 position;
    s32 icon;
    f32 width;
    f32 height;
};

struct TeamMenuPlayerLinksView;
struct TeamMenuPlayerLinksView {
    unsigned char padding_0[1496];
    void *options;
    unsigned char padding_5DC[188];
    void *controller;
};

extern float g_barrelEffectSoundMaximumPitch;

extern float g_weaponWheelResetAngleStep;

struct Body;
struct Character;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Record;
struct Rider;
struct Settings;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;
struct View;
struct ControllerButtonFlagsView;

extern float g_barrelApproachClearance;

extern float g_teamWheelPlayerShieldDuration;

struct TeamWeaponSelectionPlayerView;
struct TeamWeaponSelectionPlayerView {
    char pad0[0x38];
    s32 flags;
    char pad38[0x5D8 - 0x38 - sizeof(s32)];
    char * options;
    char pad5D8[0x62E - 0x5D8 - sizeof(char*)];
    s16 selectedWeapon;
    char pad62E[0x698 - 0x62E - sizeof(s16)];
    char * controller;
    char pad698[0x770 - 0x698 - sizeof(char*)];
    s16 requestedWeapon;
    char pad770[0xCC0 - 0x770 - sizeof(s16)];
    s32 pendingWeapon;
    char padCC0[0x11B4 - 0xCC0 - sizeof(s32)];
    s32 locked;
};


struct TeamWeaponSelectionPlayerView;
typedef struct TeamWeaponSelectionPlayerView TeamWeaponSelectionPlayerView;

struct MenuCteamselectDrawTeamWheel;
struct MenuCteamselectDrawTeamWheel {
    s32 active;
    s32 unused;
    f32 open;
    char padC[0x10];
    TeamMenuSlotView slots[4];
    s32 cursor;
};

typedef struct StickInput { char pad00[0xC6]; s8 x, y; } StickInput;
typedef struct StickPlayer { char pad00[0x698]; StickInput *input; } StickPlayer;

extern char s_selectTeamText[];

struct TeamWeaponPlayer;
typedef struct TeamWeaponPlayer TeamWeaponPlayer;
extern void TeamSelect_InitWeaponChoices(CBarrel *barrel, s32 buttonAWheel, TeamWeaponPlayer *player);

extern void SoundElement_StopAudioBySecondaryValue(s32);
#endif
