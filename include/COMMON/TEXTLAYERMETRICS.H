#ifndef COMMON_TEXTLAYERMETRICS_H
#define COMMON_TEXTLAYERMETRICS_H
#include "TYPES.H"
#include "MENU/BUILT_MENU.H"
#include "COMMON/SESSION_STATE.H"
#include "COMMON/LEVEL_ACTOR.H"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern const char g_playerMenuValueFormat[];
#endif
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
struct CMenu_t;
typedef struct CMenu_t Node_Pak_CountLiveNodes;

struct EntryPakCreateMenuFromParameters;

struct StyledMenuTextPanel;
typedef struct StyledMenuTextPanel StyledMenuTextPanel;

struct TextLayerMetrics;

struct TextLayerMetrics;
typedef struct TextLayerMetrics TextLayerMetrics;

struct MenuCharacterPreviewState;
typedef struct MenuCharacterPreviewState MenuCharacterPreviewState;

struct LayeredText;
typedef struct LayeredText LayeredText;

struct LayeredText;
struct LayeredText {
    int value;
    short mode;
    short reserved;
    int flags;
    int reservedWord1;
    int reservedWord2;
    int *text;
    int reservedWord3;
    int spacing;
    int reservedWord4;
    int reservedWord5;
};

struct StyledMenuTextPanel;
struct StyledMenuTextPanel {
    s16 selectedIndex;
    s16 x; /* 0x02 */
    s16 y; /* 0x04 */
    char pad6[6];
    struct TextBoundsText *entries; /* 0x0C */
    s32 count; /* 0x10 */
    char pad14[0x1C];
    f32 alpha; /* 0x30 */
    f32 fade; /* 0x34 */
    s32 shadowEnabled;
    s32 shadowClearRequest;
    struct TextBoundsData *data; /* 0x40 */
};

struct PakMenuInputStateView;
struct PakMenuInputStateView {
    char pad00[0xB0];
    s32 buttons;
    s32 pressedButtons;
    char padB8[0xBC - 0xB8];
    s32 history1;
};


struct CMenu_t;
struct PakMenuInputStateView;
struct TablePakUpdateDialogList;
struct ParamsPakAllocateMenu;

struct PakMenuInputStateView;
typedef struct PakMenuInputStateView PakMenuInputStateView;

struct MenuTemplateParameters;

struct CMenuFontInfo_t;

struct MenuRules;
struct Outer;

struct Outer;

struct PreviewWidget;
typedef struct PreviewWidget PreviewWidget;

struct PreviewWidget;
struct PreviewWidget {
    float x;
    float y;
    float depth;
    char padc[8];
    float dx;
    float dy;
    float dz;
    char pad20[0xD4];
    float size;
    char padf8[0x90];
};

struct MenuCharacterPreviewState;
struct MenuCharacterPreviewState {
    int selection;
    PreviewWidget model;
    s32 reserved18C;
    LevelActor actor; /* 0x190 */
    int active;
    float size;
};

struct MenuCharacterPreviewState;
struct MenuPreviewSelectionView;

struct PakMenuVirtualNode;
struct PakMenuVirtualNode {
    char pad0[0x14];
    void **vtable;
    char pad18[0x1B8];
    struct PakMenuVirtualNode *next;
};

struct MenuPreviewSelectionView;
typedef struct MenuPreviewSelectionView MenuPreviewSelectionView;


struct PakMenuVirtualNode;
struct MenuCallbackListOwner;

struct StyledMenuTextEntryView;
typedef struct StyledMenuTextEntryView StyledMenuTextEntryView;

struct ObjectPakDrawMenuCharacter;



struct CMenuFontInfo_t;
typedef struct CMenuFontInfo_t CMenuFontInfo;


struct MenuCreationParameters;

struct StyledMenuTextEntryView;

struct GamePlayerListView;
#endif
