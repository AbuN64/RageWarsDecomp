#include "Ovlgame/match.h"
#include "Engine/control.h"
#include "Common/triple.h"
#include "include_asm.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/pakqueuestate.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "libultra/os/getthreadid.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "OS/controller.H"
#include "Engine/rumble.h"
#include "Common/sharedplayer.h"
#include "Common/game_session.h"
#include "Common/Lone/controller_rumble_pool.h"
#include "Common/world.h"
#include "Common/aiprofile.h"
#include "Common/snapshot_actor.h"
#include "Common/weapon_screen_message_operations.h"
#include "libultra/os/control_updatecontrollerrumble_data.CPP.h"
#include "Ui/Smos/Controller/math_controller_events.h"
#include "Common/shared_worldfunc.h"
#include "Common/gameplay_transition.h"
#include "Common/sessionhandlerrow.h"
#include "Render/setn64_updatefadetransition.h"
#include "Render/control_cycleactorsnapshotmode.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Engine/scene_drawopaqueactors.h"

/* render_controller_input.CPP */

/* Reads the four controllers once per frame and folds them into the combined input record g_combinedControllerProfile.
 * State 0 starts a read through the message queue, converts the pads to the four per-player input
 * records (Control_UpdateControllerInput), ORs their button words into the combined record, adds the stick
 * bytes, and rescales the combined sticks by g_controllerInputScale. States 1 and 3 restart or query the
 * controllers, state 2 does nothing. */

void Control_ReadControllerStates(void) {
    ControllerProfile *summary;
    s32 i;
    f32 scale;

    switch (g_controllerPakFrontendState) {
    case 0:
        osRecvMesg((OSMesgQueue *)&g_controllerSiMessageQueue, (OSMesg *)g_controllerSiMessageBuffer, 1);
        osContGetReadData(g_controllerPadData);
        g_combinedControllerProfile.port = -1;
        g_combinedControllerProfile.connected = 0;
        g_combinedControllerProfile.stickX = 0;
        g_combinedControllerProfile.stickY = 0;
        g_combinedControllerProfile.previousStickX = 0;
        g_combinedControllerProfile.previousStickY = 0;
        g_combinedControllerProfile.buttons = 0;
        g_combinedControllerProfile.previousButtons = 0;
        g_combinedControllerProfile.pressedButtons = 0;
        g_combinedControllerProfile.history[0] = 0;
        g_combinedControllerProfile.history[1] = 0;
        g_combinedControllerProfile.buttonState = 0;
        g_combinedControllerProfile.inputButtons = 0;
        g_combinedControllerProfile.inputPreviousButtons = 0;
        g_combinedControllerProfile.inputPressedButtons = 0;
        g_combinedControllerProfile.inputHistory[0] = 0;
        g_combinedControllerProfile.inputHistory[1] = 0;
        g_combinedControllerProfile.inputHistory[2] = 0;
        summary = &g_combinedControllerProfile;
        for (i = 0; i < 4; i++) {
            Control_UpdateControllerInput(&g_controllerProfiles[i], g_controllerPadData[i].stick_x, g_controllerPadData[i].stick_y,
                             g_controllerPadData[i].button);
            summary->connected |= g_controllerProfiles[i].connected;
            summary->stickX += g_controllerProfiles[i].stickX;
            summary->stickY += g_controllerProfiles[i].stickY;
            summary->previousStickX += g_controllerProfiles[i].previousStickX;
            summary->previousStickY += g_controllerProfiles[i].previousStickY;
            summary->buttons |= g_controllerProfiles[i].buttons;
            summary->pressedButtons |= g_controllerProfiles[i].pressedButtons;
            summary->history[0] |= g_controllerProfiles[i].history[0];
            summary->history[1] |= g_controllerProfiles[i].history[1];
            summary->buttonState |= g_controllerProfiles[i].buttonState;
            summary->inputButtons |= g_controllerProfiles[i].inputButtons;
            summary->inputPreviousButtons |= g_controllerProfiles[i].inputPreviousButtons;
            summary->inputPressedButtons |= g_controllerProfiles[i].inputPressedButtons;
            summary->inputHistory[0] |= g_controllerProfiles[i].inputHistory[0];
            summary->inputHistory[1] |= g_controllerProfiles[i].inputHistory[1];
            summary->inputHistory[2] |= g_controllerProfiles[i].inputHistory[2];
        }
        scale = g_controllerInputScale;
        g_combinedControllerProfile.stickX = (s32)(g_combinedControllerProfile.stickX * scale);
        g_combinedControllerProfile.stickY = (s32)(g_combinedControllerProfile.stickY * scale);
        g_combinedControllerProfile.previousStickX = (s32)(g_combinedControllerProfile.previousStickX * scale);
        g_combinedControllerProfile.previousStickY = (s32)(g_combinedControllerProfile.previousStickY * scale);
        break;
    case 1:
        osRecvMesg((OSMesgQueue *)&g_controllerSiMessageQueue, (OSMesg *)g_controllerSiMessageBuffer, 1);
        osContGetQuery(g_controllerQueryStatus);
        for (i = 0; i < 4; i++) {
            Control_RefreshControllerConnection(&g_controllerProfiles[i]);
        }
        break;
    case 2:
        break;
    case 3:
        osContReset(&g_controllerSiMessageQueue, g_controllerQueryStatus);
        break;
    }
}

/* Polls the controller paks when they are enabled: after Rumble_RecycleFinishedEffectNodes it tries to take the pak lock
 * g_controllerReadMessageQueue without blocking and, holding it, refreshes the four pak entries through Control_UpdateControllerRumble and
 * advances the pak state (state 0 opens the pak through osContStartQuery once Control_IsAnyControllerPakEnabled detects it,
 * otherwise closes it through osContStartReadData; states 1 to 3 reset to 0 and close it), then releases the
 * lock. */

void Control_PollControllerPaks(void) {
    s32 locked;
    s32 i;

    if (g_controllerInputReady != 0) {
        Rumble_RecycleFinishedEffectNodes(&g_controllerRumblePool);
        if ((locked = osRecvMesg(&g_controllerReadMessageQueue, 0, 0) == 0)) {
            g_controllerAudioThreadId = osGetThreadId(0);
        }
        if (locked) {
            Control_ReadControllerStates();
            for (i = 0; i < 4; i++) {
                Control_UpdateControllerRumble(&g_controllerProfiles[i]);
            }
            switch (g_controllerPakFrontendState) {
            case 0:
                if (Control_IsAnyControllerPakEnabled() != 0) {
                    g_controllerPakFrontendState = 1;
                    osContStartQuery(&g_controllerSiMessageQueue);
                } else {
                    osContStartReadData(&g_controllerSiMessageQueue);
                }
                break;
            case 1:
            case 2:
            case 3:
                g_controllerPakFrontendState = 0;
                osContStartReadData(&g_controllerSiMessageQueue);
                break;
            }
            g_controllerAudioThreadId = -1;
            osSendMesg(&g_controllerReadMessageQueue, 0, 1);
        }
    }
}

/* Updates the state of the four controller ports: a port whose device is gone clears all three flags; a port whose device responds is marked ready, turning a pending reconnection into a reconnect event; a ready port that stops responding is marked pending. */

void Control_TrackControllerPakChanges(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (Control_IsControllerPakEnabled(i) != 0) {
            if (Control_IsControllerPakPresent(i) != 0) {
                g_controllerPakProbePending[i] = 1;
                if (g_controllerPakReinitializePending[i] != 0) {
                    g_controllerPakState[i] = 1;
                    g_controllerPakReinitializePending[i] = 0;
                }
            } else if (g_controllerPakProbePending[i] != 0) {
                g_controllerPakReinitializePending[i] = 1;
            }
        } else {
            g_controllerPakState[i] = 0;
            g_controllerPakReinitializePending[i] = 0;
            g_controllerPakProbePending[i] = 0;
        }
    }
}

void Control_RefreshControllerConnection(ControllerProfile *profile) {
    ControllerProfile *controller = profile;
    s32 port;
    s32 plugged;
    s32 i;

    port = controller->port;
    plugged = ((g_controllerReadStatusBytes[port * 4] >> 3) ^ 1) & 1;
    if (plugged != 0 && controller->connected == 0) {
        controller->port = port;
        controller->connected = 0;
        controller->pakActive = 0;
        controller->mode = 0;
        controller->reset = 0;
        controller->reservedWordA = 0;
        controller->reservedWordB = 0;
        controller->reservedWordC = 0;
        controller->stickX = 0;
        controller->stickY = 0;
        controller->previousStickX = 0;
        controller->previousStickY = 0;
        controller->inputPreviousButtons = 0;
        controller->inputButtons = 0;
        controller->inputPressedButtons = 0;
        controller->inputHistory[0] = 0;
        controller->inputHistory[1] = 0;
        controller->inputHistory[2] = 0;
        for (i = 0; i < 32; i++) {
            controller->buttonHistory[i].taps = 0;
            controller->buttonHistory[i].age = 0;
            controller->buttonHistory[i].repeat = 48;
            controller->buttonHistory[i].held = 0;
        }
        controller->pakAmount = 0;
        controller->pakTimer = 0;
        controller->connected = ((g_controllerReadStatusBytes[port * 4] >> 3) ^ 1) & 1;
        Rumble_InitPoolNodes(&controller->effectPool, &controller->effectNodes, 3);
    }
    controller->connected = plugged;
}

void Control_UpdateControllerInput(ControllerProfile *state, s8 x, s8 y, u32 buttons) {
    f32 fx, fy;
    u32 old, pressed, mask;
    ControllerButtonHistory *button;
    s32 i;
    if (state->connected == 0) return;
    buttons &= 0xFFFF;
    if (x < -30) buttons |= 0x20000;
    else if (x > 30) buttons |= 0x40000;
    if (y < -30) buttons |= 0x80000;
    else if (y > 30) buttons |= 0x10000;
    if (x > 0) { x = x - 3; if (x < 0) x = 0; }
    else { x = x + 3; if (x > 0) x = 0; }
    if (y > 0) { y = y - 3; if (y < 0) y = 0; }
    else { y = y + 3; if (y > 0) y = 0; }
    fx = x;
    fy = y;
    if (fx == -128.0f) fx = -127.0f;
    if (fy == -128.0f) fy = -127.0f;
    fx = fx < -80.0f ? -80.0f : fx;
    fx = 80.0f < fx ? 80.0f : fx;
    if (fy < -80.0f) fy = -80.0f;
    if (80.0f < fy) fy = 80.0f;
    old = state->inputButtons;
    state->stickX = (s32)fx;
    state->stickY = (s32)fy;
    state->inputButtons = buttons;
    state->inputPreviousButtons = old;
    pressed = (old ^ buttons) & buttons;
    state->inputPressedButtons |= pressed;
    state->inputHistory[2] |= pressed;
    mask = 1;
    button = state->buttonHistory;
    i = 19;
    do {
        if (pressed & mask) {
            if ((s8)button->age < 30) {
                button->age = 0;
                button->taps++;
                if (button->taps > 1) { state->inputHistory[1] |= mask; button->taps = 0; }
            } else { button->taps = 1; button->age = 0; }
        }
        button->age++;
        if ((s8)button->age > 30) button->age = 30;
        if (buttons & mask) {
            if ((s8)button->held >= 0) button->held += 2;
            button->repeat--;
            if ((s8)button->repeat < 0) { button->repeat += 5; state->inputHistory[2] |= mask; }
        } else {
            if ((u8)button->held < 17) {
                if (!(state->inputPreviousButtons & mask)) button->held = 0;
                else { state->inputHistory[0] |= mask; button->held = 0; }
            } else button->held = 0;
            state->inputHistory[2] &= ~mask;
            button->repeat = 48;
        }
        button++;
        mask <<= 1;
    } while (i-- != 0);
}

/* CONTROL.CPP */

void Control_UpdateControllerRumble(ControllerRumbleView *profile) {
    Triple zero;
    void *object;
    s32 *global;
    f32 first;

    if (profile->active != 0) {
        zero.x = 0;
        zero.y = 0;
        zero.z = 0;
        if (profile->state == 0) {
            goto reset;
        }
        global = &g_gameSession.clockPaused;
        if ((*global != 0) || (g_world.frozen != 0) || (global[-6] != 13)) {
reset:
            profile->amount = 0.0f;
            Rumble_FreeAllPoolNodes(profile->object);
        } else {
            object = profile->object;
            Rumble_RecycleFinishedEffectNodes(object);
            first = Rumble_GetSpatialEffectLevel(&g_controllerRumblePool, profile->x, profile->y, profile->z);
            profile->amount = first + Rumble_GetSpatialEffectLevel(object, zero.x, zero.y, zero.z);
        }
        if (profile->active != 0) {
            if (profile->amount != 0.0f) {
                profile->timer += profile->amount;
                if (profile->timer >= g_controllerRumbleUpdateInterval) {
                    profile->timer -= g_controllerRumbleUpdateInterval;

#if defined(VERSION_EU)
Control_StartMotorEu
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)
Control_StartMotorEuX
#elif defined(VERSION_US)
osMotorStart
#else
osMotorStart
#endif
((void *)profile->status);
                    return;
                }
            }

#if defined(VERSION_EU)
Control_StopMotorEu
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#if defined(VERSION_EU) || defined(VERSION_US)
Control_StopMotorEuX
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)
((unsigned int (*)(void *))Control_StopMotorEuX)
#endif
#elif defined(VERSION_US)
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
osMotorStop
#elif defined(VERSION_US)
((unsigned int (*)(void *))osMotorStop)
#endif
#else
#if defined(VERSION_DE)
((unsigned int (*)(void *))Control_StopMotorDe)
#elif defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Control_StopMotorDe
#endif
#endif
((void *)profile->status);
        }
    }
}

/* Reinitializes a present controller pak entry under the pak queue lock: resets its rumble counters and effect pool, initialises the motor, stops it with the version's stop routine, retries the initialisation (marking the pak active when it succeeds), and releases the lock. */

void Control_ResetControllerPak(ControllerProfile *pakProfile) {
    ControllerRumbleView *rumble = (ControllerRumbleView *)pakProfile;

    if (g_controllerInputReady != 0 && rumble->flags != 0) {
        if (osRecvMesg(&g_controllerReadMessageQueue, 0, 1) == 0) {
            g_controllerAudioThreadId = osGetThreadId(0);
        }
        Control_ReadControllerStates();
        g_controllerPakFrontendState = 2;
        rumble->state = 0;
        rumble->amount = 0;
        rumble->timer = 0;
        Rumble_InitPoolNodes(&pakProfile->effectPool, &pakProfile->effectNodes, 3);
        osMotorInit(&g_controllerSiMessageQueue, &pakProfile->pak, pakProfile->port);

#if defined(VERSION_DE)
        ((u32 (*)(void *))Control_StopMotorDe)(&pakProfile->pak);
#elif defined(VERSION_EU)
        Control_StopMotorEu(&pakProfile->pak);
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)
        ((u32 (*)(void *))Control_StopMotorEuX)(&pakProfile->pak);
#else
        ((u32 (*)(void *))osMotorStop)(&pakProfile->pak);
#endif

        if (osMotorInit(&g_controllerSiMessageQueue, &pakProfile->pak, pakProfile->port) == 0) {
            rumble->active = 1;
        }
        g_controllerPakFrontendState = 2;
        g_controllerAudioThreadId = -1;
        osSendMesg(&((PakQueueState *)&g_controllerPakFrontendState)->queue, 0, 1);
    }
}

/** Report whether flag 0x1000 is set in the word. */
int Control_IsStartPressed(Shared_Effect *object) {
    int flags = object->state & 0x1000;
    return flags != 0;
}

int Control_IsStartButtonSet(Shared_Effect *effect) {
    int flag = effect->state & 0x1000;
    return flag != 0;
}

/** Return the high bit of the byte. */
unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile) {
    return ((u8)(profile->pressedButtons >> 8)) >> 7;
}

/** Report whether any of the selected object flag bytes are set. */
int Control_IsLeftPressed(struct ControllerProfile *object) {
    return (object->buttonState & 0x20202) != 0;
}

/** Report whether any selected status bit is set. */
int Control_IsRightPressed(struct ControllerProfile *object) {
    return (object->buttonState & 0x40101) != 0;
}

int Control_IsNavUp(ControllerProfile *controllerProfile) {
    int flag = controllerProfile->buttonState & 0x10808;
    return flag != 0;
}

int Control_IsNavDown(ControllerProfile *controllerProfile) {
    int flag = controllerProfile->buttonState & 0x80404;
    return flag != 0;
}

int Control_IsButtonBSet(Shared_Effect *effect) {
    int flag = effect->state & 0x4000;
    return flag != 0;
}

int Control_IsButtonAPressed(struct ControllerProfile *controllerProfile) {
    return ((u8)(controllerProfile->pressedButtons >> 8)) >> 7;
}

void Control_CommitControllerInputs(void) {
    s32 i;
    ControllerProfile *profile;
    s32 frontendActive;
    s32 frontendFlagOn;

    if (g_controllerInputReady != 0) {
        i = 0;
        frontendFlagOn = 1;
        profile = g_controllerProfiles;
        for (; i < 4; i++, profile += 1) {
            Control_CommitProfileInput(profile);
            frontendActive = Tsmos_IsFrontendActive();
            if (frontendActive != frontendFlagOn) {
                continue;
            }
            if (Tsmos_IsControllerStateActive() != frontendActive) {
                continue;
            }
            Controller_DispatchControllerProfileChanges(profile);
        }
        Control_CommitProfileInput(&g_combinedControllerProfile);
    }
}

/** Shift the trailing state-history slots down and clear the newest slot. */
void Control_CommitProfileInput(ControllerProfile *controllerProfile) {
    u8 previousStickX;
    u8 previousStickY;
    s32 previousButtons;
    s32 newButtons;
    u32 newPressedButtons;
    s32 historySlot0;
    s32 historySlot1;
    s32 historySlot2;

    previousStickX = controllerProfile->stickX;
    previousStickY = controllerProfile->stickY;
    previousButtons = controllerProfile->buttons;
    newButtons = controllerProfile->inputButtons;
    newPressedButtons = controllerProfile->inputPressedButtons;
    historySlot0 = controllerProfile->inputHistory[0];
    historySlot1 = controllerProfile->inputHistory[1];
    historySlot2 = controllerProfile->inputHistory[2];
    controllerProfile->inputPressedButtons = 0;
    controllerProfile->inputHistory[0] = 0;
    controllerProfile->inputHistory[1] = 0;
    controllerProfile->inputHistory[2] = 0;
    controllerProfile->previousStickX = previousStickX;
    controllerProfile->previousStickY = previousStickY;
    controllerProfile->previousButtons = previousButtons;
    controllerProfile->buttons = newButtons;
    controllerProfile->pressedButtons = newPressedButtons;
    controllerProfile->history[0] = historySlot0;
    controllerProfile->history[1] = historySlot1;
    controllerProfile->buttonState = historySlot2;
}

s32 Control_AcquireControllerLock(s32 block) {

    s32 result;

    result = osRecvMesg(&g_controllerReadMessageQueue, 0, block) == 0;
    if (result != 0) {
        g_controllerAudioThreadId = osGetThreadId(0);
    }
    return result;
}

void Control_ReleasePakLock(void) {

    g_controllerAudioThreadId = -1;
    osSendMesg(&g_controllerReadMessageQueue, 0, 1);
}

/** Fetch-and-clear: return the old slot value, then zero it. */
s32 Control_TakePakChange(s32 controllerPort) {
    s32 old;

    if (Control_IsControllerPakEnabled(controllerPort) == 0) {
        return 0;
    }
    old = g_controllerPakState[controllerPort];
    g_controllerPakState[controllerPort] = 0;
    return old;
}

s32 Control_PeekPakChange(s32 controllerPort) {
    if (Control_IsControllerPakEnabled(controllerPort) == 0) {
        return 0;
    }
    return g_controllerPakState[controllerPort];
}

int Control_IsControllerConnected(int controllerPort) {
    return ((g_controllerReadStatusBytes[controllerPort * 4] >> 3) ^ 1) & 1;
}

int Control_IsControllerPakPresent(int controllerPort) {
    return g_controllerPakStatusBytes[controllerPort * 4] & 1;
}

s32 Control_AnyControllerConnected(void) {
    s32 i = 0;
    while (1) {
        if (!(((g_controllerReadStatusBytes[i * 4] >> 3) ^ 1) & 1)) {
            i += 1;
            if (i >= 4) {
                return 0;
            }
        } else {
            return 1;
        }
    }
}

s32 Control_CountConnectedControllers(void) {
    s32 count;
    s32 i;

    count = 0;
    i = 0;
    do {
        if (((g_controllerReadStatusBytes[i * 4] >> 3) ^ 1) & 1) {
            count += 1;
        }
        i += 1;
    } while (i < 4);
    return count;
}

s32 Control_FindConnectedControllerPort(s32 connectedOrdinal) {
    s32 connectedCount;
    s32 controllerPort;

    connectedCount = 0;
    controllerPort = 0;
loop_1:
    if (((g_controllerReadStatusBytes[controllerPort * 4] >> 3) ^ 1) & 1) {
        connectedCount += 1;
    }
    if ((connectedCount - 1) != connectedOrdinal) {
        controllerPort += 1;
        if (controllerPort >= 4) {
            return -1;
        }
        goto loop_1;
    }
    return controllerPort;
}

s32 Control_IsAnyControllerPakEnabled(void) {
    s32 i = 0;
    while (1) {
        if (g_controllerPakEnabledBytes[i] == 0) {
            i += 1;
            if (i >= 4) {
                return 0;
            }
        } else {
            return 1;
        }
    }
}

int Control_IsControllerPakEnabled(int controllerPort) {
    return g_controllerPakEnabledBytes[controllerPort];
}

void Control_EnableControllerPak(int controllerPort) {
    g_controllerPakEnabledBytes[controllerPort] = 1;
}

void Control_DisableControllerPak(int controllerPort) {
    g_controllerPakEnabledBytes[controllerPort] = 0;
}

void Control_EnableAllControllerPaks(void)
{
  int pakEnabled;
  s8 *lastEnabledByte;
  s32 controllerIndex;
  s8 *enabledByte;
  pakEnabled = 1;
  controllerIndex = 3;
  lastEnabledByte = &g_controllerPakEnabledLastByte;
  enabledByte = lastEnabledByte;
  do
  {
    *enabledByte = pakEnabled;
    controllerIndex -= 1;
    enabledByte -= 1;
  }
  while (controllerIndex >= 0);
}

void Control_DisableAllControllerPaks(void) {
    s32 controllerIndex;
    s8 *enabledByte;
    controllerIndex = 3;
    enabledByte = &g_controllerPakEnabledLastByte;
    do {
        *enabledByte = 0;
        controllerIndex -= 1;
        enabledByte -= 1;
    } while (controllerIndex >= 0);
}

/* CONTROL_CYCLEACTORSNAPSHOTMODE.CPP */

/* Advances the replay mode: when replays are possible (SetN64_IsModeThirteen, g_sessionOptionResetMode and the handle table) it
 * cycles the mode 0 -> 1 -> 2 -> 0, snapshots the actors and records the camera target, promoting mode 1
 * to 2 when the player's target changed or the player is in states 0x16 to 0x21 and recording the player's
 * target instead; otherwise the mode is cleared. An active mode arms the 240-frame timer. */

/** Return the global word at g_controllerActorSnapshotSavedActorId. */

/** Clear the global word. */

/* Restores every actor from the global replay table: copies its saved state block back into the actor and, when
 * the table's mode is 1, also restores its position, its saved value and its identifier resolved from the
 * saved handle through Scene_GetModelSectionTwoRecord. */

const float g_snapshotModeColorScale[3] = {
    1.0f, 1.0f, 0.003921569f,
};
void Control_SetProfileMode(ControllerProfile *slot, s32 profileMode) {
    slot->mode = profileMode;
    if (profileMode == 0) {
        Control_ResetControllerPak(slot);
    }
}

void Control_ResetControllerProfiles(void) {
    ControllerProfile *slot;
    s32 i;

    i = 0;
    slot = g_controllerProfiles;
    do {
        Control_ResetControllerPak(slot);
        i += 1;
        slot += 1;
    } while (i < 4);
}

void Control_SetControllerMode(s32 a) {
    ControllerProfile *slot;
    s32 i;

    i = 0;
    slot = g_controllerProfiles;
    do {
        slot->mode = a;
        if (a == 0) {
            Control_ResetControllerPak(slot);
        }
        i += 1;
        slot += 1;
    } while (i < 4);
    if (a == 0) {
        Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
    }
}

void Control_SaveControllerSetup(void)
{
  s32 profileValue;
  s32 profileIndex;
  s32 profileByteOffset;
  s32 profilesReset;
  ControllerProfile *profileCursor;
  profileIndex = 0;
  profileByteOffset = 0;
  do
  {
    profileValue = *((s32 *) ((&g_controllerProfileModeBase) + profileByteOffset));
 do { g_controllerSnapshotProfileValues[profileIndex] = profileValue; profileIndex += 1; profileByteOffset += 548; } while (0);
  }
  while (profileIndex < 4);
  profilesReset = 0;
  Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
  profileCursor = g_controllerProfiles;
  do
  {
    Control_ResetControllerPak(profileCursor);
    profilesReset += 1;
    profileCursor += 1;
  }
  while (profilesReset < 4);
  g_controllerSetupSaved = 1;
}

void Control_RestoreControllerSetup(void) {
    ControllerProfile *slot;
    s32 i;
    s32 j;
    s32 profileByteOffset;
    s32 savedProfileValue;

    if (g_controllerSetupSaved != 0) {
        i = 0;
        slot = g_controllerProfiles;
        do {
            Control_ResetControllerPak(slot);
            i += 1;
            slot += 1;
        } while (i < 4);
        j = 0;
        profileByteOffset = 0;
        do {
            savedProfileValue = g_controllerSnapshotProfileValues[j];
            j += 1;
            *(s32 *)(&g_controllerProfileModeBase + profileByteOffset) = savedProfileValue;
            profileByteOffset += 548;
        } while (j < 4);
        Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
        g_controllerSetupSaved = 0;
    }
}

void Control_ClearMenuControlFlag(void) {
    g_controlMenuControlFlag = 0;
}

void Control_SetMenuControlFlag(void) {
    g_controlMenuControlFlag = 1;
}

void Control_CycleActorSnapshotMode(void) {
    Snapshot *snapshot;
    Player *player;
    s32 enabled;
    Shared_Game *options;

    enabled = SetN64_IsModeThirteen() != 0;
    snapshot = &g_controllerActorSnapshot;
    if (g_sessionOptionResetMode == 0) {
        enabled = 0;
    }
    if (&g_world.mode == 0) {
        enabled = 0;
    }
    if (enabled) {
        switch (snapshot->mode) {
        case 0:
            snapshot->mode = 1;
            break;
        case 1:
            snapshot->mode = 2;
            break;
        case 2:
        default:
            snapshot->mode = 0;
            break;
        }
        Control_SaveActorSnapshot();
        snapshot->savedActorId = g_activeActorKind;
        options = &g_playerViewRenderContext.game;
        if (options->local == 0) {
            player = Playerai_GetFirstPlayer(&g_playerViewRenderContext);
            if (player != 0) {
                if (snapshot->mode == 1 &&
                    (g_activeActorKind != ((Player *)player)->model ||
                     (u16)(((Player *)player)->pose - 22) < 12)) {
                    snapshot->mode = 2;
                }
                snapshot->savedActorId = ((Player *)player)->model;
            }
        }
    } else {
        snapshot->mode = 0;
    }
    if (snapshot->mode != 0) {
        snapshot->countdown = 240;
        snapshot->active = 1;
    } else {
        snapshot->countdown = 0;
        snapshot->active = 0;
    }
}

void Control_ResetActorSnapshot(void) {
    g_controllerActorSnapshot.active = 0;
    g_controllerActorSnapshot.mode = 0;
    g_controllerActorSnapshot.countdown = 0;
}

s32 Control_GetSnapshotActorId(void) {
    return g_controllerActorSnapshot.savedActorId;
}

int Control_IsSnapshotActive(void) {
    return g_controllerActorSnapshot.active;
}

void Control_DeactivateActorSnapshot(void) {
    g_controllerActorSnapshot.active = 0;
}

void Control_RestoreActorSnapshot(void) {
    s32 i;
    SnapshotActorView *actor;
    Snapshot *snapshot;
    ActorList *list;

    list = (ActorList *)&g_playerViewRenderContext;
    snapshot = &g_controllerActorSnapshot;
    for (i = 0; i < list->count; i++, list = (ActorList *)&g_playerViewRenderContext) {
        actor = &list->actors[i];
        actor->block = snapshot->blocks[i];
        if (snapshot->mode == 1) {
            actor->position = snapshot->positions[i];
            actor->yaw = snapshot->values[i];
            actor->id = Scene_GetModelSectionTwoRecord(&g_world, snapshot->handles[i]);
        }
    }
}

void Control_TickSnapshotCountdown(void) {
    Snapshot *p = &g_controllerActorSnapshot;
    s32 v = p->countdown;
    if (v != 0) {
        v = v - 1;
        p->countdown = v;
        if (v == 0) {
            p->mode = 0;
        }
    }
}

void Control_SaveActorSnapshot(void) {
    s32 i;
    SnapshotActorView *actor;
    Snapshot *snapshot;
    ActorList *list;

    list = (ActorList *)&g_playerViewRenderContext;
    snapshot = &g_controllerActorSnapshot;
    for (i = 0; i < list->count; i++) {
        actor = &list->actors[i];
        snapshot->blocks[i] = actor->block;
        snapshot->positions[i] = actor->position;
        snapshot->values[i] = actor->yaw;
        snapshot->handles[i] = Scene_GetModelSectionTwoIndex(&g_world, actor->id);
        list = (ActorList *)&g_playerViewRenderContext;
    }
}

/** Initialize a three-word record with a value and two zero words. */
void Control_InitializeCurvePlayer(unsigned int *record, unsigned int value) {
    record[0] = value;
    record[1] = 0;
    record[2] = 0;
}

s32 Control_AdvanceEffectCurve(SampledEffectCurveState *curvePlayer) {
    f32 advancedTime;
    f32 remainingTime;
    s32 type;
    SampledCurve *curve;

    curve = curvePlayer->curve;
    type = curve->type;
    switch (type) {
    case 0: {
        f32 divisor = g_displayedFramebufferAndRefreshRate[1];
        advancedTime = curvePlayer->time + (g_controllerEffectTimeAdvanceScale.value / divisor);
        curvePlayer->time = advancedTime;
        if (curve->length <= advancedTime) {
            return 1;
        }
        goto block_7;
    }
    case 1: {
        RandomCurve *random = (void *)curve;
        f32 divisor = g_displayedFramebufferAndRefreshRate[1];
        remainingTime = curvePlayer->time - (g_controllerEffectTimeRetreatScale.value / divisor);
        curvePlayer->time = remainingTime;
        if (remainingTime <= 0.0f) {
            curvePlayer->time =
                remainingTime + random->period;
            curvePlayer->value = Graphu64_RandomBetween(
                (f32)random->minimum * g_controllerEffectRandomRangeScale.value,
                (f32)random->maximum * g_controllerEffectRandomRangeScale.value);
        }
        goto block_7;
    }
    default:
block_7:
        return 0;
    }
}

/* Samples a curve at the player's time: a byte-sample curve (type 0) indexes its samples by time times 16 over the curve length and scales the byte to 0..1, a constant curve (type 1) returns the player's value, and any other type yields zero. */

float Control_SampleEffectCurve(SampledEffectCurveState *p) {
    SampledCurve *c = p->curve;

    switch (c->type) {
    case 0:
        return c->samples[(int)(p->time * 16.0f / c->length)] * (1.0f / 255.0f);
    case 1:
        return p->value;
    }
    return 0.0f;
}

/* CONTROL_READCONTROLLERSTATES_DATA.CPP */

const float g_controllerStatesQuarter[1] = {
    0.25f,
};

/* CONTROL_THREAD_LABELS_GERMAN.CPP */

#if defined(VERSION_DE)
struct {
    unsigned int w0[3];
    unsigned char b1[88];
} g_threadLabelWordsGerman = {
    {
        0x6F000000, 0x73636865, 0x64756C65,
    },
    {
        0x61, 0x75, 0x64, 0x69, 0x6F, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x65, 0x64, 0x75, 0x6C, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x72, 0x61, 0x67, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00,
        0x63, 0x61, 0x63, 0x68, 0x65, 0x00, 0x00, 0x00, 0x6C, 0x6F, 0x61, 0x64, 0x65, 0x72, 0x00, 0x00,
        0x64, 0x65, 0x63, 0x6F, 0x6D, 0x70, 0x72, 0x65, 0x73, 0x73, 0x6F, 0x72, 0x00, 0x00, 0x00, 0x00,
        0x66, 0x61, 0x75, 0x6C, 0x74, 0x00, 0x00, 0x00, 0x6D, 0x61, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x69, 0x64, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00,
    },
};
#endif

/* CONTROL_RESTOREACTORSNAPSHOT.CPP */
#if defined(VERSION_US)


struct {
    unsigned int w0[3];
    unsigned char b1[88];
} g_threadLabelWordsUs = {
    {
        0x00000000, 0x116D5F46, 0x61646554,
    },
    {
        0x61, 0x75, 0x64, 0x69, 0x6F, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x65, 0x64, 0x75, 0x6C, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x72, 0x61, 0x67, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00,
        0x63, 0x61, 0x63, 0x68, 0x65, 0x00, 0x00, 0x00, 0x6C, 0x6F, 0x61, 0x64, 0x65, 0x72, 0x00, 0x00,
        0x64, 0x65, 0x63, 0x6F, 0x6D, 0x70, 0x72, 0x65, 0x73, 0x73, 0x6F, 0x72, 0x00, 0x00, 0x00, 0x00,
        0x66, 0x61, 0x75, 0x6C, 0x74, 0x00, 0x00, 0x00, 0x6D, 0x61, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x69, 0x64, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00,
    },
};
#endif
#if defined(VERSION_EU)

struct {
    unsigned int w0[3];
    unsigned char b1[88];
} g_threadLabelWordsEuropean = {
    {
        0x24420010, 0xA7C20000, 0x00111400,
    },
    {
        0x61, 0x75, 0x64, 0x69, 0x6F, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x65, 0x64, 0x75, 0x6C, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x72, 0x61, 0x67, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00,
        0x63, 0x61, 0x63, 0x68, 0x65, 0x00, 0x00, 0x00, 0x6C, 0x6F, 0x61, 0x64, 0x65, 0x72, 0x00, 0x00,
        0x64, 0x65, 0x63, 0x6F, 0x6D, 0x70, 0x72, 0x65, 0x73, 0x73, 0x6F, 0x72, 0x00, 0x00, 0x00, 0x00,
        0x66, 0x61, 0x75, 0x6C, 0x74, 0x00, 0x00, 0x00, 0x6D, 0x61, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x69, 0x64, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00,
    },
};
#endif

/* CONTROL_THREAD_LABELS_EUROPEAN_X.CPP */
#if defined(VERSION_EU_X)


struct {
    unsigned int w0[3];
    unsigned char b1[88];
} g_threadLabelWordsEuropeanX = {
    {
        0x0044EE24, 0x0044EE24, 0x0044EE24,
    },
    {
        0x61, 0x75, 0x64, 0x69, 0x6F, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x65, 0x64, 0x75, 0x6C, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x72, 0x61, 0x67, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00,
        0x63, 0x61, 0x63, 0x68, 0x65, 0x00, 0x00, 0x00, 0x6C, 0x6F, 0x61, 0x64, 0x65, 0x72, 0x00, 0x00,
        0x64, 0x65, 0x63, 0x6F, 0x6D, 0x70, 0x72, 0x65, 0x73, 0x73, 0x6F, 0x72, 0x00, 0x00, 0x00, 0x00,
        0x66, 0x61, 0x75, 0x6C, 0x74, 0x00, 0x00, 0x00, 0x6D, 0x61, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x69, 0x64, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00,
    },
};
#endif

/* CONTROL_THREAD_LABELS_US_REV1.CPP */

#if defined(VERSION_US_REV1)
struct {
    unsigned int w0[3];
    unsigned char b1[88];
} g_threadLabelWordsUsRevision = {
    {
        0x0044E674, 0x0044E674, 0x0044E674,
    },
    {
        0x61, 0x75, 0x64, 0x69, 0x6F, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x65, 0x64, 0x75, 0x6C, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x72, 0x61, 0x67, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00,
        0x63, 0x61, 0x63, 0x68, 0x65, 0x00, 0x00, 0x00, 0x6C, 0x6F, 0x61, 0x64, 0x65, 0x72, 0x00, 0x00,
        0x64, 0x65, 0x63, 0x6F, 0x6D, 0x70, 0x72, 0x65, 0x73, 0x73, 0x6F, 0x72, 0x00, 0x00, 0x00, 0x00,
        0x66, 0x61, 0x75, 0x6C, 0x74, 0x00, 0x00, 0x00, 0x6D, 0x61, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x69, 0x64, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00,
    },
};
#endif
