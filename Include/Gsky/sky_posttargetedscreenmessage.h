#ifndef GSKY_SKY_POSTTARGETEDSCREENMESSAGE_H
#define GSKY_SKY_POSTTARGETEDSCREENMESSAGE_H
void Gsky_ActivateAllMessagePools(s32 messageOwner);
void Gsky_InitializeMessageEntryPool(int viewAddress);
struct CCameraText_t *Gsky_PostTargetedScreenMessage(void *owner, void *pool, u8 *text, s32 target, f32 size);
#endif
