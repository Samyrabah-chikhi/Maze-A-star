#include <SDL3/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

void drawBrickGrid(SDL_Renderer *renderer, SDL_FRect rect, int rectnumx, int rectnumy);
void clearScreen(SDL_Renderer *renderer);
SDL_Window *createWindow(const char *title);
SDL_Renderer *createRenderer(SDL_Window *window);
void destroySDL(SDL_Window *window, SDL_Renderer *renderer);