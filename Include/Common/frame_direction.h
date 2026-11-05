#ifndef COMMON_FRAME_DIRECTION_H
#define COMMON_FRAME_DIRECTION_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/vector.h"


struct Frame;
struct RecordOutputFieldsView;
typedef struct RecordOutputFieldsView RecordOutputFieldsView;



extern void SetN64_SetFrameDirection(struct Frame *frame, CVector3 *directionStorage);


struct RecordOutputFieldsView;

extern void SetN64_OnFrameComplete(void *schedule);

extern void SetN64_ClearFrameDirection(struct Frame *frame);


#endif
