#ifndef LIBULTRA_AUDIO_SEQP_H
#define LIBULTRA_AUDIO_SEQP_H
#include "TYPES.H"
extern char __CSPVoiceHandler_Address;
extern void __CSPHandleNextSeqEvent(void *rawPlayer);
extern void __CSPPostNextSeqEvent(void *sequencePlayer);
extern s32 __voiceNeedsNoteKill(void *voice, s32 targetVoice, s32 releaseDeadline);
extern void __seqpStopOsc(void *seqPlayer, void *voiceState);
#endif
