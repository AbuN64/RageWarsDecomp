#ifndef COMMON_SOUNDINFO_H
#define COMMON_SOUNDINFO_H
#include "TYPES.H"



extern int SoundInfo_GetYaw(void *object);


extern signed char SoundInfo_GetByteF_de(void *object);





extern short SoundInfo_GetPreset(void *soundDescriptor);


extern int SoundInfo_GetPitchPresetId_de(char *object);






struct SoundDescriptor;
int SoundInfo_GetMode(struct SoundDescriptor *note);
unsigned int SoundInfo_GetPan(void *soundDescriptor);
short SoundInfo_GetX(struct SoundDescriptor *controller);
#endif
