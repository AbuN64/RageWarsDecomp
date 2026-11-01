#ifndef RENDER_SEQUENCE_PROMPT_STATE_VIEWS_H
#define RENDER_SEQUENCE_PROMPT_STATE_VIEWS_H
#include "TYPES.H"
struct SequencePromptRequestView {
    char pad0[0x26DD4];
    s32 suppressPrompt;
};
struct Prompt {
    char pad[0x88];
    s32 opened;
};
struct SequencePromptStateView {
    char pad0[0x1284];
    Prompt prompt;
};
#endif
