#ifndef COMMON_VECTOR4F_H
#define COMMON_VECTOR4F_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MTX.H"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
#define RW_LOCALIZED_TEXT(fixed, eu_table, eu_x_table, language) ((eu_x_table)[language])
#else
#define RW_LOCALIZED_TEXT(fixed, eu_table, eu_x_table, language) ((eu_table)[language])
#endif
#else
#define RW_LOCALIZED_TEXT(fixed, eu_table, eu_x_table, language) (fixed)
#endif



struct CQuatern_t;
typedef struct CQuatern_t CQuatern;

struct CQuatern_t;
struct CQuatern_t {
    float x;
    float y;
    float z;
    float w;
};

struct PlayerWeaponStateView;
struct PlayerWeaponStateView {
    char pad0[0x650];
    s16 action;
};

struct CompactOptionsPageView;
struct CompactOptionsPageView {
    char pad0[0xC];
    s32 flagWord;
};

struct Hook;
struct Hook {
    char pad[8];
    void (*fn)(void *, void *);
};

struct Hook;
typedef struct Hook Hook;




struct ActorLinkedControllerView;
struct ActorLinkedControllerView {
    char pad[0x1D8];
    int link;
};

struct ActorLinkedControllerView;
typedef struct ActorLinkedControllerView ActorLinkedControllerView;

struct WeaponGlobalRuntimeView;
struct WeaponGlobalRuntimeView {
    int classMode;
};



struct NavigationNodeCostView;
typedef struct NavigationNodeCostView NavigationNodeCostView;

struct SharedPlayer;

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
struct TurretRiderTargetView;
struct Settings;
struct SharedPlayer;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;
struct View;
struct SharedPlayer {
    union {
        struct {
            u8 reservedBytes[24];
        } view0_0;
        struct {
            u8 pad0[24];
        } view0_1;
        struct {
            char pad[0x3];
            u8 team;
        } view3_2;
        struct {
            char pad[0x8];
            CVector3 position;
        } view8_2;
        struct {
            char pad[0x8];
            CVector3 pos;
        } view8_3;
        struct {
            char pad[0x8];
            CVector3 position;
        } view8_4;
        struct {
            char pad[0x14];
            struct Shared_Model * model;
        } view14_6;
        struct { char pad[8]; s32 positionWords[3]; } positionBits;
    } views0;
    union {
        struct {
            char * track;
        } view18_0;
        struct {
            char * track;
        } view18_1;
        struct NavigationTrack *navigationTrack;
        struct {
            struct Model * model;
        } view18_2;
        struct {
            struct Body * body;
        } view18_3;
        struct {
            struct Character * character;
        } view18_4;
        struct {
            struct Shared_Body * body;
        } view18_5;
    } views18;
    union {
        struct {
            union { u8 reservedBytes1C[344]; CVector3 localDisplacement; };
        } view1C_0;
        struct {
            u8 pad1[344];
        } view1C_1;
        struct {
            char pad[0x4];
            f32 velY;
        } view20_2;
        struct {
            char pad[0x1C];
            s32 flags;
        } view38_2;
        struct {
            char pad[0x1C];
            s32 flags;
        } view38_3;
        struct {
            char pad[0x24];
            f32 emitterFloat;
        } view40_5;
        struct {
            char pad[0x40];
            Shared_Quad emitterQuad;
        } view5C_6;
        struct {
            char pad[0x50];
            f32 heading;
        } view6C_4;
        struct {
            char pad[0x50];
            f32 heading;
        } view6C_5;
        struct {
            char pad[0x50];
            f32 yaw;
        } view6C_9;
        struct {
            char pad[0xC8];
            u16 kind;
        } viewE4_6;
        struct {
            char pad[0xC8];
            u16 kind;
        } viewE4_7;
        struct {
            char pad[0xE4];
            s32 flags;
        } view100_8;
        struct {
            char pad[0xE4];
            s32 flags;
        } view100_9;
        struct {
            char pad[0xE8];
            f32 idleTime;
        } view104_10;
        struct {
            char pad[0xE8];
            f32 idleTime;
        } view104_11;
        struct {
            char pad[0xEC];
            s16 anim;
        } view108_16;
        struct {
            char pad[0xF2];
            s8 reservedByte10E;
        } view10E_12;
        struct {
            char pad[0xF2];
            s8 idle;
        } view10E_13;
        struct {
            char pad[0xF2];
            s8 replaying;
        } view10E_14;
        struct {
            char pad[0xF2];
            s8 animPending;
        } view10E_20;
        struct {
            char pad[0x154];
            char body[100];
        } view170_15;
        struct {
            char pad[0x154];
            char body[100];
        } view170_16;
        struct {
            char pad[0x154];
            s32 actorBody;
        } view170_23;
        struct {
            char pad[0x158];
            s32 bodyHealth;
        } view174_17;
        struct {
            char pad[0x15C];
            u8 reservedBytes[740];
        } view178_18;
        struct {
            char pad[0x15C];
            u8 pad2[740];
        } view178_19;
        struct {
            char pad[0x1B8];
            f32 holdTime;
        } view1D4_20;
        struct {
            char pad[0x1B8];
            f32 holdTime;
        } view1D4_21;
        struct {
            char pad[0x1BC];
            struct SharedPlayer * self;
        } view1D8_22;
        struct {
            char pad[0x1BC];
            struct SharedPlayer * self;
        } view1D8_23;
        struct {
            char pad[0x1BC];
            struct SharedPlayer * self;
        } view1D8_24;
        struct {
            char pad[0x1BC];
            void * self;
        } view1D8_32;
        struct {
            char pad[0x244];
            CVector3 muzzle;
        } view260_25;
        struct {
            char pad[0x244];
            CVector3 muzzle;
        } view260_26;
        struct {
            char pad[0x2CC];
            char weapon[368];
        } view2E8_27;
        struct {
            char pad[0x2CC];
            char weapon[368];
        } view2E8_28;
        struct {
            char pad[0x2CC];
            Shared_Emitter emitter;
        } view2E8_37;
        struct {
            char pad[0x43C];
            char ammo[384];
        } view458_29;
        struct {
            char pad[0x43C];
            char ammo[384];
        } view458_30;
        struct {
            char pad[0x43C];
            s32 weaponSelectionContext;
        } view458_40;
        struct {
            char pad[0x440];
            s32 mirroredHealth;
        } view45C_31;
        struct {
            char pad[0x444];
            u8 reservedBytes460[376];
        } view460_32;
        struct {
            char pad[0x444];
            u8 pad3[376];
        } view460_33;
        struct {
            char pad[0x468];
            struct Shared_Voice * voice;
        } view484_44;
        struct {
            char pad[0x470];
            s8 state;
        } view48C_34;
        struct {
            char pad[0x470];
            s8 state;
        } view48C_35;
        struct {
            char pad[0x4A4];
            void * self;
        } view4C0_47;
        struct {
            char pad[0x507];
            s8 busy;
        } view523_36;
        struct {
            char pad[0x507];
            s8 busy;
        } view523_37;
        struct {
            char pad[0x578];
            s32 reservedWord;
        } view594_38;
        struct {
            char pad[0x578];
            s32 gear;
        } view594_39;
        struct {
            char pad[0x578];
            s32 mode;
        } view594_40;
        struct {
            char pad[0x584];
            f32 charge;
        } view5A0_41;
        struct {
            char pad[0x584];
            f32 charge;
        } view5A0_42;
        struct {
            char pad[0x5B4];
            s32 controlKind;
        } view5D0_43;
        struct {
            char pad[0x5B4];
            s32 f5D0;
        } view5D0_44;
        struct {
            char pad[0x5B8];
            s32 playerIndex;
        } view5D4_45;
        struct {
            char pad[0x5B8];
            s32 slot;
        } view5D4_46;
        struct {
            char pad[0x5B8];
            s32 profile;
        } view5D4_47;
        struct {
            char pad[0x5B8];
            s32 f5D4;
        } view5D4_48;
    } views1C;
    union {
        struct {
            struct Record * record;
        } view5D8_0;
        struct {
            struct Record * record;
        } view5D8_1;
        struct {
            struct Controls * controls;
        } view5D8_2;
        struct {
            struct TeamInfo * teamInfo;
        } view5D8_3;
        struct {
            struct Ctrl * ctrl;
        } view5D8_4;
        struct {
            unsigned char * info;
        } view5D8_5;
        struct {
            struct Profile * profile;
        } view5D8_6;
        struct {
            struct Settings * settings;
        } view5D8_7;
        struct {
            s32 f5D8;
        } view5D8_8;
        struct {
            struct Shared_Profile * profile;
        } view5D8_9;
    } views5D8;
    union {
        struct {
            void * messageCamera;
        } view5DC_0;
        struct {
            void * view;
        } view5DC_1;
        struct {
            struct View * view;
        } view5DC_2;
        struct {
            u8 pad4[8];
        } view5DC_3;
        struct {
            void * entity;
        } view5DC_4;
        struct {
            struct TurretRiderTargetView * rider;
        } view5DC_5;
        struct {
            char * storage;
        } view5DC_6;
        struct {
            char * messages;
        } view5DC_7;
        struct {
            struct Shared_Hud * hud;
        } view5DC_8;
        struct {
            char pad[0x4];
            s32 reservedWord1;
        } view5E0_8;
        struct {
            char pad[0x4];
            s32 state;
        } view5E0_9;
        struct {
            char pad[0x4];
            s32 slot;
        } view5E0_10;
    } views5DC;
    union {
        struct {
            s32 health;
        } view5E4_0;
        struct {
            s32 active;
        } view5E4_1;
        struct {
            s32 health;
        } view5E4_2;
        struct {
            s32 alive;
        } view5E4_3;
        struct {
            s32 holding;
        } view5E4_4;
    } views5E4;
    union {
        struct {
            u8 reservedBytes1[3140];
        } view5E8_0;
        struct {
            u8 pad5[3140];
        } view5E8_1;
        struct {
            char pad[0x2];
            s16 moveEnabled;
        } view5EA_2;
        struct {
            char pad[0x2];
            s16 respawns;
        } view5EA_3;
        struct {
            char pad[0x2];
            s16 runType;
        } view5EA_4;
        struct {
            char pad[0x4];
            s32 currentItem;
        } view5EC_5;
        struct {
            char pad[0x4];
            s32 model;
        } view5EC_6;
        struct {
            char pad[0x4];
            s32 spawnPoint;
        } view5EC_7;
        struct {
            char pad[0x4];
            s32 f5EC;
        } view5EC_8;
        struct {
            char pad[0x8];
            s32 pendingItem;
        } view5F0_9;
        struct {
            char pad[0x8];
            s32 f5F0;
        } view5F0_10;
        struct {
            char pad[0xC];
            s16 ammo[4];
        } view5F4_11;
        struct {
            char pad[0xC];
            s16 ammo[4];
        } view5F4_12;
        struct {
            char pad[0xC];
            s16 ammo[3];
        } view5F4_13;
        struct {
            char pad[0x1A];
            Shared_Slot slots[22];
        } view602_14;
        struct {
            char pad[0x46];
            s16 selectedWeapon;
        } view62E_13;
        struct {
            char pad[0x46];
            s16 weapon;
        } view62E_14;
        struct {
            char pad[0x46];
            s16 character;
        } view62E_17;
        struct {
            char pad[0x68];
            s16 actionState;
        } view650_15;
        struct {
            char pad[0x68];
            s16 state;
        } view650_16;
        struct {
            char pad[0x68];
            s16 action;
        } view650_17;
        struct {
            char pad[0x68];
            s16 mode;
        } view650_18;
        struct {
            char pad[0x6A];
            s16 previous;
        } view652_19;
        struct {
            char pad[0x6A];
            s16 previous;
        } view652_20;
        struct {
            char pad[0x6A];
            s16 pad652;
        } view652_24;
        struct {
            char pad[0x6C];
            s16 prevState;
        } view654_25;
        struct {
            char pad[0x6E];
            s16 pad656;
        } view656_26;
        struct {
            char pad[0x70];
            f32 reservedFloat;
        } view658_21;
        struct {
            char pad[0x70];
            f32 counter;
        } view658_22;
        struct {
            char pad[0x70];
            f32 stride;
        } view658_23;
        struct {
            char pad[0x70];
            f32 swimTime;
        } view658_24;
        struct {
            char pad[0x70];
            f32 stateTime;
        } view658_31;
        struct {
            char pad[0x74];
            s32 savedStateTimer;
        } view65C_32;
        struct {
            char pad[0x78];
            s32 previousTimer;
        } view660_25;
        struct {
            char pad[0x78];
            s32 previousTimer;
        } view660_26;
        struct {
            char pad[0x7C];
            s32 timer;
        } view664_27;
        struct {
            char pad[0x7C];
            s32 timer;
        } view664_28;
        struct {
            char pad[0x84];
            f32 movementTimeScale;
        } view66C_29;
        struct {
            char pad[0x88];
            f32 shield;
        } view670_30;
        struct {
            char pad[0x88];
            f32 shield;
        } view670_31;
        struct {
            char pad[0x90];
            f32 powerupCountdown;
        } view678_40;
        struct {
            char pad[0xA0];
            char body[16];
        } view688_32;
        struct {
            char pad[0xA0];
            char body[16];
        } view688_33;
        struct {
            char pad[0xA0];
            Shared_Input input;
        } view688_43;
        struct {
            char pad[0xB0];
            struct Controller * controller;
        } view698_34;
        struct {
            char pad[0xB0];
            struct Controller * controller;
        } view698_35;
        struct {
            char pad[0xB0];
            void * controller;
        } view698_36;
        struct {
            char pad[0xB0];
            char * emitter;
        } view698_37;
        struct {
            char pad[0xB0];
            char * title;
        } view698_38;
        struct {
            char pad[0xB4];
            f32 stick;
            f32 pitchInput; /* +0x6A0: Player_UpdateSwimmingState */
        } view69C_39;
        struct {
            char pad[0xB4];
            f32 stick;
        } view69C_40;
        struct {
            char pad[0xBC];
            f32 strafe;
        } view6A4_41;
        struct {
            char pad[0xBC];
            f32 strafe;
        } view6A4_42;
        struct {
            char pad[0xC0];
            f32 lift;
        } view6A8_43;
        struct {
            char pad[0xC0];
            f32 lift;
        } view6A8_44;
        struct {
            char pad[0xC4];
            s32 inputFlags;
        } view6AC_45;
        struct {
            char pad[0xC8];
            s32 actionFlags;
        } view6B0_46;
        struct {
            char pad[0xC8];
            s32 input;
        } view6B0_47;
        struct {
            char pad[0xC8];
            s32 state;
        } view6B0_48;
        struct {
            char pad[0xD0];
            s32 input;
        } view6B8_49;
        struct {
            char pad[0xD0];
            s32 input;
        } view6B8_50;
        struct {
            char pad[0xD8];
            f32 movementSpeed;
        } view6C0_51;
        struct {
            char pad[0xD8];
            f32 climb;
        } view6C0_52;
        struct {
            char pad[0xD8];
            f32 speed;
        } view6C0_53;
        struct {
            char pad[0xD8];
            f32 velX;
        } view6C0_64;
        struct {
            char pad[0xDC];
            f32 sideSpeed;
        } view6C4_54;
        struct {
            char pad[0xDC];
            f32 side;
        } view6C4_55;
        struct {
            char pad[0xDC];
            f32 velZ;
        } view6C4_67;
        struct {
            char pad[0xE0];
            f32 speed;
        } view6C8_56;
        struct {
            char pad[0xE0];
            f32 speed;
        } view6C8_57;
        struct {
            char pad[0xE4];
            f32 lastVelY;
        } view6CC_70;
        struct {
            char pad[0xE8];
            s32 onGround;
        } view6D0_71;
        struct {
            char pad[0xEC];
            f32 forwardBoostSpeed;
        } view6D4_58;
        struct {
            char pad[0xF0];
            f32 boostStrength;
        } view6D8_59;
        struct {
            char pad[0xF4];
            f32 boostCooldown;
            f32 strideSign; /* +0x6E0: Player_UpdateSwimmingState */
        } view6DC_60;
        struct {
            char pad[0xFC];
            f32 jumpDelay;
        } view6E4_61;
        struct {
            char pad[0xFC];
            f32 depth;
        } view6E4_62;
        struct {
            char pad[0xFC];
            f32 airTime;
        } view6E4_77;
        struct {
            char pad[0x100];
            f32 movementX;
        } view6E8_63;
        struct {
            char pad[0x100];
            CVector3 movementPosition;
        } view6E8_79;
        struct {
            char pad[0x104];
            f32 height;
        } view6EC_64;
        struct {
            char pad[0x104];
            f32 height;
        } view6EC_65;
        struct {
            char pad[0x108];
            f32 movementZ;
        } view6F0_66;
        struct {
            char pad[0x10C];
            f32 heightDelta;
        } view6F4_83;
        struct {
            char pad[0x110];
            CVector3 previousTargetPosition;
        } view6F8_84;
        struct {
            char pad[0x11C];
            f32 lift;
            f32 viewPitch; /* +0x708: Player_BuildPlayerViewTransform */
        } view704_67;
        struct {
            char pad[0x11C];
            f32 lift;
        } view704_68;
        struct {
            char pad[0x130];
            f32 crouch;
        } view718_69;
        struct {
            char pad[0x130];
            f32 crouch;
        } view718_70;
        struct {
            char pad[0x134];
            s32 forceCrouch;
        } view71C_89;
        struct {
            char pad[0x138];
            f32 swim;
        } view720_90;
        struct {
            char pad[0x13C];
            f32 pitch;
        } view724_71;
        struct {
            char pad[0x13C];
            f32 pitch;
        } view724_72;
        struct {
            char pad[0x140];
            f32 kickPitch;
        } view728_73;
        struct {
            char pad[0x140];
            f32 kickPitch;
        } view728_74;
        struct {
            char pad[0x144];
            f32 strideRoll;
        } view72C_75;
        struct {
            char pad[0x144];
            f32 kickRoll;
        } view72C_76;
        struct {
            char pad[0x144];
            f32 lean;
        } view72C_77;
        struct {
            char pad[0x148];
            f32 sway[3];
        } view730_78;
        struct {
            char pad[0x148];
            f32 sway[3];
        } view730_79;
        struct {
            char pad[0x154];
            f32 side;
        } view73C_80;
        struct {
            char pad[0x154];
            f32 side;
        } view73C_81;
        struct {
            char pad[0x154];
            CVector3 weapon;
        } view73C_82;
        struct {
            char pad[0x158];
            f32 height;
        } view740_83;
        struct {
            char pad[0x158];
            f32 height;
        } view740_84;
        struct {
            char pad[0x15C];
            f32 forward;
        } view744_85;
        struct {
            char pad[0x15C];
            f32 forward;
        } view744_86;
        struct {
            char pad[0x170];
            f32 bobStrength;
        } view758_87;
        struct {
            char pad[0x170];
            f32 bobStrength;
        } view758_88;
        struct {
            char pad[0x174];
            f32 bobSpeed;
        } view75C_89;
        struct {
            char pad[0x174];
            f32 bobSpeed;
        } view75C_90;
        struct {
            char pad[0x188];
            s16 requestedWeapon;
        } view770_91;
        struct {
            char pad[0x188];
            s16 nextWeapon;
        } view770_92;
        struct {
            char pad[0x188];
            s16 weapon;
        } view770_113;
        struct {
            char pad[0x18A];
            s16 pad772;
        } view772_114;
        struct {
            char pad[0x18C];
            CVector3 requestedPosition;
        } view774_115;
        struct {
            char pad[0x198];
            f32 cameraHeightOffset;
        } view780_116;
        struct {
            char pad[0x19C];
            f32 movementRate;
        } view784_117;
        struct {
            char pad[0x1A0];
            s32 icons;
        } view788_93;
        struct {
            char pad[0x1A0];
            s32 icons;
        } view788_94;
        struct {
            char pad[0x1B0];
            s32 carried;
        } view798_95;
        struct {
            char pad[0x1B0];
            s32 carried;
        } view798_96;
        struct {
            char pad[0x1B4];
            CVector3 carriedPosition;
        } view79C_97;
        struct {
            char pad[0x1B4];
            CVector3 carriedPosition;
        } view79C_98;
        struct {
            char pad[0x1D0];
            s32 target;
        } view7B8_99;
        struct {
            char pad[0x1D0];
            s32 target;
        } view7B8_100;
        struct {
            char pad[0x1D4];
            f32 timer;
        } view7BC_101;
        struct {
            char pad[0x1D4];
            f32 timer;
        } view7BC_102;
        struct {
            char pad[0x1D8];
            CVector3 targetPosition;
        } view7C0_103;
        struct {
            char pad[0x1D8];
            CVector3 targetPosition;
        } view7C0_104;
        struct {
            char pad[0x200];
            s32 zoomed;
        } view7E8_105;
        struct {
            char pad[0x200];
            s32 zoomed;
        } view7E8_106;
        struct {
            char pad[0x204];
            f32 smoothedZoom;
        } view7EC_132;
        struct {
            char pad[0x208];
            f32 targetZoom;
        } view7F0_133;
        struct {
            char pad[0x224];
            struct Mount * mount;
        } view80C_107;
        struct {
            char pad[0x224];
            struct Mount * mount;
        } view80C_108;
        struct {
            char pad[0x228];
            s32 kind;
        } view810_109;
        struct {
            char pad[0x228];
            s32 kind;
        } view810_110;
        struct {
            char pad[0x22C];
            Triple offset;
        } view814_111;
        struct {
            char pad[0x22C];
            Triple offset;
        } view814_112;
        struct {
            char pad[0x250];
            f32 rideTime;
        } view838_113;
        struct {
            char pad[0x250];
            f32 rideTime;
        } view838_114;
        struct {
            char pad[0x254];
            f32 bump;
        } view83C_115;
        struct {
            char pad[0x254];
            f32 bump;
        } view83C_116;
        struct {
            char pad[0x258];
            s32 surfaced;
        } view840_117;
        struct {
            char pad[0x258];
            s32 surfaced;
        } view840_118;
        struct {
            char pad[0x264];
            s32 periodicTick;
        } view84C_149;
        struct {
            char pad[0x26C];
            f32 effectCountdown;
        } view854_147;
        struct {
            char pad[0x274];
            s32 reservedWord2;
        } view85C_119;
        struct {
            char pad[0x274];
            s32 w85C;
        } view85C_120;
        struct {
            char pad[0x27C];
            s32 reservedWord3;
        } view864_121;
        struct {
            char pad[0x27C];
            s32 f864;
        } view864_122;
        struct {
            char pad[0x280];
            s32 reservedWord4;
        } view868_123;
        struct {
            char pad[0x280];
            s32 f868;
        } view868_124;
        struct {
            char pad[0x284];
            s32 animationId;
        } view86C_125;
        struct {
            char pad[0x284];
            s32 parameter;
        } view86C_126;
        struct {
            char pad[0x284];
            s32 animation;
        } view86C_127;
        struct {
            char pad[0x288];
            s32 previousAnimationId;
        } view870_157;
        struct {
            char pad[0x290];
            Shared_Effect effect;
        } view878_158;
        struct {
            char pad[0x350];
            char strokes[2188];
        } view938_128;
        struct {
            char pad[0x350];
            char strokes[2188];
        } view938_129;
        struct {
            char pad[0x350];
            char strokes[2188];
        } view938_130;
        struct {
            char pad[0x350];
            s32 weaponWheel;
        } view938_162;
        struct {
            char pad[0x6D0];
            s32 weaponLocked;
        } viewCB8_163;
        struct {
            char pad[0x6E4];
            s32 teamWheel;
        } viewCCC_164;
        struct {
            char pad[0x758];
            s32 toggleMenu;
        } viewD40_165;
        struct {
            char pad[0x96C];
            s32 selection;
        } viewF54_131;
        struct {
            char pad[0x96C];
            s32 selection;
        } viewF54_132;
        struct {
            char pad[0x9A8];
            s32 choice;
        } viewF90_133;
        struct {
            char pad[0x9A8];
            s32 choice;
        } viewF90_134;
        struct {
            char pad[0xBCC];
            s32 locked;
        } view11B4_135;
        struct {
            char pad[0xBCC];
            s32 locked;
        } view11B4_136;
        struct {
            char pad[0xBD0];
            s32 frozen;
        } view11B8_137;
        struct {
            char pad[0xBD0];
            s32 frozen;
        } view11B8_138;
        struct {
            char pad[0xBD4];
            s32 reservedWord5;
        } view11BC_139;
        struct {
            char pad[0xBD4];
            s32 f11BC;
        } view11BC_140;
        struct {
            char pad[0xBD8];
            s32 reservedWord6;
        } view11C0_141;
        struct {
            char pad[0xBD8];
            s32 f11C0;
        } view11C0_142;
        struct {
            char pad[0xBDC];
            f32 soundTime;
        } view11C4_143;
        struct {
            char pad[0xBDC];
            f32 soundTime;
        } view11C4_144;
        struct {
            char pad[0xBE4];
            s32 reservedWord7;
        } view11CC_145;
        struct {
            char pad[0xBE4];
            s32 f11CC;
        } view11CC_146;
        struct {
            char pad[0xBF0];
            f32 jumpCooldown;
        } view11D8_147;
        struct {
            char pad[0xBF0];
            f32 recoil;
        } view11D8_148;
        struct {
            char pad[0xBF0];
            f32 stun;
        } view11D8_149;
        struct {
            char pad[0xBF4];
            f32 timeScaleCountdown;
        } view11DC_185;
        struct {
            char pad[0xBF8];
            f32 timeScale;
        } view11E0_186;
        struct {
            char pad[0xC00];
            s32 reservedWord8;
        } view11E8_150;
        struct {
            char pad[0xC00];
            s32 f11E8;
        } view11E8_151;
        struct {
            char pad[0xC04];
            f32 glowDuration;
        } view11EC_189;
        struct {
            char pad[0xC28];
            s32 marker;
        } view1210_152;
        struct {
            char pad[0xC28];
            s32 marker;
        } view1210_153;
        struct {
            char pad[0xC2C];
            s32 markerState;
        } view1214_154;
        struct {
            char pad[0xC2C];
            s32 marker;
        } view1214_155;
        struct {
            char pad[0xC2C];
            s32 markerShown;
        } view1214_156;
        struct {
            char pad[0xC30];
            s32 reservedWord1218;
        } view1218_157;
        struct {
            char pad[0xC30];
            s32 f1218;
        } view1218_158;
        struct {
            char pad[0xC34];
            s32 reservedWord9;
        } view121C_159;
        struct {
            char pad[0xC34];
            s32 f121C;
        } view121C_160;
        struct {
            char pad[0xC38];
            s32 reservedWord10;
        } view1220_161;
        struct {
            char pad[0xC38];
            s32 f1220;
        } view1220_162;
        struct { char pad[0xE]; s16 charge; } chargeView;
        struct { char pad[0x11F4 - 0x5E8]; f32 spin; s32 frame; } rapidFireView;
    } views5E8;
    union {
        struct {
            u32 flags;
        } view122C_0;
        struct {
            u32 flags;
        } view122C_1;
        struct {
            s32 options;
        } view122C_2;
        struct {
            s32 f122C;
        } view122C_3;
        struct {
            s32 fxFlags;
        } view122C_4;
    } views122C;
    f32 fxTime;
    f32 fxSpeed;
    s32 fxStage;
    char pad123C[0x4];
    f32 fxLevel;
    f32 rightAxisValue;
    char pad1248[0x7C];
    union {
        struct {
            s32 reservedWord12C4;
        } view12C4_0;
        struct {
            s32 f12C4;
        } view12C4_1;
    } views12C4;
    union {
        struct {
            s32 reservedWord12C8;
        } view12C8_0;
        struct {
            s32 f12C8;
        } view12C8_1;
    } views12C8;
    union {
        struct {
            s32 splitsA[8];
        } view12CC_0;
        struct {
            s32 splitsA[8];
        } view12CC_1;
    } views12CC;
    s32 reservedWord12EC;
    char pad12F0[0x4];
    union {
        struct {
            s32 splitsB[8];
        } view12F4_0;
        struct {
            s32 splitsB[8];
        } view12F4_1;
    } views12F4;
    char pad1314[0x20];
    union {
        struct {
            s32 reservedWord11;
        } view1334_0;
        struct {
            s32 f1334;
        } view1334_1;
    } views1334;
    union {
        struct {
            s32 reservedWord12;
        } view1338_0;
        struct {
            s32 f1338;
        } view1338_1;
    } views1338;
    union {
        struct {
            s32 reservedWord13;
        } view133C_0;
        struct {
            s32 laps;
        } view133C_1;
        struct {
            s32 lives;
        } view133C_2;
    } views133C;
    union {
        struct {
            s32 reservedWord14;
        } view1340_0;
        struct {
            s32 stalls;
        } view1340_1;
        struct {
            s32 timer;
        } view1340_2;
        struct {
            s32 respawnTimer;
        } view1340_3;
    } views1340;
    char pad1344[0x70];
    union {
        struct {
            struct StateInfo * states;
        } view13B4_0;
        struct {
            struct StateInfo * states;
        } view13B4_1;
        struct {
            struct Mode * actionDefinitions;
        } view13B4_2;
        struct {
            void * character;
        } view13B4_3;
        struct {
            s32 f13B4;
        } view13B4_4;
        struct {
            struct Shared_StateInfo * states;
        } view13B4_5;
    } views13B4;
    char pad13B8[0x10];
    union {
        struct {
            s32 reservedWord15;
        } view13C8_0;
        struct {
            s32 w13C8;
        } view13C8_1;
        struct {
            s32 f13C8;
        } view13C8_2;
    } views13C8;
    char pad13CC[0x8];
    s32 toggleState;
    union {
        struct {
            struct Held * held;
        } view13D8_0;
        struct {
            struct Held * held;
        } view13D8_1;
    } views13D8;
    char pad13DC[0xC];
    s32 messageIndex;
    char pad13EC[0x64];
    union {
        struct {
            s32 computerControlled;
        } view1450_0;
        struct {
            s32 computer;
        } view1450_1;
        struct {
            s32 infinite;
        } view1450_2;
        struct {
            s32 unlimited;
        } view1450_3;
        struct {
            s32 uncounted;
        } view1450_4;
        struct {
            s32 f1450;
        } view1450_5;
    } views1450;
    union {
        struct {
            struct AiController *aiController;
        } view1454_0;
        struct {
            s32 f1454;
        } view1454_1;
    } views1454;
    char pad1458[0xC];
    union {
        struct {
            CVector3 aim;
        } view1464_0;
        struct {
            CVector3 aim;
        } view1464_1;
    } views1464;
    char pad1470[0x10];
    union {
        struct {
            Matrix beams[2];
        } view1480_0;
        struct {
            Matrix beams[2];
        } view1480_1;
    } views1480;
    union {
        struct {
            Matrix lasers[2];
        } view1500_0;
        struct {
            Matrix lasers[2];
        } view1500_1;
    } views1500;
    union {
        struct {
            Matrix dots[2];
        } view1580_0;
        struct {
            Matrix dots[2];
        } view1580_1;
    } views1580;
    char pad1600[0xC0];
    f32 turnAccumulator; /* +0x16C0: Player_UpdateSwimmingState */
    char pad16C4[0x10];
    union {
        struct {
            s32 score;
        } view16D4_0;
        struct {
            s32 f16D4;
        } view16D4_1;
    } views16D4;
    u16 pendingBonus;
    char pad16DA[0x6];
    union {
        struct {
            struct SharedPlayer * next;
        } view16E0_0;
        struct {
            struct SharedPlayer * next;
        } view16E0_1;
        struct {
            struct SharedPlayer * next;
        } view16E0_2;
    } views16E0;
    u32 pad16E4; /* Player-array stride is 0x16E8. */
};

struct TurretRiderTargetView {
    char pad0[0x80];
    SharedPlayer *target;
    char pad84[0x18];
    f32 heading; /* 0x9C */
    char padA0[0x88];
    union {
        CVector3 position;
        struct {
            char pad128[8];
            CVector3 aim;
        };
    };
};

struct WeaponFireState;
struct WeaponFireState {
    char pad0[0x2C];
    struct AiBehaviourTable *animation;
    char pad30[4];
    s8 variant;
    s8 queuedAction; /* 0x35 */
    char pad36[0x64 - 0x36];
    f32 cueTimer;
    char pad68[0xCB - 0x68];
    s8 triggerMode; /* 0xCB */
    char padCC[0x120 - 0xCC];
    s32 animationCount;
    f32 spinStep;
    f32 spin;
    char pad12C[4];
    f32 charge; /* 0x130 */
    char pad134[4];
    s32 resetState; /* 0x138 */
    s32 mode;
    char pad140[4];
    s32 rounds;
    char pad148[4];
    s32 triggered;
    s32 alternate;
};

union FloatOrWord;
typedef union FloatOrWord FloatOrWord;

union FloatOrWord;
union FloatOrWord {
    f32 value;
    s32 word;
};


struct Shared_Actor;
typedef struct Shared_Actor Shared_Actor;






struct ActorPlayerControllerView;
typedef struct ActorPlayerControllerView ActorPlayerControllerView;

struct SliderTransitionView;
typedef struct SliderTransitionView SliderTransitionView;

struct SettingsE;
struct SettingsE {
    char pad0[0xD];
    u8 players;
};




struct PlayerStartupSoundView;
typedef struct PlayerStartupSoundView PlayerStartupSoundView;

struct SoundPlayerStateTableView;
typedef struct SoundPlayerStateTableView SoundPlayerStateTableView;



struct NavigationNodeCostView;
struct NavigationNodeCostView {
    char pad0[0x18];
    f32 cost;
};

struct SliderStepRecord;
struct SliderStepRecord {
    char pad0[0x54];
    s32 activeState;
};

struct WeaponActionRecord;
typedef struct WeaponActionRecord WeaponActionRecord;

struct Info;
typedef struct Info Info;

struct Info;
struct Info {
    unsigned char raw[20];
    f32 scale; /* 0x14: waypoint response scale */
};

struct Shared_Actor;
struct Shared_Entity;
struct Shared_Variant;
struct Shared_Actor {
    u8 pad0;
    u8 color;
    u8 pad1;
    s8 subtype;
    u8 pad2[20];
    struct Shared_Variant * variant;
    u8 pad3[152];
    s32 action;
    u8 pad4[0x100 - 0xB8];
    s32 weaponFlags;
    u8 pad104[0x140 - 0x104];
    Info effects[6];
    u8 pad5[8];
    struct Shared_Entity * entity;
};

struct WeaponFireState;
typedef struct WeaponFireState WeaponFireState;

struct PaddedFloatView;
typedef struct PaddedFloatView PaddedFloatView;

struct PaddedFloatView;
struct PaddedFloatView {
    char pad0[0x4];
    f32 value;
};

struct EffectSpawnModeView;



struct SliderStepRecord;
typedef struct SliderStepRecord SliderStepRecord;

struct WeaponActionRecord;
struct WeaponActionRecord {
    s16 action;
    char pad2[0x16];
};


struct ItemMenuSelectionView;
struct ItemMenuSelectionView {
    char pad[0xE4];
    u16 id;
};










struct SoundPlayerStateTableView;
struct SoundPlayerStateTableView {
    char pad0[0x3C];
    s32 selectedSoundIndex;
    char pad3C[0x40 - 0x3C - sizeof(s32)];
    s32 soundStates;
};


struct ActorEffectEventView;
struct ActorEffectEventView {
    char pad0[0x4];
    s32 eventIndex;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    void * actor;
};

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
#define RW_LOCALIZED_TEXT(fixed, eu_table, eu_x_table, language) ((eu_x_table)[language])
#else
#define RW_LOCALIZED_TEXT(fixed, eu_table, eu_x_table, language) ((eu_table)[language])
#endif
#else
#define RW_LOCALIZED_TEXT(fixed, eu_table, eu_x_table, language) (fixed)
#endif


struct PlayerStartupSoundView;
struct PlayerStartupSoundView {
    unsigned char padding_0[4544];
    s32 startupSoundNode;
};








struct ActorEffectEventView;
typedef struct ActorEffectEventView ActorEffectEventView;

struct ActorPlayerControllerView;
struct ActorPlayerControllerView {
    char pad0[0x1D8];
    void * player;
};

struct SliderTransitionView;
struct SliderTransitionView {
    char pad0[0x58];
    s32 modeState;
};

struct PlayerWeaponStateView;
typedef struct PlayerWeaponStateView PlayerWeaponStateView;

struct SettingsE;
typedef struct SettingsE SettingsE;






struct Owner;
struct NavigationTrack;
struct Owner {
    char pad0[8];
    CVector3 position;
    char pad14[4];
    union {
        char *track;
        struct NavigationTrack *navigationTrack;
    };
    char pad1C[0x34];
    CVector3 scale;
    CQuatern orientation;
    f32 heading;
    char pad70[4];
    struct CMatrix4 transform;
};

struct CompactOptionsPageView;
typedef struct CompactOptionsPageView CompactOptionsPageView;

struct EffectSpawnModeView;
typedef struct EffectSpawnModeView EffectSpawnModeView;



#endif
