#include "include_asm.h"

#if defined(VERSION_US_REV1)
#include "Ui/Tsmos/TSMOS.h"
void *g_overlaysNineConstantsConstantWords[3] = {
    (void *)&g_Level_GetScreenEventTableAddress[484], (void *)&g_Level_GetScreenEventTableAddress[468],
    (void *)&g_Level_GetScreenEventTableAddress[516],
};
#endif
