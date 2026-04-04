#include "path_finder.h"

int step_forward(point **grid, int rectnumx, int rectnumy, point *start, point *goal)
{
    point *current = popLowestF();
    if (!current)
        return 0; 
    printf("Current: (%d,%d) | Cost: %d\n", current->y, current->x, current->fCost);
    if (current == goal)
    {
        // Reconstruct path
        point *temp = goal;
        while (temp != NULL)
        {
            temp->type = PATH;
            temp = temp->parent;
        }
        return 1;
    }
    else
    {
        current->type = TRAVELED;
    }

    int x, y;
    for (int i = -1; i <= 1; i++)
    {
        y = current->y / BLOCK_SIZE + i; // Convert pixel to grid index
        if (y < 0 || y >= rectnumy)
            continue;
        for (int j = -1; j <= 1; j++)
        {
            x = current->x / BLOCK_SIZE + j;
            if (x < 0 || x >= rectnumx)
                continue;
            if (i == 0 && j == 0)
                continue; // Skip current

            if (grid[y][x].type == TRAVELED || grid[y][x].type == WALL)
                continue;

            int cost = (i != 0 && j != 0) ? 14 : 10;
            int tentativeG = current->gCost + cost;
            if (tentativeG < grid[y][x].gCost)
            {
                grid[y][x].gCost = tentativeG;
                grid[y][x].hCost = heuristic(&grid[y][x], goal);
                grid[y][x].fCost = grid[y][x].gCost + grid[y][x].hCost;
                grid[y][x].parent = current;
                grid[y][x].type = ADDED;

                addOpen(&grid[y][x]);
            }
        }
    }
    return 0;
}
