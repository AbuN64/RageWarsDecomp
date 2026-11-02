#include "TYPES.H"


#if defined(VERSION_US_REV1)
extern char addrLow_Link_DispatchTriggerAudio[];
extern char addrLow_Link_PlayTriggerSoundCallback[];
extern char addrLow_Link_PlayTriggerSound[];
#if defined(VERSION_US_REV1)
void * g_ResourcesEncodedWordsBlock68[3] = {
    (void *)&addrLow_Link_PlayTriggerSoundCallback, (void *)&addrLow_Link_PlayTriggerSound, (void *)&addrLow_Link_DispatchTriggerAudio
};
#endif
#endif
