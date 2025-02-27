About PicoDrive
---------------

This is yet another SEGA 8 bit and 16 bit console emulator for emulating most
of the hardware SEGA has published up to and including the 32X.

Emulated 16 bit systems: Mega Drive/Genesis, Sega/Mega CD, 32X, Pico.
Emulated 8 bit systems: SG-1000, SC-3000, Master System/Mark III, Game Gear.

PicoDrive was originally written having ARM-based handheld devices
in mind, but later had got various improvements for other architectures
too, like SH2 recompilers for MIPS (mips32r2), ARM64 (armv8), RISC-V (RV64IM)
and PowerPC (G4/2.03).

PicoDrive was the first emulator ever to properly emulate Virtua Racing and
its SVP chip.

Currently the main development happens in the
[irixxxx's fork](https://github.com/irixxxx/picodrive),
[notaz's repo](https://github.com/notaz/picodrive) isn't updated as much.

### compiling

For platforms for which release builds are supplied the most easy way is to
use the release script in tools/release.sh. See the release script for details.
To make a platform build use

> tools/release.sh [version] [platforms...]

This will deliver a file for each platform in a the release-[version] directory.
A list of platforms is in the release script.

If you want to build an executable for a unixoid platform not listed in the
platform list, try using

> configure --platform=generic

If DRC is available for the platform, it should be enabled automatically.
For gp2x, wiz, and caanoo you may need to compile libpng first.

After configure, compile with

> make


### helix MP3 decoder for ARM

For 32 bit ARM platforms, the optimized helix MP3 decoder can be used to play
MP3 audio files with CD games. The helix source files are however not supplied
due to licensing issues. If you have legally obtained the sources, put them in
the platform/common/helix directory.

To compile the helix sources, set CROSS_COMPILE to your cross compiler prefix
(e.g. arm-linux-gnueabi-) and LIBGCC to your cross compiler's libgcc.a
(e.g. /usr/lib/gcc-cross/arm-linux-gnueabi/4.7/libgcc.a), and compile with

> make -C platform/common/helix CROSS_COMPILE=$CROSS_COMPILE LIBGCC=$LIBGCC

This will result in a shared library named ${CROSS_COMPILE}helix_mp3.so. Copy
this as libhelix.so to where the PicoDrive binary is on the target device.


Also, the support for helix must be enabled in PicoDrive by compiling with

> make PLATFORM_MP3=1

This switch is automatically enabled for Gamepark Holdings devices (gp2x,
caanoo and wiz). Without installing libhelix.so those devices will not play
MP3 audio.


### installing

The release scripts produces zip files which need to be installed on the
target device manually. Usually that means unpacking the file to some
directory on the device storage or on an SD card. See device specific
descriptions on the net.

Send bug reports, fixes etc to <derkub@gmail.com>


How to make it run
------------------


Then load a ROM and enjoy! Cartridge ROMs can be in various common formats and
can be zipped, one ROM file per zip. Certain extensions are used to detect the
console the ROM is for (.sg, .sc, .sms, .gg, .smd, .md, .gen, .32x, .pco).
For MSU games, load the .cue file and make sure the cartridge ROM has the same
name and is in the same directory.
Sega/Mega CD images can be in CHD, CUE+BIN/ISO or ISO/CSO+MP3/WAV format (read
below for more details).

This emulator has lots of options with various tweaks (for improved speed mostly),
but it should have best compatibility in it's default config. If suddenly you
start getting glitches or change something and forget what, use "Restore defaults"
option.


How to run Sega/Mega CD games
-----------------------------

To play any non-MSU CD game you need BIOS files. These files must be copied to
the same directory as PicoDrive files.
Files must be named as follows:

US: us_scd1_9210.bin, us_scd2_9306.bin, SegaCDBIOS9303.bin
EU: eu_mcd1_9210.bin, eu_mcd2_9303.bin, eu_mcd2_9306.bin
JP: jp_mcd1_9112.bin, jp_mcd1_9111.bin
these files can also be zipped.

The game must be dumped to CHD, CUE+BIN or CUE+ISO format.
ISO/CSO+MP3/WAV is also supported, but may cause problems.
When using CUE/BIN, you must load .cue file from the menu, or else the emu will
not find audio tracks.


How to run Sega Pico games
--------------------------

The Pico was special in that it had a large touchpad with an associated pen, and
so-called storyware, a combination of a cartridge with a book with up to 6 pages
on which the pen could also be used.

Most storywares used the touchpad with the pen as a pointer device, showing a
pointer icon on the screen when the pen was on the touchpad which could be moved
around. The pen has a dedicated button which was often used to select something
under the pointer icon, much like a mouse button.
However, a few games also had an overlay for the touchpad.

PicoDrive supports displaying both the storyware pages as well as a pad overlay.
They must be in png format and named like the storyware ROM without the
extension, plus "_<n>.png" for the storyware page <n>, and "_pad.png" for a pad
overlay. Storyware page images should have an aspect ration of 2:1, pad images
should have 4:3. All images can have arbitrary resolution and are automatically
scaled to fit the screen.

There are 2 menu actions for switching to pages or pad which will automatically
display the images if they are available. To allow for proper pen positioning
there is also an action for having the pen on the page/touchpad or not. Pen
positioning is done through the D-pad if the screen has been switched to either
pages or pad.


Other important stuff
---------------------

* Sega/Mega CD: If the background music is missing, the CD image format may be
  wrong. Currently .cue/bin or .chd is recommended. Be aware that there are
  lots of bad dumps on the web, and some use mp3 format for audio, which often
  causes problems (see below).
* While iso/mp3 format is supported, it's not recommended to use.
  Some of many problems with mp3 are listed below:
  * MP3s may be named incorrectly and will not play.
  * The game music may play too fast/too slow/out of sync, which means they
    are encoded incorrectly. PicoDrive is not a mp3 player, so all mp3s MUST
    be encoded at 44.1kHz stereo.
* Sega/Mega CD: If your games hang at the BIOS screen (with planets shown),
  you may be using a bad BIOS dump. Try another from a different source,
  like dumping it from your own console.


Options
-------

1. "Region"
This option lets you force the game to think it is running on machine from the
specified region, or just to set autodetection order. Also affects Sega/Mega CD.

2. "Hotkey save/load slot"
This is a slot number to use for savestates, when done by a button press outside
menu. This can also be configured to be changed with a button
(see "Key configuration").

3. "Interface options"
Enters Interface options menu (see below).

4. "Display options"
Enters Display options menu (see below).

5. "Sound options"
Enters Sound options menu (see below).

6. "MD/Genesis/Pico options"
Enters Mega Drive/Genesis/Pico options menu (see below).

7. "Sega/Mega CD add-on"
Enters Sega/Mega CD options menu (see below).

8. "32X add-on"
Enters 32X options menu (see below).

9. "SG/SMS/GG options"
Enters SG-1000/SC-3000/Master System/Game Gear options menu (see below).

10. "Advanced options"
Enters advanced options menu (see below).

11. "Restore defaults"
Restores all options (except controls) to defaults.


Interface options
-----------------

1. "Save global options"
If you save your config here it will be loaded on next ROM load, but only if
there is no game specific config saved (which will be loaded in that case).
You can press left/right to switch to a different config profile.

2. "Save game options"
Whenever you load current ROM again these settings will be loaded.

3. "Show FPS"
Self-explanatory. Format is XX/YY, where XX is the number of rendered frames and
YY is the number of emulated frames per second.

4. "Confirm save/load"
Allows to enable confirmation on saving (to prevent savestate overwrites), on
loading (to prevent destroying current game progress), and on both or none, when
using shortcut buttons (not menu) for saving/loading.

5. "Don't save last used ROM"
This will disable writing last used ROM to config on exit (what might cause SD
card corruption according to DaveC).


Display options
---------------

1. "Frameskip"
How many frames to skip rendering before displaying another.
"Auto" is recommended.

2. "Max auto frameskip"
How many frames to skip rendering at most if Frameskip is "Auto".



Sound options
-------------

1. "Enable sound"
Does what it says.

2. "Sound Quality"
Sound sample rate and stereo mode. Lower rates improve performance but sound
quality is lower.

3. "Sound filter"
Enables a low pass filter, similar to filtering in the real Mega Drive hardware.

4. "Filter strength"
Controls the sound filter. Higher values have more impact.


Mega Drive/Genesis/Pico options
-------------------------------

1. "Renderer"

2. "FM audio"
This enables emulation of six-channel FM sound synthesizer chip, which was used
to produce sound effects and music.

3. "FM filter"
This filter makes the sound output more accurate, but it is slower, especially
for lower sound rates.

4. "FM DAC noise"
Makes the sound output more like a first model Mega Drive/Genesis if enabled.
Later models had an improved FM chip without the DAC noise.


Sega/Mega CD add-on
-------------------

1. "Save RAM cart"
Here you can enable 64K RAM cart. Format it in BIOS if you do.

2. "CD LEDs"
The Sega/Mega CD unit had two blinking LEDs (red and green) on it. This option
will display them on top-left corner of the screen.

3. "CDDA audio"
This option enables CD audio playback.

4. "PCM audio"
This enables 8 channel PCM sound source. It is required for some games to run,
because they monitor state of this audio chip.


32X add-on
----------

1. "32X renderer"
This currently only affects how the Genesis/MD layers are rendered, which is
same as "Renderer" in display options.

2. "PWM audio"
Emulates PWM sound portion of 32X hardware. Disabling this may greatly improve
performance for games that dedicate one of SD2s for sound, but will cause
missing sound effects and instruments.

3. "PWM IRQ optimization"
Enabling this may improve performance, but may also introduce sound glitches.


SG/Master System/Game Gear options
----------------------------------

1. "System"
Selects which of the Sega 8 bit systems is emulated. "auto" is recommended.

2. "Cartridge mapping"
Some cartridges have hardware to enable additional capabilities, e.g. mapping
excess ROM storage or acessing a battery backed RAM storage. "auto" is
recommended, but in some rare cases it may be needed to manually select this.

3. "Game Gear LCD ghosting"
The Game Gear LCD display had a very noticeable inertia for image changes. This
setting enables emulating the effect, with "weak" being recommended.

4. "FM sound unit"
The Japanese Master System (aka Mark III) has an extension slot for an FM sound
unit. Some games made use of this for providing better music and effects.
Disabling this improves performance for games using the FM unit, and usually
means falling back to the non-FM sound.


Advanced options
----------------

1. "Disable frame limiter"
This allows games to run faster then 50/60fps, useful for benchmarking.

2. "Disable sprite limit"
The Mega Drive/Genesis had a limit on how many sprites (usually smaller moving
objects) can be displayed on single line. This option allows to disable that
limit. Note that some games used this to hide unwanted things, so it is not
always good to enable this option.

3. "Disable idle loop patching"
Idle loop patching is used to improve performance, but may cause compatibility
problems in some rare cases. Try disabling this if your game has problems.

4. "Emulate Game Gear LCD"
Disabling this option displays the full Game Gear VDP image with the normally
invisible borders.

5. "Enable dynarecs"
This enables dynamic recompilation for SH2 and SVP CPU code, which is improving
emulation performance greatly. SVP dynarec is only available on 32 bit ARM CPUs.

6. "Master SH2 cycles" / "Slave SH2 cycles"
This allows underclocking the 32X CPUs for better emulation performance. The
number has the same meaning as cycles in DOSBox, which is cycles per millisecond.
Underclocking too much may cause various in-game glitches.


Key configuration
-----------------

Select "Configure controls" from the options menu. Then selecting "Player <n>"
will display 2 columns. The left column lists names of Genesis/MD controller
buttons, the right column shows which key on your handheld is assigned to it.

There is also option to enable 6 button pads (will allow you to configure XYZ
buttons), and an option to set turbo rate (in Hz) for turbo buttons.

Players 3 and 4 can only be used if a 4 player adapter is selected for input
device 1, and the game is supporting this. Only 3 button pads are currently
supported in 4 player mode.


Cheat support
-------------

To use GG/patch codes, you must type them into your favorite text editor, one
per line. Comments may follow code after a whitespace. Only GameGenie and
Genecyst patch formats are supported.
Examples:

Genecyst patch (this example is for Sonic):

00334A:0005 Start with five lives
012D24:0001 Keep invincibility until end of stage
009C76:5478 each ring worth 2
009C76:5678 each ring worth 3
...

Game Genie patch (for Sonic 2):

ACLA-ATD4 Hidden palace instead of death egg in level select
...

Both GG and patch codes can be mixed in one file.

When the file is ready, name it just like your ROM file, but with additional
.pat extension, making sure that case matches.

Examples:

ROM: Sonic.zip
PATCH FILE: Sonic.zip.pat

ROM: Sonic 2.bin
PATCH FILE: Sonic 2.bin.pat

Put the file into your ROMs directory. Then load the .pat file as you would
a ROM. Then Cheat Menu Option should appear in main menu.


What is emulated?
-----------------

SG-1000/SC-3000/Master System/Game Gear:
z80 @ 3.6MHz: yes, DrZ80 (on 32 bit ARM CPUs) or CZ80 core
VDP: yes, all SG/SMS/GG modes, except some quirks not used by games
YM2413 FM: yes, digital-sound-antiques core
SN76489 PSG: yes, MAME core
Some in-cart mappers are also supported.

Genesis/Mega Drive:
main 68k @ 7.6MHz: yes, Cyclone (on 32 bit ARM CPUs) or FAME/C core
z80 @ 3.6MHz: yes, DrZ80 (on 32 bit ARM CPUs) or CZ80 core
VDP: yes, except some quirks and mode 4, not used by games
YM2612 FM: yes, optimized MAME core
SN76489 PSG: yes, MAME core
SVP chip: yes! This is first emu to ever do this
Pico PCM: yes, MAME core
Some Mega Drive/Genesis in-cart mappers are also supported.

Sega/Mega CD:
another 68k @ 12.5MHz: yes, Cyclone or FAME/C too
gfx scaling/rotation chip (custom ASIC): yes
PCM sound source: yes
CD-ROM controller: yes (mostly)
bram (internal backup RAM): yes
RAM cart: yes

32X:
2x SH2 @ 23MHz: yes, MAME core or custom recompiler
Super VDP: yes
PWM: yes

Pico:
main 68k @ 7.6MHz: yes, Cyclone (on 32 bit ARM CPUs) or FAME/C core
VDP: yes, except some quirks and mode 4, not used by games
SN76489 PSG: yes, MAME core
ADPCM: yes, MAME core
Pico Pen: yes
Pico Storyware pages: yes
Pico pad overlays: yes


Problems / limitations
----------------------

* Various VDP modes and quirks (window bug, scroll size 2, etc.) are not
  perfectly emulated, as very few games use this (if any at all).
* The emulator is designed for speed and not 100% accurate, so some things may
  not work as expected.
* The FM sound core doesn't support all features and has some accuracy issues.


Changelog
---------

1.91 (2013-10-12)
  + Added OpenDingux support (Paul Cercueil).
  * Save directory changed to ~/.picodrive/ for generic platform build
    (Paul Cercueil).
  + Revived GP2X/Caanoo/Wiz support.
  + Switched to cleaner CD controller code from Eke-Eke's Genesis Plus GX.
  * Fixed overflow issue where cd emulation would break after
    ~10 minutes of gameplay.
  * Fixed synchronization issue where model1 CD BIOS would randomly hang.

1.90 (2013-09-24)
  + 32X+CD emulation has been implemented.
  + CD graphics processor code has been replaced with much cleaner Eke-Eke's
    implementation from Genesis Plus GX.
  + CD PCM code has been completely rewritten.
  * Various CD compatibility issues have been solved. Hopefully no more
    regressions this time.
  * pandora: fixed tv-out (again), added automatic layer switching
  * libretro: fixed crackling sound for some games, added some core options
  * sdl: multiple joystick support has been fixed (Victor Luchits)

1.85 (2013-08-31)
  * Lots of 32X compatibility and accuracy improvements. All commercial games
    are booting now, but some still have issues.
  * Fixed some regressions in MegaCD code, like hang in jap BIOS.
  * Implemented pause for SMS.
  * Updated UI with improvements from PCSX ReARMed.
  * Frontend timing has been rewritten, should no longer slowly desync from
    LCD on pandora.
  * Added libretro and SDL 32/64bit ports, fixed compatibility issues with
    Android, iOS.
  * Various other things I forgot (it has been a while since last release..)

1.80 (2010-09-19)
  + Added Caanoo support. Now the GP2X binary supports GP2X F100/F200, Wiz
    and Caanoo. Lots of internal refactoring to support this.
  + Enabled 32X and SMS code. It's still unfinished but better release something
    now than wait even more (it has been in development for more then a year now
    due to various other projects or simply lack of time).
  + Pandora: added hardware scaler support, including ability to resize the
    layer and control filtering.
  + GP2X: Added basic line-doubling vertical scaling option.
  * Changed the way keys are bound, no need to unbind old one any more.
  * Handle MP3s with ID3 tags better (some MP3s with ID3 did not play).
  * Improved shadow/hilight color levels.
  * Fixed broken cheat support.

1.80beta2
  * Pandora: updated documentation.

1.80beta1 (2010-06-02)
  + Added pandora port.
  * Internal refactoring for 32x/SMS support.
  * Move mapper database to external file.
  + Added preliminary SMS emulation.
  + Added emulation of 32x peripherals including VDP. More work is needed here.
  + ARM: Added new SH2 recompiler for 32x. Some unification with SVP one.
  - Disabled most of the above bacause I'm not yet happy with the results.

1.56 (2009-09-19)
  * Changed sync in Sega CD emulation again. Should fix games that
    broke after changes in 1.51a.
  * Fixed default keys rebinding when they shouldn't.
  * Fixed sram being loaded from wrong game.
  * Emu should no longer hang shortly after using fast-forward.
  * Fixed save states sometimes no longer showing up in save state menu.
  * ARM: some asm code refactoring for slight speed improvement.

1.55
  + Added Wiz support. Now the same GP2X binary supports F100/F200 and Wiz.
  * Changed shadow/hilight handling a bit, fixes some effects in Pirates! Gold.
  * Complete input code rewrite. This fixes some limitations like not allowing
    to control both players using single input device. It also allows to use
    more devices (like keyboards) on Linux based devices.
  * Options menu has been reordered, "restore defaults" option added.

1.51b
  * Fixed a crash when uncompressed savestate is loaded.
  * Fixed an idle loop detection related hanging problem.
  * PSP: fixed another palette related regression.
  * UIQ3: updated frontend for the latest emu core.

1.51a
  * Fixed a sync problem between main and sub 68k. Should fix the hanging
    problem for some games.
  * ARM: fixed a crash when CD savestate is loaded just after loading ROM.

1.51
  * Improved bin_to_cso_mp3 tool, it should no longer complain about
    missing lame.exe even if it's in working dir.
  * Fixed a regression from 1.50, which caused slowdowns in Final Fight.
  * Fixed some regressions from 1.50 related to sprite limit and palette
    handling (caused graphical glitches in some games).
  + Added ABC turbo actions to key config.
  * Some other minor adjustments.

1.50
  + Added some basic support for Sega Pico, a MegaDrive-based toy.
  + Added proper support for cue/bin images, including cdda playback.
    .cue sheets with iso/cso/mp3/wav files listed in them are now
    supported too (but 44kHz restriction still applies).
  + Added bin_to_cso_mp3 tool, based on Exophase's bin_to_iso_ogg.
    The tool can convert .cue/.bin Sega CD images to .cso/.mp3.
  * Greatly improved Sega CD load times.
  * Changed how scheduling between 68k and z80 is handled. Improves
    performance for some games. Credits to Lordus for the idea.
  * YM2612 state was not 100% saved, this should be better now.
  * Improved renderer performance for shadow/hilight mode.
  * Added a hack for YM2612 frequency overflow issue (bleep noises
    in Shaq Fu, Spider-Man - The Animated Series (intro music), etc.)
    Credits to Nemesis @ spritesmind forum. Works only if sound rate
    is set to 44kHz.
  + Implemented some sprite rendering improvements, as suggested by
    Exophase. Games with lots of sprites now perform better.
  + Added better idle loop detection, based on Lordus' idea again.
  - "accurate timing" option removed, as disabling it no longer
    improves performance.
  - "accurate sprites" was removed too, the new sprite code can
    properly handle sprite priorities in all cases.
  * Timers adjusted again.
  * Improved .smd detection code.
  * ARM: fixed a bug in DrZ80 core, which could cause problems in
    some rare cases.
  * ARM: fixed a problem of occasional clicks on MP3 music start.
  * Minor general optimizations and menu improvements.
  * Fixed a bug in Sega CD savestate loader, where the game would
    sometimes crash after load.
  * Fixed a crash of games using eeprom (introduced in 1.40b).
  * PSP: fixed suspend/resume (hopefully for real).

1.40c
  * Fixed a problem with sound in Marble Madness.
  * GP2X: Fixed minor problem with key config.

1.40b
  * Fixed sprite masking code. Thanks to Lordus for explaining how it works.
  + Added "disable sprite limit" option.
  + PSP: added black level adjustment to display options.
  * Changed reset to act as 'soft' reset.
  + Added detection for Puggsy (it doesn't really have sram).
  * Some small timing adjustments.

1.40a
  * GP2X: Fixed a binding problem with up and down keys.
  * Default game config no longer overrides global user config.

1.40
  + Added support for SVP (Sega Virtua Processor) to emulate Virtua Racing,
    wrote ARM recompiler and some HLE code for VR. Credits to Exophase and
    Rokas for various ideas.
  * Changed config file format, files are now human-readable. Game specific
    configs are now held in single file (but old game config files are still
    read when new one is missing).
  * Fixed a bug where some key combos didn't work as expected.
  * Fixed a regression in renderer (ARM ports only, some graphic glitches in
    rare cases).
  * Adjusted fast renderer to work with more games, including VR.
  * Fixed a problem where SegaCD RAM cart data was getting lost on reset.
  * GP2X: Greatly reduced SegaCD FMV game slowdowns by disabling read-ahead
    in the Linux kernel and C library (thanks to Rokas and Exophase for ideas
    again). Be sure to keep "ReadAhead buffer" OFF to avoid slowdowns.
  + PicoDrive now comes with a game config file for some games which need
    special settings, so they should now work out-of-the-box. More games will
    be added with later updates.
  + GP2X: Files now can be deleted by pressing A+SELECT in the file browser.

1.35b
  * PSP: mp3 code should no longer fail on 1.5 firmware.
  + PSP: added gamma adjustment option.
  + Added .cso ISO format support. Useful for non-FMV games.
  * It is now possile to force a region after the ROM is loaded.
  * Fixed a sram bug in memhandlers (fixes Shining in the Darkness saves).
  * PSP: fixed another bug in memhanlers, which crashed the emu for some games
    (like NBA Jam and NHL 9x).
  + PSP: added suspend/resume handling for Sega CD games.
  + GP2X: added additional low volume levels for my late-night gaming sessions
    (in stereo mode only).
  + GP2X: added "fast forward" action in key config. Not recommended to use for
    Sega CD, may case problems there.
  * Some other small tweaks I forgot about.

1.35a
  * PSP: fixed a bug which prevented to load any ROMs after testing the BIOS.
  * PSP: fixed incorrect CZ80 memory map setup, which caused Z80 crashes and
    graphics corruption in EU Mega CD model1 BIOS menus.
  + PSP: added additional "set to 4:3 scaled" display option for convenience.
  + PSP: Added an option to disable frame limitter (works only with non-auto frameskip).

1.35
  + PSP port added. Lots of new code for it. Integrated modified FAME/C, CZ80 cores.
  + Some minor generic optimizations.
  * Patched some code which was crashing under PSP, but was working in GP2X/Giz
    (although it should have crashed there too).
  * Readme updated.

1.34
  + Gizmondo port added.
  + Some new optimizations in memory handlers, and for shadow/hilight mode.
  + Added some hacks to make more games work without enabling "accurate timing".
  * Adjusted timing for "accurate timing" mode and added preliminary VDP FIFO
    emulation. Fixes Double Dragon 2, tearing in Chaos Engine and some other games.
  * Fixed a few games not having sound at startup.
  * Updated serial EEPROM code to support more games. Thanks to EkeEke for
    providing info about additional EEPROM types and game mappers.
  * The above change fixed hang of NBA Jam.
  * Minor adjustments to control configurator.

1.33
  * Updated Cyclone core to 0.0088.
  + Added A r k's usbjoy fix.
  + Added "perfect vsync" option, which adjusts GP2X LCD refresh rate and syncs
    emulation to it to eliminate tearing and ensure smoothest scrolling possible.
  + Added an option to use A_SN's gamma curve for gamma correction (improves dark
    and bright color display for mk2s).
  * Sometimes stray sounds were played after loading a savestate. Fixed.
  * Fixed a problem where >6MB mp3s were corrupted in memory (sound glitches in
    Snatcher).
  * PD no longer overwrites video player code in memory, video player now can be
    used after exiting PicoDrive.
  * Fixed a bug which was causing Sonic 3 code to deadlock in some rare conditions
    if "accurate timing" was not enabled.
  * Fixed support for large hacked ROMs like "Ultimate Mortal Kombat Trilogy".
    Upto 10MB hacked ROMs are supported now.
  + Config profiles added (press left/right when saving config).
  * Changed key configuration behavior to the one from gpfce (should be more
    intuitive).
  + Added some skinning capabilities to the menu system with default skin by
    ketchupgun. Delete skin directory if you want old behaviour.
  * Some other little tweaks I forgot about.

1.32
  + Added some new scaling options.
  + Added ability to reload CD images while game is running (needed for games
    with multiple CDs, like Night Trap).
  + Added RAM cart emulation.
  * Fixed DMA timing emulation (caused lock-ups for some genesis games).
  * Idle loop detection was picking up wrong code and causing glitches, fixed.
  * The ym2612 code on 940 now can handle multiple updates per frame
    (fixes Thunger Force III "seiren" level drums for example).
  * Memory handlers were ignoring some writes to PSG chip, fixed (missing sounds in
    Popful Mail, Silpheed).
  * Improved z80 timing, should fix some sound problems.
  * Fixed a bug with sram register (fixes Phantasy Star 4).
  * ROM loader was incorrectly identifying some ROMs as invalid. Fixed.
  * Added code for PRG ram write protection register (Dungeon Explorer).
  * The memory mode register change in 1.31 was unsafe and caused some glitches in
    AH-3 Thunderstrike. Fixed.
  * Fixed a file descriptor leak.
  * Updated documentation, added Gmenu2x manual.

1.31
  * Changed the way memory mode register is read (fixes Lunar 2, broken in 1.30).
  * Fixed TAS opcode on sub-68k side (fixes Batman games).
  * File browser now filters out mp3s, saves and some other files, which are not ROMS.

1.30
  + ISO files now can be zipped. Note that this causes VERY long loading times.
  + Added data pre-buffering support, this allows to reduce frequency of short pauses
    in FMV games (caused by SD access), but makes those pauses longer.
  * Fixed PCM DMA transfers (intro FMV in Popful Mail).
  + Properly implemented "decode" data transformation (Jaguar XJ220).
  * Integrated "better sync" code into cyclone code, what made this mode much faster.
  * Fixed a bug related to game specific config saving.
  * Frameskipper was skipping sound processing, what caused some audio desyncs. Fixed.
  * Fixed reset not working for some games.
  + New assembly optimized memory handlers for CD (gives at least a few fps).
    Also re-enabled all optimizations from 0.964 release.
  + New idle-loop detection code for sub-68k. Speeds up at least a few games.

1.201
  + Added basic cheat support (GameGenie and Genecyst patches).

1.20
  * Fixed a long-standing problem in audio mixing code which caused slight distortions
    at lower sample rates.
  * Changed the way 920 and 940 communicates (again), should be more reliable and give
    slight performance increase.
  * Some optimizations in audio mixing code.
  * Some menu changes (background added, smaller font in ROM browser, savestate loader
    now can select slots).
  + 1M mode DMA transfers implemented (used by FMV games like Night Trap and Sewer Shark).
  + Games now can run code from WORD RAM in 1M mode (fixes Adventures of Willy Beamish).
  + "Cell arrange" address mapping is now emulated (Heart of the alien).
  + "Color numeric operation" is now emulated (text in Lunar 2, Silpheed intro graphics).
  + "Better sync" option added (prevents some games from hanging).

1.14
  + Region autodetection now can be customized.
  * When CDDA music tracks changed, old buffer contents were incorrectly played. Fixed.
  * BRAM is now automatically formatted (no need to enter BIOS menu and format any more).
  * Games now can be reset, CDDA music no longer breaks after loading another ISO.
  * Fixed a race condition between 920 and 940 which sometimes caused CDDA music not to play.
  + Savestates implemented for Sega/Mega CD.
  + PCM sound added.
  * Some mixer code rewritten in asm. 22kHz and 11kHz sound rates are now supported in
    Mega CD mode (but mp3s must still be 44kHz stereo).
  + Timer emulation added.
  * CDC DMA tansfers fixed. Snatcher and probably some more games now boot.
  * 2M word RAM -> VDP transfers fixed, no more corruption in Ecco and some other games.

1.10
  + GP2X: Added experimental Sega CD support.
  + GP2X: Added partial gmv movie playback support.

0.964 (2006-12-03)
  * GP2X: Fixed a sound buffer underflow issue on lower sample rate modes, which was
          happening for NTSC games and causing sound clicks.
  * GP2X: Redone key config to better support USB joysticks (now multiple joysticks
          should be useable and configurable).
  + GP2X: Added save confirmation option.
  + GP2X: Added 940 CPU crash detection.
  + ALL:  UIQ3 port added.

0.963
  * GP2X: Gamma-reset-on-entering-menu bug fixed.
  * GP2X: Recompiled PicoDrive with gcc profiling option set as described here:
          http://www.gp32x.com/board/index.php?showtopic=28490

0.962
  * GP2X: Fixed an issue with incorrect sounds in some games when dualcore operation
          was enabled (for example punch sound in SOR).
  * GP2X: Limited max volume to 90, because higher values often cause distortions.
  * GP2X: Fixed a bug with lower res scaling.
  * GP2X: Gamma is now reset on exit.

0.96
  * ALL:  Severely optimized MAME's YM2612 core, part of it is now rewritten in asm.
  + GP2X: The YM2612's code now can be run in GP2X's ARM940T CPU, what causes large
          performance increase.
  * ALL:  Accurate renderers are slightly faster now.
  + GP2X: Using quadruple buffering instead of doublebuffer now, also updated
          framelimitter, this should eliminate some scrolling and tearing problems.
  * GP2X: Fixed some flickering issues of 8bit accurate renderer.
  + GP2X: craigix's RAM timings now can be enabled in the menu (see advanced options).
  + GP2X: Added ability to save config for specific games only.
  + GP2X: Gamma control added (using GP2X's hardware capabilities for this).
  * GP2X: Volume keys are now configurable.
  + GP2X: GnoStiC added USB joystick support, I made it possible to use it for
          player 2 control (currently untested).
  * GP2X: squidgehack is now applied through kernel module (cleaner way).

0.95
  * ALL:  Fixed a bug in sprite renderer which was causing slowdowns for some games.
  + GP2X: Added command line support
  + GP2X: Added optional hardware scaling for lower-res games like Shining Force.
  * ALL:  Sound chips are now sampled 2 times per frame. This fixed some games which
          had missing sounds (Vectorman 2 1st level, Thunder Force 3 water level,
	      etc.).
  + ALL:  Added another accurate 8-bit renderer which is slightly faster and made it
          default.

0.945
  + GP2X: Added frame limiter for frameskipped modes.
  * GP2X: Increased brightness a bit (unused pixel bits now also contain data).
  * GP2X: Suidgehack was not applied correctly (was applied before allocating some
          high memory and had no effect).

0.94
  + Added GP2X port.
  * Improved interrupt timing, Mazin Saga and Burning Force now works.
  * Rewritten renderer code to better suit GP2X, should be faster on other
    ports too.
  + Added support for banking used by 12-in-1 and 4-in-1 ROMs (thanks Haze).
  + Added some protection device faking, used by some unlicensed games like
    Super Bubble Bobble, King of Fighters, Elf Wor, ... (thanks to Haze again)
  + Added primitive Virtua Racing SVP faking, so menus can be seen now.

0.93
  * Fixed a problem with P900/P910 key configuration in FC mode.
  * Improved shadow/hilight mode emulation. Still not perfect, but should be
    enough for most games.
  + Save state slots added.
  + Region selector added.

0.92
  VDP changes:
  * VDP emulation is now more accurate (fixes flickering in Chase HQ II,
    Super Hang-On and some other problems in other games).
  * HV counter emulation is now much more accurate. Fixes the Asterix games,
    line in Road Rash 3, etc.
  * Minor sprite and layer scroll masking bugs fixed.
  + Added partial interlace mode renderer (Sonic 2 vs mode)
  * Fixed a crash in both renderers when certain size window layers were used.
  + Added emulation of shadow/hilight operator sprites. Other shadow/hilight
    effects are still unemulated.
  + Sprite emulation is more accurate, sprite limit is emulated.
  + Added "accurate sprites" option, which always draws sprites in correct
    order and emulates sprite collision bit, but is significantly slower.

  Emulation changes:
  * Improved interrupt handling, added deferred interrupt emulation
    (Lemmings, etc).
  + Added serial EEPROM SRAM support (Wonder Boy in Monster World,
    Megaman - The Wily Wars and many EA sports games like NBA Jam).
  + Implemented ROM banking for Super Street Fighter II - The New Challengers
  * Updated to the latest version of DrZ80 core, integrated memory handlers
    in it for better performance. A noticeable performance increase, but save
	states may not work from the previous version (you can only use them with
	sound disabled in that case).
  + SRAM word read handler was using incorrect byte order, fixed.

  Changes in Cyclone 0.0086:
  + Added missing CHK opcode handler (used by SeaQuest DSV).
  + Added missing TAS opcode handler (Gargoyles,Bubba N Stix,...). As in real genesis,
    memory write-back phase is ignored (but can be enabled in config.h if needed).
  + Added missing NBCD and TRAPV opcode handlers.
  + Added missing addressing mode for CMP/EOR.
  + Added some minor optimizations.
  - Removed 216 handlers for 2927 opcodes which were generated for invalid addressing modes.
  + Fixed flags for ASL, NEG, NEGX, DIVU, ADDX, SUBX, ROXR.
  + Bugs fixed in MOVEP, LINK, ADDQ, DIVS handlers.
  * Undocumented flags for CHK, ABCD, SBCD and NBCD are now emulated the same way as in Musashi.
  + Added Uninitialized Interrupt emulation.
  + Altered timing for about half of opcodes to match Musashi's.

0.80
  * Nearly all VDP code was rewritten in ARM asm. Gives ~10-25% performance
    increase (depends on game).
  * Optimized 32-column renderer not to render tiles offscreen, games which
    use 32-column display (like Shining Force) run ~50% faster.
  + Added new "Alternative renderer", which gives another ~30-45% performance
    increase (in addition to mentioned above), but works only with some games,
    because it is missing some features (it uses tile-based rendering
    instead of default line-based and disables H-ints).
  + Added "fit2" display mode for all FC gamers. It always uses 208x146 for
    P800 and 208x208 for all other phones.
  + Added volume control for Motorolas (experimental).

  VDP changes:
  + Added support for vertical window (used by Vapor Trail, Mercs, GRIND
    Stormer and others).
  + Added sprite masking (hiding), adds some speed.
  + Added preliminary H counter emulation. Comix Zone and Sonic 3D Blast
    special stage are now playable.
  + Added column based vertical scrolling (Gunstar Heroes battleship level,
    Sonic and Knuckles lava boss, etc).

  Emulation changes:
  + Re-added and improved Z80 faking when Z80 is disabled. Many games now can
    be played without enabling Z80 (Lost Vikings, Syndicate, etc), but some
    still need it (International Superstar Soccer Deluxe).
  * Improved ym2612 timers, Outrun music plays at correct speed, voices in
    Earthworm Jim play better, more games play sound.
  * I/O registers now remember their values (needed for Pirates! Gold)
  + Added support for 6 button pad.

  Changes in Cyclone 0.0083wip:
  + Added missing CHK opcode (used by SeaQuest DSV).
  + Added missing TAS opcode (Gargoyles). As in real genesis, write-back phase
    is ignored (but is enabled for other systems).

  Backported stuff from Snes9x:
  * Fixed Pxxx jog up/down which were not working in game.
  + Added an option to gzip save states to save space.
  + The emulator now pauses whenever it is loosing focus, so it will now pause
    when alarm/ponecall/battery low/... windows come up.
  - Removed 'pause on phonecall' feature, as it is no longer needed.
  + Video fix for asian A1000s.

0.70
  * Started using tools from "Symbian GCC Improvement Project", which give
    considerable speed increase (~4fps in "center 90" mode).
  * Rewrote some drawing routines in ARM assembly (gives ~6 more fps in
    "center 90" mode).
  * Minor improvement to 0 and 180 "fit" modes. Now they look slightly better
    and are faster.
  * Minor stability improvements (emulator is less likely to crash).
  + Added some background for OSD text for better readability.
  + Added Pal/NTSC detection. This is needed for proper sound speed.
  + Implemented Reesy's DrZ80 Z80 emu. Made some changes to it with hope to make
    it faster.
  + Implemented ym2612 emu from the MAME project. Runs well but sometimes sounds
    a bit weird. Could be a little faster, so made some changes too.
  + Implemented SN76489 emu from the MAME project.
  + Added two separate sound output methods (mediaserver and cmaudiofb) with
    autodetection (needs testing).
  * Fixed VDP DMA fill emulation (as described in Charles MacDonald's docs),
    fixes Contra and some other games.

0.301
  Launcher:
  * Launcher now starts emulation process from current directory,
    not from hardcoded paths.
  * Improved 'pause on call' feature, should hopefully work with Motorola phones.

0.30 (2006-01-07)
  Initial release based on fDave's code.


Credits
-------

This emulator is made of the code from following people/projects:

notaz
core, 32X emulation, CD code, ARM asm renderers, dynamic recompilers,
Pandora, GPH device, PSP, Gizmondo ports, CPU core hacks
lots of additional coding (see changeLog).
Homepage: http://notaz.gp2x.de/

irixxxx
improvements to dynamic recompilers, 32X emulation, ARM asm, sound, VDP,
platforms (GPH, PSP, generic linux), added SG-1000 and Game Gear support,
fixed a lot of bugs (and probably added more new bugs), cleaned up stuff,
probably more that I've already forgotten.

fDave
project starter
Cyclone 68000 core and PicoDrive core itself

Chui
FAME/C 68k interpreter core
(based on C68K by Stephane Dallongeville)

Stephane Dallongeville (written), NJ (optimized)
CZ80 Z80 interpreter core

Reesy & FluBBa
DrZ80, the Z80 interpreter written in ARM assembly.
Homepage: http://reesy.gp32x.de/ (defunct)

Tatsuyuki Satoh, Jarek Burczynski, MAME development
software implementation of Yamaha FM sound generator

MAME development
Texas Instruments SN76489 / SN76496 programmable tone/noise generator
Homepage: http://www.mame.net/

Eke-Eke
CD graphics processor and CD controller implementation (from Genesis Plus GX)

Additional thanks
-----------------

* Charles MacDonald (http://cgfm2.emuviews.com/) for old but still very useful
  info about genesis hardware.
* Steve Snake for all that he has done for Genesis emulation scene.
* Stephane Dallongeville for writing Gens and making it open source.
* Tasco Deluxe for his reverse engineering work on SVP and some mappers.
* Bart Trzynadlowski for his SSFII and 68000 docs.
* Haze for his research (http://mamedev.emulab.it/haze/).
* Lordus, Exophase and Rokas for various ideas.
* Nemesis for his YM2612, VDP research and docs.
* Eke-Eke for sharing the knowledge and his work on Genesis Plus GX.
* Many posters at spritesmind.net forums for valuable information.
* Mark and Jean-loup for zlib library.
* ketchupgun for the skin.
* GP2X specific help: rlyeh, Squidge, Dzz, A_SN, Alex and GP32X posters.
* Gizmondo code: Kingcdr, Reesy, jens.l (for the device itself)
* Hardware: craigix (GP2X), EvilDragon (Wiz, Caanoo, Pandora, ...)
  and jens.l (Gizmondo)
* Paul Cercueil for OpenDingux port.
* Inder for some graphics.
* squarepusher for some libretro fixes
* Hiroshica for support of japanese Mark-III extended YM2413 sound
* Anyone else I forgot. Let me know if it's you.


License
-------

This program and its code is released under the terms of MAME license:

 Redistribution and use of this code or any derivative works are permitted
 provided that the following conditions are met:

 * Redistributions may not be sold, nor may they be used in a commercial
 product or activity.

 * Redistributions that are modified from the original source must include the
 complete source code, including the source code for all components used by a
 binary built from the modified sources. However, as a special exception, the
 source code distributed need not include anything that is normally distributed
 (in either source or binary form) with the major components (compiler, kernel,
 and so on) of the operating system on which the executable runs, unless that
 component itself accompanies the executable.

 * Redistributions must reproduce the above copyright notice, this list of
 conditions and the following disclaimer in the documentation and/or other
 materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

SEGA/Master System/Game Gear/Genesis/Mega Drive/SEGA CD/Mega CD/32X/Pico are
trademarks of Sega Enterprises Ltd.

