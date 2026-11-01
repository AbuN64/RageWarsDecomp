#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#include "DATA/OVL1_I/SMPOVERLAY_DISPATCHPAKDIALOGEVENT_DATA.H"
#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
RestpakDialogEventHandlerRecordsUsRecord458 g_pakDialogEventHandlerRecordsUs = {
    3592,
    29,
    (unsigned int)g_SmpOverlay_TickPakDialogAddress,
    3590,
    29,
    (unsigned int)g_SmpOverlay_CreatePakDialogAddress,
    3587,
    29,
    (unsigned int)g_SmpOverlay_DestroyPakDialogAddress,
    1,
    29,
    (unsigned int)g_SmpOverlay_HandlePakDialogChoiceAddress,
    2,
    29,
    (unsigned int)g_SmpOverlay_ConsumePakDialogEventAddress,
    10,
    29,
    (unsigned int)g_SmpOverlay_ReturnUnhandledPakDialogEventAddress,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif
