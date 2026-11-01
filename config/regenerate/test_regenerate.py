"""Unit tests for tools/regenerate: `mo-butlermaster` is a fake that answers Job Invoke by running the Argv in a job root on
this machine (one tree per board.card, as Job Invoke keeps it), so the whole flow takes seconds. Scratch directories live
under the repository's ignored build/ folder, never /tmp."""
import importlib.machinery
import importlib.util
import json
import os
import re
import shutil
import subprocess
import tempfile
import tomllib
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
SCRIPT = os.path.join(ROOT, "tools", "regenerate")
SCRATCH = os.path.join(ROOT, "build")
REPOSITORY = "Projects/Test/Repo"

FAKE_BUTLERMASTER = """#!/usr/bin/env python3
# mo-butlermaster Job Invoke --input=json --output=json: record the request, run its Argv in the job's Worktree.
import json, os, subprocess, sys
assert sys.argv[1:3] == ["Job", "Invoke"] and "--input=json" in sys.argv, sys.argv
request = json.load(sys.stdin)["Request"]
with open(os.environ["FAKE_CALLS"], "a") as handle:
    handle.write(json.dumps(request) + "\\n")
if os.environ.get("FAKE_REFUSE"):
    print(json.dumps({"Metadata": {"Result": "Error"}, "Response": {"Error": {
        "Code": "Invalid", "Message": "unknown host", "NextStep": "Name a host of the Hosts", "Status": 400}}}))
    sys.exit(1)
repository, _, sha = request["Worktree"].partition("@")
subject = request["Subject"]
box = os.path.join(os.environ["FAKE_JOB_ROOT"], subject["Board"] + "." + subject["Card"], repository)
if os.path.isdir(box):
    subprocess.run(["git", "-C", box, "checkout", "-q", "--detach", sha], check=True)
else:
    os.makedirs(os.path.dirname(box), exist_ok=True)
    subprocess.run(["git", "-C", os.environ["FAKE_SOURCE"], "worktree", "add", "-q", "--detach", box, sha], check=True)
log = os.path.join(os.environ["FAKE_JOB_ROOT"], "job-%d.log" % len(open(os.environ["FAKE_CALLS"]).readlines()))
with open(log, "w") as out:
    code = subprocess.run(request["Argv"], cwd=box, stdout=out, stderr=subprocess.STDOUT,
                          env=dict(os.environ, JOBS="3")).returncode
print(json.dumps({"Metadata": {"Result": "Success"}, "Response": {
    "Exit": code, "Host": request["Host"], "Log": log, "Subject": subject, "Width": 3}}))
"""

FAKE_TOOL = """#!/bin/sh
echo "$(basename "$0") $*" >> "$HOME/calls.log"
"""

CONFIG = """[rig]
host = "rig"
repository = "%s"
seed_tree = "code/seed"
seed_link = ["roms"]
build = [%%s]
""" % REPOSITORY


def git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True,
                          env=dict(os.environ, GIT_AUTHOR_NAME="t", GIT_AUTHOR_EMAIL="t@t",
                                   GIT_COMMITTER_NAME="t", GIT_COMMITTER_EMAIL="t@t")).stdout


def load_script():
    loader = importlib.machinery.SourceFileLoader("regenerate", SCRIPT)
    module = importlib.util.module_from_spec(importlib.util.spec_from_loader("regenerate", loader))
    loader.exec_module(module)
    return module


class Regenerate(unittest.TestCase):
    build = ('"mkdir -p build && echo run >> build/log", "printf \'built from %s\\n\' \\"$(cat src.txt)\\" > README.md", '
             '"echo state > docs/state.txt", "rm -f docs/gone.txt"')

    def setUp(self):
        os.makedirs(SCRATCH, exist_ok=True)
        self.dir = tempfile.mkdtemp(prefix="regenerate-test-", dir=SCRATCH)
        self.addCleanup(shutil.rmtree, self.dir, True)
        self.home = os.path.join(self.dir, "home")
        self.jobs = os.path.join(self.dir, "jobs")
        self.tree = os.path.join(self.dir, "runs", "board1.card1", REPOSITORY)
        self.calls = os.path.join(self.dir, "calls.jsonl")
        bin_dir = os.path.join(self.dir, "bin")
        for path in (bin_dir, self.jobs, os.path.join(self.home, "code/seed/roms"),
                     self.tree + "/tools", self.tree + "/config/regenerate", self.tree + "/docs"):
            os.makedirs(path)
        open(self.calls, "w").close()
        for path, body in ((bin_dir + "/mo-butlermaster", FAKE_BUTLERMASTER),
                           (bin_dir + "/unbake", FAKE_TOOL), (bin_dir + "/make", FAKE_TOOL)):
            with open(path, "w") as handle:
                handle.write(body)
            os.chmod(path, 0o755)
        shutil.copy(SCRIPT, self.tree + "/tools/regenerate")
        self.write("config/regenerate/rig.toml", CONFIG % self.build)
        self.write(".gitignore", "build/\n")
        self.write(".gitattributes",
                   "README.md generated=tools/regenerate\ndocs/** generated=tools/regenerate\n"
                   "keep.txt merge=union\n")
        self.write("src.txt", "one\n")
        self.write("README.md", "stale\n")
        self.write("docs/state.txt", "stale\n")
        self.write("docs/gone.txt", "no longer generated\n")
        git(self.tree, "init", "-q")
        git(self.tree, "add", "-A")
        git(self.tree, "commit", "-q", "-m", "base")
        self.env = dict(os.environ, PATH=bin_dir + ":" + os.environ["PATH"], HOME=self.home, FAKE_CALLS=self.calls,
                        FAKE_JOB_ROOT=self.jobs, FAKE_SOURCE=self.tree)
        self.box = os.path.join(self.jobs, "board1.card1", REPOSITORY)

    def write(self, name, text):
        path = os.path.join(self.tree, name)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w") as handle:
            handle.write(text)

    def read(self, name, base=None):
        with open(os.path.join(base or self.tree, name)) as handle:
            return handle.read()

    def requests(self):
        with open(self.calls) as handle:
            return [json.loads(row) for row in handle]

    def regenerate(self, **extra):
        return subprocess.run([self.tree + "/tools/regenerate"], cwd=self.tree, capture_output=True,
                              text=True, env=dict(self.env, **extra))

    def test_job_runs_at_the_state_sha_and_only_declared_paths_come_back(self):
        self.write("src.txt", "two\n")  # uncommitted edit must reach the job
        self.write("untracked.txt", "kept\n")
        done = self.regenerate()
        self.assertEqual(done.returncode, 0, done.stderr)
        (request,) = self.requests()
        self.assertEqual((request["Host"], request["Subject"]), ("rig", {"Board": "board1", "Card": "card1"}))
        self.assertRegex(request["Worktree"], "^" + REPOSITORY + "@[0-9a-f]{40}$")
        self.assertEqual(request["Argv"][:2], ["sh", "-c"])  # Argv is a list, never one shell line
        self.assertEqual(self.read("README.md"), "built from two\n")
        self.assertEqual(self.read("docs/state.txt"), "state\n")
        self.assertEqual(self.read("untracked.txt"), "kept\n")
        self.assertEqual(self.read("src.txt"), "two\n")
        self.assertFalse(os.path.exists(self.tree + "/docs/gone.txt"), "stale generated file survives")
        self.assertEqual(git(self.tree, "diff", "--cached", "--name-only"), "", "real index touched")
        self.assertEqual([n for n in os.listdir(self.tree) if n.startswith(".regenerate")], [])

    def test_the_job_root_is_reused_warm_and_left_clean(self):
        self.assertEqual(self.regenerate().returncode, 0)
        self.write("src.txt", "two\n")
        done = self.regenerate()
        self.assertEqual(done.returncode, 0, done.stderr)
        self.assertEqual(self.read("README.md"), "built from two\n")
        self.assertEqual(self.read("build/log", self.box), "run\nrun\n")  # one tree: its ignored build state stayed
        self.assertEqual(git(self.box, "status", "--porcelain"), "")
        self.assertEqual(os.listdir(self.jobs).count("board1.card1"), 1)
        self.assertEqual(len(self.requests()), 2)

    def test_seed_is_linked_when_the_tree_is_created(self):
        self.write("config/regenerate/rig.toml", CONFIG % '"readlink roms > README.md", "echo ok > docs/state.txt"')
        self.assertEqual(self.regenerate().returncode, 0)
        self.assertEqual(self.read("README.md"), self.home + "/code/seed/roms\n")
        self.assertEqual(git(self.box, "status", "--porcelain"), "", "the linked seed was committed or left untracked")

    def test_build_failure_names_the_log_and_writes_nothing(self):
        self.write("config/regenerate/rig.toml",
                   CONFIG % '"echo partial > README.md", "echo rig says no >&2; false"')
        done = self.regenerate()
        self.assertEqual(done.returncode, 1)
        self.assertIn("rig says no", done.stderr)
        self.assertIn(os.path.join(self.jobs, "job-1.log"), done.stderr)
        self.assertEqual(self.read("README.md"), "stale\n")
        self.assertEqual(self.read("docs/gone.txt"), "no longer generated\n")
        self.assertEqual(git(self.box, "status", "--porcelain"), "", "a failed build left the job tree dirty")
        self.write("config/regenerate/rig.toml", CONFIG % self.build)  # and the next run still works
        self.assertEqual(self.regenerate().returncode, 0)
        self.assertEqual(self.read("README.md"), "built from one\n")

    def test_nonzero_exit_passes_through(self):
        self.write("config/regenerate/rig.toml", CONFIG % '"exit 7"')
        done = self.regenerate()
        self.assertEqual((done.returncode, "failed (7)" in done.stderr), (1, True))

    def test_job_invoke_refusal_fails_with_its_code_and_next_step(self):
        done = self.regenerate(FAKE_REFUSE="1")
        self.assertEqual(done.returncode, 1)
        for word in ("Invalid", "unknown host", "Name a host of the Hosts"):
            self.assertIn(word, done.stderr)
        self.assertEqual(self.read("README.md"), "stale\n")

    def test_undeclared_tree_fails_naming_the_log(self):
        self.write(".gitattributes", "keep.txt merge=union\n")
        done = self.regenerate()
        self.assertEqual(done.returncode, 1)
        self.assertIn("generated=tools/regenerate", done.stderr)
        self.assertIn("job-1.log", done.stderr)
        self.assertEqual(self.read("docs/gone.txt"), "no longer generated\n")

    def test_a_job_that_prints_no_archive_fails_naming_the_log(self):
        module = load_script()
        log = os.path.join(self.dir, "plain.log")
        with open(log, "w") as handle:
            handle.write("setup done\nmake done\n")
        module.job_invoke = lambda *args: (0, log)
        with self.assertRaises(module.Failure) as raised:
            module.regenerate(self.tree)
        self.assertIn("printed no generated archive", str(raised.exception))
        self.assertIn(log, str(raised.exception))

    def test_a_run_outside_a_run_folder_has_no_identity(self):
        module = load_script()
        self.assertEqual(module.identity("/runs/b1.c1/" + REPOSITORY, REPOSITORY), ("b1", "c1"))
        for root in ("/work/" + REPOSITORY, "/runs/b1c1/" + REPOSITORY, "/runs/b1.c1/other"):
            with self.assertRaises(module.Failure):
                module.identity(root, REPOSITORY)

    def test_the_rigs_own_build_links_and_checks_once_at_dos_width(self):
        """The committed rig.toml: one setup, one make check at JOBS, one sync, never a literal width or a slot."""
        with open(os.path.join(ROOT, "config", "regenerate", "rig.toml"), "rb") as handle:
            rig = tomllib.load(handle)["rig"]
        build = rig["build"]
        self.assertEqual(sum(row.startswith("make ") for row in build), 1)
        self.assertEqual(sum(row.startswith("unbake setup") for row in build), 1)
        self.assertEqual(sum(row.startswith("unbake sync") for row in build), 1)
        self.assertIn('make -j"$JOBS" check', build)
        self.assertEqual((rig["host"], rig["repository"]), ("rig", REPOSITORY.replace("Test/Repo", "AbuN64/RageWars")))
        self.write("config/regenerate/rig.toml", CONFIG % ", ".join('"%s"' % row.replace('"', '\\"') for row in build))
        done = self.regenerate()
        self.assertEqual(done.returncode, 0, done.stderr)
        self.assertEqual(self.read("calls.log", self.home), "unbake setup --no-make\nmake -j3 check\n"
                         "unbake verify 0\nunbake sync\n")

    def test_no_slot_lock_wait_or_ssh_path_is_left(self):
        text = ""
        for path in (SCRIPT, os.path.join(ROOT, "config", "regenerate", "rig.toml")):
            with open(path) as handle:
                text += handle.read()
        self.assertIsNone(re.search(r"finish/slot|flock|waitfor|FINISH_JOBS|\bssh\b|warm", text), text)

    def test_bound_is_the_configs_and_message_tail(self):
        module = load_script()
        rig = {"build": ["a", "b"], "repository": "r", "seed_tree": "s"}
        self.assertEqual(module.build_argv(rig, "c0ffee")[:2], ["sh", "-c"])
        self.assertEqual(module.build_argv(dict(rig, timeout_seconds=90), "c0ffee")[:3], ["timeout", "90", "sh"])
        self.assertEqual(module.tail("\n".join(map(str, range(100))), 3), "...\n97\n98\n99")


if __name__ == "__main__":
    unittest.main()
