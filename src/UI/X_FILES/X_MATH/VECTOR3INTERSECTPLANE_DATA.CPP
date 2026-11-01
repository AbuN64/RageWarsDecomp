#include "include_asm.h"
#include "COMMON/OBJRECAT3CV2.H"

#if !(defined(VERSION_US_REV1))
const float k_vector3intersectplaneDataFloatConstantWords[9] = {
    0.001f, -0.001f, 0.5f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_vector3intersectplaneDataFloatConstantWordsBlock1_Vector3intersectplaneData.c */
const float k_vector3intersectplaneDataFloatConstantWordsBlock1[3] = {
    0.001f, -0.001f, 0.5f,
};

/* ROM-grounded data: src/k_VectorIntersectplaneOneWords_Vector3intersectplaneData.c */
const float k_VectorIntersectplaneOneWords[1] = {
    1.0f,
};

/* ROM-grounded data: src/k_VectorIntersectplaneOneWordsVariant1_Vector3intersectplaneData.c */
const float k_VectorIntersectplaneOneWordsVariant1[1] = {
    1.0f,
};

/* ROM-grounded data: src/k_VectorIntersectplaneOneWordsVariant2_Vector3intersectplaneData.c */
const float k_VectorIntersectplaneOneWordsVariant2[1] = {
    1.0f,
};

/* ROM-grounded data: src/k_VectorIntersectplaneOneWordsVariant3_Vector3intersectplaneData.c */
const float k_VectorIntersectplaneOneWordsVariant3[1] = {
    1.0f,
};

/* ROM-grounded data: src/k_VectorIntersectplaneOneWordsVariant4_Vector3intersectplaneData.c */
const float k_VectorIntersectplaneOneWordsVariant4[1] = {
    1.0f,
};

/* ROM-grounded data: src/k_VectorIntersectplaneOneWordsVariant5_Vector3intersectplaneData.c */
const float k_VectorIntersectplaneOneWordsVariant5[1] = {
    1.0f,
};
#endif
