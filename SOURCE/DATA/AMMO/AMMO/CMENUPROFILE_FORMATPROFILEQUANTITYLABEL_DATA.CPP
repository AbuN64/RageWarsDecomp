#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"

/* 800E2320.CPP */
#if defined(VERSION_US)
const char s_CmenuprofileFormatprofilequantitylabelEquEosRText[12] =
    "equ\004.eosR\000\000\000";
#endif
#if defined(VERSION_DE)
/* Stale "%3d" format text bytes; no instruction reads it. */
const RestBytes12 g_profileQuantityStaleFormatText = {
    { 0, 0, 0, 0, 37, 51, 100, 0, 0, 0, 0, 0 },
};
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_profileQuantityTwoDigitFormat_CmenuprofileFormatprofilequantitylabelData.c */
const char g_profileQuantityTwoDigitFormat[5] = "%02d";
#endif

/* 800E9AF4.CPP */
