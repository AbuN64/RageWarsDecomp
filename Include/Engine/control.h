#ifndef ENGINE_CONTROL_H
#define ENGINE_CONTROL_H
extern int g_controllerPakState[];
#include "Frontend/frontend.h"
#include "Ai/player_symbols.h"
#include "Common/Lone/controller_rumble_pool.h"
#include "Common/contreadformat.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Engine/rumble.h"

/* Per-button tap, age, repeat and hold counters consumed by the input update. */
typedef struct ControllerButtonHistory {
    s8 taps;
    s8 age;
    s8 repeat;
    s8 held;
} ControllerButtonHistory;

struct ControllerProfile {
    s32 connected; /* 0x00 */
    s8 port; /* 0x04 */
    u8 padding005[3];
    s32 reservedWordA;
    s32 reservedWordB;
    s32 reservedWordC;
    s32 inputPreviousButtons;
    s32 inputButtons; /* 0x18 */
    u32 inputPressedButtons; /* 0x1C */
    s32 inputHistory[3]; /* 0x20 */
    ControllerButtonHistory buttonHistory[32]; /* 0x2C */
    s32 previousButtons; /* 0xAC */
    s32 buttons; /* 0xB0 */
    u32 pressedButtons; /* 0xB4 */
    s32 history[2]; /* 0xB8 */
    u32 buttonState; /* 0xC0 */
    s8 stickX; /* 0xC4 */
    s8 stickY; /* 0xC5 */
    s8 previousStickX; /* 0xC6 */
    s8 previousStickY; /* 0xC7 */
    s32 pakActive; /* 0xC8 */
    s32 mode; /* 0xCC */
    f32 pakAmount; /* 0xD0 */
    f32 pakTimer; /* 0xD4 */
    OSPfs pak; /* 0xD8 */
    struct RumbleNodePoolView effectPool; /* 0x140 */
    struct RumbleEffectNode effectNodes[3]; /* 0x16C */
    s32 reset; /* 0x220 */
};
typedef struct ControllerProfile ControllerProfile;


struct ContPad;
struct ActorList {
    s32 pad0;
    struct SnapshotActorView *actors;
    s32 count;
};

/* Type 1 curves choose a new random value each period. */
typedef struct RandomCurve {
    s32 type;
    f32 period;
    u8 minimum;
    u8 maximum;
} RandomCurve;

struct ControllerProfile;

void Control_UpdateControllerInput(struct ControllerProfile *state, s8 x, s8 y, u32 buttons);

typedef struct MenuMarker {
    char pad[0x10];
    u8 alpha;
    char pad11[0x14 - 0x11];
    s16 x;
} MenuMarker;
struct ScreenScenarioSetupSelectPreviousCatalogueCategory;
struct ScreenScenarioSetupSelectPreviousCatalogueCategory {
    char pad0[0x308];
    char view[0x434 - 0x308];
    s32 category;
    s32 selection;
    struct MenuMarker *item;
    char pad440[0x448 - 0x440];
    struct MenuMarker *marker;
    char pad44C[0x45C - 0x44C];
    s32 word45C;
    char pad460[0x464 - 0x460];
    s32 word464;
};

extern void ScenarioSetup_ClearFlagBits(void);

struct Label;


struct G;
struct G {
    char pad0[0x3DC];
    s32 reservedWord3DC;
    char pad3E0[0x3EC - 0x3E0];
    s32 reservedWord;
    s32 reservedWord1;
    char pad3F4[0x440 - 0x3F4];
    s32 reservedWord2;
    s32 reservedWord3;
    s32 reservedWord4;
    struct ResourceSmpFlickerCreateFlickerWidget *reservedPointer;
};

struct ResourceSmpFlickerCreateFlickerWidget;
struct VersusResultsScreen;
struct VersusResultsScreen {
    char pad0[0x8];
    char panels[4][0xC0];
    char tie[0x3DC - 0x308];
    s32 state;
    char pad3E0[0x434 - 0x3E0];
    s32 winnerSlot;
    s32 winner;
    char pad43C[0x450 - 0x43C];
    struct ResourceSmpFlickerCreateFlickerWidget *bannerShadow;
    struct ResourceSmpFlickerCreateFlickerWidget *banner;
    char pad458[0x464 - 0x458];
    s32 frames;
    s32 blinkDelay;
    s32 blinking;
};

struct ResourceSmpFlickerCreateFlickerWidget;

struct MenuMarker;
struct ScreenScenarioSetupSelectPreviousCatalogueItem;
struct ScreenScenarioSetupSelectPreviousCatalogueItem {
    char pad0[0x308];
    char view[0x434 - 0x308];
    s32 category;
    s32 selection;
    struct MenuMarker *item;
    struct MenuMarker *left;
    struct MenuMarker *right;
    struct MenuMarker *marker;
    char pad44C[0x45C - 0x44C];
    s32 word45C;
    char pad460[0x464 - 0x460];
    s32 word464;
};

struct Cup;
struct Cup {
    s32 index;
    s32 stages;
    u8 played[4];
};

/* The cup being played. */
extern struct Cup g_scenarioCupProgress;



struct G;
typedef struct G G;

struct ResourceSmpFlickerCreateFlickerWidget;



struct Label;
struct ScreenScenarioSetupRefreshSelectedArenaLabel;
struct ScreenScenarioSetupRefreshSelectedArenaLabel {
    void *window;
    char pad4[0x3EC - 0x4];
    struct Label *label;
    void *widgetB;
    char text[0x434 - 0x3F4];
    s32 category;
    s32 selection;
    void *item;
    void *widgetC;
    void *widgetD;
    void *widgetE;
};

extern void ScenarioSetup_ResetSelectionIndicators(void);

struct MenuRenderFill;
struct MenuRenderFill {
    s32 mode;
    f32 color[4];
};


extern s32 ScenarioSetup_DispatchCatalogueEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern s32 g_cupArenaControls[40];
struct ControllerRumbleView;
void Control_UpdateControllerRumble(struct ControllerRumbleView *profile);
extern s32 Control_TakePakChange(s32 ch);
extern void Control_EnableControllerPak(s32 kind);
extern void Control_DisableControllerPak(int controllerPort);
extern s32 Control_AnyControllerConnected(void);

extern char g_controllerSiMessageQueue[];
extern u8 g_controllerInputReady;
extern u8 g_controllerPakFrontendState;
extern struct ContPad g_controllerPadData[4];
extern void Control_DisableAllControllerPaks(void);
#endif
