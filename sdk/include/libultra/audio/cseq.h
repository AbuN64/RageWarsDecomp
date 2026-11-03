#ifndef LIBULTRA_AUDIO_CSEQ_H
#define LIBULTRA_AUDIO_CSEQ_H
struct ALCSeq_s;
u8 __getTrackByte(struct ALCSeq_s *seq, u32 track);
s32 __readVarLen(struct ALCSeq_s *seq, s32 track);
#endif
