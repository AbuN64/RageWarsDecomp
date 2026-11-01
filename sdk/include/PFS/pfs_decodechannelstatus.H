#ifndef PFS_PFS_DECODECHANNELSTATUS_H
#define PFS_PFS_DECODECHANNELSTATUS_H
#include "../OSCONTREQUESFORMATSHORT.H"
extern void __osPfsRequestOneChannel(int channel);
extern void Pfs_DecodeChannelStatus(s32 channel, ControllerInitStatusBytes *data);
#endif
