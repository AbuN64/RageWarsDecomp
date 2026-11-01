#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_weaponFireStateCallbackTable[];

#if defined(VERSION_US_REV1)
RestConstantsEncodedWordsBlock7Layout411 k_ConstantsEncodedWordsBlock7 = {
    { 0, 0 },
    { 1.0f, 1.0f },
    { (void *)&g_weaponFireStateCallbackTable, 0, 0 },
};
#endif
