#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "include_asm.h"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "FRONTEND/JOIN_RANDOMIZEJOINREQUESTENTRIES.H"
#include "COMMON/SHARED_GAMESLOT.H"

void Join_RandomizeJoinRequestEntries(s32 count, s32 level) {
    Shared_Game *game;
    char *name;
    s32 points[3];
    s32 *p;
    s32 budget;
    s32 i;
    s32 *entry;
    s32 tier;
    s32 value;
    s32 pick;
    s32 last;

    if (count <= 0) {
        return;
    }
    for (i = 2, p = points + i; i >= 0; i--) {
        *p-- = 0;
    }
    last = count - 1;
    if (count <= 0) {
        budget = 0;
    } else {
        budget = g_rewardScoreBudgets[level * 5 + last];
    }
    for (i = 0; i < count; i++) {
        points[i] = 5;
        budget -= 5;
    }
    i = 0;
    while (budget > 0) {
        entry = &points[Graphu64_NextRandom() % count];
        value = *entry;
        if (value < 20 && budget >= value) {
            *entry = value * 2;
            budget -= value;
        }
        if (++i >= 10001) {
            break;
        }
    }
    for (i = 0; i < count; i++) {
        tier = points[i] / 10;
        g_joinRequestEntries[i].word8 = 4;
        g_joinRequestEntries[i].variant = tier;
        g_joinRequestEntries[i].variantC = tier;
        do {
            pick = Graphu64_NextRandom() % 17;
            g_joinRequestEntries[i].id = g_rewardItemTiers[tier][pick].first;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            name = g_joinRequestEntries[i].name;
            game = &g_gameSettings;
            XPlus_CopyString(name, ((char **)g_rewardItemTiers[tier][pick].second)[game->language]);
#else
            XPlus_CopyString(g_joinRequestEntries[i].name, *(char **)g_rewardItemTiers[tier][pick].second);
#endif
        } while (g_joinRequestEntries[i].id == -1);
    }
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Deals out random rewards for count entries at difficulty level: starts every entry at 5 points
   from the level's budget in g_rewardScoreBudgets, then for up to 10001 random picks doubles an entry below
   20 points while the budget covers it; each entry then records mode 4 and its tier (points / 10)
   in g_joinRequestEntries's 0x1C-byte records and draws random tier items from the seventeen per tier in
   g_rewardItemTiers, copying the item's name, until it gets one that exists. */
#include "TYPES.H"

typedef struct {
    s32 id;
    char **name;
} Prize;

typedef struct {
    s32 id;
    s32 tier;
    s32 mode;
    s32 shown;
    char name[12];
} Reward;

extern s32 g_rewardScoreBudgets[];
extern Prize g_rewardItemTiers[][17];
extern Reward g_joinRequestEntries[];

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

void Join_RandomizeJoinRequestEntries(s32 count, s32 level) {
    s32 points[3];
    s32 *p;
    s32 budget;
    s32 i;
    s32 *entry;
    s32 tier;
    s32 value;
    s32 pick;
    s32 last;

    if (count <= 0) {
        return;
    }
    for (i = 2, p = points + i; i >= 0; i--) {
        *p-- = 0;
    }
    last = count - 1;
    if (count <= 0) {
        budget = 0;
    } else {
        budget = g_rewardScoreBudgets[level * 5 + last];
    }
    for (i = 0; i < count; i++) {
        points[i] = 5;
        budget -= 5;
    }
    i = 0;
    while (budget > 0) {
        entry = &points[Graphu64_NextRandom() % count];
        value = *entry;
        if (value < 20 && budget >= value) {
            *entry = value * 2;
            budget -= value;
        }
        if (++i >= 10001) {
            break;
        }
    }
    for (i = 0; i < count; i++) {
        tier = points[i] / 10;
        g_joinRequestEntries[i].mode = 4;
        g_joinRequestEntries[i].tier = tier;
        g_joinRequestEntries[i].shown = tier;
        do {
            pick = Graphu64_NextRandom() % 17;
            g_joinRequestEntries[i].id = g_rewardItemTiers[tier][pick].id;
            XPlus_CopyString(g_joinRequestEntries[i].name, *g_rewardItemTiers[tier][pick].name);
        } while (g_joinRequestEntries[i].id == -1);
    }
}
#endif
