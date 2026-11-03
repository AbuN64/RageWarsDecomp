#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/LONE/CONTROLLER_RUMBLE_POOL.H"
#include "COMMON/WORLD.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "libultra/os/getthreadid.h"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "ENGINE/CONTROL.H"
#include "ENGINE/RUMBLE.H"
#include "../../../sdk/include/libultra/os/control_updatecontrollerrumble_data.CPP.h"

/* 80263760_6.CPP */


#if defined(VERSION_EU)
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)

#elif defined(VERSION_US)
#else
#endif
#if defined(VERSION_EU)

#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)

#elif defined(VERSION_US)

#else

#endif

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

/* 80263760_7.CPP */
/* Reinitializes a present controller pak entry under the pak queue lock, resets its counters and label, retries initialization, and releases the lock; an unsigned pointer local and a queue address relative to the adjacent status byte separate address lifetimes and preserve register scheduling. */

extern u8 g_controllerInputReady;

extern u8 g_controllerPakFrontendState;

extern char g_controllerSiMessageQueue;





#if defined(VERSION_EU)

#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)

#elif defined(VERSION_US)

#else

#endif

extern void Controller_DispatchControllerProfileChanges(char *controllerProfile);

void Control_ResetControllerPak(ControllerProfile *pakProfile) {

    u32 address=(u32)pakProfile;
    char *o=(char *)address;

    if (g_controllerInputReady != 0 && ((ControllerRumbleView *)address)->flags != 0) {
        if (osRecvMesg(&g_controllerReadMessageQueue, 0, 1) == 0) {
            g_controllerAudioThreadId = osGetThreadId(0);
        }
        Control_ReadControllerStates();
        g_controllerPakFrontendState = 2;
        ((ControllerRumbleView *)o)->state = 0;
        ((ControllerRumbleView *)o)->amount = 0;
        ((ControllerRumbleView *)o)->timer = 0;
        Rumble_InitPoolNodes(&((ControllerProfile *)o)->effectPool, &((ControllerProfile *)o)->effectNodes, 3);
        osMotorInit(&g_controllerSiMessageQueue, &((ControllerProfile *)o)->pak, pakProfile->port);

#if defined(VERSION_EU)
Control_StopMotorEu
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#if defined(VERSION_EU) || defined(VERSION_US)
Control_StopMotorEuX
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)
((u32 (*)(void *))Control_StopMotorEuX)
#endif
#elif defined(VERSION_US)
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
osMotorStop
#elif defined(VERSION_US)
((u32 (*)(void *))osMotorStop)
#endif
#else
#if defined(VERSION_DE)
((u32 (*)(void *))Control_StopMotorDe)
#elif defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Control_StopMotorDe
#endif
#endif
(((ControllerRumbleView *)o)->status);

#if defined(VERSION_EU)
Control_StopMotorEu
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#if defined(VERSION_EU) || defined(VERSION_US)
Control_StopMotorEuX
#elif defined(VERSION_EU_X) || defined(VERSION_US_REV1)
((u32 (*)(void *))Control_StopMotorEuX)
#endif
#elif defined(VERSION_US)
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
osMotorStop
#elif defined(VERSION_US)
((u32 (*)(void *))osMotorStop)
#endif
#else
#if defined(VERSION_DE)
((u32 (*)(void *))Control_StopMotorDe)
#elif defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Control_StopMotorDe
#endif
#endif
(((ControllerRumbleView *)o)->status);
        if (osMotorInit(&g_controllerSiMessageQueue, &((ControllerProfile *)o)->pak, pakProfile->port) == 0) {
            ((ControllerRumbleView *)o)->active = 1;
        }
        g_controllerPakFrontendState = 2;
        g_controllerAudioThreadId = -1;
        osSendMesg(&((PakQueueState *)&g_controllerPakFrontendState)->queue, 0, 1);
    }
}

/** Report whether flag 0x1000 is set in the word at offset 0xB4. */
int Control_IsStartPressed(Shared_Effect *object) {
    int flags = object->state & 0x1000;
    return flags != 0;
}

int Control_IsStartButtonSet(Shared_Effect *effect) {
    int flag = effect->state & 0x1000;
    return flag != 0;
}

/** Return the high bit of the byte at object offset 0xB6. */
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

int Control_IsNavUp(void *controllerProfile) {
    ControllerProfile *profile = controllerProfile;
    int flag = profile->buttonState & 0x10808;
    return flag != 0;
}

int Control_IsNavDown(void *controllerProfile) {
    ControllerProfile *profile = controllerProfile;
    int flag = profile->buttonState & 0x80404;
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
    ControllerProfile *p;
    s32 frontendActive;
    s32 one;

    if (g_controllerInputReady != 0) {
        i = 0;
        one = 1;
        p = g_controllerProfiles;
        for (; i < 4; i++, p += 1) {
            Control_CommitProfileInput(p);
            frontendActive = Tsmos_IsFrontendActive();
            if (frontendActive != one) {
                continue;
            }
            if (Tsmos_IsControllerStateActive() != frontendActive) {
                continue;
            }
            Controller_DispatchControllerProfileChanges(p);
        }
        Control_CommitProfileInput(&g_combinedControllerProfile);
    }
}

/** Shift the trailing state-history slots down and clear the newest slot. */
void Control_CommitProfileInput(void *controllerProfile) {
    ControllerProfile *o = controllerProfile;
    u8 t_c4;
    u8 t_c5;
    s32 t_b0;
    s32 t_18;
    u32 t_1c;
    s32 t_20;
    s32 t_24;
    s32 t_28;

    t_c4 = o->stickX;
    t_c5 = o->stickY;
    t_b0 = o->buttons;
    t_18 = o->inputButtons;
    t_1c = o->inputPressedButtons;
    t_20 = o->inputHistory[0];
    t_24 = o->inputHistory[1];
    t_28 = o->inputHistory[2];
    o->inputPressedButtons = 0;
    o->inputHistory[0] = 0;
    o->inputHistory[1] = 0;
    o->inputHistory[2] = 0;
    o->previousStickX = t_c4;
    o->previousStickY = t_c5;
    o->previousButtons = t_b0;
    o->buttons = t_18;
    o->pressedButtons = t_1c;
    o->history[0] = t_20;
    o->history[1] = t_24;
    o->buttonState = t_28;
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
