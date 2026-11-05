#ifndef LIBGULTRA_INFERRED_CSPHANDLEMIDIMSG_H
#define LIBGULTRA_INFERRED_CSPHANDLEMIDIMSG_H
#include "Common/compressed_sequence_and_event_views.h"
/* Process one compact-sequence MIDI message; O32/native all-version proof retained. */
void __CSPHandleMIDIMsg(void *object, ALEvent *message);
#endif
