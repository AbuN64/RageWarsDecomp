#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESPONSE.H"
#include "TYPES.H"
#include "TYPES.H"
#include <ultra64.h>

#if defined(VERSION_US_REV1)




s32 Libultra_ReadDebugLinkByte(u8 *receivedByte) {
    s32 timeout;
    s32 retries;
    s32 expected;
    u8 mask;
    s32 result;
    u8 initial_control;
    u8 control;
    u8 final_control;
    u8 status;

    initial_control = (g_debugLinkModeControl & 0xF8) | 2;
    result = 0;
    g_debugLinkModeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_MODE_REGISTER = initial_control;
    control = g_debugLinkModeControl | 8;
    g_debugLinkModeControl = control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 1;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 1;
    DEBUG_LINK_MODE_REGISTER = control;
    g_debugLinkTransferFailed = 0;
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
        do {
        } while (osPiGetStatus() & 3);
        *receivedByte = g_debugLinkReceivedDataByte;
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
