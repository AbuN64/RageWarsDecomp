#include "../../include/LIBC.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/LLDIVRESULT.H"
#include "TYPES.H"
#include "../../include/EXTERNS.H"

/* sprintf: formats into a buffer through _Printf with the copying output routine, terminates the text when the length is not negative, and returns the length. */
s32 Libc_FormatString(char *buffer, const char *format, ...) {
    s32 length = _Printf(Libc_FormatStringOutputCallback, buffer, format, __builtin_next_arg(format));

    if (length >= 0) {
        buffer[length] = 0;
    }
    return length;
}



/* _Printf output routine: copy a span and return the next output position. */
void *proutSprintf(void *destination, const void *source, s32 count) {
    return (char *)Libc_CopyBytes(destination, source, count) + count;
}

/** Copy a byte span and return its destination. */
void *Libc_CopyBytes(void *destination, const void *source, size_t count) {
    unsigned char *out = destination;
    const unsigned char *in = source;
    while (count != 0) {
        *out++ = *in++;
        --count;
    }
    return destination;
}

/** Find a byte in a zero-terminated string. */
char *Libc_FindStringByte(const char *string, int value) {
    const unsigned char *cursor = (const unsigned char *)string;
    unsigned char byte = (unsigned char)value;
    while (*cursor != byte) {
        if (*cursor == 0) {
            return 0;
        }
        ++cursor;
    }
    return (char *)cursor;
}

size_t Libc_StringLength(const char *string) {
    const unsigned char *cursor = (const unsigned char *)string;
    const unsigned char *terminator;
    terminator = cursor;
    if (*cursor != 0) {
        do {
            terminator += 1;
        } while (*terminator != 0);
    }
    return terminator - cursor;
}

