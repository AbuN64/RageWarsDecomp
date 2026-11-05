#ifndef MENU_OPTIONTRANSITION_OPTIONTRANSITION_SYMBOLS_H
#define MENU_OPTIONTRANSITION_OPTIONTRANSITION_SYMBOLS_H
#include "types.h"
extern char g_Menu_ConsumeOptionsTransitionEventPackedAddress[];
extern char g_Menu_CreateOptionsImageTransitionPackedAddress[];
extern char g_Menu_DestroyOptionsImageTransitionPackedAddress[];
extern char g_Menu_DrawOptionsImageTransitionPackedAddress[];
extern char g_Menu_HandleOptionsTransitionRequestPackedAddress[];
extern char g_Menu_RequestOptionsImageTransitionPackedAddress[];
extern char g_Menu_StartOptionsImageTransitionPackedAddress[];
extern char addrLow_Menu_ConsumeOptionsTransitionEvent[];
extern char addrLow_Menu_CreateOptionsImageTransition[];
extern char addrLow_Menu_DestroyOptionsImageTransition[];
extern char addrLow_Menu_DrawOptionsImageTransition[];
extern char addrLow_Menu_HandleOptionsTransitionRequest[];
extern char addrLow_Menu_RequestOptionsImageTransition[];
extern char addrLow_Menu_StartOptionsImageTransition[];
#if (defined(VERSION_US_REV1))
extern char g_frontend_HandlePakProfileInputEntry[];
#endif
#endif
