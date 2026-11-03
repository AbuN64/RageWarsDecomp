# OnSync case 4 register spill gap

One attempt from HIDDEN-FRONTEND/w/f5.c changed the case 4 subtraction to `-(x >= x - 1) + x`, retaining the surrounding conditional. The rig compiled it through the Makefile at SN GCC 2.8.1 -O0, without -mgas, and ran the unrelocated-object pass. It did not match and is not linked.

Reference: 988 bytes. Attempt: 1004 bytes. Normalized comparison: 241 word positions differ, dominated by shifted instructions after the changed prologue. Reference begins `27bdffe8 afbf0014 afbe0010 03a0f021`; attempt begins `27bdffe0 afbf0018 afbe0014 afb00010 03a0f021`. The extra `sw s0,16(sp)` and 32-byte rather than 24-byte frame show the saved-register lifetime remains. Reference case 4 computes the flag before loading x: at offset 0x298 `lw a1,80(a0)`, then 0x29C `subu v1,a1,v1`. Reversing the arithmetic spelling did not remove the spill. The original ROM bytes remain linked.

Evidence: parent card rig job rig-20261102T231710Z, ONSYNC_ATTEMPT in job.log; original f5.ann and f5.bin in the HIDDEN-FRONTEND lane. No second attempt was made.

## Retained input and compile provenance

The coordinator authorized importing only these two OnSync paths. The gap text
was retained from parent wip `0d314eb4a`; the shared boundary and OnAccept changes
were not replayed. Parent commits `81b86fd89`, `84f899224`, `54b43ec5f` and
`775b8587f` remain retained.

`PAKINTERFACE_ONSYNC.CPP` is the exact 2512-byte source payload from the parent
job request, still named `f5`, with SHA-256
`36ea48ed9684c8d21459450592884c86dcfd1b617599599655ae101fb9c778ab`.
It preserves the one `-(flag)+x` case 4 attempt verbatim. There was no new
source variant. No Makefile, linker section, version selector or embedded
resource byte was changed to select it.

The parent job request compiled that payload as `.tmp/onsync.c` with:

```sh
make -j"$JOBS" build/us/.tmp/onsync.c.o \
  CFLAGS="-G0 -mips3 -O0 -meb -mcpu=VR4300 -mhard-float -mgp32 -mfp64 -mno-fix4300" \
  UNRELOC=1
mips-linux-gnu-objcopy -O binary -j .text \
  build/us/.tmp/onsync.c.o .tmp/onsync-text.bin
```

The reference is `.tmp/onsync-reference.bin`, the 988-byte payload retained in
that request. The comparison examined all 247 overlapping instruction words:
241 differ after masking J/JAL targets and treating `or` moves as `addu` moves.
The raw comparison likewise differs at 241 of 247 word positions (615 byte
positions). The candidate also has 16 bytes beyond the reference. This normalization is a
diagnostic only; acceptance requires a complete exact comparison.

The parent's completed answer and log were read. Its object files were no
longer available from the retained run. The coordinator authorized repeating
the identical compile for instruction measurement, without changing its source.

## Instruction measurement

The unchanged-source remeasurement in job `rig-20261103T023658Z` reproduced
1004 bytes and 241 normalized mismatched words. The preceding preparation used
the gate's ROM acquisition and `unbake setup --no-make`; the compile command
above was unchanged. Artifact identities (SHA-256):

- `.tmp/onsync-reference.bin`:
  `b5900c5527ee57c243cb88f3d430f0fd59eaa02cf6b112a7b3b5814ce39c4cd0`
- `.tmp/onsync-text.bin`, extracted from `build/us/.tmp/onsync.c.o`:
  `2f7dd8c1b96e9aabb5107dad82a193f4fdcf082bee185da5f35c5c39f8113778`

| Offset | Reference | Unchanged attempt |
|---|---|---|
| `0x000` | `27bdffe8 addiu sp,sp,-24` | `27bdffe0 addiu sp,sp,-32` |
| `0x004` | `afbf0014 sw ra,20(sp)` | `afbf0018 sw ra,24(sp)` |
| `0x008` | `afbe0010 sw s8,16(sp)` | `afbe0014 sw s8,20(sp)` |
| `0x00c` | `03a0f021 move s8,sp` | `afb00010 sw s0,16(sp)` |
| `0x298` | `8c850050 lw a1,80(a0)` | `8c840050 lw a0,80(a0)` |
| `0x29c` | `00a31823 subu v1,a1,v1` | `0085282a slt a1,a0,a1` |

Reference saves only `ra` and `s8` (frame pointer), restores them at `0x3c8`
and `0x3cc`, releases 24 bytes at `0x3d0`, and returns at `0x3d4` with its
delay slot at `0x3d8`. Candidate additionally saves `s0`, restores `ra`, `s8`
and `s0` at `0x3d4`, `0x3d8`, `0x3dc`, releases 32 bytes at `0x3e0`, and
returns at `0x3e4` with its delay slot at `0x3e8`.

The cause is visible inside case 4, beyond the shifted prologue: the candidate
loads x into `s0` at `0x278` (`8c700050`), copies it into `v1` at `0x27c`,
then computes the comparison at `0x29c` and branches at `0x2a0`. The branch
conditionally decrements that earlier x at `0x2a8` (`2463ffff addiu v1,v1,-1`).
The reference instead materializes the flag with `slt`/`xori` at `0x288` and
`0x28c`, reloads x into `a1` at `0x298`, then subtracts the flag at `0x29c`.
Changing the source arithmetic order did not force that instruction order or
eliminate the saved register. This is the named **OnSync case 4 register spill
gap**; the embedded original remains the linked implementation.
