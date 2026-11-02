#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_huffmanDeltaFiveZeroRunNodes[];
extern char g_huffmanDeltaNineZeroRunNodes[];
extern char g_huffmanDeltaSingleZeroRunNodes[];
extern char g_huffmanFiveZeroRuns[];
extern char g_huffmanNineZeroRuns[];
extern char g_huffmanSignedSmallNodes[];
extern char g_huffmanSingleZeroRuns[];

#if defined(VERSION_US_REV1)
Resthuffman_signed7_single_dictionaryLayout307 huffman_signed7_single_dictionary = {
    { -127, 127, 255, 16, 257, 256, 1 },
    { (void *)&g_huffmanSingleZeroRuns, (void *)&g_huffmanDeltaSingleZeroRunNodes },
    { -127, 127, 255, 16, 261, 256, 5 },
    { (void *)&g_huffmanFiveZeroRuns, (void *)&g_huffmanDeltaFiveZeroRunNodes },
    { -127, 127, 255, 16, 265, 256, 9 },
    { (void *)&g_huffmanNineZeroRuns, (void *)&g_huffmanDeltaNineZeroRunNodes },
    { -64, 64, -1, 16, -1, 129, 0 },
    { 0, (void *)&g_huffmanSignedSmallNodes },
};
#endif
