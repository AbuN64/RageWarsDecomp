#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/LONE/CONTROLLER_SI_MESSAGE_QUEUE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CACHE_ALLOCATERESOURCE.H"
#include "COMMON/RECORDRECAT1C.H"
#include "TYPES.H"
#include "UI/X_FILES/X_PLUS.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

/* Releases the save buffer and clears its global state. */
extern void Cache_DrainAndCompactResources(s32);





extern void Control_ReadControllerStates(void);

extern u8 g_controllerPakFrontendState;


extern PakRecord g_controllerPakChannelRecords[];




extern s32 Note_UpdateStatus(s32 a0);

extern void Control_ReleasePakLock(void);

void Note_AllocateScratchBuffer(void) {
    struct CacheResourceBlockView *block;
    s32 buffer;

    block = Cache_AllocateResource(0, 2064, 35, &g_pakPakStateNoteName);
    buffer = block->first;
    g_controllerPakProbeResource = (s32 *)block;
    g_controllerPakNoteLists = buffer;
    XPlus_FillMemory((void *)buffer, 0, 2064);
    g_controllerPakProbeActive = 1;
}

void Note_FreeScratchBuffer(void) {
    Cache_DrainAndCompactResources(0);
    if (g_controllerPakProbeResource) {
        Cache_ReleaseResource(0, g_controllerPakProbeResource);
        g_controllerPakProbeResource = 0;
        g_controllerPakNoteLists = 0;
    }
    g_controllerPakProbeActive = 0;
}

/* Probes the Controller Pak slot for kind and records its state: 2 when the probe succeeds, otherwise 3 or 1 depending on Note_UpdateStatus. */
void Note_ProbeStatus(s32 kind)
{
    PakRecord *cur;
    s32 ready;

    ((void (*)(s32))Control_AcquireControllerLock)(1);
    Control_ReadControllerStates();
    g_controllerPakFrontendState = 2;

    cur = g_controllerPakChannelRecords + kind;
    if (g_controllerReadStatusBytes[kind * 4] != 0) {
        cur->present = 0;
        ready = 0;
    } else {
        cur->present = osMotorInit(g_controllerSiMessageQueue, cur->pak, kind) == 0;
        ready = cur->present;
    }

    if (ready != 0) {
        g_controllerPakChannelStates[kind] = 2;
    } else if (Note_UpdateStatus(kind) != 0) {
        g_controllerPakChannelStates[kind] = 3;
    } else {
        g_controllerPakChannelStates[kind] = 1;
    }
    Control_ReleasePakLock();
}

/* Returns entry i of g_controllerPakChannelStatuses when entry i of the state table g_controllerPakChannelStates is 3, otherwise -2. */



s32 Note_GetStatus(s32 index) {
    if (g_controllerPakChannelStates[index] != 3) {
        return -2;
    }
    return g_controllerPakChannelStatuses[index];
}

/* Returns whether entry i of the word table g_controllerPakChannelStates equals 2. */


s32 Note_IsChannelReady(s32 index) {
    return g_controllerPakChannelStates[index] == 2;
}
