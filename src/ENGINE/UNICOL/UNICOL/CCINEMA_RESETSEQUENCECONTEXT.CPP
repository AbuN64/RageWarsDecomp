#include "COMMON/GROUP.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "TYPES.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "CAMERA/CCINEMA_RESETSEQUENCECONTEXT.H"

/* Zeroes the resident game-state block, sets its four persistent-slot markers to -1, then runs the two state-machine resets that depend on it. */






void CCinema_ResetSequenceContext(void)
{
    Shared_MenuContext *p = g_cinemaSequenceState;

    p->owner = 0;
    p->resource = 0;
    p->unknown08 = 0;
    p->onClose = 0;
    p->callback10 = 0;
    p->reservedWord1 = 0;
    p->target = 0;
    p->time = 0;
    p->time20 = 0;
    p->time24 = 0;
    p->clipStart = 0;
    p->clipEnd = 0;
    p->start = 0;
    p->end = 0;
    p->active = 0;
    p->state3C = 0;
    p->sequenceStarted = 0;
    p->initialized44 = 0;
    p->closed = 0;
    p->pendingStartFlag = 0;
    p->sequenceAdvanceRequested = 0;
    p->pending = 0;
    p->pendingTrackId = 0;
    p->noPendingTrackRequests = 0;
    p->fadeRequested = 0;
    p->fade = 0;
    p->sequenceEndRequested = 0;
    p->mode = 0;
    p->reservedElements[0] = -1;
    p->reservedElements[1] = -1;
    p->reservedElements[2] = 0;
    p->reservedElements[3] = 0;
    p->reservedElements[4] = 0;
    p->reservedElements[5] = 0;
    p->reservedElements[6] = 0;
    p->targetD8 = -1;
    p->resourceDC = -1;
    p->requestE0 = -1;
    p->callbackE4 = 0;
    p->callbackE8 = 0;
    p->reservedWord2 = 0;
    p->position.x = 0;
    p->position.y = 0;
    p->position.z = 0;
    p->yaw = 0;
    p->response = 0;
    p->loopBounds[0] = 0;

    Cinema_ResetViewport();
    Cinema_ClearMessageCount();
}
