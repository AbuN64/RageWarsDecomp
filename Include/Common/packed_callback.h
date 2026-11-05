#ifndef COMMON_PACKED_CALLBACK_H
#define COMMON_PACKED_CALLBACK_H

/*
 * Menu and overlay tables store a callback as a packed 32-bit word: the low 24 bits of the
 * function's address. PACKED_CALLBACK_LOW names the function and yields that word through the
 * linker symbol addrLow_<function>; PACKED_CALLBACK_HIGH yields the upper half the same way.
 */
#define PACKED_CALLBACK_LOW(fn) ((unsigned int)addrLow_##fn)
#define PACKED_CALLBACK_HIGH(fn) ((unsigned int)addrHigh_##fn)

#endif
