#if defined(VERSION_US)
void * __osFaultedThread = 0;
#endif
#if defined(VERSION_US_REV1)
void * __osFaultedThread[3] = { 0 };
#endif
