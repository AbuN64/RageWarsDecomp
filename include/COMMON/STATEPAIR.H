#ifndef COMMON_STATEPAIR_H
#define COMMON_STATEPAIR_H
#include "TYPES.H"
#include "COMMON/SELECTIONSCREENSTATE.H"

struct StatePair;
typedef struct StatePair StatePair;
extern StatePair g_frontendTimerState;





extern int g_frontendTransitionCountdown;















struct StatePair;











/* Shared object layout established by command-list consumers. */
struct LinkedCommandEntry {
    u8 padding000[4];
    struct LinkedCommandEntry *next; /* 0x04 */
    u8 padding008[6];
    u16 kind; /* 0x0E */
    u8 command; /* 0x10, consumers only store this byte */
};
struct CommandListMenu {
    u8 padding000[8];
    struct LinkedCommandEntry *entries; /* 0x08 */
    u8 padding00C[0x48];
    s32 state; /* 0x54 */
};


struct Widget;
void Tsmos_ScaleWidgetTree(struct Widget *, struct Widget *);

extern void Stage_StartConfiguredMatch(void);
#endif
