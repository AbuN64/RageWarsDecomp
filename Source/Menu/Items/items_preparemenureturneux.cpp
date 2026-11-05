#include "types.h"
#include "Ai/player_symbols.h"
#include "Menu/identifier.h"
#include "Common/runtime_declarations.h"

#if defined(VERSION_EU_X)
void Items_PrepareMenuReturnEuX(void) {
    g_controllerReturnResourceRange = Menu_ClassifyResourceRange(g_activeActorKind);
    g_controllerReturnPending = 1;
}
#endif
