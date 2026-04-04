#include "helper.h"

SDL_Window *createWindow(const char *title)
{
    SDL_Window *window = SDL_CreateWindow(title, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window)
    {
        printf("Error creating window: %s\n", SDL_GetError());
    }
    return window;
}

SDL_Renderer *createRenderer(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
    }
    return renderer;
}

void clearScreen(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void drawBrickGrid(SDL_Renderer *renderer, SDL_FRect rect, int rectnumx, int rectnumy)
{

    for (int i = 0; i < rectnumy; i++)
    {
        for (int j = 0; j < rectnumx; j++)
        {

            SDL_SetRenderDrawColor(renderer, 158, 51, 51, 255);
            SDL_RenderFillRect(renderer, &rect);

            SDL_SetRenderDrawColor(renderer, 215, 197, 154, 255);
            SDL_RenderRect(renderer, &rect);

            rect.x += 100;
        }
        rect.x = 0;
        rect.y += 100;
    }
}

void destroySDL(SDL_Window *window, SDL_Renderer *renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}