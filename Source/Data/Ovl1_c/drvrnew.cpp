#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Common/alfxparam.h"

/* DRVRNEW.CPP */
const RestBytes8 g_drvrnewStale = {
    { 63, 16, 0, 0, 0, 0, 0, 0 },
};

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US)
const float k_Drvrnew[2] = {
    6.5f, 0.0f,
};
#endif

#if defined(VERSION_EU)
float k_drvrnewFragment[2] = {
    1.0f, 1.7904929f,
};
#endif

#if defined(VERSION_DE)
char k_DrvrnewEncodedBytes[8] =
    "o/env.c\000";
#endif
