#ifndef LIBULTRA_OS_GETTHREADID_H
#define LIBULTRA_OS_GETTHREADID_H
#include "types.h"
struct ThreadIdentifierView {
    char pad0[0x14];
    unsigned int threadId;
};
#endif
