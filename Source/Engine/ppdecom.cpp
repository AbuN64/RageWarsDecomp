#include "include_asm.h"
#include "Common/packedmeshmaterial.h"
#include "types.h"
#include "Engine/ppdecom.h"
#include "Common/ppdecom_unpackresource.h"
#include "LIBC.H"
#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Render/particle_spawninterpolatedtrail.h"
#include <platform_sdk.h>
#include "libgultra_inferred/RNC_UNPACKMETHOD2.H"
#include "libgultra/RNC_UNPACKMETHOD1.H"
#include "Engine/Cache/cache.h"
#include "Engine/Cache/cache_allocresourceblock.h"
#include "Ppdecom/ppdecom_quicksortrecords.h"

/* CRESOURCE_UNPACKREQUEST.CPP */


/* A resource request's dispatch callback: unpacks the loaded request, its second argument. */
void CResource_UnpackRequest(s32 argument, s32 request)
{
    Ppdecom_UnpackResource(request, 0);
}

/* PPDECOM_UNPACKRESOURCE.CPP */

/* Unpack or copy a resource into an allocated buffer and install it. */
s32 Ppdecom_UnpackResource(void **handle, s32 retainUncompressed) {
    s32 succeeded;
    u8 compressionMethod;
    void **block;
    ResourcePayloadSizeView *sourceBlock;
    RncCompressedResourceHeaderView *packedHeader;
    ResourcePayloadSizeView *copySourceBlock;
    sourceBlock = *handle;
    packedHeader = sourceBlock->payload;
    if ((packedHeader->magicAndMethod & ~0xFF) == 0x524E4300) {
        if (retainUncompressed != 0) {
            block = Cache_AllocatePinnedResourceBlock(0, (s32) handle, packedHeader->decodedByteCount);
        } else {
            block = Cache_AllocResourceBlock(0, handle, packedHeader->decodedByteCount);
        }
        if (block != NULL) {
            compressionMethod = packedHeader->magicAndMethod; /* the method: low byte of the RNC magic word */
            switch (compressionMethod) {
            case 1:
                Rnc_UnpackMethod1(&packedHeader->payloadStart, *block, packedHeader->packedByteCount, packedHeader->decodedByteCount);
                break;
            case 2:
                Rnc_UnpackMethod2(packedHeader, *block, packedHeader->packedByteCount, packedHeader->decodedByteCount);
                break;
            default:
                break;
            }
            succeeded = 1;
        } else {
            succeeded = 0;
        }
    } else if (retainUncompressed == 0) {
        block = Cache_AllocResourceBlock(0, handle, sourceBlock->byteCount);
        if (block != NULL) {
            copySourceBlock = *handle;
            succeeded = 1;
            Libc_CopyBytes(*block, copySourceBlock->payload, copySourceBlock->byteCount);
        } else {
            succeeded = 0;
        }
    } else {
        succeeded = 1;
        goto done;
    }
    Cache_ReplaceResourceBlock(0, handle, block);
    done:
    return succeeded;
}
