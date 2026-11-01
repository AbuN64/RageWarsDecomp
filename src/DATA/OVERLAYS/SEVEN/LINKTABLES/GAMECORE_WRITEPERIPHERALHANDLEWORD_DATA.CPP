extern struct OSPiHandle_s g_diskPiHandle;
extern struct OSPiHandle_s g_diskPeripheralHandle;
#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    void * g_peripheralDomainHandles[2];
    u8 alignmentFill8[8];
} D_src_af61b546 __attribute__((aligned(2))) = {
    { (void *)&g_diskPiHandle, (void *)&g_diskPeripheralHandle },
    { 0x3f, 0x40, 0x0, 0x0, 0x3f, 0x0, 0x0, 0x0 }
};
typedef char D_src_af61b546SizeCheck[(sizeof(D_src_af61b546) == 16) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    void * g_peripheralDomainHandles[2];
    u8 alignmentFill8[8];
} D_src_af61b546 __attribute__((aligned(2))) = {
    { (void *)&g_diskPiHandle, (void *)&g_diskPeripheralHandle },
    { 0x68, 0x69, 0x76, 0x65, 0x20, 0x6f, 0x66, 0x20 }
};
typedef char D_src_af61b546SizeCheck[(sizeof(D_src_af61b546) == 16) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    void * g_peripheralDomainHandles[2];
    u8 alignmentFill8[8];
} D_src_af61b546 __attribute__((aligned(2))) = {
    { (void *)&g_diskPiHandle, (void *)&g_diskPeripheralHandle },
    { 0x2, 0x0, 0x4, 0x0, 0x8, 0x0, 0x10, 0x0 }
};
typedef char D_src_af61b546SizeCheck[(sizeof(D_src_af61b546) == 16) ? 1 : -1];
#endif
#endif
#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    void * g_peripheralDomainHandles[2];
    u8 alignmentFill8[8];
} D_src_af61b546 __attribute__((aligned(2))) = {
    { (void *)&g_diskPiHandle, (void *)&g_diskPeripheralHandle },
    { 0x0, 0x4, 0x0, 0x0, 0x0, 0x1c, 0x53, 0x46 }
};
typedef char D_src_af61b546SizeCheck[(sizeof(D_src_af61b546) == 16) ? 1 : -1];
#endif
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
void * g_gamecoreWriteperipheralhandlewordDataAddressWords[2] = {
    (void *)&g_diskPiHandle, (void *)&g_diskPeripheralHandle,
};
#endif
