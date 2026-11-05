#ifndef SOUND_PLAYERAI_SEQUENCE_WAITS_H
#define SOUND_PLAYERAI_SEQUENCE_WAITS_H
extern void Playerai_UpdateBackwardMovingDeathSequenceWait(void *);
extern void Playerai_UpdateSwimmingChestbursterDeathSequenceWait(void *);
extern void Playerai_UpdateClimbingDeathSequenceWait(void *);
extern void Playerai_UpdateQuicksandDeathSequenceWait(void *);
extern void Playerai_UpdateGroundDeathSequenceWait(void *);
extern void Playerai_UpdateCrawlDeathSequenceWait(void *);
extern void Playerai_UpdateRaptorChestbursterDeathSequenceWait(void *);
extern void Playerai_UpdatePrimagenDeathSequenceWait(void *);
extern void Playerai_UpdateImpalementDeathSequenceWait(void *);
extern void Playerai_UpdateFallingDeathSequenceWait(void *);
extern void Playerai_UpdateChestbursterDeathSequenceWait(void *);
extern void Playerai_UpdateExplosiveDeathSequenceWait(void *);
extern void Playerai_UpdateRunningDeathSequenceWait(void *);
extern void Playerai_UpdateLavaDeathSequenceWait(void *);
extern void Playerai_UpdateDrowningDeathSequenceWait(void *);
/* The sequence start callbacks the player sequence tables pair with these waits. */
extern void Playerai_StartExplosiveDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartDisabledCrawlDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartRunningDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartBackwardMovingDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartClimbingDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartFallingDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartQuicksandDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartLavaDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartViewSavingDrowningDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartPrimagenDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartImpalementDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartChestbursterDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartSwimmingChestbursterDeathSequence(void *player, void *sequenceActor);
extern void Playerai_StartRaptorChestbursterDeathSequence(void *player, void *sequenceActor);
#endif
