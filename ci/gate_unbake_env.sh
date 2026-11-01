# Sourced by .gate with $1 = the handed CakeUnbake64 tree (empty when the job was not handed one):
# choose the unbake the gate runs.
# A gate job handed the card's own CakeUnbake64 gets it as WORKTREE_Projects_AbuN64_CakeUnbake64,
# which .gate passes in
# (mo-butlermaster Job Invoke --Worktrees: the rest sit beside the working tree as WORKTREE_<repo>).
# When that is set, build a scratch venv in the job's own TMPDIR from that tree and put only its
# unbake commands first on PATH (python3 stays the installed one); when it is not set the installed
# unbake runs unchanged.
if [ -n "${1:-}" ]; then
  gate_venv="${TMPDIR:?job TMPDIR unset}/gate-unbake-venv" &&
    python3 -m venv "$gate_venv" &&
    "$gate_venv/bin/pip" install -q "$1" &&
    mkdir -p "$gate_venv/shim" &&
    ln -sf "$gate_venv/bin/unbake" "$gate_venv/bin/unbake-run" "$gate_venv/shim/" &&
    PATH="$gate_venv/shim:$PATH" || return 1
fi
echo "gate unbake: $(command -v unbake)"
