#ifndef COMMON_TRIGGER_AND_FLOAT_VALUE_OPERATIONS_H
#define COMMON_TRIGGER_AND_FLOAT_VALUE_OPERATIONS_H
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON.H"


struct Trigger;
extern void Link_DispatchTrigger(struct Trigger *);
#if defined(VERSION_EU)
#else
#endif
static inline f32 recordValue(s32 id) {
#if defined(VERSION_EU)
    return Menu_ExpandFloatHighWord(id);
#else
    return Menu_ExpandFloatHighWord(id);
#endif
}

#endif
