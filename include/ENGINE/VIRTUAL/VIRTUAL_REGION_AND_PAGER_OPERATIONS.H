#ifndef ENGINE_VIRTUAL_VIRTUAL_REGION_AND_PAGER_OPERATIONS_H
#define ENGINE_VIRTUAL_VIRTUAL_REGION_AND_PAGER_OPERATIONS_H
#include "COMMON/OWNERRECAT8V2.H"
extern void Vhandler_FreeVirtualRegion(s32 regionAddress);
extern void Vhandler_GetPagerCounters(struct PagerCounters *countersOut);
extern void Vhandler_UpdatePagerStatistics(void);
extern void Vhandler_MapBootstrapAddressRange(void);
#endif
