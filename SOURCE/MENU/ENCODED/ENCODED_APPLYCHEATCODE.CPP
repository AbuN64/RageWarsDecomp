#include "../../../sdk/include/LIBC.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CHEATCODE.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/SHARED_GAMESLOT.H"
extern struct IntPair g_gameSettingsView __asm__("g_gameSettings");

/* Checks the entered code g_encodedCheatCode against the twelve cheat codes of g_encodedCheatDefinitions (each stored with
   every character xored with its index): for each one that matches, ors its flags into the cheat word of g_gameSettings,
   copies them to g_persistedOptionUnlockFlags, records its index in g_encodedCheatCharacterIndex (-1 when none) and plays its sound. */



extern CheatCode g_encodedCheatDefinitions[];
extern u8 g_encodedCheatCode[];



extern u32 g_encodedCheatCharacterIndex;



s32 Encoded_ApplyCheatCode(void)
{
    u32 i;
    s32 j;
    s32 match;
    s32 hasSound; /* the code's sound is read before the match index is stored */
    struct IntPair *settings;
    u8 *code;

    g_encodedCheatCharacterIndex = -1;
    for (i = 0; i < 12; i++) {
        code = g_encodedCheatDefinitions[i].code;
        j = 0;
        if ((s32)Libc_StringLength((const char *)code) != (s32)Libc_StringLength((const char *)g_encodedCheatCode)) {
            match = 0;
        } else {
            for (;;) {
                if (j < (s32)Libc_StringLength((const char *)code)) {
                    if ((code[j] ^ j) != g_encodedCheatCode[j]) {
                        match = 0;
                        break;
                    }
                    j++;
                } else {
                    match = 1;
                    break;
                }
            }
        }
        if (match) {
            g_gameSettingsView.second |= g_encodedCheatDefinitions[i].flags;
            settings = &g_gameSettingsView;
            do {
                g_persistedOptionUnlockFlags = settings->second;
            } while (0);
            hasSound = g_encodedCheatDefinitions[i].sound != 0;
            g_encodedCheatCharacterIndex = i;
            if (hasSound) {
                SoundElement_PlayFlatSound((s16)g_encodedCheatDefinitions[i].sound);
            }
        }
    }
    return 0;
}
