#include "ENGINE/CONTROL.H"
#include "COMMON/TRIPLE.H"
#include "include_asm.h"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "libultra/os/getthreadid.h"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

#include "OS/controller.H"
/* Reads the four controllers once per frame and folds them into the combined input record g_combinedControllerProfile.
 * State 0 starts a read through the message queue, converts the pads to the four per-player input
 * records (Control_UpdateControllerInput), ORs their button words into the combined record, adds the stick
 * bytes, and rescales the combined sticks by g_controllerInputScale. States 1 and 3 restart or query the
 * controllers, state 2 does nothing. */
extern u8 g_controllerPakFrontendState;
extern char g_controllerSiMessageQueue;
extern ContPad g_controllerPadData[4];


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

extern u8 g_controllerInputReady;
extern char g_controllerRumblePool;


extern void Control_UpdateControllerRumble(void *);



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

extern s32 Rumble_InitPoolNodes(void *effectPool, void *nodeStorage, s32 nodeCount);




void Control_RefreshControllerConnection(void *profile) {
    char *o = (char *) profile;
    s32 type;
    s32 bit;
    s32 bit2;
    s32 i;

    type = ((ControllerInputRenderView *)(o))->port;
    bit = ((g_controllerReadStatusBytes[type * 4] >> 3) ^ 1) & 1;
    if (bit != 0 && ((ControllerInputRenderView *)(o))->connected == 0) {
        i = 0;
        ((ControllerInputRenderView *)(o))->port = type;
        ((ControllerInputRenderView *)(o))->connected = 0;
        ((ControllerInputRenderView *)(o))->pakActive = 0;
        ((ControllerInputRenderView *)(o))->mode = 0;
        ((ControllerInputRenderView *)(o))->reset = 0;
        ((ControllerInputRenderView *)(o))->connectResetWord1 = 0;
        ((ControllerInputRenderView *)(o))->connectResetWord2 = 0;
        ((ControllerInputRenderView *)(o))->connectResetWord3 = 0;
        ((ControllerInputRenderView *)(o))->stickX = 0;
        ((ControllerInputRenderView *)(o))->stickY = 0;
        ((ControllerInputRenderView *)(o))->previousStickX = 0;
        ((ControllerInputRenderView *)(o))->previousStickY = 0;
        ((ControllerInputRenderView *)(o))->inputPreviousButtons = 0;
        ((ControllerInputRenderView *)(o))->inputButtons = 0;
        ((ControllerInputRenderView *)(o))->inputPressedButtons = 0;
        ((ControllerInputRenderView *)(o))->inputHistory1 = 0;
        ((ControllerInputRenderView *)(o))->inputHistory2 = 0;
        ((ControllerInputRenderView *)(o))->inputHistory3 = 0;
        do {
            ((struct ControllerInputByteStateView *) (o + (i * 4)))->taps = 0;
            ((struct ControllerInputByteStateView *) (o + (i * 4)))->age = 0;
            ((struct ControllerInputByteStateView *) (o + (i * 4)))->repeat = 48;
            ((struct ControllerInputByteStateView *) (o + (i * 4)))->held = 0;
            i += 1;
        } while (i < 32);
        bit2 = ((g_controllerReadStatusBytes[type * 4] >> 3) ^ 1) & 1;
        ((ControllerInputRenderView *)(o))->pakAmount = 0;
        ((ControllerInputRenderView *)(o))->pakTimer = 0;
        ((ControllerInputRenderView *)(o))->connected = bit2;
        Rumble_InitPoolNodes(&((ControllerProfile *)o)->effectPool, &((ControllerProfile *)o)->effectNodes, 3);
    }
    ((ControllerInputRenderView *)(o))->connected = bit;
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
    /* scheduler lever (owner keeps it; card c371fLFrcRoq hunts its real cause): global-alloc ranks fx (8 refs, 33 insns
       live) below fy (8 refs, 32 insns), so plain `fx = x; fy = y;` gives fx $f1 and fy $f0; the one-shot loop makes
       fx 9 weighted refs, which flips it to $f0/$f1. Plain forms tried: statement orders, inline helpers, macros, types, flags. */
    do { fx = x; } while (0);
    fy = y;
    if (fx == -128.0f) fx = -127.0f;
    if (fy == -128.0f) fy = -127.0f;
    if (fx < -80.0f) fx = -80.0f;
    if (80.0f < fx) fx = 80.0f;
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
