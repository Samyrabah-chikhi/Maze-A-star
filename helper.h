#ifndef HELPER_H
#define HELPER_H

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef enum
{
    ROAD = 0,
    TRAVELED = 1,
    PATH = 2,
    ADDED = 3,
    GOAL = 4,
    WALL = 10
} TERRAIN_TYPE;

typedef struct point
{
    int x, y;
    int type;

    int gCost;
    int hCost;
    int fCost;

    bool visited;
    struct point *parent;
} point;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define BLOCK_SIZE 100

point **gridGenerator(int rectnumx, int rectnumy);
void drawBrickGrid(SDL_Renderer *renderer, point **grid, int rectnumx, int rectnumy);

SDL_Window *createWindow(const char *title);
SDL_Renderer *createRenderer(SDL_Window *window);
void clearScreen(SDL_Renderer *renderer);
void destroySDL(SDL_Window *window, SDL_Renderer *renderer);

int heuristic(point *a, point *b);

#endif