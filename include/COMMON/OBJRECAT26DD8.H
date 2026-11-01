#ifndef COMMON_OBJRECAT26DD8_H
#define COMMON_OBJRECAT26DD8_H
#include "TYPES.H"
/* Independent simulation-time scale, adjacent to the current time step. */
extern f32 g_roundTimerStep;
#include "COMMON/ITEMRECAT20V1.H"

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
