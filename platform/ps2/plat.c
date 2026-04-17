/*
 * PicoDrive platform interface for PS2
 * (Modified for Menu Music - WAV Streamer)
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
static unsigned char bgm_stack[0x2000] __attribute__((aligned(16)));

static int sound_rates[] = { 11025, 22050, 44100, -1 };
struct plat_target plat_target = { .sound_rates = sound_rates };

/* BGM Background Thread - Streaming WAV */
static void bgm_thread_func(void *arg) {
    FILE *f = fopen("cdfs:/menu.wav;1", "rb");
    if (!f) {
        bgm_tid = -1;
        ExitDeleteThread();
        return;
    }

    fseek(f, 44, SEEK_SET); // Skip WAV header
    static char audio_buf[4096];

    while (bgm_running) {
        int bytes_read = fread(audio_buf, 1, sizeof(audio_buf), f);
        if (bytes_read <= 0) {
            fseek(f, 44, SEEK_SET); // Loop
            continue;
        }

        audsrv_wait_audio(bytes_read);
        audsrv_play_audio(audio_buf, bytes_read);
    }

    fclose(f);
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
    }
}

void plat_stop_bgm(void) {
    bgm_running = 0;
    // Brief wait for thread cleanup
    int timeout = 100;
    while (bgm_tid != -1 && timeout-- > 0) {
        usleep(1000);
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

/* base directory for configuration and save files */
int plat_get_root_dir(char *dst, int len)
{    
    strncpy(dst, "mc0:/PICO/", len);
    DIR *dir;
    if ((dir = opendir(dst))) 
        closedir(dir);
    else
        mkdir(dst, 0777);

    return (int)strlen(dst);
}

/* base directory for emulator resources */
int plat_get_skin_dir(char *dst, int len)
{
    if (len > 5)
        strcpy(dst, "cdfs:/skin/");
    else if (len > 0)
        *dst = 0;
    return (int)strlen(dst);
}

/* top directory for rom images */
int plat_get_data_dir(char *dst, int len)
{
    if (len > 5)
        strcpy(dst, "cdfs:/ROMS/ROMS_GENS/");
    else if (len > 0)
        *dst = 0;
    return (int)strlen(dst);
}

/* check if path is a directory */
int plat_is_dir(const char *path)
{
    DIR *dir;
    if ((dir = opendir(path))) {
        closedir(dir);
        return 1;
    }
    return 0;
}

/* current time in ms */
unsigned int plat_get_ticks_ms(void)
{
    return (unsigned int)(clock() / 1000);
}

/* current time in us */
unsigned int plat_get_ticks_us(void)
{
    return (unsigned int)clock();
}

/* sleep for some time in us */
void plat_wait_till_us(unsigned int us_to)
{
    unsigned int ticks = (unsigned int)clock();
    if (us_to > ticks)
        usleep(us_to - ticks);
}

/* sleep for some time in ms */
void plat_sleep_ms(int ms)
{
    usleep(ms * 1000);
}

/* wait until some event occurs, or timeout */
int plat_wait_event(int *fds_hnds, int count, int timeout_ms)
{
    return 0;
}

/* memory mapping functions */
void *plat_mmap(unsigned long addr, size_t size, int need_exec, int is_fixed)
{
    return malloc(size);
}

void *plat_mremap(void *ptr, size_t oldsize, size_t newsize)
{
    return realloc(ptr, newsize);
}

void plat_munmap(void *ptr, size_t size)
{
    free(ptr);
}

void *plat_mem_get_for_drc(size_t size)
{
    return NULL;
}

int plat_mem_set_exec(void *ptr, size_t size)
{
    return 0;
}

int _flush_cache (char *addr, const int size, const int op)
{ 
    FlushCache(0); // WRITEBACK_DCACHE
    FlushCache(2); // INVALIDATE_ICACHE
    return 0;
}

int posix_memalign(void **p, size_t align, size_t size)
{
    if (!p) return EINVAL;
    *p = memalign(align, size);
    return (*p ? 0 : ENOMEM);
}

/* lprintf */
void lprintf(const char *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
#if defined(LOG_TO_FILE)
    vfprintf(logFile, fmt, vl);
#else
    vprintf(fmt, vl);
#endif
    va_end(vl);
}

void plat_debug_cat(char *str) {}
