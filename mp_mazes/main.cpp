#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"
using namespace cs225;

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
    maze.makeMaze(100, 100);
    maze.solveMaze();
    PNG * png = maze.drawMazeWithSolution();
    png->writeToFile("mazeSolution.png");
    delete png;

    return 0;
}
