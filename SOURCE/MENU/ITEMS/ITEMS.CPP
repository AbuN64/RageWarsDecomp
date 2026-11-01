#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#if defined(VERSION_EU)
/* Picks the label for each of the eight option rows (ids 2..9): the first text when the row's flag is set, else the second. */
typedef struct { s32 id; u8 pad4[0x10]; char ***text; } OptionRowEu;
#endif
#if defined(VERSION_EU_X)
#include "TYPES.H"
/* 80443530.CPP */
extern s32 g_activeActorKind;
extern s32 Menu_ClassifyResourceRange(s32);
void Items_PrepareMenuReturnEuX(void) {
    g_controllerReturnResourceRange = Menu_ClassifyResourceRange(g_activeActorKind);
    g_controllerReturnPending = 1;
}
#endif
