#ifndef IO_CONTROLLER_REQUEST_H
#define IO_CONTROLLER_REQUEST_H
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/ITEMRECAT20V1.H"
/* Queue protocol used by the controller filesystem wrappers. */
typedef struct ControllerRequest {
    u32 header;
    u32 status;
    u32 reserved;
    u32 command;
    s32 argument0;
    u32 argument1;
    s32 argument2;
    OSMesgQueue *reply;
} ControllerRequest;

typedef union ControllerResponse {
    void *message;
    s32 status;
} ControllerResponse;
#endif
