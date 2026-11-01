#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESPONSE.H"
#include "TYPES.H"
#include "TYPES.H"
#include <ultra64.h>

#if defined(VERSION_US_REV1)
/* Reads count bytes from the cartridge-domain port DEBUG_LINK_BLOCK_STATUS_BYTE into a buffer, waiting for bit 0x40 of DEBUG_LINK_TRANSMIT_STATUS_BYTE before each byte with g_debugLinkRetryLimit retries, accumulating a rotate-and-add checksum stored through the third argument and returning 1 on success. Adapted from Libultra_ReadDebugLinkByte with the single-byte read changed to a counted loop with a checksum and the strobe registers DEBUG_LINK_HANDSHAKE_REGISTER and DEBUG_LINK_TRANSFER_REGISTER raised and lowered around it. */





s32 Libultra_ReadDebugLinkBlock(u8 *dst, s32 count, u32 *checksum) {
    s32 timeout;
    s32 retries;
    s32 expected;
    u8 mask;
    s32 result;
    u32 sum;
    u8 control;
    u8 value;

    result = 0;
    sum = 0;
    control = g_debugLinkHandshakeControl | 8;
    g_debugLinkHandshakeControl = control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = control;
    control = g_debugLinkModeControl & 0xF8;
    g_debugLinkModeControl = control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_MODE_REGISTER = control;
    control = g_debugLinkTransferControl | 2;
    g_debugLinkTransferControl = control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_TRANSFER_REGISTER = control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_BLOCK_CONTROL_REGISTER = 0;

    if (count-- != 0) {
        mask = 0x40;
        expected = 0x40;
next:
        retries = g_debugLinkRetryLimit;
        timeout = 0x4E20;
        do {
            do {
            } while (osPiGetStatus() & 3);
            if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & mask) == expected) {
                goto ready;
            }
            if (timeout-- == 0) {
                retries--;
                timeout = 0x4E20;
            }
        } while (retries > 0);
        g_debugLinkTransferFailed = 1;
ready:
        if (g_debugLinkTransferFailed != 0) {
            goto release;
        }
        do {
        } while (osPiGetStatus() & 3);
        sum = (sum << 1) | (sum >> 31);
        value = DEBUG_LINK_BLOCK_STATUS_BYTE;
        *dst++ = value;
        sum += value;
        if (count-- != 0) {
            goto next;
        }
    }
    *checksum = sum;
    result = 1;
release:
    control = g_debugLinkTransferControl & 0xFD;
    g_debugLinkTransferControl = control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_TRANSFER_REGISTER = control;
    control = g_debugLinkHandshakeControl & 0xF7;
    g_debugLinkHandshakeControl = control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = control;
    control = g_debugLinkModeControl & 0xF8;
    g_debugLinkModeControl = control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_MODE_REGISTER = control;
    return result;
}
#endif

#if defined(VERSION_US_REV1)
extern s16 DEBUG_LINK_BLOCK_REQUEST_REGISTER;
extern s16 DEBUG_LINK_BLOCK_DATA_REGISTER;
static inline void waitPort(u8 *port, u8 mask, u8 expected)
{
    s32 retries = g_debugLinkRetryLimit;
    s32 timeout = 0x4E20;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((*port & mask) == expected)
            return;
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;
}

s32 Libultra_WriteDebugLinkBlock(u8 *stream, s32 count)
{
    s32 result = 0;
    u8 control;
    u8 data;

    waitPort(&DEBUG_LINK_RECEIVE_STATUS_BYTE, 0x40, 0x40);
    if (g_debugLinkTransferFailed == 0) {
        control = (g_debugLinkModeControl & 0xF8) | 1;
        g_debugLinkModeControl = control;
        do {} while (osPiGetStatus() & 3);
        DEBUG_LINK_MODE_REGISTER = control;
        control = g_debugLinkTransferControl | 2;
        g_debugLinkTransferControl = control;
        do {} while (osPiGetStatus() & 3);
        DEBUG_LINK_TRANSFER_REGISTER = control;
        control = g_debugLinkHandshakeControl | 1;
        g_debugLinkHandshakeControl = control;
        do {} while (osPiGetStatus() & 3);
        DEBUG_LINK_HANDSHAKE_REGISTER = control;
        do {} while (osPiGetStatus() & 3);
        DEBUG_LINK_BLOCK_REQUEST_REGISTER = 0;
        while (count-- != 0) {
            waitPort(&DEBUG_LINK_TRANSMIT_STATUS_BYTE, 0x40, 0x40);
            if (g_debugLinkTransferFailed != 0)
                goto cleanup;
            data = *stream++;
            do {} while (osPiGetStatus() & 3);
            DEBUG_LINK_BLOCK_DATA_REGISTER = data;
        }
        waitPort(&DEBUG_LINK_TRANSMIT_STATUS_BYTE, 0x40, 0x40);
        if (g_debugLinkTransferFailed == 0) {
            s32 timeout = 0x4E20;
            u8 mask = 0x40;
            s32 retries = g_debugLinkRetryLimit;
            s32 expected = 0;
            do {
                do {} while (osPiGetStatus() & 3);
                if ((DEBUG_LINK_RECEIVE_STATUS_BYTE & mask) == expected)
                    goto close_ready;
                if (timeout-- == 0) {
                    retries--;
                    timeout = 0x4E20;
                }
            } while (retries > 0);
            g_debugLinkTransferFailed = 1;
close_ready:

            if (g_debugLinkTransferFailed == 0)
                result = 1;
        }
    }
cleanup:
    control = g_debugLinkHandshakeControl & 0xFE;
    g_debugLinkHandshakeControl = control;
    do {} while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = control;
    control = g_debugLinkTransferControl & 0xFD;
    g_debugLinkTransferControl = control;
    do {} while (osPiGetStatus() & 3);
    DEBUG_LINK_TRANSFER_REGISTER = control;
    control = g_debugLinkModeControl & 0xF8;
    g_debugLinkModeControl = control;
    do {} while (osPiGetStatus() & 3);
    DEBUG_LINK_MODE_REGISTER = control;
    return result;
}
#endif
