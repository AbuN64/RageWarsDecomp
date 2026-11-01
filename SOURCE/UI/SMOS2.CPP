#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CALLBACK.H"
#include "MENU.H"
#include "include_asm.h"

/* SMOS_DISPATCHDESCENDANTSCREENEVENT.CPP */
void Smos_DispatchDescendantScreenEvent(ScreenEventTreeNode *node, s32 event, s32 source, s32 control, s32 extra,
                   s32 depth) {
    ScreenManager *context;
    s32 saved;
    s32 valid;
    s32 *value;

    if (node != 0) {
        context = g_screenManager;
        saved = context->handled;
        context->handled = 0;
        value = &context->handled;
        if (node->left != 0) {
            Smos_DispatchDescendantScreenEvent(node->left, event, source, control, extra, depth + 1);
        }
        if (context->handled == 0) {
            if (node->right != 0) {
                Smos_DispatchDescendantScreenEvent(node->right, event, source, control, extra, depth + 1);
            }
            if ((context->handled == 0) && (depth > 0) && (node->value != -1) &&
                (node->type >= 9U)) {
                valid = 1;
                if (((event == 3592) && ((node->flags | 2) == 0)) ||
                    ((event == 3593) && ((node->flags | 4) == 0))) {
                    valid = 0;
                }
                if (valid != 0) {
                    GetMenuScreenOwner();
                    Menu_RouteElementEvent(node->value, event, source, control, extra);
                }
            }
        }
        *value = saved;
    }
}

void *Smos_GetScreenManager(void) {
    return g_screenManager;
}
