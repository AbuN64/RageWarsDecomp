# Generated files

Run `unbake setup`, then `unbake sync`, then `make check` in a private build tree with the configured toolchain and ROMs. `ci/gate` uses that sequence.

`ci/generated-outputs.txt` inventories disposable setup/sync output. The linker script and all five version split configurations and text-size fragments are required before Make expands build recipes. Both matching objects and nmraw objects read the same mandatory text-size fragments. Checkout must never restore those fragments.

Makefile, layout.mk and Include/include_asm.h are authored build inputs. Normal setup/sync preserves the Makefile and header when present. Do not request `sync --makefile`: that explicitly replaces the authored build rules. The former layout and merge regeneration script is retired; layout.mk is maintained with config.toml's layout.

The current external scaffold still replaces .gitignore, and report publishing still rewrites the generated block in the authored README. Reports depend on a completed build and are not build prerequisites. Those writer contracts must be corrected in CakeUnbake before all generated-output acceptance checks can pass; this repository does not patch the installed generator.
