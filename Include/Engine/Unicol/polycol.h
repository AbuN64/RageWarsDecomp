#ifndef ENGINE_UNICOL_POLYCOL_H
#define ENGINE_UNICOL_POLYCOL_H
#include "Anim/collision_ray.h"
#include "types.h"
#include "Common/runtime_declarations.h"

struct CollisionVertex;
struct CapsuleSweep;
struct ContextB0;
struct Polygon;
extern s32 CCollision_TestOffsetPolygon(struct CapsuleSweep*,CVector3*,f32,struct Polygon*,s32);

/* Mesh display-list commands are logical words on both the ROM and native resource paths;
 * the opcode is the high byte of the first word. */
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define COMMAND_HIGH 3
#else
#define COMMAND_HIGH 0
#endif

/* Display-list opcodes the collision trace walks (F3DEX2 numbering). */
#define MESH_CMD_VTX 0x01

#define MESH_CMD_TRI1 0x05

#define MESH_CMD_TRI2 0x06

#define MESH_CMD_ENDDL 0xDF

extern void PolyCol_TraceMeshTriangle(struct ContextB0 *, struct CollisionVertex **);

/* Traces one triangle whose three vertex indices (doubled) sit in the low three bytes of a command
 * word; reversed meshes trace it a second time with the winding flipped. TRI2 visits its second
 * triangle before falling through to TRI1. */
#define TRACE_TRIANGLE(context, vertices, triangle, command, reverse, saved) \
    triangle[0] = &vertices[((*(command)) & 0xFE0000) >> 17]; \
    triangle[1] = &vertices[((*(command)) & 65024) >> 9]; \
    triangle[2] = &vertices[((*(command)) & 0xFF) >> 1]; \
    if ((triangle[0]->clipFlags & \
         triangle[1]->clipFlags & \
         triangle[2]->clipFlags) == 0) { \
        PolyCol_TraceMeshTriangle(context, triangle); \
        if (reverse) { \
            saved = triangle[0]; \
            triangle[0] = triangle[2]; \
            triangle[2] = saved; \
            PolyCol_TraceMeshTriangle(context, triangle); \
        } \
    }

/* Clip bits compare IEEE-754 bit patterns: for non-negative floats the integer order is the float
 * order, so `limit - |value|` goes negative exactly when |value| exceeds the limit. */

/* Two bits per axis: bit `shift` when value > limit, bit `shift + 1` when value < -limit. */
static inline u32 Clip_AxisOutside(f32 *value, f32 *limit, s32 shift) {
    u32 coordinate = *(u32 *)value;
    return ((*(u32 *)limit - (coordinate & 0x7FFFFFFF)) >> 31) << (shift + (coordinate >> 31));
}

/* 1 when value is non-negative and beyond limit. */
static inline u32 Clip_BeyondPositive(f32 *value, f32 *limit) {
    u32 coordinate = *(u32 *)value;
    return ~(coordinate >> 31) & ((*(u32 *)limit - coordinate) >> 31);
}

/* 1 when value is negative and beyond -limit. */
static inline u32 Clip_BeyondNegative(f32 *value, f32 *limit) {
    u32 coordinate = *(u32 *)value;
    return (coordinate >> 31) & ((*(u32 *)limit - (coordinate & 0x7FFFFFFF)) >> 31);
}

extern void CPolyCollision_SwapHits(struct Hit8 *leftHit, struct Hit8 *rightHit);

extern s32 CPolyCollision_CompareHitFractions(struct Hit8 *leftHit, struct Hit8 *rightHit);

extern float g_collisionTraceViewUpVector[];

extern s32 Barrel_GetImpactSlot(void *);
#endif
