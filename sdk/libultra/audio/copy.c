#include "../../include/BUF16B.H"

/** Copy the requested number of bytes. */
void alCopy(void *source, void *destination, s32 count) {
    u8 *src = source;
    u8 *dst = destination;
    int index;
    for (index = 0; index < count; index++) {
        *dst++ = *src++;
    }
}
