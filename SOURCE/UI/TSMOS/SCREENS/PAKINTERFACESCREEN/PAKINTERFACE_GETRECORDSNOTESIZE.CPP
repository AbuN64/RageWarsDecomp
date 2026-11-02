#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Returns 0x648, the byte size PAKInterface_CheckRecordsNoteCapacity passes on to Note_BytesToPakPages for the object it
   creates when it has none. */
s32 PAKInterface_GetRecordsNoteSize(void) {
    return 1608;
}
