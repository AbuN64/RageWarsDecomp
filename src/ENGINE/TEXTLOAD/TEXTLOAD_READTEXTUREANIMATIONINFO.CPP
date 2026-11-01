#include "COMMON/RESIDENTSTATE.H"
#include "TYPES.H"
#include "RENDER/SETN64_GETPACKSECTION.H"





void Textload_ReadTextureAnimationInfo(s32 **textureResource, Shared_AnimInfo *animInfo) {
    s32 *texturePack;
    s32 *tmp;

    texturePack = *textureResource;
    if (*texturePack != 0) {
        animInfo->frame = SetN64_GetPackSection(texturePack, 0);
        tmp = SetN64_GetPackSection(texturePack, 1);
        animInfo->count = *tmp;
        tmp = SetN64_GetPackSection(texturePack, 2);
        animInfo->variationCount = *tmp;
        return;
    }
    animInfo->frame = 0;
    animInfo->count = 0;
    animInfo->variationCount = 0;
}
