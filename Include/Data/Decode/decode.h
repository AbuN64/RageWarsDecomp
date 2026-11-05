#ifndef DATA_DECODE_DECODE_H
#define DATA_DECODE_DECODE_H
#include "types.h"
#include "Data/rest_source_records.h"
#include "Decoder/gfxdata.h"
typedef struct Huffman5ZeroRuns {
    char description[16];
    u32 words[546];
} Huffman5ZeroRuns;
extern Huffman5ZeroRuns g_huffmanShortZeroRuns;
typedef struct Huffman9ZeroRuns {
    char description[16];
    u32 words[986];
} Huffman9ZeroRuns;
extern Huffman9ZeroRuns g_huffmanLongZeroRuns;
typedef struct HuffmanSingleZeroRuns {
    char description[16];
    u32 words[106];
} HuffmanSingleZeroRuns;
extern HuffmanSingleZeroRuns g_huffmanSingleZeroRuns;
#endif
