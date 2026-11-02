#include "DATA/REST_SOURCE_RECORDS.H"
#include "TYPES.H"

#if defined(VERSION_US)
s32 g_audioSmallRoomParameters[26] = {
    3, 4000,
    0, 2160, 9830, -9830, 0, 0, 0, 0,
    760, 1520, 3276, -3276, 16383, 0, 0, 0,
    0, 2400, 5000, 0, 0, 0, 0, 20480,
};
s32 g_audioBigRoomParameters[34] = {
    4, 4000,
    0, 2640, 9830, -9830, 0, 0, 0, 0,
    880, 2160, 3276, -3276, 16383, 0, 0, 0,
    2640, 3640, 3276, -3276, 16383, 0, 0, 0,
    0, 3760, 8000, 0, 0, 0, 0, 20480,
};
s32 g_audioEchoParameters[10] = {
    1, 8000,
    0, 7160, 12000, 0, 32767, 0, 0, 0,
};
s32 g_audioChorusParameters[10] = {
    1, 800,
    0, 200, 16384, 0, 32767, 7600, 700, 0,
};
s32 g_audioFlangeParameters[10] = {
    1, 800,
    0, 200, 0, 24575, 32767, 380, 500, 0,
};
s32 g_audioNoEffectParameters[10] = {
    0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
#endif
