#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESPONSE.H"
#include "TYPES.H"
#include "TYPES.H"
#include <ultra64.h>

#if defined(VERSION_US_REV1)
/* Writes one byte through the cartridge-domain port at DEBUG_LINK_DATA_REGISTER with the control register DEBUG_LINK_MODE_REGISTER and strobe register DEBUG_LINK_HANDSHAKE_REGISTER, waiting for the ready bit of DEBUG_LINK_TRANSMIT_STATUS_BYTE to set and then clear with g_debugLinkRetryLimit retries each, setting g_debugLinkTransferFailed on a timeout and returning 1 on success. Adapted from Libultra_ReadDebugLinkByte with the read of g_debugLinkReceivedDataByte changed to a write of the argument through DEBUG_LINK_DATA_REGISTER and the strobe at DEBUG_LINK_HANDSHAKE_REGISTER raised and lowered around the handshake, and the argument copied into a second local for the port write. */


extern u8 g_debugLinkDataByte;



s32 Libultra_WriteDebugLinkByte(s32 outputByte) {
    s32 timeout;
    s32 data;
    s32 retries;
    s32 expected;
    u8 mask;
    s32 result;
    u8 initial_control;
    u8 control;
    u8 final_control;
    u8 strobe;
    u8 status;

    initial_control = (g_debugLinkModeControl & 0xF8) | 3;
    result = 0;
    g_debugLinkModeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_MODE_REGISTER = initial_control;
    g_debugLinkDataByte = outputByte;
    data = outputByte;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_DATA_REGISTER = (u8)data;
    strobe = g_debugLinkHandshakeControl | 1;
    g_debugLinkHandshakeControl = strobe;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = strobe;
    control = g_debugLinkModeControl | 8;
    g_debugLinkModeControl = control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 1;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 1;
    DEBUG_LINK_MODE_REGISTER = control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & mask) == expected) {
            goto first_done;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;
first_done:

    if (g_debugLinkTransferFailed == 0) {
        control = g_debugLinkModeControl & 0xF7;
        g_debugLinkModeControl = control;
        do {
        } while (osPiGetStatus() & 3);

        expected = 1;
        retries = g_debugLinkRetryLimit;
        timeout = 0x4E20;
        DEBUG_LINK_MODE_REGISTER = control;
        do {
            do {
            } while (osPiGetStatus() & 3);
            status = DEBUG_LINK_TRANSMIT_STATUS_BYTE & expected;
            if (status == 0) {
                goto second_done;
            }
            if (timeout-- == 0) {
                retries--;
                timeout = 0x4E20;
            }
        } while (retries > 0);
        g_debugLinkTransferFailed = 1;
second_done:

        if (g_debugLinkTransferFailed == 0) {
            strobe = g_debugLinkHandshakeControl & 0xFE;
            g_debugLinkHandshakeControl = strobe;
            do {
            } while (osPiGetStatus() & 3);
            DEBUG_LINK_HANDSHAKE_REGISTER = strobe;
            final_control = g_debugLinkModeControl & 0xF8;
            g_debugLinkModeControl = final_control;
            do {
            } while (osPiGetStatus() & 3);
            DEBUG_LINK_MODE_REGISTER = final_control;
            result = 1;
        }
    }
    return result;
}
#endif
