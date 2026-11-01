#ifndef COMMON_OBJECTRECAT28_H
#define COMMON_OBJECTRECAT28_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
struct Tree;

struct StateFrontendInitModelPreviewTransform;
typedef struct StateFrontendInitModelPreviewTransform StateFrontendInitModelPreviewTransform;

struct ModelPreviewRotationSpeedView;
struct Triple;
struct ModelPreviewRotationSpeedView {
    char pad[0x28];
    struct Triple vector;
};

struct ModelPreviewPositionView;
struct Triple;
struct ModelPreviewPositionView {
    char pad[0x10];
    struct Triple vector;
};

struct ModelPreviewPositionView;
struct Triple;

struct WidgetFlagsView;
struct Pulse;
struct WidgetFlagsView;
struct Pulse {
    union { struct WidgetFlagsView *light; struct MenuWidget *widget; };
    s32 phase;
};

struct MenuModelItem;
struct MenuModelItem {
    s32 unused;
    CVector3 scale;
    CVector3 position;
    CVector3 rotation;
    CVector3 speed;
    s32 model;
    char matrices[128];
    s32 flags;
};

struct StateFrontendInitModelPreviewTransform;
struct StateFrontendInitModelPreviewTransform {
    s32 unused;
    Triple first;
    Triple second;
    s32 rotationXBits;
    s32 rotationYBits;
    s32 rotationZBits;
    s32 rotationSpeedXBits;
    s32 rotationSpeedYBits;
    s32 rotationSpeedZBits;
    s32 modelId;
};

struct MenuModelScreen;
struct MenuModelScreen {
    char p0[40];
    f32 heading;
    char p2C[0x160 - 0x2C];
    Matrix camera;
    char p1[0x29C-0x1A0];
    f32 width;
    f32 height;
    char p2[0x380-0x2A4];
    Matrix matrices[2];
};


struct ObjectB8;
struct ObjectB8 {
    char pad[0xB8];
    s32 value;
};

struct Pulse;
typedef struct Pulse Pulse;

struct MenuModelItem;
typedef struct MenuModelItem MenuModelItem;

struct Shared_Body;
typedef struct Shared_Body Shared_Body;

struct MenuModelScreen;
typedef struct MenuModelScreen MenuModelScreen;


typedef s32 (*MenuEventHandler)(void *, s32, s32, s32, s32);
extern MenuEventHandler g_profileResetEventHandlers;
#endif
