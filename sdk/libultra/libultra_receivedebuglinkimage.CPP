#include "../include/LIBC.H"
#include "../include/libgultra_inferred/LIBULTRA_WRITEDEBUGLINKBYTE.H"
#include "COMMON/RESPONSE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "../include/libgultra.h"

#if defined(VERSION_US_REV1)

extern s32 (*g_debugLinkCallbackAddress)(s32 receivedWord);

extern s32 Libultra_ReadDebugLinkByte(u8 *);

extern u8 g_debugLinkImageFormatText;

extern void Libultra_WriteDebugLinkBlock(s32, s32);



extern void Libultra_ReadDebugLinkBlock(s32, s32, void *);

s32 Libultra_DispatchDebugLinkCallback(void) {
    ReadWord first;
    s32 word;
    u32 value;

    first.word = 0;
    Libultra_ReadDebugLinkByte(&first.byte);
    value = 0;
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
                    if (g_debugLinkCallbackAddress != 0) {
                        value = g_debugLinkCallbackAddress(first.word);
                    }
                    Libultra_WriteDebugLinkByte(value >> 24);
                    if (g_debugLinkTransferFailed == 0) {
                        Libultra_WriteDebugLinkByte((value >> 16) & 0xFF);
                        if (g_debugLinkTransferFailed == 0) {
                            Libultra_WriteDebugLinkByte((value >> 8) & 0xFF);
                            if (g_debugLinkTransferFailed == 0) {
                                Libultra_WriteDebugLinkByte(value & 0xFF);
                            }
                        }
                    }
                    if (g_debugLinkTransferFailed == 0) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

s32 Libultra_SendDebugLinkIdentification(void) {
    WordAndByteResult first;
    u32 word;
    s32 result;
    u32 transferLength;
    u8 *data;

    result = 0;
    Libultra_ReadDebugLinkByte(&first.byte);
    data = &g_debugLinkImageFormatText;
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
                    if (first.word >= (u32)Libc_StringLength((const char *)data)) {
                        transferLength = Libc_StringLength((const char *)data);
                    } else {
                        transferLength = first.word;
                    }
                    first.word = transferLength;
                    Libultra_WriteDebugLinkByte(transferLength >> 24);
                    if (g_debugLinkTransferFailed == 0) {
                        Libultra_WriteDebugLinkByte((transferLength >> 16) & 0xFF);
                        if (g_debugLinkTransferFailed == 0) {
                            Libultra_WriteDebugLinkByte((transferLength >> 8) & 0xFF);
                            if (g_debugLinkTransferFailed == 0) {
                                Libultra_WriteDebugLinkByte(transferLength & 0xFF);
                            }
                        }
                    }
                    Libultra_WriteDebugLinkBlock(data, first.word);
                    if (g_debugLinkTransferFailed == 0) {
                        result = 1;
                    }
                }
            }
        }
    }
    return result;
}

s32 Libultra_WriteDebugLinkHalfword(void) {
    ReadHalfword first;
    s32 word;
    s32 result;
    u16 value;

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
                    Libultra_ReadDebugLinkByte(&first.next_byte);
                    if (g_debugLinkTransferFailed == 0) {
                        value = first.next_byte << 8;
                        Libultra_ReadDebugLinkByte(&first.next_byte);
                        if (g_debugLinkTransferFailed == 0) {
                            first.value = value | first.next_byte;
                            result = 1;
                            *(u16 *)first.word = first.value;
                        }
                    }
                }
            }
        }
    }
    return result;
}

s32 Libultra_WriteDebugLinkWord(void) {
    ReadWord first;
    ReadWord second;
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
                    Libultra_ReadDebugLinkByte(&second.byte);
                    if (g_debugLinkTransferFailed == 0) {
                        word = second.byte << 8;
                        Libultra_ReadDebugLinkByte(&second.byte);
                        if (g_debugLinkTransferFailed == 0) {
                            word |= second.byte;
                            Libultra_ReadDebugLinkByte(&second.byte);
                            word <<= 8;
                            if (g_debugLinkTransferFailed == 0) {
                                word |= second.byte;
                                Libultra_ReadDebugLinkByte(&second.byte);
                                word <<= 8;
                                if (g_debugLinkTransferFailed == 0) {
                                    word |= second.byte;
                                    second.word = word;
                                    result = 1;
                                    *(s32 *)first.word = second.word;
                                }
                            }
                            goto block_9;
                        }
                    }
                } else {
                    goto block_9;
                }
            }
block_9:
            ;
        }
    }
    return result;
}

s32 Libultra_ReadDebugLinkHalfword(void) {
    ReadWord first;
    s32 word;
    s32 result;
    u16 value;

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
                    value = *(u16 *)first.word;
                    Libultra_WriteDebugLinkByte(value >> 8);
                    if (g_debugLinkTransferFailed == 0) {
                        Libultra_WriteDebugLinkByte(value & 0xFF);
                        result = g_debugLinkTransferFailed == 0;
                    }
                }
            }
        }
    }
    return result;
}

s32 Libultra_ReadDebugLinkWord(void) {
    ReadWord first;
    s32 word;
    s32 result;
    u32 value;

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
                    value = *(u32 *)first.word;
                    Libultra_WriteDebugLinkByte(value >> 24);
                    if (g_debugLinkTransferFailed == 0) {
                        Libultra_WriteDebugLinkByte((value >> 16) & 0xFF);
                        if (g_debugLinkTransferFailed == 0) {
                            Libultra_WriteDebugLinkByte((value >> 8) & 0xFF);
                            if (g_debugLinkTransferFailed == 0) {
                                Libultra_WriteDebugLinkByte(value & 0xFF);
                                result = g_debugLinkTransferFailed == 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

s32 Libultra_ReceiveDebugLinkMemory(void) {
    ReadWord first;
    ReadWord second;
    s32 word;
    s32 succeeded;
    s32 output;

    Libultra_ReadDebugLinkByte(&first.byte);
    succeeded = 0;
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
                    Libultra_ReadDebugLinkByte(&second.byte);
                    if (g_debugLinkTransferFailed == 0) {
                        word = second.byte << 8;
                        Libultra_ReadDebugLinkByte(&second.byte);
                        if (g_debugLinkTransferFailed == 0) {
                            word |= second.byte;
                            Libultra_ReadDebugLinkByte(&second.byte);
                            word <<= 8;
                            if (g_debugLinkTransferFailed == 0) {
                                word |= second.byte;
                                Libultra_ReadDebugLinkByte(&second.byte);
                                word <<= 8;
                                if (g_debugLinkTransferFailed == 0) {
                                    word |= second.byte;
                                    second.word = word;
                                    Libultra_ReadDebugLinkBlock(first.word, word, &output);
                                    succeeded = g_debugLinkTransferFailed == 0;
                                }
                            }
                            goto block_9;
                        }
                    }
                } else {
                    goto block_9;
                }
            }
block_9:
            ;
        }
    }
    return succeeded;
}

s32 Libultra_SendDebugLinkMemory(void) {
    ReadWord first;
    ReadWord second;
    s32 word;
    s32 succeeded;

    Libultra_ReadDebugLinkByte(&first.byte);
    succeeded = 0;
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
                    Libultra_ReadDebugLinkByte(&second.byte);
                    if (g_debugLinkTransferFailed == 0) {
                        word = second.byte << 8;
                        Libultra_ReadDebugLinkByte(&second.byte);
                        if (g_debugLinkTransferFailed == 0) {
                            word |= second.byte;
                            Libultra_ReadDebugLinkByte(&second.byte);
                            word <<= 8;
                            if (g_debugLinkTransferFailed == 0) {
                                word |= second.byte;
                                Libultra_ReadDebugLinkByte(&second.byte);
                                word <<= 8;
                                if (g_debugLinkTransferFailed == 0) {
                                    word |= second.byte;
                                    second.word = word;
                                    Libultra_WriteDebugLinkBlock(first.word, word);
                                    succeeded = g_debugLinkTransferFailed == 0;
                                }
                            }
                            goto block_9;
                        }
                    }
                } else {
                    goto block_9;
                }
            }
block_9:
            ;
        }
    }
    return succeeded;
}

s32 Libultra_ReceiveDebugLinkImage(void) {
    ReadWord first;
    ReadWord second;
    s32 word;
    s32 succeeded;
    s32 output;
    s32 addr;

    Libultra_ReadDebugLinkByte(&first.byte);
    succeeded = 0;
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
                    Libultra_ReadDebugLinkByte(&second.byte);
                    if (g_debugLinkTransferFailed == 0) {
                        word = second.byte << 8;
                        Libultra_ReadDebugLinkByte(&second.byte);
                        if (g_debugLinkTransferFailed == 0) {
                            word |= second.byte;
                            Libultra_ReadDebugLinkByte(&second.byte);
                            word <<= 8;
                            if (g_debugLinkTransferFailed == 0) {
                                word |= second.byte;
                                Libultra_ReadDebugLinkByte(&second.byte);
                                word <<= 8;
                                if (g_debugLinkTransferFailed == 0) {
                                    word |= second.byte;
                                    second.word = word;
                                    addr = 0x80100000;
                                    Libultra_ReadDebugLinkBlock(addr, first.word, &output);
                                    if (g_debugLinkTransferFailed == 0 && second.word == output) {
                                        g_debugLinkImagePending = 1;
                                        succeeded = 1;
                                        g_debugLinkImageLoadAddress = 0x80100000;
                                        g_debugLinkImageByteCount = first.word;
                                    }
                                }
                            }
                            goto block_9;
                        }
                    }
                } else {
                    goto block_9;
                }
            }
block_9:
            ;
        }
    }
    return succeeded;
}
#endif
