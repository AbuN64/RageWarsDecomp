#include "DATA/REST_SOURCE_RECORDS.H"
#include "../../../sdk/include/libultra/ACTOR_STATE_TABLE_END_DATA.H"
extern char g_actorStateEnd_us_rev1[];

#if defined(VERSION_US_REV1)
extern RestminigunTextLayout331 g_minigunText;
#endif
extern char g_overlayThreeActorStateEndFragment1[];
extern char g_overlayThreeActorStateEndFragment2[];
extern char g_overlayThreeActorStateEndFragment3[];
extern char g_overlayThreeActorStateEndFragment4[];
extern char g_overlayThreeActorStateEndFragment5[];
#include "include_asm.h"
#if defined(VERSION_US_REV1)

/* bytes live in the preceding array */

/* g_minigunText_GMiniguntext.CPP */
RestminigunTextLayout331 g_minigunText = {
    { 0, 0 },
    { (void *)&g_minigunText, (void *)&g_minigunText, (void *)((char *)&g_actorStateEnd_us_rev1 + 40), (void *)((char *)&g_overlayThreeActorStateEndFragment3 + 40), (void *)((char *)&g_actorStateTableEndWords + 40), (void *)&g_minigunText, (void *)((char *)&g_overlayThreeActorStateEndFragment1 + 40), (void *)((char *)&g_overlayThreeActorStateEndFragment2 + 40), (void *)&g_minigunText, (void *)((char *)&g_overlayThreeActorStateEndFragment4 + 40), (void *)((char *)&g_overlayThreeActorStateEndFragment5 + 40), (void *)&g_minigunText, (void *)&g_minigunText, (void *)&g_minigunText, (void *)&g_minigunText },
    "E\000\000\000MINIGUN\000",
    1.0f,
};
#endif
