#ifndef FRONTEND_FRONTEND_H
#define FRONTEND_FRONTEND_H
#include "Common/model_preview_transform.h"
#include "types.h"
#include "Common/small_records.h"

struct Pool;
struct FrontendArchiveHandleView;
struct FieldRow;
struct GlyphBuffer;
struct PreviewRotationView;
struct MenuWidget;
struct TextSpriteGlyphKey;
struct StateFlags;
struct StateFrontendUpdateOptionsPageExit;
struct ListScreenRecord;
struct ProfileWeaponRowEntry;
struct FrontendTextureTimerEntry;
struct Label;
struct RecordFrontendSetPreviewModel;
struct Header;
struct Pair14;
struct List;
struct Status;
struct HudStatusShared_Settings;
struct HudStatusShared_MatchRules;
typedef struct FieldRow FieldRow;
typedef struct MenuWidget MenuWidget;
typedef struct StateFlags StateFlags;
typedef struct HudStatusShared_MatchRules HudStatusShared_MatchRules;
typedef struct ListScreenRecord ListScreenRecord;
typedef struct GlyphBuffer GlyphBuffer;
typedef struct TextSpriteGlyphKey TextSpriteGlyphKey;
typedef struct PreviewRotationView PreviewRotationView;
typedef struct FrontendArchiveHandleView FrontendArchiveHandleView;
typedef struct Header Header;
typedef struct HudStatusShared_Settings HudStatusShared_Settings;

/* Resource node pool: word 0 is the free-node count, word 0x11 the frame stamp;
   the cache record g_resourceRecencyList sits 0xBCC bytes below. */
struct Pool {
    s32 count;
    char pad[0x40];
    s32 useCounter;
};

struct FrontendArchiveHandleView {
    char pad0[0x2C];
    int archiveHandle;
};

struct FieldRow {
    s32 value;
    char pad[8];
};

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

struct TextSpriteGlyphKey {
    char pad[0x14];
    u16 value;
};

struct StateFlags {
    u16 value;
    u16 flags;
};

struct StateFrontendUpdateOptionsPageExit {
    void *menu;
    char pad4[0x20 - 4];
    s32 value;
};

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

struct ProfileWeaponRowEntry {
    s32 value;
    char pad[28 - 4];
};

struct FrontendTextureTimerEntry {
    s32 id;
    s16 retained;
    s16 unused;
};

struct Label {
    char pad0[0x38];
    char *text;
};

struct RecordFrontendSetPreviewModel {
    s32 count;
    char pad4[0x34 - 4];
    s32 handle;
};

struct Header {
    u8 data[204];
};

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

struct Pair14 {
    char pad[0x14];
    s16 first;
    s16 second;
};

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

struct Status {
    char pad0[0x78];
    u8 active;
    char pad79[0x80 - 0x79];
    s8 kind;
    char pad81[0x91 - 0x81];
    u8 pendingClear;
    char pad92[150 - 0x92];
};

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

int Frontend_ClearEuxLoadingHints(void);
s32 Frontend_ClearLoadingHints(void);
#endif
