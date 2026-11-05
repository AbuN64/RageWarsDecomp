#ifndef FRONTEND_PAK_H
#define FRONTEND_PAK_H
#include "Common/frontend_video_mode.h"
struct PakCancelActionView;
extern void Pak_SelectPakOperationZero(void);
extern void Pak_SelectPakOperationThree(void);
extern void Pak_SelectPakOperationTwo(void);
extern s32 Pak_CancelPakAction(s32 entry, struct PakCancelActionView *action);
extern void Pak_SelectPakOperationOne(void);
extern void Pak_SelectPakOperationFour(void);
#endif
