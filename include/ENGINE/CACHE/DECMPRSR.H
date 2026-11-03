#ifndef ENGINE_CACHE_DECMPRSR_H
#define ENGINE_CACHE_DECMPRSR_H
struct ResourceLoadWorker;
void Cache_StartResourceLoadWorker(struct ResourceLoadWorker *worker, s32 id);
struct ResourceLoadRequest;
s32 Cache_SubmitResourceLoadAndWait(struct ResourceLoadWorker *worker, struct ResourceLoadRequest *message);
struct ResourceRequest;
s32 Cache_TrySubmitResourceLoad(struct ResourceLoadWorker *worker, struct ResourceRequest *request, void *replyQueue);
#endif
