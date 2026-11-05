#ifndef COMPRESSED_SEQUENCE_CURSOR_H
#define COMPRESSED_SEQUENCE_CURSOR_H
/* Measured 4-byte access at 0x18; storage view, complete object unknown. */
struct CompressedSequenceCursorView { unsigned char padding[24]; void * value; };
/* Measured 1-byte access at 0; storage view, complete object unknown. */
struct CompressedSequenceByteView { u8 value; };
#endif
