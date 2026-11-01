#ifndef COMMON_BOX_CONTACT_H
#define COMMON_BOX_CONTACT_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
struct ItemsHandleOwner;
/* A fixed point bone matrix: integer halves, then fraction halves. */
typedef struct BoxContactBone {
    s16 whole[4][4];
    u16 fraction[4][4];
} BoxContactBone;
typedef struct BoxContactActor {
    u8 reserved0;
    s8 animation;
    u8 reserved2[0x16];
    s32 *kind;
    u8 reserved1C[0x34];
    CVector3 scale;
    u8 reserved5C[0x18];
    f32 transform[4][4];
    u8 reservedB4[4];
    BoxContactBone *bones;
    u8 reservedBC[8];
    s32 shapeId;
    u8 reservedC8[8];
    s32 shapeBank;
    u8 reservedD4[0x14];
    Box box;
    u8 reserved100[0x7C];
    u32 partMask;
    u8 reserved180[0x58];
    struct ItemsHandleOwner *widget;
} BoxContactActor;
typedef struct ContactProjectile {
    u8 type;
    u8 reserved1[3];
    u16 kind;
    u8 reserved6[2];
    CVector3 position;
    u8 reserved14[8];
    CVector3 color;
    u8 reserved28[0x104];
    BoxContactActor *owner;
    u8 reserved130[4];
    s32 ticks;
    u8 reserved138[4];
    BoxContactActor *lastHit;
    u8 reserved140[12];
    u16 contactState;
} ContactProjectile;
typedef struct BoxContactMaterial {
    u32 flags;
    s8 kind, alternateKind;
    u8 reserved6[10];
    f32 response;
} BoxContactMaterial;
/* A collision part: its eight box corners, a sphere radius, flags and the part mask it belongs to. */
typedef struct BoxContactTransform {
    CVector3 corners[8];
    f32 radius;
    u8 reserved64;
    u8 flags;
    u8 reserved66[6];
    u32 mask;
} BoxContactTransform;
typedef struct BoxContactPolygon {
    s32 type;
    f32 response;
    s32 kind;
    s32 count;
    s32 flags;
    s32 valid;
    CVector3 point;
    u8 reserved24[0x24];
    CVector3 normal;
    BoxContactActor *actor;
    s32 index;
    BoxContactTransform transform;
    f32 t;
    CVector3 hit;
} BoxContactPolygon;
/* The parts of an animated shape: the byte stride of each part, then the part count; parts follow. */
typedef struct BoxContactPartTable {
    s32 stride;
    s32 count;
} BoxContactPartTable;
typedef struct BoxContactRay {
    ContactProjectile *projectile;
    u8 reserved4[0x3C];
    BoxContactMaterial *material;
    CVector3 start, end, direction;
    u8 reserved68[0x18];
    f32 slack;
    Box bounds;
    u8 reserved9C[0x14];
    BoxContactPolygon nearest;
} BoxContactRay;
typedef struct ContactEffectStyle {
    s16 kind, flags;
    s8 mode, red, green, blue;
} __attribute__((aligned(4))) ContactEffectStyle;
#endif
