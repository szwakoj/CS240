// Sorting algorithm visualizer
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>
#include <math.h>
#include <string.h>

#include "tigr.h"
#include "miniaudio.h"

void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

typedef struct {
    float frequency;  // Update this from your main thread
    float volume;
} ToneGenerator;

void tone_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ToneGenerator* gen = (ToneGenerator*)pDevice->pUserData;
    float* output = (float*)pOutput;
    static double phase = 0.0;
    
    double phaseIncrement = 2.0 * 3.14159265359 * gen->frequency / pDevice->sampleRate;
    
    for (ma_uint32 i = 0; i < frameCount; i++) {
        float sample = gen->volume * (float)sin(phase);
        output[i * 2 + 0] = sample;
        output[i * 2 + 1] = sample;
        phase += phaseIncrement;
    }
}

#define MAX_SIZE 1000

typedef struct {
    int array[MAX_SIZE];
    int size;

    int num_compare;
    int num_swap;
    int num_get;

    int highlight_i;
    int highlight_j;

    Tigr *bmp;
    int w;
    int h;
    // VisMode mode;

    char cur_sort[256];

    ToneGenerator* gen;

    void (*on_compare)(int i, int j, int i_val, int j_val, ToneGenerator* gen);
    void (*on_swap)(int i, int j, int i_val, int j_val, ToneGenerator* gen);
    void (*on_get)(int i, int val, ToneGenerator* gen);
} ArrayVis;

bool less_than(int a, int b) { return a < b; }
bool greater_than(int a, int b) { return a > b; }

void vis_init(ArrayVis* vis)
{
    if (vis->size > MAX_SIZE)
        vis->size = MAX_SIZE;

    vis->num_compare = 0;
    vis->num_swap = 0;
    vis->num_get = 0;

    for (int i = 0; i < vis->size; i++) {
        vis->array[i] = i;
    }
}

bool vis_compare(ArrayVis* vis, int i, int j, bool (*comparison)(int, int))
{
    if (vis->on_compare != NULL)
        vis->on_compare(i, j, vis->array[i], vis->array[j], vis->gen);

    vis->num_compare++;

    vis->highlight_i = i;
    vis->highlight_j = j;

    return comparison(vis->array[i], vis->array[j]);
}  

void vis_swap(ArrayVis* vis, int i, int j)
{
    if (vis->on_swap != NULL)
        vis->on_swap(i, j, vis->array[i], vis->array[j], vis->gen);


    int temp = vis->array[i];
    vis->array[i] = vis->array[j];
    vis->array[j] = temp;

    vis->highlight_i = i;
    vis->highlight_j = j;

    vis->num_swap++;
}

int vis_get(ArrayVis* vis, int i)
{
    if (vis->on_get != NULL)
        vis->on_get(i, vis->array[i], vis->gen);

    vis->highlight_i = i;

    vis->num_get++;
    
    return vis->array[i];
}

void vis_randomize(ArrayVis* vis)
{
    for (int i = 0; i < vis->size; i++) {
        int j = rand() % vis->size;
        vis_swap(vis, i, j);
    }
}

void vis_draw(ArrayVis* vis)
{
    int bar_w = vis->w / vis->size;

    tigrClear(vis->bmp, tigrRGB(0,0,0));

    for (int i = 0; i < vis->size; i++) {
        int bar_h = vis->h * vis->array[i] / vis->size;

        TPixel color =  tigrRGB(0xFF, 0xFF, 0xFF);

        if (i == vis->highlight_i){
            color = tigrRGB(0x0, 0xFF, 0x0);
        } else if (i == vis->highlight_j) {
            color = tigrRGB(0xFF, 0x0, 0x0);
        }

        tigrFillRect(vis->bmp, i * bar_w, vis->h - bar_h, bar_w, bar_h, color);
    }

    char stats[256];
    sprintf(stats, "Size: %d | Sort: %s\nCompares: %d | Swaps: %d | Gets: %d", 
            vis->size, vis->cur_sort, vis->num_compare, vis->num_swap, vis->num_get);
    tigrPrint(vis->bmp, tfont, 10, 10, tigrRGB(0xff, 0xff, 0xff), stats);
}

void on_compare(int i, int j, int i_val, int j_val, ToneGenerator* gen)
{
    gen->frequency = 100 + (i_val * 10);
    gen->volume = 0.3f;
}

void on_swap(int i, int j, int i_val, int j_val, ToneGenerator* gen)
{
    gen->frequency = 100 + ((i_val - j_val) * 10);
    gen->volume = 0.3f;
}

void on_get(int i, int i_val, ToneGenerator* gen)
{
    gen->frequency = 100 + ( i_val * 10);
    gen->volume = 0.3f;
}

#include "sorts.c"

typedef enum {
    SINGLE,
    CYCLE,
    ALL
} NumSorts;

typedef enum {
    BARS,
    RAINBOW,
    PICTURE
} RenderMode;


const char* title = "Sorting Visualizer";

int main(int argc, char const *argv[])
{  
    srand(time(NULL));

    int num_algos = sizeof(sorts) / sizeof(Sort);

    NumSorts num_sorts;
    RenderMode render_mode;

    int cur_sort = -1;

    if (argc == 1) {
        num_sorts = CYCLE;
        render_mode = BARS;
    } else if (argc == 2) {
        if (!strcmp(argv[1], "all")) {
            num_sorts = ALL;
            render_mode = BARS;
        } else {
            num_sorts = SINGLE;
            render_mode = BARS;
            cur_sort = argv[1][0]-48;
        }
    } 
    
    // Sound Stuff
    ToneGenerator gen = { 440.0f, 0.0f };  // Start silent
    
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_f32;
    config.playback.channels = 2;
    config.sampleRate        = 48000;
    config.dataCallback      = tone_callback;
    config.pUserData         = &gen;
    
    ma_device device;
    ma_device_init(NULL, &config, &device);
    ma_device_start(&device);

    int size = 100;
    Tigr *screen;
    ArrayVis vis_single;
    ArrayVis vis_list[12];

    // Setting up visualizer
    if (num_sorts == ALL) {
        int w = 200;
        int h = 200;

        for(int i = 0; i < 12; i++) {

            Tigr *bmp = tigrBitmap(w,h);

            vis_list[i] = (ArrayVis){
                .size=size,
                .bmp=bmp,
                .w=w, .h=h,
                .gen=&gen,
                .on_compare=on_compare,
                .on_get=on_get,
                .on_swap=on_swap
            };

            vis_init(&vis_list[i]);
            vis_randomize(&vis_list[i]);
            vis_list[i].num_swap = 0;
        }

        screen = tigrWindow(w * 6, h * 2, title, TIGR_FIXED);

    } else {
        int w = 1000;
        int h = 500;
        screen = tigrWindow(w, h, title, TIGR_FIXED);
        int array[MAX_SIZE] = {0};
        

        vis_single = (ArrayVis){
            .size=size,
            .bmp=screen,
            .w=w, .h=h,
            .gen=&gen,
            .on_compare=on_compare,
            .on_get=on_get,
            .on_swap=on_swap
        };

        vis_init(&vis_single);
        vis_randomize(&vis_single);
        vis_single.num_swap = 0;
    }

    // Main draw loop
    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

        switch (num_sorts) {
            case SINGLE:
                if (!is_sorted(&vis_single, less_than)) {
                    strcpy(vis_single.cur_sort, sorts[cur_sort].name);

                    sorts[cur_sort].sort_func(&vis_single);

                    for (int i=0 ; i < vis_single.size; i++){
                        vis_get(&vis_single, i);
                        vis_draw(&vis_single);
                        tigrUpdate(screen);
                    }
                }      
                break;
            case CYCLE:
                for (int i = 0; i < num_algos - 2; i++) {
                    strcpy(vis_single.cur_sort, sorts[i].name);
                    vis_single.num_compare = 0;
                    vis_single.num_get = 0;
                    vis_single.num_swap = 0;


                    sorts[i].sort_func(&vis_single);

                    for (int i=0 ; i < vis_single.size; i++){
                        vis_get(&vis_single, i);
                        vis_draw(&vis_single);
                        tigrUpdate(screen);
                    }

                    vis_randomize(&vis_single);
                }
                break;
            case ALL:
                tigrClear(screen, tigrRGB(0, 0, 0));
                for (int i = 0; i < 12 && i < num_algos; i++) {
                    int grid_x = (i % 6) * 200;
                    int grid_y = (i / 6) * 200;
                    vis_draw(&vis_list[i]);
                    tigrBlit(screen, vis_list[i].bmp, grid_x, grid_y, 0, 0, 200, 200);
                }

                break;
            default:
        }

        tigrUpdate(screen);
    }

    ma_device_uninit(&device);
    
    return 0;
}
