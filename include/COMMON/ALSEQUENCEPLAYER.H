#ifndef COMMON_ALSEQUENCEPLAYER_H
#define COMMON_ALSEQUENCEPLAYER_H
#include "COMMON/LONE/SEQUENCE_PLAYER_ASSERT_TEXT.H"
#include "COMMON/LONE/G_AUDIOSEQPLAYERTEXT.H"
#ifndef COMMON_SEQUENCE_PLAYER_EVENT_HELPERS_H
#define COMMON_SEQUENCE_PLAYER_EVENT_HELPERS_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/OBJRECAT18V1.H"


/* alSeqNextEvent */
extern void Seqplayer_HandleSequenceMidiEvent(ALSeqPlayer *, ALEvent *);           /* __handleMIDIMsg */
#include "libultra/audio/seqp_events.h"
/* alSeqGetTicks */
/* alSeqSetLoc */
/* alEvtqPostEvent */
                /* __assert */

static inline void postNextSeqEvent(ALSeqPlayer *seqp)
{
    ALEvent evt;
    s32 deltaTicks;
    struct ALSeq_s *seq = seqp->target;

    if ((seqp->state != 1) || (seq == 0))
        return;

    if (!__alSeqNextDelta(seq, &deltaTicks))
        return;

    if (seqp->loopCount) {
        if (alSeqGetTicks(seq) + deltaTicks >= seqp->loopEnd->curTicks) {
            alSeqSetLoc(seq, seqp->loopStart);
            if (seqp->loopCount != -1)
                seqp->loopCount--;
        }
    }

    evt.type = 0;   /* AL_SEQ_REF_EVT */
    alEvtqPostEvent(&seqp->evtq, &evt, deltaTicks * seqp->uspt);
}


#endif
#endif
