#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_WeaponStateEndD0664UsRev1[];

#if defined(VERSION_US_REV1)
RestConstantsEncodedWordsBlock15Layout407 k_ConstantsEncodedWordsBlock15 = {
    { 0, 0 },
    { 1.0f, 1.0f },
    { (void *)((char *)&g_WeaponStateEndD0664UsRev1 + 32), 0, 0 },
};
#endif
