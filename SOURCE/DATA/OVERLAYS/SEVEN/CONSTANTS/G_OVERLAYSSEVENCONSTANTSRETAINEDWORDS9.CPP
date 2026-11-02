#include "TYPES.H"

extern char g_weaponFireStateCallbackTable[];


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
} g_OverlaysSevenConstantsRetainedWords9 __attribute__((aligned(4))) = {
    0,
    0,
    1.0f,
    1.0f,
    (void *)&g_weaponFireStateCallbackTable,
    0,
    0
};
typedef char g_OverlaysSevenConstantsRetainedWords9SizeCheck[(sizeof(g_OverlaysSevenConstantsRetainedWords9) == 28) ? 1 : -1];
#endif
#endif
