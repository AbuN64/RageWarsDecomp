#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_FINDPROFILEOWNER.H"

/* Returns the index of the first of four 400-byte records in g_profileSlotResetWord whose byte at offset 4
   equals the second argument and whose first word equals the first, or -1 when none does. */


extern struct LinkedProfileOwnerRecord g_profileSlotResetWord[];

s32 Frontend_FindProfileOwner(s32 id, s32 kind) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_profileSlotResetWord[i].kind == kind && g_profileSlotResetWord[i].id == id) {
            return i;
        }
    }
    return -1;
}
