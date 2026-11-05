#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of ECT_C:/Projects/DM/n64/Source/Engine/Cache/heap.cpp. */
char g_heapStrEctCProjectsDmN64[52] = "ECT_C:/Projects/DM/n64/Source/Engine/Cache/heap.cpp";
char g_heapStrHeapAlignment4[20] = "HEAP_ALIGNMENT >= 4";
char g_heapStrLengthSizeofCheapblock[32] = "Length >= sizeof(CHeapBlock)";
char g_heapStrU32PaddressHeapAlignment1[44] = "!(((u32) pAddress) & (HEAP_ALIGNMENT - 1))";
char g_heapStrPaddress[12] = "pAddress";
char g_heapStrPblockPusedlast[20] = "pBlock->pUsedLast";
char g_heapStrPblockPthisPusedhead[28] = "pBlock != pThis->pUsedHead";
char g_heapStrPblockPfreelastPblockPfreelastPfreenext[64] = "!pBlock->pFreeLast || (pBlock->pFreeLast->pFreeNext == pBlock)";
char g_heapStrPblockPfreenextPblockPfreenextPfreelast[64] = "!pBlock->pFreeNext || (pBlock->pFreeNext->pFreeLast == pBlock)";
char g_heapStrPblockPusedlastPblockPusedlastPusednext[64] = "!pBlock->pUsedLast || (pBlock->pUsedLast->pUsedNext == pBlock)";
char g_heapStrPblockPusednextPblockPusednextPusedlast[64] = "!pBlock->pUsedNext || (pBlock->pUsedNext->pUsedLast == pBlock)";
char g_heapStrPblockUsedHeapHeaderSize[36] = "pBlock->Used >= HEAP_HEADER_SIZE";
char g_heapStrPusedlastPfreelast[24] = "!pUsedLast->pFreeLast";
#endif
