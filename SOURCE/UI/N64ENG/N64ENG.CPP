#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/GFX_INITIALIZEFRONTENDSERVICES.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/RECORD.H"
#include "COMMON/TEXTURE.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"
#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "include_asm.h"

extern struct Record *Cache_AllocateMemory(s32 size);


void N64Eng_SetNumericWidgetValue(RecordN64EngCreateNumericWidget *widget, s32 value);


extern void Node_ReplaceNodeRefs(struct WidgetReferenceNodeView *node, void *from, void *to);

RecordN64EngCreateNumericWidget *N64Eng_CreateNumericWidget(s32 sourceResourceId, s32 childResourceId, s32 minimumValue, s32 maximumValue, s32 wrapEnabled) {
    RecordN64EngCreateNumericWidget *source;
    s32 context;
    RecordN64EngCreateNumericWidget *result;
    RecordN64EngCreateNumericWidget *child;

    source = Node_FindWidgetByResourceId(Node_GetScreenData(GetMenuScreenOwner()), sourceResourceId & 0xFFFF);
    context = Node_GetScreenData(GetMenuScreenOwner());
    result = Cache_AllocateMemory(108);
    XPlus_FillBytes(result, 0, 108);
    *(Header44 *)result = *(Header44 *)source;
    result->classId = 2917;
    *(InstanceHdr *)&result->fields_2C = *(InstanceHdr *)&source->fields_2C;
    child = Node_FindWidgetByResourceId((void*)context, childResourceId & 0xFFFF);
    result->childWidget = child;
    child->fields_2C[3] = (intptr_t)&result->valueText;
    result->maximumValue = maximumValue;
    result->minimumValue = minimumValue;
    result->value = 0;
    result->repeatCount = 0;
    result->wrapEnabled = wrapEnabled;
    N64Eng_SetNumericWidgetValue(result, minimumValue);
    result->stepState = 2;
    Node_WrapNodeInParent(source, result);
    source->replacedMarker = -1;
    Node_ReplaceNodeRefs(context, source, result);
    return result;
}

/** Return the word at offset 0x58 in the supplied object. */
int N64Eng_GetNumericWidgetValue(void *object) {
    RecordN64EngCreateNumericWidget *record = object;
    return record->value;
}

extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);

/* Format the stream count into its existing inline state buffer. */
void N64Eng_SetNumericWidgetValue(RecordN64EngCreateNumericWidget *widget, s32 value) {
    widget->value = value;
    XStdio_FormatBuffer(widget->valueText, g_numericWidgetValueFormat, value);
}

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char g_numericWidgetValueFormat_N64eng[4] =
    "%d\000D";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const unsigned char g_numericWidgetValueFormat_N64eng[3] = {
    0x25, 0x64, 0x00,
};
#endif
#endif

#if defined(VERSION_US)
unsigned char k_N64engEncodedBytesBlock1[13] = {
    0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x73, 0x5F, 0x43, 0x43,
};
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU_X)
char s_NEngWEPURLINText[13] =
    "WE - PURLIN\000\000";
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
unsigned char k_N64engEncodedBytesBlock2[13] = {
    0x08, 0x27, 0xBD, 0x00, 0x18, 0x44, 0x00, 0x00, 0x00, 0xBF, 0x80, 0x00, 0x00,
};
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_numericWidgetValueFormat_N64eng.c */
const char k_N64engEncodedBytes[4] =
    "%d\000R";
#endif
