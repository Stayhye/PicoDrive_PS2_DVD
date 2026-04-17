/*
 * PicoDrive platform interface for PS2
 * (Modified for High Performance WAV Streaming)
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

/* Fix for the ALIGNED redefinition warning */
#ifdef ALIGNED
#undef ALIGNED
#endif
#include "../libpicofe/plat.h"

/* Embedded IRX Symbols */
extern unsigned char audsrv_irx[];
extern unsigned int size_audsrv_irx;
extern unsigned char libsd_irx[];
extern unsigned int size_libsd_irx;

extern void *_gp;

static int bgm_running = 0;
static int bgm_tid = -1;
static unsigned char bgm_stack[0x4000] __attribute__((aligned(16)));

static int sound_rates[] = { 11025, 22050, 44100, -1 };
struct plat_target plat_target = { .sound_rates = sound_rates };

static void bgm_thread_func(void *arg) {
    FILE *f = fopen("menu.wav", "rb");
    if (!f) f = fopen("MENU.WAV", "rb");
    if (!f) f = fopen("cdfs:/MENU.WAV;1", "rb");
    
    if (!f) {
        bgm_tid = -1;
        ExitDeleteThread();
        return;
    }

    fseek(f, 44, SEEK_SET); 
    
    /* 16KB buffer - balanced for disc speed */
    static char audio_buf[16384];

    while (bgm_running) {
        int bytes_read = (int)fread(audio_buf, 1, sizeof(audio_buf), f);
        if (bytes_read <= 0) {
            fseek(f, 44, SEEK_SET); // Loop
            continue;
        }

        /* This is the standard way to sync. It blocks the thread 
           until the IOP has room for 'bytes_read', naturally 
           regulating the playback speed to the wav's bitrate.
        */
        audsrv_wait_audio(bytes_read);
        audsrv_play_audio(audio_buf, bytes_read);

        /* Minor sleep to yield some CPU back to the main thread/loader */
        usleep(1000);
    }

    fclose(f);
    bgm_tid = -1;
    ExitDeleteThread();
}

void plat_start_bgm(void) {
    if (bgm_running) return;
    
    ee_thread_t thread;
    memset(&thread, 0, sizeof(ee_thread_t));
    bgm_running = 1;

    thread.func = (void *)bgm_thread_func;
    thread.stack = bgm_stack;
    thread.stack_size = sizeof(bgm_stack);
    /* Priority 100 ensures music doesn't choke the ROM loader */
    thread.initial_priority = 100; 
    thread.gp_reg = &_gp;

    bgm_tid = CreateThread(&thread);
    if (bgm_tid >= 0) {
        StartThread(bgm_tid, NULL);
    } else {
        bgm_running = 0;
    }
}

void plat_stop_bgm(void) {
    if (!bgm_running) return;
    bgm_running = 0;
    
    int timeout = 1000; 
    while (bgm_tid != -1 && timeout-- > 0) {
        usleep(100);
    }
}

static void reset_IOP() {
    SifInitRpc(0);
#if !defined(DEBUG) || defined(BUILD_FOR_PCSX2)
    while (!SifIopReset(NULL, 0)) {};
#endif
    while (!SifIopSync()) {};
    SifInitRpc(0);
    sbv_patch_enable_lmb();
    sbv_patch_disable_
