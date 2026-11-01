#ifndef MEASUREDRECAT18_H
#define MEASUREDRECAT18_H
/* Measured 4-byte access at 0x18; storage view, complete object unknown. */
struct CompressedSequenceCursorView { unsigned char padding[24]; void * value; };
/* Measured 1-byte access at 0; storage view, complete object unknown. */
struct CompressedSequenceByteView { u8 value; };
#endif
