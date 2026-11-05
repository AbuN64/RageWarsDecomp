#if defined(VERSION_US_REV1)

#include "types.h"


#include "include_asm.h"

#if defined(VERSION_US_REV1)
#include "Data/Common/menu_times_text_fragment_us_rev1_data.h"
#endif

#if defined(VERSION_US_REV1)
#include "Common/aiprofile.h"
#endif


void *g_skyPostscaledscreenmessageDataAddressWords[3] = {
    0, g_screenMessageSubstitutionReplacement, (void *)&s_menuTimesTextFragmentUsRev1[12],
};
#endif
