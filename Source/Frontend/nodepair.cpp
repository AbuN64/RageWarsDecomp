#include "Common/menu_overlay.h"
#include "Common/menu_model_preview.h"
#include "types.h"
#include "include_asm.h"

/* unit NODEPAIR.CPP */
#if defined(VERSION_US_REV1)
s32 Frontend_WrapNodePairUsRev1(void) {
    SmpButton_WrapButtonWidget(986);
    SmpButton_WrapButtonWidget(987);
    return 0;
}
#endif

#if defined(VERSION_US)

int Frontend_WrapNodePairUs(void) { SmpButton_WrapButtonWidget(986); SmpButton_WrapButtonWidget(987); return 0; }
#endif

#if defined(VERSION_EU)

int Frontend_WrapNodePairEuropean(void) {
    SmpButton_WrapButtonWidget(986);
    SmpButton_WrapButtonWidget(987);
    return 0;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_EU_X)

int Frontend_WrapNodePairGerman(void) {
    SmpButton_WrapButtonWidget(980);
    SmpButton_WrapButtonWidget(981);
    return 0;
}
#endif
