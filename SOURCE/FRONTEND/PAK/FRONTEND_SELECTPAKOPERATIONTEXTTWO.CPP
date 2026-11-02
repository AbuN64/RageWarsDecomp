#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/FRONTEND_RESOURCE_LOAD_STATE.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"

/* Points a field's text at the label for the state word g_frontendResourceLoadStage: one of 4 strings through the jump table
   k_pakOperationTwoTextStateJumpTable for states 0 to 4, and g_pakOperationTwoDefaultLabel for any other state. Returns zero. */








s32 Frontend_SelectPakOperationTextTwo(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    if (state >= 5) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto case_1;
        case 2: goto case_2;
        case 3: goto case_3;
        case 4: goto case_4;
        }
state_other:
    field->text = g_pakOperationTwoDefaultLabel;
    goto done;
case_1:
    field->text = g_pakOperationTwoStateOneLabel;
    goto done;
case_2:
    field->text = g_pakOperationTwoStateTwoLabel;
    goto done;
case_3:
    field->text = g_pakOperationTwoStateThreeLabel;
    goto done;
case_4:
    field->text = g_pakOperationTwoStateFourLabel;
done:
    return 0;
}
