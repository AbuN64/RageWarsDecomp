#include "COMMON/CHEATCODE.H"
#include "TYPES.H"
#include "MENU/ENCODED_RESETTEXTENTRYRESULT.H"

/* Resets g_encodedCheatCharacterIndex to -1. */

extern u32 g_encodedCheatCharacterIndex;

void Encoded_ResetTextEntryResult(void) {
    g_encodedCheatCharacterIndex = -1;
}
