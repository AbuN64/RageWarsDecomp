#ifndef MENU_PAK_PROFILE_H
#define MENU_PAK_PROFILE_H
#include "Menu/pak_action_prompt.h"

struct PakActionPromptItemView;
extern void Pak_SelectPromptKindFive(void);
extern void Pak_EnableOperationHeading(void);
extern void Pak_SelectPromptKindTwelve(void);
extern void Pak_DisableOperationHeading(void);
extern void Pak_SelectPromptKindZero(void);
extern void Pak_SelectPromptKindTwo(void);
extern void Pak_SelectPromptKindEleven(void);
extern void Pak_SelectPromptKindThree(void);
extern void Pak_SelectProfilePromptWithSavePending(void);
extern int Pak_OpenProfileActionPrompt(int entry, struct PakActionPromptItemView *item);
extern void Pak_SelectPromptKindSeven(void);
extern void Pak_SelectPromptKindSix(void);
extern void Pak_SelectPromptKindFifteen(void);
extern void Pak_SelectPromptKindFour(void);
extern void Pak_SelectPromptKindEight(struct MenuBuildState *record);
extern void Pak_SelectPromptKindOne(void);
extern void Pak_SelectProfilePrompt(void);
extern void Pak_SelectPromptKindTen(void);
extern void Pak_SelectPromptKindFourteen(void);
extern void Pak_SelectPromptKindThirteen(void);
extern u16 g_pakProfileRankScore;
#endif
