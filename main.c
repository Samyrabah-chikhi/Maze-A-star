#include "path_finder.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = createWindow("A* Maze Runner");
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
    bool paused = false;
    bool randomWorld = false;
    bool restartFlag = false;

    int rectnumx = GRID_COLS;
    int rectnumy = GRID_ROWS;
    
    printf("rectnumx: %d, rectnumy: %d\n", rectnumx, rectnumy);
    printf("BLOCK_SIZE: %d\n", BLOCK_SIZE);

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

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                int buttonY = WINDOW_HEIGHT - 50;
                int buttonWidth = 100;
                int buttonHeight = 40;
                if (mouseX >= 10 && mouseX <= 10 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight)
                {
                    randomWorld = true;
                }
                else if (mouseX >= 120 && mouseX <= 120 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight)
                {
                    paused = !paused;
                }
                else if (mouseX >= 230 && mouseX <= 230 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight)
                {
                    restartFlag = true;
                }
            }
        }

        if (!paused && !found && !isOpenEmpty())
        {
            if (step_forward(grid, rectnumx, rectnumy, start, goal) == 1)
            {
                grid[goalY][goalX].type = PATH;
                found = true;
            }
            else
            {
                grid[goalY][goalX].type = GOAL;
            }
            SDL_Delay(200);
        }

        if (randomWorld) {
            // Free old grid
            for (int i = 0; i < rectnumy; i++) free(grid[i]);
            free(grid);
            // Generate new
            grid = gridGenerator(rectnumx, rectnumy);
            // Reset start and goal
            grid[goalY][goalX].type = GOAL;
            grid[startY][startX].type = PATH;
            goal = &grid[goalY][goalX];
            start = &grid[startY][startX];
            start->gCost = 0;
            start->hCost = heuristic(start, goal);
            start->fCost = start->gCost + start->hCost;
            // Reset heap
            clearOpen();
            addOpen(start);
            found = false;
            paused = false;
            randomWorld = false;
        }

        if (restartFlag) {
            // Reset types and costs
            for (int i = 0; i < rectnumy; i++) {
                for (int j = 0; j < rectnumx; j++) {
                    if (grid[i][j].type != WALL) {
                        grid[i][j].type = ROAD;
                    }
                    grid[i][j].gCost = INT_MAX;
                    grid[i][j].hCost = 0;
                    grid[i][j].fCost = INT_MAX;
                    grid[i][j].parent = NULL;
                    grid[i][j].visited = false;
                }
            }
            grid[goalY][goalX].type = GOAL;
            grid[startY][startX].type = PATH;
            start->gCost = 0;
            start->hCost = heuristic(start, goal);
            start->fCost = start->gCost + start->hCost;
            clearOpen();
            addOpen(start);
            found = false;
            paused = false;
            restartFlag = false;
        }

        clearScreen(renderer);
        drawBrickGrid(renderer, grid, rectnumx, rectnumy);

        // Draw buttons
        int buttonY = WINDOW_HEIGHT - 50;
        int buttonWidth = 100;
        int buttonHeight = 40;
        SDL_FRect randomButton = {10, buttonY, buttonWidth, buttonHeight};
        SDL_FRect pauseButton = {120, buttonY, buttonWidth, buttonHeight};
        SDL_FRect restartButton = {230, buttonY, buttonWidth, buttonHeight};

        // Random button - Green
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &randomButton);

        // Pause button - Yellow
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &pauseButton);

        // Restart button - Red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &restartButton);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderRect(renderer, &randomButton);
        SDL_RenderRect(renderer, &pauseButton);
        SDL_RenderRect(renderer, &restartButton);

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
