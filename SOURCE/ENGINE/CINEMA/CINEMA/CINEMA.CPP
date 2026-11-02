#include "COMMON/GROUP.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "TYPES.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "MENU/TRACK_UPDATETRACKCAMERA.H"
#include "COMMON/FUNCPTR.H"
#include "CAMERA/EXTERNS.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "ENGINE/CINEMA/CINEMA.H"
#include "include_asm.h"
#include "CAMERA/CCINEMA_UPDATESEQUENCE.H"

/* 80243A80_8.CPP */
/** Read the word at offset 0x38 from the globally selected record. */

/* Reports whether the globally selected record is active (its word at 0x38 is non-zero) and its
   value at 0x1C lies between the bounds at 0x30 and 0x34. */

void Cinema_EndSequence(void) {
    if (Cinema_IsSequenceActive() != 0) {
        s32 owner;
        Shared_MenuContext *record;

        Cinema_InitializeSequenceOnce(1);
        Cinema_CloseSequenceOnce();
        owner = (s32)g_cinemaSequenceState->owner;
        if (owner != 0) {
            Cache_ReleaseResource(0, owner);
        }
        record = g_cinemaSequenceState;
        record->owner = 0;
        record->resource = 0;
        record->active = 0;
        record->state3C = 0;
        record->fadeRequested = 0;
    }
}

void Cinema_RequestSequenceFade(void) {
    if (Cinema_IsSequenceActive() != 0 && Cinema_IsFadeAllowed() != 0 && g_cinemaSequenceState->fadeRequested == 0) {
        f32 requestedFade = k_cinemaFadeRequestValue_de;
        g_cinemaSequenceState->fadeRequested = 1;
        g_cinemaSequenceState->fade = requestedFade;
    }
}

/** Return the constant success result used by callers at VRAM 0x80245754. */
int Cinema_IsFadeAllowed(void) {
    return 1;
}

int Cinema_HasSequenceResource(void) {
    return g_cinemaSequenceState->resourceDC != -1;
}

int Cinema_IsSequenceActive(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    return record->active;
}

int Cinema_IsSequenceInWindow(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    float time;
    int inSequenceWindow = 0;

    if (record->active != 0) {
        time = record->time;
        if (record->start <= time && time <= record->end) {
            inSequenceWindow = 1;
        }
    }
    return inSequenceWindow;
}

s32 Cinema_HasSequenceEnded(void) {
    if (g_cinemaSequenceState->active != 0) {
        if (g_cinemaSequenceState->time > g_cinemaSequenceState->end) {
            return 1;
        }
        return 0;
    }
    return 1;
}

/* 80243A80_9.CPP */
/* Calls Track_UpdateTrackCamera when the globally selected record's word at 0x38 is non-zero. */

/* Calls Track_DrawTrackOverlay when the globally selected record's word at 0x38 is non-zero. */

/** Clear the global word at VRAM 0x800E2838. */

/* Reports whether Cinema_IsSequenceInWindow accepts the globally selected record and bit 2 of its word at 0x74
   is set. */

/* Returns the globally selected record's word at 0xAC while its word at 0x38 is non-zero, and 0
   otherwise. */

/* Returns the globally selected record's word at 0xA8 while its word at 0x38 is non-zero, and 0
   otherwise. */

extern f32 Track_EvaluateTrackScalar(f32 time);

/** Clear the word at offset 0x100 in the active object. */

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

/* Returns the globally selected record's float at 0xA0 scaled by g_cinemaTrackScalarScale. */

/* Returns the state object's word at its measured value field. */

s32 Cinema_IsSequenceIdle(void) {
    s32 result;
    result = 0;
    if (Cinema_IsSequenceActive() == 0) {
        result = Cinema_HasSequenceResource() == 0;
    }
    return result;
}

/** Return the word at offset 0x3C of the current global object. */
unsigned int Cinema_GetPlaybackPauseState(void) {
    return g_cinemaSequenceState->state3C;
}

void Cinema_UpdateSequenceTrack(void *camera) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    if (record->active != 0) {
        Track_UpdateTrackCamera(camera);
    }
}

void Cinema_DrawSequenceOverlay(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    if (record->active != 0) {
        Track_DrawTrackOverlay();
    }
}

/** Set the global word at VRAM 0x800E2838 to one. */
void Cinema_SetPlaybackFlag(void) {
    g_cinemaPlaybackFlag = 1;
}

void Cinema_ClearPlaybackFlag(void) {
    g_cinemaPlaybackFlag = 0;
}

/** Return the current global object word. */
unsigned int Cinema_GetPlaybackFlag(void) {
    return g_cinemaPlaybackFlag;
}

void Cinema_ClearPlaybackPauseState(void) {
    g_cinemaSequenceState->state3C = 0;
}

int Cinema_IsSequenceFlagTwoSet(void) {
    Shared_MenuContext *record;
    if (Cinema_IsSequenceInWindow() == 0) {
        return 0;
    }
    record = g_cinemaSequenceState;
    if ((record->spec.flags & 2) != 0) {
        return 1;
    }
    return 0;
}

int Cinema_GetActiveSettingOne(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    int cond = record->active != 0;
    if (cond) {
        if (record) {
            return record->spec.settings[1];
        } else {
            return record->spec.settings[1];
        }
    }
    return 0;
}

int Cinema_GetActiveSettingZero(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    int cond = record->active != 0;
    if (cond) {
        if (record) {
            return record->spec.settings[0];
        } else {
            return record->spec.settings[0];
        }
    }
    return 0;
}

void Cinema_SetLetterboxState(void *letterboxEnabled) {
    g_cinemaLetterboxEnabled = letterboxEnabled;
}

f32 Cinema_GetSequenceResponse(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    f32 response;

    if (record->active == 0) {
        return k_cinemaInactiveResponse_de;
    }
    response = record->response;
    if (!(k_cinemaResponseThreshold_de < response)) {
        return Track_EvaluateTrackScalar(record->time);
    }
    return response;
}

void Cinema_SetResponse(float responseValue) {
    g_cinemaSequenceState->response = responseValue;
}

void Cinema_ClearResponse(void) {
    g_cinemaSequenceState->response = 0.0f;
}

void Cinema_SetLoopMode(int loopMode) {
    g_cinemaSequenceState->loopBounds[0] = loopMode;
}

/** Copy a two-word record into the global record and clear two trailing fields. */
void Cinema_ResetViewport(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    int hi = g_hudReferenceViewportHeight;
    int lo = g_hudReferenceViewportWidth;
    record->loopBounds[2] = hi;
    record->loopBounds[1] = lo;
    record->loopBounds[3] = 0;
    record->loopBounds[4] = 0;
}

/** Store four incoming words into the global record's tail fields. */
void Cinema_SetViewport(int viewportWidth, int viewportHeight, int viewportLeft, int viewportTop) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    record->loopBounds[2] = viewportHeight;
    record->loopBounds[1] = viewportWidth;
    record->loopBounds[3] = viewportLeft;
    record->loopBounds[4] = viewportTop;
}

void Cinema_AddMessage(int goal) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    int idx = record->messageCount;
    XPlus_CopyString(record->messages[idx], goal);
    record = g_cinemaSequenceState;
    record->messageCount = record->messageCount + 1;
}

void Cinema_ClearMessageCount(void) {
    g_cinemaSequenceState->messageCount = 0;
}

float Cinema_GetScaledSequenceValue(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    return (record->spec.scaleA0) * (g_cinemaTrackScalarScale);
}

/** Return the word at offset 0xB0 of the current global object. */
unsigned int Cinema_GetSequenceProperty(void) {
    return g_cinemaSequenceState->spec.unknown48;
}

s32 Cinema_GetSequenceRequest(void) {
    return g_cinemaSequenceState->requestE0;
}

/* Returns the word at offset 0xE0 of the object g_cinemaSequenceState points to. The interval also holds an
   empty function with no symbol of its own, compiled here as the file-local stub after it. */

static void Cinema_NoOperation(void) {
}

void Cinema_ReleaseSequenceContext(void) {
    int owner = (s32)g_cinemaSequenceState->owner;
    Shared_MenuContext *record;
    if (owner != 0) {
        Cache_ReleaseResource(0, owner);
    }
    record = g_cinemaSequenceState;
    record->owner = 0;
    record->resource = 0;
    record->active = 0;
    record->state3C = 0;
    record->fadeRequested = 0;
}

/* 80243A80_10.CPP */
void Cinema_InitializeSequenceOnce(s32 unused) {
    Shared_MenuContext *record;
    Shared_MenuVoidCallback fn;

    record = g_cinemaSequenceState;
    if (record->initialized44 == 0) {
        fn = record->callback10;
        if (fn != 0) {
            record->callback10 = 0;
            fn();
        }
        record = g_cinemaSequenceState;
        record->initialized44 = 1;
    }
}

void Cinema_CloseSequenceOnce(void) {
    if (g_cinemaSequenceState->closed == 0) {
        {
            void *owner = g_cinemaSequenceState->owner;
            if (owner != 0) {
                Cache_ReleaseResource(0, owner);
            }
        }
        {
            void *record = g_cinemaSequenceState;
            FuncPtr fn = ((Shared_MenuContext *)(record))->onClose;

            ((Shared_MenuContext *)(record))->owner = 0;
            ((Shared_MenuContext *)(record))->resource = 0;
            ((Shared_MenuContext *)(record))->active = 0;
            ((Shared_MenuContext *)(record))->state3C = 0;
            ((Shared_MenuContext *)(record))->fadeRequested = 0;
            if (fn != 0) {
                ((Shared_MenuContext *)(record))->onClose = 0;
                fn();
            }
        }
        g_cinemaSequenceState->closed = 1;
    }
}

/* 80243A80_11.CPP */
extern f32 g_frameElapsedTime;

/** Read the word at offset 0x38 from the globally selected record. */

void Cinema_AdvanceSequenceTime(void) {
    f32 value;
    f32 limit;
    Shared_MenuContext *record;

    if (Cinema_IsSequenceActive() != 0) {
        if (Cinema_GetPlaybackPauseState() != 0) {
            g_cinemaSequenceState->time20 = g_cinemaSequenceState->time;
            return;
        }
        record = g_cinemaSequenceState;
        record->time20 = *(volatile f32 *)&record->time;
        record->time += g_frameElapsedTime * g_cinemaTimeScale;
        if (record->start <= record->time) {
            CCinema_EnterSequenceScene();
        }
        value = g_cinemaSequenceState->time;
        limit = g_cinemaSequenceState->clipEnd;
        if (limit <= value) {
            if (g_cinemaSequenceState->loopBounds[0] == 1) {
                g_cinemaSequenceState->time = value - limit;
                return;
            }
            g_cinemaSequenceState->time = limit;
            if (g_cinemaSequenceState->sequenceEndRequested != 0) {
                g_cinemaSequenceState->state3C = 1;
                g_cinemaSequenceState->sequenceEndRequested = 0;
            }
        }
    }
}

int Cinema_GetSequenceActiveState(void) {
    Shared_MenuContext *record = g_cinemaSequenceState;
    return record->active;
}

