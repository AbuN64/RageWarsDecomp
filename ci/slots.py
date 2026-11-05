import re, subprocess, sys
from pathlib import Path
missing = set()
# A slot runs from one `. =` to the next one in the same output section; the last slot of an output section ends where
# that section ends in the ROM layout: the load address (AT) of the next output section above it. GNU ld places an
# input section at the first statement that names it, so a later statement naming the same obj(section) is empty.
V = sys.argv[1] if len(sys.argv) > 1 else 'us'
ld = open('build/' + V + '/link.ld').read().splitlines()
sizes = {}
def secs(obj):
    if obj in sizes: return sizes[obj]
    path = 'build/' + V + '/' + obj
    if not Path(path).is_file():
        missing.add(obj)
        print('MISSING', obj, file=sys.stderr)
        sizes[obj] = {}
        return {}
    out = subprocess.run(['mips-linux-gnu-objdump', '-h', path], capture_output=True, text=True, check=True).stdout
    d = {}
    for l in out.splitlines():
        p = l.split()
        if len(p) > 2 and p[1].startswith('.'): d[p[1]] = int(p[2], 16)
    sizes[obj] = d; return d
HEAD = re.compile(r'^\s*\.\S+\s+0x[0-9A-Fa-f]+\s*(?:\(NOLOAD\))?\s*:\s*AT\((0x[0-9A-Fa-f]+)\)')
ats = sorted({int(m.group(1), 16) for m in map(HEAD.match, ld) if m})
def close(group, start, end):
    if not group or start is None or end is None: return
    total = sum(secs(o).get(s, 0) for o, s, _ in group)
    if total > end - start:
        o, s, ln = group[0]
        print('OVER', ln, '+'.join(g[0] for g in group), s, 'size', hex(total), 'slot', hex(end - start))
seen = set(); cur = None; group = []; secend = None
for i, l in enumerate(ld, 1):
    h = HEAD.match(l)
    if h:
        at = int(h.group(1), 16); nxt = [a for a in ats if a > at]
        secend = nxt[0] - at if nxt else None; cur = 0; group = []; continue
    if l.strip() == '}':
        close(group, cur, secend); cur = None; group = []; continue
    m = re.search(r'\. = (?:MAX\(\., )?(0x[0-9A-Fa-f]+)', l)
    if m:
        a = int(m.group(1), 16); close(group, cur, a); group = []; cur = a
    m2 = re.match(r'\s*(\S+\.o)\((\.\S+)\);', l)
    if m2: secs(m2.group(1))
    if m2 and cur is not None and (m2.group(1), m2.group(2)) not in seen:
        seen.add((m2.group(1), m2.group(2))); group.append((m2.group(1), m2.group(2), i))

print("COVERAGE", V, "objects", len(sizes), "missing", len(missing), file=sys.stderr)
if missing: sys.exit(1)
