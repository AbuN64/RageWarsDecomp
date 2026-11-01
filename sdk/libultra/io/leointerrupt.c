#include "../../include/libultra/io/leo.h"

#define IO_READ(a) (*(volatile u32 *)(0xA0000000 | (a)))
#define IO_WRITE(a, v) (*(volatile u32 *)(0xA0000000 | (a)) = (v))
#define PI_STATUS_REG 0x04600010
#define LEO_STATUS 0x05000508
#define LEO_BM_CTL 0x05000510
#define LEO_BM_STATUS 0x05000510
#define LEO_C2_BUFF 0x05000000
#define LEO_SECTOR_BUFF 0x05000400
#define WAIT_ON_IOBUSY(stat)                         \
    stat = IO_READ(PI_STATUS_REG);                   \
    while (stat & (1 | 2))                           \
        stat = IO_READ(PI_STATUS_REG)

s32 __osLeoInterrupt(void) {
    u32 stat = 0;
    OSPiHandle_leo **handlep;
    volatile u32 pi_stat;
    u32 bm_stat;
    __OSTranxInfo *info = &g_currentDiskPeripheralHandle->transferInfo;
    __OSBlockInfo *blockInfo = &info->block[g_currentDiskPeripheralHandle->transferInfo.blockNum];

    pi_stat = IO_READ(PI_STATUS_REG);
    if (pi_stat & 1) {
        blockInfo->errStatus = 29;
        {
            s32 *maskp = &__OSGlobalIntMask;
            *maskp = *maskp & ~0x00000800;
        }
        __osLeoResume();
        return 1;
    }

    pi_stat = IO_READ(PI_STATUS_REG);
    while (pi_stat & (1 | 2)) {
        if (blockInfo) {
            pi_stat = IO_READ(PI_STATUS_REG);
        } else {
            pi_stat = IO_READ(PI_STATUS_REG);
        }
    }
    stat = IO_READ(LEO_STATUS);
    if (stat & 0x02000000) {
        WAIT_ON_IOBUSY(pi_stat);
        IO_WRITE(LEO_BM_CTL, info->bmCtlShadow | 0x01000000);
        blockInfo->errStatus = 0;
        return 0;
    }

    if (info->cmdType == 2) {
        return 1;
    }

    if (stat & 0x08000000) {
        WAIT_ON_IOBUSY(pi_stat);
        stat = IO_READ(LEO_STATUS);
        blockInfo->errStatus = 22;
        __osLeoResume();
        IO_WRITE(PI_STATUS_REG, 2);
        {
            s32 *maskp = &__OSGlobalIntMask;
            *maskp |= 0x00100401;
        }
        return 1;
    }

    if (info->cmdType == 1) {
        if ((stat & 0x40000000) == 0) {
            if (info->sectorNum + 1 != info->transferMode * 85) {
                blockInfo->errStatus = 24;
                __osLeoAbnormalResume();
                return 1;
            }

            IO_WRITE(PI_STATUS_REG, 2);
            {
            s32 *maskp = &__OSGlobalIntMask;
            *maskp |= 0x00100401;
        }
            blockInfo->errStatus = 0;
            __osLeoResume();
            return 1;
        } else {
            blockInfo->dramAddr = (void *)((u32)blockInfo->dramAddr + blockInfo->sectorSize);
            info->sectorNum++;
            __osEPiRawStartDma(g_currentDiskPeripheralHandle, 1, LEO_SECTOR_BUFF, blockInfo->dramAddr, blockInfo->sectorSize);
            return 1;
        }
    } else if (info->cmdType == 0) {
        if (info->transferMode == 3) {
            if (info->sectorNum > (s32)blockInfo->C1ErrNum + 17) {
                blockInfo->errStatus = 0;
                __osLeoAbnormalResume();
                return 1;
            }

            if ((stat & 0x40000000) == 0) {
                blockInfo->errStatus = 23;
                __osLeoAbnormalResume();
                return 1;
            }
        } else {
            blockInfo->dramAddr = (void *)((u32)blockInfo->dramAddr + blockInfo->sectorSize);
        }

        bm_stat = IO_READ(LEO_BM_STATUS);
        if ((bm_stat & 0x00200000 && bm_stat & 0x00400000) || bm_stat & 0x02000000) {
            if (blockInfo->C1ErrNum > 3) {
                if (info->transferMode != 3 || info->sectorNum > 0x52) {
                    blockInfo->errStatus = 23;
                    __osLeoAbnormalResume();
                    return 1;
                }
            } else {
                int errNum = blockInfo->C1ErrNum;
                blockInfo->C1ErrSector[errNum] = info->sectorNum + 1;
            }

            blockInfo->C1ErrNum++;
        }

        if (stat & 0x10000000) {
            if (info->sectorNum + 1 != 88) {
                blockInfo->errStatus = 24;
                __osLeoAbnormalResume();
            }

            if (info->transferMode == 2 && info->blockNum == 0) {
                info->blockNum = 1;
                info->sectorNum = -1;
                info->block[1].dramAddr = (void *)((u32)info->block[1].dramAddr - info->block[1].sectorSize);

                blockInfo->errStatus = 22;
            } else {
                IO_WRITE(PI_STATUS_REG, 2);
                {
            s32 *maskp = &__OSGlobalIntMask;
            *maskp |= 0x00100401;
        }
                info->cmdType = 2;
                blockInfo->errStatus = 0;
            }

            __osEPiRawStartDma(g_currentDiskPeripheralHandle, 0, LEO_C2_BUFF, blockInfo->C2Addr, blockInfo->sectorSize * 4);
            return 1;
        }

        if (info->sectorNum == -1 && info->transferMode == 2 && info->blockNum == 1) {
            __OSBlockInfo *bptr = &info->block[0];
            if (info->block[0].C1ErrNum == 0) {
                if (((u32 *)bptr->C2Addr)[0] | ((u32 *)bptr->C2Addr)[1] | ((u32 *)bptr->C2Addr)[2] | ((u32 *)bptr->C2Addr)[3]) {
                    bptr->errStatus = 24;
                    __osLeoAbnormalResume();
                    return 1;
                }
            }

            bptr->errStatus = 0;
            __osLeoResume();
        }
        info->sectorNum++;
        if (stat & 0x40000000) {
            if (info->sectorNum > 0x54) {
                blockInfo->errStatus = 24;
                __osLeoAbnormalResume();
                return 1;
            }

            __osEPiRawStartDma(*(handlep = &g_currentDiskPeripheralHandle), 0, LEO_SECTOR_BUFF, blockInfo->dramAddr, blockInfo->sectorSize);
            blockInfo->errStatus = 0;
            return 1;
        } else if (info->sectorNum <= 0x54) {
            blockInfo->errStatus = 24;
            __osLeoAbnormalResume();
            return 1;
        }

        return 1;
    } else {
        blockInfo->errStatus = 4;
        __osLeoAbnormalResume();
        return 1;
    }
}
