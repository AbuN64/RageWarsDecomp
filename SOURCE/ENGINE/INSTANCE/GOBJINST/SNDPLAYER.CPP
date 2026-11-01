#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_actionEnterDispatchTriggerPairs_eu_x[];
extern char g_actionMotionDispatchTriggerPairs_eu_x[];
extern char g_damageDispatchTriggerPairs_eu_x[];
extern char g_movingMotionDispatchTable[];
extern char g_spawnActorDispatchTable[];
extern char g_triggeredMotionDispatchTable[];
extern char g_turretDispatchTriggerPairs_eu_x[];
#include "TYPES.H"
#if defined(VERSION_EU_X)
/* SndplayerPointerWordBlock.CPP */
RestSndplayerEncodedWordsLayout640 k_SndplayerEncodedWords = {
    { 1.5483116f, 1.5473337f, 0.0f, 0.0f },
    { (void *)((char *)&g_triggeredMotionDispatchTable + 224), (void *)((char *)&g_spawnActorDispatchTable + 128), (void *)((char *)&g_turretDispatchTriggerPairs_eu_x + 92), 0, (void *)((char *)&g_actionEnterDispatchTriggerPairs_eu_x + 16), (void *)((char *)&g_damageDispatchTriggerPairs_eu_x + 72), 0, (void *)((char *)&g_movingMotionDispatchTable + 96), (void *)((char *)&g_actionMotionDispatchTriggerPairs_eu_x + 12), 0, 0, 0, 0 },
};
#endif
