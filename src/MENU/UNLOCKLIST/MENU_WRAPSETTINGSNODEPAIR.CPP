#include "COMMON/CHEATCODE.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "TYPES.H"

#if defined(VERSION_DE)
/* Calls SmpButton_WrapButtonWidget with 0x3D0 and then 0x3D1, and returns zero. */
s32 Menu_WrapSettingsNodePair(void) {
#if defined(VERSION_DE)
    SmpButton_WrapButtonWidget(970);
    SmpButton_WrapButtonWidget(971);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    SmpButton_WrapButtonWidget(976);
    SmpButton_WrapButtonWidget(977);
#elif defined(VERSION_EU_X)
    SmpButton_WrapButtonWidget(980);
    SmpButton_WrapButtonWidget(981);
#endif
    return 0;
}
#endif
