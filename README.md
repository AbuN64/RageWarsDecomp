# Turok: Rage Wars decompilation

A matching decompilation of *Turok: Rage Wars* for the Nintendo 64.

> **This repository contains no game content.** You must supply a legally acquired cartridge dump. Builds are verified against its SHA256.

## Progress

<!-- progress -->
<pre><code>all      [███████████████████░]  99.79% (~99.99%)  41,859,058 of 41,943,040 bytes, linker fill 436 bytes, unknown 2,101 bytes</code><br><code>de       [███████████████████░]  99.12% (~99.99%)  8,315,190 of 8,388,608 bytes, linker fill 184 bytes</code><br><code>eu       [███████████████████░]  99.99%  8,388,387 of 8,388,608 bytes, linker fill 76 bytes, unknown 145 bytes</code><br><code>eu-x     [███████████████████░]  99.87% (~99.97%)  8,378,501 of 8,388,608 bytes, linker fill 44 bytes, unknown 1,956 bytes</code><br><code>us       [███████████████████░]  99.99%  8,388,440 of 8,388,608 bytes, linker fill 64 bytes</code><br><code>us-rev1  [███████████████████░]  99.99%  8,388,540 of 8,388,608 bytes, linker fill 68 bytes</code></pre>

<a href="https://itsmo.me/attic/cake-unbake/#ragewars-decomp-us-rev1"><img src="docs/overview-us-rev1.svg" width="720"></a>

| de (NUS-NRWD-0, Germany). Censored German release. SHA256 `9dc401252bacb2ad7412ef003f97f28cb225d76b3cc76f430fbc27fa05067ca8` |
|---|
| <pre><code>code      [████████████████████]  100.00%  1,109,460 of 1,109,460</code><br><code>data      [████████████████████]  100.00%  254,998 of 254,998</code><br><code>functions [████████████████████]  100.00%  4,249 of 4,249</code><br><code>blobs     [███████████████████▒]  98.95% (~100.00%)  6,914,444 of 6,987,678</code></pre> |

| eu (NUS-NRWP-0, Europe). PAL release. SHA256 `d763cbbe485a5f9e1b7be97d5ac16735087e23d0bb62c05dc844e01b7e1156d1` |
|---|
| <pre><code>code      [████████████████████]  100.00%  1,114,888 of 1,114,888</code><br><code>data      [████████████████████]  100.00%  346,720 of 346,720</code><br><code>functions [████████████████████]  100.00%  4,254 of 4,254</code><br><code>blobs     [████████████████████]  100.00%  6,906,587 of 6,906,587</code></pre> |

| eu-x (NUS-NRWX-0, Europe). PAL multi-language release. SHA256 `511f6c876586bf401faf01a270c67f26fcb7db55ed3f35759c71ab15a29de750` |
|---|
| <pre><code>code      [████████████████████]  100.00%  1,115,612 of 1,115,612</code><br><code>data      [████████████████████]  100.00%  251,952 of 251,952</code><br><code>functions [████████████████████]  100.00%  4,256 of 4,256</code><br><code>blobs     [███████████████████▒]  99.88% (~100.00%)  6,990,745 of 6,998,852</code></pre> |

| us (NUS-NRWE-0, North America). First NTSC release (black cartridge). SHA256 `0433043aaba2649bdd1fe717c4020550ac663c0362527aa082490f5977a3e46b` |
|---|
| <pre><code>code      [████████████████████]  100.00%  1,160,704 of 1,160,704</code><br><code>data      [████████████████████]  100.00%  208,136 of 208,136</code><br><code>functions [████████████████████]  100.00%  4,325 of 4,325</code><br><code>blobs     [███████████████████▒]  99.99% (~100.00%)  6,999,408 of 6,999,512</code></pre> |

| us-rev1 (NUS-NRWE-1, North America). Revised NTSC release (grey cartridge). SHA256 `5dfbae59e4a3860b740ccbb28f33aad624315e30bfca6d60abd62d12a89e0089` |
|---|
| <pre><code>code      [████████████████████]  100.00%  1,132,592 of 1,132,592</code><br><code>data      [████████████████████]  100.00%  237,616 of 237,616</code><br><code>functions [████████████████████]  100.00%  4,355 of 4,355</code><br><code>blobs     [████████████████████]  100.00%  6,998,140 of 6,998,140</code></pre> |
<!-- /progress -->

## Development & Contributions

Contributions and corrections are welcome. Run `make check` before opening a pull request.

For detailed instructions please see [CONTRIBUTING.md](CONTRIBUTING.md).

## License

[CC0 1.0](LICENSE)

## Dependencies

<!-- dependencies -->
- [GCC 2.8.1](https://github.com/pmret/gcc-papermario)
- [abumas](https://github.com/AbuN64/mas-n64)
<!-- /dependencies -->

