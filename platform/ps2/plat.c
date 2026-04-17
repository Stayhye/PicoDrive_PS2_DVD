/*
 * PicoDrive platform interface for PS2
 * (Modified for Menu Music)
 */

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

#include <kernel.h>
#include <iopcontrol.h>
#include <sbv_patches.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <ps2_filesystem_driver.h>
#include <ps2_joystick_driver.h>
#include <ps2_audio_driver.h>
#include <audsrv.h>

#include "../libpicofe/plat.h"

/* Global pointer reference for thread initialization */
extern void *_gp;

/* BGM Control Globals */
static int bgm_running = 0;
static int bgm_tid = -1;
static unsigned char bgm_stack[0x1000] __attribute__((aligned(16)));

static int sound_rates[] = { 11025, 22050, 44100, -1 };
struct plat_target plat_target = { .sound_rates = sound_rates };

/* BGM Background Thread */
static void bgm_thread_func(void *arg) {
    // Audsrv handles the MP3 decoding on the IOP processor
    // Loop is set to 1 to enable automatic looping
    audsrv_play_mp3("cdfs:/menu.mp3;1", 1);

    while (bgm_running) {
        audsrv_get_status();
        DelayThread(100000); 
    }

    audsrv_stop_audio();
    bgm_tid = -1;
    ExitDeleteThread();
}

/* External Hooks for main.c */
void plat_start_bgm(void) {
    if (bgm_running) return;
    
    ee_thread_t thread;
    memset(&thread, 0, sizeof(ee_thread_t));

    bgm_running = 1;

    thread.func = (void *)bgm_thread_func;
    thread.stack = bgm_stack;
    thread.stack_size = sizeof(bgm_stack);
    thread.initial_priority = 80;
    thread.gp_reg = &_gp;

    bgm_tid = CreateThread(&thread);
    if (bgm_tid >= 0) {
        StartThread(bgm_tid, NULL);
    } else {
        bgm_running = 0;
        printf("BGM: Failed to create thread\n");
    }
}

void plat_stop_bgm(void) {
    bgm_running = 0;
}

static void reset_IOP() {
    SifInitRpc(0);
#if !defined(DEBUG) || defined(BUILD_FOR_PCSX2)
    while (!SifIopReset(NULL, 0)) {};
#endif
    while (!SifIopSync()) {};
    SifInitRpc(0);
    sbv_patch_enable_lmb();
    sbv_patch_disable_prefix_check();
}

static void init_drivers() {
    init_ps2_filesystem_driver();
}

static void deinit_drivers() {
    deinit_ps2_filesystem_driver();
}

int plat_target_init(void) { return 0; }

void plat_target_finish(void) {
    plat_stop_bgm();
    audsrv_quit();
    deinit_drivers();
}

int plat_parse_arg(int argc, char *argv[], int *x) { return 1; }

void plat_early_init(void) {
    reset_IOP();
    init_drivers();

    // Load bundled IRX files from the /irx/ folder
    SifLoadModule("cdfs:/irx/libsd.irx;1", 0, NULL);
    SifLoadModule("cdfs:/irx/audsrv.irx;1", 0, NULL);
    
    if (audsrv_init() != 0) {
        printf("audsrv: failed to initialize\n");
    }

#if defined(LOG_TO_FILE)
    log_init();
#endif
}

/* ... Keep all your original functions (plat_get_ticks, ticks_us, ticks_ms, etc) here ... */
