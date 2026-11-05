#ifndef OVLGAME_NOTE_RELEASERENDERBUFFERS_H
#define OVLGAME_NOTE_RELEASERENDERBUFFERS_H
#include "Common/pak_profile_load.h"
#include "Ovlgame/render_buffer_resources.h"
extern void Note_ReleaseRenderBuffers(struct RenderBufferResources *record);
extern void Note_ClearRenderRecord(struct RenderBufferResources *record);
#endif
