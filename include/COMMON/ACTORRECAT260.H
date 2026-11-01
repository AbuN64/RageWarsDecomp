#ifndef COMMON_ACTORRECAT260_H
#define COMMON_ACTORRECAT260_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TEXTLAYERMETRICS.H"

struct ControllerPakMenuActorView;
typedef struct ControllerPakMenuActorView ControllerPakMenuActorView;

struct ControllerPakMenuActorView;
struct ControllerPakMenuActorView {
    char pad[0x58];
    int flags58;
    char pad5c[0xC4];
    int flags120;
    char pad124[0x9C];
    int flags1c0;
    char pad1c4[0x4C];
    int flags210;
    char pad214[0x24];
    int flags238;
    char pad23c[0x24];
    int flags260;
};

struct ControllerPakMenuContext;
struct ControllerPakMenuContext {
    char pad[12];
    ControllerPakMenuActorView *actor;
    char pad2[12];
    int playerAddress;
};


struct ControllerPakMenuContext;
typedef struct ControllerPakMenuContext ControllerPakMenuContext;


struct PlayerRespawnMenuActor;
struct PlayerRespawnMenuActor {
    char pad0[4928];
    s32 respawnDelayFrames;
    char pad1344[268];
    s32 computerControlled;
};

struct PlayerRespawnMenuActor;
struct PlayerRespawnMenuContext;
struct PlayerRespawnMenuContext {
    char pad0[28];
    struct PlayerRespawnMenuActor * actor;
};

struct CaptionEntry;
typedef struct CaptionEntry CaptionEntry;


struct PlayerMenuFlagContext;
typedef struct PlayerMenuFlagContext PlayerMenuFlagContext;

struct Leaf;
struct Leaf {
    char pad[0x8E];
    u8 flag;
};
struct Leaf;
struct Middle;
struct Middle {
    char pad[0x5D8];
    struct Leaf *leaf;
};
struct Middle;
struct NestedPlayerMenuFlagContext;
struct NestedPlayerMenuFlagContext {
    char pad[0x1C];
    struct Middle *middle;
};

struct PlayerStateDirtyOwnerView;
typedef struct PlayerStateDirtyOwnerView PlayerStateDirtyOwnerView;

struct ControllerPakMenuActorView;
struct PlayerMenuFlagContext;
struct PlayerMenuFlagContext {
    char pad[0xC];
    struct ControllerPakMenuActorView *actor;
    char pad10[0xC];
    PlayerStateDirtyOwnerView *parent;
};


struct PlayerMenuResumeActor;
struct PlayerMenuResumeActor {
    char pad[0x5D0];
    int waiting;
    char pad5D4[4];
    FragTagProfileFlagView *info;
};
struct PlayerMenuResumeActor;
struct PlayerMenuResumeContext;
struct PlayerMenuResumeContext {
    char pad[0x1C];
    struct PlayerMenuResumeActor *actor;
};

struct PlayerMenuResumeContext;
typedef struct PlayerMenuResumeContext PlayerMenuResumeContext;


struct MenuPromptKindView;

struct CaptionEntry;
struct CaptionEntry {
    char pad0[4];
    s32 width;
    char pad8[4];
    f32 scaleX;
    f32 scaleY;
    char pad14[2];
    u16 x;
    char pad18[6];
    u16 y;
};


struct PlayerRespawnMenuActor;
typedef struct PlayerRespawnMenuActor PlayerRespawnMenuActor;

struct NestedPlayerMenuFlagContext;


struct PlayerRespawnMenuContext;
typedef struct PlayerRespawnMenuContext PlayerRespawnMenuContext;



struct MenuRules;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Player_FormatPlayerResultScore(struct LayeredText *field, struct MenuRules *holder);
#endif



#endif
