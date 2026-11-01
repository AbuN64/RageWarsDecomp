#ifndef LIBULTRA_AUDIO_REVERB_H
#define LIBULTRA_AUDIO_REVERB_H
#include "TYPES.H"
struct CallbackStateC {
    unsigned char padding_0[8];
    void (*callback)(void *, s32, s32);
};
struct AudioReverbParameterStateView {
    char pad0[0x18];
    s32 ratio;
    char pad18[0x1C - 0x18 - sizeof(s32)];
    s32 upitch;
    char pad1C[0x20 - 0x1C - sizeof(s32)];
    s32 delta;
    char pad20[0x24 - 0x20 - sizeof(s32)];
    s32 first;
    char pad24[0x30 - 0x24 - sizeof(s32)];
    s32 motion;
};
#endif
