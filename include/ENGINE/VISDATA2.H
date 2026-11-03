#ifndef ENGINE_VISDATA2_H
#define ENGINE_VISDATA2_H
struct PlaneEquation;
struct CVector3_t;
void Visdata_BuildFrustumPlanes(struct PlaneEquation *planes, struct CVector3_t *eye, struct CVector3_t *c0, struct CVector3_t *c1, struct CVector3_t *c2, struct CVector3_t *c3);
s32 Visdata_ContainsPoint(f32 (*planes)[4], f32 *point);
s32 Visdata_TestBoxAgainstFrustum(f32 (*planes)[4], f32 *boxBounds);
struct ResourceBitGrid;
int Visdata_TestVisibilityGridBit(struct ResourceBitGrid *g,int x,int y,int z);
#endif
