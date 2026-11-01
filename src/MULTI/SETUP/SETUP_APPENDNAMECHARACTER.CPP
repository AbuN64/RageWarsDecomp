#include "include_asm.h"

#include "COMMON/MENURECAT20V1.H"
#include "MULTI/SETUP_SETUPNAMESPINNER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "TYPES.H"
#include "MULTI/SETUP_COMPAREBYTESEQUENCE.H"

/* Append one selected character to an eight-character entry buffer. */
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern char g_playerViewRenderContext;
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
extern struct LocalizedInputState g_playerViewRenderContext;
#endif

extern NameSpinnerEntry g_multiplayerNameEntryStates[];

extern s32 Player_GetPlayerIndex(void *,s32);

s32 Setup_AppendNameCharacter(TextEntryBufferView *textEntry, MenuRules *menuRules) {
 s32 value; s32 count; s32 index=Player_GetPlayerIndex(&g_playerViewRenderContext,menuRules->locked);
 g_multiplayerNameEntryStates[index].timer=0;
 if(g_multiplayerNameEntryStates[index].count == 8) return 0;
 {
 g_multiplayerNameEntryStates[index].text[g_multiplayerNameEntryStates[index].value]=
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
     **textEntry->textBuffer;
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
     *textEntry->textBuffer[g_playerViewRenderContext.language];
#endif
 value=g_multiplayerNameEntryStates[index].value+1;
 count=g_multiplayerNameEntryStates[index].count+1;
 g_multiplayerNameEntryStates[index].value=value;
 g_multiplayerNameEntryStates[index].count=count;
 g_multiplayerNameEntryStates[index].text[count]=0;
 }
 return 0;
}

/* Compares two strings byte by byte and returns whether the last pair compared is equal. It stops
   at the first difference or terminator, and keeps going only while the count, decremented once
   per byte, is exactly zero, so a count of one compares a single byte. */
s32 Setup_CompareByteSequence(u8 *a, u8 *b, s32 count) {
    u8 c;
    u8 d;

    do {
        c = *a++;
        d = *b++;
        count--;
    } while (c == d && c != 0 && count == 0);
    return c == d;
}
