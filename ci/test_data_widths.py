#!/usr/bin/env python3
"""Data tables retyped to their readers' widths stay retyped.

A match on big-endian MIPS cannot see a table defined as 32-bit words and read at another width; a little-endian port
can. Every symbol below was listed by the CakeUnbake width census and retyped to the element type its readers use.
The test refuses any of them defined again as `unsigned int` words in C or as a `.word` blob in assembly.
Each width card of the decomp adds its own symbols to SYMBOLS under its own heading.
"""
import re
import subprocess
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

SYMBOLS = {
    # Source/Engine/ (card wiqYJPnA790-): every name the width census listed with a C definition under Source/Engine/
    # read at another width, with the file that now defines it at its readers' width.
    "g_audioInitdecodestreamDataConstantWords": "Source/Engine/Audio/decoder.cpp",
    "g_dialogDefaultSample": "Source/Engine/Audio/RAXPlayer.cpp",
    "g_graphicsMicrocodeText": "Source/Engine/Audio/decoder.cpp",
    "g_rootMotionRestartUnsignedBias": "Source/Engine/Anim/GAState.cpp",
    "g_rotationTrackLowerKeySpanTestBias": "Source/Engine/Anim/compressed_motion.cpp",
    "g_sampleTrackUnsignedConversionBias": "Source/Engine/Anim/compressed_motion.cpp",
    "g_affinePackUnsignedConversionThresholds": "Source/Engine/Instance/gobjinst.cpp",
    "g_optionsSecondaryLocalizedLabels": "Source/Engine/Audio/decoder.cpp",
    "g_sessionFrameRenderState": "Source/Engine/session.cpp",
    "g_schedulerState": "Source/Engine/scheduler_state_data.cpp",
    "g_geometryPreviousModePresetBlock": "Source/Engine/geometry.cpp",
    "g_smackFormatTable": "Source/Engine/session.cpp",
    "g_enemyMixWordsAndLights": "Source/Engine/curve.cpp",
    "g_savedFlagToggleStorage": "Source/Engine/curve.cpp",
    "g_dialogUnsignedTimeCorrection": "Source/Engine/Audio/RAXPlayer.cpp",
    "g_packedFloatRandomBias": "Source/Engine/mattable.cpp",
    "g_randomUnsignedFloatCorrection": "Source/Engine/graphics_math.cpp",
    "g_invertAffineMatrixConstants": "Source/Engine/graphics_math.cpp",
    "g_audioPitchRatioCurveZeroWords": "Source/Engine/Audio/channel.cpp",
    "g_actorGroundRotationUnitW": "Source/Engine/Instance/gobjinst.cpp",
    "g_collisionDownwardNormalThreshold": "Source/Engine/Unicol/polycol.cpp",
    "g_audioDecodeBlock": "Source/Engine/Audio/decoder.cpp",
    "g_audioTransformBandTables": "Source/Engine/Audio/decoder.cpp",
    "g_controllerEffectTimeAdvanceScale": "Source/Engine/control.cpp",
    "g_curvePredictorShortLagCoefficients": "Source/Engine/curve.cpp",
    "g_effectCallbackFlags": "Source/Engine/geometry.cpp",
    "g_geometryAlternateMaterialDisplayList": "Source/Engine/geometry.cpp",
    "g_sessionInitializeHandlers": "Source/Engine/session.cpp",
    # the leading words of five structs, split off: gcc 2.8.1 -O2 reads a non-const scalar global with its own
    # lui/%lo pair per access and a struct's fields through one base register, so the cartridge's readers read
    # separate scalar globals there
    "g_pointLightSavedBufferOffset": "Source/Engine/curve.cpp",
    "g_playerViewRenderingEnabled": "Source/Engine/curve.cpp",
    "g_schedulerTaskDuration": "Source/Engine/scheduler_state_data.cpp",
    "g_schedulerAudioDuration": "Source/Engine/scheduler_state_data.cpp",
    "g_schedulerElapsedFrameDuration": "Source/Engine/scheduler_state_data.cpp",
    "rwFrameBuildSeconds": "Source/Engine/scheduler_state_data.cpp",
    "g_maximumDisplayListBytes": "Source/Engine/session.cpp",
    "g_geometryPreviousModePreset": "Source/Engine/geometry.cpp",
    "g_geometryPreviousCombineMode": "Source/Engine/geometry.cpp",
}

# The definition each fixed name has, per defect class: its element type and size, as the readers read it.
PINNED = {
    # a table read at two widths: the table's own type, the scalar element aliases gone (the matrix fixed-point
    # conversion pairs are no table: GraphU64_PackFixedMatrix and Graphu64_ConvertMatrixToFixed write the literal
    # 65536.0f and convert to u32, and the compiler pools the literals per use; see LITERAL_POOLS)
    "g_audioInitdecodestreamDataConstantWords": r"AudioDecodeStream g_audioInitdecodestreamDataConstantWords( __attribute__\(\(aligned\(4\)\)\))? =",
    "g_dialogDefaultSample": r"DialogDefaultSample g_dialogDefaultSample =",
    "g_graphicsMicrocodeText": r"long long g_graphicsMicrocodeText\[626\] =",
    # a double the code loads as 8 bytes, declared as floats
    "g_rootMotionRestartUnsignedBias": r"const double g_rootMotionRestartUnsignedBias\[5\] =",
    "g_rotationTrackLowerKeySpanTestBias": r"const double g_rotationTrackLowerKeySpanTestBias\[10\] =",
    "g_sampleTrackUnsignedConversionBias": r"const double g_sampleTrackUnsignedConversionBias\[2\] =",
    "g_dialogUnsignedTimeCorrection": r"const double g_dialogUnsignedTimeCorrection =",
    "g_packedFloatRandomBias": r"const double g_packedFloatRandomBias =",
    "g_randomUnsignedFloatCorrection": r"const double g_randomUnsignedFloatCorrection =",
    # a float or pointer table declared at another element width
    "g_affinePackUnsignedConversionThresholds": r"const float g_affinePackUnsignedConversionThresholds\[12\] =",
    "g_optionsSecondaryLocalizedLabels": r"u8 \*g_optionsSecondaryLocalizedLabels\[1\] =",
    "g_actorGroundRotationUnitW": r"const float g_actorGroundRotationUnitW\[4\] =",
    "g_collisionDownwardNormalThreshold": r"const float g_collisionDownwardNormalThreshold =",
    "g_controllerEffectTimeAdvanceScale": r"const float g_controllerEffectTimeAdvanceScale =",
    "g_invertAffineMatrixConstants": r"const float g_invertAffineMatrixConstants\[1\] =",
    "g_curvePredictorShortLagCoefficients": r"s32 g_curvePredictorShortLagCoefficients\[4\] =",
    # a struct whose first field had a scalar alias: one named type per name
    "g_sessionFrameRenderState": r"EngineRenderState g_sessionFrameRenderState =",
    "g_schedulerState": r"EngineSchedulerState g_schedulerState =",
    "g_geometryPreviousModePresetBlock": r"EngineGeometryState g_geometryPreviousModePresetBlock =",
    "g_smackFormatTable": r"SmackFormatTable g_smackFormatTable =",
    "g_enemyMixWordsAndLights": r"EnemyMixWordsAndLights g_enemyMixWordsAndLights =",
    "g_savedFlagToggleStorage": r"SavedFlagToggleStorage g_savedFlagToggleStorage =",
    "g_audioPitchRatioCurveZeroWords": r"AudioVoicePoolState g_audioPitchRatioCurveZeroWords =",
    "g_audioTransformBandTables": r"FftTables g_audioTransformBandTables =",
    "g_audioDecodeBlock": r"DecodeBlock g_audioDecodeBlock\[4\] =",
    "g_effectCallbackFlags": r"ContactEffectEntry g_effectCallbackFlags\[37\] =",
    "g_geometryAlternateMaterialDisplayList": r"Gfx g_geometryAlternateMaterialDisplayList\[17\] =",
    "g_sessionInitializeHandlers": r"EngineSessionHandlers g_sessionInitializeHandlers\[21\] =",
    # a struct's leading word read as a scalar: its own non-const scalar definition, the struct holds the rest
    "g_pointLightSavedBufferOffset": r"s32 g_pointLightSavedBufferOffset =",
    "g_playerViewRenderingEnabled": r"s32 g_playerViewRenderingEnabled =",
    "g_schedulerTaskDuration": r"float g_schedulerTaskDuration =",
    "g_schedulerAudioDuration": r"f32 g_schedulerAudioDuration =",
    "g_schedulerElapsedFrameDuration": r"float g_schedulerElapsedFrameDuration =",
    "rwFrameBuildSeconds": r"f32 rwFrameBuildSeconds =",
    "g_maximumDisplayListBytes": r"u32 g_maximumDisplayListBytes =",
    "g_geometryPreviousModePreset": r"u32 g_geometryPreviousModePreset =",
    "g_geometryPreviousCombineMode": r"int g_geometryPreviousCombineMode =",
}

# The split structs' addresses (symbol_addrs.txt): each leading scalar at the struct's old address, the struct after it.
_SPLIT = {"g_pointLightSavedBufferOffset": ("g_savedFlagToggleStorage", 4), "g_schedulerTaskDuration": ("g_schedulerState", 16),
          "g_maximumDisplayListBytes": ("g_sessionFrameRenderState", 4),
          "g_geometryPreviousModePreset": ("g_geometryPreviousModePresetBlock", 8),
          "g_playerViewRenderingEnabled": ("g_enemyMixWordsAndLights", 4)}
_OLD = {"de": (0x800CBC80, 0x800CD74C, 0x800CD884, 0x800CC360, None),
        "eu": (0x800CC860, 0x800CE32C, 0x800CE464, 0x800CCF40, None),
        "eu-x": (0x800CD230, 0x800CECFC, 0x800CEE34, 0x800CD910, None),
        "us": (0x800CBB90, 0x800CD65C, 0x800CD794, 0x800CC270, None),
        "us-rev1": (0x800D0ED0, 0x800D299C, 0x800D2AD4, 0x800D15B0, 0x800D0EBC)}
ADDRESSES = {v: {k: a for (s, (n, off)), a in zip(_SPLIT.items(), olds) if a for k, a in ((s, a), (n, a + off))}
             for v, olds in _OLD.items()}

# Compiler literal pools that replaced a data table: the function and its count of literal conversions.
LITERAL_POOLS = {
    "literals_GraphU64_PackFixedMatrix": ("GraphU64_PackFixedMatrix", 16),
    "literals_Graphu64_ConvertMatrixToFixed": ("Graphu64_ConvertMatrixToFixed", 12),
}

# Names that aliased another name's address at another width: none may come back as an alias, a symbol name or an
# extern (each reader now reads the canonical name, an element of it or a field of it).
DELETED = [
    *(f"g_fullFixedMatrixElement{n}ConversionConstants" for n in range(16)),
    *(f"g_affineFixedMatrixElement{n}ConversionConstants" for n in (0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14)),
    "gPackedBitsLeft", "k_GAudiopitchratiocurveEncodedHalfwords", "g_audiopitchratiocurve",
    "g_vectorTrackSpanTestBiases", "g_vectorTrackLimitPairs", "g_affinePackUnsignedThresholdPairs",
    "g_videoFrameSchedulingMode", "g_smackFormatTableAlt",
    "g_audio_LoadDialogMetadataConstant", "g_audio_LoadDialogMetadataConstantWords",
    "g_mattable", "g_wrappedValueScaleConstants", "g_directionMatrixUnitConstants_de",
    "g_directionMatrixUnitConstants_us_rev1", "g_activeVoiceCount", "k_GAnimationsindextextEncodedBytes",
    "k_GAnimationsindextext", "k_PolycolEncodedBytes", "k_Polycol", "g_AudioDecodeframe",
    "g_audioDecodedSampleBufferAddresses", "g_audioReadpackedsamplesDataZeroWords", "g_snapshotModeColorScale",
    "k_ControlCycleactorsnapshotmodeEncodedWords", "k_CurveDecodethreebitsamples", "g_CurveDecodethreebitsamples",
    "g_eventsDeliverContactEffectHalfwords", "g_contactEffectParticleQuadDisplayList",
    "g_schedHandleRspCompletionSessionHandlers", "g_initialSessionHandlers", "g_geometryDrawResourceModelWritableWords_eu",
    "g_xPlusWritableWords_us_rev1",
    "g_fullMatrixFixedConversionPairs", "g_affineMatrixFixedConversionPairs", "g_graphU_PackFixedMatrixConstantWords",
]


def tracked(*paths: str) -> list[Path]:
    out = subprocess.run(["git", "ls-files", "--", *paths], cwd=ROOT, capture_output=True, text=True, check=True).stdout
    return [ROOT / line for line in out.splitlines() if line]


def word_definitions(names: set[str]) -> list[str]:
    """The `unsigned int NAME[...]` definitions and `.word` blobs labelled NAME, as file:line text."""
    if not names:
        return []
    alt = "|".join(map(re.escape, sorted(names)))
    c_word = re.compile(r"^\s*(?:static\s+)?(?:const\s+)?unsigned\s+int\s+(" + alt + r")\s*\[")
    label = re.compile(r"^\s*(?:glabel|dlabel)?\s*(" + alt + r")\s*:?\s*$")
    found = []
    for path in tracked("Source", "Include", "asm"):
        if path.suffix not in {".c", ".cpp", ".h", ".hpp", ".s", ".inc"} or not path.is_file():
            continue
        lines = path.read_text(errors="replace").splitlines()
        for i, line in enumerate(lines):
            rel = f"{path.relative_to(ROOT)}:{i + 1}"
            if c_word.match(line):
                found.append(f"{rel}: {line.strip()}")
            elif path.suffix in {".s", ".inc"} and label.match(line):
                following = next((n.strip() for n in lines[i + 1:] if n.strip()), "")
                if following.startswith(".word"):
                    found.append(f"{rel}: {line.strip()} {following}")
    return found


class DataWidths(unittest.TestCase):
    def test_symbols_are_named(self):
        for name, where in SYMBOLS.items():
            self.assertRegex(name, r"^[A-Za-z_]\w*$")
            self.assertTrue((ROOT / where).is_file(), f"{name}: {where} is gone")

    def test_no_word_definitions(self):
        self.assertEqual(word_definitions(set(SYMBOLS)), [])

    def test_pinned_definitions(self):
        for name, pattern in PINNED.items():
            text = (ROOT / SYMBOLS[name]).read_text(errors="replace")
            self.assertRegex(text, r"(?m)^" + pattern, f"{name}: its definition in {SYMBOLS[name]} is no longer {pattern}")

    def test_deleted_aliases_stay_deleted(self):
        names = re.compile(r"(?<![\w.>])(" + "|".join(map(re.escape, DELETED)) + r")\b")
        found = []
        for path in tracked("versions"):
            if path.name in ("aliases.txt", "symbol_addrs.txt"):
                for i, line in enumerate(path.read_text(errors="replace").splitlines()):
                    m = re.match(r"\s*(\w+)\s*=", line)
                    if m and m[1] in DELETED:
                        found.append(f"{path.relative_to(ROOT)}:{i + 1}: {line.strip()}")
        for path in tracked("Source", "Include", "sdk"):
            if path.suffix.lower() in {".c", ".cpp", ".h", ".hpp"} and path.is_file():
                for i, line in enumerate(path.read_text(errors="replace").splitlines()):
                    code = line.split("//")[0]
                    if not code.lstrip().startswith(("/*", "*")) and names.search(code):
                        found.append(f"{path.relative_to(ROOT)}:{i + 1}: {line.strip()}")
        self.assertEqual(found, [])

    def test_split_struct_addresses(self):
        for version, names in ADDRESSES.items():
            text = (ROOT / "versions" / version / "symbol_addrs.txt").read_text(errors="replace")
            for name, address in names.items():
                self.assertRegex(text, rf"(?m)^{name} = 0x{address:08X};", f"{version}: {name} is no longer at 0x{address:08X}")

    def test_literal_pools(self):
        text = (ROOT / "Source/Engine/graphics_math.cpp").read_text(errors="replace")
        for pool, (function, uses) in LITERAL_POOLS.items():
            body = re.search(rf"(?ms)^void {function}\(.*?^\}}", text)
            self.assertIsNotNone(body, function)
            self.assertEqual(len(re.findall(r"= \(u32\)\([^;]* \* 65536\.0f\);", body[0])), uses, function)
            for version in ADDRESSES:
                self.assertRegex((ROOT / "versions" / version / "symbol_addrs.txt").read_text(errors="replace"),
                                 rf"(?m)^{pool} = 0x", f"{version}: {pool} has no address")

    def test_refuses_a_word_table(self):
        sample = re.compile(r"^\s*(?:static\s+)?(?:const\s+)?unsigned\s+int\s+(g_x)\s*\[")
        self.assertTrue(sample.match("unsigned int g_x[3] = {"))
        self.assertFalse(sample.match("short g_x[6] = {"))


if __name__ == "__main__":
    sys.exit(0 if unittest.main(exit=False, verbosity=1).result.wasSuccessful() else 1)
