#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/REQUESTRECAT10.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* 8040C640_6.CPP */
#if defined(VERSION_US)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
extern ResidentEventHandlerEntry g_joinOptionsEventHandlers[];

s32 Frontend_DispatchUsJoinOptionsEvent(ActorDefinitionHeader *actor, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    s32 index;
    index = 0;
    if (g_joinOptionsEventHandlers[index].handler != 0) {
        do {
            if (g_joinOptionsEventHandlers[index].event == event) {
                if (g_joinOptionsEventHandlers[index].actorKind == actor->character || g_joinOptionsEventHandlers[index].actorKind == 30000) {
                    return g_joinOptionsEventHandlers[index].handler(actor, event, eventData, eventValue, eventContext);
                }
            }
            index++;
        } while (g_joinOptionsEventHandlers[index].handler != 0);
    }
    return 0;
}
#endif


/* 8041DF04_5.CPP */
#if !(defined(VERSION_US))

/* Steps the model of the join request the screen g_courseOptionsScreen edits (index at 0x14) back on event 1
   unless Menu_GetPreviousScreenOwner reports 0x16: calls MarkMenuEventHandled, finds the request's place in the 3 by 17
   model table g_rewardItemTiers through Join_FindJoinModelIndex, walks back through its variants and, before the
   first, to the last variant of the previous model (wrapping to the last), skipping entries whose
   id is -1, then stores the variant at 0x4 and 0xC and the id at 0x0 of the 28-byte request in
   g_joinRequestEntries, copies the name of the entry the found id selects in that variant row to 0x10, redraws through Join_UpdateJoinRequestDisplay and plays sound
   0xE81. Returns zero. */

extern struct TextEntry g_rewardItemTiers[][17];
extern void MarkMenuEventHandled();
extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

s32 Frontend_SelectPreviousJoinModel(void *unused0, void *unused1, void *unused2, s32 event) {
    s32 variant;
    s32 model;
    s32 id;

    if (event != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        return 0;
    }
    variant = g_joinRequestEntries[g_courseOptionsScreen->selection].variant;
    model = Join_FindJoinModelIndex(variant, g_joinRequestEntries[g_courseOptionsScreen->selection].id);
    do {
        variant--;
        if (variant < 0) {
            variant = 2;
            model--;
            if (model < 0) {
                model = 16;
            }
        }
        id = g_rewardItemTiers[variant][model].id;
    } while (id == -1);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variant = variant;
    g_joinRequestEntries[g_courseOptionsScreen->selection].id = id;
    XPlus_CopyString(g_joinRequestEntries[g_courseOptionsScreen->selection].name,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        g_rewardItemTiers[variant][id].text[g_languageIndex]
#else
        *g_rewardItemTiers[variant][id].text
#endif
    );
    g_joinRequestEntries[g_courseOptionsScreen->selection].variantC = variant;
    Join_UpdateJoinRequestDisplay(g_courseOptionsScreen->selection);
    SoundElement_PlayFlatSound(3713);
    return 0;
}


/* Steps the model of the join request the screen g_courseOptionsScreen edits (index at 0x14) forward on event 1
   unless Menu_GetPreviousScreenOwner reports 0x16: calls MarkMenuEventHandled, finds the request's place in the 3 by 17
   model table g_rewardItemTiers through Join_FindJoinModelIndex, walks forward through its variants and, past the
   last, to the first variant of the next model (wrapping to the first), skipping entries whose
   id is -1, then stores the variant at 0x4 and 0xC and the id at 0x0 of the 28-byte request in
   g_joinRequestEntries, copies the name of the entry the found id selects in that variant row to 0x10, redraws through Join_UpdateJoinRequestDisplay and plays sound
   0xE81. Returns zero. Adapted from Frontend_SelectPreviousJoinModel with the walk direction reversed. */

s32 Frontend_SelectNextJoinModel(void *unused0, void *unused1, void *unused2, s32 event) {
    s32 variant;
    s32 model;
    s32 id;

    if (event != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        return 0;
    }
    variant = g_joinRequestEntries[g_courseOptionsScreen->selection].variant;
    model = Join_FindJoinModelIndex(variant, g_joinRequestEntries[g_courseOptionsScreen->selection].id);
    do {
        variant++;
        if (variant >= 3) {
            variant = 0;
            model++;
            if (model >= 17) {
                model = 0;
            }
        }
        id = g_rewardItemTiers[variant][model].id;
    } while (id == -1);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variant = variant;
    g_joinRequestEntries[g_courseOptionsScreen->selection].id = id;
    XPlus_CopyString(g_joinRequestEntries[g_courseOptionsScreen->selection].name,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        g_rewardItemTiers[variant][id].text[g_languageIndex]
#else
        *g_rewardItemTiers[variant][id].text
#endif
    );
    g_joinRequestEntries[g_courseOptionsScreen->selection].variantC = variant;
    id = g_courseOptionsScreen->selection;
    Join_UpdateJoinRequestDisplay(id);
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif
