#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CONTREADFORMAT.H"
#include "TYPES.H"

/** CRC-5-style bit-shuffle: 16 rounds folding bit 10 of blockAddress with a rotating tap. */
int __osContAddressCrc(unsigned int blockAddress) {
    int crcRegister;
    int feedbackPolynomial;
    int remainingBits;
    unsigned int addressBits;
    unsigned int inputBitWindow;
    int nextCrc;

    addressBits = blockAddress;
    crcRegister = 0;
    remainingBits = 0xF;
    do {
        feedbackPolynomial = 0;
        if (crcRegister & 0x10) {
            feedbackPolynomial = 0x15;
        }
        crcRegister = crcRegister * 2;
        inputBitWindow = addressBits >> 10;
        addressBits = addressBits * 2;
        nextCrc = ((crcRegister & 0xFF) | (inputBitWindow & 1)) ^ feedbackPolynomial;
        crcRegister = nextCrc;
        remainingBits -= 1;
    } while (remainingBits >= 0);
    return nextCrc & 0x1F;
}

/* __osContDataCrc, drafted from ultralib src/io/crc.c (the branch before 2.0J): the CRC of a
   32-byte Controller Pak block with generator 0x85, flushed with eight zero bits. */

u8 __osContDataCrc(u8 *data)
{
    u8 temp = 0;
    u8 temp2;
    int i;
    int j;

    for (i = 0; i <= 32; i++) {
        for (j = 7; j > -1; j--) {
            temp2 = (temp & 0x80) ? 0x85 : 0;

            temp <<= 1;

            if (i == 32) {
                temp &= -1;
            } else {
                temp |= ((*data & (1 << j)) ? 1 : 0);
            }

            temp ^= temp2;
        }
        data++;
    }
    return temp;
}

