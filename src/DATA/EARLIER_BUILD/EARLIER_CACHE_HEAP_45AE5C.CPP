#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of ECT_C:/Projects/DM/n64/Source/Engine/Cache/heap.cpp. */
char g_earlierHeapStr_45AE5C[52] = "ECT_C:/Projects/DM/n64/Source/Engine/Cache/heap.cpp";
char g_earlierHeapStr_45AE90[20] = "HEAP_ALIGNMENT >= 4";
char g_earlierHeapStr_45AEA4[32] = "Length >= sizeof(CHeapBlock)";
char g_earlierHeapStr_45AEC4[44] = "!(((u32) pAddress) & (HEAP_ALIGNMENT - 1))";
char g_earlierHeapStr_45AEF0[12] = "pAddress";
char g_earlierHeapStr_45AEFC[20] = "pBlock->pUsedLast";
char g_earlierHeapStr_45AF10[28] = "pBlock != pThis->pUsedHead";
char g_earlierHeapStr_45AF2C[64] = "!pBlock->pFreeLast || (pBlock->pFreeLast->pFreeNext == pBlock)";
char g_earlierHeapStr_45AF6C[64] = "!pBlock->pFreeNext || (pBlock->pFreeNext->pFreeLast == pBlock)";
char g_earlierHeapStr_45AFAC[64] = "!pBlock->pUsedLast || (pBlock->pUsedLast->pUsedNext == pBlock)";
char g_earlierHeapStr_45AFEC[64] = "!pBlock->pUsedNext || (pBlock->pUsedNext->pUsedLast == pBlock)";
char g_earlierHeapStr_45B02C[36] = "pBlock->Used >= HEAP_HEADER_SIZE";
char g_earlierHeapStr_45B050[24] = "!pUsedLast->pFreeLast";
#endif
