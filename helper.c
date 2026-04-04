#include "helper.h"

void drawBrickGrid(SDL_Renderer *renderer, point **grid, int rectnumx, int rectnumy)
{
    SDL_FRect rect = {0, 0, BLOCK_SIZE, BLOCK_SIZE};

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
            else if(grid[i][j].type == ADDED)
            {
                SDL_SetRenderDrawColor(renderer, 204,125,99, 255);
            }
            else if (grid[i][j].type == TRAVELED)
            {
                SDL_SetRenderDrawColor(renderer, 97, 127, 141, 255);
            }
            else if (grid[i][j].type == PATH)
            {
                SDL_SetRenderDrawColor(renderer, 107, 66, 92, 255);
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

            grid[i][j].gCost = INT_MAX;
            grid[i][j].hCost = 0;
            grid[i][j].fCost = INT_MAX;
            grid[i][j].parent = NULL;
            grid[i][j].visited = false;

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

int heuristic(point *a, point *b)
{
    return 10 * (abs(a->x - b->x) / BLOCK_SIZE + abs(a->y - b->y) / BLOCK_SIZE);
}
