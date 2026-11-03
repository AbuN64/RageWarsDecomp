#ifndef LIBULTRA_AUDIO_SAVE_H
#define LIBULTRA_AUDIO_SAVE_H
struct ALSave;
struct ALFilter_s14;
s32 alSaveParam(struct ALSave *saveFilter, s32 parameterId, struct ALFilter_s14 *parameterValue);
#endif
