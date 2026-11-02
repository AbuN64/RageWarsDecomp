#include "COMMON/GAMEPLAY_CAMERA.H"
#include "include_asm.h"
#include "ENGINE/DEFS.H"
#include "../../../sdk/include/AUDIO/sprintf.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/VECTOR4F.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "TYPES.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

/* 80265370.CPP */
extern u32 osMemSize;

extern volatile s32 g_staticDataRegionStart;

extern char g_staticDataRegionByteCount;

extern char g_staticJumpTableRegionStart;

extern char g_staticJumpTableRegionByteCount;

extern void *g_cinemaSequenceState;

extern char g_cinemaStateRegionByteCount;

/* Returns whether an address lies in either of two resident memory ranges. */
extern char g_graphicsTaskYieldBuffer, g_runtimeHeapStart, g_menuResidentRegionStart, g_menuResidentRegionEnd;

/* Tests whether an address lies in either recognized resident range. */
extern char addrLow_Libsn_DisableInterrupts;

extern char g_mainCodeRegionByteCount;

extern char addrLow_Track_SolveSplineSecondDerivatives;

extern char g_overlayCodeRegionByteCount;

/* Returns the s32 at a byte offset into a resource loaded from the cartridge, then releases it.
   The resource's ROM address is each cartridge's own, because the data before it differs in size. */
extern char g_resourceWordRequestLabel;

extern void Cache_UnlockResource(s32, void *);

/* Loads the scene's point lights into the display list: with no light in g_dynamicLightPool it clears geometry mode bit 0x80, otherwise it sets it and fills eight light slots from the light list, transforming each active light's position into the view, storing its negated view direction, its colour scaled by its intensity, its falloff and a fixed range, marking unused slots off, and emits the light-move command for each slot, then advances the light buffer. The first direction component is truncated into a local before negating. */
extern Gfx *g_displayListCursor;

extern s32 g_pointLightBufferOffset;

extern UnitLight g_pointLightBuffer[];

extern char g_dynamicLightPool;

extern LightNode *Gdynlight_GetFirstLight(void *);

extern LightNode *Gdynlight_GetNextLight(void *, LightNode *);

u32 Defs_GetMemorySize(void) {
    if (osMemSize > 8388607U) {
        return 0x700000;
    }
    return osMemSize;
}

void Defs_MoveMemory(u8 *split, u8 *source, s32 byteCount) {
    u8 *destinationCursor;
    u8 *sourceCursor;
    s32 lastByteOffset;

    if (byteCount != 0) {
        destinationCursor = split;
        if (((u32)source | (u32)split | byteCount) & 3) {
            sourceCursor = source;
            if (split < source) {
                do {
                    *destinationCursor = *sourceCursor;
                    sourceCursor++;
                    byteCount--;
                    destinationCursor++;
                } while (byteCount != 0);
            } else {
                lastByteOffset = byteCount - 1;
                destinationCursor = split + lastByteOffset;
                sourceCursor = source + lastByteOffset;
                do {
                    *destinationCursor = *sourceCursor;
                    sourceCursor--;
                    byteCount--;
                    destinationCursor--;
                } while (byteCount != 0);
            }
        } else {
            if (split < source) {
                byteCount >>= 2;
                do {
                    *(u32 *)split = *(u32 *)source;
                    source += 4;
                    byteCount--;
                    split += 4;
                } while (byteCount != 0);
            } else {
                byteCount >>= 2;
                split += (byteCount * 4) - 4;
                source += (byteCount * 4) - 4;
                do {
                    *(u32 *)split = *(u32 *)source;
                    source -= 4;
                    byteCount--;
                    split -= 4;
                } while (byteCount != 0);
            }
        }
    }
}

s32 Defs_CompareMemory(u8 *leftBytes, u8 *rightBytes, s32 byteCount) {
    u8 *end = leftBytes + byteCount;

    if (byteCount >= 4 && !((u32)leftBytes & 3) && !((u32)rightBytes & 3)) {
        end -= 4;
        if (end < leftBytes) {
            end += 4;
            goto byte_loop;
        }
word_loop:
        if (*(u32 *)leftBytes != *(u32 *)rightBytes) {
            goto word_mismatch;
        }
        leftBytes += 4;
        goto word_continue;
word_mismatch:
        leftBytes -= 4;
        rightBytes -= 4;
        goto word_done;
word_continue:
        rightBytes += 4;
        if (leftBytes <= end) {
            goto word_loop;
        }
word_done:
        end += 4;
    }

byte_loop:
    while (leftBytes < end) {
        u8 left = *leftBytes;
        u8 right = *rightBytes;

        if (left != right) {
            if (left < right) {
                return -1;
            }
            return 1;
        }
        leftBytes++;
        rightBytes++;
    }
    return 0;
}

s32 Defs_FindSortedValue(void *entries, s32 entryCount, s32 value) {
    u32 middleIndex;
    u32 lowerIndex;

    if (entryCount != 0) {
        entryCount--;
        lowerIndex = 0;
        if (entryCount != 0) {
            do {
                middleIndex = (u32)(lowerIndex + entryCount) >> 1;
                if ((u32)*((s32 *)entries + middleIndex) < (u32)value) {
                    lowerIndex = middleIndex + 1;
                } else {
                    entryCount = middleIndex;
                }
            } while (lowerIndex < (u32)entryCount);
        }
        if (*((s32 *)entries + lowerIndex) == value) {
            return (s32)lowerIndex;
        }
        return -1;
    }
    return -1;
}

s32 Defs_FindSortedGroupRange(u32 *keys, s32 entryCount, u32 group, s32 *firstOut, s32 *last) {
    u32 middleIndex;
    u32 lowerIndex;
    s32 upperIndex;
    s32 found;

    if (entryCount != 0) {
        upperIndex = entryCount - 1;
        lowerIndex = 0;
        if (upperIndex != 0) {
            do {
                middleIndex = (u32)(lowerIndex + upperIndex) >> 1;
                if (keys[middleIndex] < group) {
                    lowerIndex = middleIndex + 1;
                } else {
                    upperIndex = middleIndex;
                }
            } while (lowerIndex < (u32)upperIndex);
        }
        if (keys[lowerIndex] == group) {
            found = lowerIndex;
        } else {
            found = -1;
        }
    } else {
        found = -1;
    }

    if (found == -1) {
        return 0;
    }

    upperIndex = found - 1;
    while ((upperIndex != -1) && (keys[upperIndex] == group)) {
        upperIndex--;
    }
    *firstOut = upperIndex + 1;

    found++;
    while ((found < entryCount) && (keys[found] == group)) {
        found++;
    }
    *last = found - 1;
    return 1;
}

int Defs_GetBitArrayByteCount(int bitCount) {
    int result = bitCount + 7;
    if (result < 0) {
        result = bitCount + 14;
    }
    return result >> 3;
}

s32 Defs_TestBit(void *bitArray, s32 index)
{
  s32 byteIndex;
  s32 bitIndex;
  s32 roundedBitIndex;
  u8 *byteAddress;
  int bitMask;
  roundedBitIndex = index;
  bitIndex = roundedBitIndex;
  if (bitIndex < 0)
  {
    roundedBitIndex = bitIndex + 7;
  }
  byteIndex = roundedBitIndex >> 3;
  bitMask = 1 << (bitIndex - (byteIndex * 8));
  byteAddress = (u8 *)bitArray + byteIndex;
  return (*byteAddress & bitMask) != 0;
}

void Defs_SetBitValue(u8 *bitArray, s32 index, s32 found) {
    s32 byteIdx;
    s32 mask;

    byteIdx = index / 8;
    mask = 1 << (index % 8);
    if (found != 0) {
        bitArray[byteIdx] |= mask;
        return;
    }
    bitArray[byteIdx] &= ~mask;
}

void Defs_ToggleBit(s32 bitArrayAddress, s32 index)
{
  s32 byteIndex;
  s32 bitIndex;
  s32 roundedBitIndex;
  u8 *byteAddress;
  int bitMask;
  roundedBitIndex = index;
  bitIndex = roundedBitIndex;
  if (bitIndex < 0)
  {
    roundedBitIndex = bitIndex + 7;
  }
  byteIndex = roundedBitIndex >> 3;
  bitMask = 1 << (bitIndex - (byteIndex * 8));
  byteAddress = bitArrayAddress + byteIndex;
  *byteAddress ^= bitMask;
}

f32 Defs_CosineEase(f32 fraction)
{
  f32 clampBound;
  f32 clampedFraction;
  clampedFraction = fraction;
  if (clampedFraction < 0.0f)
  {
    clampBound = 0.0f;
    clampedFraction = clampBound;
  }
  else
  {
    clampBound = g_cosineEaseUpperBound;
    if (clampBound < clampedFraction)
    {
      clampedFraction = clampBound;
    }
  }
  return (g_cosineEaseOutputConstants - Math_Cosf(clampedFraction * g_cosineEaseAngleScale)) * (((struct PaddedFloatView *) ((char *) (&g_cosineEaseOutputConstants)))->value);
}

/** Return whether an address lies within one of three recognized ranges. */
int Defs_IsAddressInStaticRanges(u32 callback) {
    if (callback >= (u32)&g_staticDataRegionStart &&
        callback < (u32)&g_staticDataRegionStart + (u32)&g_staticDataRegionByteCount) {
        return 1;
    }
    if (callback >= (u32)&g_staticJumpTableRegionStart &&
        callback < (u32)&g_staticJumpTableRegionStart + (u32)&g_staticJumpTableRegionByteCount) {
        return 1;
    }
    if (callback >= (u32)&g_cinemaSequenceState &&
        callback < (u32)&g_cinemaSequenceState + (u32)&g_cinemaStateRegionByteCount) {
        return 1;
    }
    return 0;
}

int Defs_IsAddressInBufferRanges(u32 address) {
    if (address >= (u32)&g_graphicsTaskYieldBuffer && address < (u32)&g_runtimeHeapStart) return 1;
    if (address >= (u32)&g_menuResidentRegionStart && address < (u32)&g_menuResidentRegionEnd) return 1;
    return 0;
}

int Defs_IsAddressInCodeRanges(u32 callback) {
    if (callback >= (u32)&addrLow_Libsn_DisableInterrupts &&
        callback < (u32)&addrLow_Libsn_DisableInterrupts + (u32)&g_mainCodeRegionByteCount) {
        return 1;
    }
    if (callback >= (u32)&addrLow_Track_SolveSplineSecondDerivatives &&
        callback < (u32)&addrLow_Track_SolveSplineSecondDerivatives + (u32)&g_overlayCodeRegionByteCount) {
        return 1;
    }
    return 0;
}

void Defs_NoOperation(void) {
}

/** Formats one value into buffer. */
void Defs_FormatIntegerValue(char *buffer, const char *format, s32 value) {
    Libc_FormatString(buffer, format, value);
}
/** Formats one value into buffer. */
void Defs_FormatSingleInteger(char *buffer, const char *format, s32 value) {
    Libc_FormatString(buffer, format, value);
}
/** Formats three values into buffer. */
void Defs_FormatThreeIntegers(char *buffer, const char *format, s32 a, s32 b, s32 c) {
    Libc_FormatString(buffer, format, a, b, c);
}
/** Formats four values into buffer. */
void Defs_FormatFourIntegers(char *buffer, const char *format, s32 a, s32 b, s32 c, s32 d) {
    Libc_FormatString(buffer, format, a, b, c, d);
}

s32 Defs_ReadResourceWord(s32 byteOffset) {
    void **resource;
    s32 result;

#if defined(VERSION_DE)
    resource = Cache_RequestResource(0, 0x28BB00, 0x28BB00, 32, 16, 0, 0, &g_resourceWordRequestLabel, 1);
#elif defined(VERSION_EU_X)
    resource = Cache_RequestResource(0, 0x290384, 0x290384, 32, 16, 0, 0, &g_resourceWordRequestLabel, 1);
#else
    resource = Cache_RequestResource(0, 0x28B244, 0x28B244, 32, 16, 0, 0, &g_resourceWordRequestLabel, 1);
#endif
    result = *(s32 *)((char *)*resource + byteOffset);
    Cache_UnlockResource(0, resource);
    return result;
}

void Defs_SetupPointLights(char *view) {
    LightNode *node;
    LightData *data;
    f32 position[4];
    f32 out[4];
    s32 i;
    s32 x;

    node = Gdynlight_GetFirstLight(&g_dynamicLightPool);
    if (node == 0) {
        Gfx *g = g_displayListCursor++;
        gSPGeometryMode(g, 0x80, 0);
        g_pointLightBufferOffset += 8;
        return;
    }
    gSPGeometryMode(g_displayListCursor++, 0, 0x80);
    for (i = 0; i < 8; i++) {
        if (node != 0 && node->active != 0) {
            data = node->data;
            position[0] = node->position[0];
            position[1] = node->position[1];
            position[2] = node->position[2];
            Graphu64_TransformPoint((char *)&((GameplayCamera *)view)->worldToView, position, out);
            x = out[0];
            g_pointLightBuffer[i + g_pointLightBufferOffset].dir[0] = -x;
            g_pointLightBuffer[i + g_pointLightBufferOffset].dir[1] = out[1];
            g_pointLightBuffer[i + g_pointLightBufferOffset].dir[2] = -(s32)out[2];
            g_pointLightBuffer[i + g_pointLightBufferOffset].color[3] = data->color[3] * node->intensity;
            g_pointLightBuffer[i + g_pointLightBufferOffset].color[2] = data->color[0] * node->intensity;
            g_pointLightBuffer[i + g_pointLightBufferOffset].color[1] = data->color[1] * node->intensity;
            g_pointLightBuffer[i + g_pointLightBufferOffset].color[0] = data->color[2] * node->intensity;
            g_pointLightBuffer[i + g_pointLightBufferOffset].falloff = data->falloff;
            g_pointLightBuffer[i + g_pointLightBufferOffset].near = data->near;
            g_pointLightBuffer[i + g_pointLightBufferOffset].range = 32640;
        } else {
            g_pointLightBuffer[i + g_pointLightBufferOffset].falloff = -0x8000;
        }
        if (node != 0) {
            node = Gdynlight_GetNextLight(&g_dynamicLightPool, node);
        }
        {
            Gfx *g = g_displayListCursor++;
            gDma2p(g, G_MOVEMEM, &g_pointLightBuffer[i + g_pointLightBufferOffset], 16, 10, ((i + 1) * 2 + 10) * 8);
        }
    }
    g_pointLightBufferOffset += 8;
}

#if defined(VERSION_US)
char s_DefsBFlagText[12] =
    "\000\000\000\000\010m_bFlag";
#endif


#if defined(VERSION_DE)
float k_DefsEncodedWordsBlock1[3] = {
    2.0e+01f, 1.0f, 1.0e+01f,
};
#endif

/* g_DefsEncodedWords_Defs.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C9498 */
float g_DefsEncodedWords[2] = {
    7.5f, 34.0f,
};
#endif
