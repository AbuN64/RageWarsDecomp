#ifndef COMMON_MENU_INITIALIZEOPTIONSSCENE_H
#define COMMON_MENU_INITIALIZEOPTIONSSCENE_H
#include "TYPES.H"
#include "COMMON/LEVEL_ACTOR.H"



extern void Menu_InitializeOptionsScene(void);


extern void Menu_ConfigureOptionsCamera(void);

struct ScreenMenuFinishTabOptionsTransition;
struct ScreenMenuFinishTabOptionsTransition {
    char pad0[0x1C];
    s32 choice;
    char pad20[0x60 - 0x20];
    s32 mode;
    s32 arena;
};

struct LevelActor;
#endif
