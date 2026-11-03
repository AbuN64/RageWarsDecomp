#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of ECT_C:/Projects/DM/n64/Source/Engine/Cache/heap.cpp. */
char g_earlierHeapStrEctCProjectsDmN64[52] = "ECT_C:/Projects/DM/n64/Source/Engine/Cache/heap.cpp";
char g_earlierHeapStrHeapAlignment4[20] = "HEAP_ALIGNMENT >= 4";
char g_earlierHeapStrLengthSizeofCheapblock[32] = "Length >= sizeof(CHeapBlock)";
char g_earlierHeapStrU32PaddressHeapAlignment1[44] = "!(((u32) pAddress) & (HEAP_ALIGNMENT - 1))";
char g_earlierHeapStrPaddress[12] = "pAddress";
char g_earlierHeapStrPblockPusedlast[20] = "pBlock->pUsedLast";
char g_earlierHeapStrPblockPthisPusedhead[28] = "pBlock != pThis->pUsedHead";
char g_earlierHeapStrPblockPfreelastPblockPfreelastPfreenext[64] = "!pBlock->pFreeLast || (pBlock->pFreeLast->pFreeNext == pBlock)";
char g_earlierHeapStrPblockPfreenextPblockPfreenextPfreelast[64] = "!pBlock->pFreeNext || (pBlock->pFreeNext->pFreeLast == pBlock)";
char g_earlierHeapStrPblockPusedlastPblockPusedlastPusednext[64] = "!pBlock->pUsedLast || (pBlock->pUsedLast->pUsedNext == pBlock)";
char g_earlierHeapStrPblockPusednextPblockPusednextPusedlast[64] = "!pBlock->pUsedNext || (pBlock->pUsedNext->pUsedLast == pBlock)";
char g_earlierHeapStrPblockUsedHeapHeaderSize[36] = "pBlock->Used >= HEAP_HEADER_SIZE";
char g_earlierHeapStrPusedlastPfreelast[24] = "!pUsedLast->pFreeLast";
#endif
