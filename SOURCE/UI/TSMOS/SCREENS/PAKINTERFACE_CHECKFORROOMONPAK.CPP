#include "include_asm.h"
#include "UI/TSMOS/PAKINTERFACE.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Sets *apResult when the user's Controller Pak has a free note and enough free pages for a save block; returns the pak error code. */
s32 PAKInterface_CheckForRoomOnPak(s32 anUser, s32 *apResult) {
    s32 nNeeded;
    s32 nPages;
    s32 nNotes;
    s32 nSize;
    s32 nRet;
    PAK_ASSERT(5157, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    *apResult = 0;
    nRet = PAK_GetPagesFree(anUser, &nPages);
    if (nRet == 0) {
        nRet = PAK_GetNotesFree(anUser, &nNotes);
        if (nRet == 0) {
            nSize = PAKInterface_CalcSaveGameSize();
            nNeeded = PAK_PagesForBytes(nSize);
            if (nNotes == 0 || nPages < nNeeded) {
                *apResult = 0;
            } else {
                *apResult = 1;
            }
        }
    }
    return nRet;
}
#endif
