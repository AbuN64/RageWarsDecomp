#ifndef COMMON_OBJB_H
#define COMMON_OBJB_H
#include "TYPES.H"
#include "COMMON/LEVEL_TRACK.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PACKED.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/LEVEL_INPUT.H"
#include "COMMON/PARTICLE_LIGHTING.H"

struct Shared_Placed;



struct ItemsPendingState;

struct ObjB;
typedef struct ObjB ObjB;

struct World;


struct CROMLevel_t;
struct CROMLevel_t {
    f32 m_GridDistance;
    char pad4[0xA - 0x4];
    u8 m_DirectionalLight[3];
    u8 m_AmbientLight[3];
    char pad10;
    signed char m_Direction[3];
};
struct CROMLevel_t;
struct SceneLightLoadView;

struct ScreenMessageOwner;

struct SceneResourceOwnerView;
typedef struct SceneResourceOwnerView SceneResourceOwnerView;

struct ScreenMessageOwner;



struct CActiveLink;
typedef struct CActiveLink CActiveLink;

struct SceneLightLoadView;
typedef struct SceneLightLoadView SceneLightLoadView;

struct SceneGridCellLoadView;

struct CDLight_t;
typedef struct CDLight_t CDLight;

typedef IntrusiveList ListRec;

struct CActiveLink;
struct CActiveLink {
    struct CActiveLink *prev;
    struct CActiveLink *next;
    struct Record14 *object;
    f32 remaining;
};

struct Floats;
typedef struct Floats Floats;

struct ItemsSelectionState;
typedef struct ItemsSelectionState ItemsSelectionState;

struct Node_Items_FindPlacedObjectsByKey;

struct ObjA;
typedef struct ObjA ObjA;


struct Face;
struct Face {
    char pad0[0xE];
    u8 flags;
    u8 hidden;
    char pad10[3];
    u8 group;
};

struct Face;
typedef struct Face Face;




struct SceneResourceOwnerView;

struct ItemsPreviewStateB;

struct World;


struct Node_Items_FindPlacedObjectsByKey;
typedef struct Node_Items_FindPlacedObjectsByKey Node_Items_FindPlacedObjectsByKey;

struct ItemsPreviewStateB;
typedef struct ItemsPreviewStateB ItemsPreviewStateB;




struct CDLight_t;
/* One of the dynamic-light pool's eight 0x18-byte records, threaded through its lists by m_pPrev (+0) and m_pNext (+4). */
struct CDLight_t {
    struct CDLight_t *m_pPrev;
    struct CDLight_t *m_pNext;
    void *m_pROMLight;
    f32 m_ColorFade;
    s16 x, y, z;
    s16 m_bEnabled;
};
struct CGameDynamicLight_t;

extern const float g_lightDirectionLength;

struct ObjA;

struct SceneGridCellLoadView;
typedef struct SceneGridCellLoadView SceneGridCellLoadView;



struct Face;
struct SceneVisibilityGeometryView;
struct SceneVisibilityGeometryView {
    char pad0[0x80];
    void *tree;
    char pad84[0x11C0 - 0x84];
    s32 nfaces;
    s32 nedges;
    void *verts;
    void *edgeData;
    struct Face *faces;
    struct Face *edges;
    IntrusiveList listA;
    IntrusiveList listB;
    CActiveLink buckets[48];
    char pad1500[0x1B40C - 0x1500];
    s32 group;
};



struct Shared_Placed;


extern short g_firstConnectedControllerPort;

struct ItemsSelectionState;



struct Scene;




struct ItemsPendingState;
typedef struct ItemsPendingState ItemsPendingState;

struct Scene;


struct Floats;
struct Floats {
    f32 reservedFloat;
    f32 floatAt4;
    f32 floatAt8;
    f32 floatAtC;
    f32 floatAt10;
    f32 floatAt14;
};



struct ItemsHandleOwner;
struct ItemsHandleOwner {
    char pad[0x11BC];
    s32 first;
    s32 second;
};
typedef struct ItemsHandleOwner ResourceHandleOwner;

struct SceneVisibilityGeometryView;
typedef struct SceneVisibilityGeometryView SceneVisibilityGeometryView;

struct ObjB;
struct ObjA {
    s8 state;
    s8 type;
    char pad2[2];
    u16 id;
    char pad6[2];
    CVector3 position;
    void *segment;
    struct StaticModelAnimationDescriptor *descriptor; /* +0x18 */
    s32 owner;
    void **block; /* +0x20 */
    char pad24[4];
    char transform[0x40];
    char matrix[0x40]; /* +0x68: placement and attachment transform */
    s32 renderIndex; /* +0xA8: initialized to -1 */
    s32 renderState[3]; /* +0xAC: cleared during placement */
    Box bounds; /* +0xB8 */
    s32 flagsD0;
    s32 surfaceType; /* +0xD4: placement surface selection */
    u16 flagsD8;
    u8 colorFrame;
    char padDB;
    u32 timer;
    s8 fade; /* signed: distance fade clamps negative values */
    char padE1[7];
};

struct ObjB {
    u8 state;
    s8 type;
    char pad2;
    s8 material;
    u16 id;
    char pad6[2];
    CVector3 position; /* +0x08 */
    void *room;
    struct ActorDefinitionHeader *definition; /* +0x18 */
    CVector3 effectPosition; /* +0x1C: Simpinst_SpawnModelEffect */
    char pad28[0x28];
    s32 animationKey; /* +0x50: model directory key */
    s32 loadedType; /* +0x54: cached model variant */
    s32 resource;
    s32 resourceSize;
    void **block; /* +0x60: cached paired geometry resource */
    char pad64[4];
    char matrices[4][0x40];
    char pad168[0xC];
    f32 angle;
    char pad178[4];
    Box bounds; /* +0x17C */
    f32 scale;
    f32 height;
    u16 flags;
    u16 placementId;
    f32 scaleTime;
    f32 frameDelta;
    Shared_ParticleLighting lights;
    s32 scene;
    Gfx *cached;
};

struct Shared_World;
extern void **Cache_RequestWordCountedResource(s32,void **,s32,void *,s32);
extern s32 g_sceneParticleEffectSectionTag;
extern s32 g_sceneGeometrySectionTag;
extern const char g_cartridgeIndex[];
extern char g_sceneDirectoryResourceTag;
extern const char g_textureSetsIndex[];
extern const char g_objectTypesText[];
extern const char g_objectsIndex[];
extern char g_sceneGeometryResourceTag;
extern const char g_particleEffects[];
extern const char g_binariesIndexText[];
extern const char g_particleSwooshes[];
extern char g_sceneSectionTwelveResourceTag;
extern const char g_warpDests[];
extern const char g_curves[];
extern const char g_rumbleLabels[];
extern char g_sceneSectionFifteenResourceTag;
extern const char g_graphicsetType[];
extern const char g_graphicsetIndex[];
extern const char g_cinemasIndexText[];
extern const char g_linkGroupTypes[];
extern const char g_constructBlLevelDataIndex[];
extern const char g_bloodlustWeaponData[];

extern void Geometry_ExpandModelWithSentinel(s32, s32);
extern const u8 g_constructMapObjectIndex[];
extern const char g_constructMapSimpModelsIndex[];
extern const u8 g_constructMapSimpleModel[];

typedef struct CollisionBuildVertex {
    f32 x;
    f32 y;
    f32 z;
    f32 ceiling;
} CollisionBuildVertex;
typedef union CollisionBuildTriangle { struct {
    u16 kind;
    u16 flags;
    CollisionBuildVertex *v[3];
    union CollisionBuildTriangle *adj[3];
    s32 mask;
} fields; CGameRegion canonical; s32 words[8]; } CollisionBuildTriangle;
typedef Packed CollisionBuildFace;
extern void SetN64_TransposeRecords(void *src, void *dst, s32 copyBack);

extern void *memcpy(void *, const void *, unsigned int);
extern s32 g_spawnReferenceFloorPolygon;
extern void Player_InitActorParts(SharedPlayer *player, LevelPlacedActorRecord *rec, s32 mode, s32 index);
#endif
