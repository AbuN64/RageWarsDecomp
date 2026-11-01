#include "include_asm.h"
#if !(defined(VERSION_DE) || defined(VERSION_US))
#ifdef VERSION_US_REV1
#include "COMMON/GAMEPLAY_SOUND_TABLE.H"
extern void *g_screenMessageTextSlot;
/* event message table read by Events_PostGameplayMessage / Link_DispatchMatchingTriggers / Action_ShowTriggerMessage:
   entry 0 points at the slot holding the screen message text pointer, entry 1 is unused */
GameplaySoundEntry g_gameplaySoundTable[2] = {
    { (s32 *)&g_screenMessageTextSlot, 0 },
    { 0, 0 },
};
/* 12 bytes of stale fill behind the table (0x000E0204, 2, 0x500), read by nothing */
unsigned int g_gameplaySoundTablePad[3] = {
    0x000E0204, 0x00000002, 0x00000500,
};
#endif
#endif
