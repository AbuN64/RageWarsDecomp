#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "TYPES.H"

/* Calls Tsmos_SetModeOneFlag with 2 and returns zero. */


s32 Timed_SetConfirmationInputMode(void) {
    Tsmos_SetModeOneFlag(2);
    return 0;
}
