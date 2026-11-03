#ifndef COMMON_ITEMRECAT20V1_H
#define COMMON_ITEMRECAT20V1_H
#include "COMMON/AUDIO_CALLBACKS.H"
#include "TYPES.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/OSTHREAD_S.H"
#include "COMMON/PAK_MENU.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "MENU/ITEMS/SCENE/OVLSCENE_FINDPLACEDOBJECTSBYKEY.H"
struct MenuLocalizedTextItemView;
struct MenuLocalizedTextItemView {
    char pad0[0x14];
    s32 x;
    char pad18[8];
    s32 y;
};

struct FontGlyphCountView;
struct FontGlyphCountView {
    char pad0[0xE];
    s16 glyphCount;
};

struct FontGlyphCountView;
typedef struct FontGlyphCountView FontGlyphCountView;

struct NavigationActorBrainView;
struct NavigationActorBrainView {
    char pad0[0x1454];
    void * brain;
};

/* Resource node pool: word 0 is the free-node count, word 0x11 the frame stamp;
   the cache record g_resourceRecencyList sits 0xBCC bytes below. */
struct Pool {
    s32 count;
    char pad[0x40];
    s32 useCounter;
};
extern s32 g_resourceFreeNodeCount;

struct FadedActorRenderView;
typedef struct FadedActorRenderView FadedActorRenderView;

struct StridedTable;
struct StridedTable {
    s32 stride;
    s32 count;
    char data[1];
};

struct FftTables;
typedef struct FftTables FftTables;

struct FftTables;
struct FftTables {
    f32 *sines;
    f32 *cosines;
    s32 *order;
    s32 size;
};

struct FrontendArchiveHandleView;
struct FrontendArchiveHandleView {
    char pad0[0x2C];
    int archiveHandle;
};

extern int g_gameModeTransitionFrames;


struct PortalLinkAvailabilityView;
struct PortalLinkAvailabilityView {
    char pad0[0x4];
    u8 available;
};

struct BreakableDamageScaleView;
struct BreakableDamageScaleView {
    unsigned char padding_0[29];
    s8 damageScale;
};

struct ActorDefinitionFlagsView;
struct ActorDefinitionFlagsView {
    s32 kind;
    char pad0[0x10];
    s32 flags;
};

struct ChoiceMenuCellView;

struct ChoiceMenuCellView;
struct MenuFrontendUpdatePlayModeMenu;
struct MenuFrontendUpdatePlayModeMenu {
    char pad[0x44];
    struct ChoiceMenuCellView *list;
};

struct FieldRow;
struct FieldRow {
    s32 value;
    char pad[8];
};

struct FieldRow;
typedef struct FieldRow FieldRow;

struct MenuCMenuProfileUpdateProfileModeLabel;
typedef struct MenuCMenuProfileUpdateProfileModeLabel MenuCMenuProfileUpdateProfileModeLabel;

struct Clip;
struct Clip {
    s16 mode;
    s16 frames;
};

struct Clip;
typedef struct Clip Clip;

struct RumbleEffectNode;
struct RumbleEffectNode {
    struct RumbleEffectNode *previous;
    struct RumbleEffectNode *next;
    Clip *key;
    CVector3 position;
    f32 value0;
    f32 value1;
    u32 amplitudeHandle; /* 0x20 */
    char pad24[8];
    u32 lifetimeHandle; /* 0x2C */
    char pad30[8];
    struct RumbleEffectNode **owner;
};

/* Shared free/active node pool initialized by Rumble_InitPoolNodes_Controller. */
struct RumbleNodePoolView {
    IntrusiveList free;
    IntrusiveList active;
    s32 baseLevel;
};

struct GlyphBuffer;
/* Font records contain a four-byte header and 147 eight-byte glyph records. */
typedef struct sm_font_char {
    u32 DataOffset;
    s8 width;
    s8 height;
    s8 PhysicalWidth;
    s8 BaselineOffset;
} sm_font_char;

struct GlyphBuffer {
    u32 header;
    sm_font_char glyphs[147];
};


struct Block70;
struct Block70 {
    s32 w[28];
};

struct Block70;
typedef struct Block70 Block70;

struct MenuCreationOwnerView;
struct MenuCreationOwnerView {
    char pad0[0x14];
    short menuFlags;
};

struct EntryPakCreateMenuFromParameters;
struct EntryPakCreateMenuFromParameters {
    s16 type;
    char pad[0x22];
};
union ScalarOrVector3;
typedef union ScalarOrVector3 ScalarOrVector3;

union ScalarOrVector3;
union ScalarOrVector3 {
    f32 scalar;
    CVector3 vector;
};

struct ALPlayer_s14;
struct ALPlayer_s14 {
    struct ALPlayer_s14 *next;
    void *clientData;
    ALVoiceHandler handler;
    s32 callTime;
    s32 samplesLeft;
};

struct ALPlayer_s14;
typedef struct ALPlayer_s14 ALPlayer_s14;



struct ListLink;
struct ListLink {
    struct ListLink *next;
    struct ListLink *prev;
};
struct ListLink;
typedef struct ListLink ListLink;




struct EffectBoneNode;
struct EffectBoneNode {
    u32 reservedWord;
    f32 value;
    s32 childValue; /* 0x08 */
    s32 matrixIndex; /* 0x0C */
};

struct PreviewRotationView;
struct PreviewRotationView {
    char pad0[0x1C];
    Triple rotation;
};

struct MenuPlayerScissorRect;
struct MenuPlayerScissorRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct AttachmentEventTableView;
typedef struct AttachmentEventTableView AttachmentEventTableView;

struct NavigationBrainView;
struct NavigationBrainView {
    struct Shared_ActorView *player;
    s32 node;
    char pad8[4];
    s32 nextNode;
    char pad10[0x210];
    s32 state;
    char pad224[8];
    s32 goal;
    char pad230[0xC];
    s32 triggerLatch; /* 0x23C */
    char pad240[0xBC];
    s32 postRouteInitReset;
    char pad300[0x14];
    s32 busy;
    char pad318[8];
    s32 jumpTimer;
};

struct BarrelTargetInfo;
struct BarrelTargetInfo {
    s32 type;
    s32 reservedWordA;
    s32 reservedWordB;
    Triple first;
    Triple second;
    s32 reservedWordC;
    Triple third;
    Triple fourth;
    s32 reservedWordD;
};

struct BarrelTargetInfo;
typedef struct BarrelTargetInfo BarrelTargetInfo;


struct MatrixF;
struct MatrixF {
    f32 m[4][4];
};

struct MenuWidget;
struct MenuWidget {
    char pad0[4];
    struct MenuWidget *sibling;
    struct MenuWidget *child;
    s16 resource;
    u16 kind;
    u8 alpha;
    char pad11[0x1];
    u16 flags;
    s16 x;
    s16 y;
    union { s16 width; s16 w; };
    s16 height;
    char pad1C[0x2C - 0x1C];
    s32 value;
    struct MenuWidget *next;
    s32 reservedWord;
    union { void *text; s32 image; s32 word38; };
    char pad3C[0x8];
    void *cells;
    u8 cellWidth;
    u8 cellHeight;
    u8 columnCount;
    u8 rowCount;
    u8 selectedColumn;
    u8 selectedRow;
    u8 initialColumn;
    u8 initialRow;
    u8 minimumColumn;
    u8 minimumRow;
};

struct MenuWidget;
typedef struct MenuWidget MenuWidget;

struct ScalarFloatView;
typedef struct ScalarFloatView ScalarFloatView;

struct ScalarFloatView;
struct ScalarFloatView {
    f32 value;
};



struct AudioAllocatedPhysicalVoiceView;


struct AudioSynthVoiceAllocatorView;
typedef struct AudioSynthVoiceAllocatorView AudioSynthVoiceAllocatorView;



typedef signed int ( *WidgetEventHandler)(void *, signed int, signed int, signed int, signed int);

struct Field_f32_10;
typedef struct Field_f32_10 Field_f32_10;

struct FadedActorRenderView;
struct FadedActorRenderView {
    char pad0[3];
    s8 pass;
    u32 pad4;
    CVector3 position0;
    u32 pad14[2];
    CVector3 position1;
    u32 pad28[13];
    CQuatern rotation;
    char pad6C[0xB4 - 0x6C];
    void *animation;
    char padB8[0x140 - 0xB8];
    Shared_ParticleLighting lighting[2];
};

struct ResourceSmpFlickerCreateFlickerWidget;
struct ResourceSmpFlickerCreateFlickerWidget {
    char pad[0x10];
    unsigned char value;
    char pad11[0x1B];
    signed int frame;
};

struct Field_s32_2E0;

struct ImageTableEntry;
typedef struct ImageTableEntry ImageTableEntry;

struct ImageTableEntry;
struct ImageTableEntry {
    s32 offset;
    u8 tag[4];
};

struct ControllerPortView;
struct ControllerPortView {
    u8 pad0[4];
    s8 controllerPort;
};

struct ControllerPortView;
struct ControllerPortOwnerView;
struct ControllerPortOwnerView {
    u8 pad0[0x20];
    struct ControllerPortView *controller;
};

struct ControllerPortOwnerView;
typedef struct ControllerPortOwnerView ControllerPortOwnerView;

struct MapBlockAllocatorView;
typedef struct MapBlockAllocatorView MapBlockAllocatorView;

struct PlayerStateDirtyOwnerView;
struct PlayerStateDirtyOwnerView {
    char pad0[0x85C];
    s32 playerStateDirty;
};


struct UnitMtx;
typedef struct UnitMtx UnitMtx;

struct UnitMtx;
struct UnitMtx {
    s32 m[16];
};


struct __OSInode;
typedef struct __OSInode __OSInode;

union __OSInodeUnit;
union __OSInodeUnit {
    struct {
        u8 bank;
        u8 page;
    } inode_t;
    u16 ipage;
};

union __OSInodeUnit;
typedef union __OSInodeUnit __OSInodeUnit;

struct __OSInode;
struct __OSInode {
    __OSInodeUnit inode_page[128];
};

struct TextLayerRect;
typedef struct TextLayerRect TextLayerRect;

struct BoneRotationIndexPair;
typedef struct BoneRotationIndexPair BoneRotationIndexPair;


struct Node75;
typedef struct Node75 Node75;

struct TrackAngleKindView;
struct TrackAngleKindView {
    char pad0[0x8];
    char kind;
};


struct PlayerCharacterKindView;
struct PlayerCharacterKindView {
    char pad0[0x80];
    s8 characterKind;
};

struct ResourceManagerState;
struct ResourceManagerState {
    s32 active;
    s32 count;
};

struct Arg1Struct;
typedef struct Arg1Struct Arg1Struct;

struct Arg1Struct;
struct Arg1Struct {
    char pad0[0x1C];
    s32 player;
    char pad1[0x20 - 0x1C - 4];
    s32 controller;
};


union ObjectLinks4_3;
typedef union ObjectLinks4_3 ObjectLinks4_3;

union ObjectLinks4_3;
union ObjectLinks4_3 {
    void * v0;
    char * v1;
};

struct AudioVoicePhysicalLinkView;
struct AudioVoicePhysicalLinkView {
    char pad0[0x8];
    ObjectLinks4_3 pvoice;
};


struct ControllerButtonFlagsView;
struct ControllerButtonFlagsView {
    char pad0[0xB0];
    s32 buttons;
};


struct ResourceSmpFlickerCreateFlickerWidget;
typedef struct ResourceSmpFlickerCreateFlickerWidget ResourceSmpFlickerCreateFlickerWidget;

struct IntPair;
struct IntPair {
    int first;
    int second;
};

struct ViewPositionZView;
struct ViewPositionZView {
    char pad0[0x130];
    f32 positionZ;
};



struct Handler;
struct Handler {
    char pad0[4];
    s16 id;
    char pad6[6];
    union {
        s32 (*targeted)(void *actor, struct Handler *entry, s32 target);
        s32 (*plain)(void *actor, struct Handler *entry);
    } handleC;
    s32 (*handle10)(void *actor, struct Handler *entry);
    s32 (*handle14)(void *actor, struct Handler *entry);
};

struct DialogPlayerState;
struct DialogPlayerState {
    int resource;
    int request;
    int state;
    int group;
    int song;
    int speed;
    int volume;
    int soundId;
};


struct ALFilter_s14;
typedef struct ALFilter_s14 ALFilter_s14;

struct ALFilter_s14;
struct ALFilter_s14 {
    struct ALFilter_s14 *source;
    ALCmdHandler handler;
    void *setParam;
    s16 inp;
    s16 outp;
    s32 type;
};


extern int g_resourceSlotLockState;

struct Key;
struct Key {
    u8 text[20];
};

struct Key;
struct SmpButtonOwnerView;
struct SmpButtonOwnerView {
    char pad[0x38];
    struct Key *selected;
};

struct ControllerInitStatusBytes;
struct ControllerInitStatusBytes {
    u16 id;
    u8 team;
    u8 slot;
};

struct ControllerInitStatusBytes;
typedef struct ControllerInitStatusBytes ControllerInitStatusBytes;

struct WidgetFlagsView;
struct WidgetFlagsView {
    unsigned char padding_0[16];
    unsigned char alpha;
};

struct NavigationActorBrainView;
typedef struct NavigationActorBrainView NavigationActorBrainView;


struct Field_u16_14;
struct Field_u16_14 {
    char pad[0x14];
    u16 value;
};

struct WidgetLabelTextView;
struct WidgetLabelTextView {
    char pad0[0x38];
    void * text;
};

struct Block24;
typedef struct Block24 Block24;


struct PlaneEquation;
struct PlaneEquation {
    CVector3 normal;
    f32 distance;
};

struct PlaneEquation;
typedef struct PlaneEquation PlaneEquation;

struct Extra;
struct Extra {
    s32 id;
    f32 scale;
};

struct Block;
struct Block {
    u8 pad000[0x100];
    s32 flags;
    u8 pad104[0x1DC];
    s32 value;
};

struct Block;
typedef struct Block Block;

struct MenuControllerSelectionView;

struct Vec3Words;
struct Vec3Words {
    s32 w[3];
};



struct PlayerViewModeView;
typedef struct PlayerViewModeView PlayerViewModeView;

extern int g_resourceHeapLockUsers;


struct StateFlags;
typedef struct StateFlags StateFlags;

struct StateFlags;
struct StateFlags {
    u16 value;
    u16 flags;
};



struct Desc;
struct Desc {
    char pad[0x108];
    s32 caps[4];
};

struct PlayerSettingsOwnerView;
struct PlayerOptions;
struct PlayerSettingsOwnerView {
    char pad[0x5D8];
    struct PlayerOptions *settings; /* its name text comes first */
};




struct AnimationResourceHandleView;
typedef struct AnimationResourceHandleView AnimationResourceHandleView;




struct StateFrontendUpdateOptionsPageExit;
struct StateFrontendUpdateOptionsPageExit {
    void *menu;
    char pad4[0x20 - 4];
    s32 value;
};

struct HudStatusShared_MatchRules;
typedef struct HudStatusShared_MatchRules HudStatusShared_MatchRules;

struct PlayerMovementScalarView;

struct ParamsRecAt8V1;
typedef struct ParamsRecAt8V1 ParamsRecAt8V1;

struct Node75;
struct Node75 {
    u16 reservedHalf;
    u16 flags; /* +0x02: Scene_FindFloorPolygon, mask0x40 */
    CVector3 *prev;
    CVector3 *cur;
    CVector3 *next;
    u8 reserved10[0x10]; /* ROM advances terrain records by0x20 */
};

struct Field_s32_2E0;
typedef struct Field_s32_2E0 Field_s32_2E0;

extern int g_difficulty;


struct InventorySlot;
struct InventorySlot {
    u8 available;
    u8 slot;
};

struct InventorySlot;
typedef struct InventorySlot InventorySlot;

struct WeaponUnlockModelView;
typedef struct WeaponUnlockModelView WeaponUnlockModelView;

struct WeaponUnlockModelView;
struct WeaponUnlockModelView {
    char pad0[0x4C];
    int reservedWord;
};

struct ObjRecAt40V1;
typedef struct ObjRecAt40V1 ObjRecAt40V1;


struct PlayerEyePositionView;
struct PlayerEyePositionView {
    char pad0[0x128];
    CVector3 eyePosition;
};


struct ListScreenRecord;
typedef struct ListScreenRecord ListScreenRecord;

struct ListScreenRecord;
struct ListScreenRecord {
    char pad0[0x78];
    u8 active;
    char pad79[6];
    u8 m_nController; /* +0x7F */
    s8 m_nCharacter; /* +0x80 */
    u8 variant; /* +0x81: selected costume */
    char pad82[0xF];
    u8 m_IsBot;
    char pad92[0x4];
};


struct MenuLabelPointerView;
typedef struct MenuLabelPointerView MenuLabelPointerView;


extern IntrusiveList g_spawnedActorList;


extern float g_motionTrackDecodeRangeStart;


struct PulsingMenuSpriteView;
struct PulsingMenuSpriteView {
    char pad0[0x14];
    int spriteResource;
    char pad14[0x1C - 0x14 - sizeof(int)];
    int pulsePhase;
};

struct CROMInitialOrientation_t;
struct CROMInitialOrientation_t {
    CVector3 position;
    s16 m_RotX;
    char padC[0xE - 0xC - sizeof(s16)];
    s16 m_RotY;
    char padE[0x10 - 0xE - sizeof(s16)];
    s16 m_RotZ;
    char pad10[0x12 - 0x10 - sizeof(s16)];
    s16 m_RotW;
};



struct Object6C;
struct Object6C {
    char pad[0x6C];
    s32 value;
};

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
struct Rider;
struct Settings;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;




struct MenuLocalizedTextItemView;
typedef struct MenuLocalizedTextItemView MenuLocalizedTextItemView;

struct StateBlock;
typedef struct StateBlock StateBlock;

struct TextBoundsText;
struct MenuStyle;
/* The draw style menu item callbacks receive last: alpha and fade scale the item's intensity. */
struct MenuStyle {
    /* The same record Menu_DrawStyledMenuText draws through as its fourth argument (StyledMenuTextPanel), and
       Setup_DrawNameCursor reads its id at +0x1C. */
    s16 state;
    s16 x; /* 0x02 */
    s16 y; /* 0x04 */
    char pad6[6];
    struct TextBoundsText *entries; /* 0x0C */
    s32 count; /* 0x10 */
    char pad14[0x1C - 0x14];
    s32 id; /* 0x1C */
    char pad20[0x30 - 0x20];
    f32 alpha; /* 0x30 */
    f32 fade; /* 0x34 */
    s32 shadowEnabled;
    s32 panelDisablesShadow;
};

struct MusicPreviewOwnerView;
struct MusicPreviewOwnerView {
    char pad[0x5D0];
    s32 value;
};

struct Holder;
struct MusicPreviewOwnerView;
struct Holder {
    char pad[0x1C];
    struct MusicPreviewOwnerView *owner;
};

struct CallbackStateC_4;
typedef struct CallbackStateC_4 CallbackStateC_4;

struct Field_void_4;
struct Field_void_4 {
    char pad[0x4];
    void * value;
};

struct SequenceTicksPerQuarterView;
struct SequenceTicksPerQuarterView {
    char pad18[0x18];
    s16 ticksPerQuarter;
};



struct MenuMarker;
struct MenuMarker {
    char pad[0x10];
    u8 alpha;
    char pad11[0x14 - 0x11];
    s16 x;
};

struct PackedMaterialHalfwordView;
typedef struct PackedMaterialHalfwordView PackedMaterialHalfwordView;

struct Draw;
typedef struct Draw Draw;


struct StateFrontendScrollResultsBackward;




struct Polytrak2QuantizationRange;
typedef struct Polytrak2QuantizationRange Polytrak2QuantizationRange;

struct Polytrak2QuantizationRange;
struct Polytrak2QuantizationRange {
    u32 value;
    f32 start;
    f32 delta;
};

struct MenuRules;
typedef struct MenuRules MenuRules;

struct Extra;
typedef struct Extra Extra;

struct AudioSynthVoiceAllocatorView;
struct AudioSynthVoiceAllocatorView {
    void *head;
    ListLink pFreeList;
    ListLink pAllocList;
    ListLink pLameList;
    s32 paramSamples;
};


struct ActorKindDefinitionPointerView;
typedef struct ActorKindDefinitionPointerView ActorKindDefinitionPointerView;

struct MenuTextOwnerView;
typedef struct MenuTextOwnerView MenuTextOwnerView;



extern int g_playerCount;


struct ProfileWeaponRowEntry;
struct ProfileWeaponRowEntry {
    s32 value;
    char pad[28 - 4];
};

struct PlayerCharacterKindView;
typedef struct PlayerCharacterKindView PlayerCharacterKindView;


struct BoneRotationTrackView;
typedef struct BoneRotationTrackView BoneRotationTrackView;


struct FrontendTextureTimerEntry;
struct FrontendTextureTimerEntry {
    s32 id;
    s16 retained;
    s16 unused;
};

struct Field_Vec_18;
struct Field_Vec_18 {
    char pad[0x18];
    CVector3 value;
};

struct PackedMaterialHalfwordView;
struct PackedMaterialHalfwordView {
    char pad0[0x2];
    u16 spreadHighWord;
};

extern int g_primaryRandomSeed;




struct CROMInitialOrientation_t;
typedef struct CROMInitialOrientation_t CROMInitialOrientation_t;

union WordOrFloat;
typedef union WordOrFloat WordOrFloat;

union WordOrFloat;
union WordOrFloat {
    s32 word;
    f32 value;
};

struct RecordCMenuProfileUpdateProfileModeLabel;
struct RecordCMenuProfileUpdateProfileModeLabel {
    char pad[0x7B];
    s8 mode;
};

struct OwnerCMenuProfileUpdateProfileModeLabel;
struct RecordCMenuProfileUpdateProfileModeLabel;
struct OwnerCMenuProfileUpdateProfileModeLabel {
    char pad[0x5D8];
    struct RecordCMenuProfileUpdateProfileModeLabel *record;
};
struct MenuCMenuProfileUpdateProfileModeLabel;
struct OwnerCMenuProfileUpdateProfileModeLabel;


struct ChoiceMenuCellView;
struct ChoiceMenuCellView {
    char pad[0x16];
    s16 transitionTimer;
    s16 reservedHalf;
    s16 transitionDuration;
};

struct ChoiceMenuCellView;
struct ObjMenuUpdateSixChoiceMenu;
struct ObjMenuUpdateSixChoiceMenu {
    char pad[0x44];
    struct ChoiceMenuCellView *transitionCell;
};
struct ChoiceMenuCellView;
struct ObjMenuUpdateSixChoiceMenu;
struct ChoiceMenuState;
struct ChoiceMenuState {
    struct ObjMenuUpdateSixChoiceMenu *slider;
    s32 labelFlicker;
    struct ChoiceMenuCellView *transitionCell;
    s32 transitionTimer;
    s32 nextScreen;
};

struct CachedPlayerModelView;
typedef struct CachedPlayerModelView CachedPlayerModelView;

struct PlayerBodyPositionYawView;
typedef struct PlayerBodyPositionYawView PlayerBodyPositionYawView;

struct Access_s32_5C;
struct Access_s32_5C {
    char pad[0x5C];
    s32 field;
};

struct GameModeEnableView;
struct GameModeEnableView {
    char pad0[0x1D];
    u8 local;
};


struct FrontendResourceScreenEntryView;
typedef struct FrontendResourceScreenEntryView FrontendResourceScreenEntryView;



struct __OSDir;
typedef struct __OSDir __OSDir;

struct FrontendResourceScreenEntryView;
struct FrontendResourceScreenEntryView {
    char pad0[0x8];
    void * reservedPointer;
};

struct BufferPool;
struct BufferPool {
    s16 count;
    FrontendResourceScreenEntryView *primary;
    FrontendResourceScreenEntryView *secondary;
    u16 *flags;
    s16 *refs;
    s32 dirty;
};



struct ConversionImageView;
typedef struct ConversionImageView ConversionImageView;

struct ControllerAxesView;
struct ControllerAxesView {
    char pad0[0xC6];
    s8 x;
    s8 y;
};

struct CROMEventEntry_t;
struct IntPair;
struct CROMEventEntry_t {
    u16 frame;
    u16 effect;
    s16 bone;
    s16 pad6;
    CVector3 local;
    struct IntPair params;
};

struct PlayerProfileStatusView;
struct PlayerProfileStatusView {
    char pad0[0x80];
    s8 kind;
    char pad81[0x13];
    u8 display;
};

struct __OSContRequesFormat;
struct __OSContRequesFormat {
    u8 dummy;
    u8 txsize;
    u8 rxsize;
    u8 cmd;
    u8 typeh;
    u8 typel;
    u8 status;
    u8 dummy1;
};


struct WeaponInfo;
struct WeaponInfo {
    void **resource;
    u16 model;
    char pad6[2];
    s16 capacity;
    char padA[2];
    s16 alternate;
    char padE[6];
    u32 flags; /* +0x14: weapon pickup availability */
    f32 chargeRate; /* 0x18 */
    char pad1C[4];
    s16 *weaponClass;
    s16 *alternateClass;
    s16 *thirdClass;
    s16 *computerClasses[3];
    char pad38[0xC];
    f32 scopeBounds[4]; /* 0x44 */
    struct AiBehaviourTable *animation; /* 0x54 */
    s32 animationCount;
};

struct SynthOutputRateView;
typedef struct SynthOutputRateView SynthOutputRateView;

struct Slot;
typedef struct Slot Slot;

struct BoneRotationIndexPair;
struct BoneRotationIndexPair {
    s16 translation;
    short rotationIndex;
};

struct SpawnedEffectMotionView;
typedef struct SpawnedEffectMotionView SpawnedEffectMotionView;

struct Field_Vec_18;
typedef struct Field_Vec_18 Field_Vec_18;


struct InstanceHdr;
struct InstanceHdr {
    union {
        s32 w[5];
        struct { s32 header[2]; CVector3 position; } spatial;
    };
};


extern int g_audioContextInitialized;

struct BarrelTrackActorView;
typedef struct BarrelTrackActorView BarrelTrackActorView;

struct __OSDir;
struct __OSDir {
    u32 game_code;
    u16 company_code;
    __OSInodeUnit start_page;
    u8 status;
    s8 reserved;
    u16 data_sum;
    u8 ext_name[4];
    u8 game_name[16];
};

struct GlyphBuffer;
typedef struct GlyphBuffer GlyphBuffer;


struct Part;
struct Part {
    char pad[0x78];
    u8 active;
};

struct PlayerFrontendCountOpenPlayerSlots;
struct PlayerFrontendCountOpenPlayerSlots {
    char pad0[0x78];
    u8 active;
    char pad79[0x96 - 0x79];
};

struct TextEntry;
struct TextEntry {
    s32 id;
    char **text;
};


struct Label;
struct Label {
    char pad0[0x38];
    char *text;
};

struct ViewPositionXView;
typedef struct ViewPositionXView ViewPositionXView;

struct SpawnedEffectMotionView;
struct SpawnedEffectMotionView {
    unsigned char pad0[0x150];
    f32 radius;
    f32 height;
};

struct Shape;
struct Shape {
    s32 flags;
    s8 enabled;
};

struct Shape;
typedef struct Shape Shape;

struct UnitVtx;
typedef struct UnitVtx UnitVtx;


struct ActorBarrelIsTargetInViewCone;
typedef struct ActorBarrelIsTargetInViewCone ActorBarrelIsTargetInViewCone;

struct Shield;
struct Shield {
    char pad0[0x66];
    char effectKind; /* 0x66: impact response variant (4 or 5) */
    u8 reserved67;
    f32 factor;
};

struct Header44;
typedef struct Header44 Header44;

struct Key;
typedef struct Key Key;






struct TripleEventsFireWithinHeightRange;
typedef struct TripleEventsFireWithinHeightRange TripleEventsFireWithinHeightRange;

struct PlayerRecord;
typedef struct PlayerRecord PlayerRecord;

struct Shared_HudView;
struct Shared_HudView {
    char pad0[0x24];
    s32 flags;
    char pad28[0x274];
    f32 width;
    f32 height;
    f32 x;
    f32 y;
};






struct PackedMatrixWords;
struct PackedMatrixWords {
    u32 upper[8];
    u32 lower[8];
};



struct ViewPositionXView;
struct ViewPositionXView {
    char pad0[0x128];
    f32 positionX;
};

struct OSPifRam;
struct OSPifRam {
    u32 ramarray[15];
    u32 pifstatus;
};

struct EffectColorContribution;
typedef struct EffectColorContribution EffectColorContribution;

struct EntryPakCreateMenuFromParameters;
struct Dialog;
struct Dialog {
    struct EntryPakCreateMenuFromParameters *entries;
    s16 count;
    char pad6[0x1A];
    signed int value;
};

struct RecordFrontendSetPreviewModel;
struct RecordFrontendSetPreviewModel {
    s32 count;
    char pad4[0x34 - 4];
    s32 handle;
};

struct Shared_PakMenu;
struct PakMenuSlot;


struct MenuPanelRoot;
struct MenuPanelRoot {
    char pad0[0xCC];
    s32 resource;
    char padD0[4];
    s32 resourceSize;
    s32 selected;
    s32 selectedResource;
    s32 window;
};

struct ReadWord;
struct ReadWord {
    s32 word;
    u8 byte;
};


struct MatchMenuObjects;
struct MatchMenuObjects {
    char pad0[0x17F0];
    s32 transition;
};


struct ActorAnimationEventTable;
struct ActorAnimationEventTable {
    int entrySize;
    int entryCount;
    u8 records[0]; /* Variable-stride model/event records follow the two-word header. */
};


struct PortalLinkAvailabilityView;
typedef struct PortalLinkAvailabilityView PortalLinkAvailabilityView;




struct WidgetLabelTextView;
typedef struct WidgetLabelTextView WidgetLabelTextView;

struct Queue;
struct Queue {
    char pad[0x14];
    s32 items[4];
};

struct HashNode;
struct HashNode {
    s32 key;
    void *value;
    s32 reservedWord1;
    struct HashNode *next;
};

struct InstanceHdr;
typedef struct InstanceHdr InstanceHdr;



struct VoiceMatchingKeyView;
typedef struct VoiceMatchingKeyView VoiceMatchingKeyView;


struct Params;
typedef struct Params Params;





struct MenuRules;
struct MenuRules {
    char pad0[0x18];
    void *message; /* osCreateMesgQueue single-message backing store */
    s32 locked;
};

struct PlayerViewModeView;
struct PlayerViewModeView {
    char pad0[0x24];
    s32 viewMode;
};

struct TextEntry;
typedef struct TextEntry TextEntry;


struct ObjRecAt28V2;
typedef struct ObjRecAt28V2 ObjRecAt28V2;



struct QuadN64EngDrawNumericWidgetChildren;
typedef struct QuadN64EngDrawNumericWidgetChildren QuadN64EngDrawNumericWidgetChildren;

struct QuadN64EngDrawNumericWidgetChildren;
struct QuadN64EngDrawNumericWidgetChildren {
    u32 x;
    u32 y;
    u32 z;
    u32 w;
};

struct Params;
struct Params {
    Triple v;
    s32 w;
};

struct CacheResourceNode;
typedef struct CacheResourceNode CacheResourceNode;


struct ActorDefinitionFlagsView;
typedef struct ActorDefinitionFlagsView ActorDefinitionFlagsView;


struct ActorInstanceHeader;
typedef struct ActorInstanceHeader ActorInstanceHeader;

struct DamagePacketWords;
struct DamagePacketWords {
    s32 source;
    char pad0[0x4 - 0x0 - sizeof(s32)];
    s32 damage;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    s32 radiusBits;
    char pad8[0xC - 0x8 - sizeof(s32)];
    s32 damageFlags;
    char padC[0x10 - 0xC - sizeof(s32)];
    s32 shield;
};

struct UnitVtx;
struct UnitVtx {
    s16 x;
    s16 y;
    s16 z;
    u16 flag;
    s16 s;
    s16 t;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

extern int g_staticObjectResourceSerial;





extern unsigned char g_unreadByte;

struct ActorInstanceHeader;
struct ActorInstanceHeader {
    s32 w[2];
    CVector3 position;
    s32 remaining[15];
};

struct SequencePromptRequestView;
typedef struct SequencePromptRequestView SequencePromptRequestView;

struct SequencePromptRequestView;


struct NumericWidgetChildView;
typedef struct NumericWidgetChildView NumericWidgetChildView;

extern int g_resourceLoadBusyPriority;

struct NavigationActorWordBrainView;
struct NavigationActorWordBrainView {
    char pad0[0x1454];
    s32 * brainWords;
};

struct Limit;
struct Limit {
    char pad[0x16];
    s16 limit;
};

struct TripleEventsFireWithinHeightRange;

struct World;
struct World {
    s32 resultFlagsA;
    char pad4[0x84];
    s32 resultFlagsB;
    char pad8C[0x4];
    signed int resource;
    char pad94[0x8];
    s32 resultFlagsC;
    char padA0[0x10];
    s32 resultFlagsD;
    char padB4[0x10];
    s32 resultFlagsE;
    char padC8[0x34];
    s32 state;
    s32 resultFlagsF;
    char pad104[0x34];
    void *placedActors;
    signed int createdActorCount;
    signed int actorCapacity;
    char pad144[0xE14];
    signed int kind1Cursor;
    char padF5C[0x1A4B0];
    signed int placedObjectGroup;
    char pad1B410[0xC];
    signed int placementInitialized;
    char nearestPlacementResult[20]; /* Scene_FindNearestPlacedObject output record */
    signed int nearestPlacedObjectKey;
    char pad1B438[0x1DC];
    float spawnOffsetX;
    float spawnOffsetY;
    float spawnOffsetZ;
    struct SceneDefinitionActorView *list[16];
    signed int count;
};
typedef struct World World;


struct Field;
struct Field {
    char pad[0x14];
    char **text;
    char pad18[0x4];
    signed int value;
};

struct PlayerBodyPositionYawView;
struct PlayerBodyPositionYawView {
    char pad0[0x8];
    CVector3 position;
    char pad14[4];
    struct Model *model; /* +0x18: actor definition */
    char pad1C[0x1C];
    u32 flags; /* +0x38 */
    char pad3C[0x30];
    f32 yaw;
};

struct Field_void_80;


struct GameModeEnableView;
typedef struct GameModeEnableView GameModeEnableView;

struct MatrixF;
typedef struct MatrixF MatrixF;

struct PlayerEyePositionView;
typedef struct PlayerEyePositionView PlayerEyePositionView;


struct MapBlockAllocatorView;

struct TargetPakSelectPromptKindEight;
struct TargetPakSelectPromptKindEight {
    char pad[0x120];
    s32 flags;
};
struct MenuPromptKindView;
struct TargetPakSelectPromptKindEight;
struct MenuPromptKindView {
    char pad[0xC];
    struct TargetPakSelectPromptKindEight *target;
};

struct ConversionImageView;
struct ConversionImageView {
    char pad0[0x8];
    short width;
};

struct Header;
struct Header {
    u8 data[204];
};


struct Vec3Words;
typedef struct Vec3Words Vec3Words;





struct StateMenuCancelSixChoiceMenu;
struct StateMenuCancelSixChoiceMenu {
    void *first;
    char pad4[0x10 - 4];
    s32 value;
};

struct HudStatusShared_MatchRules;
struct HudStatusShared_MatchRules {
    char pad0[0x14];
    f32 timeLimit; /* +0x14 */
    char pad18[8];
    s32 hideHud;
    s32 teams;
    char pad28[0x4];
    s32 teamScores[5];
    s32 squadScores[5];
    s32 countRule;
    char pad58[0x20];
    s32 squads;
    char pad7C[0x1C];
    s32 markers;
};

struct Shield;
typedef struct Shield Shield;

struct SmpControlItemView;
struct SmpControlItemView {
    s32 pad0;
    struct SmpControlItemView *next;
    char pad8[0xE - 8];
    u16 kind;
    u8 alpha;
};

struct Slot;
struct Slot {
    char data[24];
};

struct MenuPanelRoot;
typedef struct MenuPanelRoot MenuPanelRoot;

typedef void ( *VoidCallback)(void);

struct __OSContRequesFormat;
typedef struct __OSContRequesFormat __OSContRequesFormat;

struct ThreadIdentifierView;
typedef struct ThreadIdentifierView ThreadIdentifierView;

struct ReadWord;
typedef struct ReadWord ReadWord;

extern int g_debugLinkRetryLimit;

struct Buf16;
typedef struct Buf16 Buf16;


struct ResourceHandleLinkView;
typedef struct ResourceHandleLinkView ResourceHandleLinkView;

struct Buf16;
struct Buf16 {
    s16 count;
    s16 _pad2;
    s32 value;
    s32 _pad8;
    s32 _padC;
};

struct ParticleRibbonStorageView;
typedef struct ParticleRibbonStorageView ParticleRibbonStorageView;

struct Table;
struct Table {
    s32 reservedWord;
    s32 count;
    s32 deltas[1];
};

struct Request;
struct Request {
    s16 type;
};


struct ControllerAxesView;
typedef struct ControllerAxesView ControllerAxesView;

struct AudioVoiceChannelFilterView;
struct AudioVoiceChannelFilterView {
    struct AudioVoiceChannelFilterView *source;
    void *handler;
    ALSetParam setParam;
};


struct Field_u16_14;
typedef struct Field_u16_14 Field_u16_14;


struct AudioVoiceChannelFilterView;
struct AudioAllocatedPhysicalVoiceView;
struct AudioAllocatedPhysicalVoiceView {
    ListLink node;
    struct ALVoice_s *vvoice;
    struct AudioVoiceChannelFilterView *channelKnob;
    char pad10[0xD8 - 0x10];
    s32 offset;
};


struct PakActionLabelView;
struct PakActionLabelView {
    char pad[0x14];
    char *text;
};

struct Header44;
struct Header44 {
    s32 words[11];
};

struct ImageHeader;
struct ImageHeader {
    char pad0[2];
    unsigned char widthShift;
    unsigned char heightShift;
    char pad4[0x1D - 4];
    unsigned char scale;
    char pad1E[0x21 - 0x1E];
    unsigned char width;
    unsigned char height;
    unsigned char format;
    char data[1];
};
struct ImageHeader;


struct GameImage {
    char pad0[8];
    struct ImageHeader *header;
    s32 primaryData;
    s32 secondaryData;
    char pad14[0x3C - 0x14];
    s32 flags;
};
typedef struct GameImage GameImage;

extern float k_eventEmitterAngleConstants;

struct ResourceShortIdView;
typedef struct ResourceShortIdView ResourceShortIdView;




struct SoundSlotHandleView;


struct ListPreviousLinkView;
typedef struct ListPreviousLinkView ListPreviousLinkView;

struct ObjalAuxBusParam;
struct ObjalAuxBusParam {
    char pad14[0x14];
    s32 count;
    char pad18[0x4];
    s32 *base;
};

struct NavigationBrainView;
typedef struct NavigationBrainView NavigationBrainView;

struct CachedPlayerModelView;
struct CachedPlayerModelView {
    char pad0[0x8];
    f32 positionX;
    char pad8[0x10 - 0x8 - sizeof(f32)];
    f32 positionZ;
    char pad10[0xC4 - 0x10 - sizeof(f32)];
    s32 resourceKey;
    char padC4[0xD0 - 0xC4 - sizeof(s32)];
    s32 resourceFlags;
    char padD0[0x100 - 0xD0 - sizeof(s32)];
    s32 renderFlags;
    char pad100[0x1D8 - 0x100 - sizeof(s32)];
    void * player;
};

struct TrackRequestIds;
typedef struct TrackRequestIds TrackRequestIds;








struct PreviewRotationView;
typedef struct PreviewRotationView PreviewRotationView;

struct Work56EC8;
struct Work56EC8 {
    void *owner;
    s16 id;
    char pad6[2];
    char payload[64];
    void *base;
    s32 offset;
};

struct MenuSettings;
typedef struct MenuSettings MenuSettings;


struct PackedMatrixWords;
typedef struct PackedMatrixWords PackedMatrixWords;

struct FrontendArchiveHandleView;
typedef struct FrontendArchiveHandleView FrontendArchiveHandleView;


struct MenuTextOwnerView;
struct MenuTextOwnerView {
    char pad0[0x8];
    s32 flags;
};


struct ResourceHandleLinkView;
struct ResourceHandleLinkView {
    char pad0[0x10];
    void * resourceHandle;
};

struct PulsingMenuSpriteView;
typedef struct PulsingMenuSpriteView PulsingMenuSpriteView;

struct Header;
typedef struct Header Header;

extern int g_geometryAntialiasingEnabled;

struct MenuOptionLabelView;
struct MenuOptionLabelView {
    char a[8];
    s32 flags;
    char b[8];
    char *label;
};

struct StateBlock;
struct StateBlock {
    char pad0[0x84];
    s32 flickerPending;
};

struct Shared_GameMode;
typedef struct Shared_GameMode Shared_GameMode;

extern int g_modelEditorApplyToAllRecords;

struct VoiceMatchingKeyView;

struct Args;
struct Args {
    u32 words[10];
};


struct Field_f32_10;
struct Field_f32_10 {
    char pad[0x10];
    f32 value;
};




extern int g_controllerPakChannelStates[];

struct HashNode;
typedef struct HashNode HashNode;



struct Record;
typedef struct Record Record;

extern float g_creditsScrollPosition;


struct AudioSynthParamSamplesView;
struct AudioSynthParamSamplesView {
    unsigned char padding_0[28];
    int paramSamples;
};


struct BufferPool;
typedef struct BufferPool BufferPool;

struct Request;
typedef struct Request Request;

struct ListPreviousLinkView;
struct ListPreviousLinkView {
    void * previous;
};








struct DamagePacketWords;
typedef struct DamagePacketWords DamagePacketWords;

struct ActorKindDefinitionPointerView;
struct ActorKindDefinitionPointerView {
    char pad0[0x18];
    s32 * definition;
};

struct ResourceShortIdView;
struct ResourceShortIdView {
    char pad0[0x6];
    unsigned short resourceId;
};



struct Shared_HudView;
typedef struct Shared_HudView Shared_HudView;


struct MenuOptionLabelView;
typedef struct MenuOptionLabelView MenuOptionLabelView;

struct BoneRotationTrackView;
struct BoneRotationTrackView {
    char * boneIndexPairs;
    char pad0[0x4 - 0x0 - sizeof(char*)];
    char * initialOrientations;
    void * translationFrames;
    void * rotationFrames;
    char padC[0x10 - 0xC - sizeof(void*)];
    s32 rotationFirst;
    char pad10[0x14 - 0x10 - sizeof(s32)];
    s32 rotationNext;
    s32 translationFirst;
    s32 translationNext;
    s32 frameBlend;
};



struct Link;
struct Link {
    unsigned short from;
    unsigned short to;
    unsigned char type;
};

struct CollisionInfo;
struct CollisionInfo {
    s32 w[8];
};

struct MenuLabelPointerView;
struct MenuLabelPointerView {
    char pad0[0x14];
    void * label;
};

struct OSPifRam;
typedef struct OSPifRam OSPifRam;


struct NavigationActorWordBrainView;
typedef struct NavigationActorWordBrainView NavigationActorWordBrainView;



struct SmpOverlaySlotsView;
struct SmpOverlaySlotsView {
    char pad[0x4C];
    struct WidgetNode *values[1];
};

struct ChoiceMenuCellView;
typedef struct ChoiceMenuCellView ChoiceMenuCellView;

struct ScalarPair;
struct ScalarPair {
    f32 first;
    f32 second;
};


struct Pair14;
struct Pair14 {
    char pad[0x14];
    s16 first;
    s16 second;
};

struct ObjRecAt40V1;
struct ObjRecAt40V1 {
    char p[64];
    s32 value;
};





struct FrontendKeySlotEntry;
struct FrontendKeySlotEntry {
    s32 key;
    char pad[0x70 - 4];
};


struct Block24;
struct Block24 {
    s32 words[6];
};



struct AudioPhysicalVoiceOffsetView;
typedef struct AudioPhysicalVoiceOffsetView AudioPhysicalVoiceOffsetView;


struct List;
struct List {
    char pad0[0x48];
    u8 visibleX;
    u8 visibleY;
    u8 maxX;
    u8 maxY;
    u8 cursorX;
    u8 cursorY;
    u8 scrollX;
    u8 scrollY;
    u8 minX;
    u8 minY;
};

struct ParticleRibbonStorageView;
struct ParticleRibbonStorageView {
    char pad0[0x7528];
    void * ribbonStorage;
};


struct MatchMenuObjects;
typedef struct MatchMenuObjects MatchMenuObjects;


/* Per-button tap, age, repeat and hold counters consumed by the input update. */
typedef struct ControllerButtonHistory {
    s8 taps;
    s8 age;
    s8 repeat;
    s8 held;
} ControllerButtonHistory;

struct ControllerProfile;
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

struct Args;
typedef struct Args Args;

struct TrackAngleKindView;
typedef struct TrackAngleKindView TrackAngleKindView;


struct ActorBarrelIsTargetInViewCone;
struct ActorBarrelIsTargetInViewCone {
    char pad0[8];
    CVector3 position;
    char pad14[0x70 - 0x14];
    f32 eye;
};

struct WorldSceneDispatchEnabledEntityTrigger;
typedef struct WorldSceneDispatchEnabledEntityTrigger WorldSceneDispatchEnabledEntityTrigger;

struct BreakableDamageScaleView;
typedef struct BreakableDamageScaleView BreakableDamageScaleView;

extern int g_geometryTranslucentRenderMode;

struct ActorYawView;
typedef struct ActorYawView ActorYawView;

struct Link;
typedef struct Link Link;

struct Draw;
struct Draw {
    s32 drawModel;
    s32 updateAnimation;
    s32 allocationMode; /* 0x08: resource allocation request */
    void **model;
    char reserved10[0x10];
    IntrusiveList recycled; /* 0x20 */
};

struct Field_void_4;
typedef struct Field_void_4 Field_void_4;


struct MenuControllerSelectionView;
typedef struct MenuControllerSelectionView MenuControllerSelectionView;


struct SynthOutputRateView;
struct SynthOutputRateView {
    char pad0[0x44];
    s32 outputRate;
};

struct TextEntryBufferView;
struct TextEntryBufferView {
    char pad[0x14];
    u8 **textBuffer;
};

struct TrackRequestIds;
struct TrackRequestIds {
    char pad0[0x4];
    unsigned short trackId;
    char pad4[0xA - 0x4 - sizeof(unsigned short)];
    unsigned short variantId;
};

struct WorldSceneDispatchEnabledEntityTrigger;
struct WorldSceneDispatchEnabledEntityTrigger {
    u8 padding000[0x80];
    void *levels; /* 0x80 */
    void *secondaryLevels; /* 0x84 */
    u8 padding088[0x1B384];
    s32 level; /* 0x1B40C */
};


struct Field_void_80;
typedef struct Field_void_80 Field_void_80;

struct CacheResourceNode;
struct CacheResourceNode {
    s32 data;
    s32 reservedWord;
    s32 references;
    u32 flags;
};

struct TextEntryBufferView;
typedef struct TextEntryBufferView TextEntryBufferView;


struct HudStatusShared_Settings;
typedef struct HudStatusShared_Settings HudStatusShared_Settings;





struct PlayerMovementScalarView;
typedef struct PlayerMovementScalarView PlayerMovementScalarView;


struct MenuStyle;
typedef struct MenuStyle MenuStyle;

struct Access_s32_5C;
typedef struct Access_s32_5C Access_s32_5C;

struct ViewPositionZView;
typedef struct ViewPositionZView ViewPositionZView;


struct Work56EC8;
typedef struct Work56EC8 Work56EC8;

struct Table;
typedef struct Table Table;

extern int g_controllerPakChannelStatuses[];


struct MenuTextResultView;
struct MenuTextResultView {
    char pad[8];
    s32 flags;
    char padC[0x14 - 0xC];
    s32 value;
};

struct ResourceManagerState;
typedef struct ResourceManagerState ResourceManagerState;

struct StridedTable;
typedef struct StridedTable StridedTable;

struct ScalarPair;
typedef struct ScalarPair ScalarPair;


struct ControllerButtonFlagsView;
typedef struct ControllerButtonFlagsView ControllerButtonFlagsView;

struct ControllerProfile;
typedef struct ControllerProfile ControllerProfile;


struct ThreadIdentifierView;

struct TextLayerRect;
struct TextLayerRect {
    char pad[0x14];
    int x;
    int right;
    int y;
};

struct Shared_GameMode;
struct Shared_GameMode {
    char pad0[0x1C];
    s32 sound;
    char pad20[0x8];
    s32 state;
};

struct Query;
struct Query {
    f32 radius;
    f32 bottom;
    f32 top;
    f32 top1;
    f32 bottom1;
    f32 top2;
    f32 bottom2;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    s32 flag;
};

struct SmpControlItemView;
struct SmpControlItemListView;
struct SmpControlItemListView {
    char pad0[8];
    struct SmpControlItemView *items;
    char padC[0x54 - 0xC];
    s32 state;
};

extern int g_resourceSlotProtected[];

struct EffectColorContribution;


struct ActorYawView;
struct ActorYawView {
    char pad0[0x6C];
    f32 yaw;
};


struct SoundSlotHandleView;
typedef struct SoundSlotHandleView SoundSlotHandleView;



struct AudioVoiceChannelFilterView;
typedef struct AudioVoiceChannelFilterView AudioVoiceChannelFilterView;

struct AudioVoicePhysicalLinkView;
typedef struct AudioVoicePhysicalLinkView AudioVoicePhysicalLinkView;



struct BarrelTrackActorView;
struct BarrelTrackActorView {
    s32 reservedWordA;
    s32 reservedWordB;
    Triple vec;
};

struct CallbackStateC_4;
struct CallbackStateC_4 {
    char pad0[0x8];
    void (*callback)(void *, s32, void *);
};


struct ChoiceMenuState;
typedef struct ChoiceMenuState ChoiceMenuState;

struct PakControllerRequestView;
struct ControllerButtonFlagsView;

struct Status;
struct Status {
    char pad0[0x78];
    u8 active;
    char pad79[0x80 - 0x79];
    s8 kind;
    char pad81[0x91 - 0x81];
    u8 pendingClear;
    char pad92[150 - 0x92];
};

struct Model;
typedef struct Model Model;



struct ArchiveTextureDataEntryView;
struct ArchiveTextureDataEntryView {
    s32 unused;
    s32 flags;
    char rest[20];
};

struct HudStatusShared_Settings;
struct HudStatusShared_Settings {
    s32 flags;
    s32 selection;
    char pad8[0x5];
    u8 trialKind;
    char padE[0x8];
    u8 hudFade;
    char pad17[0x6];
    u8 hudShown;
    char pad1E[0xB2];
    ListScreenRecord roster[8];
    char pad580[0x1];
    u8 language;
    char pad582[0x32];
    s32 state;
    char pad5B8[0x20];
    HudStatusShared_MatchRules rules;
    char pad674[0xC];
    s32 humanWon;
};


extern int g_controllerPakState[];

struct WeaponInfo;
typedef struct WeaponInfo WeaponInfo;



extern int g_geometryOpaqueRenderMode;

struct ObjRecAt28V2;
struct ObjRecAt28V2 {
    char pad0[0x28];
    int state;
};

struct CROMEventEntry_t;
typedef struct CROMEventEntry_t CROMEventEntry;

struct AnimationResourceHandleView;
struct AnimationResourceHandleView {
    char pad0[0x10];
    s32 resourceHandle;
};

struct NumericWidgetChildView;
struct NumericWidgetChildView {
    char pad0[0x8];
    void * firstChild;
    char pad8[0x12 - 0x8 - sizeof(void*)];
    u16 flags;
};


struct MenuSettings;
struct MenuSettings {
    u32 flags;
    s32 optionFlags; /* +4: toggled menu option bits */
    u8 reservedBytes[0x1D - 8];
    u8 local; /* +0x1D: local-player input flag */
    u8 reservedBytes1[0x581 - 0x1E];
    u8 language;
};



struct AudioPhysicalVoiceOffsetView;
struct AudioPhysicalVoiceOffsetView {
    unsigned char padding[216];
    s32 offset;
};



struct RumbleEffectNode;
typedef struct RumbleEffectNode RumbleEffectNode;

struct AttachmentEventTableView;
struct AttachmentEventTableView {
    char pad0[0x4];
    s32 entryCount;
    char pad4[0x8 - 0x4 - sizeof(s32)];
    char entries;
};


struct ObjalAuxBusParam;
typedef struct ObjalAuxBusParam ObjalAuxBusParam;


struct ParamsRecAt8V1;
struct ParamsRecAt8V1 {
    s16 f0;
    s32 f4;
    s16 f8;
};


extern int g_sessionOptionResetMode;

struct PlayerRecord;
struct PlayerRecord {
    char data[400];
};


struct MenuCreationOwnerView;
typedef struct MenuCreationOwnerView MenuCreationOwnerView;
#endif
