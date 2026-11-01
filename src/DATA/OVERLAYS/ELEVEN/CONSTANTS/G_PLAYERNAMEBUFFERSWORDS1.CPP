#include "TYPES.H"

#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_player_name_buffers_us_rev1.c */
extern char g_multiplayerSavedPlayerNames[];
void *g_PlayerNameBuffersWords1[4] = {
    g_multiplayerSavedPlayerNames, (void *)(g_multiplayerSavedPlayerNames + 24), (void *)(g_multiplayerSavedPlayerNames + 48), (void *)(g_multiplayerSavedPlayerNames + 72),
};
#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
char k_DebugMenuRetainedStorageEncodedHalfwords[2] __attribute__((aligned(2))) = "os";
#endif
#endif
