#include "include_asm.h"
#include "types.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "../../include/libultra/io/pigetcmdq.h"

s32 osPiGetCmdQueue(void)
{
  int interruptMask;
  s32 *commandQueueAddress;
  interruptMask = (*((s32 *) (((s8 *) (&__osPiDevMgr)) + 0))) != 0;
  if (interruptMask)
  {
    if (commandQueueAddress)
    {
      commandQueueAddress = (s32 *) (((s8 *) (&__osPiDevMgr)) + 8);
      return *commandQueueAddress;
    }
    else
    {
      commandQueueAddress = (s32 *) (((s8 *) (&__osPiDevMgr)) + 8);
      return *commandQueueAddress;
    }
  }
  return 0;
}


