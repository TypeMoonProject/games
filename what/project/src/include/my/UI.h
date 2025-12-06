#ifndef UI
#define UI

#include<SDL2/SDL.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_surface.h>
#include<stdbool.h>
#include<stdio.h>

typedef struct color{
    int r;
    int g;
    int b;
    int a;
}color;

char position[]="./sourse/01.jpg";
//(X,Y)起始点(W,H)区域宽高
//                 X   Y   W   H
SDL_Rect rect[]={{200,200,100,100},
        };
//            R G B A
color col[]={{0,0,0,50},     //半透明
            {255,0,0,255},    //
            {0,255,0,255},    //绿
            {0,0,255,255},    //
            {255,255,255,255},//白
        };
int speed=10;

SDL_Window* init_creat();
SDL_Renderer *create_renderer(SDL_Window *win);
SDL_Surface *load_image(char *position);
SDL_Renderer *draw_rectangle(SDL_Renderer *ren,SDL_Rect *rect,color *col);
void into_image(SDL_Window *win,SDL_Renderer *ren,SDL_Surface *ima);
void move_rect(SDL_Renderer *ren,SDL_Rect *rect,color *col,int speed);
void quit(SDL_Window *win,SDL_Renderer *ren);
void draw_ui(SDL_Renderer *ren);
void action(char *position,SDL_Rect *rect,color *col,int speed);

#endif