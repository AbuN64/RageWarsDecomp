#ifndef PLAYERCOUNT_FRONTEND_UPDATEPLAYERCOUNTSCREEN_H
#define PLAYERCOUNT_FRONTEND_UPDATEPLAYERCOUNTSCREEN_H
s32 Frontend_CancelPlayerCount(void);
int Frontend_ConfirmPlayerCount(void);
s32 Frontend_DecreasePlayerCount(void *first, void *second, void *third, s32 fourth);
s32 Frontend_DestroyPlayerCountScreen(void);
s32 Frontend_IncreasePlayerCount(void *menuObject, void *unusedEvent, void *unusedContext, s32 press);
s32 Frontend_UpdatePlayerCountScreen(void);
#endif
