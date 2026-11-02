#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
unsigned int g_timerintrDataAddressWords[1] = {
    0x8014FE38,
};
#endif
