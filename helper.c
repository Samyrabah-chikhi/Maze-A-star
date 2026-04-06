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

            switch (grid[i][j].type)
            {
                case ROAD:
                    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255); // light gray
                    break;

                case ADDED:
                    SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255); // blue (open list)
                    break;

                case TRAVELED:
                    SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255); // light blue
                    break;

                case PATH:
                    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // yellow (final path)
                    break;

                case WALL:
                    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255); // dark gray
                    break;

                case GOAL:
                    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255); // green
                    break;

                default:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // debug (should not happen)
                    break;
            }

            SDL_RenderFillRect(renderer, &rect);

            // Grid border
            SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
            SDL_RenderRect(renderer, &rect);
        }
    }
}

point **gridGenerator(int rectnumx, int rectnumy)
{
    srand(time(NULL));
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
            if (rand() % 100 < 30)
            {
                grid[i][j].type = WALL;
            }
            else
            {
                grid[i][j].type = ROAD;
            }

            grid[i][j].gCost = INT_MAX;
            grid[i][j].hCost = 0;
            grid[i][j].fCost = INT_MAX;
            grid[i][j].parent = NULL;
            grid[i][j].visited = false;

            x += BLOCK_SIZE;
        }

        y += BLOCK_SIZE;
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
