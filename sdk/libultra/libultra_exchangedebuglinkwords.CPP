#include "../include/libgultra_inferred/LIBULTRA_WRITEDEBUGLINKBYTE.H"
#include "COMMON/RESPONSE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include "COMMON/LLDIVRESULT.H"
#include "TYPES.H"
#include "../include/libgultra.h"
#include "TYPES.H"
#include "../include/libgultra_inferred/libultra_exchangedebuglinkwords.H"

#if defined(VERSION_US_REV1)



extern void Libultra_InitDebugLink(void);

extern s32 Libultra_ReadDebugLinkByte(u8 *);


extern void Libultra_ReadDebugLinkHalfword(void);

extern void Libultra_ReadDebugLinkWord(void);



extern void Libultra_WriteDebugLinkHalfword(void);

extern void Libultra_WriteDebugLinkWord(void);

extern void Libultra_ReceiveDebugLinkImage(void);

extern void Libultra_DispatchDebugLinkCallback(void);

/* Sends a 0x80 command followed by two NUL-terminated strings over the handshake port and reads back a big-endian 32-bit word, returning it (zero on failure). Adapted from Libultra_ExchangeDebugLinkWord with the command 0x85 changed to 0x80, the 32-bit argument replaced by the two strings and the read retry loop removed. */





extern void Libultra_ReadDebugLinkBlock(s32, s32, void *);

extern void Libultra_WriteDebugLinkBlock(void *, s32);

extern s32 g_debugLinkCallbackAddress;

void Libultra_RunDebugLinkCommands(void) {
    CommandState state;
    u8 *command;
    u8 *address;
    u8 *callback;
    u8 *output;
    u32 word;
    u8 enabledControl;

    Libultra_InitDebugLink();
    enabledControl = g_debugLinkTransferControl | 0x40;
    g_debugLinkTransferControl = enabledControl;
    while (osPiGetStatus() & 3) {
    }
    DEBUG_LINK_TRANSFER_REGISTER = enabledControl;

    command = &state.command;
    address = &state.address.byte;
    callback = &state.callback.byte;
    output = &state.output.byte;

    while (Libultra_ReadDebugLinkByte(command) != 0) {
        if (state.command != 0x10) {
            continue;
        }
        if (Libultra_WriteDebugLinkByte(0x11) == 0) {
            continue;
        }
        if (Libultra_ReadDebugLinkByte(command) == 0) {
            continue;
        }
        switch (state.command) {
        case 0x20:
            Libultra_SendDebugLinkIdentification();
            break;
        case 0x43:
            Libultra_ReceiveDebugLinkMemory();
            break;
        case 0x47:
            Libultra_SendDebugLinkMemory();
            break;
        case 0x44:
            Libultra_ReadDebugLinkByte(address);
            if (g_debugLinkTransferFailed != 0) break;
            word = state.address.byte << 8;
            Libultra_ReadDebugLinkByte(address);
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.address.byte;
            Libultra_ReadDebugLinkByte(address);
            word <<= 8;
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.address.byte;
            Libultra_ReadDebugLinkByte(address);
            word <<= 8;
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.address.byte;
            state.address.word = word;
            Libultra_WriteDebugLinkByte(*(u8 *)word);
            break;
        case 0x45:
            Libultra_ReadDebugLinkHalfword();
            break;
        case 0x46:
            Libultra_ReadDebugLinkWord();
            break;
        case 0x22:
            Libultra_ReadDebugLinkByte(callback);
            if (g_debugLinkTransferFailed != 0) break;
            word = state.callback.byte << 8;
            Libultra_ReadDebugLinkByte(callback);
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.callback.byte;
            Libultra_ReadDebugLinkByte(callback);
            word <<= 8;
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.callback.byte;
            Libultra_ReadDebugLinkByte(callback);
            word <<= 8;
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.callback.byte;
            state.callback.word = word;
            if (word != 0) {
                osSetIntMask(1);
                osWritebackDCacheAll();
                osInvalICache(0x80000000, 0x800000);
                ((void (*)(void))word)();
            }
            break;
        case 0x40:
            Libultra_ReadDebugLinkByte(output);
            if (g_debugLinkTransferFailed != 0) break;
            word = state.output.byte << 8;
            Libultra_ReadDebugLinkByte(output);
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.output.byte;
            Libultra_ReadDebugLinkByte(output);
            word <<= 8;
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.output.byte;
            Libultra_ReadDebugLinkByte(output);
            word <<= 8;
            if (g_debugLinkTransferFailed != 0) break;
            word |= state.output.byte;
            state.output.word = word;
            Libultra_ReadDebugLinkByte(&state.output.value);
            if (g_debugLinkTransferFailed == 0) {
                *(u8 *)state.output.word = state.output.value;
            }
            break;
        case 0x41:
            Libultra_WriteDebugLinkHalfword();
            break;
        case 0x42:
            Libultra_WriteDebugLinkWord();
            break;
        case 0x18:
            Libultra_ReceiveDebugLinkImage();
            break;
        case 0x23:
            Libultra_DispatchDebugLinkCallback();
            break;
        }
    }
}

u32 Libultra_ExchangeDebugLinkStrings(u8 *firstString, u8 *secondString) {
    Response response;
    s32 timeout;
    s32 retries;
    u8 initial_control;
    s32 expected;
    u8 mask;
    u8 final_control;
    u8 cleanup_control;
    s32 final_expected;
    u8 final_mask;
    u32 word;
    s32 valid;
    u8 *byte;
    u8 *second;
    u8 second_c;
    u8 *first;
    u8 first_c;

    response.output = 0;
    g_debugLinkTransferFailed = 0;
    g_debugLinkRetryLimit = 100;
    initial_control = g_debugLinkHandshakeControl | 4;
    g_debugLinkHandshakeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 2;
    DEBUG_LINK_HANDSHAKE_REGISTER = initial_control;
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
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x10);
    valid = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&response.handshake);
        if (g_debugLinkTransferFailed == 0) {
            valid = response.handshake == 0x11;
        }
    }
    if (valid == 0) {
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x80);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    first = firstString;
    do {
        first_c = *first++;
        Libultra_WriteDebugLinkByte(first_c);
        if (g_debugLinkTransferFailed != 0) goto cleanup;
    } while (first_c != 0);

    second = secondString;
    do {
        second_c = *second++;
        Libultra_WriteDebugLinkByte(second_c);
        if (g_debugLinkTransferFailed != 0) goto cleanup;
    } while (second_c != 0);

    byte = &response.byte;
    Libultra_ReadDebugLinkByte(byte);
    if (g_debugLinkTransferFailed == 0) {
        word = response.byte << 8;
        Libultra_ReadDebugLinkByte(byte);
        if (g_debugLinkTransferFailed == 0) {
            word |= response.byte;
            Libultra_ReadDebugLinkByte(byte);
            word <<= 8;
            if (g_debugLinkTransferFailed == 0) {
                word |= response.byte;
                Libultra_ReadDebugLinkByte(byte);
                word <<= 8;
                if (g_debugLinkTransferFailed == 0) {
                    word |= response.byte;
                    response.output = word;
                }
            }
        }
    }
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    final_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = final_control;
    do {
    } while (osPiGetStatus() & 3);
    final_mask = 0;
    final_expected = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    DEBUG_LINK_HANDSHAKE_REGISTER = final_control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & final_expected) == final_mask) {
            goto cleanup;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;

cleanup:
    cleanup_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = cleanup_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = cleanup_control;
    g_debugLinkRetryLimit = 1;
    return response.output;
}

s32 Libultra_SendDebugLinkCommand81(s32 value) {
    TransferScratch scratch;
    s32 timeout;
    s32 retries;
    u8 initial_control;
    s32 expected;
    u8 mask;
    u8 final_control;
    u8 cleanup_control;
    s32 final_expected;
    u8 final_mask;
    s32 valid;

    g_debugLinkTransferFailed = 0;
    g_debugLinkRetryLimit = 100;
    initial_control = g_debugLinkHandshakeControl | 4;
    g_debugLinkHandshakeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 2;
    DEBUG_LINK_HANDSHAKE_REGISTER = initial_control;
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
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x10);
    valid = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&scratch.response);
        if (g_debugLinkTransferFailed == 0) {
            valid = scratch.response == 0x11;
        }
    }
    if (valid == 0) {
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x81);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((u32)value >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)value >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)value >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(value & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    final_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = final_control;
    do {
    } while (osPiGetStatus() & 3);
    final_mask = 0;
    final_expected = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    DEBUG_LINK_HANDSHAKE_REGISTER = final_control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & final_expected) == final_mask) {
            goto cleanup;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;

cleanup:
    cleanup_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = cleanup_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = cleanup_control;
    g_debugLinkRetryLimit = 1;
    return 0;
}

s32 Libultra_RequestDebugLinkBlock(void *stream, s32 elementBytes, s32 elementCount, s32 requestCode) {
    TransferScratch scratch;
    s32 timeout;
    s32 retries;
    s32 attempts;
    u8 initial_control;
    s32 expected;
    u8 mask;
    u8 final_control;
    u8 cleanup_control;
    s32 final_expected;
    u8 final_mask;
    s32 product;
    s32 valid;

    g_debugLinkTransferFailed = 0;
    attempts = 100;
    g_debugLinkRetryLimit = attempts;
    initial_control = g_debugLinkHandshakeControl | 4;
    g_debugLinkHandshakeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 2;
    DEBUG_LINK_HANDSHAKE_REGISTER = initial_control;
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
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x10);
    valid = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&scratch.response);
        if (g_debugLinkTransferFailed == 0) {
            valid = scratch.response == 0x11;
        }
    }
    if (valid == 0) {
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x82);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((u32)requestCode >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)requestCode >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)requestCode >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(requestCode & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    product = elementBytes * elementCount;
    Libultra_WriteDebugLinkByte((u32)product >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)product >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)product >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(product & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    do {
        g_debugLinkTransferFailed = 0;
        Libultra_ReadDebugLinkByte(&scratch.status);
    } while (attempts-- > 0 && g_debugLinkTransferFailed != 0);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_ReadDebugLinkBlock(stream, elementBytes * elementCount, &scratch.output);

    final_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = final_control;
    do {
    } while (osPiGetStatus() & 3);
    final_mask = 0;
    final_expected = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    DEBUG_LINK_HANDSHAKE_REGISTER = final_control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & final_expected) == final_mask) {
            goto cleanup;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;

cleanup:
    cleanup_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = cleanup_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = cleanup_control;
    g_debugLinkRetryLimit = 1;
    return elementCount;
}

s32 Libultra_SubmitDebugLinkBlock(void *stream, s32 elementBytes, s32 elementCount, s32 requestCode) {
    TransferScratch scratch;
    s32 timeout;
    s32 retries;
    s32 attempts;
    u8 initial_control;
    s32 expected;
    u8 mask;
    u8 final_control;
    u8 cleanup_control;
    s32 final_expected;
    u8 final_mask;
    s32 product;
    s32 valid;

    g_debugLinkTransferFailed = 0;
    attempts = 100;
    g_debugLinkRetryLimit = attempts;
    initial_control = g_debugLinkHandshakeControl | 4;
    g_debugLinkHandshakeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 2;
    DEBUG_LINK_HANDSHAKE_REGISTER = initial_control;
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
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x10);
    valid = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&scratch.response);
        if (g_debugLinkTransferFailed == 0) {
            valid = scratch.response == 0x11;
        }
    }
    if (valid == 0) {
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x83);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((u32)requestCode >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)requestCode >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)requestCode >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(requestCode & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    product = elementBytes * elementCount;
    Libultra_WriteDebugLinkByte((u32)product >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)product >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)product >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(product & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkBlock(stream, product);

    do {
        g_debugLinkTransferFailed = 0;
        Libultra_ReadDebugLinkByte(&scratch.status);
    } while (attempts-- > 0 && g_debugLinkTransferFailed != 0);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    final_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = final_control;
    do {
    } while (osPiGetStatus() & 3);
    final_mask = 0;
    final_expected = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    DEBUG_LINK_HANDSHAKE_REGISTER = final_control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & final_expected) == final_mask) {
            goto cleanup;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;

cleanup:
    cleanup_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = cleanup_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = cleanup_control;
    g_debugLinkRetryLimit = 1;
    return elementCount;
}

u32 Libultra_ExchangeDebugLinkWords(u32 firstWord, u32 secondWord, u32 thirdWord) {
    Response response;
    s32 timeout;
    s32 retries;
    s32 attempts;
    u8 initial_control;
    s32 expected;
    u8 mask;
    u8 final_control;
    u8 cleanup_control;
    s32 final_expected;
    u8 final_mask;
    u32 word;
    s32 valid;
    u8 *byte;
    u32 *output;

    response.output = 0;
    g_debugLinkTransferFailed = 0;
    attempts = 100;
    g_debugLinkRetryLimit = attempts;
    initial_control = g_debugLinkHandshakeControl | 4;
    g_debugLinkHandshakeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 2;
    DEBUG_LINK_HANDSHAKE_REGISTER = initial_control;
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
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x10);
    valid = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&response.handshake);
        if (g_debugLinkTransferFailed == 0) {
            valid = response.handshake == 0x11;
        }
    }
    if (valid == 0) {
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x84);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(firstWord >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((firstWord >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((firstWord >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(firstWord & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(secondWord >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((secondWord >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((secondWord >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(secondWord & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(thirdWord >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((thirdWord >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((thirdWord >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(thirdWord & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    output = &response.output;
    byte = &response.byte;
    do {
        g_debugLinkTransferFailed = 0;
        Libultra_ReadDebugLinkByte(byte);
        if (g_debugLinkTransferFailed == 0) {
            word = response.byte << 8;
            Libultra_ReadDebugLinkByte(byte);
            if (g_debugLinkTransferFailed == 0) {
                word |= response.byte;
                Libultra_ReadDebugLinkByte(byte);
                word <<= 8;
                if (g_debugLinkTransferFailed == 0) {
                    word |= response.byte;
                    Libultra_ReadDebugLinkByte(byte);
                    word <<= 8;
                    if (g_debugLinkTransferFailed == 0) {
                        word |= response.byte;
                        *output = word;
                    }
                }
            }
        }
    } while (attempts-- > 0 && g_debugLinkTransferFailed != 0);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    final_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = final_control;
    do {
    } while (osPiGetStatus() & 3);
    final_mask = 0;
    final_expected = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    DEBUG_LINK_HANDSHAKE_REGISTER = final_control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & final_expected) == final_mask) {
            goto cleanup;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;

cleanup:
    cleanup_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = cleanup_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = cleanup_control;
    g_debugLinkRetryLimit = 1;
    return response.output;
}

u32 Libultra_ExchangeDebugLinkWord(u32 requestWord) {
    Response response;
    s32 timeout;
    s32 retries;
    s32 attempts;
    u8 initial_control;
    s32 expected;
    u8 mask;
    u8 final_control;
    u8 cleanup_control;
    s32 final_expected;
    u8 final_mask;
    u32 word;
    s32 valid;
    u8 *byte;
    u32 *output;

    response.output = 0;
    g_debugLinkTransferFailed = 0;
    attempts = 100;
    g_debugLinkRetryLimit = attempts;
    initial_control = g_debugLinkHandshakeControl | 4;
    g_debugLinkHandshakeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 2;
    DEBUG_LINK_HANDSHAKE_REGISTER = initial_control;
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
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x10);
    valid = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&response.handshake);
        if (g_debugLinkTransferFailed == 0) {
            valid = response.handshake == 0x11;
        }
    }
    if (valid == 0) {
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x85);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(requestWord >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((requestWord >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((requestWord >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(requestWord & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    output = &response.output;
    byte = &response.byte;
    do {
        g_debugLinkTransferFailed = 0;
        Libultra_ReadDebugLinkByte(byte);
        if (g_debugLinkTransferFailed == 0) {
            word = response.byte << 8;
            Libultra_ReadDebugLinkByte(byte);
            if (g_debugLinkTransferFailed == 0) {
                word |= response.byte;
                Libultra_ReadDebugLinkByte(byte);
                word <<= 8;
                if (g_debugLinkTransferFailed == 0) {
                    word |= response.byte;
                    Libultra_ReadDebugLinkByte(byte);
                    word <<= 8;
                    if (g_debugLinkTransferFailed == 0) {
                        word |= response.byte;
                        *output = word;
                    }
                }
            }
        }
    } while (attempts-- > 0 && g_debugLinkTransferFailed != 0);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    final_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = final_control;
    do {
    } while (osPiGetStatus() & 3);
    final_mask = 0;
    final_expected = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    DEBUG_LINK_HANDSHAKE_REGISTER = final_control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & final_expected) == final_mask) {
            goto cleanup;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;

cleanup:
    cleanup_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = cleanup_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = cleanup_control;
    g_debugLinkRetryLimit = 1;
    return response.output;
}

s32 Libultra_SendDebugLinkControlWord(s32 value) {
    TransferScratch scratch;
    s32 timeout;
    s32 retries;
    u8 initial_control;
    s32 expected;
    u8 mask;
    u8 final_control;
    u8 cleanup_control;
    s32 final_expected;
    u8 final_mask;
    s32 valid;

    g_debugLinkTransferFailed = 0;
    g_debugLinkRetryLimit = 100;
    initial_control = g_debugLinkHandshakeControl | 4;
    g_debugLinkHandshakeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 2;
    DEBUG_LINK_HANDSHAKE_REGISTER = initial_control;
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
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x10);
    valid = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&scratch.response);
        if (g_debugLinkTransferFailed == 0) {
            valid = scratch.response == 0x11;
        }
    }
    if (valid == 0) {
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0xC0);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte((u32)value >> 24);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)value >> 16) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(((u32)value >> 8) & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    Libultra_WriteDebugLinkByte(value & 0xFF);
    if (g_debugLinkTransferFailed != 0) goto cleanup;

    final_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = final_control;
    do {
    } while (osPiGetStatus() & 3);
    final_mask = 0;
    final_expected = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    DEBUG_LINK_HANDSHAKE_REGISTER = final_control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & final_expected) == final_mask) {
            goto cleanup;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;

cleanup:
    cleanup_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = cleanup_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = cleanup_control;
    g_debugLinkRetryLimit = 1;
    return 0;
}

s32 Libultra_SendDebugLinkControlString(u8 *text) {
    u8 *p;
    u8 c;
    TransferScratch scratch;
    s32 timeout;
    s32 retries;
    u8 initial_control;
    s32 expected;
    u8 mask;
    u8 final_control;
    u8 cleanup_control;
    s32 final_expected;
    u8 final_mask;
    s32 valid;

    g_debugLinkTransferFailed = 0;
    g_debugLinkRetryLimit = 100;
    initial_control = g_debugLinkHandshakeControl | 4;
    g_debugLinkHandshakeControl = initial_control;
    do {
    } while (osPiGetStatus() & 3);

    mask = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    expected = 2;
    DEBUG_LINK_HANDSHAKE_REGISTER = initial_control;
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
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0x10);
    valid = 0;
    if (g_debugLinkTransferFailed == 0) {
        Libultra_ReadDebugLinkByte(&scratch.response);
        if (g_debugLinkTransferFailed == 0) {
            valid = scratch.response == 0x11;
        }
    }
    if (valid == 0) {
        goto cleanup;
    }
    Libultra_WriteDebugLinkByte(0xC1);
    if (g_debugLinkTransferFailed != 0) goto cleanup;
    p = text;
    do {
        c = *p++;
        Libultra_WriteDebugLinkByte(c);
        if (g_debugLinkTransferFailed != 0) goto cleanup;
    } while (c != 0);

    final_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = final_control;
    do {
    } while (osPiGetStatus() & 3);
    final_mask = 0;
    final_expected = 2;
    timeout = 0x4E20;
    retries = g_debugLinkRetryLimit;
    DEBUG_LINK_HANDSHAKE_REGISTER = final_control;
    do {
        do {
        } while (osPiGetStatus() & 3);
        if ((DEBUG_LINK_TRANSMIT_STATUS_BYTE & final_expected) == final_mask) {
            goto cleanup;
        }
        if (timeout-- == 0) {
            retries--;
            timeout = 0x4E20;
        }
    } while (retries > 0);
    g_debugLinkTransferFailed = 1;

cleanup:
    cleanup_control = g_debugLinkHandshakeControl & 0xFB;
    g_debugLinkHandshakeControl = cleanup_control;
    do {
    } while (osPiGetStatus() & 3);
    DEBUG_LINK_HANDSHAKE_REGISTER = cleanup_control;
    g_debugLinkRetryLimit = 1;
    return 0;
}

void Libultra_EmptyDebugLinkHook(void) {
}

void Libultra_SetDebugLinkCallback(int callbackAddress) {
    g_debugLinkCallbackAddress = callbackAddress;
}

s32 Libultra_ReceiveDebugLinkHalfword(u16 *halfwordOut) {
    u8 receivedByte;
    s32 result;
    u16 high;

    Libultra_ReadDebugLinkByte(&receivedByte);
    result = 0;
    if (g_debugLinkTransferFailed == 0) {
        high = receivedByte << 8;
        Libultra_ReadDebugLinkByte(&receivedByte);
        if (g_debugLinkTransferFailed == 0) {
            result = 1;
            *halfwordOut = high | receivedByte;
        }
    }
    return result;
}

s32 Libultra_ReceiveDebugLinkWord(s32 *wordOut) {
    u8 receivedByte;
    s32 result;
    s32 word;

    Libultra_ReadDebugLinkByte(&receivedByte);
    result = 0;
    if (g_debugLinkTransferFailed == 0) {
        word = receivedByte << 8;
        Libultra_ReadDebugLinkByte(&receivedByte);
        if (g_debugLinkTransferFailed == 0) {
            word |= receivedByte;
            Libultra_ReadDebugLinkByte(&receivedByte);
            word <<= 8;
            if (g_debugLinkTransferFailed == 0) {
                word |= receivedByte;
                Libultra_ReadDebugLinkByte(&receivedByte);
                word <<= 8;
                if (g_debugLinkTransferFailed == 0) {
                    result = 1;
                    word |= receivedByte;
                    *wordOut = word;
                }
            }
        }
    }
    return result;
}

s32 Libultra_ReceiveDebugLinkString(u8 *textOut, s32 capacity) {
    s32 result;
    s32 i;
    u8 value;

    result = 0;
    i = 0;
    while (1) {
        Libultra_ReadDebugLinkByte(&value);
        if (g_debugLinkTransferFailed != 0) {
            break;
        }
        if (i < capacity) {
            textOut[i] = value;
        }
        i += 1;
        if (value != 0) {
            continue;
        }
        result = 1;
        break;
    }
    return result;
}

s32 Libultra_SendDebugLinkHalfword(u32 value)
{
  s32 result;
  result = 0;
  Libultra_WriteDebugLinkByte((value >> 8) & 0xFF);
  if (g_debugLinkTransferFailed == 0)
  {
    Libultra_WriteDebugLinkByte(value & 0xFF);
    result = g_debugLinkTransferFailed == 0;
  }
  return result;
}

s32 Libultra_SendDebugLinkWord(u32 value) {
    s32 result;

    result = 0;
    Libultra_WriteDebugLinkByte(value >> 0x18);
    if (g_debugLinkTransferFailed == 0) {
        Libultra_WriteDebugLinkByte((value >> 0x10) & 0xFF);
        if (g_debugLinkTransferFailed == 0) {
            Libultra_WriteDebugLinkByte((value >> 8) & 0xFF);
            if (g_debugLinkTransferFailed == 0) {
                Libultra_WriteDebugLinkByte(value & 0xFF);
                result = g_debugLinkTransferFailed == 0;
            }
        }
    }
    return result;
}
#endif
