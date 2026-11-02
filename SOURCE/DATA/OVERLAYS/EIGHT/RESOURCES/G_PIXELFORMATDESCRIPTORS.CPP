#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "TYPES.H"

#include "DATA/GFXDATA/EVENT_HANDLER_CODE_TARGETS.H"
#include "include_asm.h"
#include "COMMON/FORMAT.H"
#include "DATA/PIXEL_FORMAT/G_PIXELFORMATDESCRIPTORS.H"

/* 800E2AD0.CPP */
#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_EventHandlersPointerWords1[6] = {
    { 5, 30000, (ResidentEventHandler)(void *)&g_eventHandlerCodeTargetId5 }, { 6, 30000, (ResidentEventHandler)(void *)&g_eventHandlerCodeTargetId6 }, { 7, 30000, (ResidentEventHandler)(void *)&g_eventHandlerCodeTargetId7 }, { 8, 30000, (ResidentEventHandler)(void *)&g_eventHandlerCodeTargetId8 }, { 3587, 30000, (ResidentEventHandler)(void *)&g_eventHandlerCodeTargetIdE03 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

/* 800E2B18.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E2AD0_unclaimed_E3718 */
#if defined(VERSION_US_REV1)
struct {
    u8 alignmentFill[8];
} g_GPixelformatdescriptorsWords1 __attribute__((aligned(4))) = {
    { 0xC2, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};
#endif
#endif

/* 800E2B18_2.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
Format g_pixelFormatDescriptors[36] = {
    { 0, 0, 0, 0, 0, { 0x0, 0x0, 0x0, 0x0 }, { -8, -8, -8, -8 } },
    { 1, 0, 16, 16, 16, { 0xF800, 0x7E0, 0x1F, 0x0 }, { 8, 3, -3, -8 } },
    { 2, 0, 16, 16, 16, { 0xF00, 0xF0, 0xF, 0xF000 }, { 4, 0, -4, 8 } },
    { 3, 0, 16, 16, 16, { 0xF000, 0xF00, 0xF0, 0xF }, { 8, 4, 0, -4 } },
    { 4, 0, 16, 16, 16, { 0x7C00, 0x3E0, 0x1F, 0x8000 }, { 7, 2, -3, 8 } },
    { 5, 0, 16, 16, 16, { 0xF800, 0x7C0, 0x3E, 0x1 }, { 8, 3, -2, -7 } },
    { 6, 0, 16, 16, 15, { 0x7C00, 0x3E0, 0x1F, 0x0 }, { 7, 2, -3, 7 } },
    { 7, 0, 16, 16, 15, { 0xF800, 0x7C0, 0x3E, 0x0 }, { 8, 3, -2, -8 } },
    { 8, 0, 24, 24, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, -8 } },
    { 9, 0, 24, 24, 24, { 0xF800, 0x7E0, 0x1F, 0xFF0000 }, { 8, 3, -3, 16 } },
    { 10, 0, 32, 32, 24, { 0xFF000000, 0xFF0000, 0xFF00, 0x0 }, { 24, 16, 8, -8 } },
    { 11, 0, 32, 32, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, 16 } },
    { 12, 0, 32, 32, 32, { 0xFF0000, 0xFF00, 0xFF, 0xFF000000 }, { 16, 8, 0, 24 } },
    { 13, 0, 32, 32, 32, { 0xFF000000, 0xFF0000, 0xFF00, 0xFF }, { 24, 16, 8, 0 } },
    { 14, 1, 4, 16, 16, { 0xF800, 0x7E0, 0x1F, 0x0 }, { 8, 3, -3, -8 } },
    { 15, 1, 4, 24, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, -8 } },
    { 16, 1, 4, 32, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, 16 } },
    { 17, 1, 4, 32, 24, { 0xFF000000, 0xFF0000, 0xFF00, 0x0 }, { 24, 16, 8, -8 } },
    { 18, 1, 4, 32, 32, { 0xFF0000, 0xFF00, 0xFF, 0xFF000000 }, { 16, 8, 0, 24 } },
    { 19, 1, 4, 32, 32, { 0xFF000000, 0xFF0000, 0xFF00, 0xFF }, { 24, 16, 8, 0 } },
    { 20, 1, 4, 16, 16, { 0xF800, 0x7C0, 0x3E, 0x1 }, { 8, 3, -2, -7 } },
    { 21, 1, 4, 16, 16, { 0x7C00, 0x3E0, 0x1F, 0x8000 }, { 7, 2, -3, 8 } },
    { 22, 1, 4, 16, 15, { 0xF800, 0x7C0, 0x3E, 0x0 }, { 8, 3, -2, -8 } },
    { 23, 1, 4, 16, 15, { 0x7C00, 0x3E0, 0x1F, 0x0 }, { 7, 2, -3, 7 } },
    { 24, 1, 8, 16, 16, { 0xF800, 0x7E0, 0x1F, 0x0 }, { 8, 3, -3, -8 } },
    { 25, 1, 8, 24, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, -8 } },
    { 26, 1, 8, 32, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, 16 } },
    { 27, 1, 8, 32, 24, { 0xFF000000, 0xFF0000, 0xFF00, 0x0 }, { 24, 16, 8, -8 } },
    { 28, 1, 8, 32, 32, { 0xFF0000, 0xFF00, 0xFF, 0xFF000000 }, { 16, 8, 0, 24 } },
    { 29, 1, 8, 32, 32, { 0xFF000000, 0xFF0000, 0xFF00, 0xFF }, { 24, 16, 8, 0 } },
    { 30, 1, 8, 16, 16, { 0xF800, 0x7C0, 0x3E, 0x1 }, { 8, 3, -2, -7 } },
    { 31, 1, 8, 16, 16, { 0x7C00, 0x3E0, 0x1F, 0x8000 }, { 7, 2, -3, 8 } },
    { 32, 1, 8, 16, 15, { 0xF800, 0x7C0, 0x3E, 0x0 }, { 8, 3, -2, -8 } },
    { 33, 1, 8, 16, 15, { 0x7C00, 0x3E0, 0x1F, 0x0 }, { 7, 2, -3, 7 } },
    { 34, 0, 4, 4, 4, { 0xF, 0x0, 0x0, 0x0 }, { -4, -8, -8, -8 } },
    { 35, 0, 8, 8, 8, { 0xFF, 0x0, 0x0, 0x0 }, { 0, -8, -8, -8 } },
};
#endif

#if defined(VERSION_US)
char s_GPixelformatdescriptorsALBOWTText[16] =
    "\000A\\\240\000\000\000\000L_BOWT\000\000";
#endif

/* 800E3270.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E2AD0_unclaimed_E3718_unclaimed_E3E70 */
unsigned int g_GPixelformatdescriptorsPointerWords1[4] = {
    (unsigned int)g_pixelFormatPointerWordsCodeTarget, 0x00000000, 0x00000089, 0x0000008A,
};
#endif
