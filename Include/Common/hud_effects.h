#ifndef COMMON_HUD_EFFECTS_H
#define COMMON_HUD_EFFECTS_H
#include "types.h"
#include "Common/vector.h"
struct MarkerItemMenuRestoreBootMemory;
struct MarkerItemMenuRestoreBootMemory {
    char text[15];
};

struct MarkerItemMenuRestoreBootMemory;
typedef struct MarkerItemMenuRestoreBootMemory MarkerItemMenuRestoreBootMemory;




/* Fixed-link effect lists have a 12-byte header, unlike IntrusiveList. */
typedef struct EffectList { void *head, *tail; s32 count; } EffectList;
typedef struct EffectPool { EffectList free, used; } EffectPool;






struct COverlay {
    s32 active;
    s32 *script;
    s32 state;
    s32 wait;
    f32 x;
    f32 y;
    f32 targetX;
    f32 targetY;
    f32 velX;
    f32 velY;
    f32 accelX;
    f32 accelY;
    f32 rate;
    f32 alpha; /* 0x34: overall opacity of the widget */
    union {
        s32 handle; /* +0x38: resource widgets */
        s32 fill;   /* +0x38: displayed amount for status bars */
    };
};

struct Bar;
struct Bar {
    struct COverlay mover;
    void *label;
    s32 enabled; /* 0x40 */
    s32 target;
};

struct Bar;
typedef struct Bar Bar;

typedef struct EffectTimer {
    struct EffectTimer *previous;
    struct EffectTimer *next;
    union { f32 remainingTime; s32 countdown; };
    f32 interval;
    s32 remainingCalls;
    s32 callbackData;
    void (*callback)(void *);
} EffectTimer;

/* RSP fixed matrices impose eight-byte alignment: stride 0xB8. */
struct Shared_Particle;
typedef struct RibbonSegment RibbonSegment;
struct RibbonSegment {
    struct RibbonSegment *previous;
    struct RibbonSegment *next;
    f32 remainingLifetime;
    s32 reservedWord;
    CVector3 position;
    CVector3 scale;
    Mtx matrices[2]; /* +0x28, +0x68: double-buffered transforms */
    f32 fraction; /* +0xA8 */
    union { f32 length; s32 lengthWord; }; /* +0xAC: length, initialized as a word */
    struct Shared_Particle *attachedEntity; /* +0xB0 */
};

/* The 0x54-byte actors allocated by the HUD ribbon pool. */
struct RibbonSegment;
struct CROMSwoosh_t;
struct Key;
struct RibbonActor {
    struct RibbonActor *previous;
    struct RibbonActor *next; /* 0x4 */
    struct CROMSwoosh_t *track;
    struct Key *first;
    struct Key *second;
    union { s32 model; s32 textureWords[2]; }; /* 0x14, 0x18 */
    void *object; /* 0x1C: attached actor */
    s32 contextId; /* 0x20 */
    f32 time;
    union { f32 phase; s32 phaseWord; };
    union { f32 endpoint; s32 endpointWord; }; /* 0x2C */
    union { f32 frame; s32 frameWord; }; /* 0x30 */
    s32 layer; /* 0x34: negative layers draw first, positive second */
    s32 cached_frame; /* 0x38 */
    u32 flags;
    struct RibbonSegment *tail;
    struct RibbonSegment *clock;
    s32 pointCount; /* 0x48: drawn once it has two points */
    union { f32 length; s32 lengthWord; };
    s32 retries; /* 0x50: reset when a segment is appended */
};

/* Fixed projected matrices retain the RSP eight-byte alignment (slot 0x50). */
typedef struct ProjectedMarkTransform ProjectedMarkTransform;
struct ProjectedMarkTransform {
    union {
        Mtx matrix;
        struct {
            char pad0[0x18];
            s16 position[3];
        };
    };
};

typedef struct ProjectedMark ProjectedMark;
struct ProjectedMark {
    struct ProjectedMark *previous;
    struct ProjectedMark *next;
    ProjectedMarkTransform transform;
    s32 owner; /* 0x48: actor whose projected effect this is */
};

typedef struct RibbonWorld {
    Gfx *displayList; /* +0x0: cached ribbon display list */
    s32 reserved4;
    Vtx vertices[2][300]; /* +0x8: double-buffered ribbon vertex arena */
    s32 remaining; /* +0x2588 */
    Vtx *next; /* +0x258C */
    RibbonSegment actors[96];                   /* +0x2590 */
    EffectList actorList;                       /* +0x6A90 */
    struct RibbonActor shapePool[32];               /* +0x6A9C */
    EffectPool pool;                     /* +0x751C */
    EffectTimer tailPool[3];                   /* +0x7534 */
    EffectPool timers;                      /* +0x7588 */
    ProjectedMark records[100];                  /* +0x75A0 */
    IntrusiveList cells[10];                      /* +0x94E0 */
    IntrusiveList recordList;                     /* +0x95A8 */
} RibbonWorld;


/* Session and tutorial HUD allocation; mover enable words are at +0x40/+0x88,
 * while the distinct bar target values are at +0x44/+0x8C. */
struct Hud;
struct Hud {
    Bar bars[2]; /* +0x0 */
    s32 words[4]; /* +0x90: reset by Hud_ResetHudCharTables */
    s32 envR, envG, envB; /* +0xA0 */
    s32 primR, primG, primB; /* +0xAC */
    f32 width, height; /* +0xB8 */
    s32 shadowX, shadowY; /* +0xC0 */
    unsigned char glyphLookup[256]; /* +0xC8 */
    unsigned char alternateGlyphLookup[256]; /* +0x1C8 */
    RibbonWorld actors; /* +0x2C8: Hud_InitializeWorldActorPools */
};
/* Both session and tutorial HUDs use these allocation owners. */
struct RibbonWorld;
void Hud_InitializeWorldActorPools(struct RibbonWorld *world);
struct Hud;
void Hud_ResetHudCharTables(struct Hud *hud);
struct Hud;
void Hud_StartPanelMovers(struct Hud *panel);




struct CItem;





struct CItem;
typedef struct CItem CItem;







extern float g_spriteExtentAndUnitConstants;



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


















extern float g_impactMarkScaleConstants[2]; /* impact mark scale constants, indexed by the readers in FX_SPAWNIMPACTMARK.CPP */




struct Hud;
typedef struct Hud Hud;
















extern float g_attachedTransformModelScale;

extern float g_childTransformAlternateScale;

struct CItemMenu_t;
typedef struct CItemMenu_t CItemMenu;






extern float g_childTransformDefaultScale;




struct CItemMenu_t;
struct CItemMenu_t {
    unsigned char active;
    unsigned char m_ModePos;
    char pad2[2];
    CItem entries[4];
    u16 m_LastItemPos;
    short m_ItemAlphaFade;
    int m_FrameCount;
};



extern float g_attachedTransformDefaultScale;





#endif
