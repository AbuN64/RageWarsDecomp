#include "COMMON/EXTERNS.H"
#include "COMMON/LONE/RUNTIME_HEAP.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "TYPES.H"
#include "AUDIO/HASHTABLE.H"
#include "ENGINE/CACHE/HEAP.H"

/* HASHTABLE.CPP */
/* Creates the address hash table: rounds the requested capacity up to a power of two, allocates twice that many 16-byte slots from pool g_runtimeHeap (keeping the half size, slot count and both index masks in globals), and clears every slot, numbering each with its index. */

extern s32 g_resourceHashEvenIndexMask;


void HashTable_InitializeResourceTable(s32 capacity)
{
    s32 bits = 0;
    s32 top = 0;
    s32 i;
    s32 half;
    u32 n;

    for (i = 0; i < 32; i++) {
        s32 bit = 1 << i;
        if (capacity & bit) {
            bits++;
            top = i;
        }
    }
    if (bits != 1) {
        top++;
    }
    half = 1 << top;
    g_resourceHashSlotCount = half * 2;
    g_resourceHashBucketCount = half;
    g_resourceHashEvenIndexMask = g_resourceHashSlotCount - 2;
    g_resourceHashIndexMask = g_resourceHashSlotCount - 1;
    g_resourceHashBuckets = Heap_AllocateFromFront(&g_runtimeHeap, half << 5);
    for (n = 0; n < g_resourceHashSlotCount; n++) {
        g_resourceHashBuckets[n].value = 0;
        g_resourceHashBuckets[n].key = 0;
        g_resourceHashBuckets[n].next = 0;
        g_resourceHashBuckets[n].index = n;
    }
}

/* Inserts or replaces a keyed value in the address hash table, probing odd overflow slots when its home chain is occupied. The new slot address is written as the scaled index plus the table address because the cartridge adds the index first; array indexing reorders the add and its registers (15 words). */

typedef struct Shared_HashLink Shared_HashLink;

struct Shared_HashLink {
    u32 key[3];
    Shared_HashLink *next;
};

void HashTable_SetResourceByKey(u32 key, struct ResourceLoadRequest *value) {
 CacheHashEntry *entry = g_resourceHashBuckets + (((key<<5)^(key>>1)^(key>>9)^(key>>17)) & g_resourceHashEvenIndexMask);
 CacheHashEntry *tail;
 CacheHashEntry *slot;
 s32 index;
 if (entry->value == 0) {entry->key=key;entry->value=value;return;}
 tail=entry;
 for (;;) {
  if (entry->key==key) {entry->value=value;return;}
  entry=tail->next;
  if (!entry) break;
  tail=entry;
 }
 index=tail->index|1;
 while (g_resourceHashBuckets[index].value != 0) {index+=2; index &= g_resourceHashIndexMask;}
 slot=(CacheHashEntry *)((index << 4) + (u32)g_resourceHashBuckets);
 slot->key=key;slot->value=value;tail->next=slot;
}

void HashTable_RemoveResourceByKey(s32 resourceKey) {
    s32 key;
    CacheHashEntry *preservedEntry;
    CacheHashEntry *successorEntry;
    CacheHashEntry *previousEntry;
    CacheHashEntry *entryToClear;

    key = resourceKey;
    entryToClear = g_resourceHashBuckets + (((key << 5) ^ ((u32)key >> 1) ^
                            ((u32)key >> 9) ^ ((u32)key >> 17)) &
                           g_resourceHashEvenIndexMask);
    previousEntry = 0;
    if (entryToClear->key != key) {
loop:
        previousEntry = entryToClear;
        entryToClear = entryToClear->next;
        if (entryToClear != 0) {
            if (entryToClear->key == key) {
                goto found;
            }
            goto loop;
        }
    } else {
found:
        if (entryToClear != 0) {
            successorEntry = entryToClear->next;
            if (successorEntry != 0) {
                entryToClear->value = successorEntry->value;
                entryToClear->key = successorEntry->key;
                entryToClear->next = successorEntry->next;
                preservedEntry = entryToClear;
                entryToClear = successorEntry;
                successorEntry = preservedEntry;
            }
            if (previousEntry != 0) {
                previousEntry->next = successorEntry;
            }
            entryToClear->value = 0;
            entryToClear->key = 0;
            entryToClear->next = 0;
        }
    }
}

/* Rounds a value up to a power of two by locating its highest set bit and bumping it unless exactly one bit is set. Adapted from Bitarray_GetRequiredBitCount, with a signed loop counter, an exactly-one-bit test, and 1 << bit returned instead of the bit index. */

s32 HashTable_RoundCapacityToPowerOfTwo(s32 mask) {
    s32 bitCount;
    s32 highestBit;
    s32 bit;

    bitCount = 0;
    highestBit = 0;
    bit = 0;
    do {
        if (mask & (u32)(1 << bit)) {
            bitCount += 1;
            highestBit = bit;
        }
        bit += 1;
    } while (bit < 32);
    if (bitCount != 1) {
        highestBit += 1;
    }
    return 1 << highestBit;
}

void HashTable_GetMaximumResourceChainLength(void) {
    s32 maximumChainLength;
    s32 scanCount;
    u32 i;
    u32 j;
    u32 limit;
    Shared_HashLink *chainEntry;
    Shared_HashLink *buckets;

    maximumChainLength = 0;
    i = maximumChainLength;
    limit = g_resourceHashBucketCount;
    if (limit != 0) {
        scanCount = limit;
        do {
            i += 1;
        } while (i < (u32)scanCount);
    }
    j = 0;
    if (g_resourceHashBucketCount != 0) {
        buckets = (Shared_HashLink *)g_resourceHashBuckets;
        do {
            chainEntry = &buckets[j];
            scanCount = 0;
            if (chainEntry != 0) {
                do {
                    chainEntry = chainEntry->next;
                    scanCount += 1;
                } while (chainEntry != 0);
            }
            if (scanCount < maximumChainLength) {
                scanCount = maximumChainLength;
            }
            j += 1;
            maximumChainLength = scanCount;
        } while (j < g_resourceHashBucketCount);
    }
    if (g_resourceHashInitialized != 0) {
        g_resourceHashInitialized = 0;
    }
}
