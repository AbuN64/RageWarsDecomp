#include "COMMON/ITEMRECAT20V1.H"
#include "../include/PERIPHERAL_PORT_BYTE_VIEWS.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include "COMMON/LLDIVRESULT.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "../include/libgultra.h"
#include "TYPES.H"
#include "../include/libgultra_inferred/LIBULTRA_WRITEDEBUGLINKBYTE.H"
#include "../include/libgultra_inferred/libultra_executedebuglinkaddress.H"

#if defined(VERSION_US_REV1)
s32 Libultra_SendDebugLinkString(u8 *text) {
    s32 result;
    u8 value;

    result = 0;
    while (1) {
        value = *text++;
        Libultra_WriteDebugLinkByte(value);
        if (g_debugLinkTransferFailed != 0) {
            break;
        }
        if (value != 0) {
            continue;
        }
        result = 1;
        break;
    }
    return result;
}

u8 Libultra_ReadPortStatusByte(void *statusPort) {
    do {
    } while (osPiGetStatus() & 3);
    return (((struct PeripheralPortStatusByteView *) ((s8 *) statusPort))->statusByte);
}

void Libultra_WritePortByteValue(s16 *port, s32 value) {
    do {
    } while (osPiGetStatus() & 3);
    *port = value & 0xFF;
}

/* Waits for the masked byte at offset 1 of a status block to equal a given value, polling only while the low two status bits osPiGetStatus reports are clear, returning 1 on a match and, after g_debugLinkRetryLimit retries of the given poll count each, setting g_debugLinkTransferFailed and returning 0. Adapted from Libultra_CheckDebugLinkAcknowledgement with the status address, mask, expected value and timeout reload taken from the arguments. */





s32 Libultra_WaitPortStatus(u8 *status, u8 mask, u32 expectedStatus, s32 reload) {
    s32 retries;
    s32 result;
    s32 timeout;
    s32 value;
    s32 expected;

    retries = g_debugLinkRetryLimit;
    result = 0;
    timeout = reload;
    expected = expectedStatus & 0xFF;
    do {
        do {
        } while (osPiGetStatus() & 3);
        value = mask & status[1];
        if (value == expected) {
            result = 1;
            goto done;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = reload;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;
done:
    return result;
}




s32 Libultra_WaitDebugLinkAcknowledgement(u32 expectedStatus) {
    s32 retries;
    s32 result;
    s32 timeout;
    s32 mask;
    s32 value;
    s32 expected;

    retries = g_debugLinkRetryLimit;
    mask = 1;
    result = 0;
    timeout = 0x4E20;
    expected = expectedStatus & 0xFF;
    do {
        do {
        } while (osPiGetStatus() & 3);
        value = DEBUG_LINK_TRANSMIT_STATUS_BYTE & mask;
        if (value == expected) {
            result = 1;
            goto done;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;
done:
    return result;
}

/* Waits for bit 0 of the cartridge-domain status byte DEBUG_LINK_TRANSMIT_STATUS_BYTE to equal expectedStatus, polling only while the low two status bits osPiGetStatus reports are clear, returning 1 on a match and, after g_debugLinkRetryLimit retries of two polls each, setting g_debugLinkTransferFailed and returning 0. Adapted from Libultra_WaitDebugLinkAcknowledgement with the timeout reload 0x4E20 changed to 1 and the mask held as a byte. */





s32 Libultra_CheckDebugLinkAcknowledgement(u32 expectedStatus) {
    s32 retries;
    s32 result;
    s32 timeout;
    u8 mask;
    s32 value;
    s32 expected;

    retries = g_debugLinkRetryLimit;
    mask = 1;
    result = 0;
    timeout = 1;
    expected = expectedStatus & 0xFF;
    do {
        do {
        } while (osPiGetStatus() & 3);
        value = DEBUG_LINK_TRANSMIT_STATUS_BYTE & mask;
        if (value == expected) {
            result = 1;
            goto done;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 1;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;
done:
    return result;
}

/* Waits for bit 6 of the cartridge-domain status byte DEBUG_LINK_TRANSMIT_STATUS_BYTE to equal expectedStatus, polling only while the low two status bits osPiGetStatus reports are clear, returning 1 on a match and, after g_debugLinkRetryLimit retries of 0x4E21 polls each, setting g_debugLinkTransferFailed and returning 0. Adapted from Libultra_WaitDebugLinkAcknowledgement with the mask bit 6 and the expected value held as a byte. */





s32 Libultra_WaitDebugLinkReceiveReady(u32 expectedStatus) {
    s32 retries;
    s32 result;
    s32 timeout;
    s32 mask;
    s32 value;
    u8 expected;

    mask = 0x40;
    retries = g_debugLinkRetryLimit;
    expected = (expectedStatus << 6) & 0xFF;
    result = 0;
    timeout = 0x4E20;
    do {
        do {
        } while (osPiGetStatus() & 3);
        value = DEBUG_LINK_TRANSMIT_STATUS_BYTE & mask;
        if (value == expected) {
            result = 1;
            goto done;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;
done:
    return result;
}

/* Waits for bit 6 of the cartridge-domain status byte DEBUG_LINK_RECEIVE_STATUS_BYTE to equal expectedStatus, polling only while the low two status bits osPiGetStatus reports are clear, returning 1 on a match and, after g_debugLinkRetryLimit retries of 0x4E21 polls each, setting g_debugLinkTransferFailed and returning 0. Adapted from Libultra_WaitDebugLinkAcknowledgement with the mask bit 6 and the expected value held as a byte. */





s32 Libultra_WaitDebugLinkTransmitReady(u32 expectedStatus) {
    s32 retries;
    s32 result;
    s32 timeout;
    s32 mask;
    s32 value;
    u8 expected;

    mask = 0x40;
    retries = g_debugLinkRetryLimit;
    expected = (expectedStatus << 6) & 0xFF;
    result = 0;
    timeout = 0x4E20;
    do {
        do {
        } while (osPiGetStatus() & 3);
        value = DEBUG_LINK_RECEIVE_STATUS_BYTE & mask;
        if (value == expected) {
            result = 1;
            goto done;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;
done:
    return result;
}

/* Waits for bit 1 of the cartridge-domain status byte DEBUG_LINK_TRANSMIT_STATUS_BYTE to equal expectedStatus, polling only while the low two status bits osPiGetStatus reports are clear, returning 1 on a match and, after g_debugLinkRetryLimit retries of 0x4E21 polls each, setting g_debugLinkTransferFailed and returning 0. Adapted from Libultra_WaitDebugLinkAcknowledgement with the mask bit 1 and the expected value held as a byte. */





s32 Libultra_WaitDebugLinkRequestAcknowledgement(u32 expectedStatus) {
    s32 retries;
    s32 result;
    s32 timeout;
    s32 mask;
    s32 value;
    u8 expected;

    mask = 0x2;
    retries = g_debugLinkRetryLimit;
    expected = (expectedStatus << 1) & 0xFF;
    result = 0;
    timeout = 0x4E20;
    do {
        do {
        } while (osPiGetStatus() & 3);
        value = DEBUG_LINK_TRANSMIT_STATUS_BYTE & mask;
        if (value == expected) {
            result = 1;
            goto done;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;
done:
    return result;
}



void Libultra_SetDebugLinkEnable(s32 enabled) {
    u8 controlByte;

    controlByte = (g_debugLinkTransferControl & 0xBF) | (enabled << 6);
    g_debugLinkTransferControl = controlByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_TRANSFER_REGISTER = controlByte & 0xFF;
}

void Libultra_SetDebugLinkMode(s32 mode) {
    u8 controlByte;
    controlByte = mode | (g_debugLinkModeControl & 0xF8);
    g_debugLinkModeControl = controlByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_MODE_REGISTER = controlByte & 0xFF;
}



void Libultra_SetDebugLinkByteRequest(s32 enabled) {
    u8 controlByte;

    controlByte = (g_debugLinkModeControl & 0xF7) | (enabled << 3);
    g_debugLinkModeControl = controlByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_MODE_REGISTER = controlByte & 0xFF;
}



void Libultra_SetDebugLinkReceiveEnable(s32 enabled) {
    u8 controlByte;

    controlByte = (g_debugLinkHandshakeControl & 0xF7) | (enabled << 3);
    g_debugLinkHandshakeControl = controlByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = controlByte & 0xFF;
}



void Libultra_SetDebugLinkHostRequest(s32 enabled) {
    u8 controlByte;

    controlByte = (g_debugLinkHandshakeControl & 0xFB) | (enabled << 2);
    g_debugLinkHandshakeControl = controlByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = controlByte & 0xFF;
}



void Libultra_SetDebugLinkHandshakeBit(s32 enabled) {
    u8 controlByte;

    controlByte = (g_debugLinkHandshakeControl & 0xFD) | (enabled << 1);
    g_debugLinkHandshakeControl = controlByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = controlByte & 0xFF;
}

void Libultra_SetDebugLinkTransmitStrobe(s32 enabled) {
    u8 controlByte;
    controlByte = enabled | (g_debugLinkHandshakeControl & 0xFE);
    g_debugLinkHandshakeControl = controlByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = controlByte & 0xFF;
}



void Libultra_SetDebugLinkBlockTransfer(s32 enabled) {
    u8 controlByte;

    controlByte = (g_debugLinkTransferControl & 0xFD) | (enabled << 1);
    g_debugLinkTransferControl = controlByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_TRANSFER_REGISTER = controlByte & 0xFF;
}

extern s8 g_debugLinkDataByte;
void Libultra_WriteDebugLinkDataPort(s8 dataByte) {
    g_debugLinkDataByte = dataByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_DATA_REGISTER = dataByte & 0xFF;
}

s32 Libultra_GetDebugLinkRequestAcknowledgement(void) {
    do {
    } while (osPiGetStatus() & 3);
    return ((u8) DEBUG_LINK_TRANSMIT_STATUS_BYTE >> 1) & 1;
}

/** Return the true result used by callers at VRAM 0x802B2048. */
int Libultra_DebugLinkAlwaysReady(void) {
    return 1;
}

extern s32 Libultra_ReadDebugLinkByte(u8 *);






s32 Libultra_ExecuteDebugLinkAddress(void) {
    ReadWord first;
    s32 word;
    s32 result;

    Libultra_ReadDebugLinkByte(&first.byte);
    result = 0;
    if (g_debugLinkTransferFailed == 0) {
        word = first.byte << 8;
        Libultra_ReadDebugLinkByte(&first.byte);
        if (g_debugLinkTransferFailed == 0) {
            word |= first.byte;
            Libultra_ReadDebugLinkByte(&first.byte);
            word <<= 8;
            if (g_debugLinkTransferFailed == 0) {
                word |= first.byte;
                Libultra_ReadDebugLinkByte(&first.byte);
                word <<= 8;
                if (g_debugLinkTransferFailed == 0) {
                    word |= first.byte;
                    first.word = word;
                    if (word != 0) {
                        osSetIntMask(1);
                        osWritebackDCacheAll();
                        osInvalICache(0x80000000, 0x800000);
                        ((void (*)(void))word)();
                    }
                    result = 1;
                }
            }
        }
    }
    return result;
}




s32 Libultra_WriteDebugLinkMemoryByte(void) {
    ReadWordByte first;
    s32 word;
    s32 result;

    Libultra_ReadDebugLinkByte(&first.byte);
    result = 0;
    if (g_debugLinkTransferFailed == 0) {
        word = first.byte << 8;
        Libultra_ReadDebugLinkByte(&first.byte);
        if (g_debugLinkTransferFailed == 0) {
            word |= first.byte;
            Libultra_ReadDebugLinkByte(&first.byte);
            word <<= 8;
            if (g_debugLinkTransferFailed == 0) {
                word |= first.byte;
                Libultra_ReadDebugLinkByte(&first.byte);
                word <<= 8;
                if (g_debugLinkTransferFailed == 0) {
                    word |= first.byte;
                    first.word = word;
                    Libultra_ReadDebugLinkByte(&first.value);
                    if (g_debugLinkTransferFailed == 0) {
                        result = 1;
                        *(u8 *)first.word = first.value;
                    }
                }
            }
        }
    }
    return result;
}




s32 Libultra_ReadDebugLinkMemoryByte(void) {
    ReadWord first;
    s32 word;
    s32 result;

    Libultra_ReadDebugLinkByte(&first.byte);
    result = 0;
    if (g_debugLinkTransferFailed == 0) {
        word = first.byte << 8;
        Libultra_ReadDebugLinkByte(&first.byte);
        if (g_debugLinkTransferFailed == 0) {
            word |= first.byte;
            Libultra_ReadDebugLinkByte(&first.byte);
            word <<= 8;
            if (g_debugLinkTransferFailed == 0) {
                word |= first.byte;
                Libultra_ReadDebugLinkByte(&first.byte);
                word <<= 8;
                if (g_debugLinkTransferFailed == 0) {
                    word |= first.byte;
                    first.word = word;
                    Libultra_WriteDebugLinkByte(*(u8 *)first.word);
                    result = g_debugLinkTransferFailed == 0;
                }
            }
        }
    }
    return result;
}


s32 Libultra_HandshakeDebugLink(void) {
    u8 receivedByte;
    s32 result;

    Libultra_WriteDebugLinkByte(0x10);
    result = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&receivedByte);
        if (g_debugLinkTransferFailed == 0) {
            result = receivedByte == 0x11;
        }
    }
    return result;
}
#endif
