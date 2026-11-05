"""Exercise both settings writers with mocked widget reads and four real record strides.

Usage: python3 Source/Menu/test_player_settings.py <scratch-directory>
"""
from pathlib import Path
import subprocess
import sys
import tempfile

source = Path(__file__).with_name("player.cpp").read_text()
functions = []
for name in ("Player_StorePlayerSettingsEntry", "Player_StoreAlternatePlayerSettingsEntry"):
    start = source.index("void " + name + "(")
    end = source.index("\n}", start) + 2
    functions.append(source[start:end])
header = (Path(__file__).parents[2] / "Include/Common/gameplay_settings.h").read_text()
start = header.index("struct Shared_PlayerSettingsRecord {")
end = header.index("\n};", start) + 3
record = header[start:end]
harness = r'''#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
typedef uint8_t u8; typedef int8_t s8; typedef int16_t s16; typedef int32_t s32;
'''
harness += record + r'''typedef struct Shared_PlayerSettingsRecord Shared_PlayerSettingsRecord;
static Shared_PlayerSettingsRecord g_playerSettings[4];
static u8 g_profileSlotSettingsPrimaryListSelection[1600];
static u8 g_profileSlotSettingsSecondaryListSelection[1600];
static u8 g_profileSlotSettingsPrimarySliderItem[1600];
static u8 g_profileSlotSettingsSecondarySliderItem[1600];
static u8 g_profileSlotSettingsExtraListSelection[1600];
static struct { int a,b,c,d,e; } screen = {11,22,33,44,55}, *g_playerSettingsScreen = &screen;
static struct { int listA,listB,panels[2],listC; } alternate = {61,72,{83,94},105}, *g_alternatePlayerSettingsScreen = &alternate;
static int calls;
static int SmpButton_GetListSelection(int id) { ++calls; return id; }
static int SmpSlider_GetSliderItem(int id) { ++calls; return id; }
'''
harness += "\n".join(functions)
harness += r'''int main(void) {
    int variant,slot,byte,checks=0;
    const int offsets[] = {123,125,121,122,130};
    const int values[2][5] = {{11,22,33,44,55},{61,72,83,94,105}};
    assert(sizeof(Shared_PlayerSettingsRecord) == 150);
    for (variant=0; variant<2; ++variant) for (slot=0; slot<4; ++slot) {
        unsigned char expected[sizeof(g_playerSettings)];
        memset(g_playerSettings,0xa5,sizeof(g_playerSettings));
        memset(expected,0xa5,sizeof(expected));
        for (byte=0; byte<5; ++byte) expected[150*slot+offsets[byte]]=values[variant][byte];
        calls=0;
        if (variant) Player_StoreAlternatePlayerSettingsEntry(slot);
        else Player_StorePlayerSettingsEntry(slot);
        assert(calls==5);
        assert(memcmp(expected,g_playerSettings,sizeof(expected))==0);
        assert(g_profileSlotSettingsPrimaryListSelection[400*slot]==values[variant][0]);
        assert(g_profileSlotSettingsSecondaryListSelection[400*slot]==values[variant][1]);
        assert(g_profileSlotSettingsPrimarySliderItem[400*slot]==values[variant][2]);
        assert(g_profileSlotSettingsSecondarySliderItem[400*slot]==values[variant][3]);
        assert(g_profileSlotSettingsExtraListSelection[400*slot]==values[variant][4]);
        ++checks;
    }
    printf("player settings passed %d slot and writer cases, including neighbor isolation\n",checks);
    return 0;
}
'''
with tempfile.TemporaryDirectory(prefix="player-settings-", dir=sys.argv[1]) as temporary:
    path = Path(temporary)
    (path / "test.c").write_text(harness)
    subprocess.run(["cc", "-std=c99", "-Wall", "-Werror", str(path / "test.c"), "-o", str(path / "test")], check=True)
    subprocess.run([str(path / "test")], check=True)
