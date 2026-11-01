#ifndef COMMON_OBJRECAT20V1_H
#define COMMON_OBJRECAT20V1_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"


struct RecordOutputFieldsView;
typedef struct RecordOutputFieldsView RecordOutputFieldsView;



extern void SetN64_SetFrameDirection(void *frame, void *direction);


struct RecordOutputFieldsView;

extern void SetN64_OnFrameComplete(void *schedule);

extern void SetN64_ClearFrameDirection(void *frame);


#endif
