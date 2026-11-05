#ifndef RENDER_SETN64_UPDATEFADETRANSITION_H
#define RENDER_SETN64_UPDATEFADETRANSITION_H
#include "Common/sessionhandlerrow.h"
extern int SetN64_IsModeThirteen(void);
extern void SetN64_RunGameThread(void);
extern void SetN64_BeginSessionFadeIn(struct GameSession *gameSession);
u8 *SetN64_CopyString(u8 *destination, u8 *source);
#endif
