
# ----------- release -----------
ifneq ($(findstring rel,$(MAKECMDGOALS)),)
ifeq ($(VER),)
$(error need VER)
endif
endif

include ../../config.mak

../../tools/textfilter: ../../tools/textfilter.c
	make -C ../../tools/ textfilter

readme.txt: ../../tools/textfilter ../base_readme.txt ../../ChangeLog
	../../tools/textfilter ../base_readme.txt $@ PS2

PicoDrive.elf: ../../picodrive
	$(STRIP) $^ -o $@

rel: PicoDrive.elf readme.txt ../game_def.cfg
	cd out && zip -9 -r ../../../PicoDrive_ps2_$(VER).zip *
	rm -rf out
