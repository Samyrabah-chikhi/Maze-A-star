#include "path_finder.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = createWindow("Maze Runner");
    if (!window)
    {
        return -1;
    }

    SDL_Renderer *renderer = createRenderer(window);
    if (!renderer)
    {
        return -1;
    }

    SDL_Event event;
    bool quit = false;
    bool found = false;

    int rectnumx = 12;
    int rectnumy = 8;

    int startX = 0;
    int startY = 3;

    int goalX = 10;
    int goalY = 6;

    point **grid;
    grid = gridGenerator(rectnumx, rectnumy);

    grid[goalY][goalX].type = GOAL;
    grid[startY][startX].type = PATH;

    point *goal = &grid[goalY][goalX];
    point *start = &grid[startY][startX];
    start->gCost = 0;
    start->hCost = heuristic(start, goal);
    start->fCost = start->gCost + start->hCost;

    addOpen(start);

    while (!isOpenEmpty() && !quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        }

        if (step_forward(grid, rectnumx, rectnumy, start, goal) == 1)
        {
            grid[goalY][goalX].type = PATH;
            found = true;
        }
        else
        {
            grid[goalY][goalX].type = GOAL;
        }
        SDL_Delay(100);

        clearScreen(renderer);
        drawBrickGrid(renderer, grid, rectnumx, rectnumy);
        SDL_RenderPresent(renderer);

        if(found){
            SDL_Delay(5000);
            break;
        }
    }

    for (int i = 0; i < rectnumy; i++)
        free(grid[i]);
    free(grid);
    destroySDL(window, renderer);

    return 0;
}
