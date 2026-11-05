#ifndef COMMON_SCREENMESSAGESUBSTITUTION_H
#define COMMON_SCREENMESSAGESUBSTITUTION_H
#include "types.h"

/* When a posted screen message is the text Source points at, the text Replacement points at is shown instead. */
extern char g_screenMessageSubstitutionSource[];
extern void *g_screenMessageSubstitutionReplacement[];

#endif
