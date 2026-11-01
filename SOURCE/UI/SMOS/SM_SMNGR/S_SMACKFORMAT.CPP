#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#ifdef VERSION_DE
/* s_smackFormat_SSmackformat.CPP */
/* ROM-grounded data: rodata/writable/800D2B50 */
float s_smackFormat[4] = {
    0.0f, 3.1415927f, 0.0f, -3.1415927f,
};
#endif
#ifdef VERSION_EU
RestsmackFormatLayout345 s_smackFormat = {
    { 0, 0 },
    { -1.0f, -0.70710677f },
};
#endif
#ifdef VERSION_EU_X
char s_smackFormat[16] = "\000\000\000\000re\000\000Energy r";
#endif
#ifdef VERSION_US
RestsmackFormatLayout347 s_smackFormat = {
    0,
    "quR\000",
    { 14223616, 1048587 },
};
#endif
#ifdef VERSION_US_REV1
char s_smackFormat[16] = "\000\000\000\000\000\000\000\000Smack %s";
#endif
