#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/LIGHTDATA.H"
#include "TYPES.H"
#include "SYSTEM/DEFS_TOGGLESAVEDFLAG.H"

void Defs_ToggleSavedFlag(void) {
    g_pointLightBufferOffset = g_pointLightSavedBufferOffset;
    if (g_pointLightSavedBufferOffset == 0) {
        g_pointLightSavedBufferOffset = 32;
        return;
    }
    g_pointLightSavedBufferOffset = 0;
}

