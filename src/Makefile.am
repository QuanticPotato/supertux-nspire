AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = supertux

supertux_LINK = @NSPIRE_LD@ -o @ELF_NAME@

supertux_SOURCES = \
    main.cpp \
    globals.cpp \
    menu.cpp \
    scene.cpp \
    screen.cpp \
    setup.cpp \
    text.cpp \
    texture.cpp \
    timer.cpp \
    lispreader.cpp \
    configfile.cpp \
    type.cpp \
    gameloop.cpp \
    high_scores.cpp \
    level.cpp \
    player.cpp \
    tile.cpp \
    title.cpp \
    worldmap.cpp \
    badguy.cpp \
    bitmask.cpp \
    physic.cpp \
    collision.cpp \
    sprite.cpp \
    world.cpp \
    special.cpp \
    particlesystem.cpp \
    gameobjs.cpp \
    resources.cpp \
    mousecursor.cpp \
    sprite_manager.cpp \
    intro.cpp \
    sprites_index.cpp \
    levels_index.cpp

all : all-am @EXE_NAME@

@EXE_NAME@ : @ZEHN_NAME@
	@NSPIRE_MAKE_PRG@ $^ $@
	chmod +x $@

@ZEHN_NAME@ : @ELF_NAME@
	@NSPIRE_GENZEHN@ --input $^ --output $@ @NSPIRE_ZEHN_FLAGS@
	chmod +x $@

clean: clean-am
	rm -f @ZEHN_NAME@ @EXE_NAME@ @ELF_NAME@
