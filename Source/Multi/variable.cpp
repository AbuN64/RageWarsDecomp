#include "Common/player_item_inventory.h"
#include "Multi/initial.h"
#include "Common/resident_event_handler.h"
#include "Common/shared_debugfield.h"
#include "Common/shared_menuselection.h"
#include "../../sdk/include/AUDIO/sprintf.H"
#include "include_asm.h"

/* Read the descriptor's runtime value type and format the scaled value. */
char *Multi_FormatTypedMenuVariable(Shared_DebugWidget *widget) {
    Shared_DebugField *field = widget->field;
    void *value = field->get();
    f32 number;
    switch (field->type) {
    default: number = 0.0f; break;
    case 0: { f32 *p = value; number = *p; break; }
    case 3: { s8 *p = value; number = *p; break; }
    case 4: { s16 *p = value; number = *p; break; }
    case 1:
    case 2:
    case 5: { s32 *p = value; number = *p; break; }
    case 6: { u8 *p = value; number = *p; break; }
    case 7: { u16 *p = value; number = *p; break; }
    case 8: { u32 *p = value; number = (f64)*p; break; }
    }
    number /= field->scale;
    Libc_FormatString(g_debugVariableValueBuffer, g_debugVariableValueFormat, (f64)number);
    if (field->name != 0) {
        Libc_FormatString(g_debugVariableLabelBuffer, g_debugVariableNamedFormat, field->name, g_debugVariableValueBuffer);
    } else {
        Libc_FormatString(g_debugVariableLabelBuffer, g_debugVariableUnnamedFormat, g_debugVariableValueBuffer);
    }
    return g_debugVariableLabelBuffer;
}

s32 Multi_AdjustTypedMenuVariable(TypedMenuVariableView *widget, Shared_MenuInput *menuInput) {
    void *writeValue;
    void *readValue;
    f32 unusedFloatValue;
    f32 unusedFloatResult;
    f32 adjustedValue;
    f64 unusedDoubleValue;
    s32 unusedComparison;
    u32 readValueType;
    u32 writeValueType;
    struct Variable *readDescriptor;
    struct Variable *writeDescriptor;

    readDescriptor = widget->variable;
    readValue = readDescriptor->accessor();
    readValueType = readDescriptor->valueType;
    switch (readValueType) {
    default:
        adjustedValue = 0.0f;
        break;
    case 0:
        adjustedValue = *(float *)readValue;
        break;
    case 3:
        adjustedValue = (f32) *(signed char *)readValue;
        break;
    case 4:
        adjustedValue = (f32) *(short *)readValue;
        break;
    case 1:
    case 2:
    case 5:
        adjustedValue = (f32) *(int *)readValue;
        break;
    case 6:
        adjustedValue = (f32) *(unsigned char *)readValue;
        break;
    case 7:
        adjustedValue = (f32) *(unsigned short *)readValue;
        break;
    case 8:
        adjustedValue = (float)*(unsigned int *)readValue;
        break;
    }
    if (((s32 (*)(s32))Control_IsLeftPressed)(menuInput->buttons) != 0) {
        adjustedValue -= readDescriptor->step;
        if (adjustedValue < readDescriptor->minimum) adjustedValue = readDescriptor->minimum;
    } else if (((s32 (*)(s32))Control_IsRightPressed)(menuInput->buttons) != 0) {
        adjustedValue += readDescriptor->step;
        if (adjustedValue > readDescriptor->maximum) adjustedValue = readDescriptor->maximum;
    }
    writeDescriptor = widget->variable;
    writeValue = writeDescriptor->accessor(widget);
    writeValueType = writeDescriptor->valueType;
    switch (writeValueType) {
    case 0: *(float *)writeValue = adjustedValue; break;
    case 3: *(signed char *)writeValue = (int)adjustedValue; break;
    case 4: *(short *)writeValue = (int)adjustedValue; break;
    case 1: case 2: case 5: *(int *)writeValue = adjustedValue; break;
    case 6: *(unsigned char *)writeValue = (unsigned int)adjustedValue; break;
    case 7: *(unsigned short *)writeValue = (unsigned int)adjustedValue; break;
    case 8: *(unsigned int *)writeValue = adjustedValue; break;
    }
    return 0;
}

/* printf format for the numeric value of a typed menu variable, formatted in MULTI_ADJUSTTYPEDMENUVARIABLE.CPP. */
extern const char g_debugVariableValueFormat[];

/* "%s" format for an unnamed typed menu variable, formatted in MULTI_ADJUSTTYPEDMENUVARIABLE.CPP. */
#if defined(VERSION_DE) || defined(VERSION_EU_X)
extern const char g_debugVariableUnnamedFormat[];
#endif
#if defined(VERSION_EU) || defined(VERSION_US)
extern const char g_debugVariableUnnamedFormat[4];
#endif

#if defined(VERSION_US_REV1)
extern const char g_debugVariableUnnamedFormat[];
#endif

/* Retained data for this translation unit. */

const char g_debugVariableValueFormat[] = "%3.2f";
#if defined(VERSION_DE) || defined(VERSION_EU_X)
const char g_debugVariableUnnamedFormat[] = "%s";
#endif
#if defined(VERSION_EU) || defined(VERSION_US)
const char g_debugVariableUnnamedFormat[4] = "%s";
#endif
#if defined(VERSION_US_REV1)
const char g_debugVariableUnnamedFormat[] = "%s";
#endif
