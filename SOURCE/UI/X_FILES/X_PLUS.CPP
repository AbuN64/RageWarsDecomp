#include "COMMON/MATRIXRECORD.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "TYPES.H"
#include "MATH/math_double.H"
#include "UI/X_FILES/X_PLUS.H"
#include "COMMON/MESSAGESEMAPHORE.H"
#include "include_asm.h"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include <ultra64.h>
#include "RESMGR/resmgr_string_memory.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "DATA/REST_SOURCE_RECORDS.H"

/* X_PLUS.CPP */
/* 802A0470.CPP */
/* Copies n bytes between possibly overlapping buffers and returns the destination: forwards when the destination is below the source and backwards otherwise, aligning to a word boundary with single bytes when both pointers share alignment, then copying whole words and the remaining bytes. */

char *XPlus_MoveMemory(char *dst, const char *src, s32 n) {
    char *d;
    s32 count;

    d = dst;
    if (n == 0 || dst == src) {
        return dst;
    }
    if (dst < src) {
        count = (s32)src;
        if ((count | (s32)dst) & 3) {
            if ((count ^ (s32)dst) & 3) {
                count = n;
            } else if (n < 4) {
                count = n;
            } else {
                count = 4 - (count & 3);
            }
            n -= count;
            do {
                *d++ = *src++;
            } while (--count != 0);
        }
        count = (u32)n >> 2;
        if (count != 0) {
            do {
                *(s32 *)d = *(const s32 *)src;
                src += 4;
                d += 4;
            } while (--count != 0);
        }
        count = n & 3;
        if (count != 0) {
            do {
                *d++ = *src++;
            } while (--count != 0);
        }
    } else {
        src += n;
        d = dst + n;
        count = (s32)src;
        if ((count | (s32)d) & 3) {
            if ((count ^ (s32)d) & 3) {
                count = n;
            } else if (n < 5) {
                count = n;
            } else {
                count &= 3;
            }
            n -= count;
            do {
                *--d = *--src;
            } while (--count != 0);
        }
        count = (u32)n >> 2;
        if (count != 0) {
            do {
                src -= 4;
                d -= 4;
                *(s32 *)d = *(const s32 *)src;
            } while (--count != 0);
        }
        count = n & 3;
        if (count != 0) {
            do {
                *--d = *--src;
            } while (--count != 0);
        }
    }
    return dst;
}

f64 XPlus_ParseDecimalDouble(u8 *text) {
    f64 sign;
    f64 divisor;
    f64 value;
    f64 fraction;
    f64 exponentSign;
    f64 exponent;
    f64 scale;
    f64 threshold;

    sign = k_decimalInitialSign;
    fraction = k_decimalInitialFraction;
    divisor = sign;
    if (*text == 32) {
        do {
            text++;
        } while (*text == 32);
    }
    if (*text == 45) {
        text++;
        sign = k_decimalNegativeSign;
    }
    if (*text == 43) {
        text++;
    }

    value = k_decimalInitialInteger;
    if ((u32)(*text - 48) < 10) {
        do {
            value = value * k_decimalIntegerRadix + (f64)(*text - 48);
            text++;
        } while ((u32)(*text - 48) < 10);
    }

    if (*text == 46) {
        text++;
        fraction = k_decimalFractionZero;
        if ((u32)(*text - 48) < 10) {
            do {
                divisor *= k_decimalFractionRadix;
                fraction = fraction * k_decimalFractionRadix + (f64)(*text - 48);
                text++;
            } while ((u32)(*text - 48) < 10);
        }
    }

    if (*text == 101 || *text == 69) {
        text++;
        exponentSign = k_decimalInitialExponentSign;
        if (*text == 45) {
            text++;
            exponentSign = k_decimalNegativeExponentSign;
        }
        if (*text == 43) {
            text++;
        }
        exponent = k_decimalInitialExponent;
        if ((u32)(*text - 48) < 10) {
            do {
                exponent = exponent * k_decimalExponentRadix + (f64)(*text - 48);
                text++;
            } while ((u32)(*text - 48) < 10);
        }
        if (exponent < k_decimalDirectExponentLimit) {
            threshold = k_decimalExponentLoopLimit;
            scale = k_decimalInitialExponentScale;
            if (exponent == threshold) {
                goto compare_sign;
            } else {
                do {
                    scale *= k_decimalExponentScaleRadix;
                    exponent -= k_decimalInitialExponentScale;
                } while (exponent != threshold);
            }
            goto set_threshold;
        } else {
            scale = XMath_PowerDouble(k_decimalPowerRadix, exponent);
        }
set_threshold:
        threshold = k_decimalOverflowExponentLimit;
compare_sign:
        if (exponentSign < threshold) {
            return sign * (value + fraction / divisor) / scale;
        }
        return sign * (value + fraction / divisor) * scale;
    }
    return sign * (value + fraction / divisor);
}

/* 802A0888.CPP */
/* Splits a path into drive, directory, file name and extension like _splitpath: a leading "X:" goes to the drive, everything through the last '/' or '\\' to the directory, the rest up to the last '.' at or after that point to the name and from the '.' on to the extension (or all of it to the name when there is none), each copied with a bounded strncpy and terminated, and any missing part cleared. */

static inline s32 path_length(u8 *s) {
    u8 *p = s;

    while (*p++) {
    }
    return p - s - 1;
}

static inline void copy_part(u8 *d, u8 *s, s32 n) {
    if (n != 0) {
    copy:
        if ((*d++ = *s++) != 0) {
            if (--n != 0) {
                goto copy;
            }
        }
        if (n != 0) {
            while (--n != 0) {
                *d++ = 0;
            }
        }
    }
}

void XPlus_SplitPath(u8 *path, u8 *drive, u8 *dir, u8 *name, u8 *ext) {
    u8 *dot;
    u8 *slash;
    u8 *p;
    s32 n;

    slash = 0;
    dot = 0;
    if (path_length(path) > 0 && path[1] == ':') {
        if (drive != 0) {
            copy_part(drive, path, 2);
            drive[2] = 0;
        }
        path += 2;
    } else if (drive != 0) {
        *drive = 0;
    }
    for (p = path; *p != 0; p++) {
        if (*p == '/' || *p == '\\') {
            slash = p + 1;
        } else if (*p == '.') {
            dot = p;
        }
    }
    if (slash != 0) {
        if (dir != 0) {
            n = slash - path;
            if (n >= 0x100) {
                n = 0xFF;
            }
            copy_part(dir, path, n);
            dir[n] = 0;
        }
        path = slash;
    } else if (dir != 0) {
        *dir = 0;
    }
    if (dot != 0 && dot >= path) {
        if (name != 0) {
            n = dot - path;
            if (n >= 0x100) {
                n = 0xFF;
            }
            copy_part(name, path, n);
            name[n] = 0;
        }
        if (ext != 0) {
            n = p - dot;
            if (n >= 0x100) {
                n = 0xFF;
            }
            copy_part(ext, dot, n);
            ext[n] = 0;
        }
    } else {
        if (name != 0) {
            n = p - path;
            if (n >= 257) {
                n = 0x100;
            }
            copy_part(name, path, n);
            name[n] = 0;
        }
        if (ext != 0) {
            *ext = 0;
        }
    }
}

/* Quick-sorts the elements between base and max for XPlus_SortArray (the qsort helper qst): picks the median of the first, middle and last elements as the pivot when the span reaches the six-element threshold g_xplusSortMedianThreshold, partitions around it with the comparator g_xplusSortComparator swapping g_xplusSortElementSize bytes at a time, then recurses into the smaller side and loops on the larger while it spans at least g_xplusSortPartitionThreshold bytes. Written from the BSD qsort qst structure with the halving shift unsigned. */

void XPlus_PartitionSortRange(char *base, char *max) {
    char c;
    char *i;
    char *j;
    char *jj;
    s32 ii;
    char *mid;
    char *tmp;
    s32 lo;
    s32 hi;

    lo = max - base;
    do {
        mid = i = base + g_xplusSortElementSize * ((unsigned)(lo / g_xplusSortElementSize) >> 1);
        if (lo >= g_xplusSortMedianThreshold) {
            j = (g_xplusSortComparator((jj = base), i) > 0 ? jj : i);
            if (g_xplusSortComparator(j, (tmp = max - g_xplusSortElementSize)) > 0) {
                j = (j == jj ? i : jj);
                if (g_xplusSortComparator(j, tmp) < 0) {
                    j = tmp;
                }
            }
            if (j != i) {
                ii = g_xplusSortElementSize;
                do {
                    c = *i;
                    *i++ = *j;
                    *j++ = c;
                } while (--ii);
            }
        }
        for (i = base, j = max - g_xplusSortElementSize;;) {
            while (i < mid && g_xplusSortComparator(i, mid) <= 0) {
                i += g_xplusSortElementSize;
            }
            while (j > mid) {
                if (g_xplusSortComparator(mid, j) <= 0) {
                    j -= g_xplusSortElementSize;
                    continue;
                }
                tmp = i + g_xplusSortElementSize;
                if (i == mid) {
                    mid = jj = j;
                } else {
                    jj = j;
                    j -= g_xplusSortElementSize;
                }
                goto swap;
            }
            if (i == mid) {
                break;
            } else {
                jj = mid;
                tmp = mid = i;
                j -= g_xplusSortElementSize;
            }
swap:
            ii = g_xplusSortElementSize;
            do {
                c = *i;
                *i++ = *jj;
                *jj++ = c;
            } while (--ii);
            i = tmp;
        }
        i = (j = mid) + g_xplusSortElementSize;
        if ((lo = j - base) <= (hi = max - i)) {
            if (lo >= g_xplusSortPartitionThreshold) {
                XPlus_PartitionSortRange(base, j);
            }
            base = i;
            lo = hi;
        } else {
            if (hi >= g_xplusSortPartitionThreshold) {
                XPlus_PartitionSortRange(i, max);
            }
            max = j;
        }
    } while (lo >= g_xplusSortPartitionThreshold);
}

/* Sorts n elements of the given size with a comparator (qsort): records the element size, the four- and six-element thresholds and the comparator in g_xplusSortElementSize to g_xplusSortComparator, quick-sorts arrays of four or more through XPlus_PartitionSortRange, swaps the smallest of the first elements into place as a sentinel, and finishes with an insertion sort that shifts bytes. Written from the BSD qsort driver structure. */

void XPlus_SortArray(char *base, s32 n, s32 size, s32 (*compare)(char *a, char *b)) {
    char c;
    char *i;
    char *j;
    char *lo;
    char *hi;
    char *min;
    char *max;

    if (n <= 1) {
        return;
    }
    g_xplusSortPartitionThreshold = size * 4;
    g_xplusSortMedianThreshold = size * 6;
    g_xplusSortElementSize = size;
    g_xplusSortComparator = compare;
    max = base + n * size;
    if (n >= 4) {
        XPlus_PartitionSortRange(base, max);
        hi = base + g_xplusSortPartitionThreshold;
    } else {
        hi = max;
    }
    for (j = lo = base; (lo += g_xplusSortElementSize) < hi;) {
        if (g_xplusSortComparator(j, lo) > 0) {
            j = lo;
        }
    }
    if (j != base) {
        for (i = base, hi = base + g_xplusSortElementSize; i < hi;) {
            c = *j;
            *j++ = *i;
            *i++ = c;
        }
    }
    for (min = base; (hi = min += g_xplusSortElementSize) < max;) {
        while (g_xplusSortComparator(hi -= g_xplusSortElementSize, min) > 0) {
        }
        if ((hi += g_xplusSortElementSize) != min) {
            for (lo = min + g_xplusSortElementSize; --lo >= min;) {
                c = *lo;
                for (i = j = lo; (j -= g_xplusSortElementSize) >= hi; i = j) {
                    *i = *j;
                }
                *i = c;
            }
        }
    }
}

void *XPlus_FillMemory(void *destination, int fillValue, u32 byteCount) {
    u8 *start;
    u8 *end;
    u8 *cur;
    u8 *next;
    u32 byte;
    u32 word;

    start = destination;
    end = start + byteCount;
    byte = fillValue & 0xFF;
    word = (byte << 24) | (byte << 16) | (byte << 8) | byte;
    cur = start;

    if (cur >= end) {
        goto word_test;
    }
align_test:
    if (!((u32)cur & 3)) {
        goto word_test;
    }
    *cur = fillValue;
    cur += 1;
    if (cur < end) {
        goto align_test;
    }
    goto word_test;

word_test:
    next = cur + 4;
    while (next < end) {
        *(u32 *)cur = word;
        cur = next;
        next = cur + 4;
    }

    if (cur < end) {
        do {
            *cur++ = fillValue;
        } while (cur < end);
    }
    return start;
}

/* 802A0470_2.CPP */
s32 XPlus_SearchSortedArray(s32 *index, u8 *base, s32 count, void *key,
                     s32 stride, s32 (*compare)(void *, void *)) {
    s32 low = 0;
    s32 half = 0;
    s32 high = count - 1;
    s32 result;
    u8 *entry;
    if (index != 0) {
        *index = 0;
    }
    if (count != 0) {
        while (low <= high) {
            half = (high - low) >> 1;
            entry = base + (low + half) * stride;
            result = compare(key, entry);
            if (result < 0) {
                goto less;
            }
            if (result != 0) {
                goto more;
            }

            while ((entry -= stride) > base && compare(key, entry) == 0) {
                half--;
            }
            if (index != 0) {
                *index = low + half;
            }
            return 1;
more:
            low += half + 1;
            continue;
less:
            high -= half + 1;
        }
        if (index != 0) {
            *index = low + half;
        }
    }
    return 0;
}

/* resmgr_string_memory.CPP */
void XPlus_SeedRandomGenerator(int seed) {
    g_xplusRandomState = seed;
}

s32 XPlus_NextRandomInteger(void) {
    s32 nextState;

    nextState = (g_xplusRandomState * 0x343FD) + 0x269EC3;
    g_xplusRandomState = nextState;
    return (nextState >> 16) & 0x7FFF;
}

/** Return strlen(string) (byte count not including the terminating NUL). */
s32 XPlus_StringLength(u8 *string) {
    u8 *cursor;
    u8 c;

    cursor = string + 1;
    if (*string != 0) {
        do {
            c = *cursor;
            cursor += 1;
        } while (c != 0);
    }
    return (cursor - string) - 1;
}

u8 *XPlus_CopyString(u8 *destination, u8 *source) {
    u8 *destCursor;
    u8 c;

    c = *source;
    source++;
    *destination = c;
    destCursor = destination + 1;
    if (c != 0) {
        do {
            c = *source;
            source++;
            *destCursor = c;
            destCursor++;
        } while (c != 0);
    }
    return destination;
}

/** strncpy: copy up to count bytes from source to destination, NUL-padding the remainder. */
u8 *XPlus_CopyStringBounded(u8 *destination, u8 *source, s32 count) {
    s32 remaining;
    u8 *start;
    u8 *destCursor;
    u8 *sourceCursor;
    u8 c;

    destCursor = destination;
    sourceCursor = source;
    remaining = count;
    start = destCursor;
    if (remaining != 0) {
    loop_1:
        c = *sourceCursor;
        sourceCursor += 1;
        *destCursor = c;
        destCursor += 1;
        if (c & 0xFF) {
            remaining -= 1;
            if (remaining != 0) {
                goto loop_1;
            }
        }
        if (remaining != 0) {
            remaining -= 1;
            if (remaining != 0) {
                do {
                    *destCursor = 0;
                    remaining -= 1;
                    destCursor += 1;
                } while (remaining != 0);
            }
        }
    }
    return start;
}

u8 *XPlus_AppendString(u8 *destination, u8 *source) {
    u8 *sourceCursor;
    u8 *destCursor;
    u8 c;
    sourceCursor = source;
    destCursor = destination;
    if (*destination != 0) {
        do {
            destCursor += 1;
        } while (*destCursor != 0);
    }
    do {
        c = *sourceCursor;
        sourceCursor += 1;
        *destCursor = c;
        destCursor += 1;
    } while (c & 0xFF);
    return destination;
}

u8 *XPlus_AppendStringBounded(u8 *destination, u8 *source, s32 count) {
    u8 *end = destination + 1;
    u8 byte;
    if (*destination != 0) {
        do { } while (*end++ != 0);
    }
    --end;
    while (count-- != 0) {
        byte = *source++;
        *end++ = byte;
        if (!(byte & 0xFF)) return destination;
    }
    *end = 0;
    return destination;
}

s32 XPlus_CompareStrings(const void *leftString, const void *rightString) {
    const u8 *a = leftString;
    const u8 *b = rightString;
    s32 difference;

    while ((difference = *a - *b) == 0) {
        if (*b == 0) {
            break;
        }
        a++;
        b++;
    }
    return difference;
}

s32 XPlus_CompareStringsBounded(u8 *a, u8 *b, s32 count) {
    u8 *aCursor;
    u8 *bCursor;
    u8 c;
    aCursor = a;
    bCursor = b;
    if (count == 0) {
        return 0;
    }
    count -= 1;
    while (count != 0 && (c = *aCursor) != 0 && c == *bCursor) {
        count -= 1;
        aCursor += 1;
        bCursor += 1;
    }
    return *aCursor - *bCursor;
}

s32 XPlus_CompareStringsIgnoreCase(u8 *a, u8 *b)
{
  s32 c2;
  int letterA;
  s32 c1;
  c2 = *b;
  b += 1;
  letterA = 65;
  if (c2 >= letterA)
  {
    if (c2 < 91)
    {
      c2 += 32;
    }
  }
  c1 = *a;
  a += 1;
  if (c1 >= letterA)
  {
    if (c1 < 91)
    {
      c1 += 32;
    }
  }
  if (c2 != 0)
  {
    if (c2 == c1)
    {
      return XPlus_CompareStringsIgnoreCase(a, b);
    }
  }
  return c1 - c2;
}

/* Returns a pointer to the last occurrence of a character in a string, or 0 when it does not occur
   (strrchr). */
u8 *XPlus_FindLastCharacter(u8 *s, int c) {
    u8 *start = s;
    while (*s++ != 0) {
    }
    s--;
    for (; s != start; s--) {
        if (*s == (u8)c) {
            break;
        }
    }
    if (*s == (u8)c) {
        return s;
    }
    return 0;
}

/** In-place ASCII-uppercase a NUL-terminated string; NULL-safe. */
u8 *XPlus_UppercaseString(u8 *string) {
    u8 *cursor;
    u8 c;
    cursor = string;
    if (string == 0) {
        return 0;
    }
    if (*string != 0) {
        do {
            c = *cursor;
            if ((u32)(c - 97) < 26U) {
                *cursor = c - 32;
            }
            cursor += 1;
        } while (*cursor != 0);
    }
    return string;
}

/** In-place ASCII-lowercase a NUL-terminated string; NULL-safe. */
u8 *XPlus_LowercaseString(u8 *string) {
    u8 *cursor;
    u8 c;
    cursor = string;
    if (string == 0) {
        return 0;
    }
    if (*string != 0) {
        do {
            c = *cursor;
            if ((u32)(c - 65) < 26U) {
                *cursor = c + 32;
            }
            cursor += 1;
        } while (*cursor != 0);
    }
    return string;
}

/* Searches a zero-terminated byte string for a pattern and returns the position just past the first match, or zero when there is none. */
u8 *XPlus_FindPatternEnd(u8 *s, u8 *pattern) {
    u8 *p;
    while (*s != 0) {
        while (*s != 0 && *s != *pattern) {
            s++;
        }
        p = pattern;
        while (*p != 0 && *s == *p) {
            p++;
            s++;
        }
        if (*p == 0) {
            return s;
        }
    }
    return 0;
}

/** Convert a lowercase ASCII letter to uppercase. */
int XPlus_UppercaseCharacter(int c) {
    if ((unsigned int)(c - 'a') < 26) {
        c -= 'a' - 'A';
    }
    return c;
}

/** Convert an uppercase ASCII letter to lowercase. */
int XPlus_LowercaseCharacter(int c) {
    if ((unsigned int)(c - 'A') < 26) {
        c += 'a' - 'A';
    }
    return c;
}

/* Parses a signed decimal integer from a string, skipping leading spaces and one optional sign (atoi). */
s32 XPlus_ParseDecimalInteger(u8 *s) {
    s32 n;
    s32 c;
    u8 sign;
    while (*s == ' ') {
        s++;
    }
    c = *s;
    sign = c;
    s++;
    if (sign == '-' || sign == '+') {
        c = *s;
        s++;
    }
    n = 0;
    while (c >= '0' && c <= '9') {
        n = (c - '0') + n * 10;
        c = *s;
        s++;
    }
    if (sign == '-') {
        return -n;
    }
    return n;
}

/* Formats a signed integer as a NUL-terminated decimal string (K&R itoa with the reverse inlined). */
void XPlus_FormatDecimalInteger(s32 n, char *s) {
    s32 i;
    s32 j;
    s32 sign;
    s32 len;
    char c;
    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    len = i;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    s[len] = '\0';
}

void *XPlus_CopyBytes(void *destination, const void *source, s32 bytes) {
    void *result = destination;
    if (bytes != 0) {
        result = XPlus_MoveMemory(destination, source, bytes);
    }
    return result;
}

/* Fills count bytes at destination with the byte value, storing single bytes up to word alignment, replicated words through the middle and single bytes at the tail, and returns destination. Adapted from XPlus_FillMemory. */
void *XPlus_FillBytes(void *destination, int value, u32 count) {
    u8 *start;
    u8 *end;
    u8 *cur;
    u8 *next;
    u32 fillByte;
    u32 fillWord;
    start = destination;
    end = start + count;
    fillByte = value & 0xFF;
    fillWord = (fillByte << 24) | (fillByte << 16) | (fillByte << 8) | fillByte;
    cur = start;
    if (cur >= end) {
        goto word_test;
    }
align_test:
    if (!((u32)cur & 3)) {
        goto word_test;
    }
    *cur = value;
    cur += 1;
    if (cur < end) {
        goto align_test;
    }
    goto word_test;
word_test:
    next = cur + 4;
    while (next < end) {
        *(u32 *)cur = fillWord;
        cur = next;
        next = cur + 4;
    }
    if (cur < end) {
        do {
            *cur++ = value;
        } while (cur < end);
    }
    return start;
}

u8 *XPlus_FindByte(u8 *buffer, s32 value, s32 length) {
    u8 *p;
    s32 count;
    p = buffer;
    count = length;
    if (count != 0) {
        value = value & 0xFF;
loop:
        if (*p != value) {
            count -= 1;
            p += 1;
            if (count != 0) {
                goto loop;
            }
        }
    }
    if (count == 0) {
        return 0;
    }
    return p;
}

s32 XPlus_CompareMemory(u8 *a, u8 *b, s32 count) {
    u8 *aCursor;
    u8 *bCursor;
    u8 *end;
    u8 bByte;
    u8 aByte;
    aCursor = a;
    bCursor = b;
    end = aCursor + count;
    if (count < 4) {
        goto block_17;
    }
    if ((u32)aCursor & 3) {
        goto block_17;
    }
    if ((u32)bCursor & 3) {
        goto block_17;
    }
    end -= 4;
    if (end < aCursor) {
        end += 4;
        goto block_16;
    }
loop_6:
    if (*(u32 *)aCursor != *(u32 *)bCursor) {
        aCursor -= 4;
        bCursor -= 4;
        goto block_11;
    }
    aCursor += 4;
    bCursor += 4;
    if (end >= aCursor) {
        goto loop_6;
    }
block_11:
    end += 4;
    goto block_16;
block_12:
    aByte = *aCursor;
    bByte = *bCursor;
    if (aByte == bByte) {
        aCursor += 1;
        bCursor += 1;
        goto block_16;
    }
    if (aByte < bByte) {
        return -1;
    }
    return 1;
block_16:
    ;
block_17:
    if (aCursor < end) {
        goto block_12;
    }
    return 0;
}

/** Compute a CRC-32 over length bytes, continuing from crc. */
u32 XPlus_UpdateCrc32(u8 *data, u32 length, u32 crc) {
    u32 table[256];
    u32 i;
    u32 j;
    u32 value;
    u32 shifted;
    u8 *end;
    for (i = 0; i < 256; i++) {
        value = i;
        for (j = 0; j < 8; j++) {
            shifted = value >> 1;
            if (value & 1) {
                shifted ^= 0xEDB88320U;
            }
            value = shifted;
        }
        table[i] = value;
    }
    end = data + length;
    crc = ~crc;
    while (data < end) {
        crc = table[(crc ^ *data++) & 0xFF] ^ ((crc >> 8) & 0xFFFFFF);
    }
    return ~crc;
}

/* Builds a path from drive, directory, filename and extension components. */
void XPlus_BuildPath(u8 *path, u8 *drive, u8 *directory, u8 *name, u8 *extensionArg) {
    u8 *extension = extensionArg;
    u8 *out;
    u8 *cursor;
    u8 driveLetter;
    u8 lastDirChar;
    u8 dirChar;
    u8 extFirst;
    u8 nameChar;
    u8 extChar;
    out = path;
    cursor = directory;
    if (drive != 0) {
        driveLetter = *drive;
        if (driveLetter != 0) {
            *out++ = driveLetter;
            *out++ = 58;
        }
    }
    if ((cursor != 0) && (*cursor != 0)) {
        do {
            dirChar = *cursor;
            cursor += 1;
            *out = dirChar;
            out += 1;
        } while (cursor[0] != 0);
        lastDirChar = cursor[-1];
        if ((lastDirChar != 47) && (lastDirChar != 92)) {
            *out = 92;
            out += 1;
        }
    }
    if (name != 0) {
        nameChar = *name;
        cursor = name;
        if (nameChar != 0) {
            do {
                cursor += 1;
                *out = nameChar;
                nameChar = *cursor;
                out += 1;
            } while (nameChar != 0);
        }
    }
    if (extension != 0) {
        cursor = extension;
        extFirst = *cursor;
        if (extFirst != 0) {
            if (extFirst != 46) {
                *out = 46;
                out += 1;
            }
            extChar = *cursor;
            if (extChar != 0) {
                do {
                    cursor += 1;
                    *out = extChar;
                    extChar = *cursor;
                    out += 1;
                } while (extChar != 0);
            }
        }
    }
    *out = 0;
}

void XPlus_InitializeSemaphore(void *messageSemaphore) {
    MessageSemaphore *semaphore = messageSemaphore;
    osCreateMesgQueue(messageSemaphore, &semaphore->message, 1);
    osSendMesg(messageSemaphore, 1, 1);
}

void XPlus_AcquireSemaphore(s32 queue) {
    osRecvMesg(queue, queue + 24, 1);
}

void XPlus_ReleaseSemaphore(s32 *queue) {
    osSendMesg(queue, 1, 1);
}

#if defined(VERSION_US)
unsigned int g_XPlusReleaseSemaphoreTrailingPad[1] = {
    0x00000000,
};
#endif

/* XPLUS_NEXTRANDOMINTEGER_DATA.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/writable/800D2B70 */
RestXplusNextrandomintegerEncodedWordsLayout350 g_XplusNextrandomintegerEncodedWords = {
    1,
    "re\000\000",
};
#endif

/* XPLUS_PARSEDECIMALDOUBLE_DATA.CPP */
/* 800CA60C_22.CPP */
#if defined(VERSION_US_REV1)
const float k_xplusParsedecimaldoubleDataFloatConstantWords[34] = {
    1.875f, 0.0f, 0.0f, 0.0f, -1.875f, 0.0f,
    0.0f, 0.0f, 2.5625f, 0.0f, 0.0f, 0.0f,
    2.5625f, 0.0f, 1.875f, 0.0f, -1.875f, 0.0f,
    0.0f, 0.0f, 2.5625f, 0.0f, 2.96875f, 0.0f,
    0.0f, 0.0f, 1.875f, 0.0f, 2.5625f, 0.0f,
    2.5625f, 0.0f, 0.0f, 0.0f,
};
#endif

/* 8029FA7C_6.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const f32 k_xplusParsedecimaldoubleDataConstantWords[34] = {
    1.875f, 0.0f, 0.0f, 0.0f, -1.875f, 0.0f,
    0.0f, 0.0f, 2.5625f, 0.0f, 0.0f, 0.0f,
    2.5625f, 0.0f, 1.875f, 0.0f, -1.875f, 0.0f,
    0.0f, 0.0f, 2.5625f, 0.0f, 2.96875f, 0.0f,
    0.0f, 0.0f, 1.875f, 0.0f, 2.5625f, 0.0f,
    2.5625f, 0.0f, 0.0f, 0.0f,
};
#endif

/* 8029FA7C_7.CPP */

/* 8029FA7C_8.CPP */

/* 8029FA7C_9.CPP */

/* XPLUS_PARSEDECIMALDOUBLE_DATA_LINK_GAP_WORDS_US.CPP */
