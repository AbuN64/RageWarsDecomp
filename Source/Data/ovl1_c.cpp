#include "Common/alfxparam.h"
#include "Data/Ovl1_c/env.h"
#include "Data/rest_source_records.h"
#include "include_asm.h"

/* ENV.CPP */
const char s_audioEnvText[12] = "audio/env.c";

/* COSF.CPP */
#if defined(VERSION_US_REV1)
RestTrigConstantPool624 g_Cosf = { 0, { 5, 5 }, 1.0 };
#endif
