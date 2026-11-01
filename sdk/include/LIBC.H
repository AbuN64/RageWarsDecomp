#ifndef LIBC_H
#define LIBC_H

#include <ultra64.h>

void *Libc_CopyBytes(void *destination, const void *source, size_t count);
char *Libc_FindStringByte(const char *string, int value);
size_t Libc_StringLength(const char *string);

#endif
