#include "../../include/libgultra.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJRECAT18V1.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"

/* alSeqNextEvent, drafted from ultralib src/audio/seq.c: read the next MIDI file event into an
   ALEvent, decoding tempo and end-of-track meta events and applying running status to channel
   events. */

 /* readVarLen */
extern u8 read8(ALSeq *);

/* alSeqSecToTicks, drafted from ultralib src/audio/seq.c: convert seconds to ticks at the given
   tempo. The library evaluates it in single precision as sec * (division * 1e6f), so the product is
   spelled in that order against the cartridge constant after g_sequenceMicrosecondsPerSecond; GCC's u32-to-float and
   float-to-u32 expansions are written out against g_sequenceSecondsToTicksUnsignedBias and g_sequenceSignedTickConversionLimit. */

 /* followed by 1000000.0f */

 /* 4294967296.0 */

/* alSeqNewMarker, drafted from ultralib src/audio/seq.c: fill a marker with the sequence position
   of the first event at or after the given tick count (the track start for zero), stepping a
   scratch pass with alSeqNextEvent and restoring the sequence's own position afterwards. */

 /* read8 */
void alSeqNextEvent(ALSeq *seq, ALEvent *event)
{
    u8 status;
    s32 deltaTicks;
    deltaTicks = readVarLen(seq);
    seq->lastTicks += deltaTicks;
    status = read8(seq);
    if (status == 0xFF) {
        u8 type = read8(seq);
        if (type == 0x51) {
            event->type = 3;
            event->msg.tempo.ticks = deltaTicks;
            event->msg.tempo.status = status;
            event->msg.tempo.type = type;
            event->msg.tempo.len = read8(seq);
            event->msg.tempo.byte1 = read8(seq);
            event->msg.tempo.byte2 = read8(seq);
            event->msg.tempo.byte3 = read8(seq);
        } else if (type == 0x2F) {
            event->type = AL_SEQ_END_EVT;
            event->msg.end.ticks = deltaTicks;
            event->msg.end.status = status;
            event->msg.end.type = type;
            event->msg.end.len = read8(seq);
        }
        seq->lastStatus = 0;
    } else {
        event->type = 1;
        event->msg.midi.ticks = deltaTicks;
        if (status & 0x80) {
            event->msg.midi.status = status;
            event->msg.midi.byte1 = read8(seq);
            seq->lastStatus = status;
        } else {
            event->msg.midi.status = seq->lastStatus;
            event->msg.midi.byte1 = status;
        }
        if (((event->msg.midi.status & 0xf0) != 0xC0) &&
            ((event->msg.midi.status & 0xf0) != 0xD0)) {
            event->msg.midi.byte2 = read8(seq);
        } else {
            event->msg.midi.byte2 = 0;
        }
    }
}

void alSeqNew(ALSeq *state, u8 *start, s32 len) {
    s16 division;

    state->base = start;
    state->len = len;
    state->lastStatus = 0;
    state->lastTicks = 0;
    state->curPtr = start;
    if (read32(state) == 0x4D546864) {
        read32(state);
        if (((read16(state) << 16) == 0) && (read16(state) == 1)) {
            division = read16(state);
            state->division = division;
            if (!(division & 0x8000)) {
                state->qnpt = g_sequenceQuarterNoteUnit / (f32) division;
                if (read32(state) == 0x4D54726B) {
                    read32(state);
                    state->trackStart = state->curPtr;
                }
            }
        }
    }
}

int alSeqGetTicks(struct ALSeq_s *sequence) {
    return sequence->lastTicks;
}

f32 alSeqTicksToSec(ALSeq *sequence, s32 ticks, s32 tempo) {
    f64 v;
    f32 tickCount;

    v = (f64)tempo;
    tickCount = (f32)ticks;
    if (tempo < 0) {
        v = v + g_sequenceTicksToSecondsUnsignedBias;
    }
    return (tickCount * (f32)v) / ((f32)sequence->division * g_sequenceMicrosecondsPerSecond);
}

 /* 2147483648.0f */
u32 alSeqSecToTicks(ALSeq *seq, f32 sec, u32 tempo)
{
    f32 ticks;
    f64 t;
    f32 q;
    u32 result;
    ticks = sec * ((f32)seq->division * (*(&g_sequenceMicrosecondsPerSecond + 1)));
    t = (f64)(s32)tempo;
    if ((s32)tempo < 0) {
        t = t + g_sequenceSecondsToTicksUnsignedBias;
    }
    q = ticks / (f32)t;
    if (!(q >= g_sequenceSignedTickConversionLimit)) {
        result = (s32)q;
    } else {
        q = q - g_sequenceSignedTickConversionLimit;
        result = (s32)q;
        result |= 0x80000000;
    }
    return result;
}

 /* alSeqNextEvent */
void alSeqNewMarker(ALSeq *seq, ALSeqMarker *m, u32 ticks)
{
    ALEvent evt;
    u8 *savePtr, *lastPtr;
    s32 saveTicks, lastTicks;
    s16 saveStatus, lastStatus;
    if (ticks == 0) {
        m->curPtr = seq->trackStart;
        m->lastStatus = 0;
        m->lastTicks = 0;
        m->curTicks = 0;
        return;
    } else {
        savePtr = seq->curPtr;
        saveStatus = seq->lastStatus;
        saveTicks = seq->lastTicks;
        seq->curPtr = seq->trackStart;
        seq->lastStatus = 0;
        seq->lastTicks = 0;
        do {
            lastPtr = seq->curPtr;
            lastStatus = seq->lastStatus;
            lastTicks = seq->lastTicks;
            alSeqNextEvent(seq, &evt);
            if (evt.type == AL_SEQ_END_EVT) {
                lastPtr = seq->curPtr;
                lastStatus = seq->lastStatus;
                lastTicks = seq->lastTicks;
                break;
            }
        } while (seq->lastTicks < ticks);
        m->curPtr = lastPtr;
        m->lastStatus = lastStatus;
        m->lastTicks = lastTicks;
        m->curTicks = seq->lastTicks;
        seq->curPtr = savePtr;
        seq->lastStatus = saveStatus;
        seq->lastTicks = saveTicks;
    }
}

/** Copy selected fields from the compact source record. */
void alSeqSetLoc(ALSeq *sequence, ALSeqMarker *marker) {
    sequence->curPtr = marker->curPtr;
    sequence->lastStatus = marker->lastStatus;
    sequence->lastTicks = marker->lastTicks;
}

/** Copy selected fields into the compact destination record. */
void alSeqGetLoc(ALSeq *sequenceStorage, ALSeqMarker *markerObject) {
    struct ALSeq_s *sequence = sequenceStorage;
    ALSeqMarker *marker = markerObject;
    marker->curPtr = sequence->curPtr;
    marker->lastStatus = sequence->lastStatus;
    marker->lastTicks = sequence->lastTicks;
}

s32 __alSeqNextDelta(ALSeq *sequence, s32 *deltaTicks) {
    u8 *savedCursor;

    savedCursor = sequence->curPtr;
    if (!(savedCursor < (sequence->base + sequence->len))) {
        return 0;
    }
    *deltaTicks = readVarLen(sequence);
    sequence->curPtr = savedCursor;
    return 1;
}

s32 readVarLen(struct ALSeq_s *sequence) {
    u8 *p;
    s32 b;
    s32 val;

    p = sequence->curPtr;
    b = *p;
    sequence->curPtr = p + 1;
    val = b;
    if (val & 0x80) {
        val = val & 0x7F;
        do {
            p = sequence->curPtr;
            b = *p;
            sequence->curPtr = p + 1;
            val = (val << 7) + (b & 0x7F);
        } while (b & 0x80);
    }
    return val;
}

/* ROM-grounded data: src/g_sequenceQuarterNoteUnit_StorageWords_Seq.c */
const float g_sequenceQuarterNoteUnit_StorageWords[1] = {
    1.0f,
};
