#include "LOAD_DECODE.H"
#include "COMMON/LLDIVRESULT.H"
#include <PR/abi.h>
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "TYPES.H"
#include "include_asm.h"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* Streams raw 16-bit samples into DMEM for the requested byte count: clears the output when the wave table is empty, otherwise refills a 0x100-sample block at g_audioTransformInputStream through Audio_NextDecodedSampleBlock and osWritebackDCache whenever the filter has none left (clearing and stopping when none arrives), then loads the available samples at 8-byte alignment and moves them into place. Adapted from alRaw16Pull (alRaw16Pull) with the loop handling replaced by the streamed block, updated through a pointer to g_audioTransformInputStream. */
extern s32 Audio_NextDecodedSampleBlock();



Acmd *Audio_LoadDecodedSamples(ALLoadFilter48_2 *filter, s16 *outp, s32 byteCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    s32 nbytes;
    s32 dramAlign;
    s32 dmemAlign;
    s32 nSam;
    s32 op;
    ALLoadFilter48_2 *f = filter;
    s32 *stream;
    op = *outp;
    if (f->table->base == 0) {
        aClearBuffer(ptr++, op, byteCount << 1);
        return ptr;
    }
    if (byteCount != 0) {
        stream = &g_audioTransformInputStream;
        do {
            nSam = byteCount;
            if (f->sample == 0) {
                g_audioTransformInputStream = Audio_NextDecodedSampleBlock();
                if (g_audioTransformInputStream == 0) {
                    aClearBuffer(ptr++, op, byteCount << 1);
                    return ptr;
                }
                osWritebackDCache(g_audioTransformInputStream, 0x200);
                f->sample = 256;
            }
            if (f->sample < byteCount) {
                nSam = f->sample;
            }
            nbytes = nSam << 1;
            dramAlign = g_audioTransformInputStream & 0x7;
            nbytes += dramAlign;
            if (op & 0x7) {
                dmemAlign = 8 - (op & 0x7);
            } else {
                dmemAlign = 0;
            }
            aSetBuffer(ptr++, 0, op + dmemAlign, 0, nbytes + 8 - (nbytes & 7));
            aLoadBuffer(ptr++, (g_audioTransformInputStream & 0x1FFFFFFF) - dramAlign);
            if (dramAlign || dmemAlign) {
                aDMEMMove(ptr++, op + dramAlign + dmemAlign, op, nSam << 1);
            }
            byteCount -= nSam;
            op += nSam << 1;
            *stream += nSam << 1;
            f->sample -= nSam;
        } while (byteCount != 0);
    }
    return ptr;
}
