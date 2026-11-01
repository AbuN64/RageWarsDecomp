#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const float k_CcollisionIntersectfrontplanefractionEncodedWords[3] = {
    1.0f, 1.0f, 1.0f,
};
#endif

#if defined(VERSION_US)
char s_CcollisionIntersectfrontplanefractionDwChText[8] =
    "\000\016m_dwCh";
#endif



#if defined(VERSION_DE)
float k_CcollisionIntersectfrontplanefractionEncodedWordsBlock1[2] = {
    0.4096f, 0.4096f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ccollisionIntersectfrontplanefractionOneWordsVariant2UsRev1.c */
const float k_CcollisionIntersectfrontplanefractionOneWordsVariant2[1] = {
    1.0f,
};

/* ROM-grounded data: src/ccollisionIntersectfrontplanefractionOneWordsUsRev1.c */
const float k_CcollisionIntersectfrontplanefractionOneWords[1] = {
    1.0f,
};

/* ROM-grounded data: src/ccollisionIntersectfrontplanefractionOneWordsVariant1UsRev1.c */
const float k_CcollisionIntersectfrontplanefractionOneWordsVariant1[1] = {
    1.0f,
};
#endif
