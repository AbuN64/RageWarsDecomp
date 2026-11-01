#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJB.H"
#include "TYPES.H"
#include "COMMON/LEVEL_TRACK.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PACKED.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/LEVEL_INPUT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "PFS/CONTROLLER.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "COMMON/PAKQUEUESTATE.H"
#include "libultra/os/getthreadid.h"

/* CONTROLLER.CPP */
/* Resets the controller and profile state for a new session: reinitialises the input buffers and stream through Rumble_InitPoolNodes_Controller, osCreateMesgQueue, osSetEventMesg_Controller, osContInit, osGetThreadId and osSendMesg_Mutex, then for slots 3 down to 0 clears the slot's three state words, refreshes its pad through Control_DisableControllerPakDe and counts the profiles Ovlgame_ResetControllerProfile accepts in g_connectedControllerProfileCount, remembering the lowest accepted slot in g_firstConnectedControllerPort; finally checks the profile just below slot 0 with mode 4, marks the session reset and returns the remembered slot. */

extern char g_controllerRumblePool[];
extern u8 g_controllerPakFrontendState;
extern char g_controllerSiMessageQueue[];

extern signed char g_controllerInputReady;

extern void Rumble_InitPoolNodes(char *, char *, s32);

extern void Control_DisableControllerPak(s32);

s16 Ovlgame_InitializeControllerSession(void) {
    s32 i;

    Rumble_InitPoolNodes(g_controllerRumblePool, g_controllerRumbleNodes, 8);
    g_controllerPakFrontendState = 2;
    osCreateMesgQueue(g_controllerSiMessageQueue, g_controllerSiMessageBuffer, 1);
    osCreateMesgQueue(&g_controllerReadMessageQueue, g_controllerAccessMessages, 1);
    osSetEventMesg(5, g_controllerSiMessageQueue, 1);
    osContInit(g_controllerSiMessageQueue, g_controllerPresenceBits, g_controllerQueryStatus);
    osGetThreadId(0);
    g_controllerAudioThreadId = -1;
    osSendMesg(&g_controllerReadMessageQueue, 0, 1);
    g_firstConnectedControllerPort = -1;
    g_connectedControllerProfileCount = 0;
    for (i = 3; i >= 0; i--) {
        g_controllerPakState[i] = 0;
        g_controllerPakReinitializePending[i] = 0;
        g_controllerPakProbePending[i] = 0;
        Control_DisableControllerPak(i);
        if (Ovlgame_ResetControllerProfile(&g_controllerProfiles[i], i) != 0) {
            g_firstConnectedControllerPort = i;
            g_connectedControllerProfileCount++;
        }
    }
    Ovlgame_ResetControllerProfile(&g_controllerProfiles[i], 4);
    g_controllerInputReady = 1;
    return g_firstConnectedControllerPort;
}

s32 Ovlgame_ResetControllerProfile(ControllerProfile *profile, s32 port) {
    s32 i;
    s32 connected;
    profile->port = port;
    profile->connected = 0;
    profile->pakActive = 0;
    profile->mode = 0;
    profile->reset = 0;
    profile->reservedWordA = 0;
    profile->reservedWordB = 0;
    profile->reservedWordC = 0;
    profile->stickX = 0;
    profile->stickY = 0;
    profile->previousStickX = 0;
    profile->previousStickY = 0;
    profile->inputPreviousButtons = 0;
    profile->inputButtons = 0;
    profile->inputPressedButtons = 0;
    profile->inputHistory[0] = 0;
    profile->inputHistory[1] = 0;
    profile->inputHistory[2] = 0;
    for (i = 0; i < 32; i++) {
        profile->buttonHistory[i].taps = 0;
        profile->buttonHistory[i].age = 0;
        profile->buttonHistory[i].repeat = 48;
        profile->buttonHistory[i].held = 0;
    }
    connected = ((g_controllerReadStatusBytes[port * 4] >> 3) ^ 1) & 1;
    profile->pakAmount = 0;
    profile->pakTimer = 0;
    profile->connected = connected;
    Rumble_InitPoolNodes((char *)&profile->effectPool, (char *)profile->effectNodes, 3);
    return profile->connected;
}
