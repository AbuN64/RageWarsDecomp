#include "TYPES.H"
#include "COMMON/OUTPUT.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "ENGINE/UNICOL/PLANE.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/RENDERSORTRECORD.H"
#include "ANIM/RAY180.H"
#include "ANIM/CPLANE_RESETCONTACT.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

/* 8023EEF0_13.CPP */
extern void Graphu64_CrossVectors(CVector3 *, CVector3 *, CVector3 *);
/* Is `point` inside the polygon prism, or within `radius` of its edges?
 * Each edge's outward normal (normal x edge) splits off the outside half-space; a point outside an edge
 * passes only when its distance to that edge is at most `radius`. Types 3 and 4 measure the distance
 * to the edge segment (clamped at its end vertex); other types measure it to the edge line and let the
 * projection run past either end by at most `radius`. */
s32 Plane_TestPointNearPolygon(Polygon *polygon, CVector3 *point, f32 radius)
{
    CVector3 outward;
    CVector3 edge;
    CVector3 delta;
    CVector3 *previousVertex;
    CVector3 *vertex;
    f32 projection;
    f32 side;
    f32 lengthSquared;
    f32 radiusSquared;
    f32 limit;
    s32 remaining;

    if (polygon->vertexCount == 1) {
        return 1;
    }
    previousVertex = &polygon->vertices[polygon->vertexCount - 1];
    vertex = polygon->vertices;
    radiusSquared = radius * radius;
    remaining = polygon->vertexCount;
    if (polygon->type == 3 || polygon->type == 4) {
        for (; --remaining != -1; previousVertex = vertex++) {
            Graphu64_SubtractVectors(&edge, vertex, previousVertex);
            Graphu64_CrossVectors(&outward, &polygon->normal, &edge);
            Graphu64_SubtractVectors(&delta, point, previousVertex);
            side = outward.x * delta.x + outward.y * delta.y + outward.z * delta.z;
            if (side > 0.0f) {
                if (radius > 0.0f) {
                    projection = edge.x * delta.x + edge.y * delta.y + edge.z * delta.z;
                    if (projection > 0.0f) {
                        lengthSquared = edge.x * edge.x + edge.y * edge.y + edge.z * edge.z;
                        if (lengthSquared <= projection) {
                            Graphu64_SubtractVectors(&delta, &delta, &edge);
                        } else {
                            Graphu64_ScaleVector(&edge, &edge, projection / lengthSquared);
                            Graphu64_SubtractVectors(&delta, &delta, &edge);
                        }
                    }
                    if (!(radiusSquared < delta.x * delta.x + delta.y * delta.y + delta.z * delta.z)) {
                        continue;
                    }
                }
                return 0;
            }
        }
    } else {
        for (; --remaining != -1; previousVertex = vertex++) {
            Graphu64_SubtractVectors(&edge, vertex, previousVertex);
            Graphu64_CrossVectors(&outward, &polygon->normal, &edge);
            Graphu64_SubtractVectors(&delta, point, previousVertex);
            side = outward.x * delta.x + outward.y * delta.y + outward.z * delta.z;
            if (side > 0.0f) {
                if (radius > 0.0f) {
                    projection = edge.x * delta.x + edge.y * delta.y + edge.z * delta.z;
                    lengthSquared = edge.x * edge.x + edge.y * edge.y + edge.z * edge.z;
                    projection /= lengthSquared;
                    if (projection < 0.0f) {
                        limit = -radius / Gu_Sqrtf(lengthSquared);
                        if (projection < limit) {
                            return 0;
                        }
                    } else if (1.0f < projection) {
                        limit = 1.0f + radius / Gu_Sqrtf(lengthSquared);
                        if (limit < projection) {
                            return 0;
                        }
                    }
                    Graphu64_ScaleVector(&edge, &edge, projection);
                    Graphu64_SubtractVectors(&delta, &delta, &edge);
                    if (!(radiusSquared < delta.x * delta.x + delta.y * delta.y + delta.z * delta.z)) {
                        continue;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

/* 802406C0.CPP */
/* Computes the signed incline between two horizontal points projected onto a plane. */

static inline f32 height(Plane *p,f32 x,f32 z) {
 CVector3 n=p->normal;
 if(n.y==0) return p->pos.y;
 else {CVector3 v=p->pos; return ((v.z-z)*n.z+(v.x-x)*n.x+v.y*n.y)/n.y;}
}

f32 CPlane_GetSlopeAngle(Plane *p,f32 x0,f32 z0,f32 x1,f32 z1) {
 f32 y0,y1,dx,dz,dy,h,v,r;
 if(!p)return 0;
 y0=height(p,x0,z0);y1=height(p,x1,z1);
 dx=x1-x0;dz=z1-z0;dy=y1-y0;
 h=dx*dx+dz*dz;v=h+dy*dy;
 r=0.0f;
 if(v!=0){r=Gu_Sqrtf(h/v);r=Graphu64_ArcCos(RW_MAX_GT(-1.0f,RW_MIN_LT(1.0f,r)));if(!(y0<y1))r=-r;}
 return r;
}

/* 8023EEF0_16.CPP */
void CPlane_ResetContact(void *contactStorage)
{
    PlaneContactStorageView *contact = contactStorage;
  int invalidContact;
  f32 initialContactDistance;
  initialContactDistance = (f32) g_planeInitialContactDistance;
  contact->clearedWordFirst = 0;
  contact->clearedWordSecond = 0;
  invalidContact = -1;
  contact->invalidContactIndex = invalidContact;
  contact->contactDistance = initialContactDistance;
}

/* 802406C0_2.CPP */
/* Sets up one face of a box as a four-corner quad of kind 4, copying points 0, 1, 2 and 3 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */
static inline void quad_normal(struct Quad *quad) {
    CVector3 first;
    CVector3 second;

    Graphu64_SubtractVectors(&first, &quad->corner[1], &quad->corner[0]);
    Graphu64_SubtractVectors(&second, &quad->corner[2], &quad->corner[1]);
    Graphu64_CrossVectors(&quad->normal, &second, &first);
    Graphu64_NormalizeVec3(&quad->normal);
}

void CPlane_BuildTriangleNormal(void *query) {
    QueryE0 *object = query;
    CVector3 firstEdge;
    CVector3 secondEdge;
    CVector3 *middleVertex;
    CVector3 *outputNormal;

    middleVertex = &object->vectors[1];
    Graphu64_SubtractVectors(&firstEdge, middleVertex, &object->vectors[0]);
    Graphu64_SubtractVectors(&secondEdge, &object->vectors[2], middleVertex);
    outputNormal = &object->result;
    Graphu64_CrossVectors(outputNormal, &secondEdge, &firstEdge);
    Graphu64_NormalizeVec3(outputNormal);
}

void Plane_BuildBoxFace0(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[0];
    quad->corner[2] = points[1];
    quad->corner[1] = points[2];
    quad->corner[0] = points[3];
    quad_normal(quad);
}

/* 80240DF0.CPP */
/* Sets up one face of a box as a four-corner quad of kind 4, copying points 7, 6, 5 and 4 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. Adapted from Plane_BuildBoxFace0 with the copied points changed. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */


void Plane_BuildBoxFace1(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[7];
    quad->corner[2] = points[6];
    quad->corner[1] = points[5];
    quad->corner[0] = points[4];
    quad_normal(quad);
}

/* 80240ED0.CPP */
/* Sets up one face of a box as a four-corner quad of kind 4, copying points 3, 2, 6 and 7 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. Adapted from Plane_BuildBoxFace0 with the copied points changed. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */


void Plane_BuildBoxFace2(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[3];
    quad->corner[2] = points[2];
    quad->corner[1] = points[6];
    quad->corner[0] = points[7];
    quad_normal(quad);
}

/* 80240FB0.CPP */
/* Sets up one face of a box as a four-corner quad of kind 4, copying points 4, 5, 1 and 0 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. Adapted from Plane_BuildBoxFace0 with the copied points changed. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */


void Plane_BuildBoxFace3(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[4];
    quad->corner[2] = points[5];
    quad->corner[1] = points[1];
    quad->corner[0] = points[0];
    quad_normal(quad);
}

/* 80241090.CPP */
/* Sets up one face of a box as a four-corner quad of kind 4, copying points 0, 3, 7 and 4 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. Adapted from Plane_BuildBoxFace0 with the copied points changed. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */


void Plane_BuildBoxFace4(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[0];
    quad->corner[2] = points[3];
    quad->corner[1] = points[7];
    quad->corner[0] = points[4];
    quad_normal(quad);
}

/* 80241170.CPP */
/* Sets up one face of a box as a four-corner quad of kind 4, copying points 2, 1, 5 and 6 of the
   input into corners 3, 2, 1 and 0 and deriving its normal at 0x48 from the edges corner 1 minus
   corner 0 and corner 2 minus corner 1 through Graphu64_SubtractVectors, their cross product through
   Graphu64_CrossVectors and normalisation through Graphu64_NormalizeVector_de. Adapted from Plane_BuildBoxFace0 with the copied points changed. */

/* The edge vectors belong to this helper; declared in the face function itself, GCC 2.8.1 keeps
   the second edge's frame address in a saved register and grows the frame. */


void Plane_BuildBoxFace5(struct Quad *quad, CVector3 *points) {
    quad->kind = 4;
    quad->corner[3] = points[2];
    quad->corner[2] = points[1];
    quad->corner[1] = points[5];
    quad->corner[0] = points[6];
    quad_normal(quad);
}

s32 CPlane_IsPointBehind(void *plane, CVector3 *testPoint) {
    Plane *object = plane;
    CVector3 offset;
    s32 outside;

    Graphu64_SubtractVectors(&offset, testPoint, &object->pos);
    outside = 0;
    if (!((object->normal.x * offset.x) + (object->normal.y * offset.y) + (object->normal.z * offset.z) >= 0.0f)) {
        outside = 1;
    }
    return outside;
}
