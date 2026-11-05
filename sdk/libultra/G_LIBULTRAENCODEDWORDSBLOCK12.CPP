#include "../include/libgultra.h"

#if defined(VERSION_US_REV1)
unsigned int g_turretActivateTiming[3] = {
    0x00000000, 0x00000005, 0x00000000,
};

extern char Turret_Code_ACTIVATE_Address[];
unsigned int g_turretActivateCodeEntry[3] = {
    0x00000001, 0x00000000, (unsigned int)Turret_Code_ACTIVATE_Address,
};
#endif
