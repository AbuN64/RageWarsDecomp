#ifndef ENGINE_CONTPAD_H
#define ENGINE_CONTPAD_H
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJRECAT5F14.H"
#include "TYPES.H"

struct ControllerProfile;

/* One entry of the controller button remap table g_controllerButtonRemap: a controller
   button mask and the input bit it sets. A zero source ends the table. */
typedef struct ButtonRemap {
    s32 source; /* 0x0 */
    s32 mapped; /* 0x4 */
} ButtonRemap;

/* The per-player input block at Player+0x688 that ContPad_BuildControllerState
   fills from the player's controller once per frame. */
struct ControllerInput {
    f32 turn; /* 0x00: stick X */
    f32 pitch; /* 0x04 */
    f32 strafe; /* 0x08 */
    f32 forward; /* 0x0C */
    struct ControllerProfile *controller; /* 0x10 */
    f32 shapedTurn; /* 0x14: turn * |turn * turn| */
    f32 shapedPitch; /* 0x18 */
    f32 shapedStrafe; /* 0x1C: strafe * |strafe * strafe| */
    f32 shapedForward; /* 0x20 */
    s32 buttons; /* 0x24 */
    s32 pressedButtons; /* 0x28 */
    s32 history[2]; /* 0x2C */
    s32 buttonState; /* 0x34 */
};

typedef struct ControllerInput ControllerInput;

extern ButtonRemap g_controllerButtonRemap[];

extern void ContPad_BuildControllerState(ControllerInput *input, Player *player);
extern void ContPad_InitControllerInput(void *input, s32 attributes);
extern s32 ContPad_SwapButtonPairs(s32);
#endif
