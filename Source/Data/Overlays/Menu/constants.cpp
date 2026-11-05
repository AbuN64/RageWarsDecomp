#include "types.h"
#include "include_asm.h"

/* SKY_POSTSCALEDSCREENMESSAGE_DATA.CPP */
#if defined(VERSION_US_REV1)
#include "Data/Common/menu_times_text_fragment_us_rev1_data.h"
#include "Common/aiprofile.h"
extern void *g_skyPostscaledscreenmessageDataAddressWords[3];
#endif

/* ALFXNEW_DATA.CPP */
#if defined(VERSION_US_REV1)
struct {
    u32 type;
    u32 control;
    u32 width;
    u32 burst;
} g_alfxnewDataConstantWords __attribute__((aligned(4))) = {
    0x00000000,
    0x0000324E,
    0x00000500,
    0x04651E39
};

s32 g_audioSmallRoomParameters[26] = {
    3, 4000, 0, 2160, 9830, -9830, 0, 0,
    0, 0, 760, 1520, 3276, -3276, 16383, 0,
    0, 0, 0, 2400, 5000, 0, 0, 0,
    0, 20480
};

s32 g_audioBigRoomParameters[34] = {
    4, 4000, 0, 2640, 9830, -9830, 0, 0,
    0, 0, 880, 2160, 3276, -3276, 16383, 0,
    0, 0, 2640, 3640, 3276, -3276, 16383, 0,
    0, 0, 0, 3760, 8000, 0, 0, 0,
    0, 20480
};

s32 g_audioEchoParameters[10] = {
    1, 8000, 0, 7160, 12000, 0, 32767, 0,
    0, 0
};

s32 g_audioChorusParameters[10] = {
    1, 800, 0, 200, 16384, 0, 32767, 7600,
    700, 0
};

s32 g_audioFlangeParameters[10] = {
    1, 800, 0, 200, 0, 24575, 32767, 380,
    500, 0
};
#endif
