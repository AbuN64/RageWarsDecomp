/* GCC target configuration: big-endian MIPS, 32-bit words, IEEE double. */
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
/* Native (non-MIPS) compile of the same C: little-endian word order, portable C in place of the MIPS inline asm. */
#define WORDS_BIG_ENDIAN 0
#define LIBGCC2_WORDS_BIG_ENDIAN 0
#define NO_ASM 1
#else
#define WORDS_BIG_ENDIAN 1
#define LIBGCC2_WORDS_BIG_ENDIAN 1
#endif
#define BITS_PER_UNIT 8
#define LONG_DOUBLE_TYPE_SIZE 64
#define HOST_BITS_PER_INT 32
#define HOST_BITS_PER_LONG 32
#if !defined(NO_ASM)
#define __mips__ 1
#endif
#define CROSS_COMPILE 1
