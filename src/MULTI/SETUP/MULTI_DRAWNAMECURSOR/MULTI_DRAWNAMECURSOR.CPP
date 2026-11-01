#include "COMMON/SHARED_OPTIONSSCREEN.H"

extern char g_menuResidentRegionStart;

/* 12 stale bytes in front of the cinema context pointer (differ in every build, no instruction reads them). */
#if defined(VERSION_US_REV1)
unsigned int g_cinemaSequenceStatePad[3] = {
    0x00000001, 0x800D72CC, 0x00000002,
};
#endif

#if defined(VERSION_EU_X)
unsigned int g_cinemaSequenceStatePad[3] = {
    0x00000001, 0x800DD214, 0x00000002,
};
#endif

#if defined(VERSION_EU)
unsigned int g_cinemaSequenceStatePad[3] = {
    0x26E20020, 0x4A054A95, 0x30C30004,
};
#endif

#if defined(VERSION_DE)
unsigned int g_cinemaSequenceStatePad[3] = {
    0x00000000, 0x00000001, 0x00000000,
};
#endif

#if defined(VERSION_US)
unsigned int g_cinemaSequenceStatePad[3] = {
    0x75520000, 0x6A010000, 0x10000B00,
};
#endif

/* Context of the running cinema sequence: the resident menu region (read by CCinema_ResetSequenceContext, Cinema_* and the camera code). */
Shared_MenuContext *g_cinemaSequenceState = (Shared_MenuContext *)&g_menuResidentRegionStart;

/* Unused zero word after the pointer, read by no instruction. */
unsigned int g_cinemaSequenceStateTailPad = 0;
