#include "COMMON/RESIDENTSTATE.H"
#include "TYPES.H"
#include "COMMON/TEXTURE_REQUEST.H"
#include "COMMON/WORLD.H"

/* Request a texture resource with synchronous loading. */
void **Textload_RequestTextureVariationSync(s32 *resource, s32 variation)
{
    return rw_request_texture_sync(resource, variation);
}

/* Request a texture resource with asynchronous loading. */
s32 **Textload_RequestTextureVariation(s32 *resource, s32 variation)
{
    return rw_request_texture(resource, variation, 0);
}
