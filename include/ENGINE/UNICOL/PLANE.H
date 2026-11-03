#ifndef ENGINE_UNICOL_PLANE_H
#define ENGINE_UNICOL_PLANE_H
#include "COMMON/OUTPUT.H"
#include "COMMON/VECTOR3.H"
#include "TYPES.H"
#include "ANIM/RAY180.H"
#include "COMMON/MEASURED_STORAGE.H"

extern f32 CCollision_GetContactYaw(f32 *contactRecord);

/* Measured 4-byte access at 0x4C; storage view, complete object unknown. */
struct Measured { unsigned char padding[76]; f32 value; };

extern s32 Plane_TestPointNearPolygon(Polygon*polygon, CVector3*point, f32 radius);
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
