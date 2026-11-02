#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Reads two values and reports whether the first reaches the rounded object size when the second is nonzero. */

extern int Note_GetFreePages(int slot, int *score);
extern s32 Note_CountFreeNotes(s32 ch, s32 *count);

extern u32 Note_BytesToPakPages(u32 bytes);

s32 PAKInterface_CheckRecordsNoteCapacity(void *slot, s32 *out)
{
    s32 a, b;
    s32 ret;
    s32 val;

    *out = 0;

    ret = Note_GetFreePages(slot, &a);
    if (ret == 0) {
        ret = Note_CountFreeNotes(slot, &b);
        if (ret == 0) {
            val = Note_BytesToPakPages(PAKInterface_GetRecordsNoteSize());
            if (b == 0) {
                *out = 0;
            } else if (a < val) {
                *out = 0;
            } else {
                *out = 1;
            }
        }
    }

    return ret;
}
