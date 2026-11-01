#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "../include/BUF16B.H"
#include "TYPES.H"

/* cspsetbank.CPP */
void alCSPSetBank(ALCSPlayer *player, ALBank *bank) {
    Buf16 bankEvent;

    bankEvent.value = bank;
    bankEvent.count = 0xE;
    alEvtqPostEvent(&player->evtq, &bankEvent, 0);
}

void alCSPSetChlFXMix(ALCSPlayer *player, u8 channel, u8 effectMix) {
    Buf16c controlEvent;

    controlEvent.count = 2;
    controlEvent.f8 = (s8)(channel | 0xB0);
    controlEvent.fA = effectMix;
    controlEvent.zero = 0;
    controlEvent.f9 = 0x5B;
    alEvtqPostEvent(&player->evtq, &controlEvent, 0);
}
