#ifndef COMMON_PLAYER_JOIN_REQUESTS_H
#define COMMON_PLAYER_JOIN_REQUESTS_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Join/join_cyclejoinrequestrank.h"
struct RequestDrawPair;
extern s32 Join_CountOpenPlayerSlots(void);

struct PlayerFrontendCountOpenPlayerSlots;
typedef struct PlayerFrontendCountOpenPlayerSlots PlayerFrontendCountOpenPlayerSlots;


extern s32 Key_FindKeyIndex(s32 key);

extern void Join_SeatJoinRequests(void);


extern s32 Join_ScoreJoinRequestEntries(void);

struct PlayerJoinRequestEntry;
struct PlayerJoinRequestEntry {
    s32 id;
    s32 variant;
    s32 word8;
    s32 variantC;
    char name[28 - 0x10];
};
/* g_joinRequestEntries: the three join requests the request menus edit and Join_SeatJoinRequests seats. */
extern struct PlayerJoinRequestEntry g_joinRequestEntries[3];





typedef struct RequestDrawScreen {
    char pad0[8];
    void *roots[3];
    s32 selected;
    s32 timer;
    s32 count;
} RequestDrawScreen;
typedef struct RequestDrawPair { s32 first, second; } RequestDrawPair;
extern s32 Join_FindJoinModelIndex(s32, s32);
extern struct RequestDrawPair g_joinRequestDrawPairs[];

struct CourseOptionsScreen {
    void *handle;        /* +0x00 the course-tree handle this screen was built for */
    s32 mode;            /* +0x04 what SmpOverlay_CreateOverlayNode_Slot reports for that handle */
    void *rows[3];       /* +0x08 the three option rows, addressed as block + (row << 2) + 8 */
    s32 selection;       /* +0x14 the row a join request edits */
    s32 timer;           /* +0x18 */
    s32 step;            /* +0x1C */
};
extern struct CourseOptionsScreen *g_courseOptionsScreen;
extern s32 Menu_GetPreviousScreenOwner(s32);
extern void Join_UpdateJoinRequestDisplay(s32);
#endif
