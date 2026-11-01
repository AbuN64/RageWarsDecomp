#include "COMMON/ALFXPARAM.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GUMTXL2F.H"
#include "COMMON/TRIPLE.H"
#include <ultra64.h>

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const unsigned int k_perspectiveProjectionConstantWordsUsRev1[5] = {
    0x3C8EFA35, 0x3F000000, 0xBF800000, 0x40000000, 0x48000000,
};
#endif

          /* guMtxIdentF */


/* guPerspectiveF, drafted from ultralib src/gu/perspective.c. This library evaluates it in single
   precision against the cartridge's constants: pi/180 and 0.5 at g_perspectiveFloatAngleScale, -1 and 2 at
   g_perspectiveFloatDepthAndRangeLimits, 2 * 65536 and 2^31 at g_perspectiveFloatNormalizationLimits; the float-to-u16 conversion of the perspective
   normalisation is written out in GCC's order. */
 /* pi/180 */
 /* 0.5 */
 /* -1, followed by 2 */
 /* 2 * 65536, followed by 2^31 */

  /* guMtxF2L */
                     /* cosf */
                     /* sinf */
 /* pi/180 */
 /* half */
 /* -1 */
 /* 2 */
 /* 2 * 65536 */
 /* 2^31 */

/* guPerspective (libultra gu): builds a perspective projection into a fixed-point matrix and reports its normalisation. */
void guPerspective(Mtx *m, u16 *perspNorm, float fovy, float aspect, float near, float far, float scale) {
    f32 mf[4][4];
    f32 cot;
    f32 norm;
    s32 i, j;
    f32 *row = mf[0];

    guMtxIdentF((u8 *)row);
    fovy *= g_perspectiveFieldOfViewAngleScale;
    fovy *= g_perspectiveFieldOfViewHalfScale;
    cot = Math_Cosf(fovy) / Gu_Sinf(fovy);

    mf[0][0] = cot / aspect;
    mf[1][1] = cot;
    mf[2][2] = (near + far) / (near - far);
    mf[2][3] = g_perspectiveHomogeneousDepth;
    mf[3][2] = (2 * near * far) / (near - far);
    mf[3][3] = 0;

    for (i = 0; i < 4; i++) {
        f32 *element;
        j = 0;
        element = row;
        for (; j < 4; j++) {
            *element *= scale;
            element++;
        }
        row += 4;
    }

    if (perspNorm != 0) {
        if (near + far <= g_perspectiveNearFarNormalizationLimit) {
            *perspNorm = (u16)0xFFFF;
        } else {
            norm = g_perspectiveNormalizationScale / (near + far);
            *perspNorm = (u16)(u32)norm;
            if (*perspNorm <= 0) {
                *perspNorm = (u16)0x0001;
            }
        }
    }

    guMtxF2L(mf[0], m);
}

void guPerspectiveF(float mf[4][4], u16 *perspNorm, float fovy, float aspect, float near, float far, float scale)
{
    float cot;
    int i, j;
    float norm;
    unsigned int value;
    guMtxIdentF(mf);
    fovy *= g_perspectiveFloatAngleScale;
    fovy *= g_perspectiveFloatHalfAngleScale;
    cot = Math_Cosf(fovy) / Gu_Sinf(fovy);
    mf[0][0] = cot / aspect;
    mf[1][1] = cot;
    mf[2][2] = (near + far) / (near - far);
    mf[2][3] = g_perspectiveFloatDepthAndRangeLimits;
    mf[3][2] = (2 * near * far) / (near - far);
    mf[3][3] = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            mf[i][j] *= scale;
    if (perspNorm != (u16 *)0) {
        if (near + far <= (*(&g_perspectiveFloatDepthAndRangeLimits + 1))) {
            *perspNorm = (u16)0xFFFF;
        } else {
            norm = g_perspectiveFloatNormalizationLimits / (near + far);
            if (norm >= (*(&g_perspectiveFloatNormalizationLimits + 1))) {
                goto large;
            }
            value = (int)norm;
            goto converted;
        large:
            value = (int)(norm - (*(&g_perspectiveFloatNormalizationLimits + 1)));
            value |= 0x80000000;
        converted:
            *perspNorm = (u16)value;
            if (*perspNorm <= 0)
                *perspNorm = (u16)0x0001;
        }
    }
}

const unsigned int g_guMtxF2LConstantWords[6] = {
    0x3C8EFA35, 0x3F000000, 0xBF800000, 0x40000000, 0x48000000, 0x4F000000,
};

#if defined(VERSION_US)
unsigned int k_perspectiveProjectionDataWordsUs[8] = {
    0x0B000010, 0x000B0000, 0x00000010, 0x3C8EFA35, 0x3F000000, 0xBF800000, 0x40000000, 0x48000000,
};
#endif
