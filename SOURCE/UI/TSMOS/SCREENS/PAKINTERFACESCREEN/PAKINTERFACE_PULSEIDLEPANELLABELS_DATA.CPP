#include "TYPES.H"
/* PAKInterface_PulseIdlePanelLabels reads floats at +0, +4, +8 and +12.
 * The aliases for phase and bias keep their original addresses. */
typedef struct PakPanelPulseConstants {
    f32 phaseScale;
    f32 amplitude;
    f32 bias;
    f32 unsignedConversionThreshold;
} PakPanelPulseConstants;
typedef char PakPanelPulseConstantsSize[(sizeof(PakPanelPulseConstants) == 16) ? 1 : -1];
const PakPanelPulseConstants g_pakIdlePanelPulseConstants = {
    0.0033333334140479565f, 100.0f, 150.0f, 2147483648.0f,
};
