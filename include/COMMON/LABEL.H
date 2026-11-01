#ifndef COMMON_LABEL_H
#define COMMON_LABEL_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OBJECTRECAT28.H"
struct Label;
typedef struct Label Label;





struct MenuFrontendRefreshUnlockedFocusLabel;
typedef struct MenuFrontendRefreshUnlockedFocusLabel MenuFrontendRefreshUnlockedFocusLabel;

struct PreviewPositionView;
struct PreviewPositionView {
    char pad[0x480];
    CVector3 position;
};

struct ProfileStatisticsScreen;
typedef struct ProfileStatisticsScreen ProfileStatisticsScreen;

extern void Focus_RefreshUnlockedFocusLabel(void);

extern void Focus_RefreshProfileStatistics(void);

struct Object49C;
struct Object49C {
    char pad[0x49C];
    s32 value;
};

struct PreviewFacingView;
struct PreviewFacingView {
    char pad[0x48C];
    CVector3 facing;
};

struct PreviewFacingView;
typedef struct PreviewFacingView PreviewFacingView;



struct FrontendPanelTransitionView;
typedef struct FrontendPanelTransitionView FrontendPanelTransitionView;

struct PreviewPositionView;
typedef struct PreviewPositionView PreviewPositionView;





struct PreviewAngleView;
struct PreviewAngleView {
    char pad[0x498];
    s32 angle;
};




struct PreviewAngleView;
typedef struct PreviewAngleView PreviewAngleView;



struct NodeFrontendAnimateSlotSelectionMenu;
typedef struct NodeFrontendAnimateSlotSelectionMenu NodeFrontendAnimateSlotSelectionMenu;

struct FrontendPreviewMenuView;
struct FrontendPreviewMenuView {
    char pad0[8];
    char model[1];
};

struct ProfileStatisticsScreen;
struct ProfileStatisticsScreen {
    void *handle;
    char pad4[0x10C - 4];
    s32 index;
    char kills[50];
    char wins[50];
    char deaths[50];
    char score[50];
    char count[50];
};



struct NodeFrontendAnimateSlotSelectionMenu;
struct NodeFrontendAnimateSlotSelectionMenu {
    char pad0[0x10];
    u8 style;
    char pad11[0x14 - 0x11];
    u16 x;
    u16 y;
};

struct Label;
struct MenuFrontendRefreshUnlockedFocusLabel;
struct MenuFrontendRefreshUnlockedFocusLabel {
    char pad0[0xEC];
    MenuActorInputView *focus;
    struct Label *label;
    char padF4[0x18];
    s32 player;
};

struct OverlayWidgetListView;
typedef struct OverlayWidgetListView OverlayWidgetListView;

struct FrontendPreviewMenuView;
typedef struct FrontendPreviewMenuView FrontendPreviewMenuView;


struct OverlayWidgetListView;
struct OverlayWidgetListView {
    char pad[0x48];
    int count;
    void *items[1];
};




struct FrontendPanelTransitionView;
struct NodeFrontendAnimateSlotSelectionMenu;
struct FrontendPanelTransitionView {
    char pad0[4];
    void *handle;
    char pad8[0xC8 - 8];
    struct NodeFrontendAnimateSlotSelectionMenu *left;
    char padCC[2];
    u16 leftStep;
    struct NodeFrontendAnimateSlotSelectionMenu *right;
    char padD4[2];
    u16 rightStep;
    s32 state;
    s32 timer;
    s32 fade;
    struct NodeFrontendAnimateSlotSelectionMenu *groupA;
    struct NodeFrontendAnimateSlotSelectionMenu *cursor;
    struct NodeFrontendAnimateSlotSelectionMenu *focus;
    char padF0[4];
    struct NodeFrontendAnimateSlotSelectionMenu *groupB;
    s32 styleStep;
    s32 styleValue;
    struct NodeFrontendAnimateSlotSelectionMenu *groupC;
    char pad104[3];
    u8 alphaStep;
    s32 clock;
};

extern void Focus_UpdateFocusCaption(void);

extern void SmpOverlay_SetObjectValue(struct Object6C *object, s32 value);
extern void Focus_ShowUnlockedEntries(s32 style);

extern void Model_SetPreviewRenderFlags(struct ObjectB8 *, s32);
#endif
