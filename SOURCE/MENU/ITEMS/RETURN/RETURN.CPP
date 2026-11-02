#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "MENU/OBJECT1C8.H"
#include "MENU/ITEMS/ITEMS_PREPARECONTROLLERRETURN.H"

/* 80442BC8_13.CPP */
#if defined(VERSION_EU) || defined(VERSION_US_REV1)
/* Stores what Menu_ClassifyResourceRange returns for g_activeActorKind in g_controllerReturnResourceRange and sets g_controllerReturnPending to 1. */
extern s32 g_activeActorKind;

extern s32 Menu_ClassifyResourceRange(s32);

void Items_CacheIdentifierBand(void) {
    g_controllerReturnResourceRange = Menu_ClassifyResourceRange(g_activeActorKind);
    g_controllerReturnPending = 1;
}
#endif

/* 80443530_2.CPP */
#if defined(VERSION_US)
#include "TYPES.H"
extern s32 g_activeActorKind;
extern s32 Menu_ClassifyResourceRange(s32);

void Items_PrepareMenuReturnUs(void) {
    g_controllerReturnResourceRange = Menu_ClassifyResourceRange(g_activeActorKind);
    g_controllerReturnPending = 1;
}
#endif

/* 80406A88_23.CPP */
#if defined(VERSION_EU_X)
extern int Menu_ClassifyResourceRange(s32);
extern s32 g_activeActorKind;

void Items_PrepareControllerReturnEuX(void) {
    g_controllerReturnResourceRange = Menu_ClassifyResourceRange(g_activeActorKind);
    g_controllerReturnPending = 0;
}
#endif

/* 8043D1DC_7.CPP */
#if defined(VERSION_DE)
extern int g_activeActorKind;
extern int g_controllerReturnResourceRange;
extern int g_controllerReturnPending;
extern int Pickup_ClassifyMenuCode(int);

void Items_PrepareMenuReturnDe(void) {
    g_controllerReturnResourceRange = Pickup_ClassifyMenuCode(g_activeActorKind);
    g_controllerReturnPending = 1;
}
#endif

/* 80442BC8_14.CPP */
#if !(defined(VERSION_EU_X))
/* Stores what Menu_ClassifyResourceRange returns for g_activeActorKind in g_controllerReturnResourceRange and sets g_controllerReturnPending to 0. */
extern s32 g_activeActorKind;
#if defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern s32 Menu_ClassifyResourceRange(s32);
#else
extern s32 Pickup_ClassifyMenuCode(s32);
#endif

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

/* 800E2730.CPP */
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* ROM-grounded data: rodata/shared/800E2730 */
const char g_fmtDec4Pad[8] =
    "%04d\000\000\000\000";
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif
