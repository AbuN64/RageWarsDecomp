#include "include_asm.h"
#include "../../../include/libgultra.h"
#include "COMMON/OBJRECAT18V1.H"
#include "TYPES.H"

/* READ.CPP */
/* read8_Read.c */
/** Consume and return one byte from the stream pointer at offset 8. */
int read8(struct ALSeq_s *stream) {
    unsigned char *cursor = stream->curPtr;
    int value = *cursor;
    stream->curPtr = cursor + 1;
    return value;
}

/** Consume and return two big-endian bytes from the stream pointer at offset 8. */
s16 read16(ALSeq *sequenceObject) {
    struct ALSeq_s *stream = sequenceObject;
    unsigned char *p;
    u32 b0;
    u32 b1;

    p = stream->curPtr;
    b0 = p[0];
    p = p + 1;
    stream->curPtr = p;
    b1 = p[0];
    stream->curPtr = p + 1;
    return (s16)((b0 << 8) | b1);
}

s32 read32(ALSeq *sequenceObject) {
    struct ALSeq_s *stream = sequenceObject;
    unsigned char *p;
    unsigned int b0, b1, b2, b3;

    p = stream->curPtr;
    b0 = p[0];
    p = p + 1;
    stream->curPtr = p;
    b1 = p[0];
    stream->curPtr = p + 1;
    b2 = p[1];
    stream->curPtr = p + 2;
    b3 = p[2];
    stream->curPtr = p + 3;
    return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
}

/* 802B243C_2.CPP */
