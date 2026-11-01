#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Pulses entry i of the 2920-byte records g_pakProfileScreenState points to: takes the sine of i plus the
   entry's phase word at 0x2C + 4i scaled by g_pakPanelPulsePhaseScale, maps it through the next two constants,
   and stores the unsigned result as the alpha byte at 0x10 of items 0x2C2 and 0x2C3 of the
   entry's window. */

extern struct ResourceSmpFlickerCreateFlickerWidget *Node_FindWidgetByResourceId(void *, s32);
void PAKInterface_PulseIdlePanelLabels(s32 index) {
    float f;
    u32 alpha;
    struct EntryPAKInterfacePulseIdlePanelLabels *entry;
    f = Math_Cosf((float)index + (float)g_pakProfileScreenState->selected[index] * g_pakPanelPulsePhaseScale)
        * (*(&g_pakPanelPulsePhaseScale + 1)) + g_pakPanelPulseUnsignedThreshold;
    if (f >= (*(&g_pakPanelPulseUnsignedThreshold + 1))) {
        goto large;
    }
    alpha = (s32)f;
    goto converted;
large:
    alpha = (s32)(f - (*(&g_pakPanelPulseUnsignedThreshold + 1)));
    alpha |= 0x80000000;
converted:
    entry = (struct EntryPAKInterfacePulseIdlePanelLabels *)((char *)g_pakProfileScreenState + index * sizeof(PakProfilePanelState));
#if defined(VERSION_DE)
    Node_FindWidgetByResourceId(entry->window, 740)->value = alpha;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    Node_FindWidgetByResourceId(entry->window, 706)->value = alpha;
#elif defined(VERSION_EU_X)
    Node_FindWidgetByResourceId(entry->window, 725)->value = alpha;
#endif
    entry = (struct EntryPAKInterfacePulseIdlePanelLabels *)((char *)g_pakProfileScreenState + index * sizeof(PakProfilePanelState));
#if defined(VERSION_DE)
    Node_FindWidgetByResourceId(entry->window, 741)->value = alpha;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    Node_FindWidgetByResourceId(entry->window, 707)->value = alpha;
#elif defined(VERSION_EU_X)
    Node_FindWidgetByResourceId(entry->window, 724)->value = alpha;
#endif
}
