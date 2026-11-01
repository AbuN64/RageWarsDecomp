#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_romLookupTableText[15] =
    "ROMLookupTable\000";
#endif

#if defined(VERSION_US_REV1)
const char k_DefsReadresourcewordEncodedBytes[15] =
    "ROMLookupTable";
#endif
