#include "Common/format.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "types.h"

/* NAV_UPDATEPATROLROUTE_DATA_PATROL.CPP */
#if defined(VERSION_EU)
struct {
    u8 retainedRecordWords[12];
} g_navUpdatePatrolRouteData __attribute__((aligned(4))) = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x0B, 0x28, 0x00 }
};
#endif
