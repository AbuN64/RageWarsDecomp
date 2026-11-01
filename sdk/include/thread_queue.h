#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H

/* Queue storage and thread records remain opaque at the assembly ABI boundary.
 * Pop reads one head-slot address and returns the removed node pointer.
 * Enqueue reads next/priority/queue at offsets 0/4/8 in the N64 thread prefix.
 * Full ThreadNode and OSThread layouts are deliberately not conflated here. */
extern void *__osPopThread(void *queue);
extern void __osEnqueueThread(void *queue, void *thread);

#endif
