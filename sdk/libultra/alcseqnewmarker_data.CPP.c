#include "COMMON/COMPRESSED_SEQUENCE_AND_EVENT_VIEWS.H"
#include "TYPES.H"
#include "../include/MEASUREDRECAT18.H"

/* alcseqnewmarker_data.CPP */
extern s32 __getTrackByte(s32, s32);
extern u32 __readVarLen(ALCSeq *, u32);

s32 __alCSeqGetTrackEvent(ALCSeq *state, u32 index, DecodeResult *result) {
    u8 first;
    u8 command;
    u32 first_value;
    u32 command_value;

    first = __getTrackByte(state, index);
    first_value = first & 0xFF;
    if (first_value == 0xFF) {
        command = __getTrackByte(state, index);
        command_value = command & 0xFF;
        if (command_value == 0x51) {
            result->type = 3;
            result->status = first;
            result->first_data = command;
            result->extra1 = __getTrackByte(state, index);
            ((u8 *)&result->extra2)[0] = __getTrackByte(state, index);
            ((u8 *)&result->extra2)[1] = __getTrackByte(state, index);
            state->lastStatus[index] = 0;
        } else if (command_value == 0x2F) {
            u32 active = state->validTracks ^ (1U << index);
            state->validTracks = active;
            if (active != 0) {
                result->type = 0x12;
            } else {
                result->type = 4;
            }
        } else if (command_value == 0x2E) {
            __getTrackByte(state, index);
            __getTrackByte(state, index);
            state->lastStatus[index] = 0;
            result->type = 0x13;
        } else if (command_value == 0x2D) {
            void *base;
            void *p;
            u8 lead;
            u8 count_byte;
            u32 count;
            u32 byte0;
            u32 byte1;
            u32 byte2;
            u32 byte3;
            void *next;

            base = (u8 *)state + (index * 4);
            p = ((struct CompressedSequenceCursorView *)(base))->value;
            lead = ((struct CompressedSequenceByteView *)(p))->value;
            p = (u8 *)p + 1;
            count_byte = ((struct CompressedSequenceByteView *)(p))->value;
            count = count_byte & 0xFF;
            if (count == 0) {
                next = (u8 *)p + 5;
                ((struct CompressedSequenceByteView *)(p))->value = lead;
            } else {
                if (count != first_value) {
                    ((struct CompressedSequenceByteView *)(p))->value = count_byte - 1;
                }
                p = (u8 *)p + 1;
                byte0 = ((struct CompressedSequenceByteView *)(p))->value;
                p = (u8 *)p + 1;
                byte1 = ((struct CompressedSequenceByteView *)(p))->value;
                p = (u8 *)p + 1;
                byte2 = ((struct CompressedSequenceByteView *)(p))->value;
                p = (u8 *)p + 1;
                byte3 = ((struct CompressedSequenceByteView *)(p))->value;
                p = (u8 *)p + 1;
                next = (u8 *)p - ((byte0 << 24) + (byte1 << 16) +
                                   (byte2 << 8) + byte3);
            }
            ((struct CompressedSequenceCursorView *)(base))->value = next;
            state->lastStatus[index] = 0;
            result->type = 0x14;
        }
    } else {
        result->type = 1;
        if (first & 0x80) {
            result->status = first;
            result->first_data = __getTrackByte(state, index);
            state->lastStatus[index] = first;
        } else {
            u8 running_status = state->lastStatus[index];
            result->first_data = first;
            result->status = running_status;
        }
        command_value = result->status & 0xF0;
        if ((command_value != 0xC0) && (command_value != 0xD0)) {
            result->second_data = __getTrackByte(state, index);
            if ((result->status & 0xF0) == 0x90) {
                result->extra2 = __readVarLen(state, index);
            }
        } else {
            result->second_data = 0;
        }
    }
    return 1;
}
