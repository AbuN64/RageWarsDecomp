#ifndef COMMON_GEOMETRY_BLEND_AND_INSTANCE_VIEWS_H
#define COMMON_GEOMETRY_BLEND_AND_INSTANCE_VIEWS_H
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/ITEMRECAT20V1.H"
struct SharedModelTintMaterial;
typedef struct SharedModelTintMaterial SharedModelTintMaterial;

struct Mesh;
struct Mesh {
    u32 list;
    u32 matrix;
    u32 aux;
    u32 vertices;
    u16 scaleS;
    u16 scaleT;
    s32 segmented;
    s32 unused;
    struct Mesh *next;
};

struct Mesh;
typedef struct Mesh Mesh;

struct Material18;
struct Material18 {
    u32 flags;
    char pad4[0x13];
    u8 alpha;
};

struct Material18;
typedef struct Material18 Material18;

struct Group18;
struct Group18 {
    char pad0[3];
    s8 mode;
    Material18 *material;
    Mesh *meshes;
    char padc[8];
    struct Group18 *next;
};

struct GeometryModelInstanceEntry;
struct GeometryModelInstanceEntry {
    s32 *data;
    s32 modelParamFirst;
    s32 modelParamSecond;
    s32 modelParamThird;
    u16 sourceHalfFirst;
    u16 sourceHalfSecond;
    s32 modelParamFourth;
    s32 reservedWord;
    struct GeometryModelInstanceEntry *next;
};

struct ResourceSource;
struct ResourceSource {
    s32 flags;
    u16 id;
    u8 pad6[0x12];
    u16 copiedHalfFirst;
    u16 copiedHalfSecond;
};

struct GeometryModelInstanceEntry;
struct NodeGeometryGroupModelInstances;
struct ResourceSource;
struct NodeGeometryGroupModelInstances {
    u32 key;
    struct ResourceSource *source;
    struct GeometryModelInstanceEntry *head;
    struct GeometryModelInstanceEntry *tail;
    struct NodeGeometryGroupModelInstances *prev;
    struct NodeGeometryGroupModelInstances *next;
    struct NodeGeometryGroupModelInstances *left;
    struct NodeGeometryGroupModelInstances *right;
};

extern void Geometry_BeginModelBatch(void);

struct Material;
typedef struct Material Material;

extern void Geometry_InvalidateMaterialKeys(void);

struct GeometryModelInstanceEntry;
typedef struct GeometryModelInstanceEntry GeometryModelInstanceEntry;

extern u32 g_geometryPreviousModePreset;

extern void Geometry_SelectEffectModes(void);

extern float g_geometryLightDirectionScale;


struct ResourceSource;
typedef struct ResourceSource ResourceSource;

struct Owner104;
typedef struct Owner104 Owner104;

extern int g_geometryOverrideMaterial;



struct NodeGeometryGroupModelInstances;
typedef struct NodeGeometryGroupModelInstances NodeGeometryGroupModelInstances;

struct Material;

struct Owner104;


struct Group18;
typedef struct Group18 Group18;

extern void Geometry_NoOperation(void);

extern void Geometry_InitializeModelRenderState(void);

extern void Geometry_FlushModelBatch(void);

struct SharedModelTintMaterial;



struct SceneModelBankView;
struct ObjectSceneChangeInstanceModel;

struct MeshMaterial;
struct CROMSection;
#endif
