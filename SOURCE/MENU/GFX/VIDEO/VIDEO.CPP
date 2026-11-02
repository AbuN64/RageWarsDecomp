#include "TYPES.H"
#include "COMMON/TEXTURE.H"
#include <ultra64.h>

/* Spins forever unless bypass is 5, calling osViBlack with bit 20 of a running counter each pass. */
void Gfx_BlinkVideoUnlessBypassed(s32 bypass) {
    s32 i = 0;

    while (bypass != 5) {
        s32 bit = i & 0x100000;

        i++;
        osViBlack(bit != 0);
    }
}
