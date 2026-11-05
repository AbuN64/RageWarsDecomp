#include "Common/runtime_declarations.h"
#include "types.h"
#include "Menu/menu_item_views.h"
#include "Menu/Items/items_preparecontrollerreturn.h"
#include "Menu/identifier.h"
#include "Pickup/pickup.h"
#include "Menu/Items/Return/return_symbols.h"

#if defined(VERSION_EU) || defined(VERSION_US_REV1)
/* Stores what Menu_ClassifyResourceRange returns for g_activeActorKind in g_controllerReturnResourceRange and sets g_controllerReturnPending to 1. */
void Items_CacheIdentifierBand(void) {
    g_controllerReturnResourceRange = Menu_ClassifyResourceRange(g_activeActorKind);
    g_controllerReturnPending = 1;
}
#endif

#if defined(VERSION_US)

void Items_PrepareMenuReturnUs(void) {
    g_controllerReturnResourceRange = Menu_ClassifyResourceRange(g_activeActorKind);
    g_controllerReturnPending = 1;
}
#endif

#if defined(VERSION_EU_X)

void Items_PrepareControllerReturnEuX(void) {
    g_controllerReturnResourceRange = Menu_ClassifyResourceRange(g_activeActorKind);
    g_controllerReturnPending = 0;
}
#endif

#if defined(VERSION_DE)

void Items_PrepareMenuReturnDe(void) {
    g_controllerReturnResourceRange = Pickup_ClassifyMenuCode(g_activeActorKind);
    g_controllerReturnPending = 1;
}
#endif

#if !(defined(VERSION_EU_X))
/* Stores what Menu_ClassifyResourceRange returns for g_activeActorKind in g_controllerReturnResourceRange and sets g_controllerReturnPending to 0. */
void Items_PrepareControllerReturn(void) {
    g_controllerReturnResourceRange =
#if defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
Menu_ClassifyResourceRange
#else
Pickup_ClassifyMenuCode
#endif
(g_activeActorKind);
    g_controllerReturnPending = 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
const char g_fmtDecPadLong[8] =
    "%04d\000\000\000\000";
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif
