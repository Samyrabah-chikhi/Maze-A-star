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

    SDL_FRect rect = {0, 0, 100, 100};
    int rectnumx = 12;
    int rectnumy = 8;

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
        drawBrickGrid(renderer, rect, rectnumx, rectnumy);

        SDL_RenderPresent(renderer);
    }

    destroySDL(window,renderer);

    return 0;
}
