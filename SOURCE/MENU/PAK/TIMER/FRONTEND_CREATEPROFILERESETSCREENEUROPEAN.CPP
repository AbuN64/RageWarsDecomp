#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/FRONTEND_RESOURCE_LOAD_STATE.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "COMMON/PLAYERPROFILES.H"
#if !(defined(VERSION_DE) || defined(VERSION_EU))
/* 8040B45C_17.CPP */
/* 8040B45C_8.CPP */
/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of 3 strings through the jump table
   jtbl_Frontend_SelectPakActionLabel for states 0 to 4, and s_nodeDefaultFieldText for any other state. Returns zero. */
s32 Frontend_SelectPakActionLabel(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    if (state >= 5) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto case_3;
        case 2: goto case_3;
        case 3: goto case_1;
        case 4: goto case_2;
        }
state_other:
    field->text = s_nodeDefaultFieldText;
    goto done;
case_1:
    field->text = s_nodeDefaultFieldText;
    goto done;
case_2:
    field->text = s_nodeDefaultFieldText;
    goto done;
case_3:
    field->text = s_nodeAlternateFieldText;
done:
    return 0;
}
#endif
#if defined(VERSION_EU_X)
unsigned int k_FrontendCreateprofileresetscreeneuropeanEncodedWords[1] = {
    0x0043D414,
};
#endif
#if defined(VERSION_EU)
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/WORLD.H"
#endif
