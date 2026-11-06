"""Check each EU collision target against its named regional symbol."""
import pathlib
import re
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[3]


def targets_match(rows, symbols):
    return all(address == symbols[name] + offset for address, name, offset in rows)


class CollisionTableTargets(unittest.TestCase):
    def setUp(self):
        source = pathlib.Path(__file__).with_name("node_resource_and_collision_link_data.cpp").read_text()
        table = source.split("CCollisionSetup_t g_collisionSetupTable[36] = {", 1)[1].split("};", 1)[0]
        self.rows = [(int(address, 16), name, int(offset, 16)) for address, name, offset in
                     re.findall(r"\(CCollisionInfo2_t \*\)(0x[0-9A-Fa-f]+) /\* eu (\w+) \+ (0x[0-9A-Fa-f]+)", table)]
        self.symbols = {name: int(address, 16) for name, address in
                        re.findall(r"^(\w+) = (0x[0-9A-Fa-f]+);", (ROOT / "versions/eu/symbol_addrs.txt").read_text(), re.M)}

    def test_all_eu_targets(self):
        self.assertEqual(len(self.rows), 35)
        self.assertTrue(targets_match(self.rows, self.symbols))

    def test_eux_target_in_eu_table_is_rejected(self):
        address, name, offset = self.rows[0]
        self.assertEqual(address, 0x80110458)
        self.assertFalse(targets_match([(0x8010A458, name, offset)], self.symbols))


if __name__ == "__main__":
    unittest.main()
