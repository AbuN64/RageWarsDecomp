#include "TYPES.H"

extern char __osThreadTail[];

#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
struct {
    void * next;
    s32 priority;
} g_createmesgqueueRecord __attribute__((aligned(4))) = {
    0,
    -1
};
typedef char g_createmesgqueueRecordSizeCheck[(sizeof(g_createmesgqueueRecord) == 8) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * next;
    s32 priority;
} g_createmesgqueueRecord __attribute__((aligned(4))) = {
    0,
    -1
};
typedef char g_createmesgqueueRecordSizeCheck[(sizeof(g_createmesgqueueRecord) == 8) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * next;
    s32 priority;
} g_createmesgqueueRecord __attribute__((aligned(4))) = {
    0,
    -1
};
typedef char g_createmesgqueueRecordSizeCheck[(sizeof(g_createmesgqueueRecord) == 8) ? 1 : -1];
#endif
#endif
#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    void * next;
    s32 priority;
    void * runQueue;
} g_createmesgqueueRecord __attribute__((aligned(4))) = {
    0,
    -1,
    (void *)&g_createmesgqueueRecord
};
typedef char g_createmesgqueueRecordSizeCheck[(sizeof(g_createmesgqueueRecord) == 12) ? 1 : -1];
#endif
#endif
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
void * __osActiveQueue_CreatemesgqueueData[1] = {
    &g_createmesgqueueRecord,
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
#if defined(VERSION_US_REV1)
struct {
    void * next;
    s32 priority;
    void * runQueue;
    void * activeQueue;
} g_createmesgqueueDataConstantWords __attribute__((aligned(4))) = {
    0,
    -1,
    (void *)&__osThreadTail,
    (void *)&__osThreadTail
};
typedef char g_createmesgqueueDataConstantWordsSizeCheck[(sizeof(g_createmesgqueueDataConstantWords) == 16) ? 1 : -1];
#endif
#endif
