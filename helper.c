#include "helper.h"

void drawBrickGrid(SDL_Renderer *renderer, point **grid, int rectnumx, int rectnumy, int size)
{
    SDL_FRect rect = {0, 0, size, size};

    for (int i = 0; i < rectnumy; i++)
    {
        for (int j = 0; j < rectnumx; j++)
        {
            rect.x = grid[i][j].x;
            rect.y = grid[i][j].y;

            if (grid[i][j].type == ROAD)
            {
                SDL_SetRenderDrawColor(renderer, 158, 51, 51, 255);
            }
            else if (grid[i][j].type == TRAVELED)
            {
                SDL_SetRenderDrawColor(renderer, 97, 127, 141, 255);
            }
            else if (grid[i][j].type == WALL)
            {
                SDL_SetRenderDrawColor(renderer, 61, 67, 75, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 67, 160, 71, 255);
            }
            SDL_RenderFillRect(renderer, &rect);

            SDL_SetRenderDrawColor(renderer, 215, 197, 154, 255);
            SDL_RenderRect(renderer, &rect);
        }
    }
}

point **gridGenerator(int rectnumx, int rectnumy)
{
    int y = 0;

    point **grid = malloc(rectnumy * sizeof(point *));

    for (int i = 0; i < rectnumy; i++)
    {
        grid[i] = malloc(rectnumx * sizeof(point));

        int x = 0;
        for (int j = 0; j < rectnumx; j++)
        {
            grid[i][j].x = x;
            grid[i][j].y = y;
            grid[i][j].type = ROAD;

            x += 100;
        }

        y += 100;
    }

    return grid;
}

void clearScreen(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

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

void destroySDL(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int heuristic(point *a, point *b, int cellSize) {
    return abs(a->x - b->x)/cellSize + abs(a->y - b->y)/cellSize;
}
