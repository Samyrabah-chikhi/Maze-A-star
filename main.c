#include "helper.h"

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

    int rectnumx = 12;
    int rectnumy = 8;
    int size = 100;

    int startX = 0;
    int startY = 0;

    int goalX = 9;
    int goalY = 6;

    point **grid = gridGenerator(rectnumx, rectnumy);
    grid[goalY][goalX].type = GOAL;       
    grid[startX][startY].type = TRAVELED; 


    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        }

        clearScreen(renderer);
        drawBrickGrid(renderer, grid, rectnumx, rectnumy, size);
        SDL_RenderPresent(renderer);

    }

    for (int i = 0; i < rectnumy; i++)
        free(grid[i]);
    free(grid);
    destroySDL(window, renderer);

    return 0;
}
