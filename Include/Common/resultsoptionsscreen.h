#ifndef COMMON_RESULTSOPTIONSSCREEN_H
#define COMMON_RESULTSOPTIONSSCREEN_H
#include "Frontend/frontend.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"

struct ResourceSmpFlickerCreateFlickerWidget;

struct ResultsOptionsScreen;
struct WidgetLabelTextView;
struct ResultsOptionsScreen {
    char pad0[0x20];
    char panels[2][0x4A8];
    union { struct MenuWidget *root; void *parent; };
    void *nodes;
    struct MenuWidget *leftPanel;
    s32 leftStep;
    struct MenuWidget *rightPanel;
    s32 rightStep;
    s32 state;
    s32 slideFrames;
    void *resource;
    struct MenuWidget *focusItem;
    struct WidgetLabelTextView *owner;
    struct MenuWidget *item155;
    char heading[50]; /* +0x9A0: heading text of the results options header */
    char time[50]; /* +0x9D2: best time text */
    char text[64];
    s32 selection;
    struct MenuWidget *window;
    s32 modeFlag;
    struct MenuWidget *item;
    s32 clock;
    s32 wordA58;
    s32 player;
    struct MenuWidget *bannerShadow;
    struct MenuWidget *banner;
    s32 blinking;
    s32 frames;
    s32 blinkDelay;
    u8 owned[5];
    u8 pending[5];
};

struct ProfileWeaponOwnedView;
struct ProfileWeaponOwnedView {
    char pad0[0x11C];
    u8 owned;
};


struct PlayerSettingsOptionRow;
struct PlayerSettingsOptionRow {
    s32 portrait; /* character portrait image id shown in result and selection rows */
    f32 scale[4];
    f32 distance[4];
    CVector3 position[4];
    s32 light[4];
    char pad64[0x70 - 0x64];
};









struct ResultsPreviewProfile;
struct ResultsPreviewProfile {
    char pad0[0x7E];
    u8 single[5];
    u8 versus[5];
    u8 three[5];
    u8 four[5];
    char pad92[0x190 - 0x92];
};

struct ResultsOptionsScreen;


struct ResourceSmpFlickerCreateFlickerWidget;






struct Pair;
struct Pair {
    s32 a;
    s32 b;
    union {
        s32 id;
        struct {
            u16 high;
            u16 low;
        } half;
    } c;
};



struct EntryFrontendRefreshTrialCharacterPreview;
struct EntryFrontendRefreshTrialCharacterPreview {
    char pad[0x80];
    s8 kind;
    char tail[21];
};

struct EntryFrontendRefreshTrialCharacterPreview;
struct GameSettingsModeStatusView;
struct GameSettingsModeStatusView {
    char pad0[0xD];
    u8 mode;
    char padE[0xD0 - 0xE];
    struct EntryFrontendRefreshTrialCharacterPreview status[8];
};


struct ResourceSmpFlickerCreateFlickerWidget;


struct MenuMarker;

struct WidgetLabelTextView;


struct ResultsOptionEntry;
struct ResultsOptionEntry {
    s32 id;
    s32 first;
    s32 second;
    char pad[28 - 12];
};

/* The 36 unlock nodes of the trial catalogue, one 28-byte entry each. */
extern struct ResultsOptionEntry g_trialCatalogueStages[36];


struct WidgetFlagsView;

struct TableFrontendMarkLinkedTrialsAvailable;
struct TableFrontendMarkLinkedTrialsAvailable {
    u8 pad0;
    u8 first;
    u8 items[3];
};


struct ResultsOptionsScreen;
typedef struct ResultsOptionsScreen ResultsOptionsScreen;


struct RecordFrontendFillTrialPresetWeaponRows;
struct RecordFrontendFillTrialPresetWeaponRows {
    char pad0[6];
    u16 items[8];
};

struct ProfileWeaponOwnedView;
typedef struct ProfileWeaponOwnedView ProfileWeaponOwnedView;

struct RecordFrontendFillTrialPresetWeaponRows;
typedef struct RecordFrontendFillTrialPresetWeaponRows RecordFrontendFillTrialPresetWeaponRows;
#endif
