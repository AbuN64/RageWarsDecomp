#include "include_asm.h"
#include "Common/rotation_extraction.h"
#include "Common/memory_stream_buffer.h"
#include "Common/texture.h"
#include "Common/gfx_initializefrontendservices.h"
#include "Math/xmath_evaluateexponentialdouble.h"
#include "Menu/Gfx/gfx_shutdownfrontendservices.h"
#include "Resmgr/resmgr_stream_io.h"

void Gfx_InitializeFrontendServices(void) {
    XStdio_InitializeStreams();
    XMath_InitializeMath();
}

/* Calls the per-version setup entry and then XStdio_ShutdownStreams. */
void Gfx_ShutdownFrontendServices(void) {
#if defined(VERSION_US)

#if defined(VERSION_US)
XMath_ShutdownMath
#else
XMath_ShutdownMath
#endif
();
#elif defined(VERSION_DE)
    XMath_ShutdownMath();
#elif defined(VERSION_EU)
    XMath_ShutdownMath();
#elif defined(VERSION_EU_X)
    XMath_ShutdownMath();
#else
    XMath_ShutdownMath();
#endif
    XStdio_ShutdownStreams();
}
