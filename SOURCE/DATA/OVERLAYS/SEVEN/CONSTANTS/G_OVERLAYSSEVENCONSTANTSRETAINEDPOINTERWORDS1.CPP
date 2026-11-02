#include "TYPES.H"

extern char g_Ovltab6EncodedWordsBlock1[];

#include "DATA/WEAPON_EVENT_TRANSLATION/ADDRLOW_WEAPON_TRANSLATEEVENTSIXBYPITCH.H"

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    void * reserved0;
    void * reserved1;
    f32 scale;
    f32 speed;
    void * states;
    void * enter;
    void * update;
} g_OverlaysSevenConstantsRetainedPointerWords1 __attribute__((aligned(4))) = {
    0,
    0,
    1.0f,
    1.0f,
    (void *)((char *)&g_Ovltab6EncodedWordsBlock1 + 32),
    (void *)&addrLow_Weapon_TranslateEventSixByPitch,
    0
};
typedef char g_OverlaysSevenConstantsRetainedPointerWords1SizeCheck[(sizeof(g_OverlaysSevenConstantsRetainedPointerWords1) == 28) ? 1 : -1];
#endif
#endif
