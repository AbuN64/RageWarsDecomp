#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJRECAT5F14.H"
#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/AIPROFILE.H"
#include "FX/EXTERNS.H"
#include "ENGINE/CONTPAD.H"
#include <ultra64.h>
#include "COMMON/PAKQUEUESTATE.H"
#include "ENGINE/CONTPAD.H"

/* 802631D0.CPP */
/* Builds the player's analog input from its controller: remaps the buttons through g_controllerButtonRemap when the
   profile asks for it (control modes 0 and 1), turns stick and C buttons into turn, pitch, strafe and
   forward for the profile's control mode (pitch steps scale with the profile sensitivity, the frame time
   g_frameElapsedTime and the player's 0x7EC damping; mode 1 recentres the pitch through Graphu64_DecayToZero while
   moving), then writes the cubic-shaped turn and strafe and the pitch and forward copies.
   The ROM keeps two pieces of dead source: a first per-mode table choice that the reset to NULL
   overrides, and a pitch-mode test whose two arms are the same. gcc deletes the dead stores and the
   merged branches, but their tests still load controlMode once more and keep the profile live
   in a saved register across Graphu64_DecayToZero. */
void ContPad_BuildControllerState(ControllerInput *input, Player *player) {
    AiProfile *profile;
    f32 forward;
    f32 sensitivity;
    f32 pitchStep;
    f32 pitch;
    f32 strafeSquared;
    f32 turnSquared;
    f32 strafe;
    f32 turn;
    f32 recenterStep;
    f32 pitchLimit;
    f32 nextPitch;
    f32 shapedStrafe;
    ButtonRemap *remap;
    s32 sourceButtons;
    s32 mappedButtons;
    s32 strafeButtons;
    s32 forwardButtons;
    s32 moveButtons;
    s32 pitchButtons;
    s8 stickY;
    s8 controlMode;
    struct ControllerProfile *controller;

    profile = player->profile;
    sensitivity = 1.0f - (player->state7EC * 0.99f);
    controller = input->controller;
    pitchStep = (f32)profile->sensitivity * 0.0078125f - 1.0f;
    pitchStep = pitchStep * 0.75f + 1.0f;
    pitchStep *= g_frameElapsedTime * (sensitivity * 0.1f);
    switch (profile->controlMode) {
    case 0:
        remap = g_controllerButtonRemap;
        break;
    case 1:
        remap = g_controllerButtonRemap;
        break;
    }
    remap = NULL;
    if (profile->controlMode < 2) {
        if (profile->controlMode >= 0 && profile->remap == 1) {
            remap = g_controllerButtonRemap;
        }
    }
    if (remap != NULL) {
        input->buttons = 0;
        input->pressedButtons = 0;
        input->history[0] = 0;
        input->history[1] = 0;
        input->buttonState = 0;
        if (remap->source != 0) {
            do {
                sourceButtons = remap->source;
                mappedButtons = remap->mapped;
                if (controller->buttons & sourceButtons) {
                    input->buttons |= mappedButtons;
                }
                if (controller->pressedButtons & sourceButtons) {
                    input->pressedButtons |= mappedButtons;
                }
                if (controller->history[0] & sourceButtons) {
                    input->history[0] |= mappedButtons;
                }
                if (controller->history[1] & sourceButtons) {
                    input->history[1] |= mappedButtons;
                }
                remap++;
                if (controller->buttonState & sourceButtons) {
                    input->buttonState |= mappedButtons;
                }
            } while (remap->source != 0);
        }
    } else {
        input->buttons = controller->buttons;
        input->pressedButtons = controller->pressedButtons;
        input->history[0] = controller->history[0];
        input->history[1] = controller->history[1];
        input->buttonState = controller->buttonState;
    }
    controlMode = profile->controlMode;
    switch (controlMode) {
    case 0:
        strafeButtons = input->buttons;
        if (strafeButtons & 1) {
            input->strafe = 1.0f;
        } else if (strafeButtons & 2) {
            input->strafe = -1.0f;
        } else {
            input->strafe = 0.0f;
        }
        forwardButtons = input->buttons;
        input->turn = controller->previousStickX * 0.0125f;
        if (forwardButtons & 8) {
            input->forward = 1.0f;
        } else if (forwardButtons & 4) {
            input->forward = -1.0f;
        } else {
            input->forward = 0.0f;
        }
        if (profile->pitchMode != 0) {
            input->pitch = controller->previousStickY * 0.0125f;
        } else if (player->locked == 0) {
            stickY = controller->previousStickY;
            if (stickY != 0) {
                input->pitch += pitchStep * 0.0125f * stickY;
            }
            pitch = input->pitch;
            if (1.0f < pitch) {
                input->pitch = 1.0f;
            } else if (pitch < -1.0f) {
                input->pitch = -1.0f;
            }
        }
        break;
    case 1:
        moveButtons = input->buttons;
        input->turn = controller->previousStickX * 0.0125f;
        if (moveButtons & 1) {
            input->strafe = 1.0f;
        } else if (moveButtons & 2) {
            input->strafe = -1.0f;
        } else {
            input->strafe = 0.0f;
        }
        if (player->locked == 0) {
            input->forward = controller->previousStickY * 0.0125f;
        } else {
            input->forward = 0.0f;
        }
        pitchButtons = input->buttons;
        if (!(pitchButtons & 0x10)) {
            if (pitchButtons & 8) {
                nextPitch = input->pitch + pitchStep * 0.75f;
                pitchLimit = 1.0f;
                if (pitchLimit < nextPitch) {
                    nextPitch = pitchLimit;
                }
                input->pitch = nextPitch;
            } else if (pitchButtons & 4) {
                nextPitch = input->pitch - pitchStep * 0.75f;
                pitchLimit = -1.0f;
                if (nextPitch < pitchLimit) {
                    nextPitch = pitchLimit;
                }
                input->pitch = nextPitch;
            } else if (profile->pitchMode != 0) {
                forward = input->forward;
                if (forward != 0.0f && player->state7E8 == 0) {
                    recenterStep = forward * (sensitivity * 0.1f);
                    if (recenterStep < 0.0f) {
                        recenterStep = -recenterStep;
                    }
                    input->pitch = Graphu64_DecayToZero(input->pitch, recenterStep);
                }
            }
        }
        break;
    }
    strafe = input->strafe;
    strafeSquared = strafe * strafe;
    if (strafeSquared < 0.0f) {
        shapedStrafe = strafe * -strafeSquared;
    } else {
        shapedStrafe = strafe * strafeSquared;
    }
    turn = input->turn;
    turnSquared = turn * turn;
    input->shapedStrafe = shapedStrafe;
    if (turnSquared < 0.0f) {
        input->shapedTurn = turn * -turnSquared;
    } else {
        input->shapedTurn = turn * turnSquared;
    }
    if (profile->pitchMode != 0) {
        input->shapedForward = input->forward;
        input->shapedPitch = input->pitch;
    } else {
        input->shapedForward = input->forward;
        input->shapedPitch = input->pitch;
    }
}

void ContPad_InitControllerInput(void *input, s32 attributes) {
    ContPad_ClearControllerInput(input);
    (((struct AnimationResourceHandleView *) ((s8 *) input))->resourceHandle) = attributes;
}

/* 802631D0_2.CPP */
/** Clear the object's fields, preserving the field at offset 0x10. */
void ContPad_ClearControllerInput(void *object) {
    Shared_Input *input = object;
    input->word0 = 0;
    input->word4 = 0;
    input->word8 = 0;
    input->wordC = 0;
    input->word14 = 0;
    input->word18 = 0;
    input->word1C = 0;
    input->word20 = 0;
    input->held = 0;
    input->pressed = 0;
    input->reservedWord = 0;
    input->reservedWord1 = 0;
    input->reservedWord2 = 0;
}

s32 ContPad_SwapButtonPairs(s32 buttons)
{
  int secondSourceMask;
  s32 remappedButtons;
  secondSourceMask = 0x80000;
  remappedButtons = buttons & 0xFFF6FFF3;
  if (buttons & 0x10000)
  {
    remappedButtons |= 8;
  }
  if (buttons & 8)
  {
    remappedButtons = remappedButtons | 0x10000;
  }
  if (buttons & secondSourceMask)
  {
    remappedButtons |= 4;
  }
  if (buttons & 4)
  {
    remappedButtons |= 0x80000;
  }
  return remappedButtons;
}

