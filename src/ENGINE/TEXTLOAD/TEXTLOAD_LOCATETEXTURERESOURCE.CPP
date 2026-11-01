#include "COMMON/RESIDENTSTATE.H"
#include "TYPES.H"
#include "COMMON/TEXTURE_REQUEST.H"
#include "COMMON/WORLD.H"
#include "ENGINE/TEXTLOAD.H"

/** Store two words into a two-word value. */
void Textload_SetResourceLocation(int *value, int first, int second) {
    value[0] = first;
    value[1] = second;
}

void Textload_LocateTextureResource(s32 *resourcePair, s32 sectionIndex) {
    Scene_LocateTextureResource(&g_world, sectionIndex, resourcePair, resourcePair + 1);
}
