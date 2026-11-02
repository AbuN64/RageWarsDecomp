#include "COMMON/OUTPUT.H"
#include "ENGINE/AUDIO/CHANNEL.H"

int Gsky_StartFadeModeTwo(void *outputStorage) {
    struct CCollisionResults *output = (void *)outputStorage;
    output->contactValue = 0;
    output->typeFC = 2;
    return 2;
}
