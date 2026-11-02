#include "COMMON/OUTPUT.H"
#include "ENGINE/AUDIO/CHANNEL.H"

/** Reset the word at 0x100 and enable the word at 0xFC. */
void Gsky_StartFadeModeOne(char *object) {
    struct CCollisionResults *output = (void *)object;
    output->contactValue = 0;
    output->typeFC = 1;
}
