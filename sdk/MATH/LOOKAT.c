#include "include_asm.h"
#include "types.h"
#include <PR/gbi.h>
#include "Common/resident_event_handler.h"
#include "Common/ballisticparams.h"
#include "Common/triple.h"
#include <platform_sdk.h>
#include "Common/alfxparam.h"

/* lookat.CPP */
void guLookAt(Mtx *out, f32 ex, f32 ey, f32 ez, f32 ax, f32 ay, f32 az, f32 ux, f32 uy, f32 uz)
{
    f32 matrix[4][4];
    f32 (*matrixPointer)[4] = matrix;
    f32 x, y, z, rx, ry, rz, vx, vy, vz, scale, one;
    guMtxIdentF(matrixPointer);
    x = ax - ex; y = ay - ey; z = az - ez;
    scale = g_lookAtInverseLengthScale / Gu_Sqrtf((x*x + y*y) + z*z);
    x *= scale; z *= scale; y *= scale;
    rx = uy*z - uz*y;
    ry = uz*x - ux*z;
    rz = ux*y - uy*x;
    one = g_lookAtUnitValue;
    scale = one / Gu_Sqrtf((rx*rx + ry*ry) + rz*rz);
    rx *= scale; rz *= scale; ry *= scale;
    vx = y*rz - z*ry;
    vy = z*rx - x*rz;
    vz = x*ry - y*rx;
    scale = one / Gu_Sqrtf((vx*vx + vy*vy) + vz*vz);
    vx *= scale; vy *= scale; vz *= scale;
    matrix[0][0] = rx; matrix[1][0] = ry; matrix[2][0] = rz;
    matrix[0][1] = vx; matrix[1][1] = vy; matrix[2][1] = vz;
    matrix[0][2] = x; matrix[1][2] = y; matrix[2][2] = z;
    matrix[0][3] = 0.0f; matrix[1][3] = 0.0f; matrix[2][3] = 0.0f;
    matrix[3][0] = -((ex*rx + ey*ry) + ez*rz);
    matrix[3][1] = -((ex*vx + ey*vy) + ez*vz);
    matrix[3][2] = -((ex*x + ey*y) + ez*z);
    matrix[3][3] = one;
    guMtxF2L(matrixPointer, out);
}

void guLookAtF(f32 matrix[4][4], f32 eyeX, f32 eyeY, f32 eyeZ,
                      f32 atX, f32 atY, f32 atZ, f32 upX, f32 upY, f32 upZ) {
    f32 lookX, lookY, lookZ;
    f32 rightX, rightY, rightZ;
    f32 scale, one;
    guMtxIdentF(matrix);
    lookX = atX - eyeX;
    lookY = atY - eyeY;
    lookZ = atZ - eyeZ;
    scale = g_lookAtFloatInverseLengthScale / Gu_Sqrtf(lookX * lookX + lookY * lookY + lookZ * lookZ);
    lookX *= scale;
    lookZ *= scale;
    lookY *= scale;
    rightX = upY * lookZ - upZ * lookY;
    rightY = upZ * lookX - upX * lookZ;
    rightZ = upX * lookY - upY * lookX;
    one = g_lookAtFloatUnitValue;
    scale = one / Gu_Sqrtf(rightX * rightX + rightY * rightY + rightZ * rightZ);
    rightX *= scale;
    rightZ *= scale;
    rightY *= scale;
    upX = lookY * rightZ - lookZ * rightY;
    upY = lookZ * rightX - lookX * rightZ;
    upZ = lookX * rightY - lookY * rightX;
    scale = one / Gu_Sqrtf(upX * upX + upY * upY + upZ * upZ);
    upX *= scale;
    upY *= scale;
    upZ *= scale;
    matrix[0][0] = rightX;
    matrix[1][0] = rightY;
    matrix[2][0] = rightZ;
    matrix[0][1] = upX;
    matrix[1][1] = upY;
    matrix[2][1] = upZ;
    matrix[0][2] = lookX;
    matrix[1][2] = lookY;
    matrix[2][2] = lookZ;
    matrix[3][0] = -(eyeX * rightX + eyeY * rightY + eyeZ * rightZ);
    matrix[3][1] = -(eyeX * upX + eyeY * upY + eyeZ * upZ);
    matrix[3][2] = -(eyeX * lookX + eyeY * lookY + eyeZ * lookZ);
    matrix[0][3] = 0.0f;
    matrix[1][3] = 0.0f;
    matrix[2][3] = 0.0f;
    matrix[3][3] = one;
}

/* cosf_data.c */
#if defined(VERSION_US)
unsigned int k_cosineSignedUnitWords[2] = {
    0xBF800000, 0x3F800000,
};
#endif

const unsigned int g_Math_CosfConstantWords_de_eu_eu_x_us_us_rev1[6] = {
    0x3FE00000, 0x00000000, 0x00000000, 0x00000000, 0x3FE00000, 0x00000000,
};

/* lookat.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const unsigned int k_LookatEncodedWords[1] = {
    0xBF800000,
};
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const unsigned int k_LookatEncodedWords[2] = {
    0xBF800000, 0x3F800000,
};
#endif
#endif

#if defined(VERSION_DE)
const float k_lookatUnit[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
const float k_LookatSignedUnitBoundsWords[2] = {
    -1.0f, 1.0f,
};
#endif
