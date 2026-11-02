#include "COMMON/OBJRECAT20V1.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "include_asm.h"
#include "ENGINE/SETN64.H"

void SetN64_ClearFrameDirection(void *frame) {
    Frame *view = frame;
    view->direction.x = 0.0f;
    view->direction.y = 0.0f;
}

void SetN64_OnFrameComplete(void *schedule) {}


void SetN64_SetFrameDirection(void *frame, void *directionStorage) {
    Frame *view = frame;
    CVector3 *direction = directionStorage;
    view->direction = *direction;
    Graphu64_NormalizeVec3(&view->direction.x);
}

/** Copy four scalar fields from the source into output pointers. */
void SetN64_GetRecordOutputs(void *source, int *word, float *third, float *fourth, float *second) {
    RecordOutputFieldsView *source_record = source;
    *word = source_record->outputWord;
    *second = source_record->secondScalar;
    *third = source_record->thirdScalar;
    *fourth = source_record->fourthScalar;
}

#if defined(VERSION_US)
/** Perform no operation. */
void SetN64_EmptyFrameDirectionHookUs(void) {
}

/** Perform no operation. */
void SetN64_EmptyFrameDirectionHookSecondUs(void) {
}
#endif

#if defined(VERSION_EU)
/** Perform no operation. */
void SetN64_EmptyFrameDirectionHookEu(void) {
}

/** Perform no operation. */
void SetN64_EmptyFrameDirectionHookSecondEu(void) {
}
#endif
