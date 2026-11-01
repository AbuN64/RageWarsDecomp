#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/REQUESTRECAT10.H"
#include "TYPES.H"

/* Scores the three entries (5, 10 or 20 points by kind for each active one, repeating the previous award for other kinds) and returns the first of five ranks whose threshold for the active-entry count reaches the score, 4 when none does, or zero with no active entry. */





extern InstanceHdr g_rewardScoreBudgets[];

static inline s32 entryScore(void) {
    s32 score;
    s32 points;
    s32 i;

    score = 0;
    points = 0;
    for (i = 0; i < 3; i++) {
        if (g_joinRequestEntries[i].id >= 0) {
            switch (g_joinRequestEntries[i].variant) {
            case 0:
                points = 5;
                break;
            case 1:
                points = 10;
                break;
            case 2:
                points = 20;
                break;
            }
            score += points;
        }
    }
    return score;
}


static inline s32 activeCount(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < 3; i++) {
        if (g_joinRequestEntries[i].id >= 0) {
            count++;
        }
    }
    return count;
}

s32 Join_GetJoinRequestRank(void) {
    s32 score;
    s32 i;
    s32 count;
    s32 rank;

    score = entryScore();
    count = activeCount();
    rank = 4;
    if (count <= 0) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (g_rewardScoreBudgets[i].w[count - 1] >= score) {
            rank = i;
            break;
        }
    }
    return rank;
}
