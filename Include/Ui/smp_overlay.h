#ifndef UI_SMP_OVERLAY_H
#define UI_SMP_OVERLAY_H
#include "Smp_overlay/smp_overlay.h"
#include "types.h"

struct SlotDialog;
extern void SmpOverlay_AdvancePakDialogPort(void);
extern void SmpOverlay_RefreshPakDialog(void);
/* The pak slot dialog currently shown over the screen. */
extern struct SlotDialog *g_pakDialog;
#endif
