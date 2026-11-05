#if defined(VERSION_EU)

#include "include_asm.h"


#include "Common/material_tree.h"


#include "Common/vector4f.h"


#include "Common/sharedplayer.h"


#include "types.h"


#include "Engine/graphics_math.h"


#include "Rsp/random_direction_and_affine_math.h"


#include "Graphu64/graphu64_getangledistance.h"


#include "Graphu64/graphu64_packfixedmatrix.h"


#include "Common/approachlocation.h"


#include "Common/graphics_matrix_and_vector_math.h"


#include "Common/math_helpers.h"


#include "Common/ballisticparams.h"


#include "Common/triple.h"


#include "Particle/graphu64_matrixfromeulerxyz.h"


#include "Common/pooled_floats.h"


#include "Common/mtx.h"


#include "Game/builddirectionmatrix.h"


#include "Fx/normalize_vector.h"


#include "Common/weapon_screen_message_operations.h"


#include "Common/packed.h"


#include "Common/aiprofile.h"


#include "Common/objb.h"


#include <platform_sdk.h>


#include "Graphu64/graphu64_buildlookatmatrix.h"


#include "Data/rest_source_records.h"


#include "Data/Enemy/g_pickuptrailingrodataeux.h"


#include "Common/format.h"


#include "Common/resident_event_handler.h"


#include "data_overlay_layouts.h"


#include "System/engine_data_source.h"


#include "Engine/gregion.h"


float g_arcCosEndpoint = 0.0f;
#endif
