#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

extern char Frontend_CancelPlayerCount[];
extern char Frontend_ConfirmPlayerCount[];
extern char Frontend_CreatePlayerCountScreenDe[];
extern char Frontend_CreatePlayerCountScreenEux[];
extern char Frontend_DecreasePlayerCount[];
extern char Frontend_DestroyPlayerCountScreen[];
extern char Frontend_IncreasePlayerCount[];
extern char Frontend_UpdatePlayerCountScreen[];
extern char g_Frontend_CancelPlayerCountPackedAddress24[];
extern char g_Frontend_ConfirmPlayerCountPackedAddress24[];
extern char g_Frontend_CreatePlayerCountScreenEuPackedAddress24[];
extern char g_Frontend_DecreasePlayerCountPackedAddress24[];
extern char g_Frontend_DestroyPlayerCountScreenPackedAddress24[];
extern char g_Frontend_IncreasePlayerCountPackedAddress24[];
extern char g_Frontend_UpdatePlayerCountScreenPackedAddress24[];

#include "include_asm.h"

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry eventHandlers0[8];
    u8 alignmentFill96[12];
} D_src_c64ed94a __attribute__((aligned(4))) = {
    { { 3592, 26, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePlayerCountScreen - 0x80000000U) }, { 3590, 26, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePlayerCountScreenDe - 0x80000000U) }, { 3587, 26, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyPlayerCountScreen - 0x80000000U) }, { 2, 26, (ResidentEventHandler)(void *)((char *)&Frontend_CancelPlayerCount - 0x80000000U) }, { 1, 26, (ResidentEventHandler)(void *)((char *)&Frontend_ConfirmPlayerCount - 0x80000000U) }, { 8, 26, (ResidentEventHandler)(void *)((char *)&Frontend_IncreasePlayerCount - 0x80000000U) }, { 7, 26, (ResidentEventHandler)(void *)((char *)&Frontend_DecreasePlayerCount - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0x7, 0x0, 0x0, 0x0, 0x13 }
};
typedef char D_src_c64ed94aSizeCheck[(sizeof(D_src_c64ed94a) == 108) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry handlers[8];
    u32 alignmentFill[3];
} D_src_c64ed94a __attribute__((aligned(4))) = {
    { { 3592, 26, (ResidentEventHandler)(void *)&g_Frontend_UpdatePlayerCountScreenPackedAddress24 }, { 3590, 26, (ResidentEventHandler)(void *)&g_Frontend_CreatePlayerCountScreenEuPackedAddress24 }, { 3587, 26, (ResidentEventHandler)(void *)&g_Frontend_DestroyPlayerCountScreenPackedAddress24 }, { 2, 26, (ResidentEventHandler)(void *)&g_Frontend_CancelPlayerCountPackedAddress24 }, { 1, 26, (ResidentEventHandler)(void *)&g_Frontend_ConfirmPlayerCountPackedAddress24 }, { 8, 26, (ResidentEventHandler)(void *)&g_Frontend_IncreasePlayerCountPackedAddress24 }, { 7, 26, (ResidentEventHandler)(void *)&g_Frontend_DecreasePlayerCountPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x020712D0, 0x00000250, 0x021712D0 }
};
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry D_src_c64ed94a[9] = {
    { 3592, 26, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePlayerCountScreen - 0x80000000U) }, { 3590, 26, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePlayerCountScreenEux - 0x80000000U) }, { 3587, 26, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyPlayerCountScreen - 0x80000000U) }, { 2, 26, (ResidentEventHandler)(void *)((char *)&Frontend_CancelPlayerCount - 0x80000000U) }, { 1, 26, (ResidentEventHandler)(void *)((char *)&Frontend_ConfirmPlayerCount - 0x80000000U) }, { 8, 26, (ResidentEventHandler)(void *)((char *)&Frontend_IncreasePlayerCount - 0x80000000U) }, { 7, 26, (ResidentEventHandler)(void *)((char *)&Frontend_DecreasePlayerCount - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
extern char g_Frontend_CreatePlayerCountScreenPackedAddress24[];
extern char g_Frontend_DestroyPlayerCountScreenPackedAddress242[];
extern char g_Frontend_UpdatePlayerCountScreenAddress[];
extern char g_Frontend_ConfirmPlayerCountPackedAddress242[];
extern char g_Frontend_CancelPlayerCountPackedAddress242[];
extern char g_Frontend_IncreasePlayerCountPackedAddress242[];
extern char g_Frontend_DecreasePlayerCountPackedAddress242[];
#if defined(VERSION_US)
ResidentEventHandlerEntry g_FrontendDispatchplayercounteventPointerWords1[8] = {
    { 3592, 26, (ResidentEventHandler)(void *)&g_Frontend_UpdatePlayerCountScreenAddress }, { 3590, 26, (ResidentEventHandler)(void *)&g_Frontend_CreatePlayerCountScreenPackedAddress24 }, { 3587, 26, (ResidentEventHandler)(void *)&g_Frontend_DestroyPlayerCountScreenPackedAddress242 }, { 2, 26, (ResidentEventHandler)(void *)&g_Frontend_CancelPlayerCountPackedAddress242 }, { 1, 26, (ResidentEventHandler)(void *)&g_Frontend_ConfirmPlayerCountPackedAddress242 }, { 8, 26, (ResidentEventHandler)(void *)&g_Frontend_IncreasePlayerCountPackedAddress242 }, { 7, 26, (ResidentEventHandler)(void *)&g_Frontend_DecreasePlayerCountPackedAddress242 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_FrontendDispatchplayercounteventPointerWords1[8] = {
    { 3592, 26, (ResidentEventHandler)(void *)&g_Frontend_UpdatePlayerCountScreenAddress }, { 3590, 26, (ResidentEventHandler)(void *)&g_Frontend_CreatePlayerCountScreenPackedAddress24 }, { 3587, 26, (ResidentEventHandler)(void *)&g_Frontend_DestroyPlayerCountScreenPackedAddress242 }, { 2, 26, (ResidentEventHandler)(void *)&g_Frontend_CancelPlayerCountPackedAddress242 }, { 1, 26, (ResidentEventHandler)(void *)&g_Frontend_ConfirmPlayerCountPackedAddress242 }, { 8, 26, (ResidentEventHandler)(void *)&g_Frontend_IncreasePlayerCountPackedAddress242 }, { 7, 26, (ResidentEventHandler)(void *)&g_Frontend_DecreasePlayerCountPackedAddress242 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

#if defined(VERSION_US)
char s_projectsDmPath_us[12] =
    "\\Projects\\DM";
#endif
