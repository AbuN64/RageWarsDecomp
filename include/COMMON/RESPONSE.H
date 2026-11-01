#ifndef COMMON_RESPONSE_H
#define COMMON_RESPONSE_H
#include "TYPES.H"


struct Response;
struct Response {
    u8 handshake;
    u8 pad11[3];
    u32 output;
    u8 byte;
};

struct TransferScratch;
typedef struct TransferScratch TransferScratch;


struct WriteWord;
typedef struct WriteWord WriteWord;



struct WordAndByteResult;
typedef struct WordAndByteResult WordAndByteResult;


struct TransferScratch;
struct TransferScratch {
    u8 response;
    u8 status;
    u16 pad;
    s32 output;
};

struct WriteWord;
struct WriteWord {
    u32 word;
    u8 byte;
    u8 value;
};

struct WordAndByteResult;
struct WordAndByteResult {
    u32 word;
    u8 byte;
};

struct CommandState;
struct CommandState {
    u8 command;
    u8 pad01[3];
    WordAndByteResult address;
    WordAndByteResult callback;
    WriteWord output;
};

struct CommandState;
typedef struct CommandState CommandState;

struct ReadHalfword;
typedef struct ReadHalfword ReadHalfword;

struct ReadHalfword;
struct ReadHalfword {
    s32 word;
    u8 byte;
    u16 value;
    u8 next_byte;
};




extern unsigned char g_debugLinkReceivedDataByte;


extern int g_debugLinkImageByteCount;


extern int g_debugLinkImagePending;




struct Response;
typedef struct Response Response;


extern int g_debugLinkImageLoadAddress;
#endif
