#include "Common/rotation_extraction.h"
#include "Common/gfx_initializefrontendservices.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Menu/widget_records.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/menu_screen_elements.h"
#include "Common/record.h"
#include "Common/texture.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/widget_tree.h"
#include "include_asm.h"
#include "Common/selectionscreenstate.h"
#include "Ui/X_files/x_stdio.h"

void N64Eng_SetNumericWidgetValue(RecordN64EngCreateNumericWidget *widget, s32 value);

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

/** Return the current value of a numeric widget. */
int N64Eng_GetNumericWidgetValue(void *object) {
    RecordN64EngCreateNumericWidget *record = object;
    return record->value;
}

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
const unsigned char g_numericWidgetValueFormat_N64eng[] = {
    0x25, 0x64, 0x00,
#if defined(VERSION_US)
    /* Retained suffix 800C5CC3..800C5CD0 in the same object. */
    0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x73, 0x5F, 0x43, 0x43,
#endif
#if defined(VERSION_EU)
    /* Retained suffix 800C6033..800C6040 in the same object. */
    0x08, 0x27, 0xBD, 0x00, 0x18, 0x44, 0x00, 0x00, 0x00, 0xBF, 0x80, 0x00, 0x00,
#endif
};
#endif
#endif

#if defined(VERSION_EU_X)
char s_NEngWEPURLINText[13] =
    "WE - PURLIN\000\000";
#endif

#if defined(VERSION_US_REV1)
const char k_N64engData[4] =
    "%d\000R";
#endif
