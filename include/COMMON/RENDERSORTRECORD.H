#ifndef COMMON_RENDERSORTRECORD_H
#define COMMON_RENDERSORTRECORD_H
#include "TYPES.H"

/* Sortable render item, moved as an eight-byte record. */
typedef struct RenderSortRecord {
    s32 index;
    f32 depth;
} RenderSortRecord;
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BOX_CONTACT.H"

struct PlaneContactStorageView;
struct PlaneContactStorageView {
    s32 clearedWordFirst;
    char pad0[0x54 - 0x0 - sizeof(s32)];
    s32 clearedWordSecond;
    char pad54[0x58 - 0x54 - sizeof(s32)];
    s32 invalidContactIndex;
    char pad58[0xCC - 0x58 - sizeof(s32)];
    f32 contactDistance;
};


struct Plane;
typedef struct Plane Plane;





struct Shape;



extern float g_planeInitialContactDistance;


struct PlaneContactStorageView;
typedef struct PlaneContactStorageView PlaneContactStorageView;



struct Quad;
struct Quad {
    char pad0[0x14];
    s32 kind;
    CVector3 corner[4];
    CVector3 normal;
};



struct IntPair;

struct Plane;
struct Plane {
    char pad[0x18];
    CVector3 pos;
    char pad24[0x24];
    CVector3 normal;
};



int InstHdr_UsesDefaultDefinitionHandling(struct LevelActor *source);
#endif
