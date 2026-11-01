#include "COMMON/ITEMRECAT20V1.H"
#include "../include/BUF16B.H"
#include "TYPES.H"
#include "../include/libgultra_inferred/cseq.H"

/* cspsetseq.CPP */
struct SeqpSetSeqEvent {
    s16 count;
    s16 _pad2;
    ALCSeq *sequence;
    s32 _pad8;
    s32 _padC;
};

void alCSPSetSeq(ALCSPlayer *player, ALCSeq *sequence) {
    struct SeqpSetSeqEvent setSeqEvent;

    setSeqEvent.sequence = sequence;
    setSeqEvent.count = 0xD;
    alEvtqPostEvent(&player->evtq, &setSeqEvent, 0);
}

void alCSPSetVol(ALCSPlayer *player, s16 volume) {
    Buf16b volumeEvent;

    volumeEvent.value = volume;
    volumeEvent.count = 0xA;
    alEvtqPostEvent(&player->evtq, &volumeEvent, 0);
}

void alCSPStop(ALCSPlayer *player) {
    s16 stopEvent[8];

    stopEvent[0] = 0x11;
    alEvtqPostEvent(&player->evtq, stopEvent, 0);
}
