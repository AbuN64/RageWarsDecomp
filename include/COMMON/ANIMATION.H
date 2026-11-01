#ifndef COMMON_ANIMATION_H
#define COMMON_ANIMATION_H
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct FlickerUpdateState;
struct FlickerUpdateState {
    char pad0[0x4];
    u8 reservedByte;
    char pad4[0x3F];
    s32 flickering;
    s32 entryCount;
    s32 entryValues[5];
    s32 entryHoldCounts[5];
    s32 entryIndex;
    struct ResourceSmpFlickerCreateFlickerWidget *target;
    s32 timer;
    s32 restoreValue;
    s32 armed;
};

struct MenuFadeWidget;
struct MenuFadeWidget {
    char pad0[0xC];
    s16 kindA;
    s16 kindB;
    char pad10[0x12 - 0x10];
    s16 flags;
    char pad14[0x20 - 0x14];
    union { s32 progressXWord; f32 progressX; };
    f32 progressY;
    char pad28[0x2C - 0x28];
    u32 colours[4];
    char pad3C[0x44 - 0x3C];
    struct MenuFadeWidget *frame;
    struct MenuFadeWidget *item;
    f32 scaleX;
    f32 scaleY;
    char pad54[4];
    s32 phase;
    s32 running;
    u32 copies[4];
    u32 greenStep;
    u32 redStep;
    s32 active;
};

struct Animation;
typedef struct Animation Animation;

struct FlickerStartView;
struct ResourceSmpFlickerCreateFlickerWidget;
struct FlickerStartView {
    char pad0[0x44];
    s32 busy;
    char pad48[0x4C - 0x48];
    s32 entries[(0x74 - 0x4C) / 4];
    s32 index;
    struct ResourceSmpFlickerCreateFlickerWidget *target;
};

extern float g_fadeWidgetInitialScale;

struct FrameSequence;



extern float g_fadeWidgetInitialProgress;

struct Animation;
struct Animation {
    char pad0[0xC];
    s16 kindA;
    s16 kindB;
    char pad10[2];
    s16 flags;
    char pad14[0x30];
    s32 widget;
    s32 *frames;
    char pad4C[4];
    s32 count;
    s32 reservedWordA;
    char pad58[4];
    s32 reservedWordB;
    char pad60[4];
};

struct FlickerActivityView;
struct FlickerActivityView {
    char pad0[0x44];
    s32 busy;
    char pad48[0x84 - 0x48];
    s32 pending;
};

struct FrameSequence;

struct MenuFadeWidget;
typedef struct MenuFadeWidget MenuFadeWidget;


struct FlickerActivityView;
extern s32 SmpFlicker_IsFlickerIdle(struct FlickerActivityView *object);


struct Triple;

struct FrameSequence;


struct ResourceSmpFlickerCreateFlickerWidget;
struct FlickerRestoreView;
struct FlickerRestoreView {
    char pad[0x78];
    struct ResourceSmpFlickerCreateFlickerWidget *target;
    char pad7C[0x83 - 0x7C];
    u8 value;
    s32 pending;
};

struct Triple;

struct MenuResourceWidget;
typedef struct MenuResourceWidget MenuResourceWidget;
extern MenuResourceWidget *SmpFlicker_CreateFlickerWidget(s32, s32);

struct FlickerRestoreView;
extern void SmpFlicker_RestoreFlickerValue(struct FlickerRestoreView *source);

struct FlickerUpdateState;
typedef struct FlickerUpdateState FlickerUpdateState;

struct FrameSequence;

struct MenuResourceWidget;
struct ResourceSmpFlickerCreateFlickerWidget;
struct MenuResourceWidget {
    char pad0[0xC];
    short a;
    short b;
    short pad1;
    short c;
    char pad2[0x64];
    struct ResourceSmpFlickerCreateFlickerWidget *resource;
    int pad3;
    union
  {
    int value;
    unsigned char bytes[4];
  } owner;
    int pad4;
};


extern f32 g_fadeProgressRetreatStep;
extern f32 g_fadeProgressHorizontalMaximum;
extern f32 g_fadeProgressHorizontalAdvanceStep;
#endif
