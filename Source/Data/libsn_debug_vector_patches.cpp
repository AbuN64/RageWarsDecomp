#include "Ai/Devices/actionai.h"

/* DE image of Libgultra_DispatchExceptionVectors (sdk/libsn/debugger.s builds it for the other versions): the debugger's exception and TLB vector
   patches, copied word by word over the vectors by Libsn_InstallDebuggerExceptionHooks. Each patch is the 5-word stub installed at the vector
   (parks k0 in ErrorEPC and jumps to the trace handler), the 5-word slot the original vector words are saved into (filled at run
   time) and the 4-word stub that resumes the vector 0x14 bytes in. */
typedef struct LibsnDebugVectorPatch {
    unsigned int stub[5];
    unsigned int saved[5];
    unsigned int resume[4];
} LibsnDebugVectorPatch;
#if defined(VERSION_DE)
/* Two unread padding words before the first stub; their contents differ per version and nothing reads them. */
LibsnDebugVectorPatch g_libsnDebugVectorPatches[2] = {
    {
        { MIPS_MTC0(MIPS_K0, C0_ERROR_EPC), MIPS_LUI(MIPS_K0, 0x0020), MIPS_ADDIU(MIPS_K0, MIPS_K0, 0x2460), MIPS_JR(MIPS_K0), MIPS_NOP },
        { 0, 0, 0, 0, 0 },
        { MIPS_LUI(MIPS_K0, 0x8000), MIPS_ORI(MIPS_K0, MIPS_K0, 0x0194), MIPS_JR(MIPS_K0), MIPS_NOP },
    },
    {
        { MIPS_MTC0(MIPS_K0, C0_ERROR_EPC), MIPS_LUI(MIPS_K0, 0x0020), MIPS_ADDIU(MIPS_K0, MIPS_K0, 0x2460), MIPS_JR(MIPS_K0), MIPS_NOP },
        { 0, 0, 0, 0, 0 },
        { MIPS_LUI(MIPS_K0, 0x8000), MIPS_ORI(MIPS_K0, MIPS_K0, 0x0014), MIPS_JR(MIPS_K0), MIPS_NOP },
    },
};
#endif
