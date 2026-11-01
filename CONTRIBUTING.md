# Contributing to Turok: Rage Wars

## Build

You need GNU Make, curl, tar, sha256sum, python3, cpp, the MIPS binutils (`mips-linux-gnu-as`, `-ld`, `-objcopy`)
and splat:

```sh
python3 -m pip install -r requirements.txt
```

Put your own big-endian cartridge dumps at these paths:

- `roms/baserom.de.z64`
- `roms/baserom.eu.z64`
- `roms/baserom.eu-x.z64`
- `roms/baserom.us.z64`
- `roms/baserom.us-rev1.z64`

```sh
make
```

`make` (the same as `make check`) splits each dump into `asm/<version>/` with splat the first time (`make extract`
does it again), then builds every version and verifies each ROM's SHA-1. The compilers and abumas are downloaded
into `tools/` and checked against their pinned SHA-256 hashes. Tool commands default to conventional names; put
other paths in `local.mk`.

## Pull requests

Run `make` before opening a pull request; every version must still match.

## Merging sources that the linker keeps in several output sections

A module whose units sit in different output sections inside one version (for example some in an overlay section and
the rest in the resident one) cannot merge as one source. `unbake layout mergecheck` prints the parts of such a module
(`sections: <class> parts: N: <section> [units]`); split the module row of the map into one row per part, named
`<module stem>_<output section>`, and merge each part. A module whose units only link in another order in one version
is not split: merge emits that version's order under the guard of its version macro.
