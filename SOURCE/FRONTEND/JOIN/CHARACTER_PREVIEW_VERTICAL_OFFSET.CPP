#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const unsigned char g_characterPreviewVerticalOffset[3] = {
    0x42, 0x20, 0x00,
};
#endif
#endif
#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
const float g_characterPreviewVerticalOffset40UsRev1 = 40.0f;
#endif
