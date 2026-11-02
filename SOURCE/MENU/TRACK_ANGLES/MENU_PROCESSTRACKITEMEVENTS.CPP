#include "COMMON/WORLD.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "TYPES.H"
#include "MENU/MENU_PROCESSTRACKITEMEVENTS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Releases the current record's track-2 timed items whose time has come (or all live ones once the
   record's end time has passed): special items (kind and subkind 1 and 5, 9 and 4, 10 and 3) go to
   Track_RequestTrackByIds_MenuProcesstrackitemevents and clear the record's pending flag, others to Link_ActivateTrigger, then each entry is
   marked spent and its item is flagged and refreshed through Scene_SetTriggerStateBit. Adapted from Track_HasNoTrackRequestItems: indexed entry
   access and the table base taken inside the loop. */









extern RecordMenuProcessTrackItemEvents *g_cinemaSequenceState;

extern s32 Cinema_IsSequenceActive(void);
extern void Track_RequestTrackByIds(s32 mode, TriggerStateBitDescriptor *item);
extern void Link_ActivateTrigger(TriggerStateBitDescriptor *item);
extern void Scene_SetTriggerStateBit(Shared_World *world, TriggerStateBitDescriptor *item, s32 mode);

void Menu_ProcessTrackItemEvents(void) {
    f32 time;
    s32 late;
    s32 *track;
    TrackTimedItemEvent *entry;
    Shared_World *tables;
    TriggerStateBitDescriptor *item;
    s32 n;
    s32 i;
    s32 hit;

    time = g_cinemaSequenceState->time;
    late = 0;
    if (Cinema_IsSequenceActive() == 0) {
        return;
    }
    if (g_cinemaSequenceState->active == 0) {
        return;
    }
    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 2);
    n = track[1];
    entry = (TrackTimedItemEvent *)(track + 2);
    if (n == 0) {
        return;
    }
    if (g_cinemaSequenceState->endTime <= time) {
        late = 1;
    }
    for (i = 0; i < n; i++) {
        tables = &g_world;
        if (entry[i].time <= -10000.0f) {
            continue;
        }
        if (time < entry[i].time && late == 0) {
            continue;
        }
        if (entry[i].side == 0) {
            item = &((TriggerStateBitDescriptor *)tables->recordArray)[entry[i].index];
        } else {
            item = &((TriggerStateBitDescriptor *)tables->alternateRecordArray)[entry[i].index];
        }
        hit = 0;
        switch (item->kind) {
            case 1:
                if (item->subkind == 5) {
                    hit = 1;
                }
                break;
            case 9:
                if (item->subkind == 4) {
                    hit = 1;
                }
                break;
            case 10:
                if (item->subkind == 3) {
                    hit = 1;
                }
                break;
            default:
                hit = 0;
                break;
        }
        if (hit) {
            Track_RequestTrackByIds(0, item);
            g_cinemaSequenceState->pending = 0;
        } else {
            Link_ActivateTrigger(item);
        }
        entry[i].time = -20000.0f;
        item->flags = (item->flags | 1) & 0xEF;
        Scene_SetTriggerStateBit(&g_world, item, 0);
    }
}
