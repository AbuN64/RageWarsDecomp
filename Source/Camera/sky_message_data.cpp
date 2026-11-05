#include "types.h"

#if defined(VERSION_DE)
unsigned int k_SkyPostscreenmessageQuarterWords[1] = {
    0x3E800000,
};
#endif

#if defined(VERSION_US_REV1)
struct {
    u8 retainedRecordWords[4];
} g_linkTablesTrailingRecordWord __attribute__((aligned(4))) = {
    { 0x00, 0x26, 0x98, 0x04 }
};
#endif

#if defined(VERSION_US)
unsigned int k_RecycleTextWordFragmentEncodedWords[1] = {
    0x6D5F4861,
};
#endif
