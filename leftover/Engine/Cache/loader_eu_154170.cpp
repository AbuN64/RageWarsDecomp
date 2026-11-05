#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of C:/Projects/DM/n64/Source/Engine/Cache/loader.cpp. */
char g_loaderStrPathLoaderCpp[52] = "C:/Projects/DM/n64/Source/Engine/Cache/loader.cpp";
char g_loaderStrU32Paddress0X1[28] = "!(((u32) pAddress) & 0x1)";
char g_loaderStrLength0X1[16] = "!(Length & 0x1)";
char g_loaderStrU32Pdest0X7[24] = "!(((u32) pDest) & 0x7)";
char g_loaderStrPentry[8] = "pEntry";
char g_loaderStrPentryPthisEntries0PentryPthis[88] = "(pEntry >= &pThis->Entries[0]) && (pEntry <= &pThis->Entries[LOADER_ENTRY_COUNT - 1])";
char g_loaderStrOspigetstatus0[24] = "osPiGetStatus() == 0";
char g_loaderStrMqEmptyPthisPireplyqueue[36] = "MQ_IS_EMPTY(&pThis->PiReplyQueue)";
char g_loaderStrDmaret0[12] = "dmaRet == 0";
char g_loaderStrDummymessageOsmesgLoaderDmaCompleteMsg[52] = "dummyMessage == (OSMesg) LOADER_DMA_COMPLETE_MSG";
char g_loaderStrPentryDwflagsLdrAllocated[36] = "!(pEntry->dwFlags & LDR_ALLOCATED)";
char g_loaderStrPentryDwflagsLdrAllocated2[32] = "pEntry->dwFlags & LDR_ALLOCATED";
#endif
