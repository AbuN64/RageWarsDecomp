#if defined(VERSION_US)

#include "include_asm.h"


#include "Data/Gfxdata/event_handler_code_targets.h"


#include "Data/Ui/type_text_event_table.h"


#include "Common/frontend_video_mode.h"


#include "Common/selectionscreenstate.h"


#include "Common/widget_tree.h"


#include "types.h"


#include "Frontend/archivedata.h"


#include "Common/frustum.h"


#include "Menu/Gfx/image.h"


#include "Common/runtime_declarations.h"


#include "Common/Lone/frontend_viewport_width.h"


#include "Resmgr/resmgr_stream_callbacks.h"


#include "Menu/widget_records.h"


#include "Common/sharedplayer.h"


#include "Common/archive_chunk_images.h"


#include "Frontend/frontend_openresourcearchive.h"


#include "Frontend/node_releasechunkimages.h"


#include "Resmgr/resmgr_stream_io.h"


#include "Ui/Quag/N64_Eng.h"


#include "Scene/cache_freememory.h"


#include "Resmgr/resmgr_string_memory.h"


#include "Audio/voice.h"


#include "Frontend/node_getimagetexture.h"


#include "Frontend/frontend_configureimageconversion.h"


#include "Node/node_getbanktiletexture.h"


#include "Image/image.h"


#include "Ui/smp.h"


#include "Cache/cache_allocatememory.h"


#include "X_stdio/x_stdio.h"


#include "Frontend/frontend_address_symbols.h"


#include "Common/resident_event_handler.h"


#include "Common/aiprofile.h"


#include "Common/widget_texture_retention.h"


#include "Frontend/layout.h"


#include "Node/node_configurescrolledtablecell.h"


#include "Node/frontend_openresourcearchive.h"


#include "Node/node_acquirearchiveentry.h"


#include "Frontend/node_creategridlistfromwidget.h"


#include "Frontend/widget_drawtextwidget.h"


#include "Frontend/node_findwidgetbyresourceid.h"


#include "Common/screen.h"


#include <platform_sdk.h>


#include "types.h"


#include "Frontend/layout.h"


#include "Node/node_configurescrolledtablecell.h"


#include "Widget/widget_findwidgetatpoint.h"


#include "Node/node_acquirearchiveentry.h"


#include "Frontend/frontend_address_symbols.h"

#if defined(VERSION_EU_X)
#include "Common/ccollisionsetup_t.h"
#endif

#if defined(VERSION_EU_X)
#include "Frontend/frontend_address_symbols.h"
#endif

#if defined(VERSION_EU_X)
#include "Frontend/frontend.h"
#endif




typedef struct {
    char pad0[0x20];
} Texture;


typedef struct {
    char pad0[4];
    s32 stamp;
    u16 flags;
    char pad0A[2];
    Texture texture;
} TextureSlot;


typedef struct {
    s32 offset;
    s8 fmt;
    s8 siz;
    s8 wid;
    char pad7[1];
} Tile;


typedef struct {
    s32 f0;
    s32 f4;
    s16 depth;
    s16 f0A;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 base;
    s32 size;
} BankImage;


typedef struct {
    s32 loaded;
    Tile tiles[96];
    u8 *offsets[96];
    TextureSlot **slotsByPass;
    s32 **listsByPass;
    BankImage *image;
    u8 loads;
    char pad491[3];
    s32 stamp;
    s16 held;
    char pad49A[2];
} Bank;


typedef struct List List;

char s_FrontendOpenresourcearchiveELINTRO4equText[13] =
    "EL_INTRO_4equ";
#endif
