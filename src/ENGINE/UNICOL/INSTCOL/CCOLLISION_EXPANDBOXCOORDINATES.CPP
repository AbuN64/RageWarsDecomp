#include "include_asm.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RENDERSORTRECORD.H"
#include "ENGINE/UNICOL/INSTCOL.H"

/** Expand six source floats into the fixed 24-float vertex pattern. */
void CCollision_ExpandBoxCoordinates(float *s, float *d) {
    d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; d[3]=s[3];
    d[4]=s[1]; d[5]=s[2]; d[6]=s[3]; d[7]=s[1];
    d[8]=s[5]; d[9]=s[0]; d[10]=s[1]; d[11]=s[5];
    d[12]=s[0]; d[13]=s[4]; d[14]=s[2]; d[15]=s[3];
    d[16]=s[4]; d[17]=s[2]; d[18]=s[3]; d[19]=s[4];
    d[20]=s[5]; d[21]=s[0]; d[22]=s[4]; d[23]=s[5];
}

/** Swap two eight-byte pairs. */
void CRenderSortRecord_Swap(RenderSortRecord *left, RenderSortRecord *right) {
    RenderSortRecord temporary = *left;
    *left = *right;
    *right = temporary;
}

/** Order two records by their scalar at offset four. */
int CRenderSortRecord_CompareDepth(RenderSortRecord *left, RenderSortRecord *right) {
    return left->depth < right->depth ? -1 : 1;
}

