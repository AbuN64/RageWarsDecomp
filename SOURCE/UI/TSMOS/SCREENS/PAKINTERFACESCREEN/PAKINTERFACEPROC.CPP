#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
typedef struct PAKDialogMessage { u8 unused[12]; s16 control; } PAKDialogMessage;
typedef struct PAKDialogHandler {
    s32 message;
    s32 control;
    s32 (*invoke)(PAKDialogMessage *, s32, s32, s32, s32);
} PAKDialogHandler;
extern PAKDialogHandler g_pakInterfaceHandlers[];
/* Dispatch matching screen messages until the handler-table sentinel. */
s32 PAKInterfaceProc(PAKDialogMessage *a, s32 b, s32 c, s32 d, s32 e) {
    s32 i;
    for (i = 0; g_pakInterfaceHandlers[i].invoke; i++) {
        if (g_pakInterfaceHandlers[i].message == b) {
            if (g_pakInterfaceHandlers[i].control == a->control || g_pakInterfaceHandlers[i].control == 30000) {
                return g_pakInterfaceHandlers[i].invoke(a, b, c, d, e);
            }
        }
    }
    return 0;
}
#endif
