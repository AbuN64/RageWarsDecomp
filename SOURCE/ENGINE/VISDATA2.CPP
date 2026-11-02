#include "include_asm.h"
#include "COMMON/FRUSTUM.H"
#include "ENGINE/VISDATA.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MATH_HELPERS.H"
#include "TYPES.H"
#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/SCENERECAT10C0.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "SYSTEM/ENGINE_DATA_SOURCE.H"

/* VISDATA.CPP */
s32 CBitReader_ReadBits(BitReader *, s32);

extern void AnimPool_InitializeBitReader(BitReader *, void *);
/* Decode a 17-by-17 region grid, then replace variable cells with stream offsets. */
void Visdata_DecodeRegionGrid(ResourceBitGrid *grid, s32 originX, s32 originZ,
                   DraftStreamData *source, CVector3 *position) {
    CVector3 minimum, maximum;
    u32 streamCount, streamIndex;
    s32 row, column, cellCode, index;
    s32 *streamTable = &source->count;
    grid->originX = originX;
    grid->originY = originZ;
    streamCount = *streamTable;
    streamIndex = 1;
    while (streamIndex < streamCount) {
        AnimPool_InitializeBitReader(&grid->reader, SetN64_GetPackSection(streamTable, streamIndex));
        /* Each bound is a 32-bit float bit pattern stored through an s32 lvalue into an f32 member of the same width,
         * so the store is endian-neutral and portable. Its spelling is kept: gcc 2.8.1 marks a store through a union
         * member as in-struct, which pins the sixth store ahead of the comparisons instead of in the bc1f delay slot
         * (a field union, six scalar unions, a vector/word union and a union read helper all change the code). */
        *(s32 *)&minimum.x = CBitReader_ReadBits(&grid->reader, 32);
        *(s32 *)&minimum.y = CBitReader_ReadBits(&grid->reader, 32);
        *(s32 *)&minimum.z = CBitReader_ReadBits(&grid->reader, 32);
        *(s32 *)&maximum.x = CBitReader_ReadBits(&grid->reader, 32);
        *(s32 *)&maximum.y = CBitReader_ReadBits(&grid->reader, 32);
        *(s32 *)&maximum.z = CBitReader_ReadBits(&grid->reader, 32);
        if (position->x > minimum.x && position->x < maximum.x &&
            position->y > minimum.y && position->y < maximum.y &&
            position->z > minimum.z && position->z < maximum.z) break;
        streamIndex++;
    }
    if (streamIndex == streamCount) {
        AnimPool_InitializeBitReader(&grid->reader, SetN64_GetPackSection(streamTable, 0));
    }
    for (index = row = 0; row < 17; row++) {
        for (column = 0; column < 17; column++, index++) {
            cellCode = CBitReader_ReadBits(&grid->reader, 2);
            if (cellCode != 1) {
                if (cellCode != 0) {
                    if (cellCode != 2) {
                        if (cellCode == 3) grid->cells[index] = cellCode;
                    } else grid->cells[index] = 0;
                } else grid->cells[index] = -3;
            } else grid->cells[index] = -2;
        }
    }
    for (index = row = 0; row < 17; row++) {
        for (column = 0; column < 17; column++, index++) {
            if (grid->cells[index] == 0) {
                grid->cells[index] = (u16)grid->reader.bitPos;
                grid->reader.bitPos += CBitReader_ReadBits(&grid->reader, 9);
            }
        }
    }
}

/* Tests a centered grid cell and interprets its sentinel value. */

static inline int offset(int v){return v+9;}

/* Looks up the neighbour cell for (x,y) in the object's inline grid when both axes are within 9, and sets its state from the sentinel found (or starts a placement for a normal cell). */

/* Builds six clipping planes from an eye point and four corner points: each of the first five planes takes as its normal the normalised cross product of two edges between the points and as its distance the normal's projection of a point on it (the third plane through the corners, the others through the eye), and the sixth plane is the third plane with its normal reversed, its distance projected through the eye. */

extern void Graphu64_CrossVectors(CVector3 *out, CVector3 *a, CVector3 *b);
extern void Graphu64_SubtractVectors(CVector3 *out, CVector3 *a, CVector3 *b);
static inline void make_plane(PlaneEquation *plane, CVector3 *from, CVector3 *through, CVector3 *to, CVector3 *point) {
    CVector3 a;
    CVector3 b;

    Graphu64_SubtractVectors(&a, through, from);
    Graphu64_SubtractVectors(&b, to, through);
    Graphu64_CrossVectors(&plane->normal, &b, &a);
    Graphu64_NormalizeVec3(&plane->normal);
    plane->distance = plane->normal.x * point->x + plane->normal.y * point->y + plane->normal.z * point->z;
}

static inline s32 Visdata_AnyPointInsidePlane(CVector3 *points, s32 count, f32 *plane) {
    s32 i;
    s32 inside = 0;

    for (i = 0; i < count; i++) {
        if (plane[0] * points[i].x + plane[1] * points[i].y + plane[2] * points[i].z <= plane[3]) {
            inside = 1;
            break;
        }
    }
    return inside;
}

/* Reports what occupies the board cell at the given coordinates, or nothing when it is out of reach. */
s32 Visdata_GetVisibilityCellState(ResourceBitGrid *resourceGrid, s32 cellX, s32 cellY) {
    s32 col;
    s32 row;
    s16 cell;
    if ((((f32) (cellX - resourceGrid->originX) < 0.0f) ? -(cellX - resourceGrid->originX) : (cellX - resourceGrid->originX)) >= 9) {
        return 0;
    }
    if ((((f32) (cellY - resourceGrid->originY) < 0.0f) ? -(cellY - resourceGrid->originY) : (cellY - resourceGrid->originY)) >= 9) {
        return 0;
    }
    col = (cellX - resourceGrid->originX) + 8;
    row = (cellY - resourceGrid->originY) + 8;
    cell = resourceGrid->cells[col + (row * 17)];
    if (cell == -2) {
        return 1;
    }
    if (cell == -3) {
        return 0;
    }
    if (cell == -1) {
        return 3;
    }
    return 2;
}

int Visdata_TestVisibilityGridBit(ResourceBitGrid *g,int x,int y,int z){
    int v; unsigned int adjusted;if(!(RW_ABS(x-g->originX)<9 && RW_ABS(y-g->originY)<9))return 0;v=g->cells[(x-g->originX)+8+((y-g->originY)+8)*17];if(v==-2)return 1;if(v==-3)return 0;adjusted=z+9;g->reader.bitPos=v+adjusted;return CBitReader_ReadBits(&g->reader,1)!=0;}

void Visdata_SelectVisibilityCell(ResourceBitGrid *resourceGrid, s32 x, s32 y)
{
    if (RW_ABS(x - resourceGrid->originX) >= 9) {
        return;
    }
    if (RW_ABS(y - resourceGrid->originY) >= 9) {
        return;
    }
    {
        s32 ddx = x - resourceGrid->originX;
        s32 ddy = y - resourceGrid->originY;
        s32 t = (ddy + 8) * 17 + 8;
        s16 val;
        ddx = ddx + t;
        val = resourceGrid->cells[ddx];
        if (val == -2) {
            resourceGrid->cellState = 1;
            return;
        }
        if (val == -3) {
            resourceGrid->cellState = 0;
            return;
        }
        if (val == -1) {
            resourceGrid->cellState = 3;
            return;
        }
        resourceGrid->cellState = 2;
        resourceGrid->reader.bitPos = val;
        resourceGrid->cellValue = CBitReader_ReadBits(&resourceGrid->reader, 9);
    }
}

s32 Visdata_ReadNextVisibilityBit(ResourceBitGrid *resourceGrid) {
    s32 field;
    field = resourceGrid->cellState;
    if (field != 2) {
        return field == 1;
    }
    return CBitReader_ReadBits(&resourceGrid->reader, 1) != 0;
}

void Visdata_BuildFrustumPlanes(PlaneEquation *planes, CVector3 *eye, CVector3 *c0, CVector3 *c1, CVector3 *c2, CVector3 *c3) {
    make_plane(&planes[2], c0, c1, c3, c0);
    make_plane(&planes[0], eye, c0, c2, eye);
    make_plane(&planes[1], eye, c3, c1, eye);
    make_plane(&planes[4], eye, c1, c0, eye);
    make_plane(&planes[3], eye, c2, c3, eye);
    planes[5].normal.x = -planes[2].normal.x;
    planes[5].normal.y = -planes[2].normal.y;
    planes[5].normal.z = -planes[2].normal.z;
    planes[5].distance = planes[5].normal.x * eye->x + planes[5].normal.y * eye->y + planes[5].normal.z * eye->z;
}

void Visdata_BuildPlaneFromPoints(void *planeEquation, void *rightVector, void *middleVector, void *leftVector) {
    PlaneEquation *plane = planeEquation;
    CVector3 *point = rightVector;
    CVector3 edgeRightToMiddle;
    CVector3 edgeMiddleToLeft;
    Graphu64_SubtractVectors(&edgeRightToMiddle, middleVector, rightVector);
    Graphu64_SubtractVectors(&edgeMiddleToLeft, leftVector, middleVector);
    Graphu64_CrossVectors(planeEquation, &edgeMiddleToLeft, &edgeRightToMiddle);
    Graphu64_NormalizeVec3(planeEquation);
    plane->distance = (plane->normal.x * point->x)
                                  + (plane->normal.y * point->y)
                                  + (plane->normal.z * point->z);
}

f32 Visdata_GetPlaneSegmentFraction(f32 *plane, f32 *segmentStart, f32 *segmentEnd) {
    f32 x;
    f32 y;
    f32 z;
    f32 dot1;
    f32 dot2;

    x = plane[0];
    y = plane[1];
    z = plane[2];
    dot1 = (x * segmentStart[0]) + (y * segmentStart[1]) + (z * segmentStart[2]);
    dot2 = (x * segmentEnd[0]) + (y * segmentEnd[1]) + (z * segmentEnd[2]);
    if (dot2 == dot1) {
        return g_planeParallelSegmentFraction;
    }
    return (plane[3] - dot1) / (dot2 - dot1);
}

f32 Visdata_EvaluatePlaneAtPoint(f32 *a, f32 *b) {
    return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]) - a[3];
}

/* Returns whether a point lies on the inner side of all six planes of a frustum, each stored as a normal and a distance. Adapted from Visdata_TestBoxAgainstFrustum with the per-axis box minimum replaced by the point's dot product with each plane normal, tested directly in the loop. */
s32 Visdata_ContainsPoint(f32 (*planes)[4], f32 *point) {
    s32 i;
    f32 *plane;

    for (i = 0; i < 6; i++) {
        plane = planes[i];
        if (!(plane[0] * point[0] + plane[1] * point[1] + plane[2] * point[2] <= plane[3])) {
            return 0;
        }
    }
    return 1;
}

/* Returns 1 when each of the six planes has at least one of the n points on or inside it (normal dot point <= plane distance), else 0. */

s32 Visdata_TestPointsAgainstFrustum(CQuatern *planes, s32 n, CVector3 *points) {
    s32 i;
    s32 j;
    s32 inside;

    for (i = 0; i < 6; i++) {
        inside = 0;
        for (j = 0; j < n; j++) {
            if (planes[i].x * points[j].x + planes[i].y * points[j].y + planes[i].z * points[j].z <= planes[i].w) {
                inside = 1;
                break;
            }
        }
        if (!inside) {
            return 0;
        }
    }
    return 1;
}

/* Returns 1 when every frustum plane except plane two has at least one of the points on its inner side. */
s32 Visdata_TestPointsAgainstFivePlanes(Frustum *frustum, s32 count, CVector3 *points) {
    s32 p;
    f32 *plane;

    for (p = 0; p < 6; p++) {
        if (p == 2) {
            continue;
        }
        plane = frustum->planes[p];
        if (!Visdata_AnyPointInsidePlane(points, count, plane)) {
            return 0;
        }
    }
    return 1;
}

/* Tests a box against six planes, returning 1 when for every plane the sum of the per-axis minimum products does not exceed the plane distance, else 0. Adapted from Visdata_TestBoxAgainstPlane, with its body inlined into a loop over six four-float planes and the loop-invariant product computed first. */

s32 Visdata_TestBoxAgainstFrustum(f32 (*planes)[4], f32 *boxBounds) {
    s32 i;
    s32 inside;
    f32 *plane;
    f32 normalX;
    f32 maximumXProduct;
    f32 normalY;
    f32 normalZ;
    f32 maximumYProduct;
    f32 maximumZProduct;
    f32 x;
    f32 y;
    f32 z;
    f32 sum;

    for (i = 0; i < 6; i++) {
        plane = planes[i];
        normalX = plane[0];
        maximumXProduct = boxBounds[3] * normalX;
        x = boxBounds[0] * normalX;
        if (!(x <= maximumXProduct)) {
            x = maximumXProduct;
        }
        normalY = plane[1];
        y = boxBounds[1] * normalY;
        maximumYProduct = boxBounds[4] * normalY;
        sum = x;
        if (!(y <= maximumYProduct)) {
            y = maximumYProduct;
        }
        sum += y;
        normalZ = plane[2];
        z = boxBounds[2] * normalZ;
        maximumZProduct = boxBounds[5] * normalZ;
        if (!(z <= maximumZProduct)) {
            z = maximumZProduct;
        }
        sum += z;
        inside = sum <= plane[3];
        if (!inside) {
            return 0;
        }
    }
    return 1;
}

s32 Visdata_TestBoxAgainstPlane(f32 *plane, f32 *boxBounds) {
    f32 normalX;
    f32 maximumXProduct;
    f32 normalY;
    f32 normalZ;
    f32 maximumYProduct;
    f32 maximumZProduct;
    f32 x;
    f32 y;
    f32 z;
    f32 sum;

    normalX = plane[0];
    x = boxBounds[0] * normalX;
    maximumXProduct = boxBounds[3] * normalX;
    if (!(x <= maximumXProduct)) {
        x = maximumXProduct;
    }
    normalY = plane[1];
    y = boxBounds[1] * normalY;
    maximumYProduct = boxBounds[4] * normalY;
    sum = x;
    if (!(y <= maximumYProduct)) {
        y = maximumYProduct;
    }
    sum += y;
    normalZ = plane[2];
    z = boxBounds[2] * normalZ;
    maximumZProduct = boxBounds[5] * normalZ;
    if (!(z <= maximumZProduct)) {
        z = maximumZProduct;
    }
    sum += z;
    if (sum <= plane[3]) {
        return 1;
    }
    return 0;
}

/* ROM-grounded data: src/g_planeParallelSegmentFractionStorageSource.c */
const float g_planeParallelSegmentFraction_StorageWords[1] = {
    1.0f,
};

/* G_ENGINESETN64RETAINEDWORDS4.CPP */
#if defined(VERSION_EU_X)
/* g_EngineSetn64RetainedWords4_SessionRetainedStorage2.CPP */
/* g_creditsBrotherTextFragmentEuX_SessionRetainedStorage2.CPP */
char g_creditsBrotherTextFragmentEuX[12] = "BROTHER. BE ";
#endif

/* G_VISDATAENCODEDBYTES.CPP */
#if defined(VERSION_US_REV1)
char g_VisdataEncodedBytes[12] = "\000\000\000\000GREY THA";
#endif
