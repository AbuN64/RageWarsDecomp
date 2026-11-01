#include "include_asm.h"
#include "DATA/UI/EVENT_HANDLER_RECORD.H"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
unsigned int D_src_c44120b0[28] = {
    0x00000E07, 0x00007530, 0x002A1DE4, 0x0000000F, 0x00007530, 0x002A1E20, 0x00000010, 0x00007530,
    0x002A1E5C, 0x00000008, 0x00007530, 0x002A1EC0, 0x00000007, 0x00007530, 0x002A1F3C, 0x00000E03,
    0x00007530, 0x002A206C, 0x0000000B, 0x00007530, 0x002A1FB8, 0x00000E08, 0x00007530, 0x002A1FE8,
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
};
#endif
#if defined(VERSION_EU)
unsigned int D_src_c44120b0[28] = {
    0x00000E07, 0x00007530, 0x002A1F04, 0x0000000F, 0x00007530, 0x002A1F40, 0x00000010, 0x00007530,
    0x002A1F7C, 0x00000008, 0x00007530, 0x002A1FE0, 0x00000007, 0x00007530, 0x002A205C, 0x00000E03,
    0x00007530, 0x002A218C, 0x0000000B, 0x00007530, 0x002A20D8, 0x00000E08, 0x00007530, 0x002A2108,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
#endif
#if defined(VERSION_EU_X)
unsigned int D_src_c44120b0[28] = {
    0x00000E07, 0x00007530, 0x002A1F34, 0x0000000F, 0x00007530, 0x002A1F70, 0x00000010, 0x00007530,
    0x002A1FAC, 0x00000008, 0x00007530, 0x002A2010, 0x00000007, 0x00007530, 0x002A208C, 0x00000E03,
    0x00007530, 0x002A21BC, 0x0000000B, 0x00007530, 0x002A2108, 0x00000E08, 0x00007530, 0x002A2138,
    0x00000000, 0x00000000, 0x00000000, 0x496E7669,
};
#endif
#if defined(VERSION_US)
unsigned int D_src_c44120b0[28] = {
    0x00000E07, 0x00007530, 0x002A1D24, 0x0000000F, 0x00007530, 0x002A1D60, 0x00000010, 0x00007530,
    0x002A1D9C, 0x00000008, 0x00007530, 0x002A1E00, 0x00000007, 0x00007530, 0x002A1E7C, 0x00000E03,
    0x00007530, 0x002A1FAC, 0x0000000B, 0x00007530, 0x002A1EF8, 0x00000E08, 0x00007530, 0x002A1F28,
    0x00000000, 0x00000000, 0x00000000, 0x00000400,
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
extern char N64Eng_SetLinkedCommand100_Address[];
extern char N64Eng_SetLinkedCommand200_Address[];
extern char N64Eng_SetLinkedCommand100WithSound_Address[];
extern char N64Eng_HandleNumericIncrement_Address[];
extern char N64Eng_HandleNumericDecrement_Address[];
extern char N64Eng_CancelSelectionRepeat_Address[];
extern char TickSelectionRepeat_Address[];
extern char N64Eng_FreeNumericWidget_Address[];
EventHandlerRecord g_numericWidgetEventIds_StorageWords[9] = {
    { 3591, 30000, N64Eng_SetLinkedCommand100_Address },
    { 15, 30000, N64Eng_SetLinkedCommand200_Address },
    { 16, 30000, N64Eng_SetLinkedCommand100WithSound_Address },
    { 8, 30000, N64Eng_HandleNumericIncrement_Address },
    { 7, 30000, N64Eng_HandleNumericDecrement_Address },
    { 3587, 30000, N64Eng_FreeNumericWidget_Address },
    { 11, 30000, N64Eng_CancelSelectionRepeat_Address },
    { 3592, 30000, TickSelectionRepeat_Address },
    { 0, 0, 0 },
};
#endif
