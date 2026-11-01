#ifndef COMMON_CACHE_RELEASERESOURCE_H
#define COMMON_CACHE_RELEASERESOURCE_H
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"







/* The copied prefix is exactly 0x50 bytes. */






/* The two adjacent track constants are consumed at base and base+4. */





extern void Cache_ReleaseResource(void *cacheContext, void *resource);
#endif
