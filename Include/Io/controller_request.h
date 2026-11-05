#ifndef IO_CONTROLLER_REQUEST_H
#define IO_CONTROLLER_REQUEST_H
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/runtime_declarations.h"
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
