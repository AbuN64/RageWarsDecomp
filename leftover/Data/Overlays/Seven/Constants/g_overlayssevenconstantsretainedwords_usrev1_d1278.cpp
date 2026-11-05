#include "Data/Overlays/Weaponslot/constants_addresses.h"

#if defined(VERSION_US_REV1)
extern char D_800CD710_us_rev1[];
extern char D_800CD890_us_rev1[];
extern char D_800CD9B8_us_rev1[];
unsigned int g_OverlaysSevenConstantsRetainedWords_usrev1_D1278[17] = {
    0x3FC6AF3A, 0x3FC68F30, 0x00000000, 0x00000000, (unsigned int)&D_800CD9B8_us_rev1[24], (unsigned int)&g_ActorStateEntryFragmentEncodedWords[7], 0x800CD4A0, 0x00000000,
    (unsigned int)&k_triggerActorActionHandlers[7], (unsigned int)D_800CD710_us_rev1, 0x00000000, (unsigned int)&D_800CD890_us_rev1[16], (unsigned int)&k_breakableActionHandlers[7], 0x00000000, 0x00000000,
    0x00000000,
    0x00000000,
};
#endif
