#ifndef COMMON_RECORD_H
#define COMMON_RECORD_H
#include "TYPES.H"
#include "COMMON/FRUSTUM.H"
struct Tree;



extern int g_frameHeapLowCursor;






struct RecordN64EngCreateNumericWidget;
typedef struct RecordN64EngCreateNumericWidget RecordN64EngCreateNumericWidget;

extern int g_frameHeapLowMarks[16];


extern int g_n64UiFrameCounter;

struct RecordN64EngCreateNumericWidget;
struct RecordN64EngCreateNumericWidget {
    s32 words_00[3];
    s16 replacedMarker;
    s16 classId;
    s32 words_10[7];
    s32 fields_2C[5];
    s32 reservedWord;
    struct RecordN64EngCreateNumericWidget *childWidget;
    s32 repeatCount;
    s32 maximumValue;
    s32 minimumValue;
    s32 wrapEnabled;
    s32 value;
    s32 stepState;
    s32 valueText[3];
};








extern const char g_numericWidgetValueFormat[];
#endif
