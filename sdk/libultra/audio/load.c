#include "COMMON/LLDIVRESULT.H"
#include <PR/abi.h>
#include "COMMON/MATH_HELPERS.H"
#include "LOAD_DECODE.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "TYPES.H"
#include "include_asm.h"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* 802BE370_2.CPP */
#if !(defined(VERSION_DE) || defined(VERSION_EU))
/* Decode ADPCM samples, restarting loops and clearing exhausted input.
 * The decode helper uses the existing table-opaque view of this same filter. */
Acmd *alAdpcmPull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    s16 inp;
    s32 tsam;
    s32 nframes;
    s32 nbytes;
    s32 overFlow;
    s32 startZero;
    s32 nOver;
    s32 nSam;
    s32 op;
    s32 nLeft;
    s32 bEnd;
    s32 decoded = 0;
    s32 looped = 0;
    ALLoadFilter48_2 *f = (ALLoadFilter48_2 *)filter;
    if (outCount == 0)
        return ptr;
    inp = 0;
    aLoadADPCM(ptr++, f->bookSize,
               Sound_GetCachedAudioBlockAddress(f->table->waveInfo.adpcmWave.book->book, f->bookSize));
    looped = (outCount + f->sample > f->loop.end) && (f->loop.count != 0);
    if (looped)
        nSam = f->loop.end - f->sample;
    else
        nSam = outCount;
    if (f->lastsam)
        nLeft = 16 - f->lastsam;
    else
        nLeft = 0;
    tsam = nSam - nLeft;
    if (tsam < 0) tsam = 0;
    nframes = (tsam + 16 - 1) >> 4;
    nbytes = nframes * 9;
    if (looped) {
        ptr = _decodeChunk(ptr, (ALLoadFilter48_2 *)f, tsam, nbytes, *outp, inp, f->first);
        if (f->lastsam)
            *outp += (f->lastsam << 1);
        else
            *outp += (16 << 1);
        f->lastsam = f->loop.start & 0xf;
        f->memin = (s32)f->table->base + 9 *
            ((s32)(f->loop.start >> 4) + 1);
        f->sample = f->loop.start;
        bEnd = *outp;
        while (outCount > nSam) {
            outCount -= nSam;
            op = (bEnd + ((nframes + 1) << (4 + 1))) & ~0x1f;
            bEnd += (nSam << 1);
            if ((f->loop.count != -1) && (f->loop.count != 0))
                f->loop.count--;
            nSam = RW_MIN_LT(outCount, f->loop.end - f->loop.start);
            tsam = nSam - 16 + f->lastsam;
            if (tsam < 0) tsam = 0;
            nframes = (tsam + 16 - 1) >> 4;
            nbytes = nframes * 9;
            ptr = _decodeChunk(ptr, (ALLoadFilter48_2 *)f, tsam, nbytes, op, inp, f->first | 0x02);
            aDMEMMove(ptr++, op + (f->lastsam << 1), bEnd, nSam << 1);
        }
        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += 9 * nframes;
        return ptr;
    }
    nSam = nframes << 4;
    overFlow = f->memin + nbytes - ((s32)f->table->base + f->table->len);
    if (overFlow < 0)
        overFlow = 0;
    nOver = (overFlow / 9) << 4;
    if (nOver > nSam + nLeft)
        nOver = nSam + nLeft;
    nbytes -= overFlow;
    if ((nOver - (nOver & 0xf)) < outCount) {
        decoded = 1;
        ptr = _decodeChunk(ptr, (ALLoadFilter48_2 *)f, nSam - nOver, nbytes, *outp, inp, f->first);
        if (f->lastsam)
            *outp += (f->lastsam << 1);
        else
            *outp += (16 << 1);
        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += 9 * nframes;
    } else {
        f->lastsam = 0;
        f->memin += 9 * nframes;
    }
    if (nOver) {
        f->lastsam = 0;
        if (decoded)
            startZero = (nLeft + nSam - nOver) << 1;
        else
            startZero = 0;
        aClearBuffer(ptr++, startZero + *outp, nOver << 1);
    }
    return ptr;
}
#endif

#if defined(VERSION_DE)
Acmd *alAdpcmPull(ALLoadFilter48_2 *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    s16 inp;
    s32 tsam;
    s32 nframes;
    s32 nbytes;
    s32 overFlow;
    s32 startZero;
    s32 nOver;
    s32 nSam;
    s32 op;
    s32 nLeft;
    s32 bEnd;
    s32 decoded = 0;
    s32 looped = 0;

    ALLoadFilter48_2 *f = filter;

    if (outCount == 0)
        return ptr;

    inp = 0;
    aLoadADPCM(ptr++, f->bookSize,
               Sound_GetCachedAudioBlockAddress(f->table->waveInfo.adpcmWave.book->book, f->bookSize));

    looped = (outCount + f->sample > f->loop.end) && (f->loop.count != 0);
    if (looped)
        nSam = f->loop.end - f->sample;
    else
        nSam = outCount;

    if (f->lastsam)
        nLeft = 16 - f->lastsam;
    else
        nLeft = 0;
    tsam = nSam - nLeft;
    if (tsam < 0) tsam = 0;

    nframes = (tsam + 16 - 1) >> 4;
    nbytes = nframes * 9;

    if (looped) {

        ptr = _decodeChunk(ptr, (ALLoadFilter48_2 *)f, tsam, nbytes, *outp, inp, f->first);

        if (f->lastsam)
            *outp += (f->lastsam << 1);
        else
            *outp += (16 << 1);

        f->lastsam = f->loop.start & 0xf;
        f->memin = (s32)f->table->base + 9 *
            ((s32)(f->loop.start >> 4) + 1);
        f->sample = f->loop.start;

        bEnd = *outp;
        while (outCount > nSam) {

            outCount -= nSam;

            op = (bEnd + ((nframes + 1) << (4 + 1))) & ~0x1f;

            bEnd += (nSam << 1);

            if ((f->loop.count != -1) && (f->loop.count != 0))
                f->loop.count--;

            nSam = (((outCount) < (f->loop.end - f->loop.start)) ? (outCount) : (f->loop.end - f->loop.start));
            tsam = nSam - 16 + f->lastsam;
            if (tsam < 0) tsam = 0;
            nframes = (tsam + 16 - 1) >> 4;
            nbytes = nframes * 9;
            ptr = _decodeChunk(ptr, (ALLoadFilter48_2 *)f, tsam, nbytes, op, inp, f->first | 0x02);

            aDMEMMove(ptr++, op + (f->lastsam << 1), bEnd, nSam << 1);
        }

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += 9 * nframes;
        return ptr;
    }

    nSam = nframes << 4;

    overFlow = f->memin + nbytes - ((s32)f->table->base + f->table->len);
    if (overFlow < 0)
        overFlow = 0;
    nOver = (overFlow / 9) << 4;
    if (nOver > nSam + nLeft)
        nOver = nSam + nLeft;

    nbytes -= overFlow;

    if ((nOver - (nOver & 0xf)) < outCount) {
        decoded = 1;
        ptr = _decodeChunk(ptr, (ALLoadFilter48_2 *)f, nSam - nOver, nbytes, *outp, inp, f->first);

        if (f->lastsam)
            *outp += (f->lastsam << 1);
        else
            *outp += (16 << 1);

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += 9 * nframes;
    } else {
        f->lastsam = 0;
        f->memin += 9 * nframes;
    }

    if (nOver) {
        f->lastsam = 0;
        if (decoded)
            startZero = (nLeft + nSam - nOver) << 1;
        else
            startZero = 0;
        aClearBuffer(ptr++, startZero + *outp, nOver << 1);
    }

    return ptr;
}
#endif

#if defined(VERSION_EU)
#include "LOAD_DECODE.H"

Acmd *alAdpcmPull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd        *ptr = p;
    s16         inp;
    s32         tsam;
    s32         nframes;
    s32         nbytes;
    s32         overFlow;
    s32         startZero;
    s32         nOver;
    s32         nSam;
    s32         op;
    s32         nLeft;
    s32         bEnd;
    s32         decoded = 0;
    s32         looped = 0;

    ALLoadFilter48_2 *f = (ALLoadFilter48_2 *)filter;

    if (outCount == 0)
        return ptr;

    inp = 0;
    aLoadADPCM(ptr++, f->bookSize,
               Sound_GetCachedAudioBlockAddress(f->table->waveInfo.adpcmWave.book->book, f->bookSize));

    looped = (outCount + f->sample > f->loop.end) && (f->loop.count != 0);
    if (looped)
        nSam = f->loop.end - f->sample;
    else
        nSam = outCount;

    if (f->lastsam)
        nLeft = 16 - f->lastsam;
    else
        nLeft = 0;
    tsam = nSam - nLeft;
    if (tsam<0) tsam = 0;

    nframes = (tsam+16-1)>>4;
    nbytes =  nframes*9;

    if (looped){

        ptr = _decodeChunk(ptr, f, tsam, nbytes, *outp, inp, f->first);


        if (f->lastsam)
            *outp += (f->lastsam<<1);
        else
            *outp += (16<<1);


        f->lastsam = f->loop.start &0xf;
        f->memin = (s32) f->table->base + 9 *
            ((s32) (f->loop.start>>4) + 1);
        f->sample = f->loop.start;

        bEnd = *outp;
        while (outCount > nSam){

            outCount -= nSam;


            op = (bEnd + ((nframes+1)<<(4+1))) & ~0x1f;


            bEnd += (nSam<<1);


            if ((f->loop.count != -1) && (f->loop.count != 0))
                f->loop.count--;


            nSam = (outCount < f->loop.end - f->loop.start ? outCount : f->loop.end - f->loop.start);
            tsam = nSam - 16 + f->lastsam;
            if (tsam<0) tsam = 0;
            nframes = (tsam+16-1)>>4;
            nbytes =  nframes*9;
            ptr = _decodeChunk(ptr, f, tsam, nbytes, op, inp, f->first | 2);

            aDMEMMove(ptr++, op+(f->lastsam<<1), bEnd, nSam<<1);

        }

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += 9*nframes;

        return ptr;
    }



    nSam = nframes<<4;


    overFlow = f->memin + nbytes - ((s32) f->table->base + f->table->len);
    if (overFlow < 0)
        overFlow = 0;
    nOver = (overFlow/9)<<4;
    if (nOver > nSam + nLeft)
        nOver = nSam + nLeft;

    nbytes -= overFlow;

    if ((nOver - (nOver & 0xf))< outCount){
        decoded = 1;
        ptr = _decodeChunk(ptr, f, nSam - nOver, nbytes, *outp, inp, f->first);

        if (f->lastsam)
            *outp += (f->lastsam<<1);
        else
            *outp += (16<<1);

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += 9*nframes;
    } else {
        f->lastsam = 0;
        f->memin += 9*nframes;
    }


    if (nOver){
        f->lastsam = 0;
        if (decoded)
            startZero = (nLeft + nSam - nOver)<<1;
        else
            startZero = 0;
        aClearBuffer(ptr++, startZero + *outp, nOver<<1);
    }

    return ptr;
}
#endif

/* alRaw16Pull, drafted from ultralib src/audio/load.c: DMA raw 16-bit samples into DMEM at 8-byte
   alignment for the requested output count, restarting from the loop start and merging the
   sections in DMEM when the count crosses the loop end, and clearing what runs past the table. */
Acmd *alRaw16Pull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    s32 nbytes;
    s32 dramLoc;
    s32 dramAlign;
    s32 dmemAlign;
    s32 overFlow;
    s32 startZero;
    s32 nSam;
    s32 op;
    ALLoadFilter48_2 *f = (ALLoadFilter48_2 *)filter;
    ALFilter_s14 *a = (ALFilter_s14 *)filter;
    if (outCount == 0)
        return ptr;
    if ((outCount + f->sample > f->loop.end) && (f->loop.count != 0)) {
        nSam = f->loop.end - f->sample;
        nbytes = nSam << 1;
        if (nSam > 0) {
            dramLoc = (f->dma)(f->memin, nbytes, f->dmaState);
            dramAlign = dramLoc & 0x7;
            nbytes += dramAlign;
            aSetBuffer(ptr++, 0, *outp, 0, nbytes + 8 - (nbytes & 0x7));
            aLoadBuffer(ptr++, dramLoc - dramAlign);
        } else
            dramAlign = 0;
        *outp += dramAlign;
        f->memin = (s32)f->table->base + (f->loop.start << 1);
        f->sample = f->loop.start;
        op = *outp;
        while (outCount > nSam) {
            op += (nSam << 1);
            outCount -= nSam;
            if ((f->loop.count != -1) && (f->loop.count != 0))
                f->loop.count--;
            nSam = RW_MIN_LT(outCount, f->loop.end - f->loop.start);
            nbytes = nSam << 1;
            dramLoc = (f->dma)(f->memin, nbytes, f->dmaState);
            dramAlign = dramLoc & 0x7;
            nbytes += dramAlign;
            if (op & 0x7)
                dmemAlign = 8 - (op & 0x7);
            else
                dmemAlign = 0;
            aSetBuffer(ptr++, 0, op + dmemAlign, 0, nbytes + 8 - (nbytes & 0x7));
            aLoadBuffer(ptr++, dramLoc - dramAlign);
            if (dramAlign || dmemAlign)
                aDMEMMove(ptr++, op + dramAlign + dmemAlign, op, nSam << 1);
        }
        f->sample += outCount;
        f->memin += (outCount << 1);
        return ptr;
    }
    nbytes = outCount << 1;
    overFlow = f->memin + nbytes - ((s32)f->table->base + f->table->len);
    if (overFlow < 0)
        overFlow = 0;
    if (overFlow > nbytes)
        overFlow = nbytes;
    if (overFlow < nbytes) {
        if (outCount > 0) {
            nbytes -= overFlow;
            dramLoc = (f->dma)(f->memin, nbytes, f->dmaState);
            dramAlign = dramLoc & 0x7;
            nbytes += dramAlign;
            aSetBuffer(ptr++, 0, *outp, 0, nbytes + 8 - (nbytes & 0x7));
            aLoadBuffer(ptr++, dramLoc - dramAlign);
        } else
            dramAlign = 0;
        *outp += dramAlign;
        f->sample += outCount;
        f->memin += outCount << 1;
    } else {
        f->memin += outCount << 1;
    }
    if (overFlow) {
        startZero = (outCount << 1) - overFlow;
        if (startZero < 0)
            startZero = 0;
        aClearBuffer(ptr++, startZero + *outp, overFlow);
    }
    return ptr;
}
