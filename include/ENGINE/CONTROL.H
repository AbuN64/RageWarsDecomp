#ifndef ENGINE_CONTROL_H
#define ENGINE_CONTROL_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"

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

struct MenuMarker;
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
    ResourceSmpFlickerCreateFlickerWidget *reservedPointer;
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
extern s32 g_cupCategoryZeroArenaControls[];
extern s32 g_cupCategoryOneArenaControls[];
extern s32 g_cupCategoryThreeArenaControls[];
extern s32 g_cupCategoryTwoArenaControls[];
#endif
