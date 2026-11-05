#ifndef ENGINE_CONTPAD_H
#define ENGINE_CONTPAD_H
#include "Common/animation_pool.h"
#include "types.h"

struct ButtonRemap;
struct ControllerInput;
struct Player;
struct Shared_Input;
struct ControllerProfile;

/* One entry of the controller button remap table g_controllerButtonRemap: a controller
   button mask and the input bit it sets. A zero source ends the table. */
typedef struct ButtonRemap {
    s32 source;
    s32 mapped;
} ButtonRemap;

/* The per-player input block at Player+0x688 that ContPad_BuildControllerState
   fills from the player's controller once per frame. */
struct ControllerInput {
    f32 turn; /* stick X */
    f32 pitch;
    f32 strafe;
    f32 forward;
    struct ControllerProfile *controller;
    f32 shapedTurn; /* turn * |turn * turn| */
    f32 shapedPitch;
    f32 shapedStrafe; /* strafe * |strafe * strafe| */
    f32 shapedForward;
    s32 buttons;
    s32 pressedButtons;
    s32 history[2];
    s32 buttonState;
};

typedef struct ControllerInput ControllerInput;

extern struct ButtonRemap g_controllerButtonRemap[];

extern void ContPad_BuildControllerState(struct ControllerInput *input, struct Player *player);
struct AnimationResourceHandleView;
extern void ContPad_InitControllerInput(struct AnimationResourceHandleView *input, s32 attributes);
extern s32 ContPad_SwapButtonPairs(s32);
void ContPad_ClearControllerInput(struct Shared_Input *object);
#endif
