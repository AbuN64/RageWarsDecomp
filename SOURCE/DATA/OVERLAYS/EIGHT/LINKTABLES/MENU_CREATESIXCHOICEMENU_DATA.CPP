#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "TYPES.H"

extern char g_Menu_CancelSixChoiceMenuPackedAddress24[];
extern char g_Menu_ChooseSixChoiceOptionPackedAddress24[];
extern char g_Menu_CreateSixChoiceMenuPackedAddress24[];
extern char g_Menu_DestroySixChoiceMenuPackedAddress24[];
extern char g_Menu_UpdateSixChoiceMenuPackedAddress24[];

#include "include_asm.h"

/* 800E444C_2.CPP */
/* ROM-grounded data: rodata/writable/800E4450 */
#if defined(VERSION_DE)
struct {
    void * g_sixChoiceMenuState;
} k_MenuCreatesixchoicemenuZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuCreatesixchoicemenuZeroWordsSizeCheck[(sizeof(k_MenuCreatesixchoicemenuZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * g_sixChoiceMenuState;
} k_MenuCreatesixchoicemenuZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuCreatesixchoicemenuZeroWordsSizeCheck[(sizeof(k_MenuCreatesixchoicemenuZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_sixChoiceMenuState;
} k_MenuCreatesixchoicemenuZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuCreatesixchoicemenuZeroWordsSizeCheck[(sizeof(k_MenuCreatesixchoicemenuZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_sixChoiceMenuState;
} k_MenuCreatesixchoicemenuZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuCreatesixchoicemenuZeroWordsSizeCheck[(sizeof(k_MenuCreatesixchoicemenuZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_sixChoiceMenuState;
} k_MenuCreatesixchoicemenuZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuCreatesixchoicemenuZeroWordsSizeCheck[(sizeof(k_MenuCreatesixchoicemenuZeroWords) == 4) ? 1 : -1];
#endif

/* 800E4454.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char g_Menu_DispatchExtraOptionsEventAddress[];
extern char g_Menu_DispatchSixChoiceEventAddress[];
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry handlers[6];
    u32 alignmentFill[1];
} D_src_3fb7e4b3 __attribute__((aligned(4))) = {
    { { 3592, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 404) }, { 3590, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 152) }, { 3587, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 356) }, { 2, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 828) }, { 1, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 656) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x004221F0 }
};
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry handlers[6];
    u32 alignmentFill[1];
} D_src_3fb7e4b3 __attribute__((aligned(4))) = {
    { { 3592, 27, (ResidentEventHandler)(void *)&g_Menu_UpdateSixChoiceMenuPackedAddress24 }, { 3590, 27, (ResidentEventHandler)(void *)&g_Menu_CreateSixChoiceMenuPackedAddress24 }, { 3587, 27, (ResidentEventHandler)(void *)&g_Menu_DestroySixChoiceMenuPackedAddress24 }, { 2, 27, (ResidentEventHandler)(void *)&g_Menu_CancelSixChoiceMenuPackedAddress24 }, { 1, 27, (ResidentEventHandler)(void *)&g_Menu_ChooseSixChoiceOptionPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x40013000 }
};
#endif
#endif
#if defined(VERSION_EU_X)
extern char g_Menu_DispatchExtraOptionsEventAddress[];
#if defined(VERSION_EU_X)
struct {
    ResidentEventHandlerEntry handlers[6];
    u32 alignmentFill[1];
} D_src_3fb7e4b3 __attribute__((aligned(4))) = {
    { { 3592, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 404) }, { 3590, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 152) }, { 3587, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 356) }, { 2, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 828) }, { 1, 27, (ResidentEventHandler)(void *)(g_Menu_DispatchExtraOptionsEventAddress + 656) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x00000007 }
};
#endif
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
extern char g_menu_CreateSixChoiceMenuEntry[];
extern char g_menu_DestroySixChoiceMenuEntry[];
extern char g_Menu_UpdateSixChoiceMenuAddress[];
extern char g_menu_ChooseSixChoiceOptionEntry[];
extern char g_menu_CancelSixChoiceMenuEntry[];
#if defined(VERSION_US)
ResidentEventHandlerEntry g_MenuCreatesixchoicemenuEncodedWords[6] = {
    { 3592, 27, (ResidentEventHandler)(void *)&g_Menu_UpdateSixChoiceMenuAddress }, { 3590, 27, (ResidentEventHandler)(void *)&g_menu_CreateSixChoiceMenuEntry }, { 3587, 27, (ResidentEventHandler)(void *)&g_menu_DestroySixChoiceMenuEntry }, { 2, 27, (ResidentEventHandler)(void *)&g_menu_CancelSixChoiceMenuEntry }, { 1, 27, (ResidentEventHandler)(void *)&g_menu_ChooseSixChoiceOptionEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_MenuCreatesixchoicemenuEncodedWords[6] = {
    { 3592, 27, (ResidentEventHandler)(void *)&g_Menu_UpdateSixChoiceMenuAddress }, { 3590, 27, (ResidentEventHandler)(void *)&g_menu_CreateSixChoiceMenuEntry }, { 3587, 27, (ResidentEventHandler)(void *)&g_menu_DestroySixChoiceMenuEntry }, { 2, 27, (ResidentEventHandler)(void *)&g_menu_CancelSixChoiceMenuEntry }, { 1, 27, (ResidentEventHandler)(void *)&g_menu_ChooseSixChoiceOptionEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
char k_MenuCreatesixchoicemenuTailWords[4] __attribute__((aligned(4))) = "\000\000\000+";
#endif
#endif
