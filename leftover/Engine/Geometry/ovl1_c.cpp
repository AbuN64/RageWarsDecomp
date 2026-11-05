#include "Data/rest_source_records.h"
#include "types.h"
#ifdef VERSION_DE

float g_overlayOneCFloatConstants[4] = {
    0.0f, 0.0f, 0.0f, 1.5707964f,
};
#endif
#ifdef VERSION_EU
OverlayOneCFloatConstantWordsLayout g_overlayOneCFloatConstants = {
    { 0, 0, 2814880, 2814880 },
};
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
float g_overlayOneCFloatConstants[4] = {
    0.0f, 0.0f, 0.08846038f, 0.07660268f,
};
#endif
#ifdef VERSION_US
char g_overlayOneCFloatConstants[16] = "\000\000\000\000\000\000\000\000MPACT_FL";
#endif
