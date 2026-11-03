#ifndef LIBULTRA_OS_OSCONTRESET_DATA_CPP_H
#define LIBULTRA_OS_OSCONTRESET_DATA_CPP_H
struct ControllerInitStatusBytes;
void __osContGetInitData(u8 *valid, struct ControllerInitStatusBytes *data);
void __osPackRequestData(u8 cmd);
#endif
