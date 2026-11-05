#ifndef DATA_ENEMY_CURVE_DECODETHREEBITSAMPLES_DATA_H
#define DATA_ENEMY_CURVE_DECODETHREEBITSAMPLES_DATA_H
#include "Data/rest_source_records.h"
extern char g_threadLabelWordsEuropean[];
extern char g_threadLabelWordsEuropeanX[];
extern char g_threadLabelWordsGerman[];
extern char g_threadLabelWordsUs[];
extern char g_threadLabelWordsUsRevision[];
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char g_threadLabelWordsGerman[];
#endif
#endif
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_EU)
extern char g_threadLabelWordsEuropean[];
#endif
#endif
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_EU_X)
extern char g_threadLabelWordsEuropeanX[];
#endif
#endif
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_US)
extern char g_threadLabelWordsUs[];
#endif
#endif
#endif
