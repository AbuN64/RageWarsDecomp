#ifndef MENU_TRACK_ANGLES_H
#define MENU_TRACK_ANGLES_H
#include "types.h"

extern void Menu_TriggerTrackEvent(int event);
typedef struct TrackAngleKindView {
    char pad0[0x8];
    char kind;
} TrackAngleKindView;

#endif
