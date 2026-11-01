#include "include_asm.h"

#include "COMMON/PACKEDMESHMATERIAL.H"
#include "TYPES.H"
#include "ENGINE/PPDECOM.H"

s32 Ppdecom_UnpackResource(s32, s32);
/* A resource request's dispatch callback: unpacks the loaded request, its second argument. */
void CResource_UnpackRequest(s32 argument, s32 request)
{
  Ppdecom_UnpackResource(request, 0);
}
