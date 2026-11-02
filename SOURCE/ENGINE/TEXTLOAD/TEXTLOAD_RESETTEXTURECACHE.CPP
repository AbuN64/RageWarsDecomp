#include "COMMON/FRUSTUM.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "SYSTEM/TEXTLOAD_RESETTEXTURECACHE.H"

/** Clear the global word at VRAM 0x800D2B00. */

void TextLoad_ResetTextureCache(void) {
    g_textureCacheResource = 0;
}


/** Replace the global state word. */
void Textload_SetTextureEffect(unsigned int value) {
    g_texturePaletteOverrideEnabled = value;
}
