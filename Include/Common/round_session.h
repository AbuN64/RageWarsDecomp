#ifndef COMMON_ROUND_SESSION_H
#define COMMON_ROUND_SESSION_H
#include "types.h"
/* Independent simulation-time scale, adjacent to the current time step. */
extern f32 g_roundTimerStep;
#include "Common/runtime_declarations.h"

struct SessionInitializeHandler;
struct RoundSessionItemStateView;
typedef struct RoundSessionItemStateView RoundSessionItemStateView;

struct SessionInitializeHandler {
    void (*callback)(void *sessionContext);
    s32 reservedWordFirst;
    s32 reservedWordSecond;
};

struct SessionInitializeHandler;
typedef struct SessionInitializeHandler SessionInitializeHandler;



struct SequencePromptStateView;
typedef struct SequencePromptStateView SequencePromptStateView;


struct Prompt;
typedef struct Prompt Prompt;

struct Prompt;

struct SequencePromptStateView;





extern float g_creditsInitialLineTimer;












extern float g_creditsLineTimer;







#endif
