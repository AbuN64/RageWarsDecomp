#if defined(VERSION_US_REV1)

#include "Data/rest_source_records.h"


#include "include_asm.h"


#include "Data/Ammo/slider_dim_event_record.h"


SliderDimEventRecordUsRev1Layout g_sliderDimEventRecordUsRevision = {
    30000,
    (void *)&g_SmpSlider_DimSliderItemsAddress,
    15,
};
#endif
