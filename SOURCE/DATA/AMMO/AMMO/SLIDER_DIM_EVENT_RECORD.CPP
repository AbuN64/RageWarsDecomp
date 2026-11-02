#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_SmpSlider_DimSliderItemsAddress[];

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E2394 */
extern char g_SmpSlider_DimSliderItemsAddress[];
RestsliderDimEventRecordUsRev1Layout18 g_sliderDimEventRecordUsRev1 = {
    30000,
    (void *)&g_SmpSlider_DimSliderItemsAddress,
    15,
};
#endif
