#ifndef CONTROL_CONTROL_H
#define CONTROL_CONTROL_H
#include "types.h"
#include "Common/runtime_declarations.h"
extern void Control_EnableControllerPak(s32 kind);
extern void Control_EnableControllerPak(int);
extern void Control_EnableControllerPak(int controllerPort);
extern void Control_DisableControllerPak(s32 controllerPort);
extern unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);
extern s32 Control_CountConnectedControllers(void);
extern void Control_EnableControllerPak(s32 arg);
extern void Control_DisableControllerPak(s32 arg);
extern void Control_DisableControllerPak(s32);
#endif
