#ifndef AI_NAV_BEHAVIOR_CALLBACK_ROWS_H
#define AI_NAV_BEHAVIOR_CALLBACK_ROWS_H

#include "types.h"

/* Navigation behaviour tables for the German build, laid out in the order the ROM stores them. */
typedef struct NavBehaviorCallbackRowsLayout {
    u32 routeModeIds[47];             /* small route-mode identifiers, paired with zero separators */
    u32 compassDirectionBits[22];     /* unit direction components as float bit patterns */
    void *behaviorCallbackSlots[325]; /* per-behaviour callback rows; unused slots are null */
    u32 flankRowWords[118];           /* flank rows: two callbacks, flags and a float weight per row */
    u32 tailConstantWords[84];        /* trailing tuning constants, mixed integers and float bit patterns */
} NavBehaviorCallbackRowsLayout;

#endif
