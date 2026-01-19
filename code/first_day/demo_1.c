// Recursive Design demo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tigr.h"

typedef enum {
    SIERPINSKI,
    TREE,
    FLOOD
} Demo;

const char* title = "Recursuive Things";

float random_float_range(float min, float max) {
    float scale = (float)rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

void sierpinski_tri_squares(Tigr* bmp, int x, int y, int l, TPixel c, int depth){
    // Draw the sqaure
    if (depth == 0) {
        tigrFill(bmp, x, y, l, l, tigrRGB(0x00, 0x00, 0x00));
        return;
    }

    // Top square
    sierpinski_tri_squares(
        bmp, 
        (x + (l / 4)), 
        y, 
        (l / 2),
        c, 
        depth - 1
    );
    
    // Lower Left Square
    sierpinski_tri_squares(
        bmp, 
        x , 
        y + (l / 2), 
        (l / 2), 
        c, 
        depth - 1
    );

    // Lower Rigt Square
    sierpinski_tri_squares(
        bmp, 
        (x + (l / 2)), 
        (y + (l / 2)), 
        (l / 2), 
        c, 
        depth - 1
    );
    printf("End of Recurisive Loop\n");
}

#define THICKNESS 1
#define DECAY 0.7

void fractal_tree(Tigr* bmp, int x, int y, float angle, float d_angle, int l,TPixel c, int depth)
{
    if (depth == 0) return;

    int x1 = x + l * cos(angle);
    int y1 = y + l * sin(angle);

    for(int i = -THICKNESS; i < THICKNESS; i++){
        tigrLine(bmp, x + i, y, x1 + i, y1, c);
    }
    tigrLine(bmp, x, y, x1, y1, c);
    //tigrFillCircle(bmp, x, y, 10, tigrRGB(0xFF, 0, 0));


    fractal_tree(bmp, x1, y1, angle - d_angle, d_angle, l * DECAY, c, depth-1);
    // fractal_tree(bmp, x1, y1, angle , d_angle, l * DECAY, c, depth-1);
    fractal_tree(bmp, x1, y1, angle + d_angle, d_angle, l , c, depth-1);
}



int main(int argc, char const *argv[])
{
    srand(time(NULL));

    const int w = 2000;
    const int h = w;

    // All functions
    int depth = 0;
    TPixel color = tigrRGB(0x00, 0x00, 0x00);

    // Tree
    float angle = -M_PI_2;
    float d_angle = 0.5;
    float length = 500;

    Demo cur_demo = SIERPINSKI;

    Tigr *screen = tigrWindow(w, h, title, TIGR_FIXED);

    sierpinski_tri_squares(screen, 0, 0, w, tigrRGB(0x00, 0x00, 0x00), depth);

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        if (tigrKeyDown(screen, '1') && cur_demo != SIERPINSKI){
            depth = 0;
            cur_demo = SIERPINSKI;
            tigrClear(screen, tigrRGB(0xFF, 0xFF, 0xFF));
            sierpinski_tri_squares(screen, 0, 0, w, color, depth);
        }
        if (tigrKeyDown(screen, '2') && cur_demo != TREE) {
            depth = 0;
            cur_demo = TREE;
            tigrClear(screen, tigrRGB(0xFF, 0xFF, 0xFF));
            fractal_tree(screen, w / 2, h, angle, d_angle, length, color, depth);
        }

        if (tigrKeyDown(screen, TK_SPACE)){
            depth++;
            tigrClear(screen, tigrRGB(0xFF, 0xFF, 0xFF));

            switch(cur_demo){
                case SIERPINSKI:
                    sierpinski_tri_squares(
                        screen, 
                        0, 0, 
                        w, 
                        tigrRGB(0x00, 0x00, 0x00), 
                        depth
                    );
                    break;
                case TREE:
                    fractal_tree(
                        screen,
                        w / 2, h,
                        angle,
                        d_angle,
                        length,
                        color,
                        depth
                    );
                    break;
                default:
                    break;
            }
        }

        
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
