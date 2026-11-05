#!/usr/bin/env python3
"""List the cinema track table of a RageWars ROM: key -> resource name.

Track_RequestTrackByKey (Source/Menu/track.cpp) reads section 0 of the cinema
bank, section 18 of the scene cartridge directory (Source/Ovlgame/scene.cpp).
That section is a record block: a big-endian (entry size, count) header and
count rows of entry size 0x4C: id0, id4, key, flags, two words, then a
NUL-ended name at +0x18. Usage: tracks.py roms/baserom.<version>.z64"""
import struct
import sys

ENTRY = 0x4C
NAME = 0x18


def rows_at(rom, at):
    """Return [(key, name)] for the record block at `at`, or None."""
    if at + 8 > len(rom):
        return None
    size, count = struct.unpack_from('>II', rom, at)
    if size != ENTRY or not 1 <= count <= 512 or at + 8 + count * ENTRY > len(rom):
        return None
    rows = []
    for i in range(count):
        row = at + 8 + i * ENTRY
        raw = rom[row + NAME:row + ENTRY]
        end = raw.find(b'\0')
        name = raw[:end if end >= 0 else len(raw)]
        if not name or not all(32 <= b < 127 for b in name):
            return None
        rows.append((struct.unpack_from('>i', rom, row + 8)[0], name.decode('ascii')))
    return rows


def find_tables(rom):
    for at in range(0, len(rom) - 8, 4):
        rows = rows_at(rom, at)
        if rows:
            yield at, rows


def main(argv):
    rom = open(argv[1], 'rb').read()
    found = 0
    for at, rows in find_tables(rom):
        found += 1
        print('table rom:0x%X rows %d' % (at, len(rows)))
        for key, name in rows:
            print('%6d %s' % (key, name))
    if not found:
        print('no track table in %s' % argv[1], file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
