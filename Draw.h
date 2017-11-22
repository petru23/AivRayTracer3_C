#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#ifndef DRAW_H
#define DRAW_H

struct draw_context
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    unsigned int width;
    unsigned int height;
    float delta_time;
    float aspect_ratio;
    unsigned long long last;
};

typedef struct draw_context draw_context_t;

struct draw_color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

typedef struct draw_color draw_color_t;

draw_context_t *draw_context_new(const char *, unsigned int, unsigned int);
void draw_context_destroy(draw_context_t *);
void draw_context_blit(draw_context_t *);
void draw_context_clear(draw_context_t *, draw_color_t);
void draw_context_put_pixel(draw_context_t *, int, int, draw_color_t);
draw_color_t draw_scaled(draw_color_t, float);
#endif