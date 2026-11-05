#ifndef ENGINE_UNICOL_PLANE_H
#define ENGINE_UNICOL_PLANE_H
#include "Common/output.h"
#include "Common/vector.h"
#include "types.h"
#include "Anim/collision_ray.h"
#include "Common/measured_storage.h"

struct Polygon;
extern f32 CCollision_GetContactYaw(f32 *contactRecord);

/* Measured 4-byte access at 0x4C; storage view, complete object unknown. */
struct Measured { unsigned char padding[76]; f32 value; };

extern s32 Plane_TestPointNearPolygon(struct Polygon*polygon, CVector3*point, f32 radius);
extern void CPlane_ResetContact(void *contactStorage);
extern s32 CPlane_IsPointBehind(void *plane, CVector3 *testPoint);
struct Quad;
struct CVector3_t;
void Plane_BuildBoxFace0(struct Quad *quad, struct CVector3_t *points);
void Plane_BuildBoxFace1(struct Quad *quad, struct CVector3_t *points);
void Plane_BuildBoxFace2(struct Quad *quad, struct CVector3_t *points);
void Plane_BuildBoxFace3(struct Quad *quad, struct CVector3_t *points);
void Plane_BuildBoxFace4(struct Quad *quad, struct CVector3_t *points);
void Plane_BuildBoxFace5(struct Quad *quad, struct CVector3_t *points);
#endif
