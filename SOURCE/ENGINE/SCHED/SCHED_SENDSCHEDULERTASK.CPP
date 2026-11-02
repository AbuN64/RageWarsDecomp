#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/RESULTS.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

void Sched_SendSchedulerTask(s32 schedulerAddress, s32 taskMessage) {
    osSendMesg((char *)&((OSSched *)schedulerAddress)->cmdQ, taskMessage, 1);
    osSendMesg((char *)&((OSSched *)schedulerAddress)->interruptQ, 6, 1);
}
