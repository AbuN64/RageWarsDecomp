#ifndef DATA_OVERLAY_SN_RECORDS_H
#define DATA_OVERLAY_SN_RECORDS_H
#include "TYPES.H"

/* SN Systems files store integer fields in little endian order.  Keeping the
 * encoded fields byte-aligned also preserves the variable-length record ABI. */
typedef struct SnLe16 { u8 low; u8 high; } SnLe16;
typedef struct SnLe32 { u8 byte0; u8 byte1; u8 byte2; u8 byte3; } SnLe32;
#define SN_LE16(value) { (value) & 0xFF, ((value) >> 8) & 0xFF }
#define SN_LE32(value) { (value) & 0xFF, ((value) >> 8) & 0xFF, ((value) >> 16) & 0xFF, ((value) >> 24) & 0xFF }

#endif
