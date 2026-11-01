#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/NODERECAT2A8.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/FRONTEND_RESOURCE_LOAD_STATE.H"
#include "include_asm.h"

/* MENU_SELECTEUROPEANPAKACTIONLABEL.CPP */
#if defined(VERSION_EU)
/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of 3 strings through the jump table
   jtbl_Frontend_SelectPakActionLabel for states 0 to 4, and s_nodeDefaultFieldText for any other state. Returns zero. */

s32 Menu_SelectEuropeanPakActionLabel(struct PakActionLabelView *field) {
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

/* K_WIDGETCONSTANTWORDSBLOCK2.CPP */
#if defined(VERSION_EU)
const unsigned int k_widgetConstantWordsBlock2[1] = {
    0x00330034,
};
#endif
