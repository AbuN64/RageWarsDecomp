#include "COMMON/RESPONSE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "TYPES.H"
#include <ultra64.h>

#if defined(VERSION_US_REV1)
extern s8 g_debugLinkDataByte;



s32 Libultra_InitDebugLink(void) {
    u8 enabledControl;

    g_debugLinkDataByte = 0;
    g_debugLinkHandshakeControl = 0;
    g_debugLinkTransferControl = 0;
    g_debugLinkModeControl = 0;
    g_debugLinkAuxiliaryControl = 0;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_DATA_REGISTER = 0;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = 0;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_TRANSFER_REGISTER = 0;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_MODE_REGISTER = 0;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_AUXILIARY_REGISTER = 0;
    do {
    } while (osPiGetStatus() & 3);
    enabledControl = g_debugLinkTransferControl | 0x40;
    g_debugLinkTransferControl = enabledControl;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_TRANSFER_REGISTER = enabledControl;
    g_debugLinkTransferFailed = 0;
    return 1;
}
#endif
