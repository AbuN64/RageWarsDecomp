#ifndef COMMON_OBJRECAT18V6_H
#define COMMON_OBJRECAT18V6_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
struct MarkerItemMenuRestoreBootMemory;
struct MarkerItemMenuRestoreBootMemory {
    char text[15];
};

struct MarkerItemMenuRestoreBootMemory;
typedef struct MarkerItemMenuRestoreBootMemory MarkerItemMenuRestoreBootMemory;


struct EffectBoneNode;
typedef struct EffectBoneNode EffectBoneNode;

struct ItemMenuRenderNode;
struct ItemMenuRenderNode {
    struct ItemMenuRenderNode *prev;
    struct ItemMenuRenderNode *next;
    EffectBoneNode *node;
    u8 padC[0x10];
    void *object;
    s32 contextId; /* 0x20: companion identifier used by inactive-list lookup */
    f32 value;
    u8 pad28[0xC];
    s32 renderMode; /* 0x34 */
    u8 pad38[4];
    u32 flags;
    struct Node438C *vertices; /* 0x40 */
    u8 pad44[4];
    s32 vertexCount; /* 0x48 */
};

struct RibbonNodeList;
struct ItemMenuRenderNode;
struct RibbonNodeList {
    struct ItemMenuRenderNode *head;
    struct ItemMenuRenderNode *tail;
    s32 count;
};

struct RibbonNodeList;
typedef struct RibbonNodeList RibbonNodeList;

struct RibbonNodeLists;
struct RibbonNodeLists {
    RibbonNodeList active;
    RibbonNodeList inactive;
};


struct Node44;



struct TimedEffectCallbackView;

struct Bar;
struct Bar {
    s32 active;
    s32 *script;
    s32 state;
    s32 wait;
    f32 x;
    f32 y;
    char pad18[0x20];
    s32 fill;
    void *label;
    s32 enabled; /* 0x40 */
    s32 target;
};

struct Bar;
typedef struct Bar Bar;

struct Hud;
struct Hud {
    Bar bars[2];
};

struct ToggleMenu;
typedef struct ToggleMenu ToggleMenu;



struct CItem;

struct RibbonNodeLists;
typedef struct RibbonNodeLists RibbonNodeLists;

struct RibbonWorld;
struct RibbonWorld {
    u8 pad0[0x751C];
    RibbonNodeLists lists;
};



struct CItem;
typedef struct CItem CItem;

struct ItemMenuRenderNode;
typedef struct ItemMenuRenderNode ItemMenuRenderNode;

struct ToggleMenuPlayerInputView;


struct ItemMenuToggleStateView;
typedef struct ItemMenuToggleStateView ItemMenuToggleStateView;



extern float g_spriteExtentAndUnitConstants;


struct RibbonWorld;
typedef struct RibbonWorld RibbonWorld;

struct CItem;
struct CItem {
    int active;
    int state;
    s32 resource;
    u8 key;
    unsigned char generation;
    char padE[2];
    s32 imageResource;
    s32 imageFrameOrTextureHandle;
    short transitionStep;
    int transitionFrame;
    f32 value;
    s32 extra;
    f32 restoreValue;
    s32 restoreExtra;
    s32 selectCallbackAddress;
    s32 updateCallbackOrTextureId;
};





struct EffectCallbackEntryView;
typedef struct EffectCallbackEntryView EffectCallbackEntryView;


struct AttachedEffectTimerView;
typedef struct AttachedEffectTimerView AttachedEffectTimerView;

struct TimedEffectCallbackView;
typedef struct TimedEffectCallbackView TimedEffectCallbackView;






struct MenuItem;
typedef struct MenuItem MenuItem;

struct MenuItem;
struct MenuItem {
    s32 active;
    s32 on;
    char pad8[0x10 - 0x8];
    s32 image; /* 0x10: toggle-menu GameSprite resource */
    s32 imageFrame; /* 0x14: GameSprite frame */
    s16 bounce;
    s32 startFrame;
    f32 value;
    s32 extra;
    f32 restoreValue;
    s32 restoreExtra;
    s32 (*select)(void *input, struct MenuItem *item);
    s32 (*update)(void *input, struct MenuItem *item);
};

struct ToggleMenu;

struct AttachedEffectPoolView;
typedef struct AttachedEffectPoolView AttachedEffectPoolView;

extern float g_impactMarkScaleConstants;

struct AttachedEffectPoolView;


struct ItemMenuToggleStateView;

struct Hud;
typedef struct Hud Hud;

struct AttachedEffectTimerView;








struct AttachedEffectDetachState;
typedef struct AttachedEffectDetachState AttachedEffectDetachState;



struct EntryItemMenuAdvanceSelection;
struct EntryItemMenuAdvanceSelection {
    char pad0[0x4];
    s32 active;
    char pad8[0x38 - 0x8];
};

struct EntryItemMenuAdvanceSelection;
typedef struct EntryItemMenuAdvanceSelection EntryItemMenuAdvanceSelection;

struct ItemMenuCursorState;


extern float g_attachedTransformModelScale;

extern float g_childTransformAlternateScale;

struct CItemMenu_t;
typedef struct CItemMenu_t CItemMenu;

struct AttachedEffectDetachState;





extern float g_childTransformDefaultScale;


struct EffectCallbackEntryView;


struct CItemMenu_t;
struct CItemMenu_t {
    unsigned char active;
    unsigned char m_ModePos;
    char pad2[2];
    CItem entries[4];
    short m_LastItemPos;
    short m_ItemAlphaFade;
    int m_FrameCount;
};



extern float g_attachedTransformDefaultScale;


struct ItemMenuCursorState;
typedef struct ItemMenuCursorState ItemMenuCursorState;



struct ToggleMenuPlayerInputView;
typedef struct ToggleMenuPlayerInputView ToggleMenuPlayerInputView;
#endif
