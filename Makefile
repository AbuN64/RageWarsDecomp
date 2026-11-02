# Turok: Rage Wars: matching build. Hand-maintained: edit this file. local.mk names the toolchain (compilers, CCPY,
# MKTOOLS); the build runs only the toolchain, RageWars.ld and the sources.
NAME := RageWars
VERSIONS := de eu eu-x us us-rev1
TOOLCHAIN := gcc_2_8_1_sn64
NM_DEFINE := NON_MATCHING
LABEL := [A-Za-z_.]*auto_
ASFLAGS := -march=vr4300 -mabi=32 -EB --no-pad-sections -mips3
AS_CPPFLAGS := -D_LANGUAGE_ASSEMBLY -Dmips -D_MIPS_SIM_ABI32=1 -D_MIPS_SIM=1 -D_LANGUAGE_C -DF3DEX_GBI_2 -Isdk/libgcc -Isdk/include
# The tools and toolchains: a variable local.mk sets wins.
ifneq ($(filter default undefined,$(origin ABUMAS)),)
ABUMAS := tools/abumas/abumas
endif
ifneq ($(filter default undefined,$(origin AS)),)
AS := mips-linux-gnu-as
endif
ifneq ($(filter default undefined,$(origin CPP)),)
CPP := cpp
endif
ifneq ($(filter default undefined,$(origin LD)),)
LD := mips-linux-gnu-ld
endif
ifneq ($(filter default undefined,$(origin OBJCOPY)),)
OBJCOPY := mips-linux-gnu-objcopy
endif
ifneq ($(filter default undefined,$(origin SPLAT)),)
SPLAT := splat
endif
CC_gcc_2_7_2_sn64 ?= tools/gcc-2.7.2-sn64/cc1
AS_gcc_2_7_2_sn64 ?= $(AS)
TOOLCHAIN_gcc_2_7_2_sn64 ?= tools/gcc-2.7.2-sn64/.stamp
CC_gcc_2_8_1_sn64 ?= tools/gcc-2.8.1-sn64/cc1
AS_gcc_2_8_1_sn64 ?= $(AS)
TOOLCHAIN_gcc_2_8_1_sn64 ?= tools/gcc-2.8.1-sn64/.stamp
CPPFLAGS_gcc_2_7_2_sn64 := -P -undef -nostdinc -D_LANGUAGE_C -D__GNUC__=2 -D__STDARG_GCC -D_LANGUAGE_C -DF3DEX_GBI_2 -Isdk/libgcc -Isdk/include
CFLAGS_gcc_2_7_2_sn64 := -G0 -mips3 -mgp32 -mfp32 -O2 -fno-exceptions
CPPFLAGS_gcc_2_8_1_sn64 := -P -undef -nostdinc -D_LANGUAGE_C -D__GNUC__=2 -D__STDARG_GCC -D_LANGUAGE_C -DF3DEX_GBI_2 -Isdk/libgcc -Isdk/include
CFLAGS_gcc_2_8_1_sn64 := -G0 -mips3 -O2 -mgas -meb -mcpu=VR4300 -mhard-float -mgp32 -mfp64 -mno-fix4300
STAMPS := tools/abumas/.stamp $(TOOLCHAIN_gcc_2_7_2_sn64) $(TOOLCHAIN_gcc_2_8_1_sn64)
# The program of each toolchain in use (PASS runs a helper of MKTOOLS).
PASS = python3 -I $(MKTOOLS)/
define PREPROCESS_gcc_2_7_2_sn64
$(Q)$(PPUNIT) $@ $(call shq,$(PP_FLAGS)) $(HDRKEY) $(STAMPREC) $(CPP) $(CPPFLAGS) -MMD -MP -MF $(@:.i.ok=.d) -MT $@ $(DEFINES) $(INCLUDES) $<
endef
COMPILE_gcc_2_7_2_sn64 = @probe $(OBJSTORE) get $@ $(call shq,$(lastword $(CC_gcc_2_7_2_sn64))) $(call shq,$(CC_FLAGS)) $(call shq,$(TEXTSIZE)) $(call shq,$(PROGRAM_gcc_2_7_2_sn64)) $(filter-out %/.extracted,$(filter asm/%,$^)) '&&' $(PROGRAM_gcc_2_7_2_sn64) '&&' $(OBJSTORE) put $@ $(call shq,$(lastword $(CC_gcc_2_7_2_sn64))) $(call shq,$(CC_FLAGS)) $(call shq,$(TEXTSIZE)) $(call shq,$(PROGRAM_gcc_2_7_2_sn64)) $(filter-out %/.extracted,$(filter asm/%,$^))
PROGRAM_gcc_2_7_2_sn64 = @rotate $(@:.o=.s) $(@:.o=.s.prev) '&&' @compile $(CC_gcc_2_7_2_sn64) -quiet $(CFLAGS) $(@:.o=.i) -o $(@:.o=.s) '&&' @nonempty $(@:.o=.s) $(if $(NOALIGN),'&&' $(PASS)strip_align.py $(@:.o=.s) $(NOALIGN)) $(if $(HILO),'&&' $(PASS)hilo_hazard.py $(@:.o=.s)) '&&' @jumptable $(@:.o=.s) 80000000 '&&' @settle $(@:.o=.s) $(@:.o=.s.prev) '&&' $(ABUMAS) asn64 --as $(AS_gcc_2_7_2_sn64) $(ASFLAGS) $(ASINC) $(@:.o=.s) -o $@ $(if $(UNRELOC),'&&' $(PASS)unreloc_pass.py $@) $(if $(TEXTCUT),'&&' $(PASS)textcut_pass.py $@ $(TEXTCUT))
define PREPROCESS_gcc_2_8_1_sn64
$(Q)$(PPUNIT) $@ $(call shq,$(PP_FLAGS)) $(HDRKEY) $(STAMPREC) $(CPP) $(CPPFLAGS) -MMD -MP -MF $(@:.i.ok=.d) -MT $@ $(DEFINES) $(INCLUDES) $<
endef
COMPILE_gcc_2_8_1_sn64 = @probe $(OBJSTORE) get $@ $(call shq,$(lastword $(CC_gcc_2_8_1_sn64))) $(call shq,$(CC_FLAGS)) $(call shq,$(TEXTSIZE)) $(call shq,$(PROGRAM_gcc_2_8_1_sn64)) $(filter-out %/.extracted,$(filter asm/%,$^)) '&&' $(PROGRAM_gcc_2_8_1_sn64) '&&' $(OBJSTORE) put $@ $(call shq,$(lastword $(CC_gcc_2_8_1_sn64))) $(call shq,$(CC_FLAGS)) $(call shq,$(TEXTSIZE)) $(call shq,$(PROGRAM_gcc_2_8_1_sn64)) $(filter-out %/.extracted,$(filter asm/%,$^))
PROGRAM_gcc_2_8_1_sn64 = @rotate $(@:.o=.s) $(@:.o=.s.prev) '&&' @compile $(CC_gcc_2_8_1_sn64) -quiet $(CFLAGS) $(if $(FSPLIT),-ffunction-sections) $(@:.o=.i) -o $(@:.o=.s) '&&' @nonempty $(@:.o=.s) $(if $(NOALIGN),'&&' $(PASS)strip_align.py $(@:.o=.s) $(NOALIGN)) $(if $(HILO),'&&' $(PASS)hilo_hazard.py $(@:.o=.s)) '&&' @jumptable $(@:.o=.s) 80000000 '&&' @settle $(@:.o=.s) $(@:.o=.s.prev) '&&' $(if $(FSPLIT),@out $(@:.o=.n.s) $(ABUMAS) asn64 $(@:.o=.s) '&&' $(PASS)fsplit_pass.py $(@:.o=.n.s) $(@:.o=.f.s) $(POOLPHASE) '&&' $(AS_gcc_2_8_1_sn64) $(ASFLAGS) $(ASINC) $(@:.o=.f.s) -o $@,$(ABUMAS) asn64 --as $(AS_gcc_2_8_1_sn64) $(ASFLAGS) $(ASINC) $(@:.o=.s) -o $@) '&&' $(OBJCOPY) --set-section-flags .rdata=alloc,load,readonly,data,contents $@ $(if $(UNRELOC),'&&' $(PASS)unreloc_pass.py $@) $(if $(TEXTCUT),'&&' $(PASS)textcut_pass.py $@ $(TEXTCUT))
# The [file] rows of config.toml.
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN2.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN2.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN2.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN2.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN4.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN4.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN4.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN4.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN6.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN6.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN6.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN6.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS3.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS3.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS3.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS3.CPP := 1
FILE.include/PR/ := gcc_2_8_1_sn64
FILE.sdk/LIBGCC2.c := gcc_2_8_1_sn64
CFLAGS.sdk/LIBGCC2.c := -mfp32
OMIT.sdk/LIBGCC2.c := -mfp64
FILE.sdk/LIBSN/ := gcc_2_7_2_sn64
FILE.sdk/MATH/ := gcc_2_8_1_sn64
FILE.sdk/include/ := gcc_2_8_1_sn64
FILE.sdk/libgcc/ := gcc_2_8_1_sn64
FILE.sdk/libsn/ := gcc_2_7_2_sn64
FILE.sdk/libsn/libsn_spindelay_data.CPP := gcc_2_8_1_sn64
FILE.sdk/libsn/libsn_writememorybyte.CPP := gcc_2_8_1_sn64
FILE.sdk/libsn/nav_isballisticarcobstructed_data.CPP := gcc_2_8_1_sn64
FILE.sdk/libultra/ := gcc_2_8_1_sn64
FILE.sdk/libultra/audio/_udivdi3.CPP.c := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/audio/_udivdi3.CPP.c := -msplit-addresses
FILE.sdk/libultra/audio/env.c := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/audio/env.c := -fforce-addr
FILE.sdk/libultra/gu/sqrtf.c := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/gu/sqrtf.c := -ffast-math -fno-delayed-branch
FILE.sdk/libultra/io/pfschecker/pfschecker.c := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/io/pfschecker/pfschecker.c := -fforce-addr
FILE.sdk/libultra/libc/LIBC_SIGNEDLONGLONGTODOUBLE_USREV1.CPP.c := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/libc/LIBC_SIGNEDLONGLONGTODOUBLE_USREV1.CPP.c := -mfp32
FILE.sdk/libultra/libc/_divdi3.CPP := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/libc/_divdi3.CPP := -msplit-addresses
HILO.sdk/libultra/libc/_divdi3.CPP := 1
FILE.sdk/libultra/libc/_moddi3.CPP/_moddi3.CPP.c := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/libc/_moddi3.CPP/_moddi3.CPP.c := -msplit-addresses
HILO.sdk/libultra/libc/_moddi3.CPP/_moddi3.CPP.c := 1
FILE.sdk/libultra/libc/_umoddi3.CPP := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/libc/_umoddi3.CPP := -msplit-addresses
HILO.sdk/libultra/libc/_umoddi3.CPP := 1
FILE.sdk/libultra/libc/gfx_getconvertedcounterratio_data.CPP.c := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/libc/gfx_getconvertedcounterratio_data.CPP.c := -mfp32
FILE.sdk/libultra/libc/longarith.CPP := gcc_2_8_1_sn64
CFLAGS.sdk/libultra/libc/longarith.CPP := -mfp32
FILE.sdk/rnc/ := gcc_2_8_1_sn64
FILE.SOURCE/ENGINE/AUDIO/DECODER/AUDIO_DECODETRANSFORMBLOCK.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/AUDIO/DECODER/AUDIO_DECODETRANSFORMBLOCK.CPP := -fforce-addr
FILE.SOURCE/ENGINE/AUDIO/DECODER/AUDIO_INITBITREVERSEORDER.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/AUDIO/DECODER/AUDIO_INITBITREVERSEORDER.CPP := -fforce-addr
FILE.SOURCE/ENGINE/AUDIO/DECODER/AUDIO_LOADDECODEDSAMPLES.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/AUDIO/DECODER/AUDIO_LOADDECODEDSAMPLES.CPP := -fforce-addr
FILE.SOURCE/ENGINE/AUDIO/DECODER/AUDIO_NEXTDECODEDSAMPLEBLOCK.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/AUDIO/DECODER/AUDIO_NEXTDECODEDSAMPLEBLOCK.CPP := -fforce-addr
FILE.SOURCE/ENGINE/AUDIO/DECODER/DECODE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/AUDIO/DECODER/DECODE.CPP := -fforce-addr
FILE.SOURCE/ENGINE/PARTICLE/GHOT_DISPATCHATTACHMENTEFFECTS_DATA.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/GHOT_DISPATCHATTACHMENTEFFECTS_DATA.CPP := -ffast-math
FILE.SOURCE/ENGINE/PARTICLE/PARTICLE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/PARTICLE.CPP := -ffast-math
FILE.SOURCE/ENGINE/PARTICLE/PARTICLE_BUILDMATRIX.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/PARTICLE_BUILDMATRIX.CPP := -ffast-math
FILE.SOURCE/ENGINE/PARTICLE/PARTICLE_DRAWSPRITE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/PARTICLE_DRAWSPRITE.CPP := -ffast-math
FILE.SOURCE/ENGINE/PARTICLE/PARTICLE_HASKINDZEROENTRY.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/PARTICLE_HASKINDZEROENTRY.CPP := -ffast-math
FILE.SOURCE/ENGINE/PARTICLE/PARTICLE_RECYCLERELEASEDEFFECTS.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/PARTICLE_RECYCLERELEASEDEFFECTS.CPP := -ffast-math
FILE.SOURCE/ENGINE/PARTICLE/PARTICLE_RELEASEOWNERLISTONEEFFECTS.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/PARTICLE_RELEASEOWNERLISTONEEFFECTS.CPP := -ffast-math
FILE.SOURCE/ENGINE/PARTICLE/PARTICLE_UPDATESYSTEM.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/PARTICLE_UPDATESYSTEM.CPP := -ffast-math
FILE.SOURCE/ENGINE/PARTICLE/PARTICLE_UPDATETYPEDMOTION.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/ENGINE/PARTICLE/PARTICLE_UPDATETYPEDMOTION.CPP := -ffast-math
FILE.SOURCE/MULTI/SLOTS/PLAYERSLOTS_ASSERTSLOTINDEX.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/MULTI/SLOTS/PLAYERSLOTS_ASSERTSLOTINDEX.CPP := -O0
OMIT.SOURCE/MULTI/SLOTS/PLAYERSLOTS_ASSERTSLOTINDEX.CPP := -O2 -mgas
UNRELOC.SOURCE/MULTI/SLOTS/PLAYERSLOTS_ASSERTSLOTINDEX.CPP := 1
FILE.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTLIVE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTLIVE.CPP := -O0
OMIT.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTLIVE.CPP := -O2 -mgas
UNRELOC.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTLIVE.CPP := 1
FILE.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTOCCUPIED.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTOCCUPIED.CPP := -O0
OMIT.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTOCCUPIED.CPP := -O2 -mgas
UNRELOC.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTOCCUPIED.CPP := 1
FILE.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTUNRELEASED.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTUNRELEASED.CPP := -O0
OMIT.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTUNRELEASED.CPP := -O2 -mgas
UNRELOC.SOURCE/MULTI/SLOTS/PLAYERSLOTS_COUNTUNRELEASED.CPP := 1
FILE.SOURCE/MULTI/SLOTS/PLAYERSLOTS_FINDSTAGEDWHENIDLE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/MULTI/SLOTS/PLAYERSLOTS_FINDSTAGEDWHENIDLE.CPP := -O0
OMIT.SOURCE/MULTI/SLOTS/PLAYERSLOTS_FINDSTAGEDWHENIDLE.CPP := -O2 -mgas
UNRELOC.SOURCE/MULTI/SLOTS/PLAYERSLOTS_FINDSTAGEDWHENIDLE.CPP := 1
FILE.SOURCE/UI/SMOS/SM_XLATE/SM_XLATE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/SMOS/SM_XLATE/SM_XLATE.CPP := -fno-thread-jumps -fno-rerun-cse-after-loop
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONBUTTONUP.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONBUTTONUP.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONBUTTONUP.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONBUTTONUP.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONCREATE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONCREATE.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONCREATE.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONCREATE.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONDESTROY.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONDESTROY.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONDESTROY.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONDESTROY.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONINITIALUPDATE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONINITIALUPDATE.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONINITIALUPDATE.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONINITIALUPDATE.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONLEFT.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONLEFT.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONLEFT.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONLEFT.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONRENDER.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONRENDER.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONRENDER.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONRENDER.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONRIGHT.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONRIGHT.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONRIGHT.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACESCREEN/PAKINTERFACE_ONRIGHT.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDPLAYERTOMIDDLE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDPLAYERTOMIDDLE.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDPLAYERTOMIDDLE.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDPLAYERTOMIDDLE.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDPLAYERTOSPECIFICMIDDLESLOT.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDPLAYERTOSPECIFICMIDDLESLOT.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDPLAYERTOSPECIFICMIDDLESLOT.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDPLAYERTOSPECIFICMIDDLESLOT.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDQUICKPLAYERTOGLOBAL.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDQUICKPLAYERTOGLOBAL.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDQUICKPLAYERTOGLOBAL.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ADDQUICKPLAYERTOGLOBAL.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CALCSAVEGAMESIZE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CALCSAVEGAMESIZE.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CALCSAVEGAMESIZE.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CALCSAVEGAMESIZE.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CHECKFORROOMONPAK.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CHECKFORROOMONPAK.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CHECKFORROOMONPAK.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CHECKFORROOMONPAK.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CHECKPAK.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CHECKPAK.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CHECKPAK.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_CHECKPAK.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_COPYMIDDLEPLAYERSTOGLOBAL.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_COPYMIDDLEPLAYERSTOGLOBAL.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_COPYMIDDLEPLAYERSTOGLOBAL.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_COPYMIDDLEPLAYERSTOGLOBAL.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_COPYSPECIFICMIDDLEPLAYERTOGLOBAL.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_COPYSPECIFICMIDDLEPLAYERTOGLOBAL.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_COPYSPECIFICMIDDLEPLAYERTOGLOBAL.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_COPYSPECIFICMIDDLEPLAYERTOGLOBAL.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_DECPLAYERNAMECHARACTER.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_DECPLAYERNAMECHARACTER.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_DECPLAYERNAMECHARACTER.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_DECPLAYERNAMECHARACTER.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_EXITSCREEN.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_EXITSCREEN.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_EXITSCREEN.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_EXITSCREEN.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_FINDEMPTYMIDDLESLOT.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_FINDEMPTYMIDDLESLOT.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_FINDEMPTYMIDDLESLOT.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_FINDEMPTYMIDDLESLOT.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_FINDEMPTYPLAYERDATASLOT.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_FINDEMPTYPLAYERDATASLOT.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_FINDEMPTYPLAYERDATASLOT.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_FINDEMPTYPLAYERDATASLOT.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_GETGLOBALPLAYERBYMARKER.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_GETGLOBALPLAYERBYMARKER.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_GETGLOBALPLAYERBYMARKER.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_GETGLOBALPLAYERBYMARKER.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_GETPLAYERINMIDDLESLOT.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_GETPLAYERINMIDDLESLOT.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_GETPLAYERINMIDDLESLOT.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_GETPLAYERINMIDDLESLOT.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INCPLAYERNAMECHARACTER.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INCPLAYERNAMECHARACTER.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INCPLAYERNAMECHARACTER.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INCPLAYERNAMECHARACTER.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITNAMEMANAGEMENT.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITNAMEMANAGEMENT.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITNAMEMANAGEMENT.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITNAMEMANAGEMENT.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITPAKMANAGEMENT.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITPAKMANAGEMENT.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITPAKMANAGEMENT.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITPAKMANAGEMENT.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITPLAYERMODE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITPLAYERMODE.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITPLAYERMODE.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITPLAYERMODE.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITUPDATEINFO.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITUPDATEINFO.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITUPDATEINFO.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_INITUPDATEINFO.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ISMIDDLELISTEMPTY.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ISMIDDLELISTEMPTY.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ISMIDDLELISTEMPTY.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ISMIDDLELISTEMPTY.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ISPLAYERDATALISTEMPTY.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ISPLAYERDATALISTEMPTY.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ISPLAYERDATALISTEMPTY.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_ISPLAYERDATALISTEMPTY.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_LOADGAME.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_LOADGAME.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_LOADGAME.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_LOADGAME.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PREPAREDATAAFTERLOAD.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PREPAREDATAAFTERLOAD.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PREPAREDATAAFTERLOAD.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PREPAREDATAAFTERLOAD.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PREPARESAVEBLOCKFORSAVE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PREPARESAVEBLOCKFORSAVE.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PREPARESAVEBLOCKFORSAVE.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PREPARESAVEBLOCKFORSAVE.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PRESSEDSTART.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PRESSEDSTART.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PRESSEDSTART.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_PRESSEDSTART.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REFRESHMIDDLENAMESFORCOPY.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REFRESHMIDDLENAMESFORCOPY.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REFRESHMIDDLENAMESFORCOPY.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REFRESHMIDDLENAMESFORCOPY.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REFRESHMIDDLENAMESFORPLAYERNAME.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REFRESHMIDDLENAMESFORPLAYERNAME.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REFRESHMIDDLENAMESFORPLAYERNAME.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REFRESHMIDDLENAMESFORPLAYERNAME.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REMOVEPLAYERFROMMIDDLE.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REMOVEPLAYERFROMMIDDLE.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REMOVEPLAYERFROMMIDDLE.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REMOVEPLAYERFROMMIDDLE.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REMOVEQUICKPLAYERFROMGLOBAL.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REMOVEQUICKPLAYERFROMGLOBAL.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REMOVEQUICKPLAYERFROMGLOBAL.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REMOVEQUICKPLAYERFROMGLOBAL.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REORDERGLOBALPLAYERSTOSELECTED.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REORDERGLOBALPLAYERSTOSELECTED.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REORDERGLOBALPLAYERSTOSELECTED.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_REORDERGLOBALPLAYERSTOSELECTED.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_RESETCONTROLBACKTOCOPYPLAYER.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_RESETCONTROLBACKTOCOPYPLAYER.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_RESETCONTROLBACKTOCOPYPLAYER.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_RESETCONTROLBACKTOCOPYPLAYER.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_SAVEGAME.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_SAVEGAME.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_SAVEGAME.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_SAVEGAME.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_SCROLLMANAGEMENTLIST.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_SCROLLMANAGEMENTLIST.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_SCROLLMANAGEMENTLIST.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_SCROLLMANAGEMENTLIST.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_UPDATEGROUPS.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_UPDATEGROUPS.CPP := -O0 -fno-builtin
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_UPDATEGROUPS.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_UPDATEGROUPS.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_UPDATEPAK.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_UPDATEPAK.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_UPDATEPAK.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_UPDATEPAK.CPP := 1
FILE.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_VALIDATEPAKAGAINSTGLOBAL.CPP := gcc_2_8_1_sn64
CFLAGS.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_VALIDATEPAKAGAINSTGLOBAL.CPP := -O0
OMIT.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_VALIDATEPAKAGAINSTGLOBAL.CPP := -O2 -mgas
UNRELOC.SOURCE/UI/TSMOS/SCREENS/PAKINTERFACE_VALIDATEPAKAGAINSTGLOBAL.CPP := 1
tools/abumas/.stamp:
	$(Q)mkdir -p tools/abumas && curl -fsSL https://github.com/AbuN64/mas-n64/releases/download/v0.5.0/abumas-v0.5.0-linux-x86_64.tar.gz -o tools/abumas.tar.gz && echo '9173e4f2f3bad16d94eaf149cbe09e5363060dcdf72fa64f6f66fc7b7bdb9e03  tools/abumas.tar.gz' | sha256sum -c - >/dev/null && tar -xzf tools/abumas.tar.gz -C tools/abumas --strip-components=1 abumas-v0.5.0-linux-x86_64/abumas && rm -f tools/abumas.tar.gz && cd tools/abumas && printf '%s\n' '0fe945e19ccfb49b2b6cebd42d93de6de52c9bd811a8f4b0275c074050f6d418  abumas' | sha256sum -c - >/dev/null && touch .stamp

tools/gcc-2.7.2-sn64/.stamp:
	$(Q)mkdir -p tools/gcc-2.7.2-sn64 && curl -fsSL https://github.com/decompals/SN64-gcc/releases/download/gcc-2.7.2-970404/SN64-gcc-2.7.2-970404-linux.tar.gz -o tools/gcc-2.7.2-sn64.tar.gz && echo '60abe17c2562f5ae28444fe4f783fa8217d84b73e59e29cf39c41f7551d968f4  tools/gcc-2.7.2-sn64.tar.gz' | sha256sum -c - >/dev/null && tar -xzf tools/gcc-2.7.2-sn64.tar.gz -C tools/gcc-2.7.2-sn64 cc1 && rm -f tools/gcc-2.7.2-sn64.tar.gz && cd tools/gcc-2.7.2-sn64 && printf '%s\n' '566d91772fc1435d23dbca5e8040d3e441b31375b2aec4f430e5cddc5d70d8d4  cc1' | sha256sum -c - >/dev/null && touch .stamp

tools/gcc-2.8.1-sn64/.stamp:
	$(Q)mkdir -p tools/gcc-2.8.1-sn64 && curl -fsSL https://github.com/pmret/gcc-papermario/releases/download/master/linux.tar.gz -o tools/gcc-2.8.1-sn64.tar.gz && echo '1156cf0d6a88a64c20e2a10fc9445d99cb9a38518f432b1669528dfa82ebb45f  tools/gcc-2.8.1-sn64.tar.gz' | sha256sum -c - >/dev/null && tar -xzf tools/gcc-2.8.1-sn64.tar.gz -C tools/gcc-2.8.1-sn64 cc1 && rm -f tools/gcc-2.8.1-sn64.tar.gz && cd tools/gcc-2.8.1-sn64 && printf '%s\n' 'd1ddfe21dfa61840a83f833c8bd45ed7e2f606c3d9c351d2ec732fb6e4f97c89  cc1' | sha256sum -c - >/dev/null && touch .stamp


# The build rules. The project facts sit above them and each version's facts live in versions/<version>/text_sizes.mk.
#
# make check             builds every version ROM from the committed sources and verifies its SHA-1.
# make check CHECK=tree  verifies only that the committed generated files are present (no ROMs needed).
# make extract           splits every baserom into asm/<version>/ with splat; a data file's section is its stand-in's.
#                        A build extracts a version that has no asm/<version>/ yet on its own.
# make nm                (or NON_MATCHING=1) links one ROM per version with every draft compiled in (see below).
# make V=1               echoes every command; JOBS (local.mk) sets the parallel jobs.
# local.mk (machine-local) names the tools: compilers, CCPY, MKTOOLS (the folder
# of the build's helper programs), SPLAT, CPP...
SHELL := /bin/sh
.SUFFIXES:
.DELETE_ON_ERROR:
.SECONDARY:
.SECONDEXPANSION:
.DEFAULT_GOAL := all
Q = $(if $(filter 1,$(V)),,@)
CHECK ?= rom
-include local.mk
ifneq ($(JOBS),)
ifeq ($(filter -j% --jobserver%,$(MAKEFLAGS)),)
MAKEFLAGS += -j$(JOBS)
endif
endif
ifeq ($(CHECK),rom)
MKTOOLS ?= $(error MKTOOLS is not set: name the toolchain folder in local.mk)
endif
HOSTCC ?= cc

# ---------------------------------------------------------------- paths and facts
# build/<version>/<source path>.o is a matching object; build/nmraw/<version>/ holds the objects of a NON_MATCHING
# compile and build/nm/<version>/ the ones the NM link uses. The version is the first path word that is neither.
ver = $(firstword $(filter-out nm nmraw,$(subst /, ,$1)))
src = $(patsubst $(call ver,$1)/%,%,$(patsubst nmraw/%,%,$(patsubst nm/%,%,$1)))
# The [file] row of a source: its own path, else its longest directory with a row (FILE.<key> names its toolchain).
parents = $(if $(findstring /,$1),$(dir $1) $(call parents,$(patsubst %/,%,$(dir $1))))
row = $(firstword $(foreach k,$1 $(call parents,$1),$(if $(FILE.$k),$k)))
# Looked up once per source and once per target stem: make reads each object's row many times (its flags, its
# passes) for every version. Only the row is kept so: a value that holds a target-specific variable (FSPLIT) is not.
rowof = $(if $(filter undefined,$(origin ROWOF.$1)),$(eval ROWOF.$1 := $(call row,$1)))$(ROWOF.$1)
ROW = $(if $(filter undefined,$(origin ROW@$*)),$(eval ROW@$* := $(call rowof,$(call src,$*))))$(ROW@$*)
# A row's toolchain and flags: the toolchain's flags and the project's, less the row's OMIT, plus the row's own.
TC = $(or $(FILE.$(ROW)),$(TOOLCHAIN))
CPPFLAGS = $(strip $(CPPFLAGS_$(TC)) $(CPPFLAGS.$(ROW)))
CFLAGS = $(strip $(filter-out $(OMIT.$(ROW)),$(CFLAGS_$(TC))) $(CFLAGS.$(ROW)))
HILO = $(HILO.$(ROW))
UNRELOC = $(UNRELOC.$(ROW))
DEFINES = -D$(VMACRO_$(call ver,$*)) $(if $(filter nmraw/%,$*),-D$(NM_DEFINE))
INCLUDES = -Iinclude -I$(dir $<)
ASINC = -Iasm/$(call ver,$*)
# Every version macro for the assembler, 1 for the version built and 0 for the others: library assembly keeps the
# lines its versions disagree on in `.if VERSION_A || VERSION_B` blocks
ASDEFS = $(foreach w,$(VERSIONS),--defsym $(VMACRO_$(w))=$(if $(filter $(w),$(call ver,$*)),1,0))
# Each version's facts (VMACRO_, SHA1_, ROM0_, ROM_SECTIONS_) and the size each object's .text has in the ROM: a
# compiler may pad the section past its last function, and a zero tail past that size is cut before the object links.
-include $(VERSIONS:%=versions/%/text_sizes.mk)
# Compare each object's last successful size with its own target-specific value during second expansion.
# A shared text_sizes.mk timestamp would rebuild every object; removed sizes must also invalidate the old trim.
text_size_changed = $(if $(filter x$(TEXTSIZE),x$(file <$@.textsize)),,text-size-changed)
.PHONY: text-size-changed
text-size-changed:
TRIM_TEXT = $(CCPY) --trim

.PHONY: all check extract
all: check
ifeq ($(CHECK),tree)
check:
	$(Q)for f in Makefile $(NAME).ld include/include_asm.h $(VERSIONS:%=versions/%/splat.yaml); do test -s $$f || { echo "$$f is missing" >&2; exit 1; }; done
else ifeq ($(CHECK),rom)
check: $(VERSIONS:%=build/%/$(NAME).z64)
else
$(error CHECK must be rom or tree)
endif

# ---------------------------------------------------------------- extraction
# A data file holds the ROM bytes from its symbol to the next one, in the section its stand-in names: its own
# section line goes, no .align asks more than its first address has (alignment counts from the section start),
# and a .double, which the assembler would align, is written as its two words.
DATA_SED := -e '/^\.section /d' -e 's@^(\s*/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8})([0-9A-F]{8}) \*/\s*)\.double .*@\1.word 0x\2, 0x\3@'
# An instruction splat marks handwritten (a 64-bit load in 32-bit code, a coprocessor move) is written as the word it
# is: the assembler would expand or re-encode it. So is a 64-bit load, store or divide with no symbol operand: under
# the 32-bit ABI the assembler expands it into several instructions; one with a %lo(symbol) operand keeps the
# relocation on the word, whose low half the link fills. A `b` is spelled as the branch its word is: an
# assembler may encode `b` as either beq or bgez. A handwritten line that carries a relocation (%hi, %lo, %gp_rel)
# keeps its symbol: as a .word the link has no operand to fill, and the %lo of a lui/addiu pair is left unpaired.
CODE_SED := -e 's@^(\s*/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s*)[^%]*/\* handwritten instruction \*/$$@\1.word 0x\2@' \
	-e 's@^(\s*/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{4})[0-9A-F]{4} \*/\s*)(ld|sd|ldl|ldr|sdl|sdr|lld|scd)\s[^%]*%lo\(([A-Za-z0-9_.]+)\).*@\1.reloc ., R_MIPS_LO16, \4\n    .word 0x\20000@' \
	-e 's@^(\s*/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s*)(ld|sd|ldl|ldr|sdl|sdr|lld|scd|ddiv|ddivu)\s[^%]*$$@\1.word 0x\2@' \
	-e 's@^(\s*/\* [0-9A-F]+ [0-9A-F]{8} 1000[0-9A-F]{4} \*/\s*)b(\s+)@\1beq\2$$zero, $$zero, @' \
	-e 's@^(\s*/\* [0-9A-F]+ [0-9A-F]{8} 0401[0-9A-F]{4} \*/\s*)b(\s+)@\1bgez\2$$zero, @'
# One extraction per input: a version whose baserom, splat.yaml, symbol_addrs.txt, splat and extract recipe are those of its last
# extraction (build/.extract-key-<v>) is not split again, so a build or probe extracts only a version whose inputs it changed.
# `make extract-force-<v>` (or removing asm/<v>/.extracted) splits regardless. One recipe, no sub-make (parallel sub-makes raced
# on remaking the included files). Bump rev1 when the recipe changes.
export EXTRACT_RECIPE := rev1 $(DATA_SED) $(CODE_SED)
EXTRACT_KEY = { cat roms/baserom.$*.z64 versions/$*/splat.yaml versions/$*/symbol_addrs.txt $(wildcard versions/$*/earlier_build_symbols.txt); $(SPLAT) --version 2>&1; printf %s "$$EXTRACT_RECIPE"; } | sha1sum | cut -d" " -f1
# asm/<v>/.extracted has only the ROM as prerequisite: a rebase that changed symbol_addrs.txt or splat.yaml left stale asm. A version whose
# two files differ from build/.extract-src-<v> (or have no record) gets the phony extract-stale: the full key is checked once, then recorded.
SRC_KEY = cat versions/$*/splat.yaml versions/$*/symbol_addrs.txt $(wildcard versions/$*/earlier_build_symbols.txt) 2>/dev/null | sha1sum | cut -d" " -f1
.PHONY: extract-stale
$(foreach v,$(VERSIONS),$(if $(wildcard build/.extract-key-$(v)),$(if $(filter $(shell cat versions/$(v)/splat.yaml versions/$(v)/symbol_addrs.txt $(wildcard versions/$(v)/earlier_build_symbols.txt) 2>/dev/null | sha1sum | cut -d" " -f1),$(shell cat build/.extract-src-$(v) 2>/dev/null)),,$(eval asm/$(v)/.extracted: extract-stale))))
# asm/<v>/.extracted holds the hash of the facts it was made from; an object of other facts is refused (an empty mark is not checked).
$(foreach v,$(VERSIONS),$(eval FACTS_NOW_$(v) := $(shell cat versions/$(v)/symbol_addrs.txt versions/$(v)/splat.yaml 2>/dev/null | sha1sum | cut -d' ' -f1)))
extract: $(VERSIONS:%=extract-%)
extract-force-%:
	$(Q)rm -f build/.extract-key-$* && $(MAKE) --no-print-directory extract-$*
# Records the inputs asm/<v>/ holds the extraction of (the tool that extracts runs it too).
extract-stamp-%:
	$(Q)mkdir -p build && { $(EXTRACT_KEY); } > build/.extract-key-$* && { $(SRC_KEY); } > build/.extract-src-$*
extract-%:
	$(Q)mkdir -p build; flock build/.extract-lock-$* $(MAKE) --no-print-directory extract-do-$*
# keep_dates.py gives a file splat wrote again with the same bytes its old date back; fill_data.py rewrites each data
# file as its ROM slice (splat drops string padding, a partial last word and whole tiny pieces).
extract-do-%:
	$(Q)mkdir -p build; if test -f asm/$*/.extracted && test "$$($(EXTRACT_KEY))" = "$$(cat build/.extract-key-$* 2>/dev/null)"; then rm -f build/.extract-run-$*; echo "extract-$*: inputs unchanged, not split again (make extract-force-$* splits)"; { $(SRC_KEY); } > build/.extract-src-$*; else touch build/.extract-run-$*; fi
	$(Q)test -e build/.extract-run-$* || exit 0; python3 -I $(MKTOOLS)/keep_dates.py save $*
	$(Q)test -e build/.extract-run-$* || exit 0; $(SPLAT) split versions/$*/splat.yaml
	$(Q)test -e build/.extract-run-$* || exit 0; find asm/$* \( -name '*.data.s' -o -name '*.rodata.s' \) | while read f; do \
		case $$(grep -m1 -oE '^ */\* [0-9A-F]+ [0-9A-F]{8}' "$$f" | tail -c 2) in \
		0*) c='';; 8*) c='s/^\.align [4-9]/.align 3/';; [4C]*) c='s/^\.align [3-9]/.align 2/';; \
		[26AE]*) c='s/^\.align [2-9]/.align 1/';; *) c='s/^\.align [1-9]/.align 0/';; esac; \
		sed -E $(DATA_SED) -e "$$c" "$$f" > "$${f%.*.s}.s" && rm "$$f"; done
	$(Q)test -e build/.extract-run-$* || exit 0; python3 -I $(MKTOOLS)/fill_data.py $*
	$(Q)test -e build/.extract-run-$* || exit 0; find asm/$*/nonmatchings -name '*.s' -exec sed -i -E $(CODE_SED) {} +
	$(Q)test -e build/.extract-run-$* || exit 0; printf '%s\n' $(FACTS_NOW_$*) > asm/$*/.extracted
	$(Q)test -e build/.extract-run-$* || exit 0; python3 -I $(MKTOOLS)/keep_dates.py restore $*
	$(Q)test -e build/.extract-run-$* || exit 0; { $(EXTRACT_KEY); } > build/.extract-key-$* && { $(SRC_KEY); } > build/.extract-src-$* && rm -f build/.extract-run-$*
# An object assembles extracted files its source only names through a macro: every object follows the extraction.
asm/%/.extracted: | roms/baserom.%.z64
	+$(Q)$(MAKE) --no-print-directory extract-$*

# ---------------------------------------------------------------- what make reads before any date
# Both run before make reads a directory of build/: make keeps the listing it first read, so a stamp the sweep removes
# later would still look present. asm_deps.py: every object depends on the extracted files its INCLUDE_ASM,
# INCLUDE_RODATA and INCLUDE_DATA lines name (build/asm.deps). stamp_sweep.py: a stamp or object whose inputs' bytes
# changed while its date did not (a tree copied, rebased or fast-forwarded) is dated long ago or removed. Only the
# top-level make sweeps: a recursive one (extract-<v> from a recipe) would drop an object its parent is about to link.
ifeq ($(CHECK),rom)
$(shell mkdir -p build)
$(shell python3 -I $(MKTOOLS)/asm_deps.py build/asm.deps $(VERSIONS))
-include build/asm.deps
$(if $(filter 0,$(MAKELEVEL)),$(shell python3 -I $(MKTOOLS)/stamp_sweep.py sweep $(VERSIONS) >&2))
endif
# The link script names every object, so no rule here lists a file: build/<version>/objs.mk is its list, made again
# (and make restarted) only when the script changes.
build/%/objs.mk: $(NAME).ld
	$(Q)mkdir -p $(@D)
	$(Q){ printf 'OBJS_$* :='; $(CPP) -P -undef -D$(VMACRO_$*) $< | grep -oE '[[:alnum:]_./+-]+[.]o' | sort -u | sed 's@^@ build/$*/@' | tr -d '\n'; echo; } > $@
ifeq ($(CHECK),rom)
-include $(VERSIONS:%=build/%/objs.mk)
endif
# Reading the header list of every object costs seconds of one core in each make; a make that names objects needs only
# their own lists, whatever else the tree holds.
GOAL_OBJS := $(filter build/%.o,$(MAKECMDGOALS))
-include $(if $(GOAL_OBJS),$(GOAL_OBJS:.o=.d),$(foreach v,$(VERSIONS),$(OBJS_$(v):.o=.d)))

# ---------------------------------------------------------------- objects
# An object follows the text its source preprocesses to, not the time its headers were written: the .i is replaced only
# when its bytes change, so a header edit that leaves a source's text alone preprocesses that source again and compiles
# nothing. The stamp (.i.ok) carries the header times; the object compiles when its .i is newer than it or another input
# (the extraction, the text size) changed, else it is only touched. A row's flags that change remake the objects it
# reaches: each object keeps the flags it was made with beside it (`.flags`, `.i.ok.flags`) and, when its own flags
# differ, make sees one more prerequisite that is out of date. hdrkey (the compile key of a unit: the .i without the
# declarations it never names) and stamprec (the input record each made output appends to build/.inputs.log) are
# small C tools; without a C compiler the .i is compared byte for byte and the python record runs instead.
HDRKEY := build/hdrkey
STAMPREC := build/stamprec
build/hdrkey build/stamprec: build/%: $(MKTOOLS)/%.c
	$(Q)mkdir -p build
	$(Q)$(HOSTCC) -O2 -o $@ $< 2>/dev/null || rm -f $@
RECORD = { [ -x $(STAMPREC) ] && $(STAMPREC) record $(1); } || python3 -I $(MKTOOLS)/stamp_sweep.py record $(1)
shq = '$(subst ','\'',$(1))'
CC_FLAGS = $(TC) $(CC_$(TC)) $(CFLAGS) $(ASFLAGS) $(DEFINES) $(FSPLIT)
PP_FLAGS = $(TC) $(CPPFLAGS) $(DEFINES)
same_flags = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))
flags_changed = $(if $(wildcard $@.flags),$(if $(call same_flags,$(CC_FLAGS),$(file <$@.flags)),,flags-changed))
pp_flags_changed = $(if $(wildcard $@.flags),$(if $(call same_flags,$(PP_FLAGS),$(file <$@.flags)),,flags-changed))
.PHONY: flags-changed
flags-changed:
build/%.i.ok: $$(call src,$$*) $$(pp_flags_changed) | $(STAMPS) $(HDRKEY) $(STAMPREC)
	$(PREPROCESS_$(TC))
# The extracted files an object assembles are an input by their bytes (`.asm`, their sum before the object is made; a
# make that extracts as it builds reads dates it cached): a different sum removes the object. The object rule's one
# command (stamprec `object`, else cc_cache.py's): the extracted facts it was made from, whether it stands, the compile
# (COMPILE_<toolchain>) when it does not, the flags/size/sum files and the input record.
OBJECT_ARGS = $@ $(call ver,$*) $(FACTS_NOW_$(call ver,$*)) $(call shq,$(filter-out %.i.ok,$?)$(flags_changed)) $(call shq,$(TEXTSIZE)) \
	$(call shq,$(CC_FLAGS)) $(STAMPREC) $(filter-out %/.extracted,$(filter asm/%,$^)) -- $(COMPILE_$(TC))
build/%.o: build/%.i.ok asm/$$(call ver,$$*)/.extracted $$(text_size_changed) $$(flags_changed) | $(STAMPS) $(STAMPREC)
	$(Q)if [ -x $(STAMPREC) ]; then exec $(STAMPREC) object $(OBJECT_ARGS); fi; exec $(CCPY) --object $(OBJECT_ARGS)
# A hand-written .s source is preprocessed first (its #include and #if VERSION_ lines); its .d names the headers.
build/%.s.o: $$(call src,$$*).s $$(text_size_changed) | $(STAMPS)
	$(Q)mkdir -p $(@D)
	$(Q)$(CPP) -P -undef -x assembler-with-cpp $(AS_CPPFLAGS) -D$(VMACRO_$(call ver,$*)) -Iinclude -I$(dir $<) \
	-MMD -MP -MT $@ -MF $(@:.o=.d) $< -o $(@:.o=.pp.s)
	$(Q)$(AS) $(ASFLAGS) $(ASDEFS) $(ASINC) -Iinclude $(@:.o=.pp.s) -o $@
	$(Q)$(if $(TEXTSIZE),$(TRIM_TEXT) $@ $(TEXTSIZE))
	$(Q)printf '%s\n' '$(TEXTSIZE)' > $@.textsize
build/%.bin.o: asm/%.bin
	$(Q)mkdir -p $(@D)
	$(Q)$(OBJCOPY) -I binary -O elf32-tradbigmips -B mips $< $@
# splat writes a binary piece while it extracts the version.
asm/%.bin: | asm/$$(call ver,$$*)/.extracted
	$(Q)test -f $@ || { echo "$@ is missing: run make extract-$(call ver,$*)" >&2; exit 1; }

# ---------------------------------------------------------------- the ROM
# The whole ROM links once per version, from build/<version>/, so object paths in the script stay short.
build/%/link.ld: $(NAME).ld
	$(Q)mkdir -p $(@D)
	$(Q)$(CPP) -P -undef -D$(VMACRO_$*) $< > $@
# Every fact of symbol_addrs.txt and aliases.txt and every name splat left undefined, PROVIDEd: what no object defines
# (data outside the ROM). So is every name splat made up (LABEL) that the extracted assembly or a preprocessed source
# spells, at the address the name carries: a .L label the assembler keeps out of the object, or a label inside bytes
# a C file compiles. Every object of the version is a prerequisite (the .i/.s the grep reads are complete once it is
# built) but never an input of the sed.
build/%/undefined_syms.ld: versions/%/symbol_addrs.txt build/%/undefined_syms_auto.txt build/%/undefined_funcs_auto.txt asm/%/.extracted $$(wildcard versions/$$*/aliases.txt versions/$$*/earlier_build_symbols.txt)
	$(Q)sed -nE 's/^([A-Za-z_.][A-Za-z0-9_.$$]*)[[:space:]]*=[[:space:]]*(0x[0-9A-Fa-f]+);.*/PROVIDE(\1 = \2);/p' $(filter-out %.o,$^) > $@
	$(Q)grep -rhoE --include='*.s' --include='*.i' '$(LABEL)[0-9A-F]{8}\b' asm/$* build/$* | sort -u | sed -E 's/^($(LABEL)(.*))$$/PROVIDE(\1 = 0x\2);/' >> $@
# The objects are prerequisites of each version's list by a plain rule, not by the pattern rule's second expansion:
# GNU make 4.4.1 segfaults expanding $(OBJS_$*) there once build/<v>/undefined_syms_auto.txt exists.
$(foreach v,$(VERSIONS),$(eval build/$(v)/undefined_syms.ld: $(OBJS_$(v))))
# splat writes these while it extracts the version.
build/%/undefined_syms_auto.txt build/%/undefined_funcs_auto.txt: | asm/%/.extracted
	$(Q)test -f $@ || { echo "$@ is missing: run make extract-$*" >&2; exit 1; }
build/%/$(NAME).elf: $$(OBJS_$$*) build/%/link.ld build/%/undefined_syms.ld
	$(Q)cd build/$* && $(LD) -T link.ld -o $(NAME).elf
build/%/$(NAME).bin: build/%/$(NAME).elf
	$(Q)$(OBJCOPY) $(ROM_SECTIONS_$*) -O binary --gap-fill 0 $< $@
build/%/$(NAME).z64: build/%/$(NAME).bin roms/baserom.%.z64
	$(Q){ head -c $(ROM0_$*) roms/baserom.$*.z64; cat $<; } > $@
	$(Q)truncate -s $$(wc -c < roms/baserom.$*.z64) $@
	$(Q)test "$$(sha1sum < $@ | cut -d' ' -f1)" = $(SHA1_$*) || { echo "$@: SHA-1 is not $(SHA1_$*)" >&2; exit 1; }

# ---------------------------------------------------------------- NON_MATCHING
# make NON_MATCHING=1 (or make nm): every draft compiles in (-D$(NM_DEFINE)) and one ROM per version links under
# build/nm/<version>/. The drafts compile into a second tree build/nmraw/<version>/ with the matching build's rules
# and flags. A unit whose NON_MATCHING object keeps the unit's size (nm_pick.py: the same sections, a text no longer
# than the ROM's, zero-filled to it) takes the matching object's place in the link; any other unit keeps its matching
# object. The ROM so keeps its size and every unit's address, and matches no SHA-1, so nothing here checks one.
# build/nm/<version>/report.txt names the units whose draft is in (and how many symbols move in them) and the ones
# left out (and the section that grew).
ifneq ($(NM_DEFINE),)
ifeq ($(NON_MATCHING),1)
.DEFAULT_GOAL := nm
endif
.PHONY: nm
nm: $(VERSIONS:%=build/nm/%/$(NAME).z64)
$(foreach v,$(VERSIONS),$(eval OBJS_nm_$(v) := $(patsubst build/$(v)/%,build/nm/$(v)/%,$(OBJS_$(v)))))
-include $(foreach v,$(VERSIONS),$(patsubst build/$(v)/%,build/nmraw/$(v)/%,$(if $(GOAL_OBJS),$(filter build/$(v)/%,$(GOAL_OBJS:.o=.d)),$(OBJS_$(v):.o=.d))))
# A raw object follows the extracted files its matching twin names, and takes the same text sizes.
ifeq ($(CHECK),rom)
$(shell sed -E 's@^build/@build/nmraw/@' build/asm.deps > build/asm-nmraw.deps.$$$$ && mv build/asm-nmraw.deps.$$$$ build/asm-nmraw.deps)
-include build/asm-nmraw.deps
$(shell cat $(VERSIONS:%=versions/%/text_sizes.mk) | sed -nE 's@^build/@build/nmraw/@p' > build/text_sizes_nmraw.mk.$$$$ && mv build/text_sizes_nmraw.mk.$$$$ build/text_sizes_nmraw.mk)
-include build/text_sizes_nmraw.mk
endif
build/nm/%.o: build/nmraw/%.o build/%.o
	$(Q)mkdir -p $(@D)
	$(Q)python3 -I $(MKTOOLS)/nm_pick.py $^ $@ $(OBJCOPY) $(LD)
# An assembly or binary piece is the matching build's.
build/nm/%.s.o: build/%.s.o
	$(Q)mkdir -p $(@D)
	$(Q)cp -p $< $@
build/nm/%.bin.o: build/%.bin.o
	$(Q)mkdir -p $(@D)
	$(Q)cp -p $< $@
# Static pattern rules: build/%/link.ld would also match build/nm/<version>/link.ld and write an empty script.
$(VERSIONS:%=build/nm/%/link.ld): build/nm/%/link.ld: build/%/link.ld
	$(Q)mkdir -p $(@D)
	$(Q)cp $< $@
$(VERSIONS:%=build/nm/%/undefined_syms.ld): build/nm/%/undefined_syms.ld: build/%/undefined_syms.ld
	$(Q)mkdir -p $(@D)
	$(Q)cp $< $@
# A draft may define a name that this version's ROM keeps as data, or the other way round: the first definition in link
# order wins and link.err lists every such name; any other link error stops the build.
$(VERSIONS:%=build/nm/%/$(NAME).elf): build/nm/%/$(NAME).elf: $$(OBJS_nm_$$*) build/nm/%/link.ld build/nm/%/undefined_syms.ld
	$(Q)cd build/nm/$* && { $(LD) -T link.ld -o $(NAME).elf 2> link.err \
	|| $(LD) -T link.ld --allow-multiple-definition -o $(NAME).elf 2>> link.err; } \
	|| { cat build/nm/$*/link.err >&2; exit 1; }
$(VERSIONS:%=build/nm/%/$(NAME).bin): build/nm/%/$(NAME).bin: build/nm/%/$(NAME).elf
	$(Q)$(OBJCOPY) $(ROM_SECTIONS_$*) -O binary --gap-fill 0 $< $@
$(VERSIONS:%=build/nm/%/$(NAME).z64): build/nm/%/$(NAME).z64: build/nm/%/$(NAME).bin roms/baserom.%.z64
	$(Q){ head -c $(ROM0_$*) roms/baserom.$*.z64; cat $<; } > $@
	$(Q)truncate -s $$(wc -c < roms/baserom.$*.z64) $@
	$(Q)cat $(addsuffix .pick,$(OBJS_nm_$*)) 2>/dev/null | grep -v '^same ' | sort > build/nm/$*/report.txt; \
	echo "NM ROM $*: $$(grep -c '^draft' build/nm/$*/report.txt) unit(s) with drafts in," \
	"$$(grep -c '^left-out' build/nm/$*/report.txt) left out (build/nm/$*/report.txt)"
endif
